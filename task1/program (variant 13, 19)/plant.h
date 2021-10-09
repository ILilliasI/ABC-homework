//
// Описание растения.
//

#ifndef PLANTS_PLANT_H
#define PLANTS_PLANT_H

#include "tree.h"
#include "bush.h"
#include "flower.h"
#include <cstring>

// Структура, обобщающая имеющиеся виды растений.
struct plant {
    enum key {
        TREE,
        BUSH,
        FLOWER
    };
    union {
        tree un_tree;
        bush un_bush;
        flower un_flower;
    };

    key plant_type;
    char name[21];
};

// Ввод параметров растения из указанного потока.
plant *Input(FILE *in_file);

// Случайная генерация параметров растения.
plant *RandomInput();

// Вывод параметров растения в указанный поток.
void Output(plant &out_plant, FILE *out_file);

// Поиск частного от деления числам гласных букв в названии на общую длину названия.
double CalculateRatioOfVowelsToAllLetters(plant &plant);

// Генерация случайного имени.
void GenerateRandomName(char *name);

#endif //PLANTS_PLANT_H
