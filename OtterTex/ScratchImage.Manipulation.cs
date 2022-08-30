using System;
using System.Runtime.InteropServices;

namespace OtterTex;

public partial class ScratchImage
{
    public unsafe ErrorCode FlipRotate(out ScratchImage result, FlipRotateFlags flags)
    {
        result = new ScratchImage();
        return scratchimage_flip_rotate((IntPtr)_data.Image, _data.NumImages, in _data.Meta, flags, ref result._data);
    }

    public ScratchImage FlipRotate(FlipRotateFlags flags)
        => FlipRotate(out var result, flags).ThrowIfError(result);

    public unsafe ErrorCode Resize(out ScratchImage result, int width, int height, FilterFlags flags = FilterFlags.Default)
    {
        result = new ScratchImage();
        return scratchimage_resize((IntPtr)_data.Image, _data.NumImages, in _data.Meta, (ulong)width, (ulong)height, flags, ref result._data);
    }

    public ScratchImage Resize(int width, int height, FilterFlags flags = FilterFlags.Default)
        => Resize(out var result, width, height, flags).ThrowIfError(result);

    public unsafe ErrorCode Convert(out ScratchImage result, DXGIFormat fmt, float threshold = 0.5f, FilterFlags flags = FilterFlags.Default)
    {
        result = new ScratchImage();
        return scratchimage_convert((IntPtr)_data.Image, _data.NumImages, in _data.Meta, fmt, flags, threshold, ref result._data);
    }

    public ScratchImage Convert(DXGIFormat fmt, float threshold = 0.5f, FilterFlags flags = FilterFlags.Default)
        => Convert(out var result, fmt, threshold, flags).ThrowIfError(result);

    public unsafe ErrorCode ConvertToSinglePlane(out ScratchImage result)
    {
        result = new ScratchImage();
        return scratchimage_convert_to_single_plane((IntPtr)_data.Image, _data.NumImages, in _data.Meta, ref result._data);
    }

    public ScratchImage ConvertToSinglePlane()
        => ConvertToSinglePlane(out var result).ThrowIfError(result);

    public unsafe ErrorCode GenerateMipMaps(out ScratchImage result, int levels = 0, FilterFlags flags = FilterFlags.Default)
    {
        result = new ScratchImage();
        return scratchimage_generate_mipmaps((IntPtr)_data.Image, _data.NumImages, in _data.Meta, flags, (ulong)levels, ref result._data);
    }

    public ScratchImage GenerateMipMaps(int levels = 0, FilterFlags flags = FilterFlags.Default)
        => GenerateMipMaps(out var result, levels, flags).ThrowIfError(result);

    public unsafe ErrorCode GenerateMipMaps3D(out ScratchImage result, int levels = 0, FilterFlags flags = FilterFlags.Default)
    {
        result = new ScratchImage();
        return scratchimage_generate_mipmaps_3d((IntPtr)_data.Image, _data.NumImages, in _data.Meta, flags, (ulong)levels, ref result._data);
    }

    public ScratchImage GenerateMipMaps3D(int levels = 0, FilterFlags flags = FilterFlags.Default)
        => GenerateMipMaps(out var result, levels, flags).ThrowIfError(result);

    public unsafe ErrorCode ScaleMipMapsAlphaForCoverage(out ScratchImage result, int item, float alphaReference)
    {
        result = new ScratchImage();
        return scratchimage_scale_mipmaps_alpha_for_coverage((IntPtr)_data.Image, _data.NumImages, in _data.Meta, (ulong)item, alphaReference,
            ref result._data);
    }

    public ScratchImage ScaleMipMapsAlphaForCoverage(int item, float alphaReference)
        => ScaleMipMapsAlphaForCoverage(out var result, item, alphaReference).ThrowIfError(result);

    public unsafe ErrorCode PremultiplyAlpha(out ScratchImage result, AlphaFlags flags = AlphaFlags.Default)
    {
        result = new ScratchImage();
        return scratchimage_premultiply_alpha((IntPtr)_data.Image, _data.NumImages, in _data.Meta, flags, ref result._data);
    }

    public ScratchImage PremultiplyAlpha(AlphaFlags flags = AlphaFlags.Default)
        => PremultiplyAlpha(out var result, flags).ThrowIfError(result);

    public unsafe ErrorCode Compress(out ScratchImage result, DXGIFormat format, CompressFlags flags = CompressFlags.Default,
        float threshold = 0.5f)
    {
        result = new ScratchImage();
        return scratchimage_compress((IntPtr)_data.Image, _data.NumImages, in _data.Meta, format, flags, threshold, ref result._data);
    }

    public ScratchImage Compress(DXGIFormat format, CompressFlags flags = CompressFlags.Default, float threshold = 0.5f)
        => Compress(out var result, format, flags, threshold).ThrowIfError(result);

    public unsafe ErrorCode Decompress(out ScratchImage result, DXGIFormat format)
    {
        result = new ScratchImage();
        return scratchimage_decompress((IntPtr)_data.Image, _data.NumImages, in _data.Meta, format, ref result._data);
    }

    public ScratchImage Decompress(DXGIFormat format)
        => Decompress(out var result, format).ThrowIfError(result);

    public unsafe ErrorCode ComputeNormalMap(out ScratchImage result, DXGIFormat fmt, MapFlags flags = MapFlags.Default, float amplitude = 0.5f)
    {
        result = new ScratchImage();
        return scratchimage_compute_normal_map((IntPtr)_data.Image, _data.NumImages, in _data.Meta, flags, amplitude, fmt, ref result._data);
    }

    public ScratchImage ComputeNormalMap(DXGIFormat fmt, MapFlags flags = MapFlags.Default, float amplitude = 0.5f)
        => ComputeNormalMap(out var result, fmt, flags, amplitude).ThrowIfError(result);

    // @formatter:off
    [DllImport("DirectXTexC.dll")] private static extern ErrorCode scratchimage_flip_rotate(IntPtr images, ulong numImages, in TexMeta meta, FlipRotateFlags flags, ref ScratchImageData data);
    [DllImport("DirectXTexC.dll")] private static extern ErrorCode scratchimage_resize(IntPtr images, ulong numImages, in TexMeta meta, ulong width, ulong height, FilterFlags flags, ref ScratchImageData data);
    [DllImport("DirectXTexC.dll")] private static extern ErrorCode scratchimage_convert(IntPtr images, ulong numImages, in TexMeta meta, DXGIFormat fmt, FilterFlags flags, float threshold, ref ScratchImageData data);
    [DllImport("DirectXTexC.dll")] private static extern ErrorCode scratchimage_convert_to_single_plane(IntPtr images, ulong numImages, in TexMeta meta, ref ScratchImageData data);
    [DllImport("DirectXTexC.dll")] private static extern ErrorCode scratchimage_generate_mipmaps(IntPtr images, ulong numImages, in TexMeta meta, FilterFlags flags, ulong levels, ref ScratchImageData data);
    [DllImport("DirectXTexC.dll")] private static extern ErrorCode scratchimage_generate_mipmaps_3d(IntPtr images, ulong numImages, in TexMeta meta, FilterFlags flags, ulong levels, ref ScratchImageData data);
    [DllImport("DirectXTexC.dll")] private static extern ErrorCode scratchimage_scale_mipmaps_alpha_for_coverage(IntPtr images, ulong numImages, in TexMeta meta, ulong item, float alphaReference, ref ScratchImageData data);
    [DllImport("DirectXTexC.dll")] private static extern ErrorCode scratchimage_premultiply_alpha(IntPtr images, ulong numImages, in TexMeta meta, AlphaFlags flags, ref ScratchImageData data);
    [DllImport("DirectXTexC.dll")] private static extern ErrorCode scratchimage_compress(IntPtr images, ulong numImages, in TexMeta meta, DXGIFormat fmt, CompressFlags flags, float threshold, ref ScratchImageData data);
    [DllImport("DirectXTexC.dll")] private static extern ErrorCode scratchimage_decompress(IntPtr images, ulong numImages, in TexMeta meta, DXGIFormat fmt, ref ScratchImageData data);
    [DllImport("DirectXTexC.dll")] private static extern ErrorCode scratchimage_compute_normal_map(IntPtr images, ulong numImages, in TexMeta meta, MapFlags flags, float amplitude, DXGIFormat fmt, ref ScratchImageData data);
    // @formatter:on
}
