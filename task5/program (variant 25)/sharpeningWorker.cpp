//
// Функции работника, осуществляющего заточку булавки.
//

#include "sharpeningWorker.h"
#include "workshop.h"

// Создание рабочего, осуществяющего заточку булавки.
SharpeningWorker::SharpeningWorker(Workshop* workshop) {
    this->processed_pins = 0;
    this->workshop = workshop;
}

// Заточка булавки.
void SharpeningWorker::sharpenPin() {
    while (processed_pins < this->workshop->processedPins()) {
        while ((this->workshop->pinsToSharp() <= 0) &&
        (processed_pins < this->workshop->processedPins())) {
            std::this_thread::sleep_for(std::chrono::nanoseconds(50));
        }
        std::unique_lock<std::mutex> lock(sharpen_mutex);
        Pin *pin_to_sharpen = this->workshop->pins_to_sharp[processed_pins];

        if (pin_to_sharpen != nullptr) {
            pin_to_sharpen->sharpenPin();
            this->workshop->addPinToVerify(pin_to_sharpen);
        }
        ++processed_pins;
        lock.unlock();
    }
}
