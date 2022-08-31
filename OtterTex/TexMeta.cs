using System;
using System.Reflection.Metadata;
using System.Runtime.InteropServices;

namespace OtterTex;

[StructLayout(LayoutKind.Sequential)]
public struct TexMeta
{
    private ulong                _width;
    private ulong                _height;
    private ulong                _depth;
    private ulong                _arraySize;
    private ulong                _mipLevels;
    public  D3DResourceMiscFlags MiscFlags;
    public  uint                 MiscFlags2;
    public  DXGIFormat           Format;
    public  TexDimension         Dimension;

    public int Width
    {
        get => (int)_width;
        set => _width = (ulong)value;
    }

    public int Height
    {
        get => (int)_height;
        set => _height = (ulong)value;
    }

    public int Depth
    {
        get => (int)_depth;
        set => _depth = (ulong)value;
    }

    public int ArraySize
    {
        get => (int)_arraySize;
        set => _arraySize = (ulong)value;
    }

    public int MipLevels
    {
        get => (int)_mipLevels;
        set => _mipLevels = (ulong)value;
    }

    public unsafe IntPtr Pointer
    {
        get
        {
            fixed (void* ptr = &this)
            {
                return (IntPtr)ptr;
            }
        }
    }

    public bool IsCubeMap
        => MiscFlags.HasFlag(D3DResourceMiscFlags.TextureCube);

    public bool IsPremultipliedAlpha
        => ((D3DAlphaMode)MiscFlags2 & D3DAlphaMode.AlphaModeMask) == D3DAlphaMode.Premultiplied;

    public D3DAlphaMode AlphaMode
    {
        get => (D3DAlphaMode)MiscFlags2 & D3DAlphaMode.AlphaModeMask;
        set => MiscFlags2 = (MiscFlags2 & (uint)~D3DAlphaMode.AlphaModeMask) | (uint)value;
    }

    public bool IsVolumeMap
        => Dimension == TexDimension.Tex3D;

    public int ComputeIndex(int mip, int item, int slice)
        => (int)texmetadata_compute_index(this, (ulong)mip, (ulong)item, (ulong)slice);

    public static unsafe ErrorCode FromDDS(ReadOnlySpan<byte> data, out TexMeta meta, DDSParseFlags flags = DDSParseFlags.None)
    {
        fixed (void* ptr = data)
        {
            return texmetadata_get_from_dds_memory((IntPtr)ptr, (ulong)data.Length, flags, out meta);
        }
    }

    public static TexMeta FromDDS(ReadOnlySpan<byte> data, DDSParseFlags flags = DDSParseFlags.None)
        => FromDDS(data, out var meta, flags).ThrowIfError(meta);

    public static ErrorCode FromDDS(string path, out TexMeta meta, DDSParseFlags flags = DDSParseFlags.None)
        => texmetadata_get_from_dds_file(path, flags, out meta);

    public static TexMeta FromDDS(string path, DDSParseFlags flags = DDSParseFlags.None)
        => FromDDS(path, out var meta, flags).ThrowIfError(meta);

    public static unsafe ErrorCode FromHDR(ReadOnlySpan<byte> data, out TexMeta meta)
    {
        fixed (void* ptr = data)
        {
            return texmetadata_get_from_hdr_memory((IntPtr)ptr, (ulong)data.Length, out meta);
        }
    }

    public static TexMeta FromHDR(ReadOnlySpan<byte> data)
        => FromHDR(data, out var meta).ThrowIfError(meta);

    public static ErrorCode FromHDR(string path, out TexMeta meta)
        => texmetadata_get_from_hdr_file(path, out meta);

    public static TexMeta FromHDR(string path)
        => FromHDR(path, out var meta).ThrowIfError(meta);

    public static unsafe ErrorCode FromTGA(ReadOnlySpan<byte> data, out TexMeta meta, TGAParseFlags flags = TGAParseFlags.None)
    {
        fixed (void* ptr = data)
        {
            return texmetadata_get_from_tga_memory((IntPtr)ptr, (ulong)data.Length, flags, out meta);
        }
    }

    public static TexMeta FromTGA(ReadOnlySpan<byte> data, TGAParseFlags flags = TGAParseFlags.None)
        => FromTGA(data, out var meta, flags).ThrowIfError(meta);

    public static ErrorCode FromTGA(string path, out TexMeta meta, TGAParseFlags flags = TGAParseFlags.None)
        => texmetadata_get_from_tga_file(path, flags, out meta);

    public static TexMeta FromTGA(string path, TGAParseFlags flags = TGAParseFlags.None)
        => FromTGA(path, out var meta, flags).ThrowIfError(meta);

    public static unsafe ErrorCode FromWIC(ReadOnlySpan<byte> data, out TexMeta meta, WICParseFlags flags = WICParseFlags.None)
    {
        fixed (void* ptr = data)
        {
            return texmetadata_get_from_wic_memory((IntPtr)ptr, (ulong)data.Length, flags, out meta);
        }
    }

    public static TexMeta FromWIC(ReadOnlySpan<byte> data, WICParseFlags flags = WICParseFlags.None)
        => FromWIC(data, out var meta, flags).ThrowIfError(meta);

    public static ErrorCode FromWIC(string path, out TexMeta meta, WICParseFlags flags = WICParseFlags.None)
        => texmetadata_get_from_wic_file(path, flags, out meta);

    public static TexMeta FromWIC(string path, WICParseFlags flags = WICParseFlags.None)
        => FromWIC(path, out var meta, flags).ThrowIfError(meta);

    static TexMeta()
        => NativeDll.Initialize();

    // @formatter:off
    [DllImport(NativeDll.Name)] private static extern ulong texmetadata_compute_index(in TexMeta tex, ulong mip, ulong item, ulong slice);
    [DllImport(NativeDll.Name)] private static extern ErrorCode texmetadata_get_from_dds_memory(IntPtr data, ulong size, DDSParseFlags flags, out TexMeta tex);
    [DllImport(NativeDll.Name, CharSet = CharSet.Unicode)] private static extern ErrorCode texmetadata_get_from_dds_file(string path, DDSParseFlags flags, out TexMeta tex);
    [DllImport(NativeDll.Name)] private static extern ErrorCode texmetadata_get_from_hdr_memory(IntPtr data, ulong size, out TexMeta tex);
    [DllImport(NativeDll.Name, CharSet = CharSet.Unicode)] private static extern ErrorCode texmetadata_get_from_hdr_file(string path, out TexMeta tex);
    [DllImport(NativeDll.Name)] private static extern ErrorCode texmetadata_get_from_tga_memory(IntPtr data, ulong size, TGAParseFlags flags, out TexMeta tex);
    [DllImport(NativeDll.Name, CharSet = CharSet.Unicode)] private static extern ErrorCode texmetadata_get_from_tga_file(string path, TGAParseFlags flags, out TexMeta tex);
    [DllImport(NativeDll.Name)] private static extern ErrorCode texmetadata_get_from_wic_memory(IntPtr data, ulong size, WICParseFlags flags, out TexMeta tex);
    [DllImport(NativeDll.Name, CharSet = CharSet.Unicode)] private static extern ErrorCode texmetadata_get_from_wic_file(string path, WICParseFlags flags, out TexMeta tex);
    // @formatter:on
}
