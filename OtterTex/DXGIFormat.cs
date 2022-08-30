using System.Diagnostics.CodeAnalysis;
using System.Runtime.InteropServices;

namespace OtterTex;

public enum DXGIFormat : uint
{
    Unknown                = 0,
    R32G32B32A32Typeless   = 1,
    R32G32B32A32Float      = 2,
    R32G32B32A32UInt       = 3,
    R32G32B32A32SInt       = 4,
    R32G32B32Typeless      = 5,
    R32G32B32Float         = 6,
    R32G32B32UInt          = 7,
    R32G32B32SInt          = 8,
    R16G16B16A16Typeless   = 9,
    R16G16B16A16Float      = 10,
    R16G16B16A16UNorm      = 11,
    R16G16B16A16UInt       = 12,
    R16G16B16A16SNorm      = 13,
    R16G16B16A16SInt       = 14,
    R32G32Typeless         = 15,
    R32G32Float            = 16,
    R32G32UInt             = 17,
    R32G32SInt             = 18,
    R32G8X24Typeless       = 19,
    D32FloatS8X24UInt      = 20,
    R32FloatX8X24Typeless  = 21,
    X32TypelessG8X24UInt   = 22,
    R10G10B10A2Typeless    = 23,
    R10G10B10A2UNorm       = 24,
    R10G10B10A2UInt        = 25,
    R11G11B10Float         = 26,
    R8G8B8A8Typeless       = 27,
    R8G8B8A8UNorm          = 28,
    R8G8B8A8UNormSRGB      = 29,
    R8G8B8A8UInt           = 30,
    R8G8B8A8SNorm          = 31,
    R8G8B8A8SInt           = 32,
    R16G16Typeless         = 33,
    R16G16Float            = 34,
    R16G16UNorm            = 35,
    R16G16UInt             = 36,
    R16G16SNorm            = 37,
    R16G16SInt             = 38,
    R32Typeless            = 39,
    D32Float               = 40,
    R32Float               = 41,
    R32UInt                = 42,
    R32SInt                = 43,
    R24G8Typeless          = 44,
    D24UNormS8UInt         = 45,
    R24UNormX8Typeless     = 46,
    X24TypelessG8UInt      = 47,
    R8G8Typeless           = 48,
    R8G8UNorm              = 49,
    R8G8UInt               = 50,
    R8G8SNorm              = 51,
    R8G8SInt               = 52,
    R16Typeless            = 53,
    R16Float               = 54,
    D16UNorm               = 55,
    R16UNorm               = 56,
    R16UInt                = 57,
    R16SNorm               = 58,
    R16SInt                = 59,
    R8Typeless             = 60,
    R8UNorm                = 61,
    R8UInt                 = 62,
    R8SNorm                = 63,
    R8SInt                 = 64,
    A8UNorm                = 65,
    R1UNorm                = 66,
    R9G9B9E5SharedEXP      = 67,
    R8G8B8G8UNorm          = 68,
    G8R8G8B8UNorm          = 69,
    BC1Typeless            = 70,
    BC1UNorm               = 71,
    BC1UNormSRGB           = 72,
    BC2Typeless            = 73,
    BC2UNorm               = 74,
    BC2UNormSRGB           = 75,
    BC3Typeless            = 76,
    BC3UNorm               = 77,
    BC3UNormSRGB           = 78,
    BC4Typeless            = 79,
    BC4UNorm               = 80,
    BC4SNorm               = 81,
    BC5Typeless            = 82,
    BC5UNorm               = 83,
    BC5SNorm               = 84,
    B5G6R5UNorm            = 85,
    B5G5R5A1UNorm          = 86,
    B8G8R8A8UNorm          = 87,
    B8G8R8X8UNorm          = 88,
    R10G10B10XRBiasA2UNorm = 89,
    B8G8R8A8Typeless       = 90,
    B8G8R8A8UNormSRGB      = 91,
    B8G8R8X8Typeless       = 92,
    B8G8R8X8UNormSRGB      = 93,
    BC6HTypeless           = 94,
    BC6HUF16               = 95,
    BC6HSF16               = 96,
    BC7Typeless            = 97,
    BC7UNorm               = 98,
    BC7UNormSRGB           = 99,
    AYUV                   = 100,
    Y410                   = 101,
    Y416                   = 102,
    NV12                   = 103,
    P010                   = 104,
    P016                   = 105,
    F420Opaque             = 106,
    YUY2                   = 107,
    Y210                   = 108,
    Y216                   = 109,
    NV11                   = 110,
    AI44                   = 111,
    IA44                   = 112,
    P8                     = 113,
    A8P8                   = 114,
    B4G4R4A4UNorm          = 115,
    P208                   = 130,
    V208                   = 131,
    V408                   = 132,
    SamplerFeedbackMinMipOpaque,
    SamplerFeedbackMipRegionUsedOpaque,
    ForceUInt = 0xffffffff,
}

public static class DXGIExtensions
{
    // @formatter:off
    public static bool       IsValid(this DXGIFormat fmt) => dxgiformat_is_valid(fmt);
    public static bool       IsCompressed(this DXGIFormat fmt) => dxgiformat_is_compressed(fmt);
    public static bool       IsPacked(this DXGIFormat fmt) => dxgiformat_is_packed(fmt);
    public static bool       IsVideo(this DXGIFormat fmt) => dxgiformat_is_video(fmt);
    public static bool       IsPlanar(this DXGIFormat fmt) => dxgiformat_is_planar(fmt);
    public static bool       IsPalettized(this DXGIFormat fmt) => dxgiformat_is_palettized( fmt);
    public static bool       IsDepthStencil(this DXGIFormat fmt) => dxgiformat_is_depth_stencil(fmt);
    public static bool       IsSRGB(this DXGIFormat fmt) => dxgiformat_is_srgb(fmt);
    public static bool       IsBGR(this DXGIFormat fmt) => dxgiformat_is_bgr(fmt);
    public static bool       IsTypelessPartial(this DXGIFormat fmt) => dxgiformat_is_typeless_partial(fmt);
    public static bool       IsTypelessFull(this DXGIFormat fmt) => dxgiformat_is_typeless_full(fmt);
    public static bool       HasAlpha(this DXGIFormat fmt) => dxgiformat_has_alpha(fmt);
    public static int        BitsPerPixel(this DXGIFormat fmt) => (int) dxgiformat_bits_per_pixel(fmt);
    public static int        BitsPerColor(this DXGIFormat fmt) => (int) dxgiformat_bits_per_color(fmt);
    public static DXGIFormat ToSRGB(this DXGIFormat fmt) => dxgiformat_make_srgb(fmt);
    public static DXGIFormat ToLinear(this DXGIFormat fmt) => dxgiformat_make_linear(fmt);
    public static DXGIFormat ToTypeless(this DXGIFormat fmt) => dxgiformat_make_typeless(fmt);
    public static DXGIFormat ToTypelessUNorm(this DXGIFormat fmt) => dxgiformat_make_typeless_unorm(fmt);
    public static DXGIFormat ToTypelessFloat(this DXGIFormat fmt) => dxgiformat_make_typeless_float(fmt);
    public static FormatType FormatType(this DXGIFormat fmt) => dxgiformat_data_type(fmt);

    // @formatter:on

    public static ErrorCode ComputePitch(this DXGIFormat fmt, int width, int height, out int rowPitch, out int slicePitch,
        ColorPaletteFlags flags = ColorPaletteFlags.None)
    {
        ulong rowPitchU   = 0;
        ulong slicePitchU = 0;
        var   hr          = dxgiformat_compute_pitch(fmt, (ulong)width, (ulong)height, ref rowPitchU, ref slicePitchU, flags);
        rowPitch   = (int)rowPitchU;
        slicePitch = (int)slicePitchU;
        return hr;
    }

    public static (int RowPitch, int SlicePitch) ComputePitch(this DXGIFormat fmt, int width, int height,
        ColorPaletteFlags flags = ColorPaletteFlags.None)
        => ComputePitch(fmt, width, height, out var row, out var slice).ThrowIfError((row, slice));

    public static int ComputeScanLines(this DXGIFormat fmt, int height)
        => (int)dxgiformat_compute_scanlines(fmt, (ulong)height);


    // @formatter:off
    [DllImport("DirectXTexC.dll")][return: MarshalAs(UnmanagedType.I1)] private static extern bool dxgiformat_is_valid(DXGIFormat fmt);
    [DllImport("DirectXTexC.dll")][return: MarshalAs(UnmanagedType.I1)] private static extern bool dxgiformat_is_compressed(DXGIFormat fmt);
    [DllImport("DirectXTexC.dll")][return: MarshalAs(UnmanagedType.I1)] private static extern bool dxgiformat_is_packed(DXGIFormat fmt);
    [DllImport("DirectXTexC.dll")][return: MarshalAs(UnmanagedType.I1)] private static extern bool dxgiformat_is_video(DXGIFormat fmt);
    [DllImport("DirectXTexC.dll")][return: MarshalAs(UnmanagedType.I1)] private static extern bool dxgiformat_is_planar(DXGIFormat fmt);
    [DllImport("DirectXTexC.dll")][return: MarshalAs(UnmanagedType.I1)] private static extern bool dxgiformat_is_palettized(DXGIFormat fmt);
    [DllImport("DirectXTexC.dll")][return: MarshalAs(UnmanagedType.I1)] private static extern bool dxgiformat_is_depth_stencil(DXGIFormat fmt);
    [DllImport("DirectXTexC.dll")][return: MarshalAs(UnmanagedType.I1)] private static extern bool dxgiformat_is_srgb(DXGIFormat fmt);
    [DllImport("DirectXTexC.dll")][return: MarshalAs(UnmanagedType.I1)] private static extern bool dxgiformat_is_bgr(DXGIFormat fmt);
    [DllImport("DirectXTexC.dll")][return: MarshalAs(UnmanagedType.I1)] private static extern bool dxgiformat_is_typeless_partial(DXGIFormat fmt);
    [DllImport("DirectXTexC.dll")][return: MarshalAs(UnmanagedType.I1)] private static extern bool dxgiformat_is_typeless_full(DXGIFormat fmt);
    [DllImport("DirectXTexC.dll")][return: MarshalAs(UnmanagedType.I1)] private static extern bool dxgiformat_has_alpha(DXGIFormat fmt);
    [DllImport("DirectXTexC.dll")] private static extern ulong dxgiformat_bits_per_pixel(DXGIFormat fmt);
    [DllImport("DirectXTexC.dll")] private static extern ulong dxgiformat_bits_per_color(DXGIFormat fmt);
    [DllImport("DirectXTexC.dll")] private static extern DXGIFormat dxgiformat_make_srgb(DXGIFormat fmt);
    [DllImport("DirectXTexC.dll")] private static extern DXGIFormat dxgiformat_make_linear(DXGIFormat fmt);
    [DllImport("DirectXTexC.dll")] private static extern DXGIFormat dxgiformat_make_typeless(DXGIFormat fmt);
    [DllImport("DirectXTexC.dll")] private static extern DXGIFormat dxgiformat_make_typeless_unorm(DXGIFormat fmt);
    [DllImport("DirectXTexC.dll")] private static extern DXGIFormat dxgiformat_make_typeless_float(DXGIFormat fmt);
    [DllImport("DirectXTexC.dll")] private static extern FormatType dxgiformat_data_type(DXGIFormat fmt);
    [DllImport("DirectXTexC.dll")] private static extern ErrorCode dxgiformat_compute_pitch(DXGIFormat fmt, ulong width, ulong height, ref ulong rowPitch, ref ulong slicePitch, ColorPaletteFlags flags);
    [DllImport("DirectXTexC.dll")] private static extern ulong dxgiformat_compute_scanlines(DXGIFormat fmt, ulong height);
    // @formatter:on
}
