import sys
import plant
from typing.io import TextIO
from enum import Enum
from random import randint


class Flower(plant.Plant):
    """Функции для обработки цветка."""

    class FlowerKey(Enum):
        """Вид цветка."""
        potted = 0
        garden = 1
        wild = 2

    def __init__(self):
        """Инициализация параметров цветка."""
        super().__init__()
        self.__flower_type = 0

    def input(self, flower_type: str):
        """Считывание параметров цветка."""
        if (not flower_type.isnumeric()) or (int(flower_type) < 1) or (int(flower_type) > 3):
            print(f"Incorrect value for flower type: {flower_type}. Input an integer from 1 to 3")
            sys.exit(9)
        self.__flower_type = int(flower_type) - 1

    def random_input(self):
        """Случайная генерация параметров цветка."""
        self.__flower_type = randint(0, 2)

    def output(self, out_file: TextIO):
        """Вывод параметров цветка в указанный поток."""
        out_file.write(f"It is a flower: name = {self._name} "
                       f"type = {self.FlowerKey(self.__flower_type).name}\n")

    def __del__(self):
        """Удаление параметров цветка."""
        del self.__flower_type
