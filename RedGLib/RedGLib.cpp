#include <Windows.h>
#include <assert.h>

LRESULT __stdcall WindowsProc(HWND hwnd, UINT umsg, WPARAM wParam, LPARAM lParam);

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

	while (true)
		true;

	return 0;
}

LRESULT __stdcall WindowsProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
