//
// Описание работника, проверяющего булавку на предмет кривизны.
//

#ifndef PLANTS_CURVATUREWORKER_H
#define PLANTS_CURVATUREWORKER_H

#include <iostream>
#include <mutex>

class Workshop;

class CurvatureWorker {
public:
    // Создание работника, проверяющего булавку на предмет кривизны.
    CurvatureWorker(Workshop*);

    // Проверка булавки на кривизну.
    void checkCurvature();

private:
    // Количество проверенных булавок.
    int processed_pins;
    // Цех, в котором работает работник.
    Workshop* workshop;

    std::mutex curvature_mutex;
};

#endif //PLANTS_CURVATUREWORKER_H
