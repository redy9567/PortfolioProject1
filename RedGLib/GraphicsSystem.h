#pragma once
#include <Windows.h>
#include <d2d1.h>

class GraphicsBuffer;

class GraphicsSystem
{

public:
	friend class GraphicsBuffer;

	GraphicsSystem();
	~GraphicsSystem();

	void init();
	void cleanup();
	bool update();

	void flip();
	void drawEllipse();
	void drawGraphicsBuffer(GraphicsBuffer* gb, float locX, float locY, float scale = 1.0f);

	static void initInstance();
	static GraphicsSystem* getInstance();
	static void cleanupInstance();

private:
	bool mIsInit;
	ID2D1Factory* pFactory;
	ID2D1HwndRenderTarget* pRenderTarget;
	ID2D1SolidColorBrush* pBrush;
	D2D1_ELLIPSE ellipse;
	HWND windowHandle;

	static GraphicsSystem* mspInstance;

	int __stdcall OpenWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance/*, PSTR lpCmdLine*/, INT nCmdShow);
	
	HRESULT CreateGraphicsResources();
	void DiscardGraphicsResources();
	void CalculateLayout();
	//Window Handling
	static LRESULT __stdcall WindowsProc(HWND hwnd, UINT umsg, WPARAM wParam, LPARAM lParam);
	void OnSize(HWND hwnd, UINT flag, int width, int height);
	void OnPaint(HWND hwnd);
	void PromptExit();
	void CreateFactory();

};



