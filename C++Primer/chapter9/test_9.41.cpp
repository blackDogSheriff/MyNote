#include <iostream>
#include <vector>
#include <string>
using namespace std;
void input_string(string &s)
{
	s.reverse(100);
	char c;
	while (cin >> c)
		s.push_back(c);
}
int main(void)
{
	string s;
	input_string(s);
	cout << s << endl;
	return 0;
}
