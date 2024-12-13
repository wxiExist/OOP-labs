#include <iostream>
#include "gcd.h"

int main() {
    setlocale(LC_ALL,"ru");
    int a, b;
    std::cout << "Введите два числа: ";
    std::cin >> a >> b;

    std::cout << "Наибольший общий делитель: " << gcd(a, b) << std::endl;
    system("pause");
    return 0;
}
