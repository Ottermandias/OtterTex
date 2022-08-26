#pragma once

#include "../DirectXTex/DirectXTex/DirectXTex.h"
#include <vcclr.h>

using namespace System;
using namespace System::IO;
using namespace System::Runtime::InteropServices;

namespace OtterTex
{
    ref class DXGIHelperImpl : public DXGIHelper
    {
    public:
        bool IsValid(DXGIFormat fmt) override
        {
            return DirectX::IsValid(static_cast<::DXGI_FORMAT>(fmt));
        }

        bool IsCompressed(DXGIFormat fmt) override
        {
            return DirectX::IsCompressed(static_cast<::DXGI_FORMAT>(fmt));
        }

        bool IsPacked(DXGIFormat fmt) override
        {
            return DirectX::IsPacked(static_cast<::DXGI_FORMAT>(fmt));
        }

        bool IsVideo(DXGIFormat fmt) override
        {
            return DirectX::IsVideo(static_cast<::DXGI_FORMAT>(fmt));
        }

        bool IsPlanar(DXGIFormat fmt) override
        {
            return DirectX::IsPlanar(static_cast<::DXGI_FORMAT>(fmt));
        }

        bool IsPalettized(DXGIFormat fmt) override
        {
            return DirectX::IsPalettized(static_cast<::DXGI_FORMAT>(fmt));
        }

        bool IsDepthStencil(DXGIFormat fmt) override
        {
            return DirectX::IsDepthStencil(static_cast<::DXGI_FORMAT>(fmt));
        }

        bool IsSRGB(DXGIFormat fmt) override
        {
            return DirectX::IsSRGB(static_cast<::DXGI_FORMAT>(fmt));
        }

        bool IsBGR(DXGIFormat fmt) override
        {
            return DirectX::IsBGR(static_cast<::DXGI_FORMAT>(fmt));
        }

        bool IsTypeless(DXGIFormat fmt) override
        {
            return DirectX::IsTypeless(static_cast<::DXGI_FORMAT>(fmt));
        }

        bool HasAlpha(DXGIFormat fmt) override
        {
            return DirectX::HasAlpha(static_cast<::DXGI_FORMAT>(fmt));
        }

        int BitsPerPixel(DXGIFormat fmt) override
        {
            return static_cast<int>(DirectX::BitsPerPixel(static_cast<::DXGI_FORMAT>(fmt)));
        }

        int BitsPerColor(DXGIFormat fmt) override
        {
            return static_cast<int>(DirectX::BitsPerColor(static_cast<::DXGI_FORMAT>(fmt)));
        }

        void ComputePitch(DXGIFormat fmt, int width, int height, ColorPaletteFlags flags, [Out] int% rowPitch, [Out] int% slicePitch)
        {
            auto row = static_cast<size_t>(rowPitch);
            auto slice = static_cast<size_t>(slicePitch);
            auto hr = DirectX::ComputePitch(static_cast<DXGI_FORMAT>(fmt), static_cast<size_t>(width), static_cast<size_t>(height), row, slice, static_cast<DirectX::CP_FLAGS>(flags));
            Marshal::ThrowExceptionForHR(hr);
            rowPitch = static_cast<int>(row);
            slicePitch = static_cast<int>(slice);
        }

        int ComputeScanLines(DXGIFormat fmt, int height)
        {
            return static_cast<int>(DirectX::ComputeScanlines(static_cast<DXGI_FORMAT>(fmt), static_cast<size_t>(height)));
        }

        DXGIFormat MakeSRGB(DXGIFormat fmt) override
        {
            return static_cast<DXGIFormat>(DirectX::MakeSRGB(static_cast<::DXGI_FORMAT>(fmt)));
        }

        DXGIFormat MakeLinear(DXGIFormat fmt) override
        {
            return static_cast<DXGIFormat>(DirectX::MakeLinear(static_cast<::DXGI_FORMAT>(fmt)));
        }

        DXGIFormat MakeTypeless(DXGIFormat fmt) override
        {
            return static_cast<DXGIFormat>(DirectX::MakeTypeless(static_cast<::DXGI_FORMAT>(fmt)));
        }

        DXGIFormat MakeTypelessUNorm(DXGIFormat fmt) override
        {
            return static_cast<DXGIFormat>(DirectX::MakeTypelessUNORM(static_cast<::DXGI_FORMAT>(fmt)));
        }

        DXGIFormat MakeTypelessFloat(DXGIFormat fmt) override
        {
            return static_cast<DXGIFormat>(DirectX::MakeTypelessFLOAT(static_cast<::DXGI_FORMAT>(fmt)));
        }

        FormatType FormatDataType(DXGIFormat fmt) override
        {
            return static_cast<FormatType>(DirectX::FormatDataType(static_cast<::DXGI_FORMAT>(fmt)));
        }
    };
}


