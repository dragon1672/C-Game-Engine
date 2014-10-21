#pragma once

#include <ExportHeader.h>

template <typename T>
class ENGINE_SHARED PropertyGet {
private:
	inline void init(std::function<T(T&)>getter = [](T&val){return val;}) { this->getter = getter; };
protected:
	T val;
	PropertyGet& operator=(const PropertyGet<T>&);
	PropertyGet(const PropertyGet<T>&);
public:
	//prams(1/1) ref to val
	//return something
	std::function<T(T&)>getter;

	explicit PropertyGet(float a=0) : val(a) { init(); }
	explicit PropertyGet(float a,std::function<T(T&)>getter) : val(a) { init(getter); }
	explicit PropertyGet(std::function<T(T&)>getter) : val(0) { init(getter); }

	inline T get() { return getter(val); }
	inline operator T() { return get(); }
};


template <typename T>
class PropertyGetSet : public PropertyGet<T> {
private:
	inline void init(std::function<void(T&,T&)> setter = [](T& val, T& newGuy) {val = newGuy;}) { this->setter = setter; };
public:
	//prams(1/2) ref to val
	//prams(2/2) value attempted to set
	std::function<void(T&,T&)> setter;

	inline PropertyGetSet(T a) : PropertyGet(a) {init();};
	inline PropertyGetSet(T a, std::function<T(T&)> getter) : PropertyGet(a,getter) {init();};
	inline PropertyGetSet(std::function<T(T&)> getter) : PropertyGet(0,getter) {init();};
	inline PropertyGetSet(T a, std::function<T(T&)> getter, std::function<void(T&,T&)> setter) : PropertyGet(a,getter) {init(setter);};
	inline PropertyGetSet(std::function<T(T&)> getter, std::function<void(T&,T&)> setter) : PropertyGet(0,getter) {init(setter);};
	inline PropertyGetSet(const PropertyGet<T>& that) { val = that; }

	inline PropertyGetSet & operator=(const PropertyGet<T>& that) { val = that; }
	inline void set(T toSet) { setter(val,toSet); }
	inline PropertyGetSet& operator+=(PropertyGet<T>& that){ (set(get()+that)); return *this; }
	inline PropertyGetSet& operator-=(PropertyGet<T>& that){ (set(get()-that)); return *this; }
	inline PropertyGetSet& operator*=(PropertyGet<T>& that){ (set(get()*that)); return *this; }
	inline PropertyGetSet& operator/=(PropertyGet<T>& that){ (set(get()/that)); return *this; }
	inline operator const PropertyGet<T>&() { return get(); }
};