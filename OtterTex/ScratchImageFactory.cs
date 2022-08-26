using System;

namespace OtterTex;

public abstract class ScratchImageFactory
{
    internal static readonly ScratchImageFactory Instance;

    static ScratchImageFactory()
        => Instance = Utility.LoadStatic<ScratchImageFactory>("OtterTex.ScratchImageFactoryImpl");

    public abstract ScratchImage Create();
    public abstract ScratchImage LoadFromDDSMemory(IntPtr source, int size, DDSParseFlags flags);
    public abstract ScratchImage LoadFromDDSFile(string path, DDSParseFlags flags);
    public abstract ScratchImage LoadFromHDRMemory(IntPtr source, int size);
    public abstract ScratchImage LoadFromHDRFile(string path);
    public abstract ScratchImage LoadFromTGAMemory(IntPtr source, int size, TGAParseFlags flags);
    public abstract ScratchImage LoadFromTGAFile(string path, TGAParseFlags flags);
    public abstract ScratchImage LoadFromWICMemory(IntPtr source, int size, WICParseFlags flags);
    public abstract ScratchImage LoadFromWICFile(string path, WICParseFlags flags);
}
