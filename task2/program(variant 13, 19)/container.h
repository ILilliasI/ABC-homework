//
// Описание контейнера.
//

#ifndef PLANTS_CONTAINER_H
#define PLANTS_CONTAINER_H

#include "plant.h"

class Container {
public:
   // Конструктор контейнера.
    Container(int container_size) {
        size = container_size;
        current_length = 0;
        storage = new Plant*[container_size];
    }

    ~Container();

    // Ввод содержимого контейнера из указанного потока.
    void Input(std::ifstream &ifstream);

    // Случайная генерация контейнера.
    void RandomInput(int size);

    // Вывод содержимого контейнера в указанный поток.
    void Output(std::ofstream &ofstream);

    // Удаление из контейнера тех элементов, для которых значение, полученное с
    // использованием функции, общей для всех альтернатив, меньше чем
    // среднее арифметическое для всех элементов контейнера, полученное с
    // использованием этой же функции.
    void ModifyContainer();

    // Вычисление среднего арифметического для всех элементов контейнера, полученное с
    // использованием функции, общей для всех альтернатив.
    double CalculateAverage();

private:
    void Clear();
    Plant** storage;
    int size;
    int current_length;
};

#endif //PLANTS_CONTAINER_H
