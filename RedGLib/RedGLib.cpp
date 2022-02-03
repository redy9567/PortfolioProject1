#include <Windows.h>
#include <assert.h>

LRESULT __stdcall WindowsProc(HWND hwnd, UINT umsg, WPARAM wParam, LPARAM lParam);

void OnSize(HWND hwnd, UINT flag, int width, int height);

void OnPaint(HWND hwnd);
void PromptExit(HWND hwnd);

int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
{
	const wchar_t CLASS_NAME[] = L"Sample Window Class";

	WNDCLASS wc = { };

	wc.lpfnWndProc = WindowsProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;

	RegisterClass(&wc);

	HWND hwnd = CreateWindowEx(
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

	assert(hwnd);

	ShowWindow(hwnd, nCmdShow);

	MSG msg;

	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT __stdcall WindowsProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_SIZE:
	{
		int width = LOWORD(lParam);
		int height = HIWORD(lParam);

		OnSize(hwnd, (UINT)wParam, width, height);
		break;
	}
	case WM_PAINT:
		OnPaint(hwnd);
		break;

	case WM_CLOSE:
		PromptExit(hwnd);
		return 0;
		
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void OnSize(HWND hwnd, UINT flag, int width, int height)
{

}

void OnPaint(HWND hwnd)
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hwnd, &ps);

	FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
	
	EndPaint(hwnd, &ps);
}

void PromptExit(HWND hwnd)
{
	if (MessageBox(hwnd, L"REALLY QUIT??", L"get rekt kid", MB_OKCANCEL) == IDOK)
	{
		DestroyWindow(hwnd);
	}
}