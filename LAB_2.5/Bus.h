#pragma once
#include "Car.h"

class Bus
{
private:
    // КОМПОЗИЦІЯ: автобус містить об'єкт машини як своє поле.
    Car car;
    int seats;

public:
    // Методи доступу до даних автобуса та вкладеного об'єкта Car.
    Car getCar() const { return car; }
    int getSeats() const { return seats; }
    std::string getBrand() const { return car.getBrand(); }

    // Переприсвоєння марки делегується об'єкту Car.
    void setCar(const Car& car) { this->car = car; }
    void setSeats(int seats);
    void setBrand(const std::string& brand);
    void changeSeats(int delta);
    void Init(const Car& car, int seats);

    // Конструктори автобуса: типовий, ініціалізації та копіювання.
    Bus();
    Bus(const std::string& brand, int cylinders, double power, int seats);
    Bus(const Car& car, int seats);
    Bus(const Bus& b);
    ~Bus();

    Bus& operator = (const Bus& b);       // оператор присвоєння
    operator std::string() const;
    // ++ / -- змінюють кількість пасажирських місць на 1.
    Bus& operator ++ ();
    Bus& operator -- ();
    Bus operator ++ (int);
    Bus operator -- (int);

    friend std::ostream& operator << (std::ostream& out, const Bus& b);
    friend std::istream& operator >> (std::istream& in, Bus& b);
};
