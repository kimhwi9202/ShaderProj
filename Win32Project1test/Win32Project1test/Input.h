#pragma once
class Input
{
public:
	static Input* Instance;

private:
	IDirectInput8* m_directInput;
	IDirectInputDevice8* m_keyboard;
	IDirectInputDevice8* m_mouse;


	unsigned char m_keyboardState[256];
	DIMOUSESTATE m_mouseState;

	int m_screenWidth, m_screenHeight;
	int m_mouseX, m_mouseY;
public:
	Input();
	~Input();

	bool Initialize(HINSTANCE, HWND, int, int);
	void Shutdown();
	bool Frame();

	bool IsEscapePressed();
	bool CheckKeyPressed(int Key_Code);
	void GetMouseLocation(int&, int&);

	static Input* GetInstance();

private:
	bool ReadKeyboard();
	bool ReadMouse();
	void ProcessInput();

};

