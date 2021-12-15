//
// Описание работы цеха.
//

#ifndef PLANTS_WORKSHOP_H
#define PLANTS_WORKSHOP_H

#define _GLIBCXX_HAS_GTHREADS 1
#include "pin.h"
#include "curvatureWorker.h"
#include "sharpeningWorker.h"
#include "qualityVerifyWorker.h"
#include <thread>
#include <shared_mutex>
#include <iostream>

class Workshop {
public:
    // Готовые к проверке кривизны булавки.
    Pin** pins_to_process;
    // Готовые к заточке булавки.
    Pin** pins_to_sharp;
    // Готовые к приверке заточки булавки.
    Pin** pins_to_verify;
    // Заточенные и успешно проверенные булавки.
    Pin** completed_pins;

    // Создание цеха.
    Workshop() {}

    // Начало работы цеха.
    void startWork(int);

    // Количество булавок.
    int pinsCount();

    // Количество булавок, готовых к заточке.
    int pinsToSharp();

    // Количество булавок, готовых к проверке качество заточки.
    int pinsToVerify();

    // Количество проверенных на кривизну булавок.
    int processedPins();

    // Добавление булавки к готовым к заточке.
    void addPinToSharp(Pin*);

    // Добавление булавки к готовым к проверке заточки.
    void addPinToVerify(Pin*);

    // Добавление булавки к заточенным и успешно проверенным.
    void addCompletedPin(Pin*);

private:
    // Количество булавок.
    int pins_count;
    // Количество булавок, готовых к заточке.
    int pins_to_sharp_count;
    // Количество булавок, готовых к проверке качество заточки.
    int pins_to_verify_count;
    // Количество заточенных булавок.
    int sharped_pins;
    // Количество проверенных на качество заточки булавок.
    int verified_pins;
    // Количество проверенных на кривизну булавок.
    int processed_pins;
    // Количество успешно проверенных на кривизну булавок.
    int processed_successfully_pins;

    // Рабочий, проверяющий булавку на кривизну.
    CurvatureWorker* curvature_worker;
    // Рабочий, осуществляющий заточку булавки.
    SharpeningWorker* sharpening_worker;
    // Рабочий, проверяющий заточку булавки на качество.
    QualityVerifyWorker* quality_verify_worker;

    std::shared_mutex pins_mutex;
    std::shared_mutex processed_pins_mutex;
    std::shared_mutex sharp_pins_mutex;
    std::shared_mutex qualify_pins_mutex;
    std::mutex pins_to_sharp_mutex;
    std::mutex pins_to_verify_mutex;

    // Окончание работы цеха.
    void endWork();

    // Синхронизированное увеличение и уменьшение количества булавок для заточки.
    void incrementPinsToSharp(int);

    // Синхронизированное увеличение и уменьшение количества булавок для проверки.
    void incrementPinsToVerify(int);
};

#endif //PLANTS_WORKSHOP_H
