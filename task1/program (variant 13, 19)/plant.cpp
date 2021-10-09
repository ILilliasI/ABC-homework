//
// Функции обработки растения.
//

#include "plant.h"

// Ввод параметров растения из указанного потока.
plant* Input(FILE *in_file) {
    plant *new_plant;
    int plant_type;
    new_plant = new plant;

    fscanf(in_file, "%i", &plant_type);
    fscanf(in_file, "%s", new_plant -> name);
    switch(plant_type) {
        case(1):
            new_plant -> plant_type = plant::TREE;
            Input(new_plant -> un_tree, in_file);
            return new_plant;
        case(2):
            new_plant -> plant_type = plant::BUSH;
            Input(new_plant -> un_bush, in_file);
            return new_plant;
        case(3):
            new_plant -> plant_type = plant::FLOWER;
            Input(new_plant -> un_flower, in_file);
            return new_plant;
        default:
            return 0;
    }
}

// Случайная генерация параметров растения.
plant *RandomInput() {
    plant *new_plant = new plant;
    int plant_type_number = rand() % 3 + 1;

     GenerateRandomName(new_plant -> name);
    switch(plant_type_number) {
        case(1):
            new_plant -> plant_type = plant::TREE;
            RandomInput(new_plant -> un_tree);

            break;
        case(2):
            new_plant -> plant_type = plant::BUSH;
            RandomInput(new_plant->un_bush);

            break;
        case(3):
            new_plant->plant_type = plant::FLOWER;
            RandomInput(new_plant->un_flower);

            break;
        default:
            return 0;
    }

    return new_plant;
}

// Вывод параметров растения в указанный поток.
void Output(plant &out_plant, FILE *out_file) {
    switch(out_plant.plant_type) {
        case (plant::TREE):
            Output(out_plant.un_tree, out_plant.name, out_file);
            break;
        case (plant::FLOWER):
            Output(out_plant.un_flower, out_plant.name, out_file);
            break;
        case (plant::BUSH):
            Output(out_plant.un_bush, out_plant.name, out_file);
            break;
        default:
            fprintf(out_file, "Incorrect plant.\n");
    }
}

// Генерация случайного имени.
void GenerateRandomName(char *name) {
    const int name_length = rand() % 20 + 1;

    for (int i = 0; i < name_length; ++i) {
        name[i] = static_cast<char>(rand() % 26 + 97);
    }
    name[name_length] = '\0';
}

// Поиск частного от деления числам гласных букв в названии на общую длину названия.
double CalculateRatioOfVowelsToAllLetters(plant &plant) {
    int count = std::strlen(plant.name);
    int vowels_count = 0;
    char vowels[] = "aoiue";

    for (int i = 0; i < std::strlen(plant.name); ++i) {
        for (int vowel_index = 0; vowel_index < 5; ++vowel_index) {
            if (vowels[vowel_index] == plant.name[i]) {
                ++vowels_count;
                break;
            }
        }
    }
    return static_cast<double>(vowels_count) / count;
}
