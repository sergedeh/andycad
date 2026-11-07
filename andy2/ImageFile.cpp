// ImageFile.cpp — see ImageFile.h.

#include <windows.h>
#include <wincodec.h>
#include <algorithm>
#include <cwctype>

#include "ImageFile.h"

#pragma comment(lib, "windowscodecs.lib")
#pragma comment(lib, "ole32.lib")

namespace {

// COM for the calling thread for the duration of one call.
struct ComScope {
	HRESULT hr;
	ComScope() : hr(CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED)) {}
	~ComScope() { if (SUCCEEDED(hr)) CoUninitialize(); }
};

template <class T> struct Ptr {
	T* p = nullptr;
	~Ptr() { if (p) p->Release(); }
	T** operator&() { return &p; }
	T* operator->() const { return p; }
	explicit operator bool() const { return p != nullptr; }
};

IWICImagingFactory* NewFactory() {
	IWICImagingFactory* f = nullptr;
	CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&f));
	return f;
}

// Straight 0xAARRGGBB <-> WIC 32bppBGRA (same byte order in memory).
bool ReadSource(IWICImagingFactory* wic, IWICBitmapSource* src, int& w, int& h, std::vector<uint32_t>& px) {
	Ptr<IWICFormatConverter> conv;
	if (FAILED(wic->CreateFormatConverter(&conv)) ||
	    FAILED(conv->Initialize(src, GUID_WICPixelFormat32bppBGRA, WICBitmapDitherTypeNone,
	                            nullptr, 0.0, WICBitmapPaletteTypeCustom)))
		return false;
	UINT uw = 0, uh = 0;
	conv->GetSize(&uw, &uh);
	if (uw == 0 || uh == 0 || (UINT64)uw * uh > 64ull * 1024 * 1024) return false;
	px.resize((size_t)uw * uh);
	if (FAILED(conv->CopyPixels(nullptr, uw * 4, (UINT)(px.size() * 4), (BYTE*)px.data())))
		return false;
	w = (int)uw; h = (int)uh;
	return true;
}

GUID ContainerFor(const std::wstring& path) {
	std::wstring ext;
	size_t dot = path.find_last_of(L'.');
	if (dot != std::wstring::npos) ext = path.substr(dot + 1);
	std::transform(ext.begin(), ext.end(), ext.begin(), [](wchar_t c) { return (wchar_t)towlower(c); });
	if (ext == L"jpg" || ext == L"jpeg") return GUID_ContainerFormatJpeg;
	if (ext == L"bmp") return GUID_ContainerFormatBmp;
	if (ext == L"tif" || ext == L"tiff") return GUID_ContainerFormatTiff;
	if (ext == L"gif") return GUID_ContainerFormatGif;
	return GUID_ContainerFormatPng;
}

} // namespace

bool CImageFile::Load(const std::wstring& path) {
	m_width = m_height = 0;
	m_pixels.clear();
	m_path.clear();
	ComScope com;
	Ptr<IWICImagingFactory> wic;
	wic.p = NewFactory();
	if (!wic) return false;
	Ptr<IWICBitmapDecoder> dec;
	Ptr<IWICBitmapFrameDecode> frame;
	if (FAILED(wic->CreateDecoderFromFilename(path.c_str(), nullptr, GENERIC_READ,
	                                          WICDecodeMetadataCacheOnDemand, &dec)) ||
	    FAILED(dec->GetFrame(0, &frame)))
		return false;
	if (!ReadSource(wic.p, frame.p, m_width, m_height, m_pixels)) {
		m_width = m_height = 0;
		m_pixels.clear();
		return false;
	}
	m_path = path;
	return true;
}

bool CImageFile::Save(const std::wstring& path) const {
	if (!IsValid()) return false;
	ComScope com;
	Ptr<IWICImagingFactory> wic;
	wic.p = NewFactory();
	if (!wic) return false;
	Ptr<IWICStream> stream;
	Ptr<IWICBitmapEncoder> enc;
	Ptr<IWICBitmapFrameEncode> frame;
	Ptr<IPropertyBag2> props;
	if (FAILED(wic->CreateStream(&stream)) ||
	    FAILED(stream->InitializeFromFilename(path.c_str(), GENERIC_WRITE)) ||
	    FAILED(wic->CreateEncoder(ContainerFor(path), nullptr, &enc)) ||
	    FAILED(enc->Initialize(stream.p, WICBitmapEncoderNoCache)) ||
	    FAILED(enc->CreateNewFrame(&frame, &props)) ||
	    FAILED(frame->Initialize(props.p)) ||
	    FAILED(frame->SetSize((UINT)m_width, (UINT)m_height)))
		return false;
	// Let the encoder pick its nearest format, then convert to it.
	WICPixelFormatGUID fmt = GUID_WICPixelFormat32bppBGRA;
	frame->SetPixelFormat(&fmt);
	Ptr<IWICBitmap> bmp;
	if (FAILED(wic->CreateBitmapFromMemory((UINT)m_width, (UINT)m_height, GUID_WICPixelFormat32bppBGRA,
	                                       (UINT)m_width * 4, (UINT)(m_pixels.size() * 4),
	                                       (BYTE*)m_pixels.data(), &bmp)))
		return false;
	HRESULT hr;
	if (IsEqualGUID(fmt, GUID_WICPixelFormat32bppBGRA)) {
		hr = frame->WriteSource(bmp.p, nullptr);
	} else {
		Ptr<IWICFormatConverter> conv;
		if (FAILED(wic->CreateFormatConverter(&conv)) ||
		    FAILED(conv->Initialize(bmp.p, fmt, WICBitmapDitherTypeNone, nullptr, 0.0,
		                            WICBitmapPaletteTypeMedianCut)))
			return false;
		hr = frame->WriteSource(conv.p, nullptr);
	}
	return SUCCEEDED(hr) && SUCCEEDED(frame->Commit()) && SUCCEEDED(enc->Commit());
}

void CImageFile::Assign(int width, int height, const uint32_t* pixels) {
	m_width = width > 0 ? width : 0;
	m_height = height > 0 ? height : 0;
	m_pixels.assign(pixels, pixels + (size_t)m_width * m_height);
	m_path.clear();
}

bool CImageFile::HasAlpha() const {
	for (uint32_t p : m_pixels)
		if ((p >> 24) != 0xFF) return true;
	return false;
}

void CImageFile::FlipVertical() {
	for (int y = 0; y < m_height / 2; ++y)
		std::swap_ranges(m_pixels.begin() + (size_t)y * m_width, m_pixels.begin() + (size_t)(y + 1) * m_width,
		                 m_pixels.begin() + (size_t)(m_height - 1 - y) * m_width);
}

void CImageFile::FlipHorizontal() {
	for (int y = 0; y < m_height; ++y)
		std::reverse(m_pixels.begin() + (size_t)y * m_width, m_pixels.begin() + (size_t)(y + 1) * m_width);
}

bool CImageFile::Resize(int width, int height) {
	if (!IsValid() || width <= 0 || height <= 0) return false;
	ComScope com;
	Ptr<IWICImagingFactory> wic;
	wic.p = NewFactory();
	if (!wic) return false;
	Ptr<IWICBitmap> bmp;
	Ptr<IWICBitmapScaler> scaler;
	if (FAILED(wic->CreateBitmapFromMemory((UINT)m_width, (UINT)m_height, GUID_WICPixelFormat32bppBGRA,
	                                       (UINT)m_width * 4, (UINT)(m_pixels.size() * 4),
	                                       (BYTE*)m_pixels.data(), &bmp)) ||
	    FAILED(wic->CreateBitmapScaler(&scaler)) ||
	    FAILED(scaler->Initialize(bmp.p, (UINT)width, (UINT)height, WICBitmapInterpolationModeFant)))
		return false;
	int w = 0, h = 0;
	std::vector<uint32_t> px;
	if (!ReadSource(wic.p, scaler.p, w, h, px)) return false;
	m_width = w; m_height = h; m_pixels.swap(px);
	return true;
}
