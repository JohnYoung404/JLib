#pragma once

#include <string>
#include "jMath.h"


//////////////////////////////////////////////////////////////////////////
// Too old, so Discarded, maybe restored later.
//////////////////////////////////////////////////////////////////////////
namespace jLib {

	unsigned int stringToNumber(std::string str) {
		unsigned int ret = 1;
		std::string::iterator itr = str.begin();
		for (; itr != str.end(); ++itr)
		{
			unsigned int headByte = 0xff000000 & ret;
			headByte >>= 24;
			ret = (ret << 8) | headByte;
			ret = (ret + static_cast<unsigned char>(*itr) + 1) * static_cast<unsigned char>(*itr);
		}
		return ret;
	}

	unsigned int mult_hashFunc(unsigned int key, unsigned int degree_m) {
		unsigned int r = key * GOLDEN_DIVNUM_OF_32_BIT;
		r >>= (32 - degree_m);
		return r;
	}

	unsigned int div_hashFunc(unsigned int key, unsigned int degree_m) {
		unsigned int range = static_cast<unsigned int>((pow(2, degree_m) + pow(2, degree_m + 1)) / 2);
		while (!isPrimeNumber(range)) range++;
		return key % range;
	}

	struct delistNode
	{
		unsigned int key;
		void* data;
		delistNode* prev;
		delistNode* next;
		delistNode(int keyVal = 0, void* dataVal = NULL)
			: prev(NULL)
			, next(NULL)
			, key(keyVal)
			, data(dataVal) {}
	};

	class jHashTable_chain
	{
	public:
		jHashTable_chain(unsigned int degree);
		~jHashTable_chain();
		void insertNode(delistNode* x);
		void deleteNode(delistNode* x);
		delistNode* search(unsigned int key);
	private:
		delistNode** T;
		unsigned int degree_m;
	};

	jHashTable_chain::jHashTable_chain(unsigned int degree)
		:degree_m(degree)
	{
		T = new delistNode*[static_cast<unsigned int>(pow(2, degree_m))];
		for (int i = 0; i < static_cast<int>(pow(2, degree_m)); ++i)
		{
			T[i] = new delistNode;
			T[i]->next = NULL;
		}
	}

	jHashTable_chain::~jHashTable_chain()
	{
		for (int i = 0; i < static_cast<int>(pow(2, degree_m)); ++i)
		{
			delete T[i];
		}
		delete[] T;
	}

	void jHashTable_chain::insertNode(delistNode* x) {
		unsigned int hashNum = mult_hashFunc(x->key, degree_m);
		if (T[hashNum]->next == NULL)
		{
			T[hashNum]->next = x;
			x->prev = T[hashNum];
		}
		else {
			x->next = T[hashNum]->next;
			x->prev = T[hashNum];
			T[hashNum]->next = x;
			x->next->prev = x;
		}
	}

	void jHashTable_chain::deleteNode(delistNode* x) {
		x->prev->next = x->next;
		x->next->prev = x->prev;
	}

	delistNode* jHashTable_chain::search(unsigned int key) {
		unsigned int hashNum = mult_hashFunc(key, degree_m);
		delistNode* p = T[hashNum]->next;
		while (p)
		{
			if (p->key == key)
			{
				return p;
			}
			p = p->next;
		}
		return NULL;
	}

	template<typename keyType, typename dataType>
	class jMap
	{
	public:
		jMap();
		~jMap();
		void insert(std::string key, dataType data);
		void insert(unsigned int key, dataType data);
		void deleteKey(unsigned int key);
		void deleteKey(std::string key);
		dataType* search(std::string key);
		dataType* search(unsigned int key);
	private:
		unsigned int degree;
		jHashTable_chain theHasher;
		std::vector<delistNode*> nodeVec;
	};

	template<typename keyType, typename dataType>
	jMap<keyType, dataType>::jMap()
		:degree(20)
		, theHasher(degree)
	{
		if ((typeid(keyType) != typeid(unsigned int)) && (typeid(keyType) != typeid(std::string)))
		{
			throw std::runtime_error("Key type is not supported.");
		}
	}

	template<typename keyType, typename dataType>
	jMap<keyType, dataType>::~jMap()
	{
		for (unsigned int i = 0; i < nodeVec.size(); ++i)
		{
			delete nodeVec[i]->data;
			delete nodeVec[i];
		}
	}

	template<typename keyType, typename dataType>
	void jMap<keyType, dataType>::insert(std::string key, dataType data) {
		delistNode* toInsert = new delistNode;
		toInsert->key = stringToNumber(key);
		dataType* dataptr = new dataType(data);
		toInsert->data = (void*)dataptr;
		nodeVec.push_back(toInsert);
		theHasher.insertNode(toInsert);
	}

	template<typename keyType, typename dataType>
	void jMap<keyType, dataType>::insert(unsigned int key, dataType data) {
		delistNode* toInsert = new delistNode;
		toInsert->key = key;
		dataType* dataptr = new dataType(data);
		toInsert->data = (void*)dataptr;
		nodeVec.push_back(toInsert);
		theHasher.insertNode(toInsert);
	}

	template<typename keyType, typename dataType>
	dataType* jMap<keyType, dataType>::search(unsigned int key) {
		delistNode* resultFound = theHasher.search(key);
		if (resultFound->data == NULL)
		{
			return NULL;
		}
		return (static_cast<dataType*>(resultFound->data));
	}

	template<typename keyType, typename dataType>
	dataType* jMap<keyType, dataType>::search(std::string key) {
		return search(stringToNumber(key));
	}

	template<typename keyType, typename dataType>
	void jMap<keyType, dataType>::deleteKey(unsigned int key) {
		theHasher.deleteNode(theHasher.search(key));
	}

	template<typename keyType, typename dataType>
	void jMap<keyType, dataType>::deleteKey(std::string key) {
		deleteKey(stringToNumber(key));
	}

}