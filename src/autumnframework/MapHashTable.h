/*
* Copyright 2006 the original author or authors.
* 
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
* 
*      http://www.apache.org/licenses/LICENSE-2.0
* 
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#ifndef AUTUMN_MAPHASHTABLE_H
#define AUTUMN_MAPHASHTABLE_H

#include <map>

/** 
 * Hash table template using map.
 * @param E Element type, must support operator "="
 * @param K Key type
 * @version 0.1.0
 * @since 2006-12-8
 */

using namespace std;

template<class E, class K> class MapHashTable{
private:
	/** The number of positons in hash table */
	int Divisor;

	/** Map array */
	map<K, E> *HashTable;

public:
	/** Constructor */
	MapHashTable(int divisor){
		this->Divisor = divisor;
		this->HashTable = new map<K, E>[divisor];
	}

	/** Destructor */
	~MapHashTable(){
		delete[] this->HashTable;
	}

	/** 
	 * Search a element by a key 
	 * @param k The key of the element to search
	 * @param e To save the searched element
	 * @return True if find the element, false if not
	 */
	bool searchElement(const K& key, E& e) const;

	/** Insert distinctly a element into hash table */
	void insertElement(const K& key, E& e);

	/** 
	 * Delete a element by a key 
	 * @param k The key of the element to delete
	 * @param e To save the deleted element
	 * @return True if find the element, false if not
	 */
	bool deleteElement(const K& key, E& e);
	
	/** List all elements in hash table */
	void listElement(map<K, E>& m);
};

	
template<class E, class K> bool MapHashTable<E, K>::
searchElement(const K& key, E& e) const {
	typename map<K, E>::iterator it = this->HashTable[key % this->Divisor].find(key);
	if( it != this->HashTable[key % this->Divisor].end() ){
		e = it->second;
		return true;
	}
	return false; 
}

/** Insert distinctly a element into hash table */
template<class E, class K> void MapHashTable<E, K>::
insertElement(const K& key, E& e){
	typename map<K, E>::iterator it = this->HashTable[key % this->Divisor].find(key);
	if( it != this->HashTable[key % this->Divisor].end() ){
		it->second = e;
	}
	else{
		this->HashTable[key % this->Divisor].insert(make_pair(key, e));
	}
	
}

/** Delete a element by a key */
template<class E, class K> bool MapHashTable<E, K>::
deleteElement(const K& key, E& e){
	typename map<K, E>::iterator it = this->HashTable[key % this->Divisor].find(key);
	if( it != this->HashTable[key % this->Divisor].end() ){
		e = it->second;
		this->HashTable[key % this->Divisor].erase(it);
		return true;
	}
	return false;
}

/** List all elements in hash table */
template<class E, class K> void MapHashTable<E, K>::
listElement(map<K, E>& m){
	for(int i=0; i<this->Divisor; i++){
		for(typename map<K, E>::iterator it = this->HashTable[i].begin();
				it != this->HashTable[i].end(); it++) {
			m.insert(make_pair(it->first, it->second));
		}
	}
}

#endif
