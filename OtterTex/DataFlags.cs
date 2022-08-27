using System;

namespace OtterTex;

[Flags]
public enum ColorPaletteFlags : ulong
{
    None        = 0x00,
    LegacyDWORD = 0x01,
    Paragraph   = 0x02,
    YMM         = 0x04,
    ZMM         = 0x08,

    Page4k       = 0x02_00,
    BadDXTnTails = 0x10_00,

    _24BPP = 0x01_0000,
    _16BPP = 0x02_0000,
    _8BPP  = 0x04_0000,
}

public enum FormatType
{
    Typeless,
    Float,
    UNorm,
    SNorm,
    UInt,
    SInt,
}

public enum TexDimension : byte
{
    Unknown = 0,
    Buffer  = 1,
    Tex1D   = 2,
    Tex2D   = 3,
    Tex3D   = 4,
}

[Flags]
public enum D3DResourceMiscFlags : uint
{
    GenerateMips                 = 0x000001,
    Shared                       = 0x000002,
    TextureCube                  = 0x000004,
    DrawIndirectArgs             = 0x000010,
    BufferAllowRawViews          = 0x000020,
    BufferStructured             = 0x000040,
    ResourceClamp                = 0x000080,
    SharedKeyedMutex             = 0x000100,
    GDICompatible                = 0x000200,
    SharedNTHandle               = 0x000800,
    RestrictedContent            = 0x001000,
    RestrictSharedResource       = 0x002000,
    RestrictSharedResourceDriver = 0x004000,
    Guarded                      = 0x008000,
    TilePool                     = 0x020000,
    Tiled                        = 0x040000,
    HWProtected                  = 0x080000,
    SharedDisplayable,
    SharedExclusiveWriter,
};

[Flags]
public enum D3DAlphaMode : uint
{
    Unknown       = 0,
    Straight      = 1,
    Premultiplied = 2,
    Opaque        = 3,
    Custom        = 4,

    AlphaModeMask = Straight | Premultiplied | Opaque,
};
