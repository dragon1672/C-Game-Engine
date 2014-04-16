#pragma once

#include "unsigned.h"

struct header {
	uint numOfNodes;
	uint numOfConnections;
	uint startOfBinaryData;		// 0
	uint startOfNodeData;		// numOfNodes * sizeof(GameNode)
	uint startOfConnectionData;	// numOfConnections * sizeof(GameConnection)
};