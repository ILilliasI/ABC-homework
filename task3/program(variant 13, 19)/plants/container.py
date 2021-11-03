import sys
import plant
import tree
import bush
import flower
from random import randint
from decimal import Decimal
from typing.io import TextIO


class Container:
    """Функции для обработки контейнера."""

    def __init__(self, size: int):
        """Инициализация контейнера."""
        self.__storage = [None] * size
        self.__current_size = 0

    def input(self, in_file: TextIO):
        """Ввод содержимого контейнера из указанного потока."""
        plants_info = in_file.read().splitlines()

        for i in range(0, len(plants_info), 2):
            if len(plants_info[i]) != 1:
                print("Incorrect plant type length != 1.")
                sys.exit(7)
            if len(plants_info[i + 1].split()) != 2:
                print("Incorrect plant parameters length != 2.")
                sys.exit(8)
            self.__storage[self.__current_size] = \
                Container.static_input(plants_info[i], plants_info[i + 1].split())
            self.__current_size += 1

    def random_input(self, size: int):
        """Случайная генерация контейнера."""
        for i in range(size):
            self.__storage[i] = Container.static_random_input()
            self.__current_size += 1

    def output(self, out_file: TextIO):
        """Вывод содержимого контейнера в указанный поток."""
        out_file.write(f"Container contains {self.__current_size} elements.\n")

        for i in range(self.__current_size):
            out_file.write(f"{i}: ")
            self.__storage[i].output(out_file)

    def modify(self):
        """Удаление из контейнера тех элементов, для которых значение,
        полученное с использованием функции, общей для всех альтернатив,
        меньше чем среднее арифметическое для всех элементов контейнера,
        полученное с использованием этой же функции."""
        average = self.calculate_average()
        i = 0

        while i < self.__current_size:
            if self.__storage[i].calculate_ratio_of_vowels_to_all_letters() < average:
                self.__storage.remove(self.__storage[i])
                self.__current_size -= 1
            else:
                i += 1

    def calculate_average(self) -> Decimal:
        """Вычисление среднего арифметического для всех элементов
           контейнера, полученное с использованием функции, общей
           для всех альтернатив."""
        sum_of_results = Decimal("0")

        for i in range(self.__current_size):
            sum_of_results += self.__storage[i].calculate_ratio_of_vowels_to_all_letters()

        if self.__current_size == 0:
            return Decimal("0")
        return Decimal(sum_of_results) / Decimal(self.__current_size)

    @staticmethod
    def static_input(plant_type: str, plant_info: list) -> tree.Tree or flower.Flower or bush.Bush:
        """Считывание параметров растения - статический метод."""
        if (plant_type.isnumeric()) and (int(plant_type) == 1):
            new_plant = tree.Tree()
        elif (plant_type.isnumeric()) and (int(plant_type) == 2):
            new_plant = bush.Bush()
        elif (plant_type.isnumeric()) and (int(plant_type) == 3):
            new_plant = flower.Flower()
        else:
            print(f"Incorrect value for plant type: {plant_type}. Input an integer from 1 to 3")
            sys.exit(12)
        if (len(plant_info[0]) == 0) or (len(plant_info[0]) > 20):
            print(f"Incorrect value for plant name length: {len(plant_info[0])}. "
                  f"Must be from 1 to 20.")
            sys.exit(13)
        new_plant._name = plant_info[0]
        new_plant.input(plant_info[1])

        return new_plant

    @staticmethod
    def static_random_input() -> tree.Tree or flower.Flower or bush.Bush:
        """Рандомная генерация параметров растения - статический метод."""
        plant_type = randint(1, 3)

        if int(plant_type) == 1:
            new_plant = tree.Tree()
        elif int(plant_type) == 2:
            new_plant = bush.Bush()
        elif int(plant_type) == 3:
            new_plant = flower.Flower()
        new_plant.random_input()
        new_plant._name = plant.Plant.generate_random_name()

        return new_plant

    def __del__(self):
        """Очистка контейнера от элементов."""
        for i in range(len(self.__storage) - 1, -1):
            del self.__storage[i]
        del self.__storage
