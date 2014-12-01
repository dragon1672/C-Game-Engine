#pragma once

#include <vector>
#include <ExportHeader.h>
#include <functional>

template<typename T> class ENGINE_SHARED ConstVector {
private:
	std::vector<T*> arrays;
public:

	inline void add(const std::vector<T>& toAdd)        { add(&toAdd[0],toAdd.size()); }
	inline void add(const ConstVector<T>& toAdd)        { for (int i = 0; i < toAdd.size(); i++) add(toAdd[i]); }
	inline void add(const T * toAdd, unsigned int size) { for (int i = 0; i < size;         i++) add(toAdd[i]); }

	inline void push_back(const T& toAdd)				      { add(toAdd); }
	inline void push_back(const std::vector<T>& toAdd)        { add(toAdd); }
	inline void push_back(const ConstVector<T>& toAdd)        { add(toAdd); }
	inline void push_back(const T * toAdd, unsigned int size) { add(toAdd,size); }

	inline int find(T * toMatch) {
		for (uint i = 0; i < arrays.size(); i++) {
			if(arrays[i] == toMatch)
				return i;
		}
		return -1;
	}
	inline int find(std::function<bool(const T&)> checker) {
		for (uint i = 0; i < size(); i++)
			if(checker((*this)[i])) return i;
		return -1;
	}

	inline T& add(const T& toAdd) {
		arrays.push_back(new T(toAdd));
		return back();
	}
	inline T& get(int index)   { return (*this)[index]; }
	inline T& ConstVector<T>::first() { return (*this)[0]; }
	inline T& ConstVector<T>::back() { return (*this)[size()-1]; }
	inline bool remove(T*toKill) { return remove(find(toKill)); }
	inline bool remove(int index) {
		delete arrays[index];
		arrays.erase(arrays.begin() + index);
		return true;
	}

	inline void ConstVector<T>::pop_back() {
		delete arrays.back();
		arrays.pop_back();
	}

	inline unsigned int size() { return arrays.size();   }
	inline const T& operator[](std::size_t idx) const { return const_cast<T&>(*this)[idx]; };

	inline T& operator[](std::size_t idx) {
		return *arrays[idx];
	};
	void clear() {
		while(arrays.size() > 0) {
			delete arrays.back();
			arrays.pop_back();
		}
	}
	~ConstVector() {
		clear();
	}

	void resize(unsigned int index) {
		int old = arrays.size();
		for (uint i = old; i > index; i--) { // if making smaller
			delete arrays[i];
		}
		arrays.resize(index);
		for (uint i = old; i < arrays.size(); i++) { // if making bigger
			arrays[i] = new T();
		}
	}


};