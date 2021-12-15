//
// Описание работника, осуществляющего контроль качества заточки.
//

#ifndef PLANTS_SHARPENINGWORKER_H
#define PLANTS_SHARPENINGWORKER_H

#include <iostream>
#include <mutex>
#include <chrono>

class Workshop;

class SharpeningWorker {
public:
    // Создание рабочего, осуществяющего заточку булавки.
    SharpeningWorker(Workshop*);

    // Заточка булавки.
    void sharpenPin();

private:
    // Количество заточенных булавок.
    int processed_pins;
    // Цех, в котором работает рабочий.
    Workshop* workshop;
    std::mutex sharpen_mutex;
};

#endif //PLANTS_SHARPENINGWORKER_H
