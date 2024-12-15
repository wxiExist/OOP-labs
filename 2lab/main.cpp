#include "lab2.h"

int main() {
    try {
        // Создание объектов Hex
        Hex hex1("A3F5");
        Hex hex2("1B4");
        Hex hex3("A3F5"); // Добавим третий объект для тестирования операций

        std::cout << "Hex1: " << hex1.toString() << std::endl;
        std::cout << "Hex2: " << hex2.toString() << std::endl;
        std::cout << "Hex3: " << hex3.toString() << std::endl;

        // Тест сложения
        Hex sumHex = hex1; // Создаем копию для сложения
        sumHex += hex2;
        std::cout << "Сумма (Hex1 + Hex2): " << sumHex.toString() << std::endl;

        // Тест вычитания
        Hex subHex = sumHex; // Создаем копию суммы для вычитания
        subHex -= hex2;
        std::cout << "Разность (Сумма - Hex2): " << subHex.toString() << std::endl;

        // Тест операторов сравнения
        std::cout << "Hex1 == Hex2: " << (hex1 == hex2 ? "Да" : "Нет") << std::endl;
        std::cout << "Hex1 != Hex2: " << (hex1 != hex2 ? "Да" : "Нет") << std::endl;
        std::cout << "Hex1 < Hex2: " << (hex1 < hex2 ? "Да" : "Нет") << std::endl;
        std::cout << "Hex1 > Hex2: " << (hex1 > hex2 ? "Да" : "Нет") << std::endl;

        // Тест на равенство
        std::cout << "Hex1 == Hex3: " << (hex1 == hex3 ? "Да" : "Нет") << std::endl;
        std::cout << "Hex1 != Hex3: " << (hex1 != hex3 ? "Да" : "Нет") << std::endl;

        // Дополнительные проверки для граничных случаев
        Hex hexZero("0");
        Hex hexLarge("FFFFFFF"); // большой шестнадцатеричный номер
        Hex hexNegative("1A");   // Тест с меньшим значением

        std::cout << "HexZero: " << hexZero.toString() << std::endl;
        std::cout << "HexLarge: " << hexLarge.toString() << std::endl;
        std::cout << "HexNegative: " << hexNegative.toString() << std::endl;

        // Проверка сложения с нулем
        Hex addZero = hex1; // Создаем копию для сложения
        addZero += hexZero;
        std::cout << "Сложение с нулем (Hex1 + HexZero): " << addZero.toString() << std::endl;

        // Проверка вычитания большего числа
        try {
            Hex subLarge = hexZero; // Создаем копию нуля
            subLarge -= hexLarge; // Ожидается ошибка
            std::cout << "Разность (HexZero - HexLarge): " << subLarge.toString() << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Ошибка при вычитании: " << e.what() << std::endl;
        }

    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }

    return 0;
}