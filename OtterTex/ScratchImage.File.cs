using System;
using System.Runtime.InteropServices;

namespace OtterTex;

public partial class ScratchImage
{
    public static unsafe ErrorCode LoadDDS(ReadOnlySpan<byte> data, out ScratchImage image, DDSParseFlags flags = DDSParseFlags.None)
    {
        TexMeta meta = default;
        image = new ScratchImage();
        fixed (void* ptr = data)
        {
            return scratchimage_load_from_dds_memory((IntPtr)ptr, (ulong)data.Length, flags, ref meta, ref image._data);
        }
    }

    public static ScratchImage LoadDDS(ReadOnlySpan<byte> data, DDSParseFlags flags = DDSParseFlags.None)
        => LoadDDS(data, out var image, flags).ThrowIfError(image);

    public static ErrorCode LoadDDS(string path, out ScratchImage image, DDSParseFlags flags = DDSParseFlags.None)
    {
        TexMeta meta = default;
        image = new ScratchImage();
        return scratchimage_load_from_dds_file(path, flags, ref meta, ref image._data);
    }

    public static ScratchImage LoadDDS(string path, DDSParseFlags flags = DDSParseFlags.None)
        => LoadDDS(path, out var image, flags).ThrowIfError(image);

    public static unsafe ErrorCode LoadTGA(ReadOnlySpan<byte> data, out ScratchImage image, TGAParseFlags flags = TGAParseFlags.None)
    {
        TexMeta meta = default;
        image = new ScratchImage();
        fixed (void* ptr = data)
        {
            return scratchimage_load_from_tga_memory((IntPtr)ptr, (ulong)data.Length, flags, ref meta, ref image._data);
        }
    }

    public static ScratchImage LoadTGA(ReadOnlySpan<byte> data, TGAParseFlags flags = TGAParseFlags.None)
        => LoadTGA(data, out var image, flags).ThrowIfError(image);

    public static ErrorCode LoadTGA(string path, out ScratchImage image, TGAParseFlags flags = TGAParseFlags.None)
    {
        TexMeta meta = default;
        image = new ScratchImage();
        return scratchimage_load_from_tga_file(path, flags, ref meta, ref image._data);
    }

    public static ScratchImage LoadTGA(string path, TGAParseFlags flags = TGAParseFlags.None)
        => LoadTGA(path, out var image, flags).ThrowIfError(image);

    public static unsafe ErrorCode LoadWIC(ReadOnlySpan<byte> data, out ScratchImage image, WICParseFlags flags = WICParseFlags.None)
    {
        TexMeta meta = default;
        image = new ScratchImage();
        fixed (void* ptr = data)
        {
            return scratchimage_load_from_wic_memory((IntPtr)ptr, (ulong)data.Length, flags, ref meta, ref image._data);
        }
    }

    public static ScratchImage LoadWIC(ReadOnlySpan<byte> data, WICParseFlags flags = WICParseFlags.None)
        => LoadWIC(data, out var image, flags).ThrowIfError(image);

    public static ErrorCode LoadWIC(string path, out ScratchImage image, WICParseFlags flags = WICParseFlags.None)
    {
        TexMeta meta = default;
        image = new ScratchImage();
        return scratchimage_load_from_wic_file(path, flags, ref meta, ref image._data);
    }

    public static ScratchImage LoadWIC(string path, WICParseFlags flags = WICParseFlags.None)
        => LoadWIC(path, out var image, flags).ThrowIfError(image);

    public static unsafe ErrorCode LoadHDR(ReadOnlySpan<byte> data, out ScratchImage image)
    {
        TexMeta meta = default;
        image = new ScratchImage();
        fixed (void* ptr = data)
        {
            return scratchimage_load_from_hdr_memory((IntPtr)ptr, (ulong)data.Length, ref meta, ref image._data);
        }
    }

    public static ScratchImage LoadHDR(ReadOnlySpan<byte> data)
        => LoadHDR(data, out var image).ThrowIfError(image);

    public static ErrorCode LoadHDR(string path, out ScratchImage image)
    {
        TexMeta meta = default;
        image = new ScratchImage();
        return scratchimage_load_from_hdr_file(path, ref meta, ref image._data);
    }

    public static ScratchImage LoadHDR(string path)
        => LoadHDR(path, out var image).ThrowIfError(image);

    public unsafe ErrorCode SaveDDS(string path, DDSParseFlags flags = DDSParseFlags.None)
        => scratchimage_save_to_dds_file((IntPtr)_data.Image, _data.NumImages, in _data.Meta, flags, path);


    // @formatter:off
    [DllImport("DirectXTexC.dll")] private static extern ErrorCode scratchimage_load_from_dds_memory(IntPtr source, ulong size, DDSParseFlags flags, ref TexMeta meta, ref ScratchImageData data);
    [DllImport("DirectXTexC.dll")] private static extern ErrorCode scratchimage_load_from_tga_memory(IntPtr source, ulong size, TGAParseFlags flags, ref TexMeta meta, ref ScratchImageData data);
    [DllImport("DirectXTexC.dll")] private static extern ErrorCode scratchimage_load_from_wic_memory(IntPtr source, ulong size, WICParseFlags flags, ref TexMeta meta, ref ScratchImageData data);
    [DllImport("DirectXTexC.dll")] private static extern ErrorCode scratchimage_load_from_hdr_memory(IntPtr source, ulong size, ref TexMeta meta, ref ScratchImageData data);
    [DllImport("DirectXTexC.dll", CharSet = CharSet.Unicode)] private static extern ErrorCode scratchimage_load_from_dds_file(string path, DDSParseFlags flags, ref TexMeta meta, ref ScratchImageData data);
    [DllImport("DirectXTexC.dll", CharSet = CharSet.Unicode)] private static extern ErrorCode scratchimage_load_from_tga_file(string path, TGAParseFlags flags, ref TexMeta meta, ref ScratchImageData data);
    [DllImport("DirectXTexC.dll", CharSet = CharSet.Unicode)] private static extern ErrorCode scratchimage_load_from_wic_file(string path, WICParseFlags flags, ref TexMeta meta, ref ScratchImageData data);
    [DllImport("DirectXTexC.dll", CharSet = CharSet.Unicode)] private static extern ErrorCode scratchimage_load_from_hdr_file(string path, ref TexMeta meta, ref ScratchImageData data);
    [DllImport("DirectXTexC.dll", CharSet = CharSet.Unicode)] private static extern ErrorCode scratchimage_save_to_dds_file(IntPtr images, ulong numImages, in TexMeta meta, DDSParseFlags flags, string path);
    // @formatter:on
}
