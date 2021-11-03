import sys
import plant
from typing.io import TextIO
from random import randint


class Tree(plant.Plant):
    """Функции для обработки дерева."""

    def __init__(self):
        """Инициализация параметров дерева."""
        super().__init__()
        self.__age = 0

    def input(self, age: str):
        """Считывание параметров дерева."""
        if (not age.isnumeric()) or (str(age) == 0):
            print(f"Incorrect value for tree age: {age}. Input an integer > 0")
            sys.exit(11)
        self.__age = int(age)

    def random_input(self):
        """Случайная генерация параметров дерева."""
        self.__age = randint(1, 15000)

    def output(self, out_file: TextIO):
        """Вывод параметров дерева в указанный поток."""
        out_file.write(f"It is a tree: name = {self._name} "
                       f"age = {self.__age}\n")

    def __del__(self):
        """Удаление параметров дерева."""
        del self.__age
