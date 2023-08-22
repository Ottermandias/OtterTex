#include "../DirectXTex/DirectXTex/DirectXTex.h"

#define API extern "C" __declspec(dllexport)
#define ENUM uint64_t
#define SIZE uint64_t
#define BOOL uint8_t
#define ERROR_CODE int32_t
#define TEXMETADATA DirectX::TexMetadata

static __forceinline ERROR_CODE ec(HRESULT code)
{
    return static_cast<ERROR_CODE>(code);
}

API bool dxgiformat_is_valid(ENUM fmt) noexcept
{
    return DirectX::IsValid(static_cast<DXGI_FORMAT>(fmt));
}

API bool dxgiformat_is_compressed(ENUM fmt) noexcept
{
    return DirectX::IsCompressed(static_cast<DXGI_FORMAT>(fmt));
}

API bool dxgiformat_is_packed(ENUM fmt) noexcept
{
    return DirectX::IsPacked(static_cast<DXGI_FORMAT>(fmt));
}

API bool dxgiformat_is_video(ENUM fmt) noexcept
{
    return DirectX::IsVideo(static_cast<DXGI_FORMAT>(fmt));
}

API bool dxgiformat_is_planar(ENUM fmt) noexcept
{
    return DirectX::IsPlanar(static_cast<DXGI_FORMAT>(fmt));
}

API bool dxgiformat_is_palettized(ENUM fmt) noexcept
{
    return DirectX::IsPalettized(static_cast<DXGI_FORMAT>(fmt));
}

API bool dxgiformat_is_depth_stencil(ENUM fmt) noexcept
{
    return DirectX::IsDepthStencil(static_cast<DXGI_FORMAT>(fmt));
}

API bool dxgiformat_is_srgb(ENUM fmt) noexcept
{
    return DirectX::IsSRGB(static_cast<DXGI_FORMAT>(fmt));
}

API bool dxgiformat_is_bgr(ENUM fmt) noexcept
{
    return DirectX::IsBGR(static_cast<DXGI_FORMAT>(fmt));
}

API bool dxgiformat_is_typeless_partial(ENUM fmt) noexcept
{
    return DirectX::IsTypeless(static_cast<DXGI_FORMAT>(fmt), true);
}

API bool dxgiformat_is_typeless_full(ENUM fmt) noexcept
{
    return DirectX::IsTypeless(static_cast<DXGI_FORMAT>(fmt), false);
}

API bool dxgiformat_has_alpha(ENUM fmt) noexcept
{
    return DirectX::HasAlpha(static_cast<DXGI_FORMAT>(fmt));
}

API SIZE dxgiformat_bits_per_pixel(ENUM fmt) noexcept
{
    return static_cast<SIZE>(DirectX::BitsPerPixel(static_cast<DXGI_FORMAT>(fmt)));
}

API SIZE dxgiformat_bits_per_color(ENUM fmt) noexcept
{
    return static_cast<SIZE>(DirectX::BitsPerColor(static_cast<DXGI_FORMAT>(fmt)));
}

API ENUM dxgiformat_data_type(ENUM fmt) noexcept
{
    return static_cast<ENUM>(DirectX::FormatDataType(static_cast<DXGI_FORMAT>(fmt)));
}

API ERROR_CODE dxgiformat_compute_pitch(ENUM fmt, SIZE width, SIZE height, SIZE* row_pitch,
                                        SIZE* slice_pitch, ENUM flags) noexcept
{
    size_t tmp_row_pitch = 0, tmp_slice_pitch = 0;
    const auto ret = ec(DirectX::ComputePitch(static_cast<DXGI_FORMAT>(fmt),
                                              static_cast<size_t>(width),
                                              static_cast<size_t>(height), tmp_row_pitch,
                                              tmp_slice_pitch,
                                              static_cast<DirectX::CP_FLAGS>(flags)));
    *row_pitch = static_cast<SIZE>(tmp_row_pitch);
    *slice_pitch = static_cast<SIZE>(tmp_slice_pitch);
    return ret;
}

API SIZE dxgiformat_compute_scanlines(ENUM fmt, SIZE height) noexcept
{
    return static_cast<SIZE>(DirectX::ComputeScanlines(static_cast<DXGI_FORMAT>(fmt), static_cast<size_t>(height)));
}

API ENUM dxgiformat_make_srgb(ENUM fmt) noexcept
{
    return static_cast<ENUM>(DirectX::MakeSRGB(static_cast<DXGI_FORMAT>(fmt)));
}

API ENUM dxgiformat_make_linear(ENUM fmt) noexcept
{
    return static_cast<ENUM>(DirectX::MakeLinear(static_cast<DXGI_FORMAT>(fmt)));
}

API ENUM dxgiformat_make_typeless(ENUM fmt) noexcept
{
    return static_cast<ENUM>(DirectX::MakeTypeless(static_cast<DXGI_FORMAT>(fmt)));
}

API ENUM dxgiformat_make_typeless_unorm(ENUM fmt) noexcept
{
    return static_cast<ENUM>(DirectX::MakeTypelessUNORM(static_cast<DXGI_FORMAT>(fmt)));
}

API ENUM dxgiformat_make_typeless_float(ENUM fmt) noexcept
{
    return static_cast<ENUM>(DirectX::MakeTypelessFLOAT(static_cast<DXGI_FORMAT>(fmt)));
}

API SIZE texmetadata_compute_index(void* tex, SIZE mip, SIZE item, SIZE slice) noexcept
{
    return static_cast<SIZE>(static_cast<const DirectX::TexMetadata*>(tex)->ComputeIndex(
        static_cast<SIZE>(mip), static_cast<SIZE>(item),
        static_cast<SIZE>(slice)));
}

API bool texmetadata_is_cubemap(void* tex) noexcept
{
    return static_cast<const DirectX::TexMetadata*>(tex)->IsCubemap();
}

API bool texmetadata_is_volumemap(void* tex) noexcept
{
    return static_cast<const DirectX::TexMetadata*>(tex)->IsVolumemap();
}

API bool texmetadata_is_premultiplied_alpha(void* tex) noexcept
{
    return static_cast<const DirectX::TexMetadata*>(tex)->IsPMAlpha();
}

API void texmetadata_set_alpha_mode(void* tex, ENUM mode) noexcept
{
    static_cast<DirectX::TexMetadata*>(tex)->SetAlphaMode(static_cast<DirectX::TEX_ALPHA_MODE>(mode));
}

API DirectX::TEX_ALPHA_MODE texmetadata_get_alpha_mode(void* tex) noexcept
{
    return static_cast<const DirectX::TexMetadata*>(tex)->GetAlphaMode();
}

API ERROR_CODE texmetadata_get_from_dds_memory(const void* source, SIZE size, ENUM flags, void* metadata) noexcept
{
    return ec(DirectX::GetMetadataFromDDSMemory(source, static_cast<size_t>(size),
                                                static_cast<DirectX::DDS_FLAGS>(flags),
                                                *static_cast<DirectX::TexMetadata*>(metadata)));
}

API ERROR_CODE texmetadata_get_from_dds_file(const wchar_t* path, ENUM flags, void* metadata) noexcept
{
    return ec(DirectX::GetMetadataFromDDSFile(path, static_cast<DirectX::DDS_FLAGS>(flags),
                                              *static_cast<DirectX::TexMetadata*>(metadata)));
}

API ERROR_CODE texmetadata_get_from_hdr_memory(const void* source, SIZE size, void* metadata) noexcept
{
    return ec(DirectX::GetMetadataFromHDRMemory(source, static_cast<size_t>(size),
                                                *static_cast<DirectX::TexMetadata*>(metadata)));
}

API ERROR_CODE texmetadata_get_from_hdr_file(const wchar_t* path, void* metadata) noexcept
{
    return ec(
        DirectX::GetMetadataFromHDRFile(path, *static_cast<DirectX::TexMetadata*>(metadata)));
}

API ERROR_CODE texmetadata_get_from_tga_memory(const void* source, SIZE size, ENUM flags, void* metadata) noexcept
{
    return ec(DirectX::GetMetadataFromTGAMemory(source, static_cast<size_t>(size),
                                                static_cast<DirectX::TGA_FLAGS>(flags),
                                                *static_cast<DirectX::TexMetadata*>(metadata)));
}

API ERROR_CODE texmetadata_get_from_tga_file(const wchar_t* path, ENUM flags, void* metadata) noexcept
{
    return ec(DirectX::GetMetadataFromTGAFile(path, static_cast<DirectX::TGA_FLAGS>(flags),
                                              *static_cast<DirectX::TexMetadata*>(metadata)));
}

API ERROR_CODE texmetadata_get_from_wic_memory(const void* source, SIZE size, ENUM flags, void* metadata) noexcept
{
    return ec(DirectX::GetMetadataFromWICMemory(source, static_cast<size_t>(size),
                                                static_cast<DirectX::WIC_FLAGS>(flags),
                                                *static_cast<DirectX::TexMetadata*>(metadata)));
}

API ERROR_CODE texmetadata_get_from_wic_file(const wchar_t* path, ENUM flags, void* metadata) noexcept
{
    return ec(DirectX::GetMetadataFromWICFile(path, static_cast<DirectX::WIC_FLAGS>(flags),
                                              *static_cast<DirectX::TexMetadata*>(metadata)));
}

API void scratchimage_ctor(void* scratch_image) noexcept
{
    new (static_cast<DirectX::ScratchImage*>(scratch_image)) DirectX::ScratchImage();
}

API void scratchimage_move_ctor(void* scratch_image, void* moved_from) noexcept
{
    new (static_cast<DirectX::ScratchImage*>(scratch_image)) DirectX::ScratchImage(
        std::move(*static_cast<DirectX::ScratchImage*>(moved_from)));
}

API ERROR_CODE scratchimage_initialize(void* scratch_image, const void* metadata, ENUM flags) noexcept
{
    return ec(static_cast<DirectX::ScratchImage*>(scratch_image)->Initialize(
        *static_cast<const DirectX::TexMetadata*>(metadata), static_cast<DirectX::CP_FLAGS>(flags)));
}

API ERROR_CODE scratchimage_initialize1D(void* scratch_image, ENUM fmt, SIZE length, SIZE arraySize, SIZE mipLevels,
                                         ENUM flags) noexcept
{
    return ec(static_cast<DirectX::ScratchImage*>(scratch_image)->Initialize1D(
        static_cast<DXGI_FORMAT>(fmt), static_cast<size_t>(length), static_cast<size_t>(arraySize),
        static_cast<size_t>(mipLevels), static_cast<DirectX::CP_FLAGS>(flags)));
}

API ERROR_CODE scratchimage_initialize2D(void* scratch_image, ENUM fmt, SIZE width, SIZE height, SIZE arraySize,
                                         SIZE mipLevels, ENUM flags) noexcept
{
    return ec(static_cast<DirectX::ScratchImage*>(scratch_image)->Initialize2D(
        static_cast<DXGI_FORMAT>(fmt), static_cast<size_t>(width), static_cast<size_t>(height),
        static_cast<size_t>(arraySize), static_cast<size_t>(mipLevels), static_cast<DirectX::CP_FLAGS>(flags)));
}

API ERROR_CODE scratchimage_initialize3D(void* scratch_image, ENUM fmt, SIZE width, SIZE height, SIZE depth,
                                         SIZE mipLevels, ENUM flags) noexcept
{
    return ec(static_cast<DirectX::ScratchImage*>(scratch_image)->Initialize3D(
        static_cast<DXGI_FORMAT>(fmt), static_cast<size_t>(width), static_cast<size_t>(height),
        static_cast<size_t>(depth), static_cast<size_t>(mipLevels), static_cast<DirectX::CP_FLAGS>(flags)));
}

API ERROR_CODE scratchimage_initialize_cube(void* scratch_image, ENUM fmt, SIZE width, SIZE height, SIZE nCubes,
                                           SIZE mipLevels, ENUM flags) noexcept
{
    return ec(static_cast<DirectX::ScratchImage*>(scratch_image)->InitializeCube(
        static_cast<DXGI_FORMAT>(fmt), static_cast<size_t>(width), static_cast<size_t>(height),
        static_cast<size_t>(nCubes), static_cast<size_t>(mipLevels), static_cast<DirectX::CP_FLAGS>(flags)));
}

API ERROR_CODE scratchimage_initialize_from_image(void* scratch_image, const void* image, bool allow1D,
                                                  ENUM flags) noexcept
{
    return ec(static_cast<DirectX::ScratchImage*>(scratch_image)->InitializeFromImage(
        *static_cast<const DirectX::Image*>(image), allow1D, static_cast<DirectX::CP_FLAGS>(flags)));
}

API ERROR_CODE scratchimage_initialize_array_from_images(void* scratch_image, const void* images, SIZE nImages,
                                                         bool allow1D, ENUM flags) noexcept
{
    return ec(static_cast<DirectX::ScratchImage*>(scratch_image)->InitializeArrayFromImages(
        static_cast<const DirectX::Image*>(images), static_cast<size_t>(nImages), allow1D,
        static_cast<DirectX::CP_FLAGS>(flags)));
}

API ERROR_CODE scratchimage_initialize_cube_from_images(void* scratch_image, const void* images, SIZE nImages,
                                                        ENUM flags) noexcept
{
    return ec(static_cast<DirectX::ScratchImage*>(scratch_image)->InitializeCubeFromImages(
        static_cast<const DirectX::Image*>(images), static_cast<size_t>(nImages),
        static_cast<DirectX::CP_FLAGS>(flags)));
}

API ERROR_CODE scratchimage_initialize_3D_from_images(void* scratch_image, const void* images, SIZE depth,
                                                      ENUM flags) noexcept
{
    return ec(static_cast<DirectX::ScratchImage*>(scratch_image)->Initialize3DFromImages(
        static_cast<const DirectX::Image*>(images), static_cast<size_t>(depth),
        static_cast<DirectX::CP_FLAGS>(flags)));
}

API void scratchimage_release(void* scratch_image)
{
    static_cast<DirectX::ScratchImage*>(scratch_image)->Release();
}

API bool scratchimage_override_format(void* scratch_image, ENUM fmt) noexcept
{
    return static_cast<DirectX::ScratchImage*>(scratch_image)->OverrideFormat(static_cast<DXGI_FORMAT>(fmt));
}

API bool scratchimage_is_alpha_all_opaque(const void* scratch_image) noexcept
{
    return static_cast<const DirectX::ScratchImage*>(scratch_image)->IsAlphaAllOpaque();
}

API const void* scratchimage_get_image(const void* scratch_image, SIZE mip, SIZE item, SIZE slice)
{
    return static_cast<const DirectX::ScratchImage*>(scratch_image)->GetImage(static_cast<size_t>(mip), static_cast<size_t>(item), static_cast<size_t>(slice));
}

API ERROR_CODE scratchimage_load_from_dds_memory(const void* source, SIZE size, ENUM flags, void* meta,
                                                 void* scratch_image) noexcept
{
    return ec(DirectX::LoadFromDDSMemory(source, static_cast<SIZE>(size),
                                         static_cast<DirectX::DDS_FLAGS>(flags),
                                         static_cast<DirectX::TexMetadata*>(meta),
                                         *static_cast<DirectX::ScratchImage*>(scratch_image)));
}

API ERROR_CODE scratchimage_load_from_dds_file(const wchar_t* path, ENUM flags, void* meta,
                                               void* scratch_image) noexcept
{
    return ec(DirectX::LoadFromDDSFile(path, static_cast<DirectX::DDS_FLAGS>(flags),
                                       static_cast<DirectX::TexMetadata*>(meta),
                                       *static_cast<DirectX::ScratchImage*>(scratch_image)));
}

API ERROR_CODE image_save_to_dds_memory(const void* image, ENUM flags, void* blob) noexcept
{
    return ec(DirectX::SaveToDDSMemory(*static_cast<const DirectX::Image*>(image),
                                       static_cast<DirectX::DDS_FLAGS>(flags),
                                       *static_cast<DirectX::Blob*>(blob)));
}

API ERROR_CODE scratchimage_save_to_dds_memory(const void* images, SIZE num_images, const void* meta, ENUM flags,
                                               void* blob) noexcept
{
    return ec(DirectX::SaveToDDSMemory(static_cast<const DirectX::Image*>(images),
                                       static_cast<size_t>(num_images),
                                       *static_cast<const DirectX::TexMetadata*>(meta),
                                       static_cast<DirectX::DDS_FLAGS>(flags),
                                       *static_cast<DirectX::Blob*>(blob)));
}

API ERROR_CODE image_save_to_dds_file(const void* image, ENUM flags, const wchar_t* path) noexcept
{
    return ec(DirectX::SaveToDDSFile(*static_cast<const DirectX::Image*>(image),
                                     static_cast<DirectX::DDS_FLAGS>(flags), path));
}

API ERROR_CODE scratchimage_save_to_dds_file(const void* images, SIZE num_images, const void* meta, ENUM flags,
                                             const wchar_t* path) noexcept
{
    return ec(DirectX::SaveToDDSFile(static_cast<const DirectX::Image*>(images),
                                     static_cast<size_t>(num_images),
                                     *static_cast<const DirectX::TexMetadata*>(meta),
                                     static_cast<DirectX::DDS_FLAGS>(flags), path));
}

API ERROR_CODE scratchimage_load_from_hdr_memory(const void* source, SIZE size, void* meta,
                                                 void* scratch_image) noexcept
{
    return ec(DirectX::LoadFromHDRMemory(source, static_cast<SIZE>(size),
                                         static_cast<DirectX::TexMetadata*>(meta),
                                         *static_cast<DirectX::ScratchImage*>(scratch_image)));
}

API ERROR_CODE scratchimage_load_from_hdr_file(const wchar_t* path, void* meta, void* scratch_image) noexcept
{
    return ec(DirectX::LoadFromHDRFile(path, static_cast<DirectX::TexMetadata*>(meta),
                                       *static_cast<DirectX::ScratchImage*>(scratch_image)));
}

API ERROR_CODE image_save_to_hdr_memory(const void* image, void* blob) noexcept
{
    return ec(DirectX::SaveToHDRMemory(*static_cast<const DirectX::Image*>(image),
                                       *static_cast<DirectX::Blob*>(blob)));
}

API ERROR_CODE image_save_to_hdr_file(const void* image, const wchar_t* path) noexcept
{
    return ec(DirectX::SaveToHDRFile(*static_cast<const DirectX::Image*>(image), path));
}

API ERROR_CODE scratchimage_load_from_tga_memory(const void* source, SIZE size, ENUM flags, void* meta,
                                                 void* scratch_image) noexcept
{
    return ec(DirectX::LoadFromTGAMemory(source, static_cast<SIZE>(size),
                                         static_cast<DirectX::TGA_FLAGS>(flags),
                                         static_cast<DirectX::TexMetadata*>(meta),
                                         *static_cast<DirectX::ScratchImage*>(scratch_image)));
}

API ERROR_CODE scratchimage_load_from_tga_file(const wchar_t* path, ENUM flags, void* meta,
                                               void* scratch_image) noexcept
{
    return ec(DirectX::LoadFromTGAFile(path, static_cast<DirectX::TGA_FLAGS>(flags),
                                       static_cast<DirectX::TexMetadata*>(meta),
                                       *static_cast<DirectX::ScratchImage*>(scratch_image)));
}

API ERROR_CODE image_save_to_tga_memory(const void* image, ENUM flags, void* blob) noexcept
{
    return ec(DirectX::SaveToTGAMemory(*static_cast<const DirectX::Image*>(image),
                                       static_cast<DirectX::TGA_FLAGS>(flags),
                                       *static_cast<DirectX::Blob*>(blob)));
}

API ERROR_CODE image_save_to_tga_file(const void* image, ENUM flags, const wchar_t* path) noexcept
{
    return ec(DirectX::SaveToTGAFile(*static_cast<const DirectX::Image*>(image),
                                     static_cast<DirectX::TGA_FLAGS>(flags), path));
}

API ERROR_CODE scratchimage_load_from_wic_memory(const void* source, SIZE size, ENUM flags, void* meta,
                                                 void* scratch_image) noexcept
{
    return ec(DirectX::LoadFromWICMemory(source, static_cast<SIZE>(size),
                                         static_cast<DirectX::WIC_FLAGS>(flags),
                                         static_cast<DirectX::TexMetadata*>(meta),
                                         *static_cast<DirectX::ScratchImage*>(scratch_image)));
}

API ERROR_CODE image_flip_rotate(const void* image, ENUM flags, void* scratch_image) noexcept
{
    return ec(DirectX::FlipRotate(*static_cast<const DirectX::Image*>(image),
                                  static_cast<DirectX::TEX_FR_FLAGS>(flags),
                                  *static_cast<DirectX::ScratchImage*>(scratch_image)));
}

API ERROR_CODE scratchimage_flip_rotate(const void* images, SIZE num_images, const void* meta, ENUM flags,
                                        void* scratch_image) noexcept
{
    return ec(DirectX::FlipRotate(static_cast<const DirectX::Image*>(images),
                                  static_cast<size_t>(num_images),
                                  *static_cast<const DirectX::TexMetadata*>(meta),
                                  static_cast<DirectX::TEX_FR_FLAGS>(flags),
                                  *static_cast<DirectX::ScratchImage*>(scratch_image)));
}

API ERROR_CODE image_resize(const void* image, SIZE width, SIZE height, ENUM flags, void* scratch_image) noexcept
{
    return ec(DirectX::Resize(*static_cast<const DirectX::Image*>(image),
                              static_cast<size_t>(width), static_cast<size_t>(height),
                              static_cast<DirectX::TEX_FILTER_FLAGS>(flags),
                              *static_cast<DirectX::ScratchImage*>(scratch_image)));
}

API ERROR_CODE scratchimage_resize(const void* images, SIZE num_images, const void* meta, SIZE width, SIZE height,
                                   ENUM flags,
                                   void* scratch_image) noexcept
{
    return ec(DirectX::Resize(static_cast<const DirectX::Image*>(images),
                              static_cast<size_t>(num_images),
                              *static_cast<const DirectX::TexMetadata*>(meta),
                              static_cast<size_t>(width), static_cast<size_t>(height),
                              static_cast<DirectX::TEX_FILTER_FLAGS>(flags),
                              *static_cast<DirectX::ScratchImage*>(scratch_image)));
}

API ERROR_CODE image_convert(const void* image, ENUM fmt, ENUM flags, float threshold, void* scratch_image) noexcept
{
    return ec(DirectX::Convert(*static_cast<const DirectX::Image*>(image),
                               static_cast<DXGI_FORMAT>(fmt),
                               static_cast<DirectX::TEX_FILTER_FLAGS>(flags), threshold,
                               *static_cast<DirectX::ScratchImage*>(scratch_image)));
}

API ERROR_CODE scratchimage_convert(const void* images, SIZE num_images, const void* meta, ENUM fmt, ENUM flags,
                                    float threshold, void* scratch_image) noexcept
{
    return ec(DirectX::Convert(static_cast<const DirectX::Image*>(images),
                               static_cast<size_t>(num_images),
                               *static_cast<const DirectX::TexMetadata*>(meta),
                               static_cast<DXGI_FORMAT>(fmt),
                               static_cast<DirectX::TEX_FILTER_FLAGS>(flags), threshold,
                               *static_cast<DirectX::ScratchImage*>(scratch_image)));
}

API ERROR_CODE image_convert_to_single_plane(const void* image, void* scratch_image) noexcept
{
    return ec(DirectX::ConvertToSinglePlane(*static_cast<const DirectX::Image*>(image),
                                            *static_cast<DirectX::ScratchImage*>(scratch_image)));
}

API ERROR_CODE scratchimage_convert_to_single_plane(const void* images, SIZE num_images, const void* meta,
                                                    void* scratch_image) noexcept
{
    return ec(DirectX::ConvertToSinglePlane(static_cast<const DirectX::Image*>(images),
                                            static_cast<size_t>(num_images),
                                            *static_cast<const DirectX::TexMetadata*>(meta),
                                            *static_cast<DirectX::ScratchImage*>(scratch_image)));
}

API ERROR_CODE image_generate_mipmaps(const void* image, ENUM flags, SIZE levels, void* scratch_image,
                                      bool allow1D) noexcept
{
    return ec(DirectX::GenerateMipMaps(*static_cast<const DirectX::Image*>(image),
                                       static_cast<DirectX::TEX_FILTER_FLAGS>(flags),
                                       static_cast<size_t>(levels),
                                       *static_cast<DirectX::ScratchImage*>(scratch_image),
                                       allow1D));
}

API ERROR_CODE scratchimage_generate_mipmaps(const void* images, SIZE num_images, const void* meta, ENUM flags,
                                             SIZE levels, void* scratch_image) noexcept
{
    return ec(DirectX::GenerateMipMaps(static_cast<const DirectX::Image*>(images),
                                       static_cast<size_t>(num_images),
                                       *static_cast<const DirectX::TexMetadata*>(meta),
                                       static_cast<DirectX::TEX_FILTER_FLAGS>(flags),
                                       static_cast<size_t>(levels),
                                       *static_cast<DirectX::ScratchImage*>(scratch_image)));
}

API ERROR_CODE image_generate_mipmaps_3d(const void* images, SIZE depth, ENUM flags, SIZE levels,
                                         void* scratch_image) noexcept
{
    return ec(DirectX::GenerateMipMaps3D(static_cast<const DirectX::Image*>(images),
                                         static_cast<size_t>(depth),
                                         static_cast<DirectX::TEX_FILTER_FLAGS>(flags),
                                         static_cast<size_t>(levels),
                                         *static_cast<DirectX::ScratchImage*>(scratch_image)));
}

API ERROR_CODE scratchimage_generate_mipmaps_3d(const void* images, SIZE num_images, const void* meta, ENUM flags,
                                                SIZE levels, void* scratch_image) noexcept
{
    return ec(DirectX::GenerateMipMaps3D(static_cast<const DirectX::Image*>(images),
                                         static_cast<size_t>(num_images),
                                         *static_cast<const DirectX::TexMetadata*>(meta),
                                         static_cast<DirectX::TEX_FILTER_FLAGS>(flags),
                                         static_cast<size_t>(levels),
                                         *static_cast<DirectX::ScratchImage*>(scratch_image)));
}

API ERROR_CODE scratchimage_scale_mipmaps_alpha_for_coverage(const void* images, SIZE num_images, const void* meta,
                                                             SIZE item, float alpha_reference,
                                                             void* scratch_image) noexcept
{
    return ec(DirectX::ScaleMipMapsAlphaForCoverage(static_cast<const DirectX::Image*>(images),
                                                    static_cast<size_t>(num_images),
                                                    *static_cast<const DirectX::TexMetadata*>(meta),
                                                    static_cast<size_t>(item),
                                                    alpha_reference,
                                                    *static_cast<DirectX::ScratchImage*>(scratch_image)));
}

API ERROR_CODE image_premultiply_alpha(const void* image, ENUM flags, void* scratch_image) noexcept
{
    return ec(DirectX::PremultiplyAlpha(*static_cast<const DirectX::Image*>(image),
                                        static_cast<DirectX::TEX_PMALPHA_FLAGS>(flags),
                                        *static_cast<DirectX::ScratchImage*>(scratch_image)));
}

API ERROR_CODE scratchimage_premultiply_alpha(const void* images, SIZE num_images, const void* meta, ENUM flags,
                                              void* scratch_image) noexcept
{
    return ec(DirectX::PremultiplyAlpha(static_cast<const DirectX::Image*>(images),
                                        static_cast<size_t>(num_images),
                                        *static_cast<const DirectX::TexMetadata*>(meta),
                                        static_cast<DirectX::TEX_PMALPHA_FLAGS>(flags),
                                        *static_cast<DirectX::ScratchImage*>(scratch_image)));
}

API ERROR_CODE image_compress(const void* image, ENUM fmt, ENUM flags, float threshold, void* scratch_image) noexcept
{
    return ec(DirectX::Compress(*static_cast<const DirectX::Image*>(image),
                                static_cast<DXGI_FORMAT>(fmt),
                                static_cast<DirectX::TEX_COMPRESS_FLAGS>(flags),
                                threshold,
                                *static_cast<DirectX::ScratchImage*>(scratch_image)));
}

API ERROR_CODE scratchimage_compress(const void* images, SIZE num_images, const void* meta, ENUM fmt, ENUM flags,
                                     float threshold, void* scratch_image) noexcept
{
    return ec(DirectX::Compress(static_cast<const DirectX::Image*>(images),
                                static_cast<size_t>(num_images),
                                *static_cast<const DirectX::TexMetadata*>(meta),
                                static_cast<DXGI_FORMAT>(fmt),
                                static_cast<DirectX::TEX_COMPRESS_FLAGS>(flags),
                                threshold,
                                *static_cast<DirectX::ScratchImage*>(scratch_image)));
}

#if defined(__d3d11_h__) || defined(__d3d11_x_h__)
API ERROR_CODE image_compress_d3d11(void* device, const void* image, ENUM fmt, ENUM flags, float alphaWeight,
                                    void* scratch_image) noexcept
{
    return ec(DirectX::Compress(static_cast<ID3D11Device*>(device),
                                *static_cast<const DirectX::Image*>(image),
                                static_cast<DXGI_FORMAT>(fmt),
                                static_cast<DirectX::TEX_COMPRESS_FLAGS>(flags),
                                alphaWeight,
                                *static_cast<DirectX::ScratchImage*>(scratch_image)));
}

API ERROR_CODE scratchimage_compress_d3d11(void* device, const void* images, SIZE num_images, const void* meta,
                                           ENUM fmt, ENUM flags, float alphaWeight, void* scratch_image) noexcept
{
    return ec(DirectX::Compress(static_cast<ID3D11Device*>(device),
                                static_cast<const DirectX::Image*>(images),
                                static_cast<size_t>(num_images),
                                *static_cast<const DirectX::TexMetadata*>(meta),
                                static_cast<DXGI_FORMAT>(fmt),
                                static_cast<DirectX::TEX_COMPRESS_FLAGS>(flags),
                                alphaWeight,
                                *static_cast<DirectX::ScratchImage*>(scratch_image)));
}
#endif

API ERROR_CODE image_decompress(const void* image, ENUM fmt, void* scratch_image) noexcept
{
    return ec(DirectX::Decompress(*static_cast<const DirectX::Image*>(image),
                                  static_cast<DXGI_FORMAT>(fmt),
                                  *static_cast<DirectX::ScratchImage*>(scratch_image)));
}

API ERROR_CODE scratchimage_decompress(const void* images, SIZE num_images, const void* meta, ENUM fmt,
                                       void* scratch_image) noexcept
{
    return ec(DirectX::Decompress(static_cast<const DirectX::Image*>(images),
                                  static_cast<size_t>(num_images),
                                  *static_cast<const DirectX::TexMetadata*>(meta),
                                  static_cast<DXGI_FORMAT>(fmt),
                                  *static_cast<DirectX::ScratchImage*>(scratch_image)));
}

API ERROR_CODE image_compute_normal_map(const void* image, ENUM flags, float amplitude, ENUM fmt,
                                        void* scratch_image) noexcept
{
    return ec(DirectX::ComputeNormalMap(*static_cast<const DirectX::Image*>(image),
                                        static_cast<DirectX::CNMAP_FLAGS>(flags),
                                        amplitude,
                                        static_cast<DXGI_FORMAT>(fmt),
                                        *static_cast<DirectX::ScratchImage*>(scratch_image)));
}

API ERROR_CODE scratchimage_compute_normal_map(const void* images, SIZE num_images, const void* meta, ENUM flags,
                                               float amplitude, ENUM fmt, void* scratch_image) noexcept
{
    return ec(DirectX::ComputeNormalMap(static_cast<const DirectX::Image*>(images),
                                        static_cast<size_t>(num_images),
                                        *static_cast<const DirectX::TexMetadata*>(meta),
                                        static_cast<DirectX::CNMAP_FLAGS>(flags),
                                        amplitude,
                                        static_cast<DXGI_FORMAT>(fmt),
                                        *static_cast<DirectX::ScratchImage*>(scratch_image)));
}

API void copy_array(void* target, void* source, SIZE size)
{
    std::memcpy(target, source, static_cast<size_t>(size));
}

// Skipping Rect, Transform, WIC Utility, D11 Textures and WIC saving.