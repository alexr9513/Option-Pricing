#pragma once
#include <iostream>
#include <vector>

template <typename T>
class BinaryTree
{
private:
	int _depth;
	std::vector<std::vector<T>> _tree;
public:
	void SetDepth(int depth);
	void SetNode(int,int,T);
	T GetNode(int,int);
	void display();
};

template <typename T>
void BinaryTree<T>::SetDepth(int depth) {
	_depth = depth;
	_tree.resize(_depth);
	for (int i = 0; i < _depth; i++)
	{
		_tree[i].resize(1 << i);
	}
}

template <typename T>
void BinaryTree<T>::SetNode(int i, int j, T value) {
	_tree[i][j] = value;
}

template <typename T>
T BinaryTree<T>::GetNode(int i, int j) {
	return _tree[i][j];
}

template <typename T>
void BinaryTree<T>::display() {
	for (const auto& vec : _tree) {
		for (const auto& value : vec)
		{
			std::cout << value << " ";
		}
		std::cout << std::endl;
	}
}

