//
// Функции обработки куста.
//

#include "bush.h"

// Ввод параметров куста из файла.
void Input(bush &in_bush, FILE *in_file) {
    int flowering_month;

    fscanf(in_file, "%i", &flowering_month);
    in_bush.flowering_month = static_cast<bush::bush_key>(flowering_month - 1);
}

// Случайная генерация параметров куста.
void RandomInput(bush &in_bush) {
    in_bush.flowering_month = static_cast<bush::bush_key>(rand() % 12);
}

// Вывод параметров куста в указанный поток.
void Output(bush &out_bush, char name[20], FILE *out_file) {
    fprintf(out_file, "It is a bush: name = %s, flowering month = %i\n",
            name, out_bush.flowering_month);
}