#pragma once
#include <vector>
#include <iostream>

template <typename T>
class BinaryTree {
private:
    int _depth;
    std::vector<std::vector<T>> _tree;

public:
    BinaryTree() : _depth(0) {}

    void setDepth(int depth) {
        _depth = depth;
        _tree.resize(depth + 1);
        for (int i = 0; i <= depth; ++i) {
            _tree[i].resize(i + 1);
        }
    }

    void setNode(int depth, int index, T value) {
        if (depth >= 0 && depth < _tree.size() && index >= 0 && index < _tree[depth].size()) {
            _tree[depth][index] = value;
        }
        else {
            throw std::out_of_range("Invalid depth or index");
        }
    }

    T getNode(int depth, int index) const {
        if (depth >= 0 && depth < _tree.size() && index >= 0 && index < _tree[depth].size()) {
            return _tree[depth][index];
        }
        else {
            throw std::out_of_range("Invalid depth or index");
        }
    }

    void display() const {
        for (const auto& level : _tree) {
            for (const auto& node : level) {
                std::cout << node << " ";
            }
            std::cout << std::endl;
        }
    }
};
