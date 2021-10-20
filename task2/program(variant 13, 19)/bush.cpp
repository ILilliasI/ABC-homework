//
// Функции обработки куста.
//

#include "bush.h"

// Ввод параметров куста из файла.
void Bush::Input(std::ifstream &ifstream) {
    int input_month;

    ifstream >> input_month;
    flowering_month = static_cast<bush_key>(input_month - 1);
}

// Случайная генерация параметров куста.
void Bush::RandomInput() {
    flowering_month = static_cast<bush_key>(rand() % 12);
}

// Вывод параметров куста в указанный поток.
void Bush::Output(std::ofstream &ofstream) {
    ofstream << "It is a bush: name = " << name << ", flowering month = " <<
                static_cast<int>(flowering_month) + 1;
}
