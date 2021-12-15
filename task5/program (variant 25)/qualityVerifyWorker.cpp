//
// Функции работника, осуществляющего контроль качества заточки.
//
#include "qualityVerifyWorker.h"
#include "workshop.h"

// Создание рабочево, проверяющего качество заточки.
QualityVerifyWorker::QualityVerifyWorker(Workshop* workshop) {
    this->processed_pins = 0;
    this->workshop = workshop;
}

// Проверка заточки на качество.
void QualityVerifyWorker::verifyQuality() {
    while (processed_pins < this->workshop->processedPins()) {
        while ((this->workshop->pinsToVerify() <= 0) &&
               (processed_pins < this->workshop->processedPins())) {
            std::this_thread::sleep_for(std::chrono::nanoseconds(50));
        }
        std::unique_lock<std::mutex> lock(verify_mutex);
        Pin *pin_to_verify = this->workshop->pins_to_verify[processed_pins];

        if (pin_to_verify != nullptr) {
            pin_to_verify->verifyQuality();
            this->workshop->addCompletedPin(pin_to_verify);
        }
        ++processed_pins;
        lock.unlock();
    }
}
