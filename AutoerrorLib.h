#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>

//using namespace std;

namespace autoerrorlib
{
	struct data;

	bool checkargs(std::vector <std::string> args1, std::vector <std::string> args2, unsigned i1, unsigned i2);

	std::vector <std::string> stringparser(std::string str, unsigned beg, unsigned end);

	std::vector <std::string> defparser(std::string str, std::vector <std::pair <char, char>> c, unsigned beg, unsigned end, unsigned index);

	int gstr(std::string& name, std::vector <std::string>& arg, std::vector <std::string> strvec, const std::string func, unsigned i, unsigned frbck);

	int goodstring(std::string& name, std::vector <std::string>& arg, std::string& erword, std::vector <std::string> strvec, const std::string func, unsigned i);

	std::vector <std::string> wordparser(std::string str);

	std::vector <std::string> spaceparser(std::string str, unsigned beg, unsigned end);

	std::vector <struct data> erhandlerparser(std::string name);

	int autoerror(std::string from, std::string to, std::string infofile);

}
