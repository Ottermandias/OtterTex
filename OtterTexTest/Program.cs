using System;
using OtterTex;

public class Program
{
    public static void TestDXGIFormat(DXGIFormat format)
    {
        format.IsValid();
        format.IsCompressed();
        format.IsPacked();
        format.IsVideo();
        format.IsPlanar();
        format.IsPalettized();
        format.IsDepthStencil();
        format.IsSRGB();
        format.IsBGR();
        format.IsTypelessPartial();
        format.IsTypelessFull();
        format.HasAlpha();
        format.BitsPerPixel();
        format.BitsPerColor();
        format.FormatType();
        format.ComputePitch(128, 128);
        format.ComputePitch(128, 128, out var row, out var slice);
        format.ComputeScanLines(128);
        format.ToSRGB();
        format.ToLinear();
        format.ToTypeless();
        format.ToTypelessUNorm();
        format.ToTypelessFloat();
    }

    public static void TestTexMeta()
    {
        var tex = new TexMeta();
        tex.ComputeIndex(0, 0, 0);
        TexMeta.FromDDS(ReadOnlySpan<byte>.Empty, out tex);
        TexMeta.FromHDR(ReadOnlySpan<byte>.Empty, out tex);
        TexMeta.FromTGA(ReadOnlySpan<byte>.Empty, out tex);
        TexMeta.FromWIC(ReadOnlySpan<byte>.Empty, out tex);
        TexMeta.FromDDS(string.Empty, out tex);
        TexMeta.FromHDR(string.Empty, out tex);
        TexMeta.FromTGA(string.Empty, out tex);
        TexMeta.FromWIC(string.Empty, out tex);
        try
        {
            tex = TexMeta.FromDDS(ReadOnlySpan<byte>.Empty);
        }
        catch
        { }

        try
        {
            tex = TexMeta.FromHDR(ReadOnlySpan<byte>.Empty);
        }
        catch
        { }

        try
        {
            tex = TexMeta.FromTGA(ReadOnlySpan<byte>.Empty);
        }
        catch
        { }

        try
        {
            tex = TexMeta.FromWIC(ReadOnlySpan<byte>.Empty);
        }
        catch
        { }

        try
        {
            tex = TexMeta.FromDDS(string.Empty);
        }
        catch
        { }

        try
        {
            tex = TexMeta.FromHDR(string.Empty);
        }
        catch
        { }

        try
        {
            tex = TexMeta.FromTGA(string.Empty);
        }
        catch
        { }

        try
        {
            tex = TexMeta.FromWIC(string.Empty);
        }
        catch
        { }
    }

    public static void TestImage()
    {
        var x = new Image();
        try
        {
            x.Save("invalid_path");
        }
        catch
        { }
    }

    public static void TestScratchImage()
    {
        var image = new ScratchImage();
        image.Dispose();
        using (var test = new ScratchImage())
        { }

        image = new ScratchImage();
        var overridden = image.OverrideFormat(DXGIFormat.BC1Typeless);
        image.GetImage(0, 0, 0, out var t);
        try
        {
            var im = image.GetImage(0, 0, 0);
        }
        catch
        { }

        var              images    = image.Images;
        var              pixels    = image.Pixels;
        ref readonly var meta      = ref image.Meta;
        var              allOpaque = image.IsAlphaAllOpaque;

        var ec = ScratchImage.Initialize(new TexMeta(), out image);
        ec = ScratchImage.Initialize1D(DXGIFormat.BC5UNorm, 128, 1, 0, out image);
        ec = ScratchImage.Initialize2D(DXGIFormat.BC5UNorm, 128, 128, 1, 0, out image);
        ec = ScratchImage.Initialize3D(DXGIFormat.BC5UNorm, 128, 128, 1, 0, out image);
        ec = ScratchImage.InitializeCube(DXGIFormat.BC5UNorm, 128, 128, 1, 0, out image);

        ec = ScratchImage.Initialize(new Image(), out image);
        ec = ScratchImage.InitializeArray(ReadOnlySpan<Image>.Empty, out image);
        ec = ScratchImage.InitializeCube(ReadOnlySpan<Image>.Empty, out image);
        ec = ScratchImage.Initialize3D(ReadOnlySpan<Image>.Empty, out image);

        ec = ScratchImage.LoadDDS(ReadOnlySpan<byte>.Empty, out image);
        ec = ScratchImage.LoadTGA(ReadOnlySpan<byte>.Empty, out image);
        ec = ScratchImage.LoadWIC(ReadOnlySpan<byte>.Empty, out image);
        ec = ScratchImage.LoadHDR(ReadOnlySpan<byte>.Empty, out image);
        ec = image.SaveDDS("invalid_path");

        ec = image.FlipRotate(out image, FlipRotateFlags.Rotate180);
        ec = image.Resize(out image, 64, 64);
        ec = image.Convert(out image, DXGIFormat.BC1Typeless);
        ec = image.ConvertToSinglePlane(out image);
        ec = image.GenerateMipMaps(out image);
        ec = image.GenerateMipMaps3D(out image);
        ec = image.ScaleMipMapsAlphaForCoverage(out image, 0, 0.5f);
        ec = image.PremultiplyAlpha(out image);
        ec = image.Compress(out image, DXGIFormat.BC5UNorm);
        ec = image.Decompress(out image, DXGIFormat.G8R8G8B8UNorm);
        ec = image.ComputeNormalMap(out image, DXGIFormat.G8R8G8B8UNorm);
    }

    public static int Main(string[] args)
    {
        try
        {
            OtterTex.NativeDll.Initialize();
            TestDXGIFormat(DXGIFormat.BC7UNorm);
            TestTexMeta();
            TestImage();
            TestScratchImage();
            return 0;
        }
        catch (Exception e)
        {
            Console.Write($"{e}");
        }

        return 1;
    }
}
