#ifndef MY_STRBLOB_H
#define MY_STRBLOB_H
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <initializer_list>
#include <stdexcept>

using namespace std;

class StrBlob {
public:
	typedef vecter<string>::size_type size_type;
	StrBlob();
	StrBlob(initializer_list<string> li);
	size_type size() const { return data->size(); }
	bool empty() const { return data->empty(); }
	void push_back(const string &t) { data->push_back(t); }
	void pop_back();
	string& front();
	const string& front() const;
	string& back();
	const string& back() const;

private:
	shared_ptr<vector<string>> data;
	void check(size_type i, const string &msg) const;
};

inline StrBlob::StrBlob(): data(make_shared<vector<string>>()) { }
StrBlob::StrBlob(initializer_list<string> li): 
			data(make_shared<vector<string>>(li) { }

inline void StrBlob::check(size_type i, const string &msg) const
{
	if (i >= data->size())
		throw out_of_rang(msg);
}

void StrBlob::pop_back()
{
	check(0, "pop_back on empty StrBlob");
	data->pop_back();
}

inline string& StrBlob::front()
{
	check(0, "front on empty StrBlob");
	return data->front();
}

inline const string& StrBlob::front() const
{
	check(0, "front on empty StrBlob");
	return data->front();
}

inline string& StrBlob::back() 
{
	check(0, "back on empty StrBlob");
	return data->back();
}

inline const string& StrBlob::back() const
{
	check(0, "back on empty StrBlob");
	return data->back();
}


#endif
