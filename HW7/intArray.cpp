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
    // ��������� ������ �� 10 ���������
    IntArray array(10);

    // ��������� ������
    for (int i{ 0 }; i < 10; ++i)
        array[i] = i + 1;

    // �������� ������ �� 8 ���������
    array.resize(8);

    // �������� ����� 20 ����� ��������� � �������� 5
    array.insertBefore(20, 5);

    // ������� ������� � �������� 3
    array.remove(3);

    // �������� 30 � 40 � ����� � ������
    array.insertAtEnd(30);
    array.insertAtBeginning(40);

    // ��� ��������� ������ ��� ����������� �������� ����� ���������� ��������
    // ������ �� ������
    //{
        IntArray b{ array };
        b = array;
        b = b;
        array = array;
    //}

    // ������������ ��� �����
    for (int i{ 0 }; i < array.getLength(); ++i)
        std::cout << array[i] << ' ';

    std::cout << '\n';

    return 0;
}