using System;

namespace OtterTex;

[Flags]
public enum FlipRotateFlags : ulong
{
    Rotate0        = 0x00,
    Rotate90       = 0x01,
    Rotate180      = 0x02,
    Rotate270      = 0x03,
    FlipHorizontal = 0x08,
    FlipVertical   = 0x10,
}

[Flags]
public enum FilterFlags : ulong
{
    Default = 0x00,
    WrapU   = 0x01,
    WrapV   = 0x02,
    WrapW   = 0x04,
    Wrap    = WrapU | WrapV | WrapW,
    MirrorU = 0x10,
    MirrorV = 0x20,
    MirrorW = 0x40,
    Mirror  = MirrorU | MirrorV | MirrorW,

    SeparateAlpha = 0x01_00,
    FloatX2Bias   = 0x02_00,
    RGBCopyRed    = 0x10_00,
    RGBCopyGreen  = 0x20_00,
    RGBCopyBlue   = 0x40_00,

    Dither          = 0x01_0000,
    DitherDiffusion = 0x02_0000,
    DitherMask      = 0x0F_0000,

    Point    = 0x10_0000,
    Linear   = 0x20_0000,
    Cubic    = 0x30_0000,
    Box      = 0x40_0000,
    Fant     = Box,
    Triangle = 0x50_0000,
    ModeMask = 0xF0_0000,

    SRGBIn   = 0x01_000000,
    SRGBOut  = 0x02_000000,
    SRGB     = SRGBIn | SRGBOut,
    SRGBMask = 0x0F_000000,

    ForceNonWIC = 0x10_000000,
    ForceWIC    = 0x20_000000,
}

[Flags]
public enum AlphaFlags : ulong
{
    Default    = 0x00,
    IgnoreSRGB = 0x01,
    Reverse    = 0x02,

    SRGBIn  = 0x01_000000,
    SRGBOut = 0x02_000000,
    SRGB    = SRGBIn | SRGBOut,
}

[Flags]
public enum CompressFlags : ulong
{
    Default = 0x00,

    RGBDither      = 0x01_0000,
    ADither        = 0x02_0000,
    Dither         = 0x03_0000,
    Uniform        = 0x04_0000,
    BC7Use3Subsets = 0x08_0000,
    BC7Quick       = 0x10_0000,

    SRGBIn   = 0x01_000000,
    SRGBOut  = 0x02_000000,
    SRBG     = SRGBIn | SRGBOut,
    Parallel = 0x10_000000,
}

[Flags]
public enum MapFlags : ulong
{
    Default          = 0,
    ChannelRed       = 0x01,
    ChannelGreen     = 0x02,
    ChannelBlue      = 0x03,
    ChannelAlpha     = 0x04,
    ChannelLuminance = 0x05,

    MirrorU          = 0x10_00,
    MirrorV          = 0x20_00,
    Mirror           = 0x30_00,
    InvertSign       = 0x40_00,
    ComputeOcclusion = 0x80_00,
}
