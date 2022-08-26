using System;
using System.IO;
using System.Reflection;

namespace OtterTex;

internal static class Utility
{
    private static Assembly? _assembly = null;

    public static T LoadStatic<T>(string typeName)
    {
        _assembly ??= GetAssembly();

        var type = _assembly.GetType(typeName);
        if (type == null)
            throw new ApplicationException("Missing type {typeName}.");

        return (T)Activator.CreateInstance(type)!;
    }

    private static Assembly GetAssembly()
    {
        var directory = Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location) ?? string.Empty;
        var path      = Path.Combine(directory, "OtterTexCLI.dll");
        if (!File.Exists(path))
            throw new ApplicationException("Missing OtterTexCLI.dll");

        return Assembly.LoadFile(path);
    }
}