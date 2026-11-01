#include "Bus.h"
#include <sstream>
#include <stdexcept>

void Bus::setSeats(int value)
{
    // Автобус не може мати нуль або від'ємну кількість місць.
    if (value < 1 || value > 200)
        throw std::invalid_argument("Кількість місць має бути від 1 до 200");
    seats = value;
}

// Марка — це поле вкладеної машини, тому змінюємо її через Car.
void Bus::setBrand(const std::string& brand) { car.setBrand(brand); }
void Bus::changeSeats(int delta) { setSeats(seats + delta); }

void Bus::Init(const Car& newCar, int newSeats)
{
    // За композиції Bus отримує готовий незалежний об'єкт Car.
    setCar(newCar);
    setSeats(newSeats);
}

Bus::Bus() : car(), seats(20) { }

Bus::Bus(const std::string& brand, int cylinders, double power, int newSeats)
    : car(brand, cylinders, power)
{
    // Спочатку створюється вкладена Car, після чого перевіряються місця.
    setSeats(newSeats);
}

Bus::Bus(const Car& newCar, int newSeats) { Init(newCar, newSeats); }
Bus::Bus(const Bus& b) : car(b.car), seats(b.seats) { }
Bus::~Bus() { }

Bus& Bus::operator = (const Bus& b)
{
    // Копіюються обидві складові автобуса: машина і місця.
    if (this != &b) { car = b.car; seats = b.seats; }
    return *this;
}

Bus::operator std::string() const
{
    std::ostringstream ss;
    ss << std::string(car) << "seats = " << seats << '\n';
    return ss.str();
}

Bus& Bus::operator ++ () { if (seats < 200) changeSeats(1); return *this; }
Bus& Bus::operator -- () { if (seats > 1) changeSeats(-1); return *this; }
Bus Bus::operator ++ (int) { Bus old(*this); ++(*this); return old; }
Bus Bus::operator -- (int) { Bus old(*this); --(*this); return old; }

std::ostream& operator << (std::ostream& out, const Bus& b) { out << std::string(b); return out; }

std::istream& operator >> (std::istream& in, Bus& b)
{
    // Спочатку читаємо Car, потім кількість місць і створюємо Bus через Init.
    Car c;
    int seats;
    std::cout << "car:" << std::endl;
    in >> c;
    std::cout << "seats = ? ";
    in >> seats;
    if (in) b.Init(c, seats);
    return in;
}
