#include <iostream>
using namespace std;
class Quote {
public:
	Quote() = default;
	Quote(const string &book, double sales_price):
			bookNo(book), price(sales_price) { }
	string isbn() const { return bookNo; }
	//派生类重新定义虚构函数override
	virtual double net_price(size_t n) const
			{ return n * price; }
	virtual ~Quote() = default;
	virtual void debug()
	{
		cout << "bookNo = " << bookNo << " price = " << price << endl;
	}
private:
	string bookNo;
protected:
	double price = 0.0;
};

class Disc_quote : public Quote {
public:
	Disc_quote() = default;
	Disc_quote(const string &book = " ", double price = 0.0, size_t qty = 0, double disc = 0.0):
			Quote(book, price), quantity(qty), discount(disc) { }
	//不可以在类的内部定义纯虚函数, 含有纯虚函数的类是抽象基类，
	//抽象基类负责定义接口，后续其他的类可以覆盖该接口
	//抽象基类不可以直接创建对象
	double net_price(size_t) const = 0;	//覆盖基类的纯虚函数
protected:
	size_t quantity = 0;
	double discount = 0.0;
};

class Bulk_Quote : public Disc_quote {
public:
	Bulk_Quote() = default;
	//调用基类构造函数初始化基类成员
	Bulk_Quote(const string &book, double p, size_t qty, double disc):
			Disc_quote(book, p, qty, disc), min_qty(qty), discount(disc) { }
	//派生类必须在内部对所有重新定义的虚函数进行声明
	//voerride：显示声明使用改写基类虚函数的成员
	//如果派生类没有继承虚函数，则派生类会直接继承其在基类中的版本
	double net_price(size_t) const override;
	virtual void debuf()
	{
		Quote::debug();
		cout << "min_qty = " << min_qty << " discount = " << discount << endl;
	}
private:
	size_t min_qty = 0;
	double discount = 0.0;
};

class Limited_quote : public Disc_quote {
public:
	Limited_quote(const string &book = " ", double p = 0.0, size_t qty = 0, double disc = 0.0) :
			Disc_quote(book, p, qty, disc), min_qty(qty), discount(disc) { }
	double net_price(size_t) const override;
private:
	size_t min_qty;
	double discount;

};

double Limited_quote::net_price(size_t cnt) const 
{
	if (cnt <= min_qty)
		return cnt * (1 - discount) * price;
	else
		return (cnt - min_qty * discount) * price;
}

//派生类可以访问基类的public和protected成员
double Bulk_Quote::net_price(size_t cnt) const 
{
	if (cnt >= min_qty)
		return cnt * (1 - discount) * price;
	else
		return cnt * price;
}
//基类的行参可以传递派生类的类型
double print_total(ostream &os, const Quote &item, size_t n)
{
	double ret = item.net_price(n);
	os << "ISBN: " << item.isbn() << " # sold: " 
	   << n << " total due: " << ret << endl;
	return ret;
}

int main(void) 
{
/*
	Quote item;
	Bulk_Quote bulk;
	Quote *p = &item;
	p = &bulk;
	Quote &r = bulk;
*/

	Quote qm("C++ Primer", 67); print_total(cout, qm, 10);
	Bulk_Quote bm("C Primer Plus", 67, 11, 0.1); print_total(cout, bm, 10);
	Limited_quote lm("C Primer Plus", 67, 5, 0.1); print_total(cout, lm, 10);

#if 0
	Quote base;
	Bulk_Quote *bulkP = &base;		//错误：不能将基类转换成派生类
	Bulk_Quote &bulkRef = base;		//错误：不能将基类转换成派生类
	Bulk_Quote bulk;

	Quote *itemP = &bulk;
	Bulk_Quote *bulkP = itemP;	//错误：不能将基类转换成派生类
#endif


	return 0;
}
