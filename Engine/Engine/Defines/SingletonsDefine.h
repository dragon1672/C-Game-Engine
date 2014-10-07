//Place this in the class header, I prefer the first line
#define DEFINE_SINGLETON(class_name) \
	private: static class_name * _instance; \
	public: static class_name##& getInstance(); \
	private:

//place in a CPP file
#define IMPLEMENT_SINGLETON(class_name) \
	class_name * class_name##::_instance = nullptr; \
	class_name##& class_name##::getInstance() { return *(_instance == nullptr ? _instance = new class_name : _instance); }