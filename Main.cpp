#include"JSONList.h"
#include"Command.h"
#include<iostream>

using namespace std;

int main(int argc, char **argv)
{
	string str = "luojian henhao";
	int i = str.find("jianluo");

	string name(argv[0]);
	size_t loc = name.find_last_of("/");
	if (loc == string::npos)
	{
		Command cmd;
		cmd.Run();
	}else
	{
		string temp(name.substr(loc+1,name.size()-loc));
		Command cmd(temp);
		cmd.Run();
	}

	return 0;
}