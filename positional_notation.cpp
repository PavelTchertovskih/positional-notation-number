#include "positional_notation.h"
#include <iostream>
using std::cerr;
using std::endl;
positional_notation_number::positional_notation_number(unsigned int base_)
{
	base = base_;
	if (base_ > 36 || base_ <= 1)
		cerr << "cant create positional_notation_number with " << "base = " << base_ << endl;
	if (base_ <= 1)
	{
		cerr << "base = 2 will be set" << endl;
		base = 2;
	}
	if (base_ > 36)
	{
		cerr << "base = 36 will be set" << endl;
		base = 36;
	}
}
positional_notation_number::positional_notation_number()
{
	base = 10;//default
}
positional_notation_number::positional_notation_number(const positional_notation_number& pnn)
{
	base = pnn.base;
	number = pnn.number;
}
positional_notation_number::positional_notation_number(unsigned int b, unsigned int n)
{
	base = b;
	*this = n;
}
ostream& operator<< (ostream& out, const positional_notation_number& pnn)
{
	out << pnn.base << ": ";
	if (pnn.number.empty())
		out << '0';
	for (auto& i: pnn.number)
	{
		if (i < 10)
			out << i;
		else if (i >= 10 && i < pnn.base)
			out << char(i + 'A' - 10);
		else 
		{
			out << '?';
			cerr << "positional_notation_number with invalid number detected" << endl;
			cerr << "base = " << pnn.base << "; got number = " << i << endl;
		}
	}
	return out;
}
istream& operator>>(istream& is, positional_notation_number& pnn)
{
	pnn.number.clear();
	//format is 
	//36: "HELLO"
	//or
	//36: HELLO
	is >> pnn.base;
	char c;
	is >> c;//:
	string s;
	is >> s;//"HELLO" or HELLO
	if (s[0] == '\"')
	{	//remove "'s
		s.pop_back();
		s.erase(0,1);
	}
	for (auto& i: s)
	{
		unsigned int num = pnn.base;
		if (i <= '9' && i >= '0') num = i - '0';
		else if (i <= 'Z' && i >= 'A') num = i - 'A' + 10;
		else if (i <= 'z' && i >= 'a') num = i - 'a' + 10;
		if (num >= pnn.base)
		{
			is.setstate(std::ios::failbit);
			break;
		}
		else
			pnn.number.push_back(num);
	}
	return is;
}
positional_notation_number& positional_notation_number::operator=(unsigned int num)
{
	number.clear();
	while (num != 0)
	{
		number.push_front(num % base);
		num = num / base;
	}
	return *this;
}
unsigned int positional_notation_number::modulo (list<unsigned int>& num, unsigned int base, unsigned int divisor)
{
	unsigned int tmp = 0;
	for (auto& i: num)
	{
		i += tmp * base;
		tmp = i % divisor;
		i = i / divisor;
	}
	return tmp;
}
bool positional_notation_number::eq_zero(const list<unsigned int>& num)
{
	for (auto& i: num)
	{
		if (i != 0)
			return false;
	}	
	return true;
}
void positional_notation_number::conversion (unsigned int new_base)
{
	if (new_base == base) return;
	list<unsigned int> tmp = number;
	number.clear();
	while(!eq_zero(tmp))
	{
		number.push_front(modulo(tmp, base, new_base));
	}
	base = new_base;
}
positional_notation_number& positional_notation_number::operator=(const positional_notation_number& pnn)
{
	if (this != &pnn)
	{
		unsigned int b = this->base;//saving the base
		this->number = pnn.number;//copying the value
		this->base = pnn.base;//copying the base
		this->conversion(b);//conversion
	}
	return *this;
}
bool positional_notation_number::set(vector<unsigned int>& A, unsigned int baseA)
{
	number.clear();
	base = baseA;
	for (auto& i: A)
	{
		if (i < base)
		{
			number.push_back(i);
		}
		else
		{
			number.clear();
			cerr << "invalid vector<unsigned int>" << endl;
			return false;
		}
	}	
	return true;
}
bool positional_notation_number::set(list<unsigned int>& A, unsigned int baseA)
{
	number.clear();
	base = baseA;
	for (auto& i: A)
	{
		if (i < base)
		{
			number.push_back(i);
		}
		else
		{
			number.clear();
			cerr << "invalid list<unsigned int>" << endl;
			return false;
		}
	}	
	return true;
}
positional_notation_number& positional_notation_number::operator+=(const positional_notation_number& pnn)
{
	//if (positional_notation_number::eq_zero(pnn.number))
	if (pnn.number.empty())// == 0
	{
		return *this;
	}
	//if (positional_notation_number::eq_zero(this->number))
	if (this->number.empty())// == 0
	{
		*this = pnn;
		return *this;
	}
	if (this-> base != pnn.base)
	{
		positional_notation_number tmp (this->base);
		tmp = pnn;
		*this += tmp;
		return *this;
	}
	auto i = this->number.rbegin();
	unsigned int tmp = 0;
	for (auto j = pnn.number.crbegin(); j != pnn.number.crend(); ++j)
	{
		if (i == this->number.rend())//fit lists sizes if necessary
		{
			number.push_front(0);
		}
		(*i) = (*i) + tmp + (*j);
		if (*i >= this->base)
		{
			tmp = 1;
			(*i) -= this->base;
		}
		else
			tmp = 0;
		++i;
		//std::cout << *i << endl;
	}
	if (tmp == 1)
	{
		for (;i != this->number.rend(); ++i)
		{
			(*i) = (*i) + tmp;
			if (*i >= this->base)
			{
				tmp = 1;
				(*i) -= this->base;
			}
			else
			{
				tmp = 0;
				break;
			}
		}
		if (tmp == 1)
			this->number.push_front(1);
	}
	return *this;
}
positional_notation_number& positional_notation_number::operator+=(unsigned int num)
{
	if (num == 0) return *this;
	if (this->number.empty())// == 0
	{
		*this = num;
		return *this;
	}
	positional_notation_number tmp(this->base);
	tmp = num;
	*this += tmp;
	return *this;
}
const positional_notation_number positional_notation_number::operator+(const positional_notation_number& other) const
{
	positional_notation_number result (*this);
	result += other;
	return result;
}
const positional_notation_number positional_notation_number::operator+(unsigned int other) const
{
	positional_notation_number result  (*this);
	result += other;
	return result;
}
positional_notation_number& positional_notation_number::operator++()
{
	//if (positional_notation_number::eq_zero(this->number))
	if (this->number.empty())// == 0
	{
		*this = 1;
		return *this;
	}
	unsigned int tmp = 1;
	for (auto i = this->number.rbegin(); i != this->number.rend(); ++i)
	{
		(*i) = (*i) + tmp;
		if (*i >= this->base)
		{
			tmp = 1;
			(*i) -= this->base;
		}
		else
		{
			tmp = 0;
			break;
		}
	}
	if (tmp == 1)
		this->number.push_front(1);
	return *this;
}
positional_notation_number positional_notation_number::operator++(int)
{
	positional_notation_number tmp (*this);
	operator++();
	return tmp;
}
bool positional_notation_number::operator==(const positional_notation_number& pnn) const
{
	//bool this_zero = positional_notation_number::eq_zero(this->number);
	bool this_zero = this->number.empty();
	//bool pnn_zero = positional_notation_number::eq_zero(pnn.number);
	bool pnn_zero = pnn.number.empty();
	if (this_zero && pnn_zero) return true;
	if (this_zero && !pnn_zero) return false;
	if (!this_zero && pnn_zero) return false;
	if (this->base != pnn.base)
	{
		positional_notation_number tmp(this->base);
		tmp = pnn;
		return operator==(tmp);
	}
	if (this->number.size() != pnn.number.size()) return false;
	auto i = this->number.cbegin();
	for(auto j = pnn.number.cbegin(); j != pnn.number.cend(); ++j)
	{
		if (*i != *j) return false;
		++i;
	}
	return true;
}
bool positional_notation_number::operator==(unsigned int num) const
{
	//bool this_zero = positional_notation_number::eq_zero(this->number);
	bool this_zero = this->number.empty();
	if (this_zero && num == 0) return true;
	if (this_zero && num != 0) return false;
	if (!this_zero && num == 0) return false;
	positional_notation_number tmp (this->base);
	tmp = num;
	return operator==(tmp);
}
bool positional_notation_number::operator!=(const positional_notation_number& pnn) const
{
	return !operator==(pnn);
}
bool positional_notation_number::operator!=(unsigned int num) const
{
	return !operator==(num);
}
