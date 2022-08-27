using System;
using System.Diagnostics.CodeAnalysis;

namespace OtterTex;

public interface ITexMeta
{
    public int                  Width      { get; }
    public int                  Height     { get; }
    public int                  Depth      { get; }
    public int                  ArraySize  { get; }
    public D3DResourceMiscFlags MiscFlags  { get; }
    public D3DAlphaMode         MiscFlags2 { get; }
    public DXGIFormat           Format     { get; }
    public short                MipLevels  { get; }
    public TexDimension         Dimension  { get; }

    public bool IsCubeMap            { get; }
    public bool IsPremultipliedAlpha { get; }
    public bool IsVolumeMap          { get; }
}

public sealed class TexMeta : ITexMeta
{
    public int                  Width      { get; set; }
    public int                  Height     { get; set; }
    public int                  Depth      { get; set; }
    public int                  ArraySize  { get; set; }
    public D3DResourceMiscFlags MiscFlags  { get; set; }
    public D3DAlphaMode         MiscFlags2 { get; set; }
    public DXGIFormat           Format     { get; set; }
    public short                MipLevels  { get; set; }
    public TexDimension         Dimension  { get; set; }

    public TexMeta(int width, int height, int depth, int arraySize, D3DResourceMiscFlags flags, D3DAlphaMode flags2, DXGIFormat format,
        short mipLevels, TexDimension dimension)
    {
        Width      = width;
        Height     = height;
        Depth      = depth;
        ArraySize  = arraySize;
        MiscFlags  = flags;
        MiscFlags2 = flags2;
        Format     = format;
        MipLevels  = mipLevels;
        Dimension  = dimension;
    }

    public bool IsCubeMap
        => MiscFlags.HasFlag(D3DResourceMiscFlags.TextureCube);

    public bool IsPremultipliedAlpha
        => (MiscFlags2 & D3DAlphaMode.AlphaModeMask) == D3DAlphaMode.Premultiplied;

    public void SetAlphaMode(D3DAlphaMode mode)
        => MiscFlags2 = (MiscFlags2 & ~D3DAlphaMode.AlphaModeMask) | mode;

    public bool IsVolumeMap
        => Dimension == TexDimension.Tex3D;

    public static TexMeta FromDDSData(IntPtr source, int length, DDSParseFlags flags)
        => TexMetaHelper.Instance.GetMetaDataFromDDSMemory(source, length, flags);

    public static unsafe TexMeta FromDDSData(ReadOnlySpan<byte> source, DDSParseFlags flags)
    {
        fixed (byte* ptr = source)
        {
            return FromDDSData((IntPtr)ptr, source.Length, flags);
        }
    }

    public static bool FromDDSData(IntPtr source, int length, DDSParseFlags flags, [NotNullWhen(true)] out TexMeta? meta)
    {
        try
        {
            meta = TexMetaHelper.Instance.GetMetaDataFromDDSMemory(source, length, flags);
            return true;
        }
        catch
        {
            meta = null;
            return false;
        }
    }

    public static unsafe bool FromDDSData(ReadOnlySpan<byte> source, DDSParseFlags flags, [NotNullWhen(true)] out TexMeta? meta)
    {
        fixed (byte* ptr = source)
        {
            return FromDDSData((IntPtr)ptr, source.Length, flags, out meta);
        }
    }
}

public abstract class TexMetaHelper
{
    internal static readonly TexMetaHelper Instance;

    static TexMetaHelper()
        => Instance = Utility.LoadStatic<TexMetaHelper>("OtterTex.TexMetaHelperImpl");

    public abstract TexMeta GetMetaDataFromDDSMemory(IntPtr source, int size, DDSParseFlags flags = DDSParseFlags.None);
    public abstract TexMeta GetMetaDataFromDDSFile(string path, DDSParseFlags flags = DDSParseFlags.None);

    public abstract TexMeta GetMetaDataFromHDRMemory(IntPtr source, int size);
    public abstract TexMeta GetMetaDataFromHDRFile(string path);

    public abstract TexMeta GetMetaDataFromTGAMemory(IntPtr source, int size, TGAParseFlags flags = TGAParseFlags.None);
    public abstract TexMeta GetMetaDataFromTGAFile(string path, TGAParseFlags flags = TGAParseFlags.None);

    public abstract TexMeta GetMetaDataFromWICMemory(IntPtr source, int size, WICParseFlags flags = WICParseFlags.None);
    public abstract TexMeta GetMetaDataFromWICFile(string path, WICParseFlags flags = WICParseFlags.None);

    public abstract int WriteDDSHeader(TexMeta meta, IntPtr data, int size, DDSParseFlags flags);
}
