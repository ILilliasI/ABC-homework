//
// Функции для обработки цветка.
//

#include "flower.h"

// Ввод параметров цветка из файла.
void Flower::Input(std::ifstream &ifstream) {
    int input_type;

    ifstream >> input_type;
    placement_type = static_cast<flower_key>(input_type - 1);
}

// Случайная генерация параметров цветка.
void Flower::RandomInput() {
    placement_type = static_cast<flower_key>(rand() % 3);
}

// Вывод параметров цветка в указанный поток.
void Flower::Output(std::ofstream &ofstream) {
    ofstream << "It is a flower: name = " << name << ", type = " << placement_types[placement_type];
}