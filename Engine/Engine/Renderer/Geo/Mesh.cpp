#include "Mesh.h"

void Mesh::updateMinAndMax()
{
	for (uint i = 0; i < verts.size(); i++) {
		min.x = i==0 || verts[i].pos.x < min.x ? verts[i].pos.x : min.x;
		min.x = i==0 || verts[i].pos.y < min.y ? verts[i].pos.y : min.y;
		max.x = i==0 || verts[i].pos.x < max.x ? verts[i].pos.x : max.x;
		max.x = i==0 || verts[i].pos.y < max.y ? verts[i].pos.y : max.y;
	}
}

void Mesh::passToHardware()
{
	geo.init(sizeof(Vert),(const void*)&verts[0],verts.size(),&indices[0],indices.size(),3);
	geo.addStreamedParameters(Vert().getAtribs(),Vert().getNumOfAtribs());
}
