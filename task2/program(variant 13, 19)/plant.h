//
// Описание растения.
//

#ifndef PLANTS_PLANT_H
#define PLANTS_PLANT_H

#include <string>
#include <iostream>
#include <fstream>

class Plant {
protected:
    std::string name;
public:
    virtual ~Plant() {}

    // Ввод параметров растения из указанного потока.
    static Plant *StaticInput(std::ifstream &ifstream);

    // Ввод обобщенной фигуры
    virtual void Input(std::ifstream &ifstream) = 0;

    // Случайный ввод обобщенной фигуры
    static Plant *StaticRandomInput();

    // Виртуальный метод ввода случайной фигуры
    virtual void RandomInput() = 0;

    // Вывод параметров растения в указанный поток.
    virtual void Output(std::ofstream &ofstream) = 0;

    // Поиск частного от деления числам гласных букв в названии на общую длину названия.
    double CalculateRatioOfVowelsToAllLetters();

    // Генерация случайного имени.
    void GenerateRandomName();
};

#endif //PLANTS_PLANT_H
