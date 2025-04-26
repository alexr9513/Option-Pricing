import os
import subprocess
import json
from flask import Flask, render_template, request, jsonify

app = Flask(__name__)

# Define the executable names - adjust these to match your compiled filenames
BS_PRICER = "./bs_pricer.exe"  # Using .exe extension for Windows
BS_MC_PRICER = "./bs_mc_pricer.exe"
CRR_PRICER = "./crr_pricer.exe"

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/price', methods=['POST'])
def price_option():
    data = request.get_json()
    pricing_method = data.get('pricing_method')
    
    try:
        if pricing_method == "black_scholes":
            result = run_bs_pricer(data)
        elif pricing_method == "monte_carlo":
            result = run_bs_mc_pricer(data)
        elif pricing_method == "binomial_tree":
            result = run_crr_pricer(data)
        else:
            return jsonify({"error": "Invalid pricing method"}), 400
        
        return jsonify({"price": result})
    except Exception as e:
        return jsonify({"error": str(e)}), 500

def run_bs_pricer(data):
    # Extract parameters for Black-Scholes
    option_type = data.get('option_type')
    S0 = data.get('S0')
    K = data.get('K')
    T = data.get('T')
    r = data.get('r')
    sigma = data.get('sigma')
    
    # Execute bs_pricer
    cmd = [
        BS_PRICER, 
        option_type,
        str(S0),
        str(K),
        str(T),
        str(r),
        str(sigma)
    ]
    
    result = subprocess.run(cmd, capture_output=True, text=True)
    
    if result.returncode != 0:
        raise Exception(f"Error running bs_pricer: {result.stderr}")
    
    return float(result.stdout.strip())

def run_bs_mc_pricer(data):
    # Extract parameters for Monte Carlo
    option_type = data.get('option_type')
    S0 = data.get('S0')
    K = data.get('K')
    T = data.get('T')
    r = data.get('r')  
    sigma = data.get('sigma')
    m = data.get('m', 12)  # Default 12 fixings per year
    nb_simulations = data.get('nb_simulations', 10000)
    ci_target = data.get('ci_target', 0.1)
    
    # Execute bs_mc_pricer
    cmd = [
        BS_MC_PRICER,
        option_type,
        str(S0),
        str(K),
        str(T),
        str(r),
        str(sigma),
        str(m),
        str(nb_simulations),
        str(ci_target)
    ]
    
    result = subprocess.run(cmd, capture_output=True, text=True)
    
    if result.returncode != 0:
        raise Exception(f"Error running bs_mc_pricer: {result.stderr}")
    
    return float(result.stdout.strip())

def run_crr_pricer(data):
    # Extract parameters for Binomial Tree (CRR)
    option_type = data.get('option_type')
    S0 = data.get('S0')
    K = data.get('K')
    T = data.get('T')
    r = data.get('r')
    sigma = data.get('sigma')
    N = data.get('N', 100)  # Number of steps
    U = data.get('U', 1.01)  # Up factor
    D = data.get('D', 0.99)  # Down factor
    R = data.get('R')  # Risk-free rate per period
    
    # Execute crr_pricer
    cmd = [
        CRR_PRICER,
        option_type,
        str(S0),
        str(K),
        str(T),
        str(r),
        str(sigma),
        str(N),
        str(U),
        str(D),
        str(R)
    ]
    
    result = subprocess.run(cmd, capture_output=True, text=True)
    
    if result.returncode != 0:
        raise Exception(f"Error running crr_pricer: {result.stderr}")
    
    return float(result.stdout.strip())

if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0', port=5000)