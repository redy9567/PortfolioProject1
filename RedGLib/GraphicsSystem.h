#pragma once
#include <Windows.h>
#include <d2d1.h>

class GraphicsSystem
{

public:
	GraphicsSystem();
	~GraphicsSystem();

	void init();
	void cleanup();

	static void initInstance();
	static GraphicsSystem* getInstance();
	static void cleanupInstance();

private:
	bool mIsInit;
	ID2D1Factory* pFactory;
	ID2D1HwndRenderTarget* pRenderTarget;
	ID2D1SolidColorBrush* pBrush;
	D2D1_ELLIPSE ellipse;

	static GraphicsSystem* mspInstance;

	int __stdcall OpenWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance/*, PSTR lpCmdLine*/, INT nCmdShow);
	
	HRESULT CreateGraphicsResources(HWND hwnd);
	void DiscardGraphicsResources();
	void CalculateLayout();
	//Window Handling
	static LRESULT __stdcall WindowsProc(HWND hwnd, UINT umsg, WPARAM wParam, LPARAM lParam);
	void OnSize(HWND hwnd, UINT flag, int width, int height);
	void OnPaint(HWND hwnd);
	void PromptExit(HWND hwnd);
	void CreateFactory();

};



