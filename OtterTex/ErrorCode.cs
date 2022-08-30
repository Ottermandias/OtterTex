using System;
using System.Runtime.InteropServices;

namespace OtterTex;

public readonly struct ErrorCode : IEquatable<ErrorCode>
{
    public static readonly ErrorCode Ok = new();

    public int Value { get; } = 0;

    public ErrorCode()
    { }

    public ErrorCode(int value)
        => Value = value;

    public static implicit operator bool(ErrorCode code)
        => code.Value >= 0;

    public static implicit operator ErrorCode(int code)
        => new(code);

    public static bool operator true(ErrorCode code)
        => code.Value >= 0;

    public static bool operator false(ErrorCode code)
        => code.Value < 0;

    public void ThrowIfError()
        => Marshal.ThrowExceptionForHR(Value);

    public T ThrowIfError<T>(T value)
    {
        Marshal.ThrowExceptionForHR(Value);
        return value;
    }

    public Exception? GetException()
        => Marshal.GetExceptionForHR(Value);

    public bool Equals(ErrorCode other)
        => Value == other.Value;

    public override bool Equals(object? obj)
        => obj is ErrorCode other && Equals(other);

    public override int GetHashCode()
        => Value;

    public static bool operator ==(ErrorCode x, ErrorCode y)
        => x.Value == y.Value;

    public static bool operator !=(ErrorCode x, ErrorCode y)
        => x.Value != y.Value;

    public static bool operator !(ErrorCode x)
        => x.Value < 0;

    public override string ToString()
        => GetException()?.Message ?? "No Error.";

    public string StackTrace
        => GetException()?.ToString() ?? string.Empty;
}
