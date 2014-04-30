#pragma once

#include "NodeManager.h"
#include "LevelFileHeader.h"
#include <fstream>
#include "LevelFileHeader.h"
#include "GameNode.h"
#include "GameNodeConnection.h"
#include "ExportHeader.h"

typedef char myByte;

namespace LevelSerializer {
	//must be deleted
	ENGINE_SHARED myByte * loadFile(const char * filename, int& sizeResult);
	ENGINE_SHARED void     writeFile(const char * levelBinary, NodeManager& nodeManager, const char * outfile);
	//returns level data
	ENGINE_SHARED myByte * readFile(const char * filename, NodeManager& nodeManager);
	ENGINE_SHARED void     readFile(const char * filename, myByte*& out_levelBinary, GameNode*& out_GameNodes, uint& out_numOfNodes);
}