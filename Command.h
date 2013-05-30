#ifndef COMMAND
#define COMMAND

#include"JSONList.h"

class Command
{
public:
	Command(void);
	Command(std::string shell);
	~Command(void);

	void Run(void);

	std::string GetFromConsole();

	int ReadString();

	std::string ReadFile();

	void WriteFile();

	void DisplayShell();

	void GetHelp();

private:
	JSONList *m_jsonList;
	
	std::string m_firstCmd;
	std::string m_secondCmd;
	std::string m_shellName;
};

#endif

