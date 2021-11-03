#include "container.h"
#include <ctime>

void errMessage1() {
    printf("Incorrect command line!\n"
           "  Waited:\n"
           "     command -f infile outfile01 outfile02\n"
           "  Or:\n"
           "     command -n number outfile01 outfile02\n");
}

void errMessage2() {
    printf("Incorrect qualifier value!\n"
           "  Waited:\n"
           "     command -f infile outfile01 outfile02\n"
           "  Or:\n"
           "     command -n number outfile01 outfile02\n");
}

int main(int argc, char* argv[]) {
    if (argc != 5) {
        errMessage1();
        return 1;
    }
    printf("Start\n");

    srand(static_cast<unsigned int>(std::time(0)));

    Container *container = new Container(10000);
    std::string file_mode = argv[1];

    if (file_mode == "-f") {
        std::ifstream ifstream1(argv[2]);
        if (ifstream1.fail()) {
            std::cout << "Can't find this file: " << argv[2] << "\n";
            return 4;
        }

        container->Input(ifstream1);
    }
    else if (file_mode == "-n") {
        int size = atoi(argv[2]);
        if((size < 1) || (size > 10000)) {
            std::cout << "Incorrect number of figures = "
                      << size
                      << ". Set 0 < number <= 10000\n";
            return 3;
        }
        container->RandomInput(size);
    }
    else {
        errMessage2();
        return 2;
    }
    std::ofstream ofstream1(argv[3]);
    ofstream1 << "Filled container:\n";
    container->Output(ofstream1);

    std::ofstream ofstream2(argv[4]);
    ofstream2 << "Modified container:\n";
    container->ModifyContainer();
    container->Output(ofstream2);
    std::cout << "Stop"<< std::endl;
    return 0;
}
