#pragma once
class D3D11Device;
class SimpleCamera;
class SimpleModel;
class ColorShader;

class MainApp
{
public:
	static MainApp* Instance;
private:
	D3D11Device* m_D3D11;
	SimpleCamera* m_Camera;
	SimpleModel* m_Model;
	ColorShader* m_ColorShader;
public:
	MainApp();
	~MainApp();

	bool Frame();
	bool Render();
	void Update();
	bool Init(int, int, HWND);
	void Shutdown();

	
};

