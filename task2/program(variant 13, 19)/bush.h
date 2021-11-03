//
// Описание куста.
//

#ifndef PLANTS_BUSH_H
#define PLANTS_BUSH_H

#include "plant.h"

class Bush: public Plant {
public:
    virtual ~Bush() {}

    // Ввод параметров куста из файла.
    virtual void Input(std::ifstream &ifstream);

    // Случайная генерация параметров куста.
    virtual void RandomInput();

    // Вывод параметров куста в указанный поток.
    virtual void Output(std::ofstream &ofstream);
private:
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

    // Месяц цветения куста.
    bush_key flowering_month;
};

#endif //PLANTS_BUSH_H
