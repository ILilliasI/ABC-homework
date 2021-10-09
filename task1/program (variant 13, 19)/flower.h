//
// Описание цветка.
//

#ifndef PLANTS_FLOWER_H
#define PLANTS_FLOWER_H

#include <cstdio>
#include <cstdlib>

// Структура цветка.
struct flower {
    enum flower_key {
        POTTED,
        GARDEN,
        WILD
    };

    flower_key placement_type;

    static const char *TypeToString(enum flower_key placement_type)
    {
        static const char *placement_types[] = { "potted", "garden", "wild"};

        return placement_types[placement_type];
    }
};

// Ввод параметров цветка из файла.
void Input(flower &flower, FILE *in_file);

// Случайная генерация параметров цветка.
void RandomInput(flower &flower);

// Вывод параметров цветка в указанный поток.
void Output(flower &out_flower, char name[20], FILE *out_file);

#endif //PLANTS_FLOWER_H
