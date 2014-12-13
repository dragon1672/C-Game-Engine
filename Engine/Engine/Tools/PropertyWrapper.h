#pragma once

#include <ExportHeader.h>
#include <functional>

template <typename T>
class ENGINE_SHARED PropertyGet {
private:
	inline void init(std::function<T(T&)>getter = [](T&val){return val;}) { this->getter = getter; };
protected:
	T val;
	PropertyGet& operator=(const PropertyGet<T>& that) {
		val = that.val;
		getter = that.getter;
		return *this;
	}
	PropertyGet(const PropertyGet<T>& that) {
		val = that.val;
		getter = that.getter;
	}
public:
	//prams(1/1) ref to val
	//return something
	std::function<T(T& internalValue)>getter;

	explicit PropertyGet() { init(); }
	explicit PropertyGet(T a) : val(a) { init(); }
	explicit PropertyGet(T a,std::function<T(T&)>getter) : val(a) { init(getter); }
	explicit PropertyGet(std::function<T(T&)>getter) : val(0) { init(getter); }

	inline T get() { return getter(val); }
	inline operator T() { return get(); }
};


template <typename T>
class ENGINE_SHARED PropertyGetSet : public PropertyGet<T> {
private:
	inline void init(std::function<void(T&,T&)> setter = [](T& val, T& newGuy) {val = newGuy;}) { this->setter = setter; };
public:
	//prams(1/2) ref to val
	//prams(2/2) value attempted to set
	std::function<void(T& internalValue,T& incomming)> setter;

	PropertyGetSet() : PropertyGet() {init();};
	PropertyGetSet(T a) : PropertyGet(a) {init();};
	PropertyGetSet(T a, std::function<T(T&)> getter) : PropertyGet(a,getter) {init();};
	PropertyGetSet(std::function<T(T&)> getter) : PropertyGet(0,getter) {init();};
	PropertyGetSet(T a, std::function<T(T&)> getter, std::function<void(T&,T&)> setter) : PropertyGet(a,getter) {init(setter);};
	PropertyGetSet(std::function<T(T&)> getter, std::function<void(T&,T&)> setter) : PropertyGet(0,getter) {init(setter);};
	PropertyGetSet(const PropertyGet<T>& that) { val = that; }

	inline PropertyGetSet & operator=(const PropertyGet<T>& that) { val = that; }
	inline void set(T toSet) { setter(val,toSet); }
	inline PropertyGetSet& operator=(T& that){ (set(that)); return *this; }
	inline PropertyGetSet& operator+=(PropertyGet<T>& that){ (set(get()+that)); return *this; }
	inline PropertyGetSet& operator-=(PropertyGet<T>& that){ (set(get()-that)); return *this; }
	inline PropertyGetSet& operator*=(PropertyGet<T>& that){ (set(get()*that)); return *this; }
	inline PropertyGetSet& operator/=(PropertyGet<T>& that){ (set(get()/that)); return *this; }
	inline T& getRef() { return val; }
	//inline operator const T&() { return get(); }
};