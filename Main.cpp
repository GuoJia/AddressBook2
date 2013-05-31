/**Copyright (c) 2013 Jian Luo (romain_cool@163.com)
* Main.cpp
* The entrance of the command application
*/
#include"JSONList.h"
#include"Command.h"

using namespace std;

int main(int argc, char **argv)
{
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
