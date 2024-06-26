#pragma once
#include<string>
using namespace std;
template <typename E>
class CODE {
private:
	string Co;
	E Va;
public:
	void setCo(string s) {
		Co = s;
	}
	void setVa(E v) {
		Va = v;
	}
	int length() { return Co.length(); }
	string getCo() { return Co; }
	E getVa() { return Va; }
};