#pragma once
#include <string>
#include <Windows.h>
#include <d2d1.h>
#include <wincodec.h>

class GraphicsBuffer
{
public:
	GraphicsBuffer(std::string filepath);
	~GraphicsBuffer();

private:
	GraphicsBuffer() = delete;

	

};
