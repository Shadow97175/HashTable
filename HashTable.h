#pragma once
#include <functional>
#include <memory>

using namespace std;

template <typename KEY, typename VALUE>
struct HashTableNode
{
	int hash;
	KEY key;
	VALUE value;
	shared_ptr<HashTableNode> lesserNode;
	shared_ptr<HashTableNode> biggerNode;
};

template <typename KEY, typename VALUE>
class HashTable
{
public:
	HashTable(function<int(KEY)> hashFunction);
	HashTable(const HashTable<KEY, VALUE>& otherHashTable);

	void setValue(KEY key, VALUE value);
	VALUE getValue(KEY key, VALUE defaultValue = VALUE());
	void remove(KEY key);
	bool containes(KEY key);
	void clear();
	const HashTable<KEY, VALUE>& operator = (const HashTable<KEY, VALUE>& otherHashTable);
private:
	function<int(KEY)> HashFunction;
	shared_ptr<HashTableNode<KEY,VALUE> > FirstNode;

	// recursive functions
	void setValue(KEY key, VALUE value, int hash, shared_ptr<HashTableNode<KEY, VALUE> >& node);
	VALUE getValue(KEY key, VALUE defaultValue, int hash, shared_ptr<HashTableNode<KEY, VALUE> >& node);
	void remove(KEY key, int hash, shared_ptr<HashTableNode<KEY, VALUE> >& node);
	void addNode(shared_ptr<HashTableNode<KEY, VALUE> >& nodeToAdd, shared_ptr<HashTableNode<KEY, VALUE> >& destinationNode);
	bool containes(KEY key, int hash, shared_ptr<HashTableNode<KEY, VALUE> >& node);
	void copyNode(const shared_ptr<HashTableNode<KEY, VALUE> >& sourceNode, shared_ptr<HashTableNode<KEY, VALUE> >& destinationNode);
};



template <typename KEY, typename VALUE>
HashTable<KEY, VALUE>::HashTable(function<int(KEY)> hashFunction) :
	HashFunction(hashFunction)
{
}

template <typename KEY, typename VALUE>
HashTable<KEY, VALUE>::HashTable(const HashTable<KEY, VALUE>& otherHashTable)
{
	*this = otherHashTable;
}

template <typename KEY, typename VALUE>
void HashTable<KEY, VALUE>::setValue(KEY key, VALUE value)
{
	int newHash = HashFunction(key);
	setValue(key, value, newHash, FirstNode);
}

template <typename KEY, typename VALUE>
void HashTable<KEY, VALUE>::setValue(KEY key, VALUE value, int hash, shared_ptr<HashTableNode<KEY, VALUE> >& node)
{
	if (node == nullptr)
	{
		node = make_shared<HashTableNode<KEY, VALUE> >();
		node->hash = hash;
		node->key = key;
		node->value = value;
		return;
	}

	if (node->hash == hash)
	{
		if (node->key == key)
		{
			node->value = value;
		}
		else
		{
			setValue(key, value, hash, node->biggerNode);
		}
		return;
	}

	if (hash < node->hash)
	{
		setValue(key, value, hash, node->lesserNode);
	}
	else
	{
		setValue(key, value, hash, node->biggerNode);
	}
}

template <typename KEY, typename VALUE>
VALUE HashTable<KEY, VALUE>::getValue(KEY key, VALUE defaultValue)
{
	int newHash = HashFunction(key);
	return getValue(key, defaultValue, newHash, FirstNode);
}

template <typename KEY, typename VALUE>
VALUE HashTable<KEY, VALUE>::getValue(KEY key, VALUE defaultValue, int hash, shared_ptr<HashTableNode<KEY, VALUE> >& node)
{
	if (node == nullptr)
	{
		return defaultValue;
	}

	if (node->hash == hash)
	{
		if (node->key == key)
		{
			return node->value;
		}
		else
		{
			return getValue(key, defaultValue, hash, node->biggerNode);
		}
	}

	if (hash < node->hash)
	{
		return getValue(key, defaultValue, hash, node->lesserNode);
	}
	else
	{
		return getValue(key, defaultValue, hash, node->biggerNode);
	}
}

template <typename KEY, typename VALUE>
void HashTable<KEY, VALUE>::remove(KEY key)
{
	int newHash = HashFunction(key);
	remove(key, newHash, FirstNode);
}

template <typename KEY, typename VALUE>
void HashTable<KEY, VALUE>::remove(KEY key, int hash, shared_ptr<HashTableNode<KEY, VALUE> >& node)
{
	if (node == nullptr)
	{
		return;
	}

	if (node->hash == hash)
	{
		if (node->key == key)
		{
			shared_ptr<HashTableNode<KEY, VALUE> > lesserNode = node->lesserNode;
			shared_ptr<HashTableNode<KEY, VALUE> > biggerNode = node->biggerNode;
			node.reset();
			node = biggerNode;
			addNode(lesserNode, node);
		}
		else
		{
			remove(key, hash, node->biggerNode);
		}
		return;
	}

	if (hash < node->hash)
	{
		remove(key, hash, node->lesserNode);
	}
	else
	{
		remove(key, hash, node->biggerNode);
	}
}

template <typename KEY, typename VALUE>
void HashTable<KEY, VALUE>::addNode(shared_ptr<HashTableNode<KEY, VALUE> >& nodeToAdd, shared_ptr<HashTableNode<KEY, VALUE> >& destinationNode)
{
	if (destinationNode == nullptr)
	{
		destinationNode = nodeToAdd;
		return;
	}

	if (nodeToAdd->hash >= destinationNode->hash)
	{
		addNode(nodeToAdd, destinationNode->biggerNode);
	}
	else
	{
		addNode(nodeToAdd, destinationNode->lesserNode);
	}
}

template <typename KEY, typename VALUE>
bool HashTable<KEY, VALUE>::containes(KEY key)
{
	int newHash = HashFunction(key);
	return containes(key, newHash, FirstNode);
}

template <typename KEY, typename VALUE>
bool HashTable<KEY, VALUE>::containes(KEY key, int hash, shared_ptr<HashTableNode<KEY, VALUE> >& node)
{
	if (node == nullptr)
	{
		return false;
	}

	if (node->hash == hash)
	{
		if (node->key == key)
		{
			return true;
		}
		else
		{
			return containes(key, hash, node->biggerNode);
		}
	}

	if (hash < node->hash)
	{
		return containes(key, hash, node->lesserNode);
	}
	else
	{
		return containes(key, hash, node->biggerNode);
	}
}

template <typename KEY, typename VALUE>
void HashTable<KEY, VALUE>::clear()
{
	FirstNode.reset();
}

template <typename KEY, typename VALUE>
const HashTable<KEY, VALUE>& HashTable<KEY, VALUE>::operator = (const HashTable<KEY, VALUE>& otherHashTable)
{
	HashFunction = otherHashTable.HashFunction;
	copyNode(otherHashTable.FirstNode, FirstNode);
	return otherHashTable;
}

template <typename KEY, typename VALUE>
void HashTable<KEY, VALUE>::copyNode(const shared_ptr<HashTableNode<KEY, VALUE> >& sourceNode, shared_ptr<HashTableNode<KEY, VALUE> >& destinationNode)
{
	if (destinationNode != nullptr)
	{
		destinationNode.reset();
	}

	if (sourceNode == nullptr)
	{
		return;
	}

	destinationNode = make_shared<HashTableNode<KEY, VALUE> >();
	destinationNode->hash = sourceNode->hash;
	destinationNode->key = sourceNode->key;
	destinationNode->value = sourceNode->value;

	copyNode(sourceNode->lesserNode, destinationNode->lesserNode);
	copyNode(sourceNode->biggerNode, destinationNode->biggerNode);
}
