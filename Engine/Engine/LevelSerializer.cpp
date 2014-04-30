#include "LevelSerializer.h"

#define RIC_BYTE(a) reinterpret_cast<myByte*>(&a), sizeof(a)
#define RIC(type,value) reinterpret_cast<type>(value)
#define POINTER_FIX(toFix, finalType, source) toFix = RIC(finalType,RIC(myByte*,source) + (int)toFix)

myByte * LevelSerializer::loadFile (const char * filename, int& sizeResult) {
	std::ifstream input( filename , std::ios::binary | std::ios::in);
	assert(input.good()); 
	input.seekg(0, std::ios::end);
	sizeResult = (int)input.tellg();
	input.seekg(0, std::ios::beg);

	myByte * bytes = new myByte[sizeResult];
	input.read(bytes, sizeResult);
	input.close();

	return bytes;
}
void     LevelSerializer::writeFile(const char * levelBinary, NodeManager& nodeManager, const char * outfile) {
	LevelFileHeader myHeader;

	int sizeOfFile;
	myByte * levelObject = loadFile(levelBinary,sizeOfFile);

	myHeader.numOfNodes            = nodeManager.nodes.size();
	myHeader.numOfConnections      = nodeManager.numOfConnections;
	myHeader.startOfBinaryData     = sizeof(myHeader);
	myHeader.startOfNodeData       = myHeader.startOfBinaryData     + sizeOfFile;
	myHeader.startOfConnectionData = myHeader.startOfNodeData       + myHeader.numOfNodes       * sizeof(GameNode);
	myHeader.endOfFile             = myHeader.startOfConnectionData + myHeader.numOfConnections * sizeof(GameNodeConnection);

	std::ofstream out(outfile, std::ios::binary );

	out.write(RIC_BYTE(myHeader)); // write header 

	out.write(RIC(myByte*, levelObject),sizeOfFile); // write level binary data
	delete levelObject; // cleaning up

	std::vector<EditorNodeConnection> allConnetions; // save when scanning nodes to save easier
	int currentConnetionOffset = myHeader.startOfConnectionData - myHeader.startOfNodeData; // tracks previous connetion offsets to calculate offset

	for (uint i = 0; i < nodeManager.nodes.size(); i++)
	{
		/* ----GameNode----						// total Size: 20
			glm::vec3 pos;						// size: 4*3
			uint numOfConnections;				// size: 4
			GameNodeConnection * connections;	// size: 4
		*/
		out.write(RIC_BYTE((nodeManager.nodes[i]->pos)));				//WRITTING:	(1/3) POS
		uint numOfConnections = nodeManager.nodes[i]->connections.size();
		out.write(RIC_BYTE(numOfConnections));							//WRITTING: (2/3) numOfConnections
			
		out.write(RIC_BYTE(currentConnetionOffset));					//WRITTING: (3/3) Connection File Pointer

		currentConnetionOffset += nodeManager.nodes[i]->connections.size() * sizeof(GameNodeConnection); // update with size of current node's connections

		for (uint j = 0; j < nodeManager.nodes[i]->connections.size(); j++) // adding connection data
		{
			/* ----GameNodeConnection----	// totalSize: 8
				GameNode * to;				// size: 4
				float cost;					// size: 4
			*/
			EditorNodeConnection currentConnection = *(nodeManager.nodes[i]->connections[j]); // copy data
			int id = nodeManager.getNodeId(currentConnection.to);
			int nodeOffsetInFile = (id >= 0) ? id * sizeof(GameNode) : -1;
			currentConnection.to = reinterpret_cast<EditorNode*>(nodeOffsetInFile); // change pointer to point in file
			allConnetions.push_back(currentConnection);
		}
	}
	for (uint i = 0; i < allConnetions.size(); i++)
	{
		/* ----GameNodeConnection----	// totalSize: 8
			GameNode * to;				// size: 4
			float cost;					// size: 4
		*/
		out.write(RIC_BYTE(allConnetions[i].to)  );	//WRITTING: (1/2) pointer
		out.write(RIC_BYTE(allConnetions[i].cost));	//WRITTING: (2/2) float cost
	}
	out.close();
}
myByte * LevelSerializer::readFile (const char * filename, NodeManager& nodeManager) {
	myByte* levelBinary;
	GameNode * gameNodes;
	uint numOfNodes;

	readFile(filename,levelBinary,gameNodes,numOfNodes);

	nodeManager.importNodesAndConnections(gameNodes,numOfNodes);

	return levelBinary;
}
void     LevelSerializer::readFile (const char * filename, myByte*& out_levelBinary, GameNode*& out_GameNodes, uint& out_numOfNodes) {
	std::ifstream input( filename , std::ios::binary | std::ios::in);
	assert(input.good()); 
	input.seekg(0, std::ios::end);
	int fileSize = (int)input.tellg();
	input.seekg(0, std::ios::beg);

	LevelFileHeader meHeader;
	input.read(RIC_BYTE(meHeader)); // read header

	int levelSize = meHeader.startOfNodeData - meHeader.startOfBinaryData; // because node data is right after node data
	out_levelBinary = new myByte[levelSize];
	input.read(out_levelBinary,levelSize);

	out_numOfNodes = meHeader.numOfNodes;
	int nodeAndConnectionSize = meHeader.numOfNodes * sizeof(GameNode) + meHeader.numOfConnections * sizeof(GameNodeConnection);
	out_GameNodes = RIC(GameNode *,new myByte[nodeAndConnectionSize]);
	input.read(RIC(myByte*,out_GameNodes),nodeAndConnectionSize);
	input.close();

	GameNodeConnection* temp = RIC(GameNodeConnection*,out_GameNodes + meHeader.numOfNodes);
	
	for (uint i = 0; i < meHeader.numOfNodes; i++)
	{
		POINTER_FIX(out_GameNodes[i].connections,GameNodeConnection *,out_GameNodes);
		for (uint j = 0; j < out_GameNodes[i].numOfConnections; j++)
		{
			POINTER_FIX(out_GameNodes[i].connections[j].to,GameNode *,out_GameNodes);
		}
	}
}

/*
void     readFile_old_First_version (const char * filename, myByte*& out_levelBinary, GameNode*& out_GameNodes, uint& out_numOfNodes) {
	int fileSize;
	myByte * file = LevelSerializer::loadFile(filename,fileSize);
	LevelFileHeader * header = RIC(LevelFileHeader *, file);
	myByte * levelBinary = file + header->startOfBinaryData;

	GameNode * gameNodes = RIC(GameNode *,file + header->startOfNodeData);
	for (uint i = 0; i < header->numOfNodes; i++)
	{
		POINTER_FIX(gameNodes[i].connections,GameNodeConnection *,file);
		for (uint j = 0; j < gameNodes[i].numOfConnections; j++)
		{
			POINTER_FIX(gameNodes[i].connections[j].to,GameNode *,file);
		}
	}
	out_GameNodes = gameNodes;
	out_numOfNodes = header->numOfNodes;
	out_levelBinary = levelBinary;
}
//*/