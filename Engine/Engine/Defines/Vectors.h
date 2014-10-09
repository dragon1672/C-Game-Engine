#define CLEAR_VECTOR(meVector) while(meVector.size() != 0) { \
	meVector.pop_back();                                 \
	}
#define CLEAR_VECTOR_WITH_CALL(meVector,method)  \
	while(meVector.size() != 0) {                \
	meVector[meVector.size() - 1]->method(); \
	meVector.pop_back();                     \
	}

#define DELETE_VECTOR(meVector) while(meVector.size() != 0) { \
		delete meVector[meVector.size() - 1];                \
		meVector.pop_back();                                 \
	}
#define DELETE_VECTOR_WITH_CALL(meVector,method)  \
	while(meVector.size() != 0) {                \
		meVector[meVector.size() - 1]->method(); \
		delete meVector[meVector.size() - 1];    \
		meVector.pop_back();                     \
	}