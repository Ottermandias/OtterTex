using System;
using System.Runtime.InteropServices;

namespace OtterTex;

public partial class ScratchImage : IDisposable
{
    public ScratchImage()
    {
        scratchimage_ctor(ref _data);
    }

    public void Dispose()
    {
        scratchimage_release(ref _data);
    }

    ~ScratchImage()
    {
        Dispose();
    }

    public bool OverrideFormat(DXGIFormat fmt)
        => scratchimage_override_format(ref _data, fmt);

    public unsafe bool GetImage(int mip, int item, int slice, out Image image)
    {
        var ret = scratchimage_get_image(ref _data, (ulong)mip, (ulong)item, (ulong)slice);
        if (ret == IntPtr.Zero)
        {
            image = default;
            return false;
        }

        image = *(Image*)ret;
        return true;
    }

    public Image GetImage(int mip, int item, int slice)
    {
        if (GetImage(mip, item, slice, out var image))
            return image;

        throw new ArgumentOutOfRangeException("Invalid image access.");
    }

    public unsafe ReadOnlySpan<Image> Images
        => new(_data.Image, (int)_data.NumImages);

    public unsafe ReadOnlySpan<byte> Pixels
        => new(_data.Data, (int)_data.Size);

    public ref readonly TexMeta Meta
        => ref _data.Meta;

    public bool IsAlphaAllOpaque
        => scratchimage_is_alpha_all_opaque(ref _data);

    private ScratchImageData _data;


    [StructLayout(LayoutKind.Sequential)]
    private unsafe struct ScratchImageData
    {
        public ulong   NumImages;
        public ulong   Size;
        public TexMeta Meta;
        public Image*  Image;
        public byte*   Data;
    }

    // @formatter:off
    [DllImport("DirectXTexC.dll")] private static extern void scratchimage_ctor(ref ScratchImageData data);
    [DllImport("DirectXTexC.dll")] private static extern void scratchimage_release(ref ScratchImageData data);
    [DllImport("DirectXTexC.dll")][return: MarshalAs(UnmanagedType.I1)] private static extern bool scratchimage_override_format(ref ScratchImageData data, DXGIFormat fmt);
    [DllImport("DirectXTexC.dll")] private static extern IntPtr scratchimage_get_image(ref ScratchImageData data, ulong mip, ulong item, ulong slice);
    [DllImport("DirectXTexC.dll")][return: MarshalAs(UnmanagedType.I1)] private static extern bool scratchimage_is_alpha_all_opaque(ref ScratchImageData data);
    // @formatter:on
}
