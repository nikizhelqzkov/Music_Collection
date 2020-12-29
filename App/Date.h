#ifndef DATE_H_INCLUDED
#define DATE_H_INCLUDED
#include <iostream>
/**
 * @brief Класа дата е нужен за потребителя да си въвежда рожденната дата
 * 
 */
class Date
{
private:
	unsigned short day, month, year;

	bool isValidDate(unsigned short day, unsigned short month, unsigned short year);

public:
	Date();
	Date(unsigned day, unsigned month, unsigned year);
	Date(const Date &);

	void read();

	void print() const;
	void print(std::ostream &) const;
	Date &operator=(const Date &);

	unsigned getDay() const;
	void setDay(unsigned);

	unsigned getMonth() const;
	void setMonth(unsigned);

	unsigned getYear() const;
	void setYear(unsigned);

	//Date &getLiveData();
	bool operator==(const Date &) const;
	bool isEqual(const Date &other) const;
	bool isBefore(const Date &other) const;
	friend std::ostream &operator<<(std::ostream &, const Date &);
	bool operator<(const Date &) const;
};

#endif