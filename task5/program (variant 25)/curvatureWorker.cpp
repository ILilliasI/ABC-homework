//
// Функции работника, проверяющего булавку на предмет кривизны.
//

#include "curvatureWorker.h"
#include "workshop.h"

class Workshop;

// Создание работника, проверяющего булавку на предмет кривизны.
CurvatureWorker::CurvatureWorker(Workshop* workshop) {
    this->processed_pins = 0;
    this->workshop = workshop;
}

// Проверка булавки на кривизну.
void CurvatureWorker::checkCurvature() {
    while (processed_pins < this->workshop->pinsCount()) {
        std::unique_lock<std::mutex> lock(curvature_mutex);
        Pin *pin_to_process = this->workshop->pins_to_process[processed_pins];

        pin_to_process->checkCurvature();
        this->workshop->addPinToSharp(pin_to_process);
        ++processed_pins;
        lock.unlock();
    }
}
