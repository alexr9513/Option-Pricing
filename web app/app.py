from flask import Flask, render_template, request, jsonify
import subprocess
import os
import platform

app = Flask(__name__)

EXECUTABLE_EXTENSIONS = ".exe" if platform.system() == "Windows" else ""

BS_PRICER = f"./bs_pricer{EXECUTABLE_EXTENSIONS}"
BS_MC_PRICER = f"./bs_mc_pricer{EXECUTABLE_EXTENSIONS}"
CRR_PRICER = f"./crr_pricer{EXECUTABLE_EXTENSIONS}"

# Ensure all executables have execution permissions if on Unix-like systems
if platform.system() != "Windows":
    for exe in [BS_PRICER, BS_MC_PRICER, CRR_PRICER]:
        os.chmod(exe, 0o755)

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/api/price', methods=['POST'])
def price_option():
    try:
        data = request.json
        pricing_method = data['pricing_method']
        option_type = data['option_type']
        
        # Common parameters
        S0 = data['S0']
        K = data['K']
        T = data['T']
        r = data['r']
        sigma = data['sigma']
        
        # Execute the appropriate pricer based on method
        if pricing_method == 'black_scholes':
            cmd = [BS_PRICER, option_type, str(S0), str(K), str(T), str(r), str(sigma)]
        elif pricing_method == 'monte_carlo':
            m = data.get('m', 12)  # Default to monthly fixings if not provided
            nb_simulations = data.get('nb_simulations', 10000)
            ci_target = data.get('ci_target', 0.1)
            cmd = [BS_MC_PRICER, option_type, str(S0), str(K), str(T), str(r), str(sigma), 
                   str(m), str(nb_simulations), str(ci_target)]
        elif pricing_method == 'binomial':
            N = data.get('N', 100)  # Default to 100 steps if not provided
            cmd = [CRR_PRICER, option_type, str(S0), str(K), str(T), str(r), str(sigma), str(N)]
        else:
            return jsonify({'error': 'Invalid pricing method'}), 400
        
        # Run the executable
        result = subprocess.run(cmd, capture_output=True, text=True)
        
        if result.returncode != 0:
            return jsonify({'error': f'Execution error: {result.stderr}'}), 500
        
        # Parse the output
        price = float(result.stdout.strip())
        
        return jsonify({'price': price})
    
    except Exception as e:
        return jsonify({'error': str(e)}), 500

@app.route('/templates/<path:path>')
def serve_template(path):
    return render_template(path)

if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0', port=5000)