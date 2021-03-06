#pragma once
#include "View.h"
namespace FlameUI
{
	class D3DViewPort :
		public View
	{
	private:
#ifdef _DX12
		ID3D12Resource* d12Tex;
#else

#endif
		ID3D11Resource* d11Tex;
		IDXGISurface* dxgiSurface;
		ID2D1Bitmap* d2dTex;
		HANDLE shareHandle;
	protected:
		LRESULT OnEvent(Message msg, WPARAM wParam, LPARAM lParam) override;
		void Draw() override;
	public:
		bool dontPaint = true;

		D3DViewPort(View* parent);
#ifdef _DX12
		HRESULT SetOutput(ID3D12Resource* res);
#endif
		HRESULT SetOutput(ID3D11Resource* res);
		void* GetD3DResource();
		void* GetD3DDevice();
		void* GetDXGIDevice();
	};
}
