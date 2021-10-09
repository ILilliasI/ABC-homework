//
// Описание дерева.
//

#ifndef PLANTS_TREE_H
#define PLANTS_TREE_H

#include <cstdio>
#include <cstdlib>

// Структура дерева.
struct tree {
    long age;
};

// Ввод параметров дерева из файла.
void Input(tree &in_tree, FILE *in_file);

// Случайная генерация параметров дерева.
void RandomInput(tree &in_tree);

// Вывод параметров дерева в указанный поток.
void Output(tree &out_tree, char name[20], FILE *out_file);
#endif //PLANTS_TREE_H
