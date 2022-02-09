#include "GraphicsBuffer.h"
#include "GraphicsSystem.h"

using namespace std;

GraphicsBuffer::GraphicsBuffer(LPCWSTR filepath)
{
    HRESULT res;

    res = CoCreateInstance(
        CLSID_WICImagingFactory,
        NULL,
        CLSCTX_INPROC_SERVER,
        IID_PPV_ARGS(&mpIWICFactory)
    );

    IWICBitmapDecoder* pDecoder = NULL;

    if (SUCCEEDED(res))
    {
        
        res = mpIWICFactory->CreateDecoderFromFilename(
            filepath,
            NULL,
            GENERIC_READ,
            WICDecodeMetadataCacheOnDemand,
            &pDecoder
        );

    }

    IWICBitmapFrameDecode* pFrame = NULL;

    if (SUCCEEDED(res))
    {
        res = pDecoder->GetFrame(0, &pFrame);
    }

    if (SUCCEEDED(res))
    {
        res = mpIWICFactory->CreateFormatConverter(&mpConvertedSourceBitmap);
    }

    if (SUCCEEDED(res))
    {
        res = mpConvertedSourceBitmap->Initialize(
            pFrame,                          // Input bitmap to convert
            GUID_WICPixelFormat32bppPBGRA,   // Destination pixel format
            WICBitmapDitherTypeNone,         // Specified dither pattern
            NULL,                            // Specify a particular palette 
            0.f,                             // Alpha threshold
            WICBitmapPaletteTypeCustom       // Palette translation type
        );
    }

    if (SUCCEEDED(res))
    {
        res = GraphicsSystem::getInstance()->pRenderTarget->CreateBitmapFromWicBitmap(mpConvertedSourceBitmap, NULL, &mpD2DBitmap);
    }
}

GraphicsBuffer::~GraphicsBuffer()
{

}