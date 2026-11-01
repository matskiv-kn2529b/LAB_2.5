#include "Car.h"
#include <sstream>
#include <stdexcept>

void Car::setBrand(const std::string& value)
{
    // Через setter неможливо задати порожню торгову марку.
    if (value.empty())
        throw std::invalid_argument("Марка машини не може бути порожньою");
    brand = value;
}

void Car::setCylinders(int value)
{
    // Перевірка предметної області: реальна машина має 1..16 циліндрів.
    if (value < 1 || value > 16)
        throw std::invalid_argument("Кількість циліндрів має бути від 1 до 16");
    cylinders = value;
}

void Car::setPower(double value)
{
    // Потужність не може бути нульовою або від'ємною.
    if (value <= 0 || value > 2000)
        throw std::invalid_argument("Потужність має бути більшою за 0 і не більшою за 2000");
    power = value;
}

void Car::changePower(double delta)
{
    setPower(power + delta);
}

void Car::Init(const std::string& newBrand, int newCylinders, double newPower)
{
    // Ініціалізація проходить тільки через setters, тому перевірки не обійти.
    setBrand(newBrand);
    setCylinders(newCylinders);
    setPower(newPower);
}

Car::Car() : brand("Не вказано"), cylinders(4), power(100.0) { }

Car::Car(const std::string& newBrand) : cylinders(4), power(100.0)
{
    setBrand(newBrand);
}

Car::Car(const std::string& newBrand, int newCylinders, double newPower)
{
    // Конструктор ініціалізації використовує спільний метод Init.
    Init(newBrand, newCylinders, newPower);
}

Car::Car(const Car& c) : brand(c.brand), cylinders(c.cylinders), power(c.power) { }

Car::~Car() { }

Car& Car::operator = (const Car& c)
{
    // Захист від самоприсвоєння: c = c.
    if (this != &c)
    {
        brand = c.brand;
        cylinders = c.cylinders;
        power = c.power;
    }
    return *this;
}

Car::operator std::string() const
{
    std::ostringstream ss;
    ss << "brand = " << brand << '\n'
       << "cylinders = " << cylinders << '\n'
       << "power = " << power << '\n';
    return ss.str();
}

Car& Car::operator ++ ()
{
    changePower(1.0);
    return *this;
}

Car& Car::operator -- ()
{
    if (power > 1.0) changePower(-1.0);
    return *this;
}

Car Car::operator ++ (int)
{
    // Постфіксна форма повертає старий стан, а потім змінює об'єкт.
    Car old(*this);
    ++(*this);
    return old;
}

Car Car::operator -- (int)
{
    Car old(*this);
    --(*this);
    return old;
}

std::ostream& operator << (std::ostream& out, const Car& c)
{
    out << std::string(c);
    return out;
}

std::istream& operator >> (std::istream& in, Car& c)
{
    // Введені дані передаємо Init, щоб спрацювали всі перевірки.
    std::string brand;
    int cylinders;
    double power;
    std::cout << "brand = ? ";
    in >> brand;
    std::cout << "cylinders = ? ";
    in >> cylinders;
    std::cout << "power = ? ";
    in >> power;
    if (in) c.Init(brand, cylinders, power);
    return in;
}
