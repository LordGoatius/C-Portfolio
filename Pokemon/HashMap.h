#ifndef HASHMAP_H_
#define HASHMAP_H_

#include <string>
#include <cmath>
#include <vector>
#include <sstream>
#include "Pair.h"
#include "HashMapInterface.h"

#define DEFAULT_MAP_HASH_TABLE_SIZE	31
#define HASH_CONSTANT				3
#define LOAD_THRESHOLD				75

using namespace std;

template <typename K,typename V>
class HashMap :  public HashMapInterface<K,V> {
private:
	size_t size_;
	size_t capacity;
	Pair<string,V>* data;
	vector<K> hashes = {};
public:
	HashMap() : size_(0), capacity(DEFAULT_MAP_HASH_TABLE_SIZE), data(new Pair<string,V>[DEFAULT_MAP_HASH_TABLE_SIZE]) {}
	HashMap(int newSize) : size_(0), capacity(newSize), data(new Pair<string, V>[newSize]) {}
	virtual ~HashMap() {
		this->clear();
		delete[] data;
	}

	size_t keyToIndex(const K& key) const {
		long index = 0;
		for (size_t i = 0, hash = key.length() - 1; i < key.length(); ++i, --hash) {
			index += (key.at(i) * pow(HASH_CONSTANT, hash));
		}
		index %= capacity;
		collision(key, index);
		return (size_t)index;
	}

	size_t toIndex(const K& key) {
		long index = 0;
		for (size_t i = 0, hash = key.length() - 1; i < key.length(); ++i, --hash) {
			index += (key.at(i) * pow(HASH_CONSTANT, hash));
		}
		index %= capacity;
		return (size_t)index;
	}

	bool collision(const K& key, long& index) const {
		if (data[index].first == "") return false;
		int count = 1;
		while (data[index].first != "") {
			if (data[index].first == key) return false;
			index = (index + count) % capacity;
			++count;
			++count;
		}
		return false;
	}

	/** Read/write index access operator.
	If the key is not found, an entry is made for it.
	@return: Read and write access to the value mapped to the provided key. */
	virtual V& operator[](const K& key) {
		if ((size_ * 100 / capacity) > LOAD_THRESHOLD) {
			this->resize();
		}
		int index = this->keyToIndex(key);
		if (notInHashes(key)) {
			hashes.push_back(key);
			++size_;
		}
		data[index].first = key;
		return data[index].second;
	}

	void resize() {
		size_ = 0;
		HashMap* copy = new HashMap<K, V>((capacity * 2));
		for (unsigned i = 0; i < this->hashes.size(); ++i) {
			if (data[i].first != "") {
				copy->operator[](hashes[i]) = this->data[this->keyToIndex(hashes[i])].second;
			}
		}
		this->clear();
		delete[] this->data;
		HashMap* temp = this;
//		this = copy;
		*this = *copy;
		copy = new HashMap();
		delete copy;
	}

	bool notInHashes(const K& key) {
		for (unsigned i = 0; i < hashes.size(); ++i) {
			if (key == hashes[i]) return false;
		}
		return true;
	}

	/** @return: the number of elements that match the key in the Map. */
	virtual size_t count(const K& key) {
		size_t count = 0;
		for (unsigned i = 0; i < hashes.size(); ++i) {
			if (key == hashes[i]) ++count;
			if ((count - 1) == capacity) {
				return true;
			}
		}
		return count;
	}

	// Removes all items from the Map. 
	virtual void clear(void) {
		delete[] data;
		size_ = 0;
		capacity = DEFAULT_MAP_HASH_TABLE_SIZE;
		data = new Pair<string, V>[DEFAULT_MAP_HASH_TABLE_SIZE];
	}

	// number of Key-Value pairs stored in the Map. 
	virtual size_t size(void) const {
		return this->size_;
	}

	// maximum number of Key-Value pairs that the Map can hold. 
	virtual size_t max_size(void) const {
		return this->capacity;
	}

	// string representation of Key-Value pairs in Map. 
	virtual string toString(void) const {
		ostringstream oss;
		for (unsigned i = 0; i < capacity; ++i) {
			if (data[i].first != "") {
				oss << "\t" << "[" << i << ":" << data[i].first << "->" << data[i].second << "]" << endl;
			}
		}
		return oss.str();
	}

	friend ostream& operator<<(ostream& os, const HashMap<K,V>& d) {
		os << d.toString();
		return os;
	}
};
#endif
