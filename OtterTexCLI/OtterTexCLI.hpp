#pragma once

#include "../DirectXTex/DirectXTex/DirectXTex.h"
#include <vcclr.h>

using namespace System;
using namespace System::IO;
using namespace System::Runtime::InteropServices;

namespace OtterTex
{
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

    static void FromManaged(Image^ managed, _Out_ DirectX::Image& native)
    {
        native.width = static_cast<size_t>(managed->Width);
        native.height = static_cast<size_t>(managed->Height);
        native.format = static_cast<::DXGI_FORMAT>(managed->Format);
        native.rowPitch = static_cast<size_t>(managed->RowPitch);
        native.slicePitch = static_cast<size_t>(managed->SlicePitch);
    }

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

        int WriteDDSHeader(TexMeta^ meta, IntPtr target, int size, DdsFlags flags) override
        {
            auto data = DirectX::TexMetadata();
            FromManaged(meta, data);
            size_t required = 0;
            auto hr = DirectX::EncodeDDSHeader(data, static_cast<DirectX::DDS_FLAGS>(flags), static_cast<void*>(target), static_cast<size_t>(size), required);
            Marshal::ThrowExceptionForHR(hr);
            return static_cast<int>(required);
        }
    };

    ref class ScratchImageImpl : public ScratchImage
    {
    public:
        static ScratchImage^ Create()
        {
            return gcnew ScratchImageImpl();
        }

        static ScratchImage^ Create(ScratchImageImpl movedFrom)
        {
            return gcnew ScratchImageImpl(movedFrom._base);
        }

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

        void Initialize(TexMeta^ meta, ColorPaletteFlags flags)
        {
            DirectX::TexMetadata metaData;
            FromManaged(meta, metaData);
            auto hr = _base->Initialize(metaData, static_cast<DirectX::CP_FLAGS>(flags));
            Marshal::ThrowExceptionForHR(hr);
        }

        void Initialize1D(DXGIFormat fmt, int length, int arraySize, int mipLevels, ColorPaletteFlags flags)
        {
            auto hr = _base->Initialize1D(static_cast<DXGI_FORMAT> (fmt), static_cast<size_t>(length), static_cast<size_t>(arraySize), static_cast<size_t>(mipLevels), static_cast<DirectX::CP_FLAGS>(flags));
            Marshal::ThrowExceptionForHR(hr);
        }

        void Initialize2D(DXGIFormat fmt, int width, int height, int arraySize, int mipLevels, ColorPaletteFlags flags)
        {
            auto hr = _base->Initialize2D(static_cast<DXGI_FORMAT> (fmt), static_cast<size_t>(width), static_cast<size_t>(height), static_cast<size_t>(arraySize), static_cast<size_t>(mipLevels), static_cast<DirectX::CP_FLAGS>(flags));
            Marshal::ThrowExceptionForHR(hr);
        }

        void Initialize3D(DXGIFormat fmt, int width, int height, int depth, int mipLevels, ColorPaletteFlags flags)
        {
            auto hr = _base->Initialize2D(static_cast<DXGI_FORMAT> (fmt), static_cast<size_t>(width), static_cast<size_t>(height), static_cast<size_t>(depth), static_cast<size_t>(mipLevels), static_cast<DirectX::CP_FLAGS>(flags));
            Marshal::ThrowExceptionForHR(hr);
        }

        void InitializeCube(DXGIFormat fmt, int width, int height, int nCubes, int mipLevels, ColorPaletteFlags flags)
        {
            auto hr = _base->Initialize2D(static_cast<DXGI_FORMAT> (fmt), static_cast<size_t>(width), static_cast<size_t>(height), static_cast<size_t>(nCubes), static_cast<size_t>(mipLevels), static_cast<DirectX::CP_FLAGS>(flags));
            Marshal::ThrowExceptionForHR(hr);
        }

        void Release()
        {
            _base->Release();
        }

        bool OverrideFormat(DXGIFormat fmt)
        {
            return _base->OverrideFormat(static_cast<DXGI_FORMAT> (fmt));
        }

        property ITexMeta^ Meta
        {
            ITexMeta^ get()
            {
                if (_meta == nullptr)
                    _meta = ToManaged(_base->GetMetadata());
                return _meta;
            }
        }

        property int ImageCount
        {
            int get() { return static_cast<int>(_base->GetImageCount()); }
        }

        property int PixelCount
        {
            int get() { return static_cast<int>(_base->GetPixelsSize()); }
        }

        property bool IsOpaque
        {
            bool get() { return _base->IsAlphaAllOpaque(); }
        }

        Image^ GetImage(int mip, int item, int slice)
        {
            auto image = _base->GetImage(mip, item, slice);
            if (image == nullptr)
                return nullptr;
            return ToManaged(*image);
        }

        array<Image^>^ GetImages()
        {
            auto count = this->ImageCount;
            array< Image^ >^ ret = gcnew array< Image^ >(count);
            auto images = _base->GetImages();
            for (auto i = 0; i < count; i++)
                ret[i] = ToManaged(images[i]);
            return ret;
        }

        static ScratchImage^ LoadFromDDSMemory(const void* source, int size, DDSParseFlags flags)
        {
            auto image = DirectX::ScratchImage();
            auto hr = DirectX::LoadFromDDSMemory(source, static_cast<size_t>(size), static_cast<DirectX::DDS_FLAGS>(flags), nullptr, image);
            Marshal::ThrowExceptionForHR(hr);
            return gcnew ScratchImageImpl(&image);
        }

        static ScratchImage^ LoadFromDDSFile(String^ path, DDSParseFlags flags)
        {
            pin_ptr<const wchar_t> pathPtr = PtrToStringChars(path);
            auto image = DirectX::ScratchImage();
            auto hr = DirectX::LoadFromDDSFile(pathPtr, static_cast<DirectX::DDS_FLAGS>(flags), nullptr, image);
            Marshal::ThrowExceptionForHR(hr);
            return gcnew ScratchImageImpl(&image);
        }

        static ScratchImage^ LoadFromHDRMemory(const void* source, int size)
        {
            auto image = DirectX::ScratchImage();
            auto hr = DirectX::LoadFromHDRMemory(source, static_cast<size_t>(size), nullptr, image);
            Marshal::ThrowExceptionForHR(hr);
            return gcnew ScratchImageImpl(&image);
        }

        static ScratchImage^ LoadFromHDRFile(String^ path)
        {
            pin_ptr<const wchar_t> pathPtr = PtrToStringChars(path);
            auto image = DirectX::ScratchImage();
            auto hr = DirectX::LoadFromHDRFile(pathPtr, nullptr, image);
            Marshal::ThrowExceptionForHR(hr);
            return gcnew ScratchImageImpl(&image);
        }

        static ScratchImage^ LoadFromTGAMemory(const void* source, int size, TGAParseFlags flags)
        {
            auto image = DirectX::ScratchImage();
            auto hr = DirectX::LoadFromTGAMemory(source, static_cast<size_t>(size), static_cast<DirectX::TGA_FLAGS>(flags), nullptr, image);
            Marshal::ThrowExceptionForHR(hr);
            return gcnew ScratchImageImpl(&image);
        }

        static ScratchImage^ LoadFromTGAFile(String^ path, TGAParseFlags flags)
        {
            pin_ptr<const wchar_t> pathPtr = PtrToStringChars(path);
            auto image = DirectX::ScratchImage();
            auto hr = DirectX::LoadFromTGAFile(pathPtr, static_cast<DirectX::TGA_FLAGS>(flags), nullptr, image);
            Marshal::ThrowExceptionForHR(hr);
            return gcnew ScratchImageImpl(&image);
        }

        static ScratchImage^ LoadFromWICMemory(const void* source, int size, WICParseFlags flags)
        {
            auto image = DirectX::ScratchImage();
            auto hr = DirectX::LoadFromWICMemory(source, static_cast<size_t>(size), static_cast<DirectX::WIC_FLAGS>(flags), nullptr, image);
            Marshal::ThrowExceptionForHR(hr);
            return gcnew ScratchImageImpl(&image);
        }

        static ScratchImage^ LoadFromWICFile(String^ path, WICParseFlags flags)
        {
            pin_ptr<const wchar_t> pathPtr = PtrToStringChars(path);
            auto image = DirectX::ScratchImage();
            auto hr = DirectX::LoadFromWICFile(pathPtr, static_cast<DirectX::WIC_FLAGS>(flags), nullptr, image);
            Marshal::ThrowExceptionForHR(hr);
            return gcnew ScratchImageImpl(&image);
        }

        ScratchImage^ FlipRotate(FlipRotateFlags flags)
        {
            auto ret = DirectX::ScratchImage();
            auto hr = DirectX::FlipRotate(_base->GetImages(), _base->GetImageCount(), _base->GetMetadata(), static_cast<DirectX::TEX_FR_FLAGS>(flags), ret);
            Marshal::ThrowExceptionForHR(hr);
            return gcnew ScratchImageImpl(&ret);
        }

        ScratchImage^ Resize(int width, int height, FilterFlags flags)
        {
            auto ret = DirectX::ScratchImage();
            auto hr = DirectX::Resize(_base->GetImages(), _base->GetImageCount(), _base->GetMetadata(), static_cast<size_t>(width), static_cast<size_t>(height), static_cast<DirectX::TEX_FILTER_FLAGS>(flags), ret);
            Marshal::ThrowExceptionForHR(hr);
            return gcnew ScratchImageImpl(&ret);
        }

        ScratchImage^ Convert(DXGIFormat fmt, FilterFlags flags, float threshold)
        {
            auto ret = DirectX::ScratchImage();
            auto hr = DirectX::Convert(_base->GetImages(), _base->GetImageCount(), _base->GetMetadata(), static_cast<DXGI_FORMAT>(fmt), static_cast<DirectX::TEX_FILTER_FLAGS>(flags), threshold, ret);
            Marshal::ThrowExceptionForHR(hr);
            return gcnew ScratchImageImpl(&ret);
        }

        ScratchImage^ ConvertToSinglePlane()
        {
            auto ret = DirectX::ScratchImage();
            auto hr = DirectX::ConvertToSinglePlane(_base->GetImages(), _base->GetImageCount(), _base->GetMetadata(), ret);
            Marshal::ThrowExceptionForHR(hr);
            return gcnew ScratchImageImpl(&ret);
        }

        ScratchImage^ GenerateMipMaps(int levels, FilterFlags flags)
        {
            auto ret = DirectX::ScratchImage();
            auto hr = DirectX::GenerateMipMaps(_base->GetImages(), _base->GetImageCount(), _base->GetMetadata(), static_cast<DirectX::TEX_FILTER_FLAGS>(flags), levels, ret);
            Marshal::ThrowExceptionForHR(hr);
            return gcnew ScratchImageImpl(&ret);
        }

        ScratchImage^ GenerateMipMaps3D(int levels, FilterFlags flags)
        {
            auto ret = DirectX::ScratchImage();
            auto hr = DirectX::GenerateMipMaps3D(_base->GetImages(), _base->GetImageCount(), _base->GetMetadata(), static_cast<DirectX::TEX_FILTER_FLAGS>(flags), levels, ret);
            Marshal::ThrowExceptionForHR(hr);
            return gcnew ScratchImageImpl(&ret);
        }

        ScratchImage^ ScaleMipMapsAlphaForCoverage(int item, float alphaReference)
        {
            auto ret = DirectX::ScratchImage();
            auto hr = DirectX::ScaleMipMapsAlphaForCoverage(_base->GetImages(), _base->GetImageCount(), _base->GetMetadata(), static_cast<size_t>(item), alphaReference, ret);
            Marshal::ThrowExceptionForHR(hr);
            return gcnew ScratchImageImpl(&ret);
        }

        ScratchImage^ PremultiplyAlpha(AlphaFlags flags)
        {
            auto ret = DirectX::ScratchImage();
            auto hr = DirectX::PremultiplyAlpha(_base->GetImages(), _base->GetImageCount(), _base->GetMetadata(), static_cast<DirectX::TEX_PMALPHA_FLAGS>(flags), ret);
            Marshal::ThrowExceptionForHR(hr);
            return gcnew ScratchImageImpl(&ret);
        }

        ScratchImage^ Compress(DXGIFormat fmt, CompressFlags flags, float threshold)
        {
            auto ret = DirectX::ScratchImage();
            auto hr = DirectX::Compress(_base->GetImages(), _base->GetImageCount(), _base->GetMetadata(), static_cast<DXGI_FORMAT>(fmt), static_cast<DirectX::TEX_COMPRESS_FLAGS>(flags), threshold, ret);
            Marshal::ThrowExceptionForHR(hr);
            return gcnew ScratchImageImpl(&ret);
        }

        ScratchImage^ Decompress(DXGIFormat fmt)
        {
            auto ret = DirectX::ScratchImage();
            auto hr = DirectX::Decompress(_base->GetImages(), _base->GetImageCount(), _base->GetMetadata(), static_cast<DXGI_FORMAT>(fmt), ret);
            Marshal::ThrowExceptionForHR(hr);
            return gcnew ScratchImageImpl(&ret);
        }

        ScratchImage^ ComputeNormalMap(MapFlags flags, float amplitude, DXGIFormat fmt)
        {
            auto ret = DirectX::ScratchImage();
            auto hr = DirectX::ComputeNormalMap(_base->GetImages(), _base->GetImageCount(), _base->GetMetadata(), static_cast<DirectX::CNMAP_FLAGS>(flags), amplitude, static_cast<DXGI_FORMAT>(fmt), ret);
            Marshal::ThrowExceptionForHR(hr);
            return gcnew ScratchImageImpl(&ret);
        }
    private:
        ScratchImageImpl()
        {
            _base = new DirectX::ScratchImage();
        }

        ScratchImageImpl(DirectX::ScratchImage* movedFrom)
        {
            _base = new DirectX::ScratchImage(std::move(*movedFrom));
        }

        DirectX::ScratchImage* _base;
        ITexMeta^ _meta;
    };
}


