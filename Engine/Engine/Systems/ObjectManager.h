
#include <vector>
#include <Engine/Systems/Object.h>


class ObjectManagerPrivates;
class ObjectManager {
private:
	ObjectManagerPrivates * privates;
public:
	ObjectManager();
	~ObjectManager();
	void Register(Object * toAdd);
	void UnRegister(Object * toKill);
	Object * getFirst(int id);
	Object * getFirst(const char * name);
	std::vector<Object *> getAll(const char * name);
	int getUniqueId();
};