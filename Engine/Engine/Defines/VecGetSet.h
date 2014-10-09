#define GET_SET_VEC2(short_name,var_name) \
private: \
	glm::vec2 var_name; \
public: \
	inline float     get##short_name##X() { return var_name.x; } \
	inline float     get##short_name##Y() { return var_name.y; } \
	inline glm::vec2 get##short_name##()  { return var_name;   } \
	inline void set##short_name##X(float x) { var_name.x = x;  } \
	inline void set##short_name##Y(float y) { var_name.y = y;  } \
	inline void set##short_name##(float x, float y) { var_name = glm::vec2(x,y); } \
	inline void set##short_name##(glm::vec2 toSet) { var_name = toSet; }

#define GET_SET_VEC3(short_name,var_name) \
private: \
	glm::vec3 var_name; \
public: \
	inline float     get##short_name##X() { return var_name.x; } \
	inline float     get##short_name##Y() { return var_name.y; } \
	inline float     get##short_name##Z() { return var_name.z; } \
	inline glm::vec3 get##short_name##()  { return var_name;   } \
	inline void set##short_name##X(float x) { var_name.x = x;  } \
	inline void set##short_name##Y(float y) { var_name.y = y;  } \
	inline void set##short_name##Z(float z) { var_name.z = z;  } \
	inline void set##short_name##(float x, float y, float z) { var_name = glm::vec3(x,y,z); } \
	inline void set##short_name##(glm::vec3 toSet) { var_name = toSet; }

#define GET_SET_VEC4(short_name,var_name) \
private: \
	glm::vec4 var_name; \
public: \
	inline float     get##short_name##X() { return var_name.x; } \
	inline float     get##short_name##R() { return var_name.x; } \
	inline float     get##short_name##Y() { return var_name.y; } \
	inline float     get##short_name##G() { return var_name.y; } \
	inline float     get##short_name##B() { return var_name.z; } \
	inline float     get##short_name##G() { return var_name.z; } \
	inline float     get##short_name##A() { return var_name.a; } \
	inline float     get##short_name##W() { return var_name.a; } \
	inline glm::vec4 get##short_name##()  { return var_name;   } \
	inline void set##short_name##X(float x) { var_name.x = x;  } \
	inline void set##short_name##R(float r) { var_name.x = x;  } \
	inline void set##short_name##Y(float y) { var_name.y = y;  } \
	inline void set##short_name##G(float g) { var_name.y = y;  } \
	inline void set##short_name##Z(float z) { var_name.z = z;  } \
	inline void set##short_name##B(float b) { var_name.z = z;  } \
	inline void set##short_name##W(float w) { var_name.a = w;  } \
	inline void set##short_name##A(float a) { var_name.a = a;  } \
	inline void set##short_name##(float r, float g, float b, float a) { var_name = glm::vec4(r,g,b,a); } \
	inline void set##short_name##(glm::vec4 toSet) { var_name = toSet; }

#define GET_SET_TRACK_VEC2(short_name,var_name) \
private: \
	glm::vec2 var_name; bool short_name##Changed; \
public: \
	inline float     get##short_name##X() { return var_name.x; } \
	inline float     get##short_name##Y() { return var_name.y; } \
	inline glm::vec2 get##short_name##()  { return var_name;   } \
	inline void set##short_name##X(float x) { var_name.x = x; short_name##Changed = true; } \
	inline void set##short_name##Y(float y) { var_name.y = y; short_name##Changed = true; } \
	inline void set##short_name##(float x, float y) { var_name = glm::vec2(x,y); short_name##Changed = true; } \
inline void set##short_name##(glm::vec2 toSet) { var_name = toSet; short_name##Changed = true; }

#define GET_SET_TRACK_VEC3(short_name,var_name) \
private: \
	glm::vec3 var_name; bool short_name##Changed; \
public: \
	inline float     get##short_name##X() { return var_name.x; } \
	inline float     get##short_name##Y() { return var_name.y; } \
	inline float     get##short_name##Z() { return var_name.z; } \
	inline glm::vec3 get##short_name##()  { return var_name;   } \
	inline void set##short_name##X(float x) { var_name.x = x; short_name##Changed = true; } \
	inline void set##short_name##Y(float y) { var_name.y = y; short_name##Changed = true; } \
	inline void set##short_name##Z(float z) { var_name.z = z; short_name##Changed = true; } \
	inline void set##short_name##(float x, float y, float z) { var_name = glm::vec3(x,y,z); short_name##Changed = true; } \
	inline void set##short_name##(glm::vec3 toSet) { var_name = toSet; short_name##Changed = true; }

#define GET_SET_TRACK_VEC4(short_name,var_name) \
private: \
	glm::vec3 var_name; bool short_name##Changed; \
public: \
	inline float     get##short_name##X() { return var_name.x; } \
	inline float     get##short_name##R() { return var_name.x; } \
	inline float     get##short_name##Y() { return var_name.y; } \
	inline float     get##short_name##G() { return var_name.y; } \
	inline float     get##short_name##B() { return var_name.z; } \
	inline float     get##short_name##G() { return var_name.z; } \
	inline float     get##short_name##A() { return var_name.a; } \
	inline float     get##short_name##W() { return var_name.a; } \
	inline glm::vec4 get##short_name##()  { return var_name;   } \
	inline void set##short_name##X(float x) { var_name.x = x; short_name##Changed = true; } \
	inline void set##short_name##R(float r) { var_name.x = x; short_name##Changed = true; } \
	inline void set##short_name##Y(float y) { var_name.y = y; short_name##Changed = true; } \
	inline void set##short_name##G(float g) { var_name.y = y; short_name##Changed = true; } \
	inline void set##short_name##Z(float z) { var_name.z = z; short_name##Changed = true; } \
	inline void set##short_name##B(float b) { var_name.z = z; short_name##Changed = true; } \
	inline void set##short_name##W(float w) { var_name.a = w; short_name##Changed = true; } \
	inline void set##short_name##A(float a) { var_name.a = a; short_name##Changed = true; } \
	inline void set##short_name##(float r, float g, float b, float a) { var_name = glm::vec4(r,g,b,a); short_name##Changed = true; } \
	inline void set##short_name##(glm::vec4 toSet) { var_name = toSet; short_name##Changed = true; }

