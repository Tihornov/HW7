#ifndef INTARRAY_H
#define INTARRAY_H

#include <exception>
#include <iostream>

class Bad_range : public std::exception {
public:
    const char* what() const noexcept override;
};
class Bad_length : public std::exception {
public:
    const char* what() const noexcept override;
};


class IntArray
{
private:
    int m_length{};
    int* m_data{};

public:
    IntArray() = default;

    IntArray(int length) :
        m_length{ length }
    {   
        if (length >= 0)
            m_data = new int[length] {};
        else
        {
            throw Bad_length();
        }
    }

   
    IntArray(const IntArray& a)
    {
        // Установите размер нового массива соответствующим образом
        reallocate(a.getLength());

        // Скопируйте элементы
        for (int index{ 0 }; index < m_length; ++index)
            m_data[index] = a.m_data[index];
    }

    ~IntArray()
    {
        delete[] m_data;
        // нам не нужно устанавливать здесь значение m_data равным null или m_length равным 0, так как объект в любом случае будет уничтожен сразу после выполнения этой функции
    }

    void erase()
    {
        delete[] m_data;
        // Нам нужно убедиться, что мы установили здесь значение m_data равным nullptr, иначе это
        // останется указывать на освобожденную память
        m_data = nullptr;
        m_length = 0;
    }

    int& operator[](int index)

    {
        if (index < 0 && index >= m_length)
        {
            throw Bad_range();
        }
        return m_data[index];
    }

    // перераспределение изменяет размер массива. Все существующие элементы будут уничтожены. Эта функция работает быстро.
    void reallocate(int newLength)
    {
        // Сначала мы удаляем все существующие элементы
        erase();

        // Если наш массив сейчас будет пустым, вернитесь сюда
        if (newLength <= 0)
            return;

        // Затем мы должны выделить новые элементы
        m_data = new int[newLength];
        m_length = newLength;
    }

    // изменение размера изменяет размер массива. Все существующие элементы будут сохранены. Эта функция работает медленно.
    void resize(int newLength)
    {
        // если массив уже имеет нужную длину, мы закончили
        if (newLength == m_length)
            return;

        // Если мы изменяем размер до пустого массива, сделайте это и верните
        if (newLength <= 0)
        {
            erase();
            return;
        }

        // Теперь мы можем предположить, что newLength равен как минимум 1 элементу. Этот алгоритм
        // работает следующим образом: сначала мы собираемся выделить новый массив. Тогда мы
        // собираемся скопировать элементы из существующего массива в новый массив.
        // Как только это будет сделано, мы можем уничтожить старый массив и создать m_data
        // указывает на новый массив.
        // Сначала мы должны выделить новый массив
        int* data{ new int[newLength] };

        // Затем мы должны выяснить, сколько элементов нужно скопировать из существующего
        // array в новый массив. Мы хотим скопировать столько элементов, сколько имеется
        // в меньшем из двух массивов.
        if (m_length > 0)
        {
            int elementsToCopy{ (newLength > m_length) ? m_length : newLength };

            // Теперь скопируйте элементы один за другим
            for (int index{ 0 }; index < elementsToCopy; ++index)
                data[index] = m_data[index];
        }

        // Теперь мы можем удалить старый массив, потому что он нам больше не нужен
        delete[] m_data;

        // И вместо этого используйте новый массив! Обратите внимание, что это просто указывает на m_data
        // по тому же адресу, что и новый массив, который мы динамически выделили. Потому что
        // данные были распределены динамически, они не будут уничтожены, когда выйдут за пределы области видимости.
        m_data = data;
        m_length = newLength;
    }

    IntArray& operator=(const IntArray& a)
    {
        //  Проверка самостоятельного присвоения
        if (&a == this)
            return *this;

        // Установите размер нового массива соответствующим образом
        reallocate(a.getLength());

        // Затем скопируйте элементы
        for (int index{ 0 }; index < m_length; ++index)
            m_data[index] = a.m_data[index];

        return *this;
    }

    void insertBefore(int value, int index)
    {
        //  проверяется значение индекса
        if (index < 0 && index >= m_length)
        {
            throw Bad_range();
        }

        // Сначала создайте новый массив, который на один элемент больше старого массива
        int* data{ new int[m_length + 1] };

        // Скопируйте все элементы вплоть до индекса
        for (int before{ 0 }; before < index; ++before)
            data[before] = m_data[before];

        // Вставляем наш новый элемент в новый массив
        data[index] = value;

        // Скопируйте все значения после вставленного элемента
        for (int after{ index }; after < m_length; ++after)
            data[after + 1] = m_data[after];

        // Наконец, удалите старый массив и используйте вместо него новый массив
        delete[] m_data;
        m_data = data;
        ++m_length;
    }

    void remove(int index)
    {
        // проверьте значение вашего индекса
        if (index < 0 && index >= m_length)
        {
            throw Bad_range();
        }
        // Если мы удаляем последний элемент в массиве, мы можем просто стереть массив и вернуться раньше
        if (m_length == 1)
        {
            erase();
            return;
        }

        // Сначала создайте новый массив, который на один элемент меньше старого массива
        int* data{ new int[m_length - 1] };

        // Скопируйте все элементы вплоть до индекса
        for (int before{ 0 }; before < index; ++before)
            data[before] = m_data[before];

        // Скопируйте все значения после удаленного элемента
        for (int after{ index + 1 }; after < m_length; ++after)
            data[after - 1] = m_data[after];

        // наконец, удалите старый массив и используйте вместо него новый массив
        delete[] m_data;
        m_data = data;
        --m_length;
    }

    // Пара дополнительных функций просто для удобства
    void insertAtBeginning(int value) { insertBefore(value, 0); }
    void insertAtEnd(int value) { insertBefore(value, m_length); }

    int getLength() const { return m_length; }
};

#endif