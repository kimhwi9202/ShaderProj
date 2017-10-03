#include "stdafx.h"
#include "MainApp.h"
#include "D3D11Device.h"
#include "SimpleCamera.h"
#include "SimpleModel.h"
#include "ColorShader.h"
#include "Input.h"



MainApp* MainApp::Instance = 0;

MainApp::MainApp()
{
	m_D3D11 = 0;
	m_Camera = 0;
	m_Model = 0;
	m_ColorShader = 0;
}


MainApp::~MainApp()
{

}

bool MainApp::Frame()
{
	bool result;


	// Render the graphics scene.
	result = Render();
	if (!result)
	{
		return false;
	}

	return true;
}

bool MainApp::Render()
{
	D3DXMATRIX viewMatrix, projectionMatrix, worldMatrix;
	bool result;
	// Clear the buffers to begin the scene.
	m_D3D11->BeginScene(0.0f, 0.f, 1.0f, 1.0f);
	

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D11->GetWorldMatrix(worldMatrix);
	m_D3D11->GetProjectionMatrix(projectionMatrix);

	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_Model->Render(m_D3D11->GetDeviceContext());

	// Render the model using the color shader.
	result = m_ColorShader->Render(m_D3D11->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_Model->GetTexture());
	if (!result)
	{
		return false;
	}



	// Present the rendered scene to the screen.
	m_D3D11->EndScene();

	return true;
}

bool MainApp::Update()
{
	m_Input->Frame();
	if (m_Input->IsEscapePressed())
		return false;
	m_Camera->Update();

	return true;
}


bool MainApp::Init(int screenWidth, int screenHeight, HWND hwnd)

{
	if (Instance = NULL)
		Instance = this;

	bool result;


	// Create the Direct3D object.
	m_D3D11 = new D3D11Device;
	if (!m_D3D11)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_D3D11->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D", L"Error", MB_OK);
		return false;
	}

	//Create Input Class
	m_Input = new Input;
	m_Input->Initialize(g_HInstance, g_hWnd, ScreenX, ScreenY);

	// Create the camera object.
	m_Camera = new SimpleCamera;
	if (!m_Camera)
	{
		return false;
	}

	// Set the initial position of the camera.
	m_Camera->SetPosition(0.0f, 0.0f, -10.0f);

	// Create the model object.
	m_Model = new SimpleModel;
	if (!m_Model)
	{
		return false;
	}

	// Initialize the model object.
	result = m_Model->Initialize(m_D3D11->GetDevice(),L"Textures/test3.png");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Create the color shader object.
	m_ColorShader = new ColorShader;
	if (!m_ColorShader)
	{
		return false;
	}

	// Initialize the color shader object.
	result = m_ColorShader->Initialize(m_D3D11->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the color shader object.", L"Error", MB_OK);
		return false;
	}



	return true;

}

void MainApp::Shutdown()
{

	// Release the color shader object.
	if (m_ColorShader)
	{
		m_ColorShader->Shutdown();
		delete m_ColorShader;
		m_ColorShader = 0;
	}

	// Release the model object.
	if (m_Model)
	{
		m_Model->Shutdown();
		delete m_Model;
		m_Model = 0;
	}

	// Release the camera object.
	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	if (m_Input)
	{
		delete m_Input;
		m_Input = 0;
	}

	if (m_D3D11)
	{
		m_D3D11->Shutdown();
		delete m_D3D11;
		m_D3D11 = 0;
	}

	return;

}

