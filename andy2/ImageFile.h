// ImageFile.h — an image file in memory (the role CxImage used to play).
//
// Loads and saves BMP, PNG, JPEG, TIFF, GIF and ICO (plus any WIC codecs
// installed on the machine) through the Windows Imaging Component, and
// keeps the pixels as straight-alpha 0xAARRGGBB, top row first.

#pragma once

#include <cstdint>
#include <string>
#include <vector>

class CImageFile
{
public:
	CImageFile() = default;

	// Load a file; false (and an empty image) if it can't be decoded.
	bool Load(const std::wstring& path);
	// Save to a file; the format comes from the extension (.png, .jpg,
	// .jpeg, .bmp, .tif, .tiff, .gif). PNG keeps alpha.
	bool Save(const std::wstring& path) const;

	// Make an image from pixels (0xAARRGGBB, top row first).
	void Assign(int width, int height, const uint32_t* pixels);

	bool   IsValid() const { return m_width > 0 && m_height > 0; }
	int    Width()  const { return m_width; }
	int    Height() const { return m_height; }
	const uint32_t* Pixels() const { return m_pixels.data(); }
	uint32_t Pixel(int x, int y) const { return m_pixels[(size_t)y * m_width + x]; }
	// True if any pixel is not fully opaque.
	bool   HasAlpha() const;
	const std::wstring& Path() const { return m_path; }

	void FlipVertical();
	void FlipHorizontal();
	// High-quality resize (WIC Fant scaler); false on failure.
	bool Resize(int width, int height);

private:
	int m_width = 0, m_height = 0;
	std::vector<uint32_t> m_pixels;
	std::wstring m_path;
};
