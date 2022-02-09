#pragma once
#include <string>
#include <Windows.h>
#include <d2d1.h>
#include <d2d1_1.h>
#include <d3d11.h>
#include <wincodec.h>

class GraphicsBuffer
{
public:
	friend class GraphicsSystem;

	GraphicsBuffer(LPCWSTR filepath);
	~GraphicsBuffer();

private:
	GraphicsBuffer() = delete;

	//ID2D1Bitmap mBitmap;
	IWICImagingFactory* mpIWICFactory;
	IWICFormatConverter* mpConvertedSourceBitmap;
	ID2D1Bitmap* mpD2DBitmap;

};
