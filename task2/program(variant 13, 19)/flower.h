//
// Описание цветка.
//

#ifndef PLANTS_FLOWER_H
#define PLANTS_FLOWER_H

#include "plant.h"

class Flower: public Plant {
public:
    virtual ~Flower() {}

    // Ввод параметров цветка из файла.
    virtual void Input(std::ifstream &ifstream);

    // Случайная генерация параметров цветка.
    virtual void RandomInput();

    // Вывод параметров цветка в указанный поток.
    virtual void Output(std::ofstream &ofstream);
private:
    static const inline char *placement_types[3] = { "potted", "garden", "wild"};

    enum flower_key {
        POTTED,
        GARDEN,
        WILD
    };

    // Тип цветка.
    flower_key placement_type;
};

#endif //PLANTS_FLOWER_H
