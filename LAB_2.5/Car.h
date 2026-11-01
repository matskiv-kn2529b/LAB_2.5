#pragma once
#include <iostream>
#include <string>

class Car
{
private:
    // Характеристики машини: усі поля приховані (інкапсуляція).
    std::string brand;
    int cylinders;
    double power;

public:
    // Методи читання полів (не змінюють об'єкт, тому const).
    std::string getBrand() const { return brand; }
    int getCylinders() const { return cylinders; }
    double getPower() const { return power; }

    // Методи запису перевіряють коректність значень.
    void setBrand(const std::string& brand);
    void setCylinders(int cylinders);
    void setPower(double power);
    void changePower(double delta);
    void Init(const std::string& brand, int cylinders, double power);

    // Три обов'язкові види конструкторів: без аргументів,
    // ініціалізації та копіювання.
    Car();
    explicit Car(const std::string& brand);
    Car(const std::string& brand, int cylinders, double power);
    Car(const Car& c);
    ~Car();

    Car& operator = (const Car& c);       // присвоєння
    // Перетворення об'єкта на рядок для зручного виведення.
    operator std::string() const;
    // ++ / -- змінюють числове поле power на одну одиницю.
    Car& operator ++ ();
    Car& operator -- ();
    Car operator ++ (int);
    Car operator -- (int);

    friend std::ostream& operator << (std::ostream& out, const Car& c);
    friend std::istream& operator >> (std::istream& in, Car& c);
};
