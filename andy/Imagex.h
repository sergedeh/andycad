// Imagex.h: interface for the CImagex class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMAGEX_H__72667AA8_96A2_42D2_9B17_8EF7B40978B2__INCLUDED_)
#define AFX_IMAGEX_H__72667AA8_96A2_42D2_9B17_8EF7B40978B2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// defines

//#define DIBSECTION_NO_DITHER          // Disallow dithering via DrawDib functions
#define DIBSECTION_NO_MEMDC_REUSE       // Disallow the reuse of memory DC's
//#define DIBSECTION_NO_PALETTE         // Remove palette support

// Only provide palette support for non-CE platforms, or for CE 2.11 and above
#ifdef _WIN32_WCE
#define DIBSECTION_NO_DITHER            // DrawDib not supported on CE
#if (_WIN32_WCE < 211)
#define DIBSECTION_NO_PALETTE           // No palette support on early CE devices
#endif
#endif

// Include headers and lib for DrawDib routines
#ifndef DIBSECTION_NO_DITHER 
#include <vfw.h>
#pragma comment(lib, "vfw32")
#endif

#define DS_BITMAP_FILEMARKER  ((WORD) ('M' << 8) | 'B')    // is always "BM" = 0x4D42
/////////////////////////////////////////////////////////////////////////////
typedef struct _CGLRGBTRIPLE {
   BYTE rgbRed ;
   BYTE rgbGreen ;
   BYTE rgbBlue ;
} CGLRGBTRIPLE ;

// BITMAPINFO wrapper

struct DIBINFO : public BITMAPINFO
{
	RGBQUAD	 arColors[255];    // Color table info - adds an extra 255 entries to palette

	operator LPBITMAPINFO()          { return (LPBITMAPINFO) this; }
	operator LPBITMAPINFOHEADER()    { return &bmiHeader;          }
	RGBQUAD* ColorTable()            { return bmiColors;           }
};
/////////////////////////////////////////////////////////////////////////////
// LOGPALETTE wrapper

#ifndef DIBSECTION_NO_PALETTE
struct PALETTEINFO : public LOGPALETTE
{
    PALETTEENTRY arPalEntries[255];               // Palette entries

    PALETTEINFO() 
    {
        palVersion    = (WORD) 0x300;
        palNumEntries = 0;
        ::memset(palPalEntry, 0, 256*sizeof(PALETTEENTRY)); 
    }

    operator LPLOGPALETTE()   { return (LPLOGPALETTE) this;            }
    operator LPPALETTEENTRY() { return (LPPALETTEENTRY) (palPalEntry); }
};
#endif // DIBSECTION_NO_PALETTE


class CImagex  
{
 protected:
   // Member Variables
   HBITMAP m_hBitmap;
   BOOL bTrans;
   COLORREF crTransColor;
   int     m_iWidth, m_iHeight;
   HDC      m_MemDC;            // Memory DC for drawing on bitmap
    DIBINFO  m_DIBinfo;          // Bitmap header & color table info
	static RGBQUAD ms_StdColors[];
    VOID    *m_ppvBits;          // Pointer to bitmap bits
    UINT     m_iColorDataType;   // color data type (palette or RGB values)
    UINT     m_iColorTableSize;  // Size of color table
#ifndef DIBSECTION_NO_DITHER
    BOOL     m_bDither;           // Use DrawDib routines for dithering?
    HDRAWDIB m_hDrawDib;          // handle to a DrawDib DC 
#endif

#ifndef DIBSECTION_NO_MEMDC_REUSE
    BOOL     m_bReuseMemDC;      // Reeuse the memory DC? (Quicker, but not fully tested)
#endif

#ifndef DIBSECTION_NO_PALETTE
    HPALETTE m_Palette;         // Color palette
    HPALETTE *m_pOldPalette;
#endif // DIBSECTION_NO_PALETTE

	// Helper Methods
   void Free();

 public:
   // Constructor(s)/Destructor
    BOOL SetBitmap(HDC hdc,HBITMAP hBitmap
#ifndef DIBSECTION_NO_PALETTE
                   , HPALETTE* pPalette = NULL
#endif
                   );
   CImagex();
   CImagex(HDC hDC, LPTSTR szFileName,BOOL bTrans=FALSE, COLORREF crTransColor=RGB(255,255,255));
   CImagex(HDC hDC, UINT uiResID, HINSTANCE hInstance,BOOL bTrans=FALSE, COLORREF crTransColor=RGB(255,255,255));
   CImagex(HDC hDC, int iWidth, int iHeight, COLORREF crColor =
     RGB(0, 0, 0));
   virtual ~CImagex();

   // General Methods
   BOOL Create(HDC hDC, LPTSTR szFileName);
   BOOL Create(HDC hDC, UINT uiResID, HINSTANCE hInstance);
   BOOL Create(HDC hDC, int iWidth, int iHeight, COLORREF crColor);
   void Draw(HDC hDC, int x, int y);

   void DrawPart(HDC hDC, int x, int y, int xPart, int yPart,
   int wPart, int hPart);

   int  GetWidth() { return m_iWidth; };
   int  GetHeight() { return m_iHeight; };
   int          GetPlanes() const           { return m_DIBinfo.bmiHeader.biPlanes;    }
   int          GetBitCount() const         { return m_DIBinfo.bmiHeader.biBitCount;  }
   LPVOID       GetDIBits()                 { return m_ppvBits;                       }
   LPBITMAPINFO GetBitmapInfo()             { return  (BITMAPINFO*) m_DIBinfo;        }
   DWORD        GetImageSize() const        { return m_DIBinfo.bmiHeader.biSizeImage; }
   LPBITMAPINFOHEADER GetBitmapInfoHeader() { return (BITMAPINFOHEADER*) m_DIBinfo;   }

   LPRGBQUAD GetColorTable()             { return m_DIBinfo.ColorTable();          }
   BYTE* ConvertRGB();

 private:
    BOOL SetBitmap(HDC hdc,HINSTANCE handle,UINT nIDResource);
    BOOL SetBitmap(HDC hdc,LPBITMAPINFO lpBitmapInfo, LPVOID lpBits);
	BOOL SetBitmap(HDC hdc,HINSTANCE handle,LPCTSTR lpszResourceName);

	UINT GetColorTableEntries(HDC hdc, HBITMAP hBitmap);
	BOOL SetPalette(HPALETTE* pPalette);
	BOOL SetLogPalette(LOGPALETTE* pLogPalette);
#ifndef DIBSECTION_NO_PALETTE
    BOOL CreatePalette();
    BOOL FillDIBColorTable(UINT nNumColors, RGBQUAD *pRGB);
#endif // DIBSECTION_NO_PALETTE
#ifndef DIBSECTION_NO_PALETTE
    static BOOL UsesPalette(HDC* pDC) { return (::GetDeviceCaps(*pDC,RASTERCAPS) & RC_PALETTE); }
    static BOOL CreateHalftonePalette(HPALETTE& palette, int nNumColors);
#endif // DIBSECTION_NO_PALETTE
	 
   int NumColorEntries(int nBitsPerPixel, int nCompression, DWORD biClrUsed = 0);
   int BytesPerLine(int nWidth, int nBitsPerPixel);
   void DeleteObject();
   BOOL ReleaseMemoryDC(BOOL bForceRelease =FALSE);

   HBITMAP  m_hOldBitmap;      // Storage for previous bitmap in Memory DC


};



#endif // !defined(AFX_IMAGEX_H__72667AA8_96A2_42D2_9B17_8EF7B40978B2__INCLUDED_)
