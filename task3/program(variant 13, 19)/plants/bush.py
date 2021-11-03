import sys
import plant
from typing.io import TextIO
from enum import Enum
from random import randint


class Bush(plant.Plant):
    """Функции для обработки куста."""

    class BushKey(Enum):
        """Месяц цветения куста."""
        january = 1
        february = 2
        march = 3
        april = 4
        may = 5
        june = 6
        july = 7
        august = 8
        september = 9
        october = 10
        november = 11
        december = 12

    def __init__(self):
        """Инициализация параметров куста."""
        super().__init__()
        self.__flowering_month = 0

    def input(self, flowering_month: str):
        """Считывание параметров куста."""
        if (not flowering_month.isnumeric()) or \
                (int(flowering_month) < 1) or \
                (int(flowering_month) > 12):
            print(f"Incorrect value for bush flowering month: {flowering_month}. "
                  f"Input an integer from 1 to 12")
            sys.exit(10)
        self.__flowering_month = int(flowering_month)

    def random_input(self):
        """Случайная генерация параметров куста."""
        self.__flowering_month = randint(1, 12)

    def output(self, out_file: TextIO):
        """Вывод параметров куста в указанный поток."""
        out_file.write(f"It is a bush: name = {self._name} "
                       f"flowering month = {self.BushKey(self.__flowering_month).name}\n")

    def __del__(self):
        """Удаление параметров куста."""
        del self.__flowering_month
