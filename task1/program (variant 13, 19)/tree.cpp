//
// Функции обработки дерева.
//

#include "tree.h"

// Ввод параметров дерева из файла.
void Input(tree &in_tree, FILE *in_file) {
    fscanf(in_file, "%ld", &in_tree.age);
}

// Случайная генерация параметров дерева.
void RandomInput(tree &in_tree) {
    in_tree.age = rand() % 10000000000 + 1;
}

// Вывод параметров дерева в указанный поток.
void Output(tree &out_tree, char name[20], FILE *out_file) {
    fprintf(out_file, "%s%s%s%ld\n",
            "It is a tree: name = ", name, ", age = ", out_tree.age);
}
