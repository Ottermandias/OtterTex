#pragma once

#include "../DirectXTex/DirectXTex/DirectXTex.h"
#include <vcclr.h>

using namespace System;
using namespace System::IO;
using namespace System::Runtime::InteropServices;

namespace OtterTex
{
    static void FromManaged(TexMeta^ managed, _Out_ DirectX::TexMetadata& native)
    {
        native.width = static_cast<size_t>(managed->Width);
        native.height = static_cast<size_t>(managed->Height);
        native.depth = static_cast<size_t>(managed->Depth);
        native.arraySize = static_cast<size_t>(managed->ArraySize);
        native.mipLevels = static_cast<size_t>(managed->MipLevels);
        native.miscFlags = static_cast<uint32_t>(managed->MiscFlags);
        native.miscFlags2 = static_cast<uint32_t>(managed->MiscFlags2);
        native.format = static_cast<::DXGI_FORMAT>(managed->Format);
        native.dimension = static_cast<DirectX::TEX_DIMENSION>(managed->Dimension);
    }

    static TexMeta^ ToManaged(_In_ const DirectX::TexMetadata& native)
    {
        return gcnew TexMeta
        (
            static_cast<int>(native.width),
            static_cast<int>(native.height),
            static_cast<int>(native.depth),
            static_cast<int>(native.arraySize),
            static_cast<D3DResourceMiscFlags>(native.miscFlags),
            static_cast<D3DAlphaMode>(native.miscFlags2),
            static_cast<DXGIFormat>(native.format),
            static_cast<short>(native.mipLevels),
            static_cast<TexDimension>(native.dimension)
        );
    }

    ref class TexMetaHelperImpl : TexMetaHelper
    {
    public:
        TexMeta^ GetMetaDataFromDDSMemory(IntPtr source, int size, DDSParseFlags flags) override
        {
            DirectX::TexMetadata native;
            auto hr = DirectX::GetMetadataFromDDSMemory((void*)source, static_cast<size_t>(size), static_cast<DirectX::DDS_FLAGS>(flags), native);
            Marshal::ThrowExceptionForHR(hr);
            return ToManaged(native);
        }

        TexMeta^ GetMetaDataFromDDSFile(String^ path, DDSParseFlags flags) override
        {
            pin_ptr<const wchar_t> pathPtr = PtrToStringChars(path);
            DirectX::TexMetadata native;
            auto hr = DirectX::GetMetadataFromDDSFile(pathPtr, static_cast<DirectX::DDS_FLAGS>(flags), native);
            Marshal::ThrowExceptionForHR(hr);
            return ToManaged(native);
        }

        TexMeta^ GetMetaDataFromHDRMemory(IntPtr source, int size) override
        {
            DirectX::TexMetadata native;
            auto hr = DirectX::GetMetadataFromHDRMemory((void*)source, static_cast<size_t>(size), native);
            Marshal::ThrowExceptionForHR(hr);
            return ToManaged(native);
        }

        TexMeta^ GetMetaDataFromHDRFile(String^ path) override
        {
            pin_ptr<const wchar_t> pathPtr = PtrToStringChars(path);
            DirectX::TexMetadata native;
            auto hr = DirectX::GetMetadataFromHDRFile(pathPtr, native);
            Marshal::ThrowExceptionForHR(hr);
            return ToManaged(native);
        }

        TexMeta^ GetMetaDataFromTGAMemory(IntPtr source, int size, TGAParseFlags flags) override
        {
            DirectX::TexMetadata native;
            auto hr = DirectX::GetMetadataFromTGAMemory((void*)source, static_cast<size_t>(size), static_cast<DirectX::TGA_FLAGS>(flags), native);
            Marshal::ThrowExceptionForHR(hr);
            return ToManaged(native);
        }

        TexMeta^ GetMetaDataFromTGAFile(String^ path, TGAParseFlags flags) override
        {
            pin_ptr<const wchar_t> pathPtr = PtrToStringChars(path);
            DirectX::TexMetadata native;
            auto hr = DirectX::GetMetadataFromTGAFile(pathPtr, static_cast<DirectX::TGA_FLAGS>(flags), native);
            Marshal::ThrowExceptionForHR(hr);
            return ToManaged(native);
        }

        TexMeta^ GetMetaDataFromWICMemory(IntPtr source, int size, WICParseFlags flags) override
        {
            DirectX::TexMetadata native;
            auto hr = DirectX::GetMetadataFromWICMemory((void*)source, static_cast<size_t>(size), static_cast<DirectX::WIC_FLAGS>(flags), native);
            Marshal::ThrowExceptionForHR(hr);
            return ToManaged(native);
        }

        TexMeta^ GetMetaDataFromWICFile(String^ path, WICParseFlags flags) override
        {
            pin_ptr<const wchar_t> pathPtr = PtrToStringChars(path);
            DirectX::TexMetadata native;
            auto hr = DirectX::GetMetadataFromWICFile(pathPtr, static_cast<DirectX::WIC_FLAGS>(flags), native);
            Marshal::ThrowExceptionForHR(hr);
            return ToManaged(native);
        }

        int WriteDDSHeader(TexMeta^ meta, IntPtr target, int size, DDSParseFlags flags) override
        {
            auto data = DirectX::TexMetadata();
            FromManaged(meta, data);
            size_t required = 0;
            auto hr = DirectX::EncodeDDSHeader(data, static_cast<DirectX::DDS_FLAGS>(flags), static_cast<void*>(target), static_cast<size_t>(size), required);
            Marshal::ThrowExceptionForHR(hr);
            return static_cast<int>(required);
        }
    };
}


