#include "Resource.h"
#include "Locator.h"
#include <WICTextureLoader.h>


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

bool Resource::loadTexture(ID3D11ShaderResourceView** SRV, ID3D11Resource** texture, const wchar_t* filename)
{
	bool success = true;
	HRESULT hr = DirectX::CreateWICTextureFromFile(Locator::getD3D()->GETgDevice(), filename, texture, SRV);
	if (FAILED(hr)) {
		success = false;
		assert(FAILED(hr) && "Failed to create texture from file - Resource");
	}
	return success;
}

bool Resource::load(const char * modelFilename, const wchar_t* texFilename, RESOURCETYPE type, size_t ID)
{
	return false;
}

bool Resource::load(ObjectData objData, RESOURCETYPE type, size_t ID)
{
	return false;
}

bool Resource::load(const wchar_t* filename, RESOURCETYPE type, size_t ID)
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

/*void ResourceManager::initTexQuad()
{
	std::array<Vertex, 4> vertices;

	vertices[0].position = Vector3(0.0f, 1.0f, 0.0f);
	vertices[1].position = Vector3(0.0f, 0.0f, 0.0f);
	vertices[2].position = Vector3(1.0f, 1.0f, 0.0f);
	vertices[3].position = Vector3(1.0f, 0.0f, 0.0f);

	vertices[0].normal = Vector3(0.0f, 0.0f, -1.0f);
	vertices[1].normal = Vector3(0.0f, 0.0f, -1.0f);
	vertices[2].normal = Vector3(0.0f, 0.0f, -1.0f);
	vertices[3].normal = Vector3(0.0f, 0.0f, -1.0f);

	vertices[0].texCoords = Vector2(0.0f, 1.0f);
	vertices[1].texCoords = Vector2(0.0f, 0.0f);
	vertices[2].texCoords = Vector2(1.0f, 1.0f);
	vertices[3].texCoords = Vector2(1.0f, 0.0f);

	size_t indices[] = {
		0, 1, 2,
		2, 1, 3,
	};

	ObjectData data = ObjectData(RESOURCEOBJECT::ID::TEXQUAD, vertices.data(), indices, vertices.size(), 6, sizeof(Vertex), 0, 0);
	this->addResource(data);
	}*/