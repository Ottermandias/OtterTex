#pragma once
#include <cstdint>
#include <cstdbool>

#define API extern "C" __declspec(dllexport)

#define DXGI_FORMAT uint64_t
#define FORMAT_TYPE uint64_t
#define CP_FLAGS uint64_t
#define SIZE uint64_t
#define ERROR_CODE uint64_t

API bool dxgiformat_is_valid(DXGI_FORMAT fmt);
API bool dxgiformat_is_compressed(DXGI_FORMAT fmt);
API bool dxgiformat_is_packed(DXGI_FORMAT fmt);
API bool dxgiformat_is_video(DXGI_FORMAT fmt);
API bool dxgiformat_is_planar(DXGI_FORMAT fmt);
API bool dxgiformat_is_palettized(DXGI_FORMAT fmt);
API bool dxgiformat_is_depth_stencil(DXGI_FORMAT fmt);
API bool dxgiformat_is_srgb(DXGI_FORMAT fmt);
API bool dxgiformat_is_bgr(DXGI_FORMAT fmt);
API bool dxgiformat_is_typeless_partial(DXGI_FORMAT fmt);
API bool dxgiformat_is_typeless_full(DXGI_FORMAT fmt);
API bool dxgiformat_has_alpha(DXGI_FORMAT fmt);
API SIZE dxgiformat_bits_per_pixel(DXGI_FORMAT fmt);
API SIZE dxgiformat_bits_per_color(DXGI_FORMAT fmt);

API FORMAT_TYPE dxgiformat_data_type(DXGI_FORMAT fmt);

API ERROR_CODE dxgiformat_compute_pitch(DXGI_FORMAT fmt, SIZE width, SIZE height, SIZE* rowPitch, SIZE* slicePitch);
API ERROR_CODE dxgiformat_compute_pitch_flags(DXGI_FORMAT fmt, SIZE width, SIZE height, SIZE* rowPitch, SIZE* slicePitch, CP_FLAGS flags);
API SIZE dxgiformat_compute_scanlines(DXGI_FORMAT fmt, SIZE height);

API DXGI_FORMAT dxgiformat_make_srgb(DXGI_FORMAT fmt);
API DXGI_FORMAT dxgiformat_make_linear(DXGI_FORMAT fmt);
API DXGI_FORMAT dxgiformat_make_typeless(DXGI_FORMAT fmt);
API DXGI_FORMAT dxgiformat_make_typeless_unorm(DXGI_FORMAT fmt);
API DXGI_FORMAT dxgiformat_make_typeless_float(DXGI_FORMAT fmt);