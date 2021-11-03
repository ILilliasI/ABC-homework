from typing.io import TextIO
from random import randint
from decimal import Decimal
from abc import ABC, abstractmethod


class Plant(ABC):
    """Функции для обработки растения."""

    def __init__(self):
        """Инициализация параметров растения."""
        self._name = ""

    @abstractmethod
    def input(self, plant_info: str):
        """Считывание параметров растения - абстрактный метод."""
        pass

    @abstractmethod
    def output(self, out_file: TextIO):
        """Вывод параметров растения - абстрактный метод."""
        pass

    @abstractmethod
    def random_input(self):
        """Рандомная генерация параметров растения - абстрактный метод."""
        pass

    @staticmethod
    def generate_random_name() -> str:
        """Генерация рандомного имени."""
        name_length = randint(1, 20)
        name = ""

        for i in range(name_length):
            name += chr(randint(97, 122))
        return name

    def calculate_ratio_of_vowels_to_all_letters(self) -> Decimal:
        """Поиск частного от деления числам гласных букв в названии на общую длину названия."""
        vowels_count = 0
        vowels = "aoiue"

        for char in self._name:
            if char in vowels:
                vowels_count += 1

        return Decimal(vowels_count) / Decimal(len(self._name))
