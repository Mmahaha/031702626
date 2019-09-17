#include <fstream>
#include <string>
#include <iostream>
#include <regex>
#include <codecvt>
using namespace std;

string find_name(string add)
{
	string name;
	name.append(add, 0, add.find(','));

	return name;
}

string find_number(string add)
{
	smatch result;
	string num;
	regex reg(".*(\\d{11}).*");
	if (regex_match(add, result, reg))
		return result[1];
}

string delete_num(string add, string number)		//返回删除号码后的地址
{
	add.erase(add.size() - 1, 1);
	regex pattern(number);
	return regex_replace(add, pattern, "");
}

int main()
{
	ifstream in("1.txt");
	ofstream out("2.txt");
	string address;
	string name;
	string number;
	char level;

	if (in) // 有该文件
	{
		out << '[';
		while (getline(in, address)) // line中不包括每行的换行符
		{
			level = address[0];
			address.erase(0, 2);
			name = find_name(address);
			//out << name << ':';
			address.erase(0, address.find(',') + 1);	//删除名字
			number = find_number(address);
			//out << number << endl;
			address = delete_num(address, number);	//此时字符串只剩下地址

			if (level == '1')
			{
				regex reg1("(.*省)(.*市)(.*区|.*县)(.*街道|.*镇|.*乡)?(.*路)?.*");
				smatch result1;
				out << '{' << "\"姓名\":"  << "\"" << name << "\"," << endl;
				out << "\"手机\":" << "\"" << number << "\"," << endl;
				out << "\"地址\":" << '[';
				if (regex_match(address, result1, reg1))
				{
					for (int i = 1; i < result1.size(); i++)
					{
						out << '"' << result1[i] << '"';
						if (i != (result1.size() - 1))	out << ',';
					}
					out << "]}," << endl;
				}
			}

			else
			{
				regex reg2("(.*省)(.*市)(.*区|.*县)(.*街道|.*镇|.*乡)?(.*路)?(.*号)?(.*)");
				smatch result2;
				out << '{' << "\"姓名\":" << "\"" << name << "\"," << endl;
				out << "\"手机\":" << "\"" << number << "\"," << endl;
				out << "\"地址\":" << '[';
				if (regex_match(address, result2, reg2))
				{
					for (int i = 1; i < result2.size(); i++)
					{
						out << '"' << result2[i] << '"';
						if (i != (result2.size() - 1))	out << ',';
					}
					out << "]}," << endl;
				}
			}
		}
	}
	else
	{
		cout << "no such file" << endl;
	}

	return 0;
}