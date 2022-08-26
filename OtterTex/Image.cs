using System;

namespace OtterTex;

public unsafe class Image
{
    public int        Width;
    public int        Height;
    public DXGIFormat Format;
    public int        RowPitch;
    public int        SlicePitch;
    public byte*      Pixels;

    public Image(int width, int height, DXGIFormat fmt, int rowPitch, int slicePitch, IntPtr pixels)
    {
        Width      = width;
        Height     = height;
        Format     = fmt;
        RowPitch   = rowPitch;
        SlicePitch = slicePitch;
        Pixels     = (byte*)pixels;
    }
}

