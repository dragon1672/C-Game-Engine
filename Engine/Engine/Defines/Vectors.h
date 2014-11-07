#define CLEAR_VECTOR(meVector) while(meVector.size() != 0) { \
	meVector.pop_back();                                 \
	}
#define CLEAR_VECTOR_WITH_CALL(meVector,method)  \
	while(meVector.size() != 0) {                \
	meVector.back()->method(); \
	meVector.pop_back();                     \
	}

#define DELETE_VECTOR(meVector) while(meVector.size() != 0) { \
		delete meVector.back();                \
		meVector.pop_back();                                 \
	}
#define DELETE_VECTOR_WITH_CALL(meVector,method)  \
	while(meVector.size() != 0) {                \
		meVector.back()->method(); \
		delete meVector.back();    \
		meVector.pop_back();                     \
	}

//example with vector<int> (myVector, == 4)
//example with vector<class> (myVector,.hasPie)
#define VECTOR_REMOVE_CONDITION(vec,condition)\
	for (int i = vec.size()-1; i >= 0; i--) { \
		if(vec[i]##condition##) {			  \
		auto tmp = vec[i];					  \
		vec[i] = vec.back();				  \
		vec.back() = tmp;					  \
		vec.pop_back();						  \
		}									  \
	}