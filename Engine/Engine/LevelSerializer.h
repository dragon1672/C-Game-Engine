#pragma once

#include "NodeManager.h"
#include "LevelFileHeader.h"
#include <fstream>
#include "LevelFileHeader.h"
#include "GameNode.h"
#include "GameNodeConnection.h"

typedef char myByte;

class LevelSerializer {
public:
	//must be deleted
	static myByte * loadFile(const char * filename, int& sizeResult);
	static void writeFile(const char * levelBinary, NodeManager& nodeManager, const char * outfile);
	//returns level data
	static myByte * readFile(const char * filename, NodeManager& nodeManager);
	static void readFile(const char * filename, myByte*& out_levelBinary, GameNode*& out_GameNodes, uint& out_numOfNodes);
};