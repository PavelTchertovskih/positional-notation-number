#include <gtest/gtest.h>
#include <sstream>
#include "positional_notation.h"
#include <iostream>
using namespace std;
TEST(positional_notation_number_test, test_01)//testing constructors and operator<<
{
	stringstream ss;
	string s;

	positional_notation_number pnn1;//10: 0
	ss << pnn1 << endl;
	getline(ss, s);
	ASSERT_TRUE(s == "10: 0");

	vector<positional_notation_number> numbers;
	for (unsigned int i = 2; i <= 36; i++)
	{
		positional_notation_number tmp (i);
		numbers.push_back(tmp);
	}
	for (unsigned int i = 2; i <= 36; i++)
	{
		ss << numbers[i - 2] << endl;
		getline(ss, s);//i: 0
		string tmp = to_string(i) + ": 0";
		//cout << tmp << endl;
		//cout << s << endl;
		ASSERT_TRUE(s == tmp);
	}
	
	positional_notation_number pnn2(1);//2: 0
	ss << pnn2 << endl;
	getline(ss, s);
	ASSERT_TRUE(s == "2: 0");
	
	positional_notation_number pnn3(37);//36: 0
	ss << pnn3 << endl;
	getline(ss, s);
	ASSERT_TRUE(s == "36: 0");

	vector<positional_notation_number> more_numbers;
	more_numbers = numbers;
	for (unsigned int i = 2; i <= 36; i++)
	{
		ss << more_numbers[i - 2] << endl;
		getline(ss, s);//i: 0
		string tmp = to_string(i) + ": 0";
		//cout << tmp << endl;
		//cout << s << endl;
		ASSERT_TRUE(s == tmp);
	}
}
TEST(positional_notation_number_test, test_02)//tesing operator>> and operator<< 
{
	stringstream is, os;
	positional_notation_number pnn;
	for (unsigned int b = 10; b <= 36; b++)
	{
		for (unsigned int num = 0; num <= 100; num++)
		{	
			string s = to_string(b) + ": " + to_string(num);
			is << s << endl;
			is >> pnn;
			os << pnn << endl;
			string tmp;
			getline(os, tmp);
			//cout << s << endl;
			//cout << tmp << endl;
			ASSERT_TRUE(tmp == s);
		}
	}
}
TEST(positional_notation_number_test, test_03)//testing operator= and conversion
{
	positional_notation_number pnn;
	stringstream ss;
	string s, tmp;
	for (unsigned int i = 0; i <= 100; i++)
	{
		pnn = i;
		ss << pnn << endl;
		getline(ss, s);//10: i
		tmp = "10: " + to_string(i);
		ASSERT_TRUE(tmp == s);
	}

	pnn = 12131415;
	
	pnn.conversion(2);
	ss << pnn << endl;
	getline(ss, s);//2: 101110010001110001010111
	ASSERT_TRUE(s == "2: 101110010001110001010111");

	pnn.conversion(3);
	ss << pnn << endl;
	getline(ss, s);//3: 211211100011200
	ASSERT_TRUE(s == "3: 211211100011200");

	pnn.conversion(8);
	ss << pnn << endl;
	getline(ss, s);//8: 56216127
	ASSERT_TRUE(s == "8: 56216127");

	pnn.conversion(16);
	ss << pnn << endl;
	getline(ss, s);//16: B91C57
	ASSERT_TRUE(s == "16: B91C57");

	pnn.conversion(17);
	ss << pnn << endl;
	getline(ss, s);//17: 89443b
	ASSERT_TRUE(s == "17: 89443B");

	pnn.conversion(23);
	ss << pnn << endl;
	getline(ss, s);//23: 1k81gj
	ASSERT_TRUE(s == "23: 1K81GJ");
	
	pnn.conversion(36);
	ss << pnn << endl;
	getline(ss, s);//36: 780nr
	ASSERT_TRUE(s == "36: 780NR");

	pnn.conversion(9);
	ss << pnn << endl;
	getline(ss, s);//9: 24740150
	ASSERT_TRUE(s == "9: 24740150");

	pnn.conversion(13);
	ss << pnn << endl;
	getline(ss, s);//13: 2689a6a
	ASSERT_TRUE(s == "13: 2689A6A");

	pnn.conversion(33);
	ss << pnn << endl;
	getline(ss, s);//33: a7ivl
	ASSERT_TRUE(s == "33: A7IVL");

	pnn.conversion(17);
	positional_notation_number pnn2;//4586931

	stringstream ss2;
	ss <<  "2: 10001011111110110110011" << endl;
	ss <<  "3: 22122001002100" << endl;
	ss <<  "4: 101133312303" << endl;
	ss <<  "5: 2133240211" << endl;
	ss <<  "6: 242151443" << endl;
	ss <<  "7: 53662656" << endl;
	ss <<  "8: 21376663" << endl;
	ss <<  "9: 8561070" << endl;
	ss << "10: 4586931" << endl;
	ss << "11: 2653258" << endl;
	ss << "12: 1652583" << endl;
	ss << "13: c47a7b" << endl;
	ss << "14: 87589d" << endl;
	ss << "15: 609156" << endl;
	ss << "16: 45fdb3" << endl;
	ss << "17: 33fac8" << endl;
	ss << "18: 27c939" << endl;
	ss << "19: 1g3e38" << endl;
	ss << "20: 18d76b" << endl;
	ss << "21: 12c646" << endl;
	ss << "22: jch2j" << endl;
	ss << "23: g8mli" << endl;
	ss << "24: djja3" << endl;
	ss << "25: bie26" << endl;
	ss << "26: a0pab" << endl;
	ss << "27: 8h129" << endl;
	ss << "28: 7cqir" << endl;
	ss << "29: 6e241" << endl;
	ss << "30: 5jqhl" << endl;
	ss << "31: 4tu2g" << endl;
	ss << "32: 4bvdj" << endl;
	ss << "33: 3sl1u" << endl;
	ss << "34: 3envp" << endl;  
	ss << "35: 31yf6" << endl;  
	ss << "36: 2qbar";  

	while(ss.good())
	{
		ss >> pnn2;
		pnn = pnn2;
		/*cout << pnn << "    ";
		cout << pnn2 << endl;*/
		ss2 << pnn << endl;
		getline(ss2, s);//"17: 33fac8"
		EXPECT_TRUE(s == "17: 33FAC8");
	}
}
TEST(positional_notation_number_test, test_04)//testing operator+, operator+= and operator==
{
	for (unsigned int b1 = 2; b1 <= 18; b1++)
	for (unsigned int b2 = 19; b2 <= 36; b2++)
	//for (unsigned int b3 = 2; b3 <= 36; b3++)
	for (unsigned int i = 50; i <= 100; i++)
	for (unsigned int j = 50; j <= 100; j++)
	{
		positional_notation_number pnn1(b1), pnn2(b2), pnn3;
		pnn1 = i;
		pnn2 += j;
		pnn3 = (i + j);
		ASSERT_TRUE(pnn1 == i);
		ASSERT_TRUE(pnn2 == j);
		ASSERT_TRUE(pnn3 == i + j);
		ASSERT_TRUE(pnn3 == pnn1 + j);
		ASSERT_TRUE(pnn3 == pnn1 + pnn2);
		pnn2 += pnn1;
		ASSERT_TRUE(pnn3 == pnn2);
	}
}
TEST(positional_notation_number_test, test_05)//testing operator++ and operator!=
{
	for (unsigned int b = 2; b <= 36; b++)
	{
		unsigned int j = 0;
		for (positional_notation_number i(b, 0); i != 37; i++)
		{
			ASSERT_TRUE(i == j);
			j++;
		}
	}
}
TEST(positional_notation_number_test, test_06)//using big numbers
{
	stringstream ss;
	ss << "34: XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" << endl;
	positional_notation_number pnn;
	ss >> pnn;
	pnn++;
	stringstream ss2;
	ss2 << pnn << endl;
	//cout << pnn << endl;
	string s;
	getline(ss2, s);//"34: XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"	
	//cout << s << endl;
	ASSERT_TRUE(s ==  "34: 1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
}
int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
