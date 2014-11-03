//Place this in the class header, I prefer the first line
#define DEFINE_SINGLETON(class_name)            \
	private: static class_name * _instance;     \
	public: static class_name##& getInstance(); \
	public: static void delInstance();          \
	private:


//place in a CPP file
#define IMPLEMENT_SINGLETON(class_name) \
	class_name * class_name##::_instance = nullptr; \
	class_name##& class_name##::getInstance() { if(_instance==nullptr) { _instance = new class_name(); } return *_instance; } \
	void class_name##::delInstance() { if(_instance != nullptr) { delete _instance; } _instance = nullptr; }

#define DEFINE_SINGLETON_CAST(class_name,type_cast) \
	private: static class_name * _instance; \
	public: static type_cast##& getInstance(); \
	public: static void delInstance(); \
	private:

//place in a CPP file
#define IMPLEMENT_SINGLETON_CAST(class_name,type_cast) \
	class_name * class_name##::_instance = nullptr; \
	type_cast##& class_name##::getInstance() { return *(type_cast*)(_instance == nullptr ? _instance = new class_name() : _instance); } \
	void class_name##::delInstance() { if(_instance == nullptr) delete _instance; _instance = nullptr; }