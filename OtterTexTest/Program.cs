using System;
using OtterTex;

public class Program
{
    public static int Main(string[] args)
    {
        try
        {
            var file = ScratchImage.LoadFromDDSFile(@"h:\DXT5.dds");
            
            Console.WriteLine($"{file.ImageCount} {file.PixelCount} {file.IsOpaque} {file.Meta.Height} {file.Meta.Width} {file.Meta.Format} {file.IsOpaque} {file.Meta.MipLevels}");
            var decompressed = file.Decompress(DXGIFormat.R8G8B8A8UNorm);
            file = decompressed;
            Console.WriteLine($"{file.ImageCount} {file.PixelCount} {file.IsOpaque} {file.Meta.Height} {file.Meta.Width} {file.Meta.Format} {file.IsOpaque} {file.Meta.MipLevels}");
            file.SaveToDDSFile(@"h:\rgba.dds");
            file = file.Compress(DXGIFormat.BC3UNorm, CompressFlags.Default, 0.5f);
            Console.WriteLine($"{file.ImageCount} {file.PixelCount} {file.IsOpaque} {file.Meta.Height} {file.Meta.Width} {file.Meta.Format} {file.IsOpaque} {file.Meta.MipLevels}");
            file.SaveToDDSFile(@"h:\DXT52.dds");
            file = decompressed.Compress(DXGIFormat.BC7UNorm, CompressFlags.Default, 0.5f);
            Console.WriteLine($"{file.ImageCount} {file.PixelCount} {file.IsOpaque} {file.Meta.Height} {file.Meta.Width} {file.Meta.Format} {file.IsOpaque} {file.Meta.MipLevels}");
            file.SaveToDDSFile(@"h:\BC7.dds");
        }
        catch (Exception e)
        {
            Console.Write($"{e}");
        }

        return 0;
    }
}
