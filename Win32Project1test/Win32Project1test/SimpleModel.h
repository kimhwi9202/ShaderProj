#pragma once
class SimpleModel
{

private:
	struct VertexType
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 uv;
	};

private:
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount;
	ID3D11ShaderResourceView* m_texture;

public:
	SimpleModel();
	~SimpleModel();

	bool Initialize(ID3D11Device*, WCHAR* textureFilename);
	void Shutdown();
	void Render(ID3D11DeviceContext*);

	int GetIndexCount();

	ID3D11ShaderResourceView* GetTexture();

private:
	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

	bool LoadTexture(ID3D11Device*, WCHAR*);
	void ReleaseTexture();

};

