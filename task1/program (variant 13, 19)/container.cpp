//
// Функции обработки контейнера.
//

#include "container.h"

// Инициализация контейнера.
void Init(container &container) {
    container.current_length = 0;
}

// Очистка контейнера.
void Clear(container &container) {
    for (int i = 0; i < container.current_length; ++i) {
        delete container.plants[i];
    }
    container.current_length = 0;
}

// Ввод содержимого контейнера из указанного потока.
void Input(container &container, FILE *in_file) {
    char symb;
    while ((symb = getc(in_file)) != EOF) {
        ungetc(symb, in_file);
        container.plants[container.current_length] = Input(in_file);
        ++container.current_length;
    }
}

// Случайная генерация содержимого контейнера.
void RandomInput(container &container, int container_size) {
    while (container.current_length < container_size) {
        if ((container.plants[container.current_length] = RandomInput()) != nullptr) {
            ++container.current_length;
        }
    }
}

// Вывод содержимого контейнера в указанный поток
void Output(container &container, FILE *out_file) {
    fprintf(out_file, "Container contains %i elements.\n", container.current_length);
    for (int i = 0; i < container.current_length; ++i) {
        fprintf(out_file, "%i: ", i);
        Output(*(container.plants[i]), out_file);
    }
}

// Удаление из контейнера тех элементов, для которых значение, полученное с
// использованием функции, общей для всех альтернатив, меньше чем
// среднее арифметическое для всех элементов контейнера, полученное с
// использованием этой же функции.
void ModifyContainer(container &container) {
    double average = CalculateAverage(container);
    int i = 0;

    while (i < container.current_length) {
        if (CalculateRatioOfVowelsToAllLetters(*container.plants[i]) < average) {
            // Удаление элемента.
            for (int j = i; j < container.current_length - 1; j++) {
                container.plants[j] = container.plants[j + 1];
            }
            --container.current_length;
        } else {
            ++i;
        }
    }
}

// Вычисление реднего арифметического для всех элементов контейнера, полученное с
// использованием функции, общей для всех альтернатив.
double CalculateAverage(container &container) {
    double sum = 0.0;
    for (int i = 0; i < container.current_length; ++i) {
        sum += CalculateRatioOfVowelsToAllLetters(*(container.plants[i]));
    }

    return sum / container.current_length;
}
