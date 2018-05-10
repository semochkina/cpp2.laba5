#include "BinaryTree.h"

BinaryTree::BinaryTree() {
    header = nullptr;
}

BinaryTree::~BinaryTree() {
    while (deleteAllSheets() > 0) {
        //
    }
}

// вставка элемента в дерево
Element *newElement(Element *element, std::vector<int> *vec, long numberInVector) {
    if (vec->size() == numberInVector + 1) {
        // нужный нам элемент на следующем уровне
        if (vec->at(numberInVector) == 0) {
            // указатель на левый поток
            if (element->left == nullptr) {
                // лист дерева
                element->left = new Element(element);
            }
            return element->left;
        } else {
            // указатель на правый поток
            if (element->right == nullptr) {
                // лист дерева
                element->right = new Element(element);
            }
            return element->right;
        }
    }
    Element *element2 = (vec->at(numberInVector) == 0) ? element->left : element->right;
    if (element2 == nullptr) {
        const char *string = "put: not element";
        throw string;
    }
    return newElement(element2, vec, numberInVector + 1);
}

// вставка элемента в дерево
void BinaryTree::put(int value, std::vector<int> *vec) {
    if (vec->empty()) {
        // начальный элемент
        if (header == nullptr) {
            header = new Element(nullptr);
        }
        header->value = value;
    } else {
        if (header == nullptr) {
            throw "put: not header";
        }
        Element *pElement = newElement(header, vec, 0);
        pElement->value = value;
    }
}

// удалить листья данного поддерева (не должен быть листом) 
int deleteSheets(Element *element) {
    int deleteCount = 0;
	// для левого
    Element *elementLeft = element->left;
    if (elementLeft != nullptr) {
        if (elementLeft->left == nullptr && elementLeft->right == nullptr) {
            // удаляем лист
            delete elementLeft;
            element->left = nullptr;
            deleteCount++;
        } else {
            deleteCount += deleteSheets(elementLeft);
        }
    }
	// для правого
    Element *elementRight = element->right;
    if (elementRight != nullptr) {
        if (elementRight->left == nullptr && elementRight->right == nullptr) {
            // удаляем лист
            delete elementRight;
            element->right = nullptr;
            deleteCount++;
        } else {
            deleteCount += deleteSheets(elementRight);
        }
    }
    return deleteCount;
}

// удалить все листья (возвращает количество удаленных листьев)
int BinaryTree::deleteAllSheets() {
    int deleteCount = 0;
    if (header != nullptr) {
        if (header->left == nullptr && header->right == nullptr) {
            // удаляем начальный элемент
            delete header;
            header = nullptr;
            deleteCount = 1;
        } else {
            deleteCount = deleteSheets(header);
        }
    }
    return deleteCount;
}

void print(std::ostream &os, Element *element, int level) {
    if (element != nullptr) {
        for (int i = 0; i < level; i++) os << "    ";
        os << element->value << std::endl;
        print(os, element->left, level + 1);
        print(os, element->right, level + 1);
    }
}

std::ostream &operator<<(std::ostream &os, const BinaryTree &tree) {
    print(os, tree.header, 0);
    return os;
}

// количество четных чисел поддерева
int countEven(Element *element) {
    return (element == nullptr)
           ? 0
           : (element->value % 2 ? 0 : 1)
             + countEven(element->left)
             + countEven(element->right);
}
// количество четных чисел в дереве
int BinaryTree::countEvenNumbers() {
    int count = 0;
    if (header != nullptr) {
        if (header->left == nullptr && header->right == nullptr) {
            count = (header->value % 2 ? 0 : 1);
        } else {
            count = countEven(header);
        }
    }
    return count;
}

// проверка что в поддереве только положительные числа
bool onlyPositive(Element *element) {
    if (element == nullptr) return true;
    if (element->value < 0) return false;
    return onlyPositive(element->left) && onlyPositive(element->right);
}
// проверка что в дереве только положительные числа
bool BinaryTree::onlyPositiveNumbers() {
    return onlyPositive(header);
}

// структура для подсчета среднего арифметического
struct ForAverage {
    ForAverage() : count(0), sum(0) {}
    int count;
    long sum;
};

// среднее арифметическое всех чисел в поддереве
void averageCalk(ForAverage *forAverage, Element *element) {
    if (element != nullptr) {
        forAverage->count++;
        forAverage->sum += element->value;
        averageCalk(forAverage, element->left);
        averageCalk(forAverage, element->right);
    }
}
// среднее арифметическое всех чисел в дереве
double BinaryTree::average() {
    if (header == nullptr) return 0;
    ForAverage *forAverage = new ForAverage();
    averageCalk(forAverage, header);
    return forAverage->sum * 1.0 / forAverage->count;
}

// поиск заданного элемента в поддереве
std::vector<int> *findValue(int value, std::vector<int> *vector, Element *element) {
    if (element == nullptr) return nullptr;
    if (element->value == value) return vector;
    
    // проверяем левый поток
    vector->push_back(0);    
    std::vector<int> *leftVector = findValue(value, vector, element->left);
    if (leftVector != nullptr) return leftVector;
    vector->pop_back();

    // проверяем правый поток
    vector->push_back(1);
    std::vector<int> *rightVector = findValue(value, vector, element->right);
    if (rightVector != nullptr) return rightVector;
    vector->pop_back();

    return nullptr;
}

// поиск заданного элемента в дереве
std::vector<int> *BinaryTree::find(int value) {
    std::vector<int> *vector = new std::vector<int>;
    return findValue(value, vector, header);
}

// проверка элемента что его связь с предками удовлетворяет условию двоичного поиска
bool checkElementBinarySearchTree(Element *element) {
    if (element == nullptr) return true;
    Element *parent = element->parent;
    if (parent == nullptr) {
        // это начальный элемент 
        return true;
    }
    if (element == parent->left) {
        // левый поток
        if (parent->value < element->value) return false;
    } else {
        // правый поток
        if (parent->value > element->value) return false;
    }
    return checkElementBinarySearchTree(parent);
}

// проверка что в поддереве является деревом двоичного поиска
bool isBinarySearchTree(Element *element) {
    if (element == nullptr) return true;
    if (!checkElementBinarySearchTree(element)) return false;
    return isBinarySearchTree(element->left) && isBinarySearchTree(element->right);
}

// дерево является деревом двоичного поиска
bool BinaryTree::binarySearchTree() {
    return isBinarySearchTree(header);
}
