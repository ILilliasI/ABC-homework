#include <ctime>
#include "container.h"

void errMessage1() {
    printf("incorrect command line!\n"
            "  Waited:\n"
            "     command -f infile outfile01 outfile02\n"
            "  Or:\n"
            "     command -n number outfile01 outfile02\n");
}

void errMessage2() {
    printf("incorrect qualifier value!\n"
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
    clock_t start = clock();
    printf("Start\n");
    srand(static_cast<unsigned int>(time(0)));

    container container;

    Init(container);

    if (!strcmp(argv[1], "-f")) {
        FILE *in_file = fopen(argv[2], "r");

        if (in_file == NULL) {
            printf("Can't find this file.\n");
            return 4;
        }
        Input(container, in_file);
        fclose(in_file);
    }
    else if (!strcmp(argv[1], "-n")) {
        int size = atoi(argv[2]);
        if ((size < 1) || (size > 10000)) {
            printf("Incorrect number of figures =  %d. Set 0 < number <= 10000.\n", size);
            return 3;
        }
        RandomInput(container, size);
    }
    else {
        errMessage2();
        return 2;
    }

    // Вывод содержимого контейнера в файл
    FILE *out_file1 = fopen(argv[3], "w");
    fprintf(out_file1, "Filled container:\n");
    Output(container, out_file1);
    fclose(out_file1);

    // Обработка контейнера.
    FILE *out_file2 = fopen(argv[4], "w");
    ModifyContainer(container);
    fprintf(out_file2, "Modified container:\n");
    Output(container, out_file2);
    fclose(out_file2);

    Clear(container);
    printf("Stop");

    return 0;
}
