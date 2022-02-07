#pragma comment(lib, "d2d1")
#include "GraphicsSystem.h"
#include <assert.h>

GraphicsSystem* GraphicsSystem::mspInstance = nullptr;

void GraphicsSystem::initInstance()
{
	if (mspInstance == nullptr)
	{
		mspInstance = new GraphicsSystem();
	}
}

void GraphicsSystem::cleanupInstance()
{
	if (mspInstance)
	{
		mspInstance->cleanup();
		delete mspInstance;
		mspInstance = nullptr;
	}
}

GraphicsSystem* GraphicsSystem::getInstance()
{
	return mspInstance;
}

GraphicsSystem::GraphicsSystem()
{
	mIsInit = false;
	pFactory = nullptr;
}

GraphicsSystem::~GraphicsSystem()
{
	if(mIsInit)
		cleanup();
}

void GraphicsSystem::init()
{
	if (!mIsInit)
	{
		OpenWindow(GetModuleHandle(NULL), 0, 1);
		CreateGraphicsResources();
		pRenderTarget->BeginDraw();
		mIsInit = true;
	}
	
}

void GraphicsSystem::cleanup()
{
	if (mIsInit)
	{
		pRenderTarget->EndDraw();
		DiscardGraphicsResources();
		PostQuitMessage(0);
		mIsInit = false;
	}
}

int __stdcall GraphicsSystem::OpenWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance/*, PSTR lpCmdLine*/, INT nCmdShow)
{
	const wchar_t CLASS_NAME[] = L"Sample Window Class";

	WNDCLASS wc = { };

	wc.lpfnWndProc = WindowsProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;

	RegisterClass(&wc);

	windowHandle = CreateWindowEx(
		0, //Optional Window Styles
		CLASS_NAME, //Window Class
		L"Welcome to the world of programming!", //Window Text
		WS_OVERLAPPEDWINDOW, //Window Style

		//Size and Position
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

		NULL, //Parent Window
		NULL, //Menu
		hInstance, //Instance Handle
		NULL //Additional Application Data
	);

	assert(windowHandle);

	ShowWindow(windowHandle, nCmdShow);

	return 0;
}

LRESULT __stdcall GraphicsSystem::WindowsProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		mspInstance->CreateFactory();
		break;
	case WM_SIZE:
	{
		int width = LOWORD(lParam);
		int height = HIWORD(lParam);

		mspInstance->OnSize(hwnd, (UINT)wParam, width, height);
		break;
	}
	case WM_PAINT:
		//mspInstance->OnPaint(hwnd);
		break;

	case WM_CLOSE:
		mspInstance->PromptExit();
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

HRESULT GraphicsSystem::CreateGraphicsResources()
{
	HRESULT endResult = S_OK;
	if (pRenderTarget == nullptr)
	{
		RECT area;
		GetClientRect(windowHandle, &area);

		D2D1_SIZE_U size = D2D1::SizeU(area.right, area.bottom);

		endResult = pFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(windowHandle, size),
			&pRenderTarget);

		if (SUCCEEDED(endResult))
		{
			const D2D1_COLOR_F color = D2D1::ColorF(1.0f, 0.5f, 0.5f);
			endResult = pRenderTarget->CreateSolidColorBrush(color, &pBrush);

			if (SUCCEEDED(endResult))
			{
				CalculateLayout();
			}
		}
	}
	return endResult;
}

void GraphicsSystem::CalculateLayout()
{
	if (pRenderTarget != NULL)
	{
		D2D1_SIZE_F size = pRenderTarget->GetSize();
		const float x = size.width / 2;
		const float y = size.height / 2;
		const float radius = min(x, y);
		ellipse = D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius);
	}
}

void GraphicsSystem::DiscardGraphicsResources()
{
	if (pRenderTarget)
	{
		pRenderTarget->Release();
		pRenderTarget = nullptr;
	}
		

	if (pBrush)
	{
		pBrush->Release();
		pBrush = nullptr;
	}
}

void GraphicsSystem::CreateFactory()
{
	D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory);
}


void GraphicsSystem::OnSize(HWND hwnd, UINT flag, int width, int height)
{

}

void GraphicsSystem::OnPaint(HWND hwnd)
{
	HRESULT endResult = CreateGraphicsResources();
	if (SUCCEEDED(endResult))
	{
		PAINTSTRUCT ps;
		BeginPaint(hwnd, &ps);

		pRenderTarget->BeginDraw();

		pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::SkyBlue));
		pRenderTarget->FillEllipse(ellipse, pBrush);

		endResult = pRenderTarget->EndDraw();
		if (FAILED(endResult) || endResult == D2DERR_RECREATE_TARGET)
		{
			DiscardGraphicsResources();
		}
		EndPaint(hwnd, &ps);
	}
}

void GraphicsSystem::PromptExit()
{
	if (MessageBox(windowHandle, L"REALLY QUIT??", L"you did it!", MB_OKCANCEL) == IDOK)
	{
		DestroyWindow(windowHandle);
		windowHandle = NULL;
	}
}

bool GraphicsSystem::update()
{
	if (!windowHandle)
		return false;

	MSG msg;

	while (PeekMessage(&msg, windowHandle, 0, 0, PM_REMOVE))
	{

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return true;
}

void GraphicsSystem::flip()
{
	pRenderTarget->EndDraw();
	pRenderTarget->BeginDraw();
}

void GraphicsSystem::drawEllipse()
{
	PAINTSTRUCT ps;
	BeginPaint(windowHandle, &ps);

	pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::SkyBlue));
	pRenderTarget->FillEllipse(ellipse, pBrush);

	EndPaint(windowHandle, &ps);
}