#include "Object.h"
#include <cassert>


bool Object::load(ObjectData objData, RESOURCETYPE type, size_t ID)
{
	this->loaded = false;

	ID3D11Buffer* vBuffer;
	ID3D11Buffer* iBuffer;
	this->loaded = this->createBuffers(&vBuffer, &iBuffer, objData.vertices, objData.indices, objData.numVertices, objData.numIndices, objData.stride, objData.offset);

	if (this->loaded) {
		this->type = type;
		this->ID = ID;
		this->data = VertexData(vBuffer, iBuffer, objData.numVertices, objData.numIndices, objData.numFaces, objData.stride, objData.offset);
	}

	return this->loaded;
}

void Object::unload()
{
	this->data.vBuffer->Release();
	this->data.iBuffer->Release();
	this->loaded = false;
}

bool Object::reload()
{
	return false; // this->loaded = this->createBuffers(&this->data.vBuffer, &this->data.iBuffer, vertices, indices, this->data.numVertices, this->data.numIndices, this->data.stride, this->data.offset);
}

VertexData Object::getRenderData()
{
	return this->data;
}
