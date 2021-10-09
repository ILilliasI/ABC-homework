//
// Функции обработки цветка.
//

#include "flower.h"

// Ввод параметров цветка из файла.
void Input(flower &flower, FILE *in_file) {
    int placement_type;

    fscanf(in_file, "%i", &placement_type);
    flower.placement_type = static_cast<flower::flower_key>(placement_type - 1);
}

// Случайная генерация параметров цветка.
void RandomInput(flower &flower) {
    flower.placement_type = static_cast<flower::flower_key>(rand() % 3);
}

// Вывод параметров цветка в указанный поток.
void Output(flower &out_flower, char name[20], FILE *out_file) {
    fprintf(out_file, "It is a flower: name = %s, type = %s\n",
            name, flower::TypeToString(out_flower.placement_type));
}