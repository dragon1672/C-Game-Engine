#pragma once
#ifndef SINGLE_KEY_MANAGER_H
#define SINGLE_KEY_MANAGER_H

#include <Windows.h>
#include <ExportHeader.h>
//adds additional ultities to make checking key presses simpler
class SingleKeyManager {
	int   toCheck;
	int   framesClicked;
	float secondsClicked;
public:
	SingleKeyManager() { ; }
	SingleKeyManager(int toCheck) {
		setToCheck(toCheck);
	}
	inline void  setToCheck(int toSet) {
		toCheck = toSet;
	}
	inline void  update(float dt) {
		if(GetAsyncKeyState( toCheck )!=0) {//if the key is being pressed
			framesClicked++;
			secondsClicked += dt;
		} else {//if the key isn't being pressed
			framesClicked  = 0;
			secondsClicked = 0;
		}
	}
	inline bool  hasBeenClicked() {
		return (framesClicked==1);
	}
	inline int   getFramesClicked() {
		return framesClicked;
	}
	inline float getSecondsClicked() {
		return secondsClicked;
	}
	inline int   getCheckedElement() {
		return toCheck;
	}
};

#endif