#include "pch.h"   
#include "CppUnitTest.h"

#include <string>
#include <sstream>
#include <stdexcept>

// підключаємо код лабораторної (разом з реалізацією)
#include "C:\Users\Mackiv\source\repos\LAB_2.5\LAB_2.5\Car.h"
#include "C:\Users\Mackiv\source\repos\LAB_2.5\LAB_2.5\Bus.h"
#include "C:\Users\Mackiv\source\repos\LAB_2.5\LAB_2.5\Car.cpp"
#include "C:\Users\Mackiv\source\repos\LAB_2.5\LAB_2.5\Bus.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
    TEST_CLASS(CarTests)
    {
    public:
        TEST_METHOD(DefaultConstructor)
        {
            Car c;
            Assert::IsFalse(c.getBrand().empty());  // марка за замовчуванням задана
            Assert::AreEqual(4, c.getCylinders());
            Assert::AreEqual(100.0, c.getPower());
        }

        TEST_METHOD(InitConstructor)
        {
            Car c("BMW", 6, 250);
            Assert::AreEqual("BMW", c.getBrand().c_str());
            Assert::AreEqual(6, c.getCylinders());
            Assert::AreEqual(250.0, c.getPower());
        }

        TEST_METHOD(CopyConstructorAndAssignment)
        {
            Car a("Audi", 4, 150);
            Car b(a);
            Car c;
            c = a;
            Assert::AreEqual("Audi", b.getBrand().c_str());
            Assert::AreEqual(150.0, c.getPower());
            Assert::AreEqual(4, c.getCylinders());
        }

        TEST_METHOD(SettersValidate)
        {
            Car c;
            Assert::ExpectException<std::invalid_argument>([&] { c.setBrand(""); });
            Assert::ExpectException<std::invalid_argument>([&] { c.setCylinders(0); });
            Assert::ExpectException<std::invalid_argument>([&] { c.setCylinders(17); });
            Assert::ExpectException<std::invalid_argument>([&] { c.setPower(-5); });
            Assert::ExpectException<std::invalid_argument>([&] { Car tmp("X", 4, 0); });
        }

        TEST_METHOD(ChangePower)
        {
            Car c("Ford", 4, 100);
            c.changePower(20);
            Assert::AreEqual(120.0, c.getPower());
            Assert::ExpectException<std::invalid_argument>([&] { c.changePower(-500); });
        }

        TEST_METHOD(PrefixIncrementDecrement)
        {
            Car c("Ford", 4, 100);
            Car r = ++c;
            Assert::AreEqual(101.0, c.getPower());
            Assert::AreEqual(101.0, r.getPower());
            --c;
            Assert::AreEqual(100.0, c.getPower());
        }

        TEST_METHOD(PostfixIncrementDecrement)
        {
            Car c("Ford", 4, 100);
            Car old = c++;
            Assert::AreEqual(100.0, old.getPower());
            Assert::AreEqual(101.0, c.getPower());
            old = c--;
            Assert::AreEqual(101.0, old.getPower());
            Assert::AreEqual(100.0, c.getPower());
        }

        TEST_METHOD(DecrementDoesNotGoBelowOne)
        {
            Car c("Ford", 4, 1);
            --c;
            Assert::AreEqual(1.0, c.getPower());
        }

        TEST_METHOD(ToStringAndOutput)
        {
            Car c("BMW", 6, 250);
            std::string expected = "brand = BMW\ncylinders = 6\npower = 250\n";
            std::string s = std::string(c);
            Assert::AreEqual(expected.c_str(), s.c_str());

            std::ostringstream out;
            out << c;
            std::string o = out.str();
            Assert::AreEqual(expected.c_str(), o.c_str());
        }
    };

    TEST_CLASS(BusTests)
    {
    public:
        TEST_METHOD(DefaultConstructor)
        {
            Bus b;
            Car defaultCar;                          // Bus() має містити типову Car()
            Assert::AreEqual(defaultCar.getBrand().c_str(), b.getBrand().c_str());
            Assert::AreEqual(20, b.getSeats());
        }

        TEST_METHOD(InitConstructors)
        {
            Bus b1("MAN", 6, 320, 50);
            Assert::AreEqual("MAN", b1.getBrand().c_str());
            Assert::AreEqual(50, b1.getSeats());
            Assert::AreEqual(320.0, b1.getCar().getPower());

            Car c("Volvo", 6, 300);
            Bus b2(c, 40);
            Assert::AreEqual("Volvo", b2.getBrand().c_str());
            Assert::AreEqual(40, b2.getSeats());
        }

        TEST_METHOD(CopyConstructorAndAssignment)
        {
            Bus a("MAN", 6, 320, 50);
            Bus b(a);
            Bus c;
            c = a;
            Assert::AreEqual(50, b.getSeats());
            Assert::AreEqual("MAN", c.getBrand().c_str());
            Assert::AreEqual(320.0, c.getCar().getPower());
        }

        TEST_METHOD(SettersValidate)
        {
            Bus b;
            Assert::ExpectException<std::invalid_argument>([&] { b.setSeats(0); });
            Assert::ExpectException<std::invalid_argument>([&] { b.setSeats(201); });
            Assert::ExpectException<std::invalid_argument>([&] { b.setBrand(""); });
            Assert::ExpectException<std::invalid_argument>([&] { b.changeSeats(-100); });
        }

        TEST_METHOD(SetBrandAndChangeSeats)
        {
            Bus b("MAN", 6, 320, 50);
            b.setBrand("Mercedes");
            b.changeSeats(10);
            Assert::AreEqual("Mercedes", b.getBrand().c_str());
            Assert::AreEqual(60, b.getSeats());
        }

        TEST_METHOD(PrefixAndPostfixOperators)
        {
            Bus b("MAN", 6, 320, 50);
            Bus r = ++b;
            Assert::AreEqual(51, b.getSeats());
            Assert::AreEqual(51, r.getSeats());

            Bus old = b--;
            Assert::AreEqual(51, old.getSeats());
            Assert::AreEqual(50, b.getSeats());

            --b;
            Assert::AreEqual(49, b.getSeats());
            old = b++;
            Assert::AreEqual(49, old.getSeats());
            Assert::AreEqual(50, b.getSeats());
        }

        TEST_METHOD(SeatsStayInBounds)
        {
            Bus lo("MAN", 6, 320, 1);
            --lo;
            Assert::AreEqual(1, lo.getSeats());

            Bus hi("MAN", 6, 320, 200);
            ++hi;
            Assert::AreEqual(200, hi.getSeats());
        }

        TEST_METHOD(ToStringAndOutput)
        {
            Bus b("MAN", 6, 320, 50);
            std::string expected =
                "brand = MAN\ncylinders = 6\npower = 320\nseats = 50\n";
            std::string s = std::string(b);
            Assert::AreEqual(expected.c_str(), s.c_str());

            std::ostringstream out;
            out << b;
            std::string o = out.str();
            Assert::AreEqual(expected.c_str(), o.c_str());
        }
    };
}