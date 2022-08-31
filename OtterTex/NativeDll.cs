using System;
using System.IO;
using System.Reflection;
using System.Runtime.InteropServices;

namespace OtterTex;

public static class NativeDll
{
    public const   string                                         Name = "DirectXTexC.dll";
    public static  string                                         Directory { get; private set; } = string.Empty;
    private static bool                                           _initialized;
    public static event Action<string, string, Assembly, IntPtr>? AssemblyLoaded;

    public static void Initialize(string? path = null)
    {
        Directory = path ?? Path.GetDirectoryName(typeof(NativeDll).Assembly.Location) ?? string.Empty;
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
            var path = Path.Combine(Directory, name);
            NativeLibrary.TryLoad(path, out ret);
            AssemblyLoaded?.Invoke(name, path, assembly, ret);
        }

        return ret;
    }
}
