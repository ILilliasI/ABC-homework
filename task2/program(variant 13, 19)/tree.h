//
// Описание дерева.
//

#ifndef PLANTS_TREE_H
#define PLANTS_TREE_H

#include "plant.h"

class Tree: public Plant {
public:
    virtual ~Tree() {}

    // Ввод параметров дерева из файла.
    virtual void Input(std::ifstream &ifstream);

    // Случайная генерация параметров дерева.
    virtual void RandomInput();

    // Вывод параметров дерева в указанный поток.
    virtual void Output(std::ofstream &ofstream);
private:
    // Возраст дерева.
    long age;
};

#endif //PLANTS_TREE_H
