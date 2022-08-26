using System;

namespace OtterTex;

[Flags]
public enum DDSParseFlags : ulong
{
    None               = 0x00,
    LegacyDWORD        = 0x01,
    NoLegacyExpansion  = 0x02,
    NoR10B10G10A2Fixup = 0x04,
    ForceRGB           = 0x08,
    No16BPP            = 0x10,
    ExpandLuminance    = 0x20,
    BadDXTnTails       = 0x40,

    ForceDX10      = 0x01_0000,
    ForceDX10Misc2 = 0x02_0000,
    ForceDX9Legacy = 0x04_0000,

    AllowLargeFiles = 0x01_000000,
}

[Flags]
public enum TGAParseFlags : ulong
{
    None              = 0x00,
    BGR               = 0x01,
    AllowAllZeroAlpha = 0x02,
    IgnoreSRGB        = 0x10,
    ForceSRGB         = 0x20,
    ForceLinear       = 0x40,
    DefaultSRGB       = 0x80,
}

[Flags]
public enum WICParseFlags : ulong
{
    None        = 0x00,
    ForceRGB    = 0x01,
    NoX2Bias    = 0x02,
    No16BPP     = 0x04,
    AllowMono   = 0x04,
    AllFrames   = 0x10,
    IgnoreSRGB  = 0x20,
    ForceSRGB   = 0x40,
    ForceLinear = 0x80,

    DefaultSRGB = 0x01_00,

    Dither          = 0x01_0000,
    DitherDiffusion = 0x02_0000,
    FilterPoint     = 0x10_0000,
    FilterLinear    = 0x20_0000,
    FilterCubic     = 0x30_0000,
    FilterFant      = 0x40_0000,
}
