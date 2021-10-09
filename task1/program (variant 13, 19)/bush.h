//
// Описание куста.
//

#ifndef PLANTS_BUSH_H
#define PLANTS_BUSH_H

#include <cstdio>
#include <cstdlib>

// Структура куста.
struct bush {
    enum bush_key {
        JANUARY,
        FEBRUARY,
        MARCH,
        APRIL,
        MAY,
        JUNE,
        JULY,
        AUGUST,
        SEPTEMBER,
        OCTOBER,
        NOVEMBER,
        DECEMBER
    };

    bush_key flowering_month;
};

// Ввод параметров куста из файла.
void Input(bush &in_bush, FILE *in_file);

// Случайная генерация параметров куста.
void RandomInput(bush &in_bush);

// Вывод параметров куста в указанный поток.
void Output(bush &out_bush, char name[20], FILE *out_file);

#endif //PLANTS_BUSH_H
