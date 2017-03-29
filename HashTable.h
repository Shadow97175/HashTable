#include <iostream>
#include <vector>
#include <cmath>




enum cellState { null, full, del };

template <typename k, typename v>
struct node {
	v value;
	k key;
	cellState s;
};

template <typename key, typename val>
class HashTable
{
private:
	int hashFunction(key k, int i);
	int primeNumber();
public:
	int m, tableSize;
	std::vector<node<key, val>> T;
	HashTable();
	~HashTable();
	int search(key k);
	void erase(key k);
	void insert(key k, val value);
	int size();

	typedef node<key, val> * iterator;
	iterator begin()
	{
		return &T[0];
	}

	iterator end()
	{
		return begin()+m;
	}
	const node<key, val> operator[](const int index) const
	{
		if (index >= m || index < 0)
		{
			_DEBUG_ERROR("out of range");
		//	std::cout << "out of range" << std::endl;
		}

		return T[index];
	}

};


template <typename key, typename val>
HashTable<key, val>::HashTable()
{
	m = 3;
	tableSize = 0;
	node<key, val> l;
	l.s = null;
	for (int i = 0; i < m; i++) {
		T.push_back(l);
	}
}


template <typename key, typename val>
HashTable<key, val>::~HashTable()
{
}




template <typename key, typename val>
int HashTable<key, val>::hashFunction(key k, int i)
{
	int a, b;
	std::hash<key> hash_fn;
	a = hash_fn(k);
	a = abs(a);
	b = a + i*(1 + a % (m - 2));
	return b;
}


template <typename key, typename val>
int HashTable<key, val>::search(key k)
{
	int i;
	int j;
	for (i = 0; i <= m; i++){
		j = (hashFunction(k, i)) % m;
		if (T[j].key == k && T[j].s == full) {
			return j;
		}
		if (T[j].s == null)
			return -1;
	}

	return -1;
}


template <typename key, typename val>
void HashTable<key, val>::erase(key k)
{
	int i;
	i = search(k);
	if (i != -1) {
		T[i].s = del;
		tableSize--;
	}
	else {
		_DEBUG_ERROR("not found");
	//	std::cout << "not found" << std::endl;
	}

	return;
}


template <typename key, typename val>
void HashTable<key, val>::insert(key k, val value)
{
	int i = 0;
	int j;
	int w = -1;
	bool keyError = false;

	/*cout << "----------------------" << endl;
	for (int p = 0; p < m; p++){
	j = (hashFunction(k, p)) % m;
	cout << j << endl;
	}
	cout << "----------------------" << endl;*/
	do {
		j = (hashFunction(k, i)) % m;
		if (T[j].s != full && w == -1)
			w = j;
		if (T[j].s == full){
			if (T[j].key == k)
				keyError = true;
		}
		i++;

	} while (T[j].s != null && i < m);

	if (keyError == false && w > -1){
		T[w].value = value;
		T[w].key = k;
		T[w].s = full;
		tableSize++;
	}
	if (keyError == true)
		_DEBUG_ERROR("key already exist");
	//	std::cout << "key already exist" << std::endl;

	if (i == m) {
		int n = primeNumber();
		/*std::cout << "overflow" << std::endl;
		int n;
		bool isPrime = true;
		n = 2 * m;
		do{
			isPrime = true;
			n++;
			for (int e = 2; e < n / 2; e++)
				if (n % e == 0)
					isPrime = false;
		} while (isPrime == false);*/

		vector<node<key, val>> T1;
		node<key, val> l;
		l.s = null;
		for (int i1 = 0; i1 < n; i1++)
			T1.push_back(l);
		T.swap(T1);
		swap(m, n);
		for (int i1 = 0; i1 < n; i1++){
			insert(T1[i1].key, T1[i1].value);
			tableSize--;
		}
		insert(k, value);
	}
	return;
}


template <typename key, typename val>
int HashTable<key, val>::primeNumber()
{
	int n;
	bool isPrime = true;
	n = 2 * m;
	do{
		isPrime = true;
		n++;
		for (int e = 2; e < n / 2; e++)
			if (n % e == 0){
				isPrime = false;
				break;
			}
	} while (isPrime == false);
	return(n);
}


template <typename key, typename val>
int HashTable<key, val>::size()
{
	return(tableSize);
}
