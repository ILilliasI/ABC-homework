//
// Описание работника, осуществляющего контроль качества заточки.
//

#ifndef PLANTS_QUALITYVERIFYWORKER_H
#define PLANTS_QUALITYVERIFYWORKER_H

#include <iostream>
#include <mutex>
#include <chrono>

class Workshop;

class QualityVerifyWorker {
public:
    // Создание рабочево, проверяющего качество заточки.
    QualityVerifyWorker(Workshop*);

    // Проверка заточки на качество.
    void verifyQuality();

private:
    // Количество проверенных булавок.
    int processed_pins;
    // Цех, в котором работает рабочий.
    Workshop* workshop;
    std::mutex verify_mutex;
};

#endif //PLANTS_QUALITYVERIFYWORKER_H
