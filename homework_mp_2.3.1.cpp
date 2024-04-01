// homework2.3.1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

//Задание 3
//Защищённый обмен данными

//Создайте класс Data, содержащий в качестве полей скалярные данные и мьютекс.
//Создайте функцию swap, которая принимает ссылки на два объекта класса Data и обменивает их местами.
//В функциях нужно сначала захватить мьютексы обоих объектов, а затем выполнить обмен данными.
//Реализуйте три варианта этой функции : при помощи lock, scoped_lock и unique_lock.


#include <iostream>
#include <vector>
#include <mutex>

std::mutex m;
class Data
{
    std::mutex m;
public:
    int a;
    int b;
};

void swap1(Data& data1, Data& data2)
{
    int c;
    int d;
    int e;
    int f;
    c = data1.a;
    d = data1.b;
    e = data2.a;
    f = data2.b;
    m.lock();
    data2.a = c;
    data2.b = d;
    data1.a = e;
    data1.b = f;
    m.unlock();
}

// Работает неустойчиво, то меняет данные в двух потоках, то не меняет
void swap2(Data& data1, Data& data2)
{
    int c;
    int d;
    int e;
    int f;
    c = data1.a;
    d = data1.b;
    e = data2.a;
    f = data2.b;

    std::lock_guard lk(m);
    data2.a = c;
    data2.b = d;
    data1.a = e;
    data1.b = f;
}

// через раз меняет данные, то есть неустойчивый результат
void swap3(Data& data1, Data& data2)
{
    int c;
    int d;
    int e;
    int f;

    c = data1.a;
    d = data1.b;
    e = data2.a;
    f = data2.b;
    std::scoped_lock lk(m);
    data2.a = c;
    data2.b = d;
    data1.a = e;
    data1.b = f;
}

// Работает неустойчиво, то меняет данные в двух потоках, то не меняет
void swap4(Data& data1, Data& data2)
{
    int c;
    int d;
    int e;
    int f;
    c = data1.a;
    d = data1.b;
    e = data2.a;
    f = data2.b;
    std::unique_lock lk(m);
    data2.a = c;
    data2.b = d;
    data1.a = e;
    data1.b = f;
}
int main()
{
    std::cout << "Hello World!\n";

    Data data1;
    data1.a = 1;
    data1.b = 2;

    Data data2;
    data2.a = 3;
    data2.b = 4;

    std::cout << " data1.a = " << data1.a << std::endl;
    std::cout << " data1.b = " << data1.b << std::endl;
    std::cout << " data2.a = " << data2.a << std::endl;
    std::cout << " data2.b = " << data2.b << std::endl;

    // в двух потоках дважды меняет местами данные и результат остаётся тот же
    std::thread t1(swap2, std::ref(data1), std::ref(data2));
    std::thread t2(swap2, std::ref(data1), std::ref(data2));
    t1.join();
    t2.join();

    std::cout << " data1.a = " << data1.a << std::endl;
    std::cout << " data1.b = " << data1.b << std::endl;
    std::cout << " data2.a = " << data2.a << std::endl;
    std::cout << " data2.b = " << data2.b << std::endl;

    return 0;
}
