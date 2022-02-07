#include "GraphicsBuffer.h"

using namespace std;

GraphicsBuffer::GraphicsBuffer(string filepath)
{
	IWICImagingFactory::CreateDecoderFromFilename();
}

GraphicsBuffer::~GraphicsBuffer()
{

}