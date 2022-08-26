#pragma once

#include "../DirectXTex/DirectXTex/DirectXTex.h"
#include "ImageCLI.hpp"
#include "TexMetaHelperImpl.hpp"
#include <vcclr.h>

using namespace System;
using namespace System::IO;
using namespace System::Runtime::InteropServices;

namespace OtterTex
{
    ref class ScratchImageImpl : public ScratchImage
    {
    public:
        ~ScratchImageImpl()
        {
            this->!ScratchImageImpl();
        }

        !ScratchImageImpl()
        {
            if (_base)
            {
                _base->Release();
                delete _base;
                _base = nullptr;
            }
        }

        void Initialize(TexMeta^ meta, ColorPaletteFlags flags) override
        {
            DirectX::TexMetadata metaData;
            FromManaged(meta, metaData);
            auto hr = _base->Initialize(metaData, static_cast<DirectX::CP_FLAGS>(flags));
            Marshal::ThrowExceptionForHR(hr);
        }

        void Initialize1D(DXGIFormat fmt, int length, int arraySize, int mipLevels, ColorPaletteFlags flags) override
        {
            auto hr = _base->Initialize1D(static_cast<DXGI_FORMAT> (fmt), static_cast<size_t>(length), static_cast<size_t>(arraySize), static_cast<size_t>(mipLevels), static_cast<DirectX::CP_FLAGS>(flags));
            Marshal::ThrowExceptionForHR(hr);
        }

        void Initialize2D(DXGIFormat fmt, int width, int height, int arraySize, int mipLevels, ColorPaletteFlags flags) override
        {
            auto hr = _base->Initialize2D(static_cast<DXGI_FORMAT> (fmt), static_cast<size_t>(width), static_cast<size_t>(height), static_cast<size_t>(arraySize), static_cast<size_t>(mipLevels), static_cast<DirectX::CP_FLAGS>(flags));
            Marshal::ThrowExceptionForHR(hr);
        }

        void Initialize3D(DXGIFormat fmt, int width, int height, int depth, int mipLevels, ColorPaletteFlags flags) override
        {
            auto hr = _base->Initialize2D(static_cast<DXGI_FORMAT> (fmt), static_cast<size_t>(width), static_cast<size_t>(height), static_cast<size_t>(depth), static_cast<size_t>(mipLevels), static_cast<DirectX::CP_FLAGS>(flags));
            Marshal::ThrowExceptionForHR(hr);
        }

        void InitializeCube(DXGIFormat fmt, int width, int height, int nCubes, int mipLevels, ColorPaletteFlags flags) override
        {
            auto hr = _base->Initialize2D(static_cast<DXGI_FORMAT> (fmt), static_cast<size_t>(width), static_cast<size_t>(height), static_cast<size_t>(nCubes), static_cast<size_t>(mipLevels), static_cast<DirectX::CP_FLAGS>(flags));
            Marshal::ThrowExceptionForHR(hr);
        }

        void Release() override
        {
            _base->Release();
        }

        bool OverrideFormat(DXGIFormat fmt) override
        {
            return _base->OverrideFormat(static_cast<DXGI_FORMAT> (fmt));
        }

        property ITexMeta^ Meta
        {
            ITexMeta^ get() override
            {
                if (_meta == nullptr)
                    _meta = ToManaged(_base->GetMetadata());
                return _meta;
            }
        }

        property int ImageCount
        {
            int get() override { return static_cast<int>(_base->GetImageCount()); }
        }

        property int PixelCount
        {
            int get() override { return static_cast<int>(_base->GetPixelsSize()); }
        }

        property bool IsOpaque
        {
            bool get() override { return _base->IsAlphaAllOpaque(); }
        }

        Image^ GetImage(int mip, int item, int slice) override
        {
            auto image = _base->GetImage(mip, item, slice);
            if (image == nullptr)
                return nullptr;
            return ToManaged(*image);
        }

        array<Image^>^ GetImages() override
        {
            auto count = this->ImageCount;
            array< Image^ >^ ret = gcnew array< Image^ >(count);
            auto images = _base->GetImages();
            for (auto i = 0; i < count; i++)
                ret[i] = ToManaged(images[i]);
            return ret;
        }

        ScratchImage^ FlipRotate(FlipRotateFlags flags) override
        {
            auto ret = DirectX::ScratchImage();
            auto hr = DirectX::FlipRotate(_base->GetImages(), _base->GetImageCount(), _base->GetMetadata(), static_cast<DirectX::TEX_FR_FLAGS>(flags), ret);
            Marshal::ThrowExceptionForHR(hr);
            return gcnew ScratchImageImpl(&ret);
        }

        ScratchImage^ Resize(int width, int height, FilterFlags flags) override
        {
            auto ret = DirectX::ScratchImage();
            auto hr = DirectX::Resize(_base->GetImages(), _base->GetImageCount(), _base->GetMetadata(), static_cast<size_t>(width), static_cast<size_t>(height), static_cast<DirectX::TEX_FILTER_FLAGS>(flags), ret);
            Marshal::ThrowExceptionForHR(hr);
            return gcnew ScratchImageImpl(&ret);
        }

        ScratchImage^ Convert(DXGIFormat fmt, FilterFlags flags, float threshold) override
        {
            auto ret = DirectX::ScratchImage();
            auto hr = DirectX::Convert(_base->GetImages(), _base->GetImageCount(), _base->GetMetadata(), static_cast<DXGI_FORMAT>(fmt), static_cast<DirectX::TEX_FILTER_FLAGS>(flags), threshold, ret);
            Marshal::ThrowExceptionForHR(hr);
            return gcnew ScratchImageImpl(&ret);
        }

        ScratchImage^ ConvertToSinglePlane() override
        {
            auto ret = DirectX::ScratchImage();
            auto hr = DirectX::ConvertToSinglePlane(_base->GetImages(), _base->GetImageCount(), _base->GetMetadata(), ret);
            Marshal::ThrowExceptionForHR(hr);
            return gcnew ScratchImageImpl(&ret);
        }

        ScratchImage^ GenerateMipMaps(int levels, FilterFlags flags) override
        {
            auto ret = DirectX::ScratchImage();
            auto hr = DirectX::GenerateMipMaps(_base->GetImages(), _base->GetImageCount(), _base->GetMetadata(), static_cast<DirectX::TEX_FILTER_FLAGS>(flags), levels, ret);
            Marshal::ThrowExceptionForHR(hr);
            return gcnew ScratchImageImpl(&ret);
        }

        ScratchImage^ GenerateMipMaps3D(int levels, FilterFlags flags) override
        {
            auto ret = DirectX::ScratchImage();
            auto hr = DirectX::GenerateMipMaps3D(_base->GetImages(), _base->GetImageCount(), _base->GetMetadata(), static_cast<DirectX::TEX_FILTER_FLAGS>(flags), levels, ret);
            Marshal::ThrowExceptionForHR(hr);
            return gcnew ScratchImageImpl(&ret);
        }

        ScratchImage^ ScaleMipMapsAlphaForCoverage(int item, float alphaReference) override
        {
            auto ret = DirectX::ScratchImage();
            auto hr = DirectX::ScaleMipMapsAlphaForCoverage(_base->GetImages(), _base->GetImageCount(), _base->GetMetadata(), static_cast<size_t>(item), alphaReference, ret);
            Marshal::ThrowExceptionForHR(hr);
            return gcnew ScratchImageImpl(&ret);
        }

        ScratchImage^ PremultiplyAlpha(AlphaFlags flags) override
        {
            auto ret = DirectX::ScratchImage();
            auto hr = DirectX::PremultiplyAlpha(_base->GetImages(), _base->GetImageCount(), _base->GetMetadata(), static_cast<DirectX::TEX_PMALPHA_FLAGS>(flags), ret);
            Marshal::ThrowExceptionForHR(hr);
            return gcnew ScratchImageImpl(&ret);
        }

        ScratchImage^ Compress(DXGIFormat fmt, CompressFlags flags, float threshold) override
        {
            auto ret = DirectX::ScratchImage();
            auto hr = DirectX::Compress(_base->GetImages(), _base->GetImageCount(), _base->GetMetadata(), static_cast<DXGI_FORMAT>(fmt), static_cast<DirectX::TEX_COMPRESS_FLAGS>(flags), threshold, ret);
            Marshal::ThrowExceptionForHR(hr);
            return gcnew ScratchImageImpl(&ret);
        }

        ScratchImage^ Decompress(DXGIFormat fmt) override
        {
            auto ret = DirectX::ScratchImage();
            auto hr = DirectX::Decompress(_base->GetImages(), _base->GetImageCount(), _base->GetMetadata(), static_cast<DXGI_FORMAT>(fmt), ret);
            Marshal::ThrowExceptionForHR(hr);
            return gcnew ScratchImageImpl(&ret);
        }

        ScratchImage^ ComputeNormalMap(MapFlags flags, float amplitude, DXGIFormat fmt) override
        {
            auto ret = DirectX::ScratchImage();
            auto hr = DirectX::ComputeNormalMap(_base->GetImages(), _base->GetImageCount(), _base->GetMetadata(), static_cast<DirectX::CNMAP_FLAGS>(flags), amplitude, static_cast<DXGI_FORMAT>(fmt), ret);
            Marshal::ThrowExceptionForHR(hr);
            return gcnew ScratchImageImpl(&ret);
        }

        int SaveToDDSMemory(IntPtr target, int maxLength, DdsFlags flags) override
        {
            DirectX::Blob memory;
            auto hr = DirectX::SaveToDDSMemory(_base->GetImages(), _base->GetImageCount(), _base->GetMetadata(), static_cast<DirectX::DDS_FLAGS>(flags), memory);
            Marshal::ThrowExceptionForHR(hr);
            return SaveBlob(memory, target, maxLength);
        }

        void SaveToDDSFile(String^ path, DdsFlags flags) override
        {
            pin_ptr<const wchar_t> pathPtr = PtrToStringChars(path);
            auto hr = DirectX::SaveToDDSFile(_base->GetImages(), _base->GetImageCount(), _base->GetMetadata(), static_cast<DirectX::DDS_FLAGS>(flags), pathPtr);
            Marshal::ThrowExceptionForHR(hr);
        }

        ScratchImageImpl()
        {
            _base = new DirectX::ScratchImage();
        }

        ScratchImageImpl(DirectX::ScratchImage* movedFrom)
        {
            _base = new DirectX::ScratchImage(std::move(*movedFrom));
        }
    private:
        DirectX::ScratchImage* _base;
        TexMeta^ _meta;

        int SaveBlob(const DirectX::Blob& blob, IntPtr target, int maxLength)
        {
            auto size = blob.GetBufferSize();
            if (size <= maxLength)
                std::memcpy(target.ToPointer(), blob.GetBufferPointer(), size);
            return static_cast<int>(size);
        }
    };
}


