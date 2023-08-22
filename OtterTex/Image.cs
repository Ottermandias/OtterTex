using System;
using System.Runtime.InteropServices;

namespace OtterTex;

[StructLayout(LayoutKind.Sequential)]
public unsafe partial struct Image
{
    static Image()
        => NativeDll.Initialize();

    private ulong      _width;
    private ulong      _height;
    public  DXGIFormat Format;
    private ulong      _rowPitch;
    private ulong      _slicePitch;
    private byte*      _pixels;

    public int Width
        => (int)_width;

    public int Height
        => (int)_height;

    public int RowPitch
        => (int)_rowPitch;

    public int SlicePitch
        => (int)_slicePitch;

    public IntPtr Pixels
        => (IntPtr)_pixels;

    public ReadOnlySpan<byte> Span
        => new(_pixels, (int)_slicePitch);

    public ErrorCode Save(string path, DDSParseFlags flags = DDSParseFlags.None)
        => image_save_to_dds_file(this, flags, path);

    [DllImport(NativeDll.Name, CharSet = CharSet.Unicode)]
    private static extern ErrorCode image_save_to_dds_file(in Image image, DDSParseFlags flags, string path);
}
