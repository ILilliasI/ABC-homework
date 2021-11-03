//
// Функции обработки растения.
//

#include "plant.h"
#include "bush.h"
#include "tree.h"
#include "flower.h"

// Ввод параметров растения из указанного потока.
Plant* Plant::StaticInput(std::ifstream &ifstream) {
    int plant_type;

    Plant *new_plant;
    ifstream >> plant_type;

    switch (plant_type) {
        case 1:
            new_plant = new Tree;
            break;
        case 2:
            new_plant = new Bush;
            break;
        case 3:
            new_plant = new Flower;
            break;
        default:
            return nullptr;
    }
    ifstream >> new_plant->name;
    new_plant->Input(ifstream);
    return new_plant;
}

// Случайная генерация параметров растения.
Plant *Plant::StaticRandomInput() {
    int plant_type = rand() % 3 + 1;
    Plant* new_plant;

    switch(plant_type) {
        case 1:
            new_plant = new Tree;
            break;
        case 2:
            new_plant = new Bush;
            break;
        case 3:
            new_plant = new Flower;
            break;
        default:
            return nullptr;
    }
    new_plant->GenerateRandomName();
    new_plant->RandomInput();
    return new_plant;
}

// Генерация случайного имени.
void Plant::GenerateRandomName() {
    const int name_length = rand() % 20 + 1;

    for (int i = 0; i < name_length; ++i) {
        name += static_cast<char>(rand() % 26 + 97);
    }
}

// Поиск частного от деления числам гласных букв в названии на общую длину названия.
double Plant::CalculateRatioOfVowelsToAllLetters() {
    int vowels_count = 0;
    std::string vowels = "aoiue";

    for (char &letter : name) {
        for (int vowel_index = 0; vowel_index < 5; ++vowel_index) {
            if (vowels[vowel_index] == letter) {
                ++vowels_count;
                break;
            }
        }
    }
    return static_cast<double>(vowels_count) / name.length();
}
