#pragma once

#include "../DirectXTex/DirectXTex/DirectXTex.h"

using namespace System;

namespace OtterTex
{
    static void FromManaged(Image^ managed, _Out_ DirectX::Image& native)
    {
        native.width = static_cast<size_t>(managed->Width);
        native.height = static_cast<size_t>(managed->Height);
        native.format = static_cast<DXGI_FORMAT>(managed->Format);
        native.rowPitch = static_cast<size_t>(managed->RowPitch);
        native.slicePitch = static_cast<size_t>(managed->SlicePitch);
        native.pixels = static_cast<uint8_t*>(managed->Pixels);
    }

    static Image^ ToManaged(_In_ const DirectX::Image& native)
    {
        return gcnew Image
        (
            static_cast<int>(native.width),
            static_cast<int>(native.height),
            static_cast<DXGIFormat>(native.format),
            static_cast<int>(native.rowPitch),
            static_cast<int>(native.slicePitch),
            static_cast<IntPtr>(native.pixels)
        );
    }
}


