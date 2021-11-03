import sys
import container


def err_message1():
    print("Incorrect command line!\n"
          "  Waited:\n"
          "     command -f infile outfile01 outfile02\n"
          "  Or:\n"
          "     command -n number outfile01 outfile02\n")


def err_message2():
    print("Incorrect qualifier value!\n"
          "  Waited:\n"
          "     command -f infile outfile01 outfile02\n"
          "  Or:\n"
          "     command -n number outfile01 outfile02\n")


if __name__ == '__main__':
    if len(sys.argv) != 5:
        err_message1()
        sys.exit(1)

    container = container.Container(10000)

    if sys.argv[1] == "-f":
        try:
            with open(sys.argv[2], 'r', encoding="utf-8") as input_file:
                container.input(input_file)
        except IOError:
            print(f"Can not open file {sys.argv[2]}")
            sys.exit(2)

    elif sys.argv[1] == "-n":
        if not sys.argv[2].isnumeric():
            print(f"Incorrect size {sys.argv[2]}")
            sys.exit(14)
        size = int(sys.argv[2])
        if (size < 1) or (size > 10000):
            print(f"Incorrect number of plants = {str(size)}. Set 0 < number <= 10000\n")
            sys.exit(3)
        container.random_input(size)
    else:
        err_message2()
        sys.exit(4)

    try:
        with open(sys.argv[3], 'w', encoding="utf-8") as output_file1:
            output_file1.write("Filled container:\n")
            container.output(output_file1)
    except IOError:
        print(f"Can not write in file {sys.argv[3]}")
        sys.exit(5)

    try:
        with open(sys.argv[4], 'w', encoding="utf-8") as output_file2:
            output_file2.write("Modified container:\n")
            container.modify()
            container.output(output_file2)
    except IOError:
        print(f"Can not write in file {sys.argv[4]}")
        sys.exit(6)
