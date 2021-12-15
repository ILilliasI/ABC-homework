//
// Функции работы цеха.
//

#include "workshop.h"

// Начало работы цеха.
void Workshop::startWork(int pins_count) {
    this->processed_pins = pins_count;
    this->processed_successfully_pins = 0;
    this->sharped_pins = 0;
    this->verified_pins = 0;
    this->pins_to_sharp_count = 0;
    this->pins_to_verify_count = 0;
    this->pins_count = pins_count;
    this->pins_to_process = new Pin*[pins_count];
    this->pins_to_verify = new Pin*[pins_count];
    this->pins_to_sharp = new Pin*[pins_count];
    this->completed_pins = new Pin*[pins_count];

    for (int i = 1; i <= pins_count; ++i) {
        pins_to_process[i - 1] = new Pin(i);
    }
    // Создание работников цеха.
    curvature_worker = new CurvatureWorker(this);
    sharpening_worker = new SharpeningWorker(this);
    quality_verify_worker = new QualityVerifyWorker(this);

    for (int i = 0; i < pins_count; ++i) {
        pins_to_sharp[i] = nullptr;
        pins_to_verify[i] = nullptr;
    }
    std::cout << "Work in workshop started." << std::endl;
    std::thread curvature_worker_thread(&CurvatureWorker::checkCurvature, &*curvature_worker);
    std::thread sharpening_worker_thread(&SharpeningWorker::sharpenPin, &*sharpening_worker);
    std::thread verify_worker_thread(&QualityVerifyWorker::verifyQuality, &*quality_verify_worker);

    curvature_worker_thread.join();
    sharpening_worker_thread.join();
    verify_worker_thread.join();

    endWork();
}

// Возврат количества булавок.
int Workshop::pinsCount() {
    std::shared_lock<std::shared_mutex> lock(pins_mutex);

    return pins_count;
}

// Возврат количества булавок для заточки.
int Workshop::pinsToSharp() {
    std::shared_lock<std::shared_mutex> lock(sharp_pins_mutex);

    return pins_to_sharp_count;
}

// Возврат количества булавок для проверки качества.
int Workshop::pinsToVerify() {
    std::shared_lock<std::shared_mutex> lock(qualify_pins_mutex);

    return pins_to_verify_count;
}

// Возврат количества проверенных на кривизну булавок.
int Workshop::processedPins() {
    std::shared_lock<std::shared_mutex> lock(processed_pins_mutex);

    return processed_pins;
}

// Синхронизированное увеличение и уменьшение количества булавок для заточки.
void Workshop::incrementPinsToSharp(int value) {
    std::unique_lock<std::mutex> lock(pins_to_sharp_mutex);
    pins_to_sharp_count += value;
}

// Синхронизированное увеличение и уменьшение количества булавок для проверки.
void Workshop::incrementPinsToVerify(int value) {
    std::unique_lock<std::mutex> lock(pins_to_verify_mutex);
    pins_to_verify_count += value;
}

void Workshop::addPinToSharp(Pin* checked_pin) {
    if (checked_pin->curvatureChecked()) {
        pins_to_sharp[processed_successfully_pins] = checked_pin;
        incrementPinsToSharp(1);
        ++processed_successfully_pins;
    } else {
        --processed_pins;
    }
}

void Workshop::addPinToVerify(Pin* sharped_pin) {
    pins_to_verify[sharped_pins] = sharped_pin;
    ++sharped_pins;
    incrementPinsToVerify(1);
    incrementPinsToSharp(-1);
}

void Workshop::addCompletedPin(Pin* verified_pin) {
    if (verified_pin->isVerified()) {
        completed_pins[verified_pins] = verified_pin;
        ++verified_pins;
    }
    incrementPinsToVerify(-1);
}

// Окончание работы цеха.
void Workshop::endWork() {
    std::cout << "-------------------------------\n";
    std::cout << "Tested for the quality of pins:\n";

    for (int i = 0; i < verified_pins; ++i) {
        std::cout << "Pin number " << completed_pins[i]->Number() << ".\n";
    }
    for (int i = 0; i < pins_count; ++i) {
        delete pins_to_process[i];
    }
    delete[] pins_to_process;
    delete[] pins_to_verify;
    delete[] pins_to_sharp;
    delete[] completed_pins;

    delete curvature_worker;
    delete sharpening_worker;

    std::cout << "Work in workshop has ended.\n";
}
