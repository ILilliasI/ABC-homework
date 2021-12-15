//
// Описание булавки.
//

#ifndef PLANTS_PIN_H
#define PLANTS_PIN_H

#include <iostream>
#include <random>
#include <string>
#include <mutex>

class Pin {
public:
    // Создание булавки.
    Pin(int);

    // Проверка булавки на кривизну.
    void checkCurvature();

    // Заточка булавки.
    void sharpenPin();

    // Проверка заточки на качество.
    void verifyQuality();

    // Номер булавки.
    int Number();

    // Прошла ли булавка проверку на кривизну.
    bool curvatureChecked();

    // Качественно ли заточена булавка.
    bool isVerified();

private:
    // Номер булавки.
    int number;
    // Прошла ли булавка проверку на кривизну.
    bool curvature_checked;
    // Заточена ли булавка.
    bool pin_sharpened;
    // Качественно ли заточена булавка.
    bool is_verified;

    // Печать сообщения.
    static void printMessage(std::string);
};

#endif //PLANTS_PIN_H
