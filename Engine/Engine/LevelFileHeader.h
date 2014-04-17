#pragma once

#include "unsigned.h"

struct LevelFileHeader {
	uint numOfNodes;
	uint numOfConnections;
	uint startOfBinaryData;		// header
	uint startOfNodeData;		// header + sizeOfFile
	uint startOfConnectionData;	// start of node + numOfNodes * sizeof(GameNode)
	uint endOfFile;				// start of connections + numOfConnetions * sizeof(GameConnetion)
};