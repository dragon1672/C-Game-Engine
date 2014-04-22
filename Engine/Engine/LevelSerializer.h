#pragma once

#include "NodeManager.h"
#include "LevelFileHeader.h"
#include <fstream>
#include "LevelFileHeader.h"
#include "GameNode.h"
#include "GameNodeConnection.h"

typedef char myByte;

#define RIC_BYTE(a) reinterpret_cast<myByte*>(&a), sizeof(a)
#define RIC(type,value) reinterpret_cast<type>(value)
#define POINTER_FIX(toFix, finalType, source) toFix = RIC(finalType,source + (int)toFix)

class LevelSerializer {
public:
	//must be deleted
	static myByte * loadFile(const char * filename, int& sizeResult) {
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
	static void writeFile(const char * levelBinary, NodeManager& nodeManager, const char * outfile) {
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
		int currentConnetionOffset = myHeader.startOfConnectionData; // tracks previous connetion offsets to calculate offset

		for (uint i = 0; i < nodeManager.nodes.size(); i++)
		{
			/* ----GameNode----						// total Size: 20
				glm::vec3 pos;						// size: 4*3
				uint numOfConnections;				// size: 4
				GameNodeConnection * connections;	// size: 4
			*/
			out.write(RIC_BYTE((nodeManager.nodes[i]->pos)));			//WRITTING:	(1/3) POS
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
				int nodeOffsetInFile = (id >= 0) ? myHeader.startOfNodeData + id * sizeof(GameNode) : myHeader.endOfFile;
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
	//returns level data
	static myByte * readFile(const char * filename, NodeManager& nodeManager) {
		int fileSize;
		myByte * file = loadFile(filename,fileSize);
		LevelFileHeader * header = RIC(LevelFileHeader *, file);
		myByte * levelBinary = file + header->startOfBinaryData;

		GameNode * gameNodes = RIC(GameNode *,file + header->startOfNodeData);
		for (uint i = 0; i < header->numOfNodes; i++)
		{
			POINTER_FIX(gameNodes[i].connections,GameNodeConnection *,file);
			for (int j = 0; j < gameNodes[i].numOfConnections; j++)
			{
				POINTER_FIX(gameNodes[i].connections[j].to,GameNode *,file);
			}
		}

		nodeManager.importNodesAndConnections(gameNodes,header->numOfNodes);

		return levelBinary;
	}
};