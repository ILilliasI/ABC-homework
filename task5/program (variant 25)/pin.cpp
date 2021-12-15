//
// Функции обработки булавки.
//

#include "pin.h"

static std::mutex output_mutex;

// Создание булавки.
Pin::Pin(int number) {
    this->number = number;
    this->curvature_checked = false;
    this->pin_sharpened = false;
    this->is_verified = false;
}

// Проверка булавки на кривизну.
void Pin::checkCurvature() {
    this->curvature_checked = (rand() % 10 < 9);
    std::string out_string;

    if (this->curvature_checked) {
        out_string = "Worker 1 has checked pin's " + std::to_string(this->number) + " curvature. "
                                                    "The pin has passed the test.";
    } else {
        out_string = "Worker 1 has checked pin's " + std::to_string(this->number) + " curvature. "
                                                     "The pin has NOT passed the test.";
    }
    printMessage(out_string);
}

// Заточка булавки.
void Pin::sharpenPin() {
    this->pin_sharpened = (rand() % 10 < 9);
    std::string out_string = "Worker 2 has sharpened pin " + std::to_string(this->number) + ".";

    printMessage(out_string);
}

// Проверка заточки на качество.
void Pin::verifyQuality() {
    this->is_verified = this->pin_sharpened;
    std::string out_string;

    if (this->pin_sharpened) {
        out_string = "Worker 3 has checked pin's " + std::to_string(this->number) + " quality. "
                                                       "The pin has been verified.";
    } else {
        out_string = "Worker 3 has checked pin's " + std::to_string(this->number) + " quality. "
                                                      "The pin has NOT been verified.";
    }
    printMessage(out_string);
}

// Печать сообщения.
void Pin::printMessage(std::string message) {
    std::unique_lock<std::mutex> lock(output_mutex);
    std::cout << message << std::endl;
}

// Номер булавки.
int Pin::Number() {
    return number;
}

// Прошла ли булавка проверку на кривизну.
bool Pin::curvatureChecked() {
    return curvature_checked;
}

// Качественно ли заточена булавка.
bool Pin::isVerified() {
    return is_verified;
}
