#include <iostream>
#include <vector>
using namespace std;

class Screen {
public:
//友元类成员函数可以访问Screen的所有成员
friend class Window_mgr;	//将Window_mgr定义成友元
//成员函数做友元
	typedef string::size_type pos;	

	pos size() const 
	{
		return height * width;
	}
	//using pos = string::size_type;
	Screen() = default;
	Screen(pos ht, pos wd, char c) : height(ht), width(wd), 
									contents(ht * wd, c){}
	//定义在类内部的成员函数自动内联, 因此构造函数和get也是内联函数
	//成员函数重载
	char get() const { return contents[cursor]; }	//隐式内联
	inline char get(pos ht, pos wd) const;			//显式内联

	Screen &move(pos r, pos c);						//可以在之后设为内联
	void some_member() const;
	
	Screen &set(char);
	Screen &set(pos, pos, char);

	//从const成员返回*this
	//一个const成员如果以引用的形式返回*this，那么返回的是产量引用
	Screen &display(ostream &os)
			{ do_display(os); return *this;}
	const Screen &display(ostream &os) const 
			{ do_display(os); return *this; }

private:
	pos cursor = 0;	
	pos height = 0, width = 0;
	string contents;
	mutable size_t access_ctr;	//可变的是const成员函数可以修改该私有变量

	void do_display(ostream &os) const {os << contents;}
};

class Window_mgr {
public:
	using ScreenIndex = vector<Screen>::size_type;
	void clear(ScreenIndex);
	ScreenIndex addScreen(const Screen &);
private:
	//类内初始值必须使用=或者{}
	vector<Screen> screens{Screen(24, 80, ' ')};
};

Window_mgr::ScreenIndex Window_mgr::addScreen(const Screen &s)
{
	screens.push_back(s);
	return screens.size() - 1;
}

void Window_mgr::clear(ScreenIndex i)
{
	Screen &s = screens[i];
	s.contents = string(s.height * s.width, ' ');
}

inline Screen &Screen::set(char c)
{
	contents[cursor] = c;
	return *this;
}
inline Screen &Screen::set(pos r, pos col, char ch)
{
	contents[r * width + col] = ch;
	return *this;
}

inline Screen &Screen::move(pos r, pos c)
{
	pos row = r * width;
	cursor = row + c;
	return *this;
}
char Screen::get(pos r, pos c) const	//在类的内部声明成inline
{
	pos row = r * width;
	return contents[row + c];
}

void Screen::some_member() const
{
	++ access_ctr;
}


int main(void)
{
	Screen myScreen(5, 3, ' ');
	const Screen blank(5, 3, ' ');
	myScreen.set('#').display(cout);
	blank.display(cout);
//	myScreen.move(4, 0).set('#');	//使用引用操作同一对象，如果直接返回类则不是
	return 0;
}
