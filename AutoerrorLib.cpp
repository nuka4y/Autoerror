// AutoerrorLib.cpp : Определяет функции для статической библиотеки.
//
//#include "framework.h"

#include "AutoerrorLib.h"

namespace autoerrorlib
{
	struct data
	{
		std::string name;
		std::string erword;
		std::vector <std::string> args;
		std::string text;
	};

	bool checkargs(std::vector <std::string> args1, std::vector <std::string> args2, unsigned i1 = 0, unsigned i2 = 0)
	{
		using namespace autoerrorlib;
		unsigned len1 = args1.size() - i1;
		unsigned len2 = args2.size() - i2;
		if (len1 != len2)
		{
			return false;
		}
		for (unsigned i = 0; i < len1; i++)
		{
			if (args1[i + i1] != args2[i + i2])
			{
				return false;
			}
		}
		return true;
	}

	std::vector <std::string> stringparser(std::string str, unsigned beg = 0, unsigned end = 0)
	{
		using namespace autoerrorlib;
		std::string s;
		std::vector <std::string> pars;
		if (end > str.length())
		{
			std::cout << "end > strlen" << std::endl;
			return pars;
		}
		unsigned len = str.length() - end;
		for (unsigned i = beg; i < len; i++)
		{
			s += str[i];
			if (s[0] == ' ' || s[0] == '\n')
			{
				s.clear();
				continue;
			}
			if ((s[0] >= 'a' && s[0] <= 'z') || (s[0] >= 'A' && s[0] <= 'Z') || (s[0] >= '0' && s[0] <= '9') || s[0] == '_')
			{
				for (++i; i < len; i++)
				{
					if (!((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= '0' && str[i] <= '9') || str[i] == '_'))
					{
						break;
					}
					s += str[i];
				}
				i--;
			}
			pars.push_back(s);
			s.clear();
		}
		return pars;
	}

	std::vector <std::string> defparser(std::string str, std::vector <std::pair <char, char>> c, unsigned beg = 0, unsigned end = 0, unsigned index = 0)
	{
		using namespace autoerrorlib;
		std::string s;
		std::vector <std::string> pars;
		char c1 = c[index].first;
		char c2 = c[index].second;
		if (end > str.length())
		{
			std::cout << "end > strlen" << std::endl;
			return pars;
		}
		unsigned len = str.length() - end;
		for (unsigned i = beg; i < len; i++)
		{
			if (str[i] == c1)
			{
				s += str[i];
				for (++i; i < len; i++)
				{
					s += str[i];
					if (str[i] == c2)
					{
						pars.push_back(s);
						s.clear();
						index++;
						if (!(index >= c.size()))
						{
							c1 = c[index].first;
							c2 = c[index].second;
						}
						break;
					}
				}
				i--;
			}
			if (index >= c.size())
			{
				break;
			}
		}
		return pars;
	}

	int gstr(std::string& name, std::vector <std::string>& arg, std::vector <std::string> strvec, const std::string func, unsigned i = 0, unsigned frbck = 0)
	{
		using namespace autoerrorlib;
		unsigned len = strvec.size() - frbck;
		std::string s = "";
		int k = 0;
		if (len > (i + 2))
		{
			if (strvec[i] == func && strvec[i + 1] == "(")
			{
				name = strvec[i];
				k = 1;
				for (i += 2; i < len; i++)
				{
					if (strvec[i] == "(" || strvec[i] == "[")
					{
						k++;
					}
					if (strvec[i] == ")" || strvec[i] == "]")
					{
						k--;
						if (k == 0)
						{
							arg.push_back(s);
							s.clear();
							break;
						}
					}
					if (k > 1)
					{
						s += strvec[i];
					}
					if (k == 1)
					{
						if (strvec[i] == ",")
						{
							arg.push_back(s);
							s.clear();
							continue;
						}
						s += strvec[i];
					}
				}
			}
			else
			{
				return 1;
			}
			if (k != 0)
			{
				return 2;
			}
		}
		else
		{
			return 3;
		}

		std::cout << "gstr done" << std::endl;
		return 0;
	}

	int goodstring(std::string& name, std::vector <std::string>& arg, std::string& erword, std::vector <std::string> strvec, const std::string func, unsigned i = 0)
	{
		using namespace autoerrorlib;
		erword.clear();
		name.clear();
		unsigned len = strvec.size();
		std::string s = "";
		int k = 0;
		bool fl = false;
		int e = 0;

		if (len > (i + 2))
		{
			if (strvec[i] == func && strvec[i + 1] == "(")
			{
				e = gstr(name, arg, strvec, func);
				return e;
			}
			else
			{
				for (unsigned j = i; j < len; j++)
				{
					if (strvec[j] == func)        //strvec[j+1]=="("
					{                           //before func no ( or )
						fl = true;                //before func "="
						break;
					}
					if (strvec[j] == "(" && fl == false)
					{
						break;
					}
				}
				if (fl == false)
				{
					return 4;
				}
				for (unsigned j = i; j < len; j++)
				{
					if (strvec[j] == "=")
					{
						erword = s;
						s.clear();
						j++;
						e = gstr(name, arg, strvec, func, j);
						return e;
					}
					s += strvec[j];
				}
				return 5;
			}
		}
		else
		{
			return 6;
		}
	}

	std::vector <std::string> wordparser(std::string str)
	{
		using namespace autoerrorlib;
		std::string s = "";
		std::vector <std::string> pars;
		unsigned len = str.length();
		for (unsigned i = 0; i < len; i++)
		{
			if ((str[i] == ' ' || str[i] == '\n'/* || str[i] == '[' || str[i] == ']' || str[i] == '@'*/) && !s.empty())
			{
				pars.push_back(s);
				s.clear();
			}
			s += str[i];
			if ((s[0] == ' ' || s[0] == '\n') || (i + 1 == len))
			{
				pars.push_back(s);
				s.clear();
				continue;
			}
		}
		return pars;
	}

	std::vector <std::string> spaceparser(std::string str, unsigned beg = 0, unsigned end = 0)
	{
		using namespace autoerrorlib;
		std::string s;
		std::vector <std::string> pars;
		if (end > str.length())
		{
			std::cout << "end > strlen" << std::endl;
			return pars;
		}
		unsigned len = str.length() - end;
		for (unsigned i = beg; i < len; i++)
		{
			s += str[i];
			if (s[0] == ' ' || s[0] == '\n')
			{
				pars.push_back(s);
				s.clear();
				continue;
			}
			if ((s[0] >= 'a' && s[0] <= 'z') || (s[0] >= 'A' && s[0] <= 'Z') || (s[0] >= '0' && s[0] <= '9') || s[0] == '_')
			{
				for (++i; i < len; i++)
				{
					if (!((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= '0' && str[i] <= '9') || str[i] == '_'))
					{
						break;
					}
					s += str[i];
				}
				i--;
			}
			pars.push_back(s);
			s.clear();
		}
		return pars;
	}

	std::vector <struct data> erhandlerparser(std::string name)
	{
		using namespace autoerrorlib;
		std::cout << std::endl << "ERHANDLER START" << std::endl;
		std::ifstream file(name);
		if (!file.is_open())
		{
			std::cout << "file " << name << " not opened" << std::endl;
			return {};
		}
		std::string s;
		std::vector <std::string> vec;
		std::vector <std::string> strvec;
		struct data temp;
		int error = 0;
		std::vector <struct data> funcprot;

		while (!file.eof())
		{
			std::getline(file, s);
			if (s[0] == '[')
			{
				vec = defparser(s, { {'[', ']'}, {'@', '@'} });
				s.clear();
				if (!vec.empty())
				{
					if (vec[0][0] != '[')
					{
						std::cout << "vec[0][0] != '['" << std::endl;
						std::cout << "ERHANDLER STOP" << std::endl;
						return {};
					}
					strvec = stringparser(vec[0], 1, 1);
					if (!((strvec[0][0] >= 'a' && strvec[0][0] <= 'z') || (strvec[0][0] >= 'A' && strvec[0][0] <= 'Z') || (strvec[0][0] >= '0' && strvec[0][0] <= '9') || strvec[0][0] == '_'))
					{
						std::cout << "wrong parsing" << std::endl;
						std::cout << "ERHANDLER STOP" << std::endl;
						return {};
					}
					temp.name = strvec[0];
					std::cout << "name: " << temp.name << std::endl;
					if (strvec[1] != "(")
					{
						std::cout << "not ( after name " << strvec[0] << std::endl;
						std::cout << "ERHANDLER STOP" << std::endl;
						return {};
					}
					for (unsigned i = 2; i < strvec.size(); i++)
					{
						if (strvec[i] == ")")
						{
							temp.args.push_back(s);
							std::cout << "got " << "|" << s << "|" << std::endl;
							s.clear();
							break;
						}
						if (strvec[i] == ",")
						{
							temp.args.push_back(s);
							std::cout << "got " << "|" << s << "|" << std::endl;
							s.clear();
						}
						else
						{
							s += strvec[i];
						}
					}
					if (vec.size() > 1)
					{
						if (vec[1][0] == '@')
						{
							strvec = stringparser(vec[1], 1, 1);
							temp.erword = strvec[0];
						}
					}
					funcprot.push_back(temp);
					temp.name.clear();
					temp.args.clear();
					temp.text.clear();
					temp.erword.clear();
				}

			}
			else
			{
				if (funcprot.empty())
				{
					std::cout << "extra text: " << s << std::endl;
					continue;
				}
				funcprot.back().text += s;
				funcprot.back().text += "\n";
			}
		}

		file.close();
		std::cout << "ERHANDLER STOP" << std::endl;
		return funcprot;
	}

	int autoerror(std::string from, std::string to, std::string infofile)
	{
		using namespace autoerrorlib;
		std::ifstream fin;
		std::string curin = from;
		fin.open(curin);
		if (!fin.is_open())
		{
			std::cout << "fin not opened" << std::endl;
			return 1;
		}
		std::ofstream fout;
		std::string curout = to;
		fout.open(curout);
		if (!fout.is_open())
		{
			std::cout << "fout not opened" << std::endl;
			return 2;
		}

		std::string func;
		std::string s;
		std::string erword;
		int flag = 0;
		int len;
		std::vector <std::string> vec;
		std::vector <std::string> arg;
		std::vector <struct data> funcinfo = erhandlerparser(infofile);
		std::string erhandle;

		std::string funcname;
		std::string fnderword;

		std::string temp = "C:\\Users\\Master\\Documents\\temp.txt";

		std::cout << std::endl << "INSERTING START" << std::endl;
		for (auto var : funcinfo)
		{
			std::cout << std::endl << "ITERATION" << std::endl;
			erhandle = var.text;
			func = var.name;
			erword = var.erword;

			std::cout << "func: " << func << std::endl;
			std::cout << "erword: " << erword << std::endl;
			unsigned numofargs = 0;
			for (unsigned i = 0; i < var.args.size(); i++)
			{
				if (!var.args[i].empty())
				{
					numofargs++;
				}
			}
			std::cout << "NUMOFARGS: " << numofargs << std::endl;

			while (!fin.eof())
			{
				
				std::getline(fin, s);
				
				vec = stringparser(s);

				flag = goodstring(funcname, arg, fnderword, vec, func);
				std::cout << "for: |" << s << "| flag = " << flag << std::endl;
				std::cout << "FUNCNAME: " << funcname << std::endl;
				std::cout << "FNDERWORD: " << fnderword << std::endl;
				for (auto argum : arg)
				{
					std::cout << "ARGUM: " << argum << std::endl;
				}
				if (flag == 0)
				{
					len = arg.size();
					unsigned count = 0;
					for (int i = 0; i < len; i++)
					{
						if (!arg[i].empty())
						{
							count++;
						}
					}
					std::cout << "COUNT: " << count << std::endl;
					if (count == numofargs)
					{
						vec = spaceparser(erhandle);
						for (auto el : vec)
						{
							if (el == erword)
							{
								if (!fnderword.empty())
								{
									fout << fnderword;
								}
								else
								{
									fout << erword;
								}
								continue;
							}
							unsigned i;
							for (i = 0; i < var.args.size(); i++)
							{
								if (el == var.args[i])
								{
									fout << arg[i];
									break;
								}
							}
							if (i < var.args.size())
							{
								continue;
							}
							fout << el;
						}
					}
					else
					{
						fout << s << '\n';
					}
				}
				else
				{
					fout << s << '\n';
				}
				arg.clear();
				s.clear();
			}
			if (curin == from && curout == to)
			{
				curin = to;
				curout = temp;
				fin.close();
				fout.close();
				fin.open(curin);
				if (!fin.is_open())
				{
					std::cout << "fin " << curin << " not opened" << std::endl;
					return 3;
				}
				fout.open(curout);
				if (!fout.is_open())
				{
					std::cout << "fout " << curout << " not opened" << std::endl;
					return 4;
				}
				continue;
			}
			if (curin == to && curout == temp)
			{
				curin = temp;
				curout = to;
				fin.close();
				fout.close();
				fin.open(curin);
				if (!fin.is_open())
				{
					std::cout << "fin " << curin << " not opened" << std::endl;
					return 5;
				}
				fout.open(curout);
				if (!fout.is_open())
				{
					std::cout << "fout " << curout << " not opened" << std::endl;
					return 6;
				}
				continue;
			}
			if (curin == temp && curout == to)
			{
				curin = to;
				curout = temp;
				fin.close();
				fout.close();
				fin.open(curin);
				if (!fin.is_open())
				{
					std::cout << "fin " << curin << " not opened" << std::endl;
					return 7;
				}
				fout.open(curout);
				if (!fout.is_open())
				{
					std::cout << "fout " << curout << " not opened" << std::endl;
					return 8;
				}
				continue;
			}
		}
		std::cout << "INSERTING END" << std::endl << std::endl;

		int count = 0;
		while (!fin.eof())
		{
			std::getline(fin, s);
			s += '\n';
			vec = spaceparser(s);
			for (unsigned i = 0; i < vec.size(); i++)
			{
				if (vec[i] == "^")
				{
					if ((i + 1) < vec.size())
					{
						i++;
						funcname.clear();
						unsigned j = 0;
						for (; j < vec[i].length(); j++)
						{
							if (!(vec[i][j] >= '0' && vec[i][j] <= '9'))
							{
								break;
							}
							funcname += vec[i][j];
						}
						if (!(j < vec[i].length()))
						{
							count = stoi(funcname);
						}
					}
					continue;
				}
				if (vec[i] == "$")
				{
					if ((i + 1) >= vec.size() || ((i + 1) < vec.size() && !((vec[0][0] >= 'a' && vec[0][0] <= 'z') || (vec[0][0] >= 'A' && vec[0][0] <= 'Z') || (vec[0][0] >= '0' && vec[0][0] <= '9') || vec[0][0] == '_')))
					{
						fout << count++;
					}
					continue;
				}
				fout << vec[i];
			}

		}

		if (curin == to && curout == temp)
		{
			curin = temp;
			curout = to;
			fin.close();
			fout.close();
			fin.open(curin);
			if (!fin.is_open())
			{
				std::cout << "fin " << curin << " not opened" << std::endl;
				return 5;
			}
			fout.open(curout);
			if (!fout.is_open())
			{
				std::cout << "fout " << curout << " not opened" << std::endl;
				return 6;
			}

			std::cout << "START TRANSFER" << std::endl;
			std::cout << "curin: " << curin << std::endl;
			std::cout << "curout: " << curout << std::endl;
			while (!fin.eof())
			{
				std::getline(fin, s);
				fout << s << '\n';
			}
			std::cout << "END TRANSFER" << std::endl;
		}
		/*else
		{
			if (curin == temp && curout == to)
			{
				curin = to;
				curout = temp;
				fin.close();
				fout.close();
				fin.open(curin);
				if (!fin.is_open())
				{
					std::cout << "fin " << curin << " not opened" << std::endl;
					return 7;
				}
				fout.open(curout);
				if (!fout.is_open())
				{
					std::cout << "fout " << curout << " not opened" << std::endl;
					return 8;
				}
			}
		}

		/*if (curin == temp && curout == to)
		{
			std::cout << "START TRANSFER" << std::endl;
			std::cout << "curin: " << curin << std::endl;
			std::cout << "curout: " << curout << std::endl;
			while (!fin.eof())
			{
				std::getline(fin, s);
				fout << s << '\n';
			}
			std::cout << "END TRANSFER" << std::endl;
		}*/


		fin.close();
		fout.close();
		return 0;
	}
}


