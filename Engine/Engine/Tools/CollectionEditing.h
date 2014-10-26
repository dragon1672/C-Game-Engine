#pragma once

#include <vector>
#include <functional>
#include <unordered_set>
#include <Engine/Tools/ConstVector.h>
#include <Engine/TypeDefs.h>
//included here since templates don't export well

namespace Collections {

	//sets
	template<typename Key, typename Hash, typename Pred, typename Alloc> bool contains(std::unordered_set<Key,Hash,Pred,Alloc> map, Key toFind) {
		return map.find(toFind) != map.end();
	}

	//vector
	template <typename T> int	 find(std::vector<T>& array, T toFind) {
		for (uint i = 0; i < array.size(); i++)
			if(array[i] == toFind) return i;
		return -1
	}
	template <typename T> bool	 contains(std::vector<T>& array, T toFind) {
		return find(array,toFind) >= 0;
	}
	template <typename T> std::vector<T> Where(std::vector<T>& array, std::function<bool(T&)> condition) {
		std::vector<T> ret;
		for(uint i=0;i<array.size();i++) if(condition(array[i])) ret.push_back(array[i]);
		return ret;
	}
	template <typename T> T SingleSelect(std::vector<T>& array, std::function<T(T&,T&)> selector) {
		T ret = T();
		for(uint i=0;i<array.size();i++) {
			ret = i==0 ? array[i] : selector(array[i],ret);
		};
		return ret;
	}
	template <typename T> int    Max(std::vector<T>& array, std::function<int    (T&)> selector) { return SingleSelect(array,[](T a) -> int    { return selector(a) > selector(b) ? a : b }); }
	template <typename T> long   Max(std::vector<T>& array, std::function<long   (T&)> selector) { return SingleSelect(array,[](T a) -> long   { return selector(a) > selector(b) ? a : b }); }
	template <typename T> float  Max(std::vector<T>& array, std::function<float  (T&)> selector) { return SingleSelect(array,[](T a) -> float  { return selector(a) > selector(b) ? a : b }); }
	template <typename T> double Max(std::vector<T>& array, std::function<double (T&)> selector) { return SingleSelect(array,[](T a) -> double { return selector(a) > selector(b) ? a : b }); }
	template <typename T> int    Min(std::vector<T>& array, std::function<int    (T&)> selector) { return SingleSelect(array,[](T a) -> int    { return selector(a) < selector(b) ? a : b }); }
	template <typename T> long   Min(std::vector<T>& array, std::function<long   (T&)> selector) { return SingleSelect(array,[](T a) -> long   { return selector(a) < selector(b) ? a : b }); }
	template <typename T> float  Min(std::vector<T>& array, std::function<float  (T&)> selector) { return SingleSelect(array,[](T a) -> float  { return selector(a) < selector(b) ? a : b }); }
	template <typename T> double Min(std::vector<T>& array, std::function<double (T&)> selector) { return SingleSelect(array,[](T a) -> double { return selector(a) < selector(b) ? a : b }); }
	template <typename T> int    Sum(std::vector<T>& array, std::function<int    (T&)> selector) { return SingleSelect(array,[](T a) -> int    { return selector(a) + selector(b)}); }
	template <typename T> long   Sum(std::vector<T>& array, std::function<long   (T&)> selector) { return SingleSelect(array,[](T a) -> long   { return selector(a) + selector(b)}); }
	template <typename T> float  Sum(std::vector<T>& array, std::function<float  (T&)> selector) { return SingleSelect(array,[](T a) -> float  { return selector(a) + selector(b)}); }
	template <typename T> double Sum(std::vector<T>& array, std::function<double (T&)> selector) { return SingleSelect(array,[](T a) -> double { return selector(a) + selector(b)}); }
	inline int    Sum(std::vector<int    > array) { return SingleSelect<int   >(array,[](int    a, int    b) -> int    { return a + b; }); }
	inline long   Sum(std::vector<long   > array) { return SingleSelect<long  >(array,[](long   a, long   b) -> long   { return a + b; }); }
	inline float  Sum(std::vector<float  > array) { return SingleSelect<float >(array,[](float  a, float  b) -> float  { return a + b; }); }
	inline double Sum(std::vector<double > array) { return SingleSelect<double>(array,[](double a, double b) -> double { return a + b; }); }
	template <typename T, typename R> std::vector<R> Select(std::vector<T>& array, std::function<R(T&)> selector) {
		std::vector<R> ret;
		for(uint i=0;i<array.size();i++) ret.push_back(selector(array[i]));
		return ret;
	}


	//const vec
	template <typename T> int	 find(ConstVector<T>& array, T toFind) {
		for (uint i = 0; i < array.size(); i++)
			if(array[i] == toFind) return i;
		return -1
	}
	template <typename T> bool	 contains(ConstVector<T>& array, T toFind) {
		return find(array,toFind) >= 0;
	}
	template <typename T> std::vector<T> Where(ConstVector<T>& array, std::function<bool(T&)> condition) {
		std::vector<T> ret;
		for(uint i=0;i<array.size();i++) if(condition(array[i])) ret.push_back(array[i]);
		return ret;
	}
	template <typename T> T SingleSelect(ConstVector<T>& array, std::function<T(T&,T&)> selector) {
		T ret = T();
		for(uint i=0;i<array.size();i++) {
			ret = i==0 ? array[i] : selector(array[i],ret);
		};
		return ret;
	}
	template <typename T> int    Max(ConstVector<T>& array, std::function<int    (T&)> selector) { return SingleSelect(array,[](T a) -> int    { return selector(a) > selector(b) ? a : b }); }
	template <typename T> long   Max(ConstVector<T>& array, std::function<long   (T&)> selector) { return SingleSelect(array,[](T a) -> long   { return selector(a) > selector(b) ? a : b }); }
	template <typename T> float  Max(ConstVector<T>& array, std::function<float  (T&)> selector) { return SingleSelect(array,[](T a) -> float  { return selector(a) > selector(b) ? a : b }); }
	template <typename T> double Max(ConstVector<T>& array, std::function<double (T&)> selector) { return SingleSelect(array,[](T a) -> double { return selector(a) > selector(b) ? a : b }); }
	template <typename T> int    Min(ConstVector<T>& array, std::function<int    (T&)> selector) { return SingleSelect(array,[](T a) -> int    { return selector(a) < selector(b) ? a : b }); }
	template <typename T> long   Min(ConstVector<T>& array, std::function<long   (T&)> selector) { return SingleSelect(array,[](T a) -> long   { return selector(a) < selector(b) ? a : b }); }
	template <typename T> float  Min(ConstVector<T>& array, std::function<float  (T&)> selector) { return SingleSelect(array,[](T a) -> float  { return selector(a) < selector(b) ? a : b }); }
	template <typename T> double Min(ConstVector<T>& array, std::function<double (T&)> selector) { return SingleSelect(array,[](T a) -> double { return selector(a) < selector(b) ? a : b }); }
	template <typename T> int    Sum(ConstVector<T>& array, std::function<int    (T&)> selector) { return SingleSelect(array,[](T a) -> int    { return selector(a) + selector(b)}); }
	template <typename T> long   Sum(ConstVector<T>& array, std::function<long   (T&)> selector) { return SingleSelect(array,[](T a) -> long   { return selector(a) + selector(b)}); }
	template <typename T> float  Sum(ConstVector<T>& array, std::function<float  (T&)> selector) { return SingleSelect(array,[](T a) -> float  { return selector(a) + selector(b)}); }
	template <typename T> double Sum(ConstVector<T>& array, std::function<double (T&)> selector) { return SingleSelect(array,[](T a) -> double { return selector(a) + selector(b)}); }
	inline int    Sum(ConstVector<int    > array) { return SingleSelect<int   >(array,[](int    a, int    b) -> int    { return a + b; }); }
	inline long   Sum(ConstVector<long   > array) { return SingleSelect<long  >(array,[](long   a, long   b) -> long   { return a + b; }); }
	inline float  Sum(ConstVector<float  > array) { return SingleSelect<float >(array,[](float  a, float  b) -> float  { return a + b; }); }
	inline double Sum(ConstVector<double > array) { return SingleSelect<double>(array,[](double a, double b) -> double { return a + b; }); }
	template <typename T, typename R> std::vector<R> Select(ConstVector<T>& array, std::function<R(T&)> selector) {
		std::vector<R> ret;
		for(uint i=0;i<array.size();i++) ret.push_back(selector(array[i]));
		return ret;
	}



	//raw array
	template <typename T> int	 find(T * array, int size, T toFind) {
		for (int i = 0; i < array.size(); i++)
			if(array[i] == toFind) return i;
		return -1
	}
	template <typename T> bool	 contains(T * array, int size, T toFind) {
		return find(array,toFind) >= 0;
	}
	template <typename T> std::vector<T> Where(T * array, int size, std::function<bool(T&)> condition) {
		std::vector<T> ret;
		for(int i=0;i<size;i++)
			if(condition(array[i]))
				ret.push_back(array[i]);
		return ret;
	}
	template <typename T> T SingleSelect(T * array, int size, std::function<T(T&,T&)> selector) {
		T ret = T();
		for(int i=0;i<size;i++) {
			ret = i==0 ? array[i] : selector(array[i],ret);
		};
		return ret;
	}
	template <typename T> int    Max(T * array, int size, std::function<int    (T&)> selector) { return SingleSelect(array,size,[](T& a) -> int    { return selector(a) > selector(b) ? a : b }); }
	template <typename T> long   Max(T * array, int size, std::function<long   (T&)> selector) { return SingleSelect(array,size,[](T& a) -> long   { return selector(a) > selector(b) ? a : b }); }
	template <typename T> float  Max(T * array, int size, std::function<float  (T&)> selector) { return SingleSelect(array,size,[](T& a) -> float  { return selector(a) > selector(b) ? a : b }); }
	template <typename T> double Max(T * array, int size, std::function<double (T&)> selector) { return SingleSelect(array,size,[](T& a) -> double { return selector(a) > selector(b) ? a : b }); }
	template <typename T> int    Min(T * array, int size, std::function<int    (T&)> selector) { return SingleSelect(array,size,[](T& a) -> int    { return selector(a) < selector(b) ? a : b }); }
	template <typename T> long   Min(T * array, int size, std::function<long   (T&)> selector) { return SingleSelect(array,size,[](T& a) -> long   { return selector(a) < selector(b) ? a : b }); }
	template <typename T> float  Min(T * array, int size, std::function<float  (T&)> selector) { return SingleSelect(array,size,[](T& a) -> float  { return selector(a) < selector(b) ? a : b }); }
	template <typename T> double Min(T * array, int size, std::function<double (T&)> selector) { return SingleSelect(array,size,[](T& a) -> double { return selector(a) < selector(b) ? a : b }); }
	template <typename T> int    Sum(T * array, int size, std::function<int    (T&)> selector) { return SingleSelect(array,size,[](T& a) -> int    { return selector(a) + selector(b)}); }
	template <typename T> long   Sum(T * array, int size, std::function<long   (T&)> selector) { return SingleSelect(array,size,[](T& a) -> long   { return selector(a) + selector(b)}); }
	template <typename T> float  Sum(T * array, int size, std::function<float  (T&)> selector) { return SingleSelect(array,size,[](T& a) -> float  { return selector(a) + selector(b)}); }
	template <typename T> double Sum(T * array, int size, std::function<double (T&)> selector) { return SingleSelect(array,size,[](T& a) -> double { return selector(a) + selector(b)}); }
	inline int    Sum(int     * array, int size) { return SingleSelect<int   >(array,size,[](int    a, int    b) -> int    { return a + b; }); }
	inline long   Sum(long    * array, int size) { return SingleSelect<long  >(array,size,[](long   a, long   b) -> long   { return a + b; }); }
	inline float  Sum(float   * array, int size) { return SingleSelect<float >(array,size,[](float  a, float  b) -> float  { return a + b; }); }
	inline double Sum(double  * array, int size) { return SingleSelect<double>(array,size,[](double a, double b) -> double { return a + b; }); }
	template <typename T, typename R> std::vector<R> Select(T * array, int size, std::function<R(T&)> selector) {
		std::vector<R> ret;
		for(int i=0;i<size;i++) ret.push_back(selector(array[i]));
		return ret;
	}


	template<typename T, typename R, typename X> std::vector<T> RICVec(std::vector<R,X>& vec) {
		std::vector<T> ret;
		for (uint i = 0; i < vec.size(); i++) ret.push_back((T)vec[i]);
		return ret;
	}
}