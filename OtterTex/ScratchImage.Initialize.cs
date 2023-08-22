using System;
using System.Runtime.InteropServices;

namespace OtterTex;

public partial class ScratchImage
{
    public static ErrorCode Initialize(in TexMeta meta, out ScratchImage image, ColorPaletteFlags flags = ColorPaletteFlags.None)
    {
        image = new ScratchImage();
        return scratchimage_initialize(ref image._data, in meta, flags);
    }

    public static ScratchImage Initialize(in TexMeta meta, ColorPaletteFlags flags = ColorPaletteFlags.None)
        => Initialize(in meta, out var image, flags).ThrowIfError(image);

    public static ErrorCode Initialize1D(DXGIFormat format, int length, int arraySize, int mipLevels, out ScratchImage image,
        ColorPaletteFlags flags = ColorPaletteFlags.None)
    {
        image = new ScratchImage();
        return scratchimage_initialize1D(ref image._data, format, (ulong)length, (ulong)arraySize, (ulong)mipLevels, flags);
    }

    public static ScratchImage Initialize1D(DXGIFormat format, int length, int arraySize, int mipLevels,
        ColorPaletteFlags flags = ColorPaletteFlags.None)
        => Initialize1D(format, length, arraySize, mipLevels, out var image, flags).ThrowIfError(image);

    public static ErrorCode Initialize2D(DXGIFormat format, int width, int height, int arraySize, int mipLevels, out ScratchImage image,
        ColorPaletteFlags flags = ColorPaletteFlags.None)
    {
        image = new ScratchImage();
        return scratchimage_initialize2D(ref image._data, format, (ulong)width, (ulong)height, (ulong)arraySize, (ulong)mipLevels, flags);
    }

    public static ScratchImage Initialize2D(DXGIFormat format, int width, int height, int arraySize, int mipLevels,
        ColorPaletteFlags flags = ColorPaletteFlags.None)
        => Initialize2D(format, width, height, arraySize, mipLevels, out var image, flags).ThrowIfError(image);

    public static ErrorCode Initialize3D(DXGIFormat format, int width, int height, int depth, int mipLevels, out ScratchImage image,
        ColorPaletteFlags flags = ColorPaletteFlags.None)
    {
        image = new ScratchImage();
        return scratchimage_initialize3D(ref image._data, format, (ulong)width, (ulong)height, (ulong)depth, (ulong)mipLevels, flags);
    }

    public static ScratchImage Initialize3D(DXGIFormat format, int width, int height, int depth, int mipLevels,
        ColorPaletteFlags flags = ColorPaletteFlags.None)
        => Initialize3D(format, width, height, depth, mipLevels, out var image, flags).ThrowIfError(image);

    public static ErrorCode InitializeCube(DXGIFormat format, int width, int height, int numCubes, int mipLevels, out ScratchImage image,
        ColorPaletteFlags flags = ColorPaletteFlags.None)
    {
        image = new ScratchImage();
        return scratchimage_initialize_cube(ref image._data, format, (ulong)width, (ulong)height, (ulong)numCubes, (ulong)mipLevels, flags);
    }

    public static ScratchImage InitializeCube(DXGIFormat format, int width, int height, int numCubes, int mipLevels,
        ColorPaletteFlags flags = ColorPaletteFlags.None)
        => InitializeCube(format, width, height, numCubes, mipLevels, out var image, flags).ThrowIfError(image);


    public static ErrorCode Initialize(in Image sourceImage, out ScratchImage image, bool allow1D = false,
        ColorPaletteFlags flags = ColorPaletteFlags.None)
    {
        image = new ScratchImage();
        return scratchimage_initialize_from_image(ref image._data, in sourceImage, allow1D, flags);
    }

    public static ScratchImage Initialize(in Image sourceImage, bool allow1D = false, ColorPaletteFlags flags = ColorPaletteFlags.None)
        => Initialize(in sourceImage, out var image, allow1D, flags).ThrowIfError(image);

    public static unsafe ErrorCode InitializeArray(ReadOnlySpan<Image> images, out ScratchImage image, bool allow1D = false,
        ColorPaletteFlags flags = ColorPaletteFlags.None)
    {
        image = new ScratchImage();
        fixed (Image* ptr = images)
        {
            return scratchimage_initialize_array_from_images(ref image._data, (IntPtr)ptr, (ulong)images.Length, allow1D, flags);
        }
    }

    public static ScratchImage InitializeArray(ReadOnlySpan<Image> images, bool allow1D = false,
        ColorPaletteFlags flags = ColorPaletteFlags.None)
        => InitializeArray(images, out var image, allow1D, flags).ThrowIfError(image);

    public static unsafe ErrorCode InitializeCube(ReadOnlySpan<Image> images, out ScratchImage image,
        ColorPaletteFlags flags = ColorPaletteFlags.None)
    {
        image = new ScratchImage();
        fixed (Image* ptr = images)
        {
            return scratchimage_initialize_cube_from_images(ref image._data, (IntPtr)ptr, (ulong)images.Length, flags);
        }
    }

    public static ScratchImage InitializeCube(ReadOnlySpan<Image> images, ColorPaletteFlags flags = ColorPaletteFlags.None)
        => InitializeCube(images, out var image, flags).ThrowIfError(image);

    public static unsafe ErrorCode Initialize3D(ReadOnlySpan<Image> images, out ScratchImage image,
        ColorPaletteFlags flags = ColorPaletteFlags.None)
    {
        image = new ScratchImage();
        fixed (Image* ptr = images)
        {
            return scratchimage_initialize_3D_from_images(ref image._data, (IntPtr)ptr, (ulong)images.Length, flags);
        }
    }

    public static ScratchImage Initialize3D(ReadOnlySpan<Image> images, ColorPaletteFlags flags = ColorPaletteFlags.None)
        => Initialize3D(images, out var image, flags).ThrowIfError(image);

    public static unsafe ErrorCode FromRGBA(ReadOnlySpan<byte> data, int width, int height, out ScratchImage scratchImage)
    {
        var ec = Initialize2D(DXGIFormat.R8G8B8A8UNorm, width, height, 1, 1, out scratchImage);
        if (!ec)
            return ec;

        var size = width * height * 4;
        if (data.Length < size || scratchImage.Pixels.Length < size)
            return Marshal.GetHRForException(new ArgumentOutOfRangeException());

        var pixels = scratchImage._data.Data;
        fixed (byte* ptr = data)
        {
            copy_array((IntPtr)pixels, (IntPtr)ptr, (ulong)size);
        }

        return ErrorCode.Ok;
    }

    public static ScratchImage FromRGBA(ReadOnlySpan<byte> data, int width, int height)
        => FromRGBA(data, width, height, out var s).ThrowIfError(s);

    // @formatter:off

    [DllImport("DirectXTexC.dll")] private static extern ErrorCode scratchimage_initialize(ref ScratchImageData data, in TexMeta meta, ColorPaletteFlags flags);
    [DllImport("DirectXTexC.dll")] private static extern ErrorCode scratchimage_initialize1D(ref ScratchImageData data, DXGIFormat fmt, ulong length, ulong arraySize, ulong mipLevels, ColorPaletteFlags flags);
    [DllImport("DirectXTexC.dll")] private static extern ErrorCode scratchimage_initialize2D(ref ScratchImageData data, DXGIFormat fmt, ulong width, ulong height, ulong arraySize, ulong mipLevels, ColorPaletteFlags flags);
    [DllImport("DirectXTexC.dll")] private static extern ErrorCode scratchimage_initialize3D(ref ScratchImageData data, DXGIFormat fmt, ulong width, ulong height, ulong depth, ulong mipLevels, ColorPaletteFlags flags);
    [DllImport("DirectXTexC.dll")] private static extern ErrorCode scratchimage_initialize_cube(ref ScratchImageData data, DXGIFormat fmt, ulong width, ulong height, ulong numCubes, ulong mipLevels, ColorPaletteFlags flags);
    [DllImport("DirectXTexC.dll")] private static extern ErrorCode scratchimage_initialize_from_image(ref ScratchImageData data, in Image image, bool allow1D, ColorPaletteFlags flags);
    [DllImport("DirectXTexC.dll")] private static extern ErrorCode scratchimage_initialize_array_from_images(ref ScratchImageData data, IntPtr images, ulong numImages, bool allow1D, ColorPaletteFlags flags);
    [DllImport("DirectXTexC.dll")] private static extern ErrorCode scratchimage_initialize_cube_from_images(ref ScratchImageData data, IntPtr images, ulong numImages, ColorPaletteFlags flags);
    [DllImport("DirectXTexC.dll")] private static extern ErrorCode scratchimage_initialize_3D_from_images(ref ScratchImageData data, IntPtr images, ulong depth, ColorPaletteFlags flags);
    [DllImport("DirectXTexC.dll")] private static extern void copy_array(IntPtr target, IntPtr source, ulong size);
    // @formatter:on
}
