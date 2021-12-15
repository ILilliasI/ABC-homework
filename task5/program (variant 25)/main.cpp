#include <iostream>
#include <thread>
#include <ctime>
#include "workshop.h"

int main(int argc, char* argv[]) {
    std::ios_base::sync_with_stdio(false);

    srand(static_cast<unsigned int>(std::time(0)));

    if (argc != 2) {
        std::cout << "Incorrect number of command arguments. Waited:\n"
                     "command pins_number(integer from from 0 to 10000)";
        return 1;
    }
    std::string string_pins_number = argv[1];
    int pins_number;

    if ((string_pins_number.length() < 1) || (string_pins_number.length() > 5)) {
        std::cout << "Incorrect value for pins number.";
        return 2;
    }
    for (int i = 0; i < string_pins_number.length(); ++i) {
        if (!isdigit(string_pins_number[i])) {
            std::cout << "Entered value is not an integer.";
            return 3;
        }
    }
    pins_number = stoi(string_pins_number);

    if ((pins_number < 0) || (pins_number > 10000)) {
        std::cout << "Incorrect value for pins number (from 0 to 10000).";
        return 4;
    }
    Workshop* workshop = new Workshop();
    workshop->startWork(pins_number);

    delete workshop;

    return 0;
}
