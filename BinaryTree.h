// двоичное дерево

#include <istream>
#include <vector>

// элемент дерева
struct Element {
    Element(Element *parent) : parent(parent), left(nullptr), right(nullptr) {}

    int value;
    // указатель на родителя (null - начальный элемент)
    Element *parent;
    // указатель на левый поток (соответствует 0) null - пусто
    Element *left;
    // указатель на правый поток (соответствует 1)
    Element *right;
};

class BinaryTree {
public:
    BinaryTree();

    virtual ~BinaryTree();

    // вставка элемента в дерево
    void put(int value, std::vector<int> *vec);

    // удалить все листья (возвращает количество удаленных листьев)
    int deleteAllSheets();

    // operator вывода
    friend std::ostream &operator<<(std::ostream &os, const BinaryTree &tree);

    // количество четных чисел в дереве
    int countEvenNumbers();

    // проверка что в дереве только положительные числа
    bool onlyPositiveNumbers();

    // среднее арифметическое всех чисел в дереве
    double average();

    // поиск заданного элемента в дереве (nullptr - нет данного значения)
    std::vector<int>* find(int value);

    // дерево является деревом двоичного поиска
    bool binarySearchTree();

private:
    // указатель на начальный элемент
    Element *header;
};
