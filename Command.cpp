#include "Command.h"
#include<iostream>
#include<fstream>

using namespace std;

/**
* Default Constructor
*/
Command::Command(void)
{
	//string jsonStr = "{\"entries\": {\"lilei\" : {\"age\": 27,\"mobile\" : \"13700000000\",\"address\" : \"Earth somewhere\"}, \"hanmeimei\" : {\"age\": 26,\"mobile\" : \"13700000001\",\"address\" : \"Earth somewhere else\"}}}";
	//m_jsonList = new JSONList(jsonStr);
	
	m_shellName = "AB";

	string jsonStr = ReadFile();

	m_jsonList = new JSONList(jsonStr);
}

/**
* Constructor
* @param shellName: the name of the shell
*/
Command::Command(string shellName)
{
	m_shellName = shellName;

	string jsonStr = ReadFile();

	m_jsonList = new JSONList(jsonStr);
}

Command::~Command(void)
{
}

/**
* Run the command application
*/
void Command::Run(void)
{
	bool quitFlag = false;
	while (!quitFlag)
	{
		DisplayShell();
		int com = 0;
		com = ReadString();

		switch (com)
		{
		case 0:
			cout << "Command Wrong!\n\n";
			GetHelp();
			break;
		case 1:
			m_jsonList->getls();
			break;
		case 2:
			m_jsonList->getcd(m_secondCmd);
			break;
		case 3:
			m_jsonList->getcat(m_secondCmd);
			break;
		case 4:
			m_jsonList->getadd();
			break;
		case 5:
			m_jsonList->getremove();
			break;
		case 6:
			GetHelp();
			break;
		case 7:
			if (m_jsonList->GetDirty())
			{
				WriteFile();
			}
			quitFlag = true;
			break;
		default:
			break;
		}
	}
}

/**
* Display the shell name
*/
void Command::DisplayShell()
{
	cout << m_shellName << ">";
}

/**
* Read a command line from console
*/
string Command::GetFromConsole()
{
	string line = "";
	getline(cin,line);
	return line;
}

/**
* Analyze the command line
* @return com: command type, 0-7
*/
int Command::ReadString()
{
	int com = 0;
	string line = "";

	line = GetFromConsole();

	// delete the space in front of the command line
	int start = 0;
	while (line[start] == ' ')
	{
		start++;
	}
	line = line.substr(start);

	if (line.empty())
	{
		return com;
	}

	int i = line.find(" ");
	if (i == -1)// only have the first command
	{
		m_firstCmd = line;
		m_secondCmd = "";
	}else
	{
		m_firstCmd = line.substr(0,i);
		m_secondCmd = line.substr(i+1);

		// delete the space in front of the second command 
		int j = 0;
		while (m_secondCmd[j] == ' ')
		{
			j++;
		}
		m_secondCmd = '\"' + m_secondCmd.substr(j) + '\"';
	}
	
	if ("ls" == m_firstCmd && m_secondCmd.empty())
	{
		com = 1;
	}else if ("cd" == m_firstCmd && !m_secondCmd.empty())
	{
		com = 2;
	}else if ("cat" == m_firstCmd && !m_secondCmd.empty())
	{
		com = 3;
	}else if ("add" == m_firstCmd && m_secondCmd.empty())
	{
		com = 4;
	}else if ("remove" == m_firstCmd && m_secondCmd.empty())
	{
		com = 5;
	}else if ("!help" == m_firstCmd && m_secondCmd.empty())
	{
		com = 6;
	}else if ("!quit" == m_firstCmd && m_secondCmd.empty())
	{
		com = 7;
	}

	return com;
}

/**
* Read data from file "data.txt"
* @return jsonStr: the data string saved int file "data.txt"
*/
string Command::ReadFile()
{
	ifstream inFile;
	inFile.open("data.txt");
	if (!inFile)
	{
		cout << "File open error, data load failure!\n";
		exit(0);
	}
	
	string jsonStr;
	getline(inFile, jsonStr);
	inFile.close();

	return jsonStr;
}

/**
* Write data into file "data.txt" when quit from application.
*/
void Command::WriteFile()
{
	ofstream outFile("data.txt");
	if (!outFile)
	{
		cout << "File open error, data save failure!\n";
		exit(0);
	}
	outFile << m_jsonList->GetValue(m_jsonList->GetRootNode());
	outFile.close();
}


/**
* Get help message for the command application
*/
void Command::GetHelp()
{
	string sb = "Help!\n";
	sb.append("ls           :command to list the items in current position\n");
	sb.append("cd [entry]   :command to go to the entry like go to a directory\n");
	sb.append("cat [key]    :command to display th item data\n");
	sb.append("add          :command to add new address entry to JSON\n");
	sb.append("remove [key] :command to remove one or more address entries\n");
	sb.append("!help        :commadn to get help\n");
	sb.append("!quit        :command to quit from the application\n");
	cout << sb;
}