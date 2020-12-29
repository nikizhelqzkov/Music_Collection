#include <iostream>
#include <ctime>
#include "Date.h"
#include <string>
/**
 * @brief Construct a new Date:: Date object
 * 
 */
Date::Date() : day(1), month(1), year(1)
{
}
/**
 * @brief Construct a new Date:: Date object
 * 
 * @param d 
 * @param m 
 * @param y 
 */
Date::Date(unsigned d, unsigned m, unsigned y)
{

    if (isValidDate(d, m, y))
    {
        this->day = d;
        this->month = m;
        this->year = y;
    }

    else
    {
        this->day = 1;
        this->month = 1;
        this->year = 2020;
    }
}
/**
 * @brief Copy Construct a new Date:: Date object
 * 
 * @param other 
 */
Date::Date(const Date &other)
{
    this->day = other.day;
    this->month = other.month;
    this->year = other.year;
}
/**
 * @brief Четене от конзола на дата докато тя не е валидна според условията за валидност
 * 
 */
void Date::read()
{
    int day, month, year;
    std::string d, m, y;
    bool isOk = false;
    do
    {
        isOk = false;
        std::cout << "Day: ";
        std::getline(std::cin, d);
        std::cout << "Month: ";
        std::getline(std::cin, m);
        std::cout << "Year: ";
        std::getline(std::cin, y);
        day = !d.empty() ? std::stoi(d) : -1;
        month = !m.empty() ? std::stoi(m) : -1;
        year = !y.empty() ? std::stoi(y) : -1;
        if (day == -1 || month == -1 || year == -1)
        {
            std::cout << "Wrong numbers\n";
        }
        else if (!isValidDate(day, month, year))
        {
            std::cout << "Invalid date!!!\n";
        }
        else
        {
            isOk = true;
        }

    } while (!isOk);

    this->day = day;
    this->month = month;
    this->year = year;
}
/**
 * @brief Проверка дали има правилен номер на месец(0<месец<=12) и според месеца проверка дали съществува такъв ден като номер при условие дали е високосна годината или не
 *  и връща дали е правилна датата
 * 
 * @param d 
 * @param m 
 * @param y 
 * @return true 
 * @return false 
 */
bool Date::isValidDate(unsigned short d, unsigned short m, unsigned short y)
{
    if (!y)
    {
        return false;
    }

    if (m < 1 || m > 12)
    {
        return false;
    }

    bool leapYear = (y % 4 == 0) && !(y % 100 == 0 && y % 400 != 0);

    unsigned maxDays;
    switch (m)
    {
    case 2:
        maxDays = 28 + leapYear;
        break;
    case 4:
    case 6:
    case 9:
    case 11:
        maxDays = 30;
        break;
    default:
        maxDays = 31;
        break;
    }

    return d > 0 && d <= maxDays;
}
/**
 * @briefМутатор извеждащ стойността на член-данната day
 * 
 * @return unsigned 
 */
unsigned Date::getDay() const
{
    return this->day;
}
/**
 * @brief Мутатор с аргумент, който се вкарва в член-данната day
 * 
 * @param newDay 
 */
void Date::setDay(unsigned newDay)
{
    if (isValidDate(newDay, this->month, this->year))
        this->day = newDay;
}
/**
 * @brief Мутатор извеждащ стойността на член-данната month
 * 
 * @return unsigned 
 */
unsigned Date::getMonth() const
{
    return this->month;
}
/**
 * @brief Мутатор с аргумент, който се вкарва в член-данната month
 * 
 * @param newMonth 
 */
void Date::setMonth(unsigned newMonth)
{
    if (isValidDate(this->day, newMonth, this->year))
        this->month = newMonth;
}
/**
 * @brief Мутатор извеждащ стойността на член-данната year
 * 
 * @return unsigned 
 */
unsigned Date::getYear() const
{
    return this->year;
}
/**
 * @brief Мутатор с аргумент, който се вкарва в член-данната year
 * 
 * @param newYear 
 */
void Date::setYear(unsigned newYear)
{
    if (isValidDate(this->day, this->month, newYear))
        this->year = newYear;
}
/**
 * @brief Булева функция проверяваща дали две дати съвпадат
 * 
 * @param other 
 * @return true 
 * @return false 
 */
bool Date::isEqual(const Date &other) const
{
    return this->day == other.day && this->month == other.month && this->year == other.year;
}
/**
 * @brief Булева функция проверяваща дали една дата е преди друга дата
 * 
 * @param other 
 * @return true 
 * @return false 
 */
bool Date::isBefore(const Date &other) const
{
    if (this->year < other.year)
        return true;
    if (this->year > other.year)
        return false;

    if (this->month < other.month)
        return true;
    if (this->month > other.month)
        return false;

    return this->day < other.day;
}
/**
 * @brief Оператор за присвояване на 2 дати
 * 
 * @param other 
 * @return Date& 
 */
Date &Date::operator=(const Date &other)
{
    this->day = other.day;
    this->month = other.month;
    this->year = other.year;
    return *this;
}
/**
 * @brief Булев оператор проверяващ дали две дати съвпадат
 * 
 * @param other 
 * @return true 
 * @return false 
 */
bool Date::operator==(const Date &other) const
{
    return day == other.day && month == other.month && year == other.year;
}
/**
 * @brief Оператор за извеждане на данни в поток
 * 
 * @param out 
 * @param date 
 * @return std::ostream& 
 */
std::ostream &operator<<(std::ostream &out, const Date &date)
{
    // out << date.day << '-' << date.month << '-' << date.year<<" ";
    bool d = true;
    bool m = true;
    if (date.month < 10)
    {
        m = false;
    }
    if (date.day < 10)
    {
        d = false;
    }
    if (!d && !m)
    {
        out << "0" << date.day << " 0" << date.month << ' ' << date.year;
    }
    else if (!m)
    {
        out << date.day << " 0" << date.month << ' ' << date.year;
    }
    else if (!d)
    {
        out << "0" << date.day << ' ' << date.month << ' ' << date.year;
    }
    else
    {
        out << date.day << ' ' << date.month << ' ' << date.year;
    }
    return out;
}
/**
 * @brief Булев оператор извеждащ дали една дата е преди друга дата
 * 
 * @param date 
 * @return true 
 * @return false 
 */
bool Date::operator<(const Date &date) const
{
    return isBefore(date);
}