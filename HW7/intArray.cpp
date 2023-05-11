#include <iostream>
#include "IntArray.h"

const char* Bad_length::what() const noexcept {
    return "ERROR: Bad_length!";
}
const char* Bad_range::what() const noexcept {
    return "ERROR: Bad_range!";
}

int main()
{
    // Объявляем массив из 10 элементов
    IntArray array(10);

    // Заполняем массив
    for (int i{ 0 }; i < 10; ++i)
        array[i] = i + 1;

    // Изменяем массив на 8 элементов
    array.resize(8);

    // Вставьте число 20 перед элементом с индексом 5
    array.insertBefore(20, 5);

    // Удалите элемент с индексом 3
    array.remove(3);

    // Добавьте 30 и 40 к концу и началу
    array.insertAtEnd(30);
    array.insertAtBeginning(40);

    // Еще несколько тестов для обеспечения создания копий присвоения массивов
    // ничего не ломает
    //{
        IntArray b{ array };
        b = array;
        b = b;
        array = array;
    //}

    // Распечатайте все цифры
    for (int i{ 0 }; i < array.getLength(); ++i)
        std::cout << array[i] << ' ';

    std::cout << '\n';

    return 0;
}