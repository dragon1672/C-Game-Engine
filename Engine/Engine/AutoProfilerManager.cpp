#include "AutoProfileManager.h"
#include <iostream>
#include <fstream>

#ifdef ENABLE_PROFILING
#define SIZE_OF_ARRAY(a) (sizeof(a) / sizeof(*a))

int AutoProfileManager::numberOfProfiles = 0;
ProfileCategory AutoProfileManager::categories[MAX_CATEGORIES];


void AutoProfileManager::startup() {
	numberOfProfiles = 0;
}
void AutoProfileManager::shutdown() {
	//not currently needed
}
void AutoProfileManager::writeToFile() {
	std::ofstream profileOutput;
	profileOutput.open (PROFILE_FILE_NAME);
	//headers
	profileOutput << "name,times called,total time(ms),min Time(ms),max Time(ms),average time(ms)";
	for(int i=0; i < MAX_FRAMES_TO_MESURE; i++) {
		profileOutput << ",frame(" << i << ")";
	}
	//populating data
	for(int i=0; i < numberOfProfiles; i++) {
		profileOutput << "\n";
		//headers-----------NAME-------------------------TIMES CALLED----------------------------Total Time-----------------MIN TIME---------------------MAX TIME-----------------------------AVERAGE TIME(ms)-------------------------------//
		profileOutput << categories[i].name << "," << categories[i].timesCalled << "," << categories[i].totalTime << "," << categories[i].min << "," << categories[i].max <<  "," << categories[i].totalTime / categories[i].timesCalled;
		//in case function doesn't have max frames (like called 10 out of 50 possible)
		int frames = (MAX_FRAMES_TO_MESURE>categories[i].timesCalled)? categories[i].timesCalled : MAX_FRAMES_TO_MESURE;
		int startingIndex = categories[i].timesCalled % SIZE_OF_ARRAY(categories[i].data) - 1;
		for(int j=0; j < frames; j++) {
			int index = ( startingIndex - j ) % SIZE_OF_ARRAY(categories[i].data);
			profileOutput << "," << categories[i].data[index];
		}
	}
	profileOutput.close();
}
int AutoProfileManager::indexOfProfile(const char* description) {
	for(int i=0;i<numberOfProfiles;i++) {
		if(description == categories[i].name) return i;
	}
	return -1;
}
void AutoProfileManager::addEntry(const char* description, float time) {
	int id = indexOfProfile(description);
	if(id<0) addNewProfile(description, time);
	else addToProfile(id,time);
}
void AutoProfileManager::addToProfile(int i, float time) {
	categories[i].totalTime += time;
	int index = categories[i].timesCalled % SIZE_OF_ARRAY(categories[i].data);
	categories[i].data[index] = time;
	categories[i].timesCalled++;
	categories[i].min = ((categories[i].min>time || categories[i].min==0) && time!=0)? time : categories[i].min;
	categories[i].max = (categories[i].max<time)? time : categories[i].max;

}
void AutoProfileManager::addNewProfile(const char* description, float time) {
	categories[numberOfProfiles++].name = description;
	addToProfile(numberOfProfiles-1,time);
}
#endif