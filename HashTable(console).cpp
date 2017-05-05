#include "stdafx.h"
#include "HashTable.h"
#include <assert.h>
#include <string>

int stringHash(string str)
{
	int sum = 0;
	for (int i = 0; i < static_cast<int>(str.length()); i++)
	{
		sum += str[i] * (i + 1);
	}
	return sum;
}

int main()
{
	std::function<int(string)> stringHashFunction = stringHash;
	HashTable<string, string> rus2eng(stringHashFunction);

	assert(!rus2eng.containes(string("ÿáëîêî")));
	rus2eng.setValue(string("ÿáëîêî"), string("apple"));
	assert(rus2eng.containes(string("ÿáëîêî")));
	assert(rus2eng.getValue(string("ÿáëîêî"), string("tomato")) == string("apple"));

	rus2eng.setValue(string("ïîìèäîð"), string("tomato"));
	assert(rus2eng.containes(string("ïîìèäîð")));
	assert(rus2eng.getValue(string("ÿáëîêî"), string("tomato")) == string("apple"));
	assert(rus2eng.getValue(string("ïîìèäîð"), string("")) == string("tomato"));

	HashTable<string, string> rus2eng2(rus2eng);
	assert(rus2eng2.containes(string("ïîìèäîð")));
	assert(rus2eng2.containes(string("ÿáëîêî")));

	rus2eng.remove(string("ÿáëîêî"));
	assert(rus2eng.containes(string("ïîìèäîð")));
	assert(!rus2eng.containes(string("ÿáëîêî")));

	rus2eng2.clear();
	assert(!rus2eng2.containes(string("ïîìèäîð")));
	assert(!rus2eng2.containes(string("ÿáëîêî")));

    return 0;
}
