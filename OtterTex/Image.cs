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
    {
        get => (int)_width;
        set => _width = (ulong)value;
    }

    public int Height
    {
        get => (int)_height;
        set => _height = (ulong)value;
    }

    public int RowPitch
    {
        get => (int)_rowPitch;
        set => _rowPitch = (ulong)value;
    }

    public int SlicePitch
    {
        get => (int)_slicePitch;
        set => _slicePitch = (ulong)value;
    }

    public ErrorCode Save(string path, DDSParseFlags flags = DDSParseFlags.None)
        => image_save_to_dds_file(this, flags, path);

    [DllImport(NativeDll.Name, CharSet = CharSet.Unicode)]
    private static extern ErrorCode image_save_to_dds_file(in Image image, DDSParseFlags flags, string path);
}
