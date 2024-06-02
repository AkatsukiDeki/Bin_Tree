#pragma once

#include <vector>
#include <iostream>
#include <stdexcept> 
#include <random>
#include <exception>
#include <ctime>

using namespace std;	

class Node {
public:
	int value;
	Node* left;
	Node* right;

	Node(int _value) : value(_value), left(nullptr), right(nullptr) {};
};


class MyTree {
private:
	Node* root;

	Node* copy(Node* ptr) {
		if (!ptr) {
			return nullptr;
		}
		auto tmp = new Node(ptr->value);
		tmp->left = copy(ptr->left);
		tmp->right = copy(ptr->right);
		return tmp;
	}

	void delete_tree(Node* ptr) {
		if (!ptr) {
			return;
		}
		delete_tree(ptr->left);
		delete_tree(ptr->right);
		delete ptr;
	}

	Node* min(Node* ptr) {
		while (ptr->left) {
			ptr = ptr->left;
		}
		return ptr;
	}


	Node* max(Node* ptr) {
		while (ptr->right) {
			ptr = ptr->right;
		}
		return ptr;
	}

	Node* erase(Node* ptr, const int value) {
		if (!ptr) {
			return nullptr;
		}
		if (value < ptr->value) {
			ptr->left = erase(ptr->left, value);
		}
		else if (value > ptr->value) {
			ptr->right = erase(ptr->right, value);
		}
		else {
			if (ptr->left == nullptr || ptr->right == nullptr) {
				Node* tmp;
				if (ptr->left != nullptr) {
					tmp = ptr->left;
				}
				else {
					tmp = ptr->right;
				}
				if (tmp == nullptr) {
					tmp = ptr;
					ptr = nullptr;
				}
				else {
					*ptr = *tmp;
				}
				delete tmp;
			}
			else {
				auto tmp = min(ptr->right);
				ptr->value = tmp->value;
				ptr->right = erase(ptr->right, tmp->value);
			}

		}
		return ptr;
	}


	void insert(int key) {
		root = insertRecursive(root, key);
	}

	

	Node* insertRecursive(Node* node, int key) {
		if (node == nullptr) {
			return new Node(key);
		}

		if (key < node->value) {
			node->left = insertRecursive(node->left, key);
		}
		else if (key > node->value) {
			node->right = insertRecursive(node->right, key);
		}

		return node;
	}

	void inorderTraversalRecursive(Node* node, std::function<void(int)> callback) {
		if (node) {
			inorderTraversalRecursive(node->left, callback);
			callback(node->value);
			inorderTraversalRecursive(node->right, callback);
		}
	}


	void print(Node* ptr) {
		if (ptr) {
			cout << ptr->value << " ";
			this->print(ptr->left);
			this->print(ptr->right);
		}
		else {
			cout << "- ";
		}
	}

	bool contains(Node* ptr, const int value) {
		if (ptr == nullptr) {
			return false;
		}
		if (ptr->value != value) {
			return true;
		}
		if (value > ptr->value) {
			return contains(ptr->right, value);
		}
		else {
			return contains(ptr->right, value);
		}
	}



public:

	Node* getRoot() {
		return root;
	}
	MyTree() : root(nullptr) {};
	MyTree(MyTree& other) {
		root = copy(other.root);
	}
	~MyTree() {
		delete_tree(root);
		root = nullptr;

	}

	MyTree& operator=(const MyTree& other) {
		if (this == &other) {
			return *this;
		}

		delete_tree(root);
		root = copy(other.root);
		return *this;
    }
    
    int min() {
        return min(root)->value;
    }
    
    int max() {
        return max(root)->value;
    }
    
    void clear() {
        delete_tree(root);
        root = nullptr;
    }

    bool insertRecursive(const int value) {
        if (contains(value)) {
            return false;
        }
        else {
            root = insertRecursive(root, value);
            return true;
        }
    }

	void inorderTraversal(std::function<void(int)> callback) {
		inorderTraversalRecursive(root, callback);
	}

    void print() {
        print(root);
        cout << endl;
    }

    bool contains(const int value) {
        if (!contains(root, value)) {
            return false;
        }
        return true;
    }

    bool erase(const int value) {
        if (!contains(value)) {
            return false;
        }
        else {
            root = erase(root, value);
            return true;
        }
    }
};

size_t lcg() {
	static size_t x = 0;
	x = (1021 * x + 24631) % 116640;
	return x;
}
