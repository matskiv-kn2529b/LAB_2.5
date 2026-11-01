// Source.cpp
#ifdef _WIN32
// Windows.h має бути до заголовків, що підключають <iostream>:
// інакше Windows::byte конфліктує зі std::byte.
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#endif
#include "Bus.h"
#include <stdexcept>
using namespace std;

// Дзеркальні структури з тими ж типами полів, щоб показати розмір
// класів у режимі #pragma pack(1) (самі класи компілюються зі звичайним вирівнюванням)
#pragma pack(push, 1)
struct CarPacked { string brand; int cylinders; double power; };
struct BusPacked { CarPacked car; int seats; };
#pragma pack(pop)

int main()
{
#ifdef _WIN32
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
#endif

    try
    {
        // Демонстрація всіх потрібних способів створення об'єкта Car.
        cout << "=== Car: способи створення ===" << endl;
        Car c1;                          // без аргументів
        Car c2("Audi");                  // лише марка
        Car c3("BMW", 6, 250);           // ініціалізація
        Car c4(c3);                      // копіювання
        Car c5 = c3;                     // теж копіювання
        c1 = c3;                         // присвоєння
        cout << "c1:\n" << c1 << "c2:\n" << c2 << "c4:\n" << c4;

        cout << "=== Car: ++ / -- ===" << endl;
        Car c6 = ++c3;                   // префіксний
        cout << "++c3 -> c6:\n" << c6;
        c6 = c3--;                       // постфіксний
        cout << "c3-- -> c6:\n" << c6 << "c3 після:\n" << c3;
        --c3;
        c3.setPower(300);                // переприсвоєння потужності
        c3.changePower(-50);             // зміна потужності
        cout << "c3 після setPower/changePower:\n" << c3;

        // Статичний масив об'єктів — вимога методички.
        cout << "=== Масиви Car ===" << endl;
        Car arr[3] = { Car("Ford", 4, 120), Car(), Car("Opel") };
        for (int i = 0; i < 3; i++) cout << arr[i];

        // Bus містить Car: саме тут демонструється композиція класів.
        cout << "=== Bus: способи створення ===" << endl;
        Bus b1;
        Bus b2("MAN", 6, 320, 50);
        Bus b3(c3, 30);
        Bus b4(b2);
        b1 = b2;
        cout << "b1:\n" << b1 << "b3:\n" << b3;

        cout << "=== Bus: ++ / -- та методи ===" << endl;
        Bus b5 = ++b2;
        cout << "++b2 -> b5:\n" << b5;
        b5 = b2--;
        cout << "b2-- -> b5:\n" << b5 << "b2 після:\n" << b2;
        b2.setBrand("Mercedes");         // переприсвоєння марки
        b2.changeSeats(10);              // зміна кількості місць
        cout << "b2 після setBrand/changeSeats:\n" << b2;
        cout << "Марка b2: " << b2.getBrand() << endl;

        cout << "=== Масиви Bus ===" << endl;
        Bus busArr[2] = { Bus("Neoplan", 8, 400, 60), Bus() };
        for (int i = 0; i < 2; i++) cout << busArr[i];
        Bus* dyn = new Bus[2];           // динамічний масив об'єктів
        dyn[0] = b3;
        cout << dyn[0] << dyn[1];
        delete[] dyn;

        cout << "=== Приведення до string ===" << endl;
        string s = string(b3);
        cout << s;

        // Порівняння вирівнювання полів без pack(1) і з ним.
        cout << "=== Розміри класів ===" << endl;
        cout << "Без pack(1): Car = " << sizeof(Car)
            << ", Bus = " << sizeof(Bus) << endl;
        cout << "З pack(1):   Car = " << sizeof(CarPacked)
            << ", Bus = " << sizeof(BusPacked) << endl;

        cout << "=== Введення з клавіатури ===" << endl;
        Bus b6;
        cin >> b6;
        cout << b6;

        cout << "=== Перевірка коректності ===" << endl;
        c1.setCylinders(100); // навмисна помилка: демонстрація перевірки
    }
    catch (const invalid_argument& e)
    {
        cout << "Помилка: " << e.what() << endl;
    }
    return 0;
}
