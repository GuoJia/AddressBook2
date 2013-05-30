#ifndef JSON_LIST
#define JSON_LIST

#include<string>

struct JSONNode
{
	std::string key;
	std::string value;

	JSONNode *pPrev;
	JSONNode *pNext;
	JSONNode *pSub;
};

class JSONList
{
public:
	JSONList(void);
	JSONList(std::string jsonStr);
	~JSONList(void);

	void getls();
	void getcd(std::string key);
	void getcat(std::string key);
	void getadd();
	void getremove();

	std::string DeleteChar(std::string str, char ch);
	//std::string deleteQuote(std::string str);

	bool isFormatLegal(std::string content);
	bool isKeyExist(std::string key);

	bool isLegalOuter(std::string content);
	bool isLegalInner(std::string content);
	bool isNumber(std::string str);
	bool isMobile(std::string str);
	bool isAddress(std::string str);

	std::string GetValue(JSONNode *node);

	JSONNode *GetRootNode();
	JSONNode *GetCurrNode();
	bool GetDirty();

private:
	JSONNode *m_pRootNode;
	JSONNode *m_pCurrNode;
	bool m_dirty;//true if change the the address book
};

#endif
