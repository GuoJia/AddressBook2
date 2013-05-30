#include"JSONList.h"
#include"Command.h"
#include<iostream>

using namespace std;

/*string deleteSpaceOfString(string str)
{
	//string noSpaceStr = "";
	int count = 0;
	int len = str.size();
	for (int i = 0; i < len; i++)
	{
		if (str[i] == ' ')
		{
			count++;
		}
	}
	int *arr = new int[count];

	int j = 0;
	for (int i = 0; i < len; i++)
	{
		if (str[i] == ' ')
		{
			arr[j++] = i;
			if (j == count)
			{
				break;
			}	
		}
	}
	for (int i = 0; i < count; i++)
	{
		cout << arr[i] << endl;
	}
	for (int i = count-1; i >= 0; i--)
	{
		str.erase(arr[i],1);
	}
	delete []arr;
	return str;
}*/

int main(int argc, char **argv)
{
	string str = "luojian henhao";
	int i = str.find("jianluo");

	string name(argv[1]);
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
	

	/*string jsonStr = "{\"entries\": {\"lilei\" : {\"age\": 27,\"mobile\" : \"13700000000\",\"address\" : \"Earth somewhere\"}, \"hanmeimei\" : {\"age\": 26,\"mobile\" : \"13700000001\",\"address\" : \"Earth somewhere else\"}}}";
	jsonStr = deleteSpaceOfString(jsonStr);
	//string str = "\"hello";	
	
	string key,value;
	//getline(cin,key);
	//getline(cin,value);
	//string temp = ",\"" + key + "\":" + value;
	//temp = deleteSpaceOfString(temp);

	JSONList jsonlist(jsonStr);
	jsonlist.getls();
	jsonlist.getcd("\"entries\"");
	jsonlist.getls();
	string nodeValue = jsonlist.getValue(jsonlist.curr);
	cout << jsonlist.curr->key << endl;
	cout << nodeValue << endl;
	
	jsonlist.getcat("\"hanmeimei\"");

	jsonlist.getadd("\"xiaoming\"","{ \"age\": 28, \"mobile\" : \"13700000002\", \"address\" : \"Earth somewhere too\" }");
	jsonlist.getls();
	int len = jsonlist.curr->value.size();
	jsonlist.getcat("\"xiaoming\"");

	jsonlist.getremove("\"xiaoming\"");
	//jsonlist.curr->value.insert(len-2,temp);

	jsonlist.getls();*/


	/*int i = jsonStr.find("{");
	int j = jsonStr.find(":");
	string key = jsonStr.substr(i+1,j-i);
	int k = jsonStr.rfind("}",jsonStr.size()-2);
	jsonStr = jsonStr.substr(j+1,k-j);
	//i = jsonStr.find("{");
	//j = jsonStr.find(":");
	//key = jsonStr.substr(i+1,j);
	//jsonStr = jsonStr.substr(j+1);
	//size_t a = strlen(str.c_str());

	JSONList list;
	JSONNode *tmp = new JSONNode();
	tmp->key = key;
	tmp->value = jsonStr;
	tmp->pPrev = list.root;
	list.root->pNext = tmp;
	list.curr = tmp;
	tmp->pNext = NULL;
	
	//jsonStr.find_first_of
	
	cout << list.curr->key << endl;
	cout << list.curr->value;
	while (!jsonStr.empty())
	{
		i = jsonStr.find("{");
		j = jsonStr.find(":");
		k = jsonStr.find("}");
		key = jsonStr.substr(i+1,j-i-1);
		jsonStr = jsonStr.substr(j+2,k-j-1);
		JSONNode *node = new JSONNode();
		node->key = key;
		//node->value = 
	}*/

	return 0;
}