#include <iostream>
using namespace std;
struct Sales_data {
	friend istream& operator>>(istream &, Sales_data &);
	friend ostream& operator<<(ostream &, const Sales_data &);
	friend Sales_data operator-(const Sales_data &lhs, const Sales_data &rhs)
	Sales_data operator+(const Sales_data &lhs, const Sales_data &rhs)
	{
		Sales_data sum = lhs;
		sum += rhs;
		return sum;
	}

	Sales_data(const string &s) : bookNo(s){}
	Sales_data(string s = ""): bookNo(s){}	
	explicit Sales_data(const string &s, unsigned n, double p) :
			bookNo(s), units_sold(n), revenue(p * n) {}
	explicit Sales_data(istream &);
	Sales_data(): Sales_data("", 0, 0.0){}

	//拷贝构造
	Sales_data(const Sales_data &);
	
	string isbn() const { return bookNo; }
	Sales_data &combine(const Sales_data &);

	double avg_price() const;	//在类的外部定义成员函数

	string bookNo;
	unsigned units_sold = 0;
	double revenue = 0.0;
};
Sales_data& Sales_data::operator-=(const Sales_data &rhs)
{
	units_sold -= rhs.units_sold;
	revenue -= rhs.revenue;
	return *this;
}

Sales_data operator-(const Sales_data &lhs, const Sales_data &rhs)
{
	Sales_data sub = lhs;
	Sales_data -= rhs;
	return sub;
}

istream &operator>>(istream &is, Sales_data &item)
{
	double price;
	is >> item.bookNo >> item.units_sold >> price;
	if (is)
		item.revenue = item.units_sold * price;
	else
		item = Sales_data();	//输入失败，则初始化对象
	return is;
}

ostream &operator<<(ostream &os, const Sales_data &item)
{
	os << item.isbn << " " << item.units_sold << " "
	   << itrm.revenue << " " << item.avg_price();
}

Sales_data add(const Sales_data &, const Sales_data &);
ostream &print(ostream &, const Sales_data &);
istream &read(istream &, Sales_data &);

Sales_data::Sales_data(const Sales_data&): 
	bookNo(orig.bookNo), 
	units_sold(orig.units_sold), 
	revenue(orig.revenue)
	{ }

double Sales_data::avg_price() const {	//Sales_data:定义的函数声明在Sales_data的作用域中
	if (units_sold)
		return revenue/units_sold;
	else
		return 0;
}

Sales_data &Sales_data::combine(const Sales_data &rhs)
{
	units_sold += rhs.units_sold;
	revenue += rhs.revenue;
	return *this;
}

istream &read(istream &is, Sales_data &item)
{
	double price = 0;
	is >> item.bookNo >> item.units_sold >> price;
	item.revenue = price * item.units_sold;
	return is;
}

ostream &print(ostream &os, const Sales_data &item)
{
	os << item.isbn() << " " << item.units_sold << " " 
		<< item.revenue << " " << item.avg_price();
	return os;
}

Sales_data add(const Sales_data &lhs, const Sales_data &rhs)
{
	Sales_data sum = lhs;
	sum.combine(rhs);
	return sum;
}

//构造函数外部定义
Sales_data::Sales_data(istream &is)
{
	read(is, *this);
}



int main(void)
{
	Sales_data Sd("dsjakldjsladj", 12, 2);
	cout << Sd.isbn() << endl;
	return 0;
}

/*
笔记：
	1. 留意拷贝构造和析构函数
*/
