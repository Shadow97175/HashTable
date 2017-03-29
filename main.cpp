#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "HashTable.h"

using namespace std;

int main()
{
	int i, k, chose;
	string val;
	HashTable<int, string> table;


	do{
		for (HashTable<int, string>::iterator it = table.begin(); it != table.end(); it++)
		{
			node<int, string> tr;
			tr = *it;
			if (tr.s == full)
				cout << "[" << tr.key << ";" << tr.value << "] " << endl;
			else
				cout << "[ ] " << endl;
		}

		do
		{
			cout << "1-insert; 2-delete; 3-serch; 4-size; 5-exit" << endl;
			cin.sync();
			cin.clear();
			cin >> chose;
		} while (cin.fail());
		if (chose == 1) {
			do
			{
				cout << "enter key: " << endl;
				cin.sync();
				cin.clear();
				cin >> k;
			} while (cin.fail());
			do
			{
				cout << "enter val: " << endl;
				cin.sync();
				cin.clear();
				cin >> val;
			} while (cin.fail());
			table.insert(k, val);
		}
		if (chose == 2) {
			do
			{
				cout << "enter key: " << endl;
				cin.sync();
				cin.clear();
				cin >> k;
			} while (cin.fail());
			table.erase(k);
		}
		if (chose == 3){
			do
			{
				cout << "enter key: " << endl;
				cin.sync();
				cin.clear();
				cin >> k;
			} while (cin.fail());
			i = table.search(k);
			if (i >= 0 && i<table.size())
				cout << "value: " << table[i].value << endl;
			else 
				cout << "not found" << endl;
		}
		if (chose == 4) {
			cout << table.size() << endl;
		}
		cout << "" << endl;
	} while (chose != 5);
	return 0;
}
