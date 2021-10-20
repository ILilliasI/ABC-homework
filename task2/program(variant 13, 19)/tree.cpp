//
// Функции обработки дерева.
//

#include "tree.h"

// Ввод параметров дерева из файла.
void Tree::Input(std::ifstream &ifstream) {
    ifstream >> age;
}

// Случайная генерация параметров дерева.
void Tree::RandomInput() {
    age = rand() % 10000000000 + 1;
}

// Вывод параметров дерева в указанный поток.
void Tree::Output(std::ofstream &ofstream) {
    ofstream << "It is a tree: name = " << name << ", age = " << age;
}
