//
// Функции для обработки контейнера.
//

#include "container.h"

// Деструктор контейнера.
Container::~Container() {
    Clear();
    delete[] storage;
}

// Очистка контейнера от элементов.
void Container::Clear() {
    for (int i = 0; i < current_length; i++) {
        delete storage[i];
    }
    current_length = 0;
}

// Ввод содержимого контейнера из указанного потока.
void Container::Input(std::ifstream &ifstream) {
    while (!ifstream.eof()) {
        if ((storage[current_length] = Plant::StaticInput(ifstream)) != nullptr) {
            ++current_length;
        }
    }
}

// Случайная генерация контейнера.
void Container::RandomInput(int elements_number) {
    while (current_length < elements_number) {
        if ((storage[current_length] = Plant::StaticRandomInput()) != nullptr) {
            current_length++;
        }
    }
}

// Вывод содержимого контейнера в указанный поток.
void Container::Output(std::ofstream &ofstream) {
    ofstream << "Container contains " << current_length << " elements.\n";
    for (int i = 0; i < current_length; ++i) {
        ofstream << i << ": ";
        storage[i]->Output(ofstream);
        ofstream << "\n";
    }
}

// Удаление из контейнера тех элементов, для которых значение, полученное с
// использованием функции, общей для всех альтернатив, меньше чем
// среднее арифметическое для всех элементов контейнера, полученное с
// использованием этой же функции.
void Container::ModifyContainer() {
    double average = CalculateAverage();
    int i = 0;

    while (i < current_length) {
        if (storage[i]->CalculateRatioOfVowelsToAllLetters() < average) {
            // Удаление элемента.
            for (int j = i; j < current_length - 1; j++) {
                storage[j] = storage[j + 1];
            }
            --current_length;
        } else {
            ++i;
        }
    }
}

// Вычисление среднего арифметического для всех элементов контейнера, полученное с
// использованием функции, общей для всех альтернатив.
double Container::CalculateAverage() {
    double sum = 0.0;
    for (int i = 0; i < current_length; ++i) {
        sum += storage[i]->CalculateRatioOfVowelsToAllLetters();
    }

    return sum / current_length;
}
