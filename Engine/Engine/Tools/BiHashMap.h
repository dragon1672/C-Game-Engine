#pragma once

#include <unordered_map>
#include <functional>

template<typename Key,typename Val>
class BiHashMap {
	std::unordered_map<Key,Val> forward;
	std::unordered_map<Val,Key> backwards;
public:
	bool containsKey(Key k)   { return forward.find(k)   != forward.end();   }
	bool containsValue(Val v) { return backwards.find(v) != backwards.end(); }
	void insert(Key k,Val v) {
		forward.emplace(k,v);
		backwards.emplace(v,k);
	}
	void emplace(Key k,Val v) { insert(k,v); }
	void removeKey(Key k) {
		auto v = forward[k];
		forward.erase(k);
		backwards.erase(v);
	}
	void removeValue(Key v) {
		auto k = backwards[v];
		forward.erase(k);
		backwards.erase(v);
	}
	Val getVal(Key k) { return forward[k];   }
	Key getKey(Val v) { return backwards[v]; }
	unsigned int size() const {
		return forward.size();
	}
	void clear() {
		forward.clear();
		backwards.clear();
	}
	void foreachKey(std::function<void(const Key& k)> toRun) {
		for (auto tmp : forward) {
			toRun(tmp.first);
		}
	}
	void foreachVal(std::function<void(const Val& v)> toRun) {
		for (auto tmp : backwards) {
			toRun(tmp.first);
		}
	}
	void foreachKeyVal(std::function<void(const Key& k,const Val& v)> toRun) {
		for (auto tmp : forward) {
			toRun(tmp.first,tmp.second);
		}
	}
	Key getRandomKey() {
		auto itr = forward.begin();
		return itr->first;
	}
	Val getRandomValue() {
		auto itr = backwards.begin();
		return itr->first;
	}
};