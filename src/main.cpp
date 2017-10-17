#include <string>
#include <algorithm>
#include <iostream>
#include <tuple>
#include <ctime>
#include <cstdint>
#include <sstream>
#include "sformat.h"

void Test1()
{
	auto buffer = new char[40960];
	auto c = 0;
	auto t = clock();
	while (t + 1000 > clock())
	{
		++c;
		snprintf(buffer, 40960, "%s", "format, format, format, format, format");
	}
	std::cout << c << std::endl;

	c = 0;
	t = clock();
	while (t + 1000 > clock())
	{
		++c;
		SFormat("{0}, {0}, {0}, {0}, {0}", "format");
	}
	std::cout << c << std::endl;
}

void Test2()
{
	auto buffer = new char[40960];
	auto c = 0;
	auto t = clock();
	while (t + 1000 > clock())
	{
		++c;
		snprintf(buffer, 40960, "%s, %s, %s", "format", "format", "format");
	}
	std::cout << c << std::endl;

	c = 0;
	t = clock();
	while (t + 1000 > clock())
	{
		++c;
		SFormat("{0}, {0}, {0}", "format");
	}
	std::cout << c << std::endl;
}

void Test3()
{
	auto buffer = new char[40960];
	auto c = 0;
	auto t = clock();
	while (t + 1000 > clock())
	{
		++c;
		snprintf(buffer, 40960, "%d, %d, %d", 999999, 999999, 999999);
	}
	std::cout << c << std::endl;

	c = 0;
	t = clock();
	while (t + 1000 > clock())
	{
		++c;
		SFormat("{0}, {0}, {0}", 999999);
	}
	std::cout << c << std::endl;
}

void Test4()
{
	auto buffer = new char[40960];
	auto c = 0;
	auto t = clock();
	while (t + 1000 > clock())
	{
		++c;
		snprintf(buffer, 40960, "%lf, %lf, %lf", 999999.0, 999999.0, 999999.0);
	}
	std::cout << c << std::endl;

	c = 0;
	t = clock();
	while (t + 1000 > clock())
	{
		++c;
		SFormat("{0}, {0}, {0}", 999999.0);
	}
	std::cout << c << std::endl;
}

int main()
{
	std::cout << "---test1---" << std::endl;
	Test1();
	std::cout << "---test2---" << std::endl;
	Test2();
	std::cout << "---test3---" << std::endl;
	Test3();
	std::cout << "---test4---" << std::endl;
	Test4();
	return 0;
}