/**Copyright (c) 2013 Jian Luo (romain_cool@163.com)
* JSONList.cpp
* The implementation of JSONList class: implement all the functions in JSONList class
*/
#include "JSONList.h"
#include<iostream>
#include<stdlib.h>

using namespace std;

/**
* Default Constructor
*/
JSONList::JSONList(void)
{
	m_pRootNode = new JSONNode();
	m_pRootNode->key = "root";
	m_pRootNode->pNext = NULL;
	m_pRootNode->pPrev = NULL;
	m_pRootNode->pSub = NULL;
	m_pCurrNode = NULL;

}

/**
* Constructor
* @param jsonStr: a complete JSON data structure for address book
*/
JSONList::JSONList(string jsonStr)
{
	jsonStr = DeleteChar(jsonStr,' ');
	if (!isLegalOuter(jsonStr))
	{
		cout << "JSON data structure wrong, constructor failure!\n";
		exit(0);
	}

	m_dirty = false;
	m_pRootNode = new JSONNode();
	m_pRootNode->key = "root";
	m_pRootNode->pPrev = NULL;
	m_pRootNode->pNext = NULL;
	m_pRootNode->pSub = NULL;

	int i = jsonStr.find("{");
	int j = jsonStr.find(":");
	string key = jsonStr.substr(i+1,j-i-1);
	if (key.empty())
	{
		exit(0);
	}
	int k = jsonStr.rfind("}",jsonStr.size()-2);
	jsonStr = jsonStr.substr(j+1,k-j);

	JSONNode *node = new JSONNode();
	node->key = key;
	if (jsonStr.empty())
	{
		node->value = "{}";
	}else
	{
		node->value = "{}";//jsonStr;
	}
	
	m_pCurrNode = node;
	m_pRootNode->pSub = node;
	node->pPrev = m_pRootNode;
	node->pNext = NULL;
	node->pSub = NULL;

	JSONNode * pFlag = m_pCurrNode;
	int flag = 1;
	while (!jsonStr.empty() && jsonStr != "{}")
	{
		i = jsonStr.find("\"");
		j = jsonStr.find(":");
		k = jsonStr.find("}");
		key = jsonStr.substr(i,j-i);
		string value = jsonStr.substr(j+1,k-j);
		jsonStr  = jsonStr.substr(k+1);

		if (jsonStr == "}")
		{
			jsonStr = "";
		}

		JSONNode *node = new JSONNode();
		node->key = key;
		node->value = "{}";
		node->pNext = NULL;
		if (flag == 1)
		{
			pFlag->pSub = node;
		}else
		{
			pFlag->pNext = node;
		}
		flag++;
		node->pPrev = pFlag;
		pFlag = node;

		int subFlag = 1;
		JSONNode *subPFlag = node;
		while (!value.empty())
		{
			int ii = value.find("\"");
			int jj = value.find(":");
			int kk = value.find(",");
			string subKey = value.substr(ii,jj-ii);
			string subValue = value.substr(jj+1,kk-jj-1);
			if (kk == -1)
			{
				subValue = value.substr(jj+1,value.size()-jj-2);
				value = "";
			}
			value = value.substr(kk+1);

			JSONNode *subNode = new JSONNode();
			subNode->key = subKey;
			subNode->value = subValue;
			subNode->pNext = NULL;
			subNode->pSub = NULL;
			if (subFlag == 1)
			{
				subPFlag->pSub = subNode;
			}else
			{
				subPFlag->pNext = subNode;
			}
			subFlag++;
			subNode->pPrev = subPFlag;
			subPFlag = subNode;
		}
		
	}
}

/**
* Default Destructor
*/
JSONList::~JSONList(void)
{
	DeleteNode(&m_pRootNode);
	m_pRootNode = NULL;
}

/**
*
*/
void JSONList::DeleteNode(JSONNode **node)
{
	if (*node == NULL)
	{
		return;
	}

	if ((*node)->pSub == NULL && (*node)->pNext == NULL)
	{
		JSONNode *pTempNode = (*node)->pPrev;
		
		delete (*node);
		(*node) = NULL;

		return;
	}

	DeleteNode(&(*node)->pNext);
	(*node)->pNext = NULL;

	DeleteNode(&(*node)->pSub);
	(*node)->pSub = NULL;
	
	DeleteNode(&(*node));
	(*node) = NULL;
}

/**
* List all keys in current directory
*/
void JSONList::getls()
{
	if (m_pCurrNode == NULL)
	{
		return;
	}

	JSONNode *pTemp = m_pCurrNode;
	while (pTemp != NULL)
	{
		cout << DeleteChar(pTemp->key, '\"') << " ";
		pTemp = pTemp->pNext;
	}
	cout << endl;
}

/**
* Go to a entry like go to a directory
* @param key: the key of a entry
*/
void JSONList::getcd(string key)
{
	JSONNode *pTempNode = m_pRootNode->pSub;
	while (pTempNode != NULL)
	{
		if (pTempNode->key == key)
		{
			if (pTempNode->pSub != NULL || m_pRootNode->pSub->pSub == NULL)
			{
				m_pCurrNode = pTempNode->pSub;
				return;
			}else if (m_pRootNode->pSub->pSub == NULL)
			{
				m_pCurrNode = NULL;
				cout << "NULL in directory, !help\n";
				return;
			}
		}

		if (pTempNode->pNext != NULL)
		{
			pTempNode = pTempNode->pNext;
		}else
		{
			pTempNode = pTempNode->pSub;
		}
	}
	
}

/**
* Display the value of the key
* @param key: the key
*/
void JSONList::getcat(string key)
{
	JSONNode *pTempNode = m_pCurrNode;
	while (pTempNode != NULL)
	{
		if (pTempNode->key == key)
		{
			cout << key << ": " << GetValue(pTempNode) << endl;
		}
		pTempNode = pTempNode->pNext;
	}
}

/**
* Add command: add a node with a given key and a given value
* Enter key and value with a given format
*/
void JSONList::getadd()
{
	if (m_pCurrNode != NULL && (m_pCurrNode->pPrev->pPrev == NULL || m_pCurrNode->pPrev->pPrev->key != "root"))
	{
		cout << "Go to \"entries\" before add!\n";
		return;
	}
	string key;
	string content;
	cout << "key: ";
	getline(cin, key);
	key = '\"' + DeleteChar(key, ' ') + '\"';

	if (isKeyExist(key))
	{
		cout << key << " exist in database, enter a different one, try again!\n";
		return;
	}
	
	cout << "value: ";
	getline(cin, content);
	content = DeleteChar(content, ' ');

	if (!isLegalInner(key + ':' + content))
	{
		cout << "Enter wrong value!\n";
		cout << "Format example:\n  key: lilei\n  value: {\"age\":28,\"mobile\":\"13700000000\",\"address\":\"China\"}\n";
		return;
	}

	JSONNode *node = new JSONNode();
	node->key = key;
	node->value = content;
	node->pNext = NULL;
	node->pSub = NULL;

	JSONNode *pTempNode;
	if (m_pCurrNode == NULL)
	{
		pTempNode = m_pRootNode->pSub;
	}else
	{
		pTempNode = m_pCurrNode;
	}
	 
	if (m_pRootNode->pSub->pSub != NULL)
	{
		while (pTempNode->pNext != NULL)
		{
			pTempNode = pTempNode->pNext;
		}
		node->pPrev = pTempNode;
		pTempNode->pNext = node;
	}else
	{
		node->pPrev = pTempNode;
		pTempNode->pSub = node;
	}
	
	content = DeleteChar(content, ' ');
	int subFlag = 1;
	JSONNode *subPFlag = node;
	while (!content.empty())
	{
		int ii = content.find("\"");
		int jj = content.find(":");
		int kk = content.find(",");
		string subKey = content.substr(ii,jj-ii);
		string subValue = content.substr(jj+1,kk-jj-1);
		if (kk == -1)
		{
			subValue = content.substr(jj+1,content.size()-jj-2);
			content = "";
		}
		content = content.substr(kk+1);
		JSONNode *subNode = new JSONNode();
		subNode->key = subKey;
		subNode->value = subValue;
		subNode->pNext = NULL;
		subNode->pSub = NULL;
		if (subFlag == 1)
		{
			subPFlag->pSub = subNode;
		}else
		{
			subPFlag->pNext = subNode;
		}
		subFlag++;
		subNode->pPrev = subPFlag;
		subPFlag = subNode;
	}
	m_pCurrNode = m_pRootNode->pSub->pSub;

	m_dirty = true;
}

/**
* Delete command: delete a node with a given key
* Enter a key which exists in database
*/
void JSONList::getremove()
{
	if (m_pCurrNode->pPrev->pPrev == NULL || m_pCurrNode->pPrev->pPrev->key != "root")
	{
		cout << "Go to \"entries\" before remove!\n";
		return;
	}
	cout << "Please give the key: ";
	
	string key;
	getline(cin, key);
	key = '\"' + key + '\"';
	JSONNode *pTempNode = m_pCurrNode;
	while (pTempNode != NULL)
	{
		if (pTempNode->key == key)
		{
			break;
		}
		pTempNode = pTempNode->pNext;
	}

	if (pTempNode == NULL)
	{
		return;
	}

	JSONNode *pTempPrev = pTempNode->pPrev;

	if (pTempNode->pPrev->pPrev->key == "root")
	{
		pTempPrev->pSub = pTempNode->pNext;

		m_pCurrNode = m_pCurrNode->pNext;
		if (m_pCurrNode != NULL)
		{
			m_pCurrNode->pPrev = m_pRootNode->pSub;
		}
		m_pRootNode->pSub->pSub = m_pCurrNode;
	}else
	{
		pTempPrev->pNext = pTempNode->pNext;
	}

	DeleteNode(&(pTempNode->pSub));
	delete (pTempNode);
	
	m_dirty = true;
}

/**
* Get the value of a JSONNode recursively
* @return: the value of a given node
*/
string JSONList::GetValue(JSONNode *node)
{
	if (node->pSub == NULL)
	{
		return (node->value);
	}

	string value = "{}";
	int len;

	JSONNode *pTempNode = node->pSub;
	while (pTempNode != NULL)
	{
		len = value.size();
		value.insert(len-1,pTempNode->key);

		len = value.size();
		value.insert(len-1,":");

		len = value.size();
		value.insert(len-1,GetValue(pTempNode));

		pTempNode = pTempNode->pNext;

		if (pTempNode != NULL)
		{
			len = value.size();
			value.insert(len-1,",");
		}
	}

	return value;
}

/**
* Delete a given char from a string
* @param str
* @param ch
*/
string JSONList::DeleteChar(string str, char ch)
{
	int count = 0;
	int len = str.size();
	for (int i = 0; i < len; i++)
	{
		if (str[i] == ch)
		{
			count++;
		}
	}
	int *arr = new int[count];

	int j = 0;
	for (int i = 0; i < len; i++)
	{
		if (str[i] == ch)
		{
			arr[j++] = i;
			if (j == count)
			{
				break;
			}	
		}
	}

	for (int i = count-1; i >= 0; i--)
	{
		str.erase(arr[i],1);
	}

	delete []arr;

	return str;
}

/**
* Judge the format of the outer of a JSON data structure
* Format: {"entries": {"xx": {}, "yy": {}}}
* @param content
*/
bool JSONList::isLegalOuter(string content)
{
	int len = content.size();
	if (content[0] != '{' || content[len-1] != '}')
	{
		return false;
	}

	content = content.substr(1,len-2);
	len = content.size();
	int i = content.find(':');
	if (i == -1 || i == len-1)
	{
		return false;
	}

	string key = content.substr(0,i);
	if (key != "\"entries\"" || content[i+1] != '{' || content[len-1] != '}')
	{
		return false;
	}

	content = content.substr(i+2,len-i-3);
	len = content.size();
	if (content.empty())
	{
		return true;
	}

	i = content.find('}');
	if (i == -1)
	{
		return false;
	}

	while (i < len-1)
	{
		if (content[i+1] != ',')
		{
			return false;
		}

		if (!isLegalInner(content.substr(0,i+1)))
		{
			return false;
		}
		content = content.substr(i+2);
		len = content.size();

		i = content.find('}');
		if (i == -1)
		{
			return false;
		}
	}

	if (!isLegalInner(content))
	{
		return false;
	}

	return true;
}

/**
* Judge the format of the inner of a JSON data structure
* Format: lilei: {\"age\":28,\"mobile\":\"13700000000\",\"address\":\"China\"}
* @param content
*/
bool JSONList::isLegalInner(string content)
{
	int len = content.size();
	int i = content.find(':');
	if (i == -1 || i == len-1 || content[i+1] != '{' || content[len-1] != '}')
	{
		return false;
	}
	
	string key = content.substr(0,i);
	if (key[0] != '\"' || key[key.size()-1] != '\"' || key.substr(1,key.size()-2).empty())
	{
		return false;
	}

	content = content.substr(i+2,len-i-3);
	len = content.size();
	i = content.find(',');
	if (i == -1)
	{
		return false;
	}
	string str = content.substr(0,i);
	int j = str.find(':');
	if (j == -1 || str.substr(0,j) != "\"age\"" || !isNumber(str.substr(j+1)) )
	{
		return false;
	}

	content = content.substr(i+1);
	len = content.size();
	i = content.find(',');
	if (i == -1)
	{
		return false;
	}
	str = content.substr(0,i);
	j = str.find(':');
	if (j == -1 || str.substr(0,j) != "\"mobile\"" || !isMobile(str.substr(j+1)) )
	{
		return false;
	}

	content = content.substr(i+1);
	len = content.size();
	
	str = content;
	j = str.find(':');
	if (j == -1 || str.substr(0,j) != "\"address\"" || !isAddress(str.substr(j+1)) )
	{
		return false;
	}

	return true;
}

/**
* Judge the format of a number
* @param str
*/
bool JSONList::isNumber(string str)
{
	int len = str.size();
	for (int i = 0; i < len; i++)
	{
		if (str[i] < '0' && str[i] > '9')
		{
			return false;
		}
	}

	if (str[0] == '0')
	{
		return false;
	}

	return true;
}

/**
* Judge the format of a mobile number
* @param str
*/
bool JSONList::isMobile(string str)
{
	int len = str.size();
	if (len != 13)
	{
		return false;
	}

	if (str[0] != '\"' || str[len-1] != '\"')
	{
		return false;
	}

	str = str.substr(1,len-2);

	return isNumber(str);
}

/**
* Judge the format of an address
* @param str
*/
bool JSONList::isAddress(string str)
{
	int len = str.size();
	if (str[0] != '\"' || str[len-1] != '\"' || str.substr(1,len-2).empty())
	{
		return false;
	}
	return true;
}

/**
* Find a node with a given key
* @param key
*/
bool JSONList::isKeyExist(string key)
{
	JSONNode *pTempNode = m_pCurrNode;
	while (pTempNode !=NULL)
	{
		if (pTempNode->key == key)
		{
			return true;
		}
		pTempNode = pTempNode->pNext;
	}
	return false;
}

/**
* Get the root node
*/
JSONNode* JSONList::GetRootNode()
{
	return m_pRootNode;
}

/**
* Get the current node
*/
JSONNode* JSONList::GetCurrNode()
{
	return m_pCurrNode;
}

/**
* Get the dirty flag
*/
bool JSONList::GetDirty()
{
	return m_dirty;
}
