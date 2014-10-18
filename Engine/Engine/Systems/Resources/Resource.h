#pragma once

#include <unordered_set>
#include <map>
#include <vector>

class Object {
	static int GLOBAL_ID;
	static std::vector<Object*> allObjs_list;
	struct NameMatches {std::vector<Object*> data; };
	static std::map<const char *,NameMatches> nameObjectPairs;

public:
	static void Register(Object * toAdd) {
		while(allObjs_list.size() <= toAdd->getID())  allObjs_list.push_back(nullptr);
		allObjs_list[toAdd->getID()];

		auto id = nameObjectPairs.find(toAdd->getName());
		if (id == nameObjectPairs.end()) {
			nameObjectPairs.emplace(toAdd->name,NameMatches());
		}
		nameObjectPairs[toAdd->getName()].data.push_back(toAdd);
	}
	static void UnRegister(Object * toKill) {
		allObjs_list[toKill->getID()] = nullptr;

		auto id = nameObjectPairs.find(toKill->getName());
		if (id != nameObjectPairs.end()) {
			auto& data = nameObjectPairs[toKill->getName()].data;
			for (unsigned int i = 0; i < data.size(); i++)
			{
				if(data[i] == toKill) {
					data.erase(data.begin() + i);
					i--;
				}
			}
			//wonder if this is worth it
			if(data.size() <= 0) {
				nameObjectPairs.erase(toKill->getName());
			}
		}
	}
	static Object * getFirst(int id) {
		return 0 <= id && id < allObjs_list.size() ? allObjs_list[id] : nullptr;
	}
	static void GetFirst(const char * name) {
		allObjs_list[toKill->getID()] = nullptr;

		auto id = nameObjectPairs.find(toKill->getName());
		if (id != nameObjectPairs.end()) {
			auto& data = nameObjectPairs[toKill->getName()].data;
			for (unsigned int i = 0; i < data.size(); i++)
			{
				if(data[i] == toKill) {
					data.erase(data.begin() + i);
					i--;
				}
			}
			//wonder if this is worth it
			if(data.size() <= 0) {
				nameObjectPairs.erase(toKill->getName());
			}
		}
	}

	int id;
	const char * name;
public:
	Object() : name(nullptr), id(GLOBAL_ID++) {}
	int getID() { return id; }
	const char * getName() { return name; }
};