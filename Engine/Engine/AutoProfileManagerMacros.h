#ifdef ENABLE_PROFILING//1==1 included to require ';'
	#define START_PROFILING AutoProfileManager::startup()
	#define PROFILE(a) {AutoProfile someName(a) //starting Profile
	#define END_PROFILE }1==1 //end the last Profile
	#define LOG_CURRENT_PROFILE AutoProfileManager::writeToFile()
	#define STOP_PROFILING AutoProfileManager::shutdown()
#else // filled with dummy data (still requires ';')
	#define START_PROFILING 1==1
	#define PROFILE(a) 1==1
	#define END_PROFILE 1==1
	#define LOG_CURRENT_PROFILE 1==1
	#define STOP_PROFILING 1==1
#endif