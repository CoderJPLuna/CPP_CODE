#include<iostream>
using namespace std;
class Date
{
public:
	int GetMonthDay(int year, int month)
	{
		static int monthDays[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
		//是二月且闰年返回29
		//每四年闰，每百年不闰，每四百年闰
		if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0))
		{
			return 29;
		}
		return monthDays[month];
	}
	Date(int year = 1, int month = 1, int day = 1)
	{
		if (year >= 1 && month <= 12 && day >= 1 && day <= GetMonthDay(year, month))
		{
			_year = year;
			_month = month;
			_day = day;
		}
		else
		{
			cout << "非法日期" << endl;
		}
	}
	Date(const Date& d)
	{
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}
	//运算符的重载是为了自定义类型能够像内置类型一样使用运算符
	//日期比较的重载
	bool operator<(const Date& d)
	{
		if (_year < d._year)
			return true;
		else if (_year == d._year && _month < d._month)
			return true;
		else if (_year = d._year && _month == d._month && _day < d._day)
			return true;
		return false;
	}
	bool operator==(const Date & d)
	{
		return _year == d._year && _month == d._month && _day == d._day;
	}
	bool operator<=(const Date& d)
	{
		return *this < d || *this == d;//复用上面的重载来实现
	}
	bool operator>(const Date& d)
	{
		return !(*this <= d);
	}
	bool operator>=(const Date& d)
	{
		return !(*this < d);
	}
	bool operator!=(const Date& d)
	{
		return !(*this == d);
	}
	//日期加减的重载
	Date& operator+(int day)
	{
		Date ret(*this);//用d拷贝构造一个ret
		ret._day += day;
		while (ret._day > GetMonthDay(ret._year, ret._month))
		{
			//如果日期不合法，就需要进位
			ret._day -= GetMonthDay(ret._year, ret._month);
			ret._month++;
			if (ret._month == 13)
			{
				ret._year++;
				ret._month = 1;
			}
		}
		return ret;
	}
	Date& operator+=(int day)
	{
		if (day < 0)
			return *this -= -day;
		_day += day;
		while (_day > GetMonthDay(_year, _month))
		{
			_day -= GetMonthDay(_year, _month);
			_month++;
			if (_month == 13)
			{
				_year++;
				_month = 1;
			}
		}
		return *this;
	}
	Date& operator-(int day)
	{
		Date ret(*this);
		ret._day -= day;
		while (ret._day <= 0)
		{
			ret._month--;
			if (ret._month == 0)
			{
				ret._year--;
				ret._month = 12;
			}
			ret._day += GetMonthDay(ret._year, ret._month);
		}
		return ret;
	}
	Date& operator-=(int day)
	{
		if (day < 0)
			return *this += -day;
		_day -= day;
		while (_day <= 0)
		{
			_month--;
			if (_month == 0)
			{
				_year--;
				_month = 12;
			}
			_day += GetMonthDay(_year, _month);
		}
		return *this;
	}
	Date& operator++()//默认为前置++
	{
		*this += 1;
		return *this;
	}
	Date& operator++(int)//为了构成函数重载，编译器处理为后置++
	{
		Date tmp(*this);
		*this += 1;
		return tmp;//返回加之前的值
	}
	Date& operator--()
	{
		*this -= 1;
		return *this;
	}
	Date& operator--(int)
	{
		Date tmp(*this);
		*this -= 1;
		return tmp;
	}
	int operator-(const Date& d)
	{
		int flag = 1;
		Date max = *this;
		Date min = d;
		if (*this < d)
		{
			max = d;
			min = *this;
			flag = -1;
		}
		int n = 0;
		while (min != max)
		{
			++min;
			++n;
		}
		return n*flag;
	}
	//日期赋值的重载
	Date& operator=(const Date& d)//传引用返回可以减少一次赋值
	{
		if (this != &d)
		{
			_year = d._year;
			_month = d._month;
			_day = d._day;
		}
		return *this;
	}
	//d1=d2=d3
	//为实现连续赋值，d2=d3必须有返回值
	void Print()
	{
		cout << _year << "-" << _month << "-" << _day << endl;
	}
private:
	int _year;
	int _month;
	int _day;
};