#include "D3DViewPort.h"
#include "FlameUI.h"

using namespace FlameUI;
using namespace D2D1;

IDWriteTextFormat* ffmt = nullptr;
D3DViewPort::D3DViewPort(View* parent) :View(parent), d2dTex(nullptr)
{
	keyable = true;
	render.direct = true;
	if (!ffmt)
	{
		gDWFactory->CreateTextFormat(L"", NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 48, locale, &ffmt);
		ffmt->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
		ffmt->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	}
}
LRESULT D3DViewPort::OnEvent(Message msg, WPARAM wParam, LPARAM lParam)
{
	return 0;
}
#ifdef _DX12
HRESULT D3DViewPort::SetOutput(ID3D12Resource* res)
{
	auto hr = gD3D12Device->CreateSharedHandle(res, nullptr, GENERIC_ALL, nullptr, &shareHandle);
	if (hr != S_OK) return hr;
	hr = gD3D11Device->OpenSharedResource1(shareHandle, IID_PPV_ARGS(&d11Tex));
	if (hr != S_OK) return hr;
	hr = SetOutput(d11Tex);
	return hr;
}
#endif
HRESULT D3DViewPort::SetOutput(ID3D11Resource* res)
{
	if (d2dTex) d2dTex->Release();
	auto hr = res->QueryInterface(&dxgiSurface);
	if (hr != S_OK) return hr;
	hr = render.context->CreateSharedBitmap(__uuidof(IDXGISurface), dxgiSurface, &BitmapProperties(
		D2D1::PixelFormat(DXGI_FORMAT_R16G16B16A16_FLOAT, D2D1_ALPHA_MODE_PREMULTIPLIED)), &d2dTex);
	return hr;
}



void D3DViewPort::Draw()
{
	auto ctx = BeginDraw(ColorF::ColorF(ColorF::Black, 1));
	if (!dontPaint && d2dTex)
	{
		ctx->DrawBitmap(d2dTex, { 0,0,rect.width(),rect.height() });
	}
	else
	{
		ID2D1SolidColorBrush* br;
		ctx->CreateSolidColorBrush(ColorF::ColorF(ColorF::Gray), &br);
		ctx->DrawTextW(L"No Image", 8, ffmt, { 0,0,rect.width(),rect.height() }, br);
		br->Release();
	}

	EndDraw();

}
