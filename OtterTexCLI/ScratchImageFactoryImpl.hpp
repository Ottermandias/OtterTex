#pragma once

#include "../DirectXTex/DirectXTex/DirectXTex.h"
#include "ScratchImageImpl.hpp"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace OtterTex
{
    ref class ScratchImageFactoryImpl : ScratchImageFactory
    {
    public:
        ScratchImage^ Create() override
        {
            return gcnew ScratchImageImpl();
        }

        ScratchImage^ LoadFromDDSMemory(IntPtr source, int size, DDSParseFlags flags) override
        {
            auto image = DirectX::ScratchImage();
            auto hr = DirectX::LoadFromDDSMemory(source.ToPointer(), static_cast<size_t>(size), static_cast<DirectX::DDS_FLAGS>(flags), nullptr, image);
            Marshal::ThrowExceptionForHR(hr);
            return gcnew ScratchImageImpl(&image);
        }

        ScratchImage^ LoadFromDDSFile(String^ path, DDSParseFlags flags) override
        {
            pin_ptr<const wchar_t> pathPtr = PtrToStringChars(path);
            auto image = DirectX::ScratchImage();
            auto hr = DirectX::LoadFromDDSFile(pathPtr, static_cast<DirectX::DDS_FLAGS>(flags), nullptr, image);
            Marshal::ThrowExceptionForHR(hr);
            return gcnew ScratchImageImpl(&image);
        }

        ScratchImage^ LoadFromHDRMemory(IntPtr source, int size) override
        {
            auto image = DirectX::ScratchImage();
            auto hr = DirectX::LoadFromHDRMemory(source.ToPointer(), static_cast<size_t>(size), nullptr, image);
            Marshal::ThrowExceptionForHR(hr);
            return gcnew ScratchImageImpl(&image);
        }

        ScratchImage^ LoadFromHDRFile(String^ path) override
        {
            pin_ptr<const wchar_t> pathPtr = PtrToStringChars(path);
            auto image = DirectX::ScratchImage();
            auto hr = DirectX::LoadFromHDRFile(pathPtr, nullptr, image);
            Marshal::ThrowExceptionForHR(hr);
            return gcnew ScratchImageImpl(&image);
        }

        ScratchImage^ LoadFromTGAMemory(IntPtr source, int size, TGAParseFlags flags) override
        {
            auto image = DirectX::ScratchImage();
            auto hr = DirectX::LoadFromTGAMemory(source.ToPointer(), static_cast<size_t>(size), static_cast<DirectX::TGA_FLAGS>(flags), nullptr, image);
            Marshal::ThrowExceptionForHR(hr);
            return gcnew ScratchImageImpl(&image);
        }

        ScratchImage^ LoadFromTGAFile(String^ path, TGAParseFlags flags) override
        {
            pin_ptr<const wchar_t> pathPtr = PtrToStringChars(path);
            auto image = DirectX::ScratchImage();
            auto hr = DirectX::LoadFromTGAFile(pathPtr, static_cast<DirectX::TGA_FLAGS>(flags), nullptr, image);
            Marshal::ThrowExceptionForHR(hr);
            return gcnew ScratchImageImpl(&image);
        }

        ScratchImage^ LoadFromWICMemory(IntPtr source, int size, WICParseFlags flags) override
        {
            auto image = DirectX::ScratchImage();
            auto hr = DirectX::LoadFromWICMemory(source.ToPointer(), static_cast<size_t>(size), static_cast<DirectX::WIC_FLAGS>(flags), nullptr, image);
            Marshal::ThrowExceptionForHR(hr);
            return gcnew ScratchImageImpl(&image);
        }

        ScratchImage^ LoadFromWICFile(String^ path, WICParseFlags flags) override
        {
            pin_ptr<const wchar_t> pathPtr = PtrToStringChars(path);
            auto image = DirectX::ScratchImage();
            auto hr = DirectX::LoadFromWICFile(pathPtr, static_cast<DirectX::WIC_FLAGS>(flags), nullptr, image);
            Marshal::ThrowExceptionForHR(hr);
            return gcnew ScratchImageImpl(&image);
        }
    };
}


