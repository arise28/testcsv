#include<iostream>
#include<fstream>
#include<cstdlib>
#include<string>
#include<vector>
#include<stdio.h>

using namespace std;

struct Node {
	Node *next;
	Node *pre;
	vector<string> myflied;
};

struct List {
	Node *head;
	Node *tail;
};

List* create_list(void)
{
	List *list = new List;
	list->head = NULL;
	list->tail = NULL;
	return list;
}

List *add_node(List *list, vector<string> flied)
{
	if (list->head == NULL)
	{
		Node *newnode = new Node;
		newnode->next = NULL;
		newnode->pre = list->head;
		newnode->myflied = flied;
		list->head = newnode;
		list->tail = newnode;
	}
	else
	{
		Node *newnode = new Node;
		newnode->next = NULL;
		newnode->pre = list->tail;
		newnode->myflied = flied;
		list->tail->next = newnode;
		list->tail = newnode;
	}
	vector<string>::iterator it2;
	/*for (it2 = flied.begin(); it2 != flied.end(); it2++)
	{
		cout << *it2 << ',';
	}
	cout << "\b " << endl;*/
	return list;
}

List* Flieds(string buffer, List *list)
{
	vector<string> flied;

	//int flag = 0;
	
	string::iterator it;
	string flied2;
	string::iterator f2_it;
	flied2.clear();
	for (it = buffer.begin(); it != buffer.end(); it++)
	{
		f2_it = flied2.end();

		if (*it == ',')
		{


			if (flied2.empty())
			{
				flied2 = "\"\"";
			}
			flied.push_back(flied2);
			flied2.clear();


			continue;
		}

		flied2.insert(f2_it, *it);
	}
	if (flied2.empty())
	{
		flied2 = "\"\"";
	}
	flied.push_back(flied2);
	flied2.clear();

	add_node(list, flied);
	return list;
}

List *traverse_list(List* list, int flag)
{
	//int judge_num;
	List *newlist = create_list();

	Node *p;
	Node *p2;

	while (list->head->next != NULL)
	{
		p = list->head->next;
		p2 = p->next;

		while (p2 != NULL)
		{
			if (p->myflied[flag - 1].length() < p2->myflied[flag - 1].length())
			{
				p2 = p2->next;
			}
			else if (p->myflied[flag - 1].length() > p2->myflied[flag - 1].length())
			{
					p = p2;
					p2 = p2->next;
			}
			else
			{	


				string::iterator pit ;
				pit = p->myflied[flag - 1].begin();
				string::iterator p2it ;
				p2it = p2->myflied[flag - 1].begin();

				//int i = 0;
				//while(p->myflied[flag - 1][i] != '\0')
				while (pit != p->myflied[flag - 1].end())
				{
					if (*pit == *p2it)
					{
						pit++;
						p2it++;
						continue;
					}
					else if (*pit < *p2it)
					{
						p2 = p2->next;
						break;
					}
					else if (*pit > *p2it)
					{
						p = p2;
						p2 = p2->next;
						break;
					}
					
				}
			}
			//judge_num = p->myflied[flag - 1].compare(p2->myflied[flag - 1]);
		}

		add_node(newlist, p->myflied);
		if (p->next != NULL)
		{
			p->pre->next = p->next;
			p->next->pre = p->pre;
			p->next = NULL;
			p->pre = NULL;
		}
		else
		{
			p->pre->next = NULL;
			p->pre = NULL;
		}

		delete p;
	}

	list->head->next = newlist->head;
	list->tail = newlist->tail;
	newlist->head->pre = list->head;
	newlist->head = NULL;
	newlist->tail = NULL;
	delete newlist;

	p = list->head->next;
	while (p != NULL)
	{
		vector<string>::iterator it2;
		for (it2 = p->myflied.begin(); it2 != p->myflied.end(); it2++)
		{
			cout << *it2 << ',';
		}
		cout << "\b " << endl;
		p = p->next;
	}
	return list;
}


int main()
{
	ifstream infile("test.csv");
	if (!infile.is_open())
	{
		cout << "file open error !" << endl;
		exit(1);
	}


	List *list1 = create_list();

	string buffer;
	//int account = 0 ;
	while (getline(infile, buffer))
	{


		//cout<<buffer<<endl;
		Flieds(buffer, list1);
		// if(account == 0)
		// {
		// account = 1;
		// continue;
		// }
	}
	cout << "请选择一项属性排序查找" << endl;
	vector<string>::iterator it2;
	int i = 1;
	for (it2 = list1->head->myflied.begin(); it2 != list1->head->myflied.end(); it2++)
	{
		cout << i++ << "." << *it2 << ' ';
	}
	cout << "\b " << endl;
	while (1)
	{
		int flag;
		cin >> flag;
		traverse_list(list1, flag);
	}
	return 0;
}