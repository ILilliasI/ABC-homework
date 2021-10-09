//
// Описание контейнера.
//

#ifndef PLANTS_CONTAINER_H
#define PLANTS_CONTAINER_H

#include "plant.h"

// Структура контейнера.
struct container {
    static const int max_length = 10000;
    int current_length;
    plant *plants[max_length];
};

// Инициализация контейнера
void Init(container &container);

// Очистка контейнера от элементов (освобождение памяти)
void Clear(container &container);

// Ввод содержимого контейнера из указанного потока.
void Input(container &container, FILE *in_file);

// Случайная генерация контейнера.
void RandomInput(container &container, int container_size);

// Вывод содержимого контейнера в указанный поток.
void Output(container &container, FILE *out_file);

// Удаление из контейнера тех элементов, для которых значение, полученное с
// использованием функции, общей для всех альтернатив, меньше чем
// среднее арифметическое для всех элементов контейнера, полученное с
// использованием этой же функции.
void ModifyContainer(container &container);

// Вычисление реднего арифметического для всех элементов контейнера, полученное с
// использованием функции, общей для всех альтернатив.
double CalculateAverage(container &container);

#endif //PLANTS_CONTAINER_H
