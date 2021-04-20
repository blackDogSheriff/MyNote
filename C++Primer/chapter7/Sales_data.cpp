#include <iostream>
using namespace std;
struct Sales_data {
	//Sales_data() = default;	//=default可以写在类的内部：内联，也可以写在类的外面：不是内联
	//默认实参构造函数
	Sales_data(const string &s) : bookNo(s){}
	Sales_data(string s = ""): bookNo(s){}	
	//下面两者等价
	//explicit关键字：限定隐式类型转换，只对一个实参的构造函数有效，需要多个实参的构造函数不能用于执行隐式转换，所以无须将这些构造函数指定为explicit的；
	//explicit 只能在类内声明构造函数的时候可以使用；
	explicit Sales_data(const string &s, unsigned n, double p) :
			bookNo(s), units_sold(n), revenue(p * n) {}
#if 0
	Sales_data(const string &s, unsigned n, double p) 
	{
		bookNo = s;
		units_sold = n;
		revenue = n * p;
	}
#endif
	explicit Sales_data(istream &);
	//委托构造函数-初始化列表调用其他构造函数
	Sales_data(): Sales_data("", 0, 0.0){}
	//Sales_data(string s): Sales_data(s, 0, 0){}
	//构造函数：
	//没有返回值，默认构造函数没有实参，不能声明成const，可以有多个构造函数重载
	//如果没有显性定义构造函数，那么编译器就会隐式的定义一个默认构造函数也叫合成的默认构造函数；//构造函数：
	string isbn() const { return bookNo; }
	//this指针
	//string isbn() const { return this->bookNo; };
	//调用成员函数时，将对象地址传递给this指针
	//this指针默认为Sales_data *const,因此不可以传递const Sales_data *，
	//所以常量对象不能调用成员函数	--重点
	//常成员函数参数列表后面的const，表示this是一个指向常量的指针，因此可以被常量对象调用
	Sales_data &combine(const Sales_data &);

	double avg_price() const;	//在类的外部定义成员函数

	string bookNo;
	unsigned units_sold = 0;
	double revenue = 0.0;
};

Sales_data add(const Sales_data &, const Sales_data &);
ostream &print(ostream &, const Sales_data &);
istream &read(istream &, Sales_data &);

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
