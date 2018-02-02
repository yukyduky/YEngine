#include "Resource.h"
#include "Locator.h"
#include "WICTextureLoader.h"


bool Resource::createVertexBuffer(ID3D11Buffer ** gVertexBuffer, void * v, size_t & stride, size_t & offset, size_t numVertices)
{
	bool success = true;
	// Describe the vertex buffer
	D3D11_BUFFER_DESC vertexBufferDesc;
	memset(&vertexBufferDesc, 0, sizeof(D3D11_BUFFER_DESC));
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = stride * numVertices;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;

	// Set the vertex buffer data
	D3D11_SUBRESOURCE_DATA vertexData;
	memset(&vertexData, 0, sizeof(vertexData));
	vertexData.pSysMem = v;

	HRESULT hr = Locator::getD3D()->GETgDevice()->CreateBuffer(&vertexBufferDesc, &vertexData, gVertexBuffer);
	if (FAILED(hr)) {
		assert(FAILED(hr) && "Resource - Failed to create vertex buffer");
		success = false;
	}
	return success;
}

bool Resource::createIndexBuffer(ID3D11Buffer ** gIndexBuffer, void * data, size_t & numIndices)
{
	bool success = true;
	// Describe the index buffer
	D3D11_BUFFER_DESC indexBufferDesc;
	memset(&indexBufferDesc, 0, sizeof(indexBufferDesc));

	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(size_t) * numIndices;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;

	// Set the index buffer data
	D3D11_SUBRESOURCE_DATA indexData;

	indexData.pSysMem = data;
	HRESULT hr = Locator::getD3D()->GETgDevice()->CreateBuffer(&indexBufferDesc, &indexData, gIndexBuffer);
	if (FAILED(hr)) {
		assert(FAILED(hr) && "Resource - Failed to create index buffer");
		success = false;
	}
	return success;
}

bool Resource::createBuffers(ID3D11Buffer ** vBuffer, ID3D11Buffer ** iBuffer, void * vertices, void * indices, size_t numVertices, size_t numIndices, size_t stride, size_t offset)
{
	bool allLoaded = false;
	bool vLoaded = true;
	bool iLoaded = true;

	vLoaded = this->createVertexBuffer(vBuffer, vertices, stride, offset, numVertices);

	iLoaded = this->createIndexBuffer(iBuffer, indices, numIndices);

	if (vLoaded && iLoaded) {
		allLoaded = true;
	}

	return allLoaded;
}

bool Resource::loadTexture(ID3D11ShaderResourceView** SRV, ID3D11Resource** texture, const char* filename)
{
	//CreateWICTextureFromFile(Locator::getD3D()->GETgDevice(), filename, texture, SRV);
	return false;
}

bool Resource::load(const char * modelFilename, const char* texFilename, RESOURCETYPE type, size_t ID)
{
	return false;
}

bool Resource::load(ObjectData objData, RESOURCETYPE type, size_t ID)
{
	return false;
}

bool Resource::isLoaded()
{
	return this->loaded;
}

RESOURCETYPE Resource::getResourceType()
{
	return this->type;
}

size_t Resource::getID()
{
	return this->ID;
}
