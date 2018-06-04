#include <map>
#include <iostream>
#include <iterator>
#include <vector>

#include "BinaryTree.h"

void outFind(int value, BinaryTree *binaryTree) {
	std::vector<int> *v = binaryTree->find(value);
	std::cout << "find(" << value << ") = ";
	if (v == nullptr) {
		std::cout << "not found";
	}
	else {
		std::copy(v->begin(), v->end(), std::ostream_iterator<int>(std::cout, " "));
	}
	std::cout << "\n";
}

int main() {
	std::cout << "\nBinaryTree\n";

	BinaryTree tree;
	tree.put(50, new std::vector<int>{});

	tree.put(20, new std::vector<int>{ 0 });
	tree.put(10, new std::vector<int>{ 0, 0 });
	tree.put(33, new std::vector<int>{ 0, 1 });

	tree.put(70, new std::vector<int>{ 1 });
	tree.put(60, new std::vector<int>{ 1, 0 });
	tree.put(100, new std::vector<int>{ 1, 1 });

	//    try {
	//        // проверка ошибочного узла дерева
	//        tree.put(200, new std::vector<int>{1, 1, 1, 1});
	//        throw "error";
	//    } catch (const char *message) {}

	std::cout << "\n" << tree << "\n";

	std::cout << "countEvenNumbers = " << tree.countEvenNumbers() << "\n";
	std::cout << "onlyPositiveNumbers = " << tree.onlyPositiveNumbers() << "\n";
	std::cout << "average = " << tree.average() << "\n";
	outFind(15, &tree);
	outFind(60, &tree);
	std::cout << "binarySearchTree = " << tree.binarySearchTree() << "\n";

	std::cin.get();
	return 0;
}
