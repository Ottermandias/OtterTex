using System;
using System.Threading;

namespace OtterTex;

public abstract class ScratchImage
{
    public abstract ITexMeta     Meta       { get; }
    public abstract int          ImageCount { get; }
    public abstract int          PixelCount { get; }
    public abstract bool         IsOpaque   { get; }
    public abstract void         Initialize(TexMeta meta, ColorPaletteFlags flags);
    public abstract void         Initialize1D(DXGIFormat fmt, int length, int arraySize, int mipLevels, ColorPaletteFlags flags);
    public abstract void         Initialize2D(DXGIFormat fmt, int width, int height, int arraySize, int mipLevels, ColorPaletteFlags flags);
    public abstract void         Initialize3D(DXGIFormat fmt, int width, int height, int depth, int mipLevels, ColorPaletteFlags flags);
    public abstract void         InitializeCube(DXGIFormat fmt, int width, int height, int nCubes, int mipLevels, ColorPaletteFlags flags);
    public abstract void         Release();
    public abstract bool         OverrideFormat(DXGIFormat fmt);
    public abstract Image        GetImage(int mip, int item, int slice);
    public abstract Image[]      GetImages();
    public abstract ScratchImage FlipRotate(FlipRotateFlags flags);
    public abstract ScratchImage Resize(int width, int height, FilterFlags flags);
    public abstract ScratchImage Convert(DXGIFormat format, FilterFlags flags, float threshold);
    public abstract ScratchImage ConvertToSinglePlane();
    public abstract ScratchImage GenerateMipMaps(int levels, FilterFlags flags);
    public abstract ScratchImage GenerateMipMaps3D(int levels, FilterFlags flags);
    public abstract ScratchImage ScaleMipMapsAlphaForCoverage(int item, float alphaReference);
    public abstract ScratchImage PremultiplyAlpha(AlphaFlags flags);
    public abstract ScratchImage Compress(DXGIFormat fmt, CompressFlags flags, float threshold);
    public abstract ScratchImage Decompress(DXGIFormat fmt);
    public abstract ScratchImage ComputeNormalMap(MapFlags flags, float amplitude, DXGIFormat fmt);
    public abstract int          SaveToDDSMemory(IntPtr target, int maxLength, DdsFlags flags);
    public abstract void         SaveToDDSFile(string path, DdsFlags flags);

    public unsafe int SaveToDDSMemory(Span<byte> data, DdsFlags flags)
    {
        fixed (byte* ptr = data)
        {
            return SaveToDDSMemory((IntPtr)ptr, data.Length, flags);
        }
    }

    public unsafe byte[] Encode(DdsFlags flags)
    {
        var size = SaveToDDSMemory(IntPtr.Zero, 0, flags);
        var ret  = new byte[size];
        fixed (byte* ptr = ret)
        {
            return SaveToDDSMemory((IntPtr)ptr, ret.Length, flags) <= ret.Length
                ? ret
                : Array.Empty<byte>();
        }
    }
}
