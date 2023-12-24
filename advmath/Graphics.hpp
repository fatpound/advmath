/******************************************************************************************
*	Chili DirectX Framework Version 16.10.01											  *
*	Graphics.hpp																			  *
*	Copyright 2016 PlanetChili <http://www.planetchili.net>								  *
*																						  *
*	This file is part of The Chili DirectX Framework.									  *
*																						  *
*	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
*	it under the terms of the GNU General Public License as published by				  *
*	the Free Software Foundation, either version 3 of the License, or					  *
*	(at your option) any later version.													  *
*																						  *
*	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
*	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
*	GNU General Public License for more details.										  *
*																						  *
*	You should have received a copy of the GNU General Public License					  *
*	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
******************************************************************************************/
#pragma once
#include "GDIPlusManager.hpp"
#include "ChiliException.hpp"
#include "Color.hpp"
#include "Surface.hpp"
#include "Vec3.hpp"
#include "Mat3.hpp"
#include "TextureVertex.hpp"

#include <d3d11.h>
#include <wrl.h>

#define CHILI_GFX_EXCEPTION( hr,note ) Graphics::Exception( hr,note,_CRT_WIDE(__FILE__),__LINE__ )

using fatpound::math::Vef2;
using fatpound::math::Vef3;
using fatpound::math::Maf3;

class Graphics
{
public:
    class Exception : public ChiliException
    {
    public:
        Exception(HRESULT hr, const std::wstring& note, const wchar_t* file, unsigned int line);
        std::wstring GetErrorName() const;
        std::wstring GetErrorDescription() const;
        virtual std::wstring GetFullMessage() const override;
        virtual std::wstring GetExceptionType() const override;
    private:
        HRESULT hr;
    };
private:
    // vertex format for the framebuffer fullscreen textured quad
    struct FSQVertex
    {
        float x, y, z;		// position
        float u, v;			// texcoords
    };
public:
    Graphics(class HWNDKey& key);
    Graphics(const Graphics&) = delete;
    Graphics& operator=(const Graphics&) = delete;
    void EndFrame();
    void BeginFrame();
    void DrawTriangle(const Vef2& v0, const Vef2& v1, const Vef2& v2, Color color);
    void DrawTriangleTextured(const TextureVertex& v0, const TextureVertex& v1, const TextureVertex& v2, const Surface& texture);
    void DrawLine(const Vef2& p1, const Vef2& p2, Color color)
    {
        DrawLine(p1.x, p1.y, p2.x, p2.y, color);
    }
    void DrawLine(float x1, float y1, float x2, float y2, Color c);
    void PutPixel(int x, int y, int r, int g, int b)
    {
        PutPixel(x, y, { unsigned char(r),unsigned char(g),unsigned char(b) });
    }
    void PutPixel(int x, int y, Color c)
    {
        sysBuffer.PutPixel(x, y, c);
    }
    ~Graphics();
private:
    void DrawFlatTopTriangle(const Vef2& v0, const Vef2& v1, const Vef2& v2, Color color);
    void DrawFlatBottomTriangle(const Vef2& v0, const Vef2& v1, const Vef2& v2, Color color);
    void DrawFlatTopTriangleTextured(const TextureVertex& v0, const TextureVertex& v1, const TextureVertex& v2, const Surface& texture);
    void DrawFlatBottomTriangleTextured(const TextureVertex& v0, const TextureVertex& v1, const TextureVertex& v2, const Surface& texture);
    void DrawFlatTriangleTextured(const TextureVertex& v0, const TextureVertex& v1, const TextureVertex& v2, const Surface& texture, const TextureVertex& dv0, const TextureVertex& dv1, TextureVertex& intrpEdge1);
private:
    GDIPlusManager										gdipMan;
    Microsoft::WRL::ComPtr<IDXGISwapChain>				pSwapChain;
    Microsoft::WRL::ComPtr<ID3D11Device>				pDevice;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext>			pImmediateContext;
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView>		pRenderTargetView;
    Microsoft::WRL::ComPtr<ID3D11Texture2D>				pSysBufferTexture;
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	pSysBufferTextureView;
    Microsoft::WRL::ComPtr<ID3D11PixelShader>			pPixelShader;
    Microsoft::WRL::ComPtr<ID3D11VertexShader>			pVertexShader;
    Microsoft::WRL::ComPtr<ID3D11Buffer>				pVertexBuffer;
    Microsoft::WRL::ComPtr<ID3D11InputLayout>			pInputLayout;
    Microsoft::WRL::ComPtr<ID3D11SamplerState>			pSamplerState;
    D3D11_MAPPED_SUBRESOURCE							mappedSysBufferTexture;
    Surface												sysBuffer;
public:
    static constexpr uint32_t ScreenWidth  = 640ui32;
    static constexpr uint32_t ScreenHeight = 640ui32;
};