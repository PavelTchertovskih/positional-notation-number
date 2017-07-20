#ifndef POSITIONAL_NOTATION_H
#define POSITIONAL_NOTATION_H
#include <string>
#include <list>
#include <vector>
#include <istream>
#include <ostream>
using std::string;
using std::list;
using std::vector;
using std::istream;
using std::ostream;
class positional_notation_number
{
	unsigned int base;
	list<unsigned int> number;
	static unsigned int modulo(list<unsigned int>&, unsigned int, unsigned int);
	static bool eq_zero(const list<unsigned int>&);
public:
	//positional_notation_number(unsigned int base_){base = base_};
	positional_notation_number(unsigned int);
	positional_notation_number();
	positional_notation_number(unsigned int, unsigned int);
	positional_notation_number(const positional_notation_number&);
	bool set(vector<unsigned int>& A, unsigned int baseA);
	bool set(list<unsigned int>& A, unsigned int baseA);
	void conversion(unsigned int new_base);
	friend ostream& operator<<(ostream&, const positional_notation_number&);
	friend istream& operator>>(istream& is, positional_notation_number& pnn);
	positional_notation_number& operator=(const positional_notation_number&);
	positional_notation_number& operator=(unsigned int);
	positional_notation_number& operator+=(const positional_notation_number&);
	positional_notation_number& operator+=(unsigned int);
	positional_notation_number& operator++();
	positional_notation_number operator++(int);
	const positional_notation_number operator+(const positional_notation_number&) const;
	const positional_notation_number operator+(unsigned int) const;
	bool operator==(const positional_notation_number&) const;
	bool operator==(unsigned int) const;
	bool operator!=(const positional_notation_number&) const;
	bool operator!=(unsigned int) const;
};
ostream& operator<<(ostream& out, const positional_notation_number& pnn);
istream& operator>>(istream& is, positional_notation_number& pnn);
//std::vector<int> plus(const std::vector<int>& A, int baseA, const std::vector<int>& B, unsigned int baseB, unsigned int baseResult);
//std::list<int> plus(const std::list<int>& A, int baseA, const std::list<int>& B, unsigned int baseB, unsigned int baseResult);
#endif
