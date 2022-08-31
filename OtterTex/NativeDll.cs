using System;
using System.IO;
using System.Reflection;
using System.Runtime.InteropServices;

namespace OtterTex;

public static class NativeDll
{
    public const   string Name         = "DirectXTexC.dll";
    private static bool   _initialized;

    public static void Initialize()
    {
        if (!_initialized)
        {
            NativeLibrary.SetDllImportResolver(typeof(NativeDll).Assembly, DllImportResolver);
            _initialized = true;
        }
    }

    private static IntPtr DllImportResolver(string name, Assembly assembly, DllImportSearchPath? searchPath)
    {
        var ret = IntPtr.Zero;
        if (name == Name)
        {
            var basePath = assembly.Location;
            var parent   = Path.GetDirectoryName(basePath) ?? string.Empty;
            var path     = Path.Combine(parent, Name);
            NativeLibrary.TryLoad(path, out ret);
        }

        return ret;
    }
}
