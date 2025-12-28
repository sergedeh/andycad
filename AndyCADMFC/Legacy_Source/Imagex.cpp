// Imagex.cpp: implementation of the CImagex class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cad.h"
#include "Imagex.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


// Spit out some messages as a sanity check for programmers
#ifdef DIBSECTION_NO_DITHER
#pragma message(" - CDIBSectionLite: No dithering")
#endif
#ifdef DIBSECTION_NO_MEMDC_REUSE
#pragma message(" - CDIBSectionLite: No memory DC reuse")
#endif
#ifdef DIBSECTION_NO_PALETTE
#pragma message(" - CDIBSectionLite: No palette support")
#endif

// Standard colors
RGBQUAD CImagex::ms_StdColors[] = {
    { 0x00, 0x00, 0x00, 0 },  // System palette - first 10 colors
    { 0x80, 0x00, 0x00, 0 },
    { 0x00, 0x80, 0x00, 0 },
    { 0x80, 0x80, 0x00, 0 },
    { 0x00, 0x00, 0x80, 0 },
    { 0x80, 0x00, 0x80, 0 },
    { 0x00, 0x80, 0x80, 0 },
    { 0xC0, 0xC0, 0xC0, 0 },
    { 0xC0, 0xDC, 0xC0, 0 },
    { 0xA6, 0xCA, 0xF0, 0 },

    { 0x2C, 0x00, 0x00, 0 },
    { 0x56, 0x00, 0x00, 0 },
    { 0x87, 0x00, 0x00, 0 },
    { 0xC0, 0x00, 0x00, 0 },
    { 0xFF, 0x00, 0x00, 0 },
    { 0x00, 0x2C, 0x00, 0 },
    { 0x2C, 0x2C, 0x00, 0 },
    { 0x56, 0x2C, 0x00, 0 },
    { 0x87, 0x2C, 0x00, 0 },
    { 0xC0, 0x2C, 0x00, 0 },
    { 0xFF, 0x2C, 0x00, 0 },
    { 0x00, 0x56, 0x00, 0 },
    { 0x2C, 0x56, 0x00, 0 },
    { 0x56, 0x56, 0x00, 0 },
    { 0x87, 0x56, 0x00, 0 },
    { 0xC0, 0x56, 0x00, 0 },
    { 0xFF, 0x56, 0x00, 0 },
    { 0x00, 0x87, 0x00, 0 },
    { 0x2C, 0x87, 0x00, 0 },
    { 0x56, 0x87, 0x00, 0 },
    { 0x87, 0x87, 0x00, 0 },
    { 0xC0, 0x87, 0x00, 0 },
    { 0xFF, 0x87, 0x00, 0 },
    { 0x00, 0xC0, 0x00, 0 },
    { 0x2C, 0xC0, 0x00, 0 },
    { 0x56, 0xC0, 0x00, 0 },
    { 0x87, 0xC0, 0x00, 0 },
    { 0xC0, 0xC0, 0x00, 0 },
    { 0xFF, 0xC0, 0x00, 0 },
    { 0x00, 0xFF, 0x00, 0 },
    { 0x2C, 0xFF, 0x00, 0 },
    { 0x56, 0xFF, 0x00, 0 },
    { 0x87, 0xFF, 0x00, 0 },
    { 0xC0, 0xFF, 0x00, 0 },
    { 0xFF, 0xFF, 0x00, 0 },
    { 0x00, 0x00, 0x2C, 0 },
    { 0x2C, 0x00, 0x2C, 0 },
    { 0x56, 0x00, 0x2C, 0 },
    { 0x87, 0x00, 0x2C, 0 },
    { 0xC0, 0x00, 0x2C, 0 },
    { 0xFF, 0x00, 0x2C, 0 },
    { 0x00, 0x2C, 0x2C, 0 },
    { 0x2C, 0x2C, 0x2C, 0 },
    { 0x56, 0x2C, 0x2C, 0 },
    { 0x87, 0x2C, 0x2C, 0 },
    { 0xC0, 0x2C, 0x2C, 0 },
    { 0xFF, 0x2C, 0x2C, 0 },
    { 0x00, 0x56, 0x2C, 0 },
    { 0x2C, 0x56, 0x2C, 0 },
    { 0x56, 0x56, 0x2C, 0 },
    { 0x87, 0x56, 0x2C, 0 },
    { 0xC0, 0x56, 0x2C, 0 },
    { 0xFF, 0x56, 0x2C, 0 },
    { 0x00, 0x87, 0x2C, 0 },
    { 0x2C, 0x87, 0x2C, 0 },
    { 0x56, 0x87, 0x2C, 0 },
    { 0x87, 0x87, 0x2C, 0 },
    { 0xC0, 0x87, 0x2C, 0 },
    { 0xFF, 0x87, 0x2C, 0 },
    { 0x00, 0xC0, 0x2C, 0 },
    { 0x2C, 0xC0, 0x2C, 0 },
    { 0x56, 0xC0, 0x2C, 0 },
    { 0x87, 0xC0, 0x2C, 0 },
    { 0xC0, 0xC0, 0x2C, 0 },
    { 0xFF, 0xC0, 0x2C, 0 },
    { 0x00, 0xFF, 0x2C, 0 },
    { 0x2C, 0xFF, 0x2C, 0 },
    { 0x56, 0xFF, 0x2C, 0 },
    { 0x87, 0xFF, 0x2C, 0 },
    { 0xC0, 0xFF, 0x2C, 0 },
    { 0xFF, 0xFF, 0x2C, 0 },
    { 0x00, 0x00, 0x56, 0 },
    { 0x2C, 0x00, 0x56, 0 },
    { 0x56, 0x00, 0x56, 0 },
    { 0x87, 0x00, 0x56, 0 },
    { 0xC0, 0x00, 0x56, 0 },
    { 0xFF, 0x00, 0x56, 0 },
    { 0x00, 0x2C, 0x56, 0 },
    { 0x2C, 0x2C, 0x56, 0 },
    { 0x56, 0x2C, 0x56, 0 },
    { 0x87, 0x2C, 0x56, 0 },
    { 0xC0, 0x2C, 0x56, 0 },
    { 0xFF, 0x2C, 0x56, 0 },
    { 0x00, 0x56, 0x56, 0 },
    { 0x2C, 0x56, 0x56, 0 },
    { 0x56, 0x56, 0x56, 0 },
    { 0x87, 0x56, 0x56, 0 },
    { 0xC0, 0x56, 0x56, 0 },
    { 0xFF, 0x56, 0x56, 0 },
    { 0x00, 0x87, 0x56, 0 },
    { 0x2C, 0x87, 0x56, 0 },
    { 0x56, 0x87, 0x56, 0 },
    { 0x87, 0x87, 0x56, 0 },
    { 0xC0, 0x87, 0x56, 0 },
    { 0xFF, 0x87, 0x56, 0 },
    { 0x00, 0xC0, 0x56, 0 },
    { 0x2C, 0xC0, 0x56, 0 },
    { 0x56, 0xC0, 0x56, 0 },
    { 0x87, 0xC0, 0x56, 0 },
    { 0xC0, 0xC0, 0x56, 0 },
    { 0xFF, 0xC0, 0x56, 0 },
    { 0x00, 0xFF, 0x56, 0 },
    { 0x2C, 0xFF, 0x56, 0 },
    { 0x56, 0xFF, 0x56, 0 },
    { 0x87, 0xFF, 0x56, 0 },
    { 0xC0, 0xFF, 0x56, 0 },
    { 0xFF, 0xFF, 0x56, 0 },
    { 0x00, 0x00, 0x87, 0 },
    { 0x2C, 0x00, 0x87, 0 },
    { 0x56, 0x00, 0x87, 0 },
    { 0x87, 0x00, 0x87, 0 },
    { 0xC0, 0x00, 0x87, 0 },
    { 0xFF, 0x00, 0x87, 0 },
    { 0x00, 0x2C, 0x87, 0 },
    { 0x2C, 0x2C, 0x87, 0 },
    { 0x56, 0x2C, 0x87, 0 },
    { 0x87, 0x2C, 0x87, 0 },
    { 0xC0, 0x2C, 0x87, 0 },
    { 0xFF, 0x2C, 0x87, 0 },
    { 0x00, 0x56, 0x87, 0 },
    { 0x2C, 0x56, 0x87, 0 },
    { 0x56, 0x56, 0x87, 0 },
    { 0x87, 0x56, 0x87, 0 },
    { 0xC0, 0x56, 0x87, 0 },
    { 0xFF, 0x56, 0x87, 0 },
    { 0x00, 0x87, 0x87, 0 },
    { 0x2C, 0x87, 0x87, 0 },
    { 0x56, 0x87, 0x87, 0 },
    { 0x87, 0x87, 0x87, 0 },
    { 0xC0, 0x87, 0x87, 0 },
    { 0xFF, 0x87, 0x87, 0 },
    { 0x00, 0xC0, 0x87, 0 },
    { 0x2C, 0xC0, 0x87, 0 },
    { 0x56, 0xC0, 0x87, 0 },
    { 0x87, 0xC0, 0x87, 0 },
    { 0xC0, 0xC0, 0x87, 0 },
    { 0xFF, 0xC0, 0x87, 0 },
    { 0x00, 0xFF, 0x87, 0 },
    { 0x2C, 0xFF, 0x87, 0 },
    { 0x56, 0xFF, 0x87, 0 },
    { 0x87, 0xFF, 0x87, 0 },
    { 0xC0, 0xFF, 0x87, 0 },
    { 0xFF, 0xFF, 0x87, 0 },
    { 0x00, 0x00, 0xC0, 0 },
    { 0x2C, 0x00, 0xC0, 0 },
    { 0x56, 0x00, 0xC0, 0 },
    { 0x87, 0x00, 0xC0, 0 },
    { 0xC0, 0x00, 0xC0, 0 },
    { 0xFF, 0x00, 0xC0, 0 },
    { 0x00, 0x2C, 0xC0, 0 },
    { 0x2C, 0x2C, 0xC0, 0 },
    { 0x56, 0x2C, 0xC0, 0 },
    { 0x87, 0x2C, 0xC0, 0 },
    { 0xC0, 0x2C, 0xC0, 0 },
    { 0xFF, 0x2C, 0xC0, 0 },
    { 0x00, 0x56, 0xC0, 0 },
    { 0x2C, 0x56, 0xC0, 0 },
    { 0x56, 0x56, 0xC0, 0 },
    { 0x87, 0x56, 0xC0, 0 },
    { 0xC0, 0x56, 0xC0, 0 },
    { 0xFF, 0x56, 0xC0, 0 },
    { 0x00, 0x87, 0xC0, 0 },
    { 0x2C, 0x87, 0xC0, 0 },
    { 0x56, 0x87, 0xC0, 0 },
    { 0x87, 0x87, 0xC0, 0 },
    { 0xC0, 0x87, 0xC0, 0 },
    { 0xFF, 0x87, 0xC0, 0 },
    { 0x00, 0xC0, 0xC0, 0 },
    { 0x2C, 0xC0, 0xC0, 0 },
    { 0x56, 0xC0, 0xC0, 0 },
    { 0x87, 0xC0, 0xC0, 0 },
    { 0xFF, 0xC0, 0xC0, 0 },
    { 0x00, 0xFF, 0xC0, 0 },
    { 0x2C, 0xFF, 0xC0, 0 },
    { 0x56, 0xFF, 0xC0, 0 },
    { 0x87, 0xFF, 0xC0, 0 },
    { 0xC0, 0xFF, 0xC0, 0 },
    { 0xFF, 0xFF, 0xC0, 0 },
    { 0x00, 0x00, 0xFF, 0 },
    { 0x2C, 0x00, 0xFF, 0 },
    { 0x56, 0x00, 0xFF, 0 },
    { 0x87, 0x00, 0xFF, 0 },
    { 0xC0, 0x00, 0xFF, 0 },
    { 0xFF, 0x00, 0xFF, 0 },
    { 0x00, 0x2C, 0xFF, 0 },
    { 0x2C, 0x2C, 0xFF, 0 },
    { 0x56, 0x2C, 0xFF, 0 },
    { 0x87, 0x2C, 0xFF, 0 },
    { 0xC0, 0x2C, 0xFF, 0 },
    { 0xFF, 0x2C, 0xFF, 0 },
    { 0x00, 0x56, 0xFF, 0 },
    { 0x2C, 0x56, 0xFF, 0 },
    { 0x56, 0x56, 0xFF, 0 },
    { 0x87, 0x56, 0xFF, 0 },
    { 0xC0, 0x56, 0xFF, 0 },
    { 0xFF, 0x56, 0xFF, 0 },
    { 0x00, 0x87, 0xFF, 0 },
    { 0x2C, 0x87, 0xFF, 0 },
    { 0x56, 0x87, 0xFF, 0 },
    { 0x87, 0x87, 0xFF, 0 },
    { 0xC0, 0x87, 0xFF, 0 },
    { 0xFF, 0x87, 0xFF, 0 },
    { 0x00, 0xC0, 0xFF, 0 },
    { 0x2C, 0xC0, 0xFF, 0 },
    { 0x56, 0xC0, 0xFF, 0 },
    { 0x87, 0xC0, 0xFF, 0 },
    { 0xC0, 0xC0, 0xFF, 0 },
    { 0xFF, 0xC0, 0xFF, 0 },
    { 0x2C, 0xFF, 0xFF, 0 },
    { 0x56, 0xFF, 0xFF, 0 },
    { 0x87, 0xFF, 0xFF, 0 },
    { 0xC0, 0xFF, 0xFF, 0 },
    { 0xFF, 0xFF, 0xFF, 0 },
    { 0x11, 0x11, 0x11, 0 },
    { 0x18, 0x18, 0x18, 0 },
    { 0x1E, 0x1E, 0x1E, 0 },
    { 0x25, 0x25, 0x25, 0 },
    { 0x2C, 0x2C, 0x2C, 0 },
    { 0x34, 0x34, 0x34, 0 },
    { 0x3C, 0x3C, 0x3C, 0 },
    { 0x44, 0x44, 0x44, 0 },
    { 0x4D, 0x4D, 0x4D, 0 },
    { 0x56, 0x56, 0x56, 0 },
    { 0x5F, 0x5F, 0x5F, 0 },
    { 0x69, 0x69, 0x69, 0 },
    { 0x72, 0x72, 0x72, 0 },
    { 0x7D, 0x7D, 0x7D, 0 },
    { 0x92, 0x92, 0x92, 0 },
    { 0x9D, 0x9D, 0x9D, 0 },
    { 0xA8, 0xA8, 0xA8, 0 },
    { 0xB4, 0xB4, 0xB4, 0 },
    { 0xCC, 0xCC, 0xCC, 0 },
    { 0xD8, 0xD8, 0xD8, 0 },
    { 0xE5, 0xE5, 0xE5, 0 },
    { 0xF2, 0xF2, 0xF2, 0 },
    { 0xFF, 0xFF, 0xFF, 0 },

    { 0xFF, 0xFB, 0xF0, 0 },  // System palette - last 10 colors
    { 0xA0, 0xA0, 0xA4, 0 },
    { 0x80, 0x80, 0x80, 0 },
    { 0xFF, 0x00, 0x00, 0 },
    { 0x00, 0xFF, 0x00, 0 },
    { 0xFF, 0xFF, 0x00, 0 },
    { 0x00, 0x00, 0xFF, 0 },
    { 0xFF, 0x00, 0xFF, 0 },
    { 0x00, 0xFF, 0xFF, 0 },
    { 0xFF, 0xFF, 0xFF, 0 },
};

void error(LPSTR lpszFunction) 
{ 
    CHAR szBuf[80]; 
    DWORD dw = GetLastError(); 
 
    sprintf(szBuf, "%s failed: GetLastError returned %u\n", 
        lpszFunction, dw); 
 
    MessageBox(NULL, szBuf, "ERROR", MB_OK); 
    ExitProcess(dw); 
} 
 

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CImagex::CImagex()
{

    m_hBitmap     = NULL;
    m_hOldBitmap  = NULL;

#ifndef DIBSECTION_NO_MEMDC_REUSE
    m_bReuseMemDC = FALSE;
#endif

#ifndef DIBSECTION_NO_PALETTE
    m_pOldPalette = NULL;
#endif

#ifndef DIBSECTION_NO_DITHER
    m_bDither     = FALSE;
    m_hDrawDib    = NULL;
#endif

    DeleteObject(); // This will initialise to a known state - ie. empty

}

CImagex::~CImagex()
{
    if (m_hBitmap)
        ::DeleteObject(m_hBitmap);
}
CImagex::CImagex(HDC hDC, LPTSTR szFileName,BOOL bT, COLORREF crT)
{
	bTrans=bT;
	crTransColor=crT;
    m_hBitmap     = NULL;
    m_hOldBitmap  = NULL;

#ifndef DIBSECTION_NO_MEMDC_REUSE
    m_bReuseMemDC = FALSE;
#endif

#ifndef DIBSECTION_NO_PALETTE
    m_pOldPalette = NULL;
#endif

#ifndef DIBSECTION_NO_DITHER
    m_bDither     = FALSE;
    m_hDrawDib    = NULL;
#endif

    DeleteObject(); // This will initialise to a known state - ie. empty

	Create(hDC,szFileName);
}
CImagex::CImagex(HDC hDC, UINT uiResID, HINSTANCE hInstance,BOOL bT, COLORREF crT)
{
	bTrans=bT;
	crTransColor=crT;
    m_hBitmap     = NULL;
    m_hOldBitmap  = NULL;

#ifndef DIBSECTION_NO_MEMDC_REUSE
    m_bReuseMemDC = FALSE;
#endif

#ifndef DIBSECTION_NO_PALETTE
    m_pOldPalette = NULL;
#endif

#ifndef DIBSECTION_NO_DITHER
    m_bDither     = FALSE;
    m_hDrawDib    = NULL;
#endif

    DeleteObject(); // This will initialise to a known state - ie. empty

	Create(hDC,uiResID,hInstance);

}
CImagex::CImagex(HDC hDC, int iWidth, int iHeight, COLORREF crColor)
{
	bTrans=false;
	crTransColor=RGB(0,0,0);
    m_hBitmap     = NULL;
    m_hOldBitmap  = NULL;

#ifndef DIBSECTION_NO_MEMDC_REUSE
    m_bReuseMemDC = FALSE;
#endif

#ifndef DIBSECTION_NO_PALETTE
    m_pOldPalette = NULL;
#endif

#ifndef DIBSECTION_NO_DITHER
    m_bDither     = FALSE;
    m_hDrawDib    = NULL;
#endif

    DeleteObject(); // This will initialise to a known state - ie. empty
    m_iWidth=iWidth;
	m_iHeight=iHeight;
	Create(hDC,iWidth,iHeight,crColor);
}

// Setting the bitmap...

// --- In  : nIDResource - resource ID
// --- Out :
// --- Returns : Returns TRUE on success, FALSE otherwise
// --- Effect : Initialises the bitmap from a resource. If failure, then object is
//              initialised back to an empty bitmap.
BOOL CImagex::SetBitmap(HDC hdc,HINSTANCE handle,UINT nIDResource)
{
    return SetBitmap(hdc,handle,MAKEINTRESOURCE(nIDResource));
}

// --- In  : lpszResourceName - resource name
// --- Out :
// --- Returns : Returns TRUE on success, FALSE otherwise
// --- Effect : Initialises the bitmap from a resource. If failure, then object is
//              initialised back to an empty bitmap.
BOOL CImagex::SetBitmap(HDC hdc,HINSTANCE handle,LPCTSTR lpszResourceName)
{
    HBITMAP hBmp = (HBITMAP)::LoadImage(handle,  
                                        lpszResourceName,
                                        IMAGE_BITMAP, 
                                        0,0, 
#ifdef _WIN32_WCE
                                        0
#else
                                        LR_CREATEDIBSECTION
#endif
                                        );

    if (!hBmp) 
    {
        error("Unable to LoadImage");
        return FALSE;
    }

    BOOL bResult = SetBitmap(hdc,hBmp);
    ::DeleteObject(hBmp);
    return bResult;
}


BOOL CImagex::Create(HDC hDC, LPTSTR szFileName)
{
	HANDLE hFile; 
 
hFile = CreateFile(szFileName,           // open MYFILE.TXT 
                GENERIC_READ,              // open for reading 
                FILE_SHARE_READ,           // share for reading 
                NULL,                      // no security 
                OPEN_EXISTING,             // existing file only 
                FILE_ATTRIBUTE_NORMAL,     // normal file 
                NULL);                     // no attr. template 
 
if (hFile == INVALID_HANDLE_VALUE) 
{ 
        error("Could not open file.");   // process error 
} 


    // Get the current file position.  
    DWORD dwFileStart = SetFilePointer (hFile, 0, NULL, FILE_CURRENT);//file.GetPosition();

    // The first part of the file contains the file header.
    // This will tell us if it is a bitmap, how big the header is, and how big 
    // the file is. The header size in the file header includes the color table.
    BITMAPFILEHEADER BmpFileHdr;
    DWORD nBytes;
	
    ReadFile(hFile,&BmpFileHdr, sizeof(BmpFileHdr),&nBytes,NULL);
    if (nBytes != sizeof(BmpFileHdr)) 
    {
        error("Failed to read file header\n");
        return FALSE;
    }

    // Check that we have the magic 'BM' at the start.
    if (BmpFileHdr.bfType != DS_BITMAP_FILEMARKER)
    {
        error("Not a bitmap file\n");
        return FALSE;
    }

    // Read the header (assuming it's a DIB). 
    DIBINFO    BmpInfo;
    ReadFile(hFile,&BmpInfo, sizeof(BITMAPINFOHEADER),&nBytes,NULL); 
    if (nBytes != sizeof(BITMAPINFOHEADER)) 
    {
        error("Failed to read BITMAPINFOHEADER\n");
        return FALSE;
    }

    // Check that we have a real Windows DIB file.
    if (BmpInfo.bmiHeader.biSize != sizeof(BITMAPINFOHEADER))
    {
        error(" File is not a Windows DIB\n");
        return FALSE;
    }

    // See how big the color table is in the file (if there is one).  
    int nColors = NumColorEntries(BmpInfo.bmiHeader.biBitCount, BmpInfo.bmiHeader.biCompression, BmpInfo.bmiHeader.biClrUsed);
    if (nColors > 0) 
    {
        // Read the color table from the file.
        int nColorTableSize = nColors * sizeof(RGBQUAD);
        ReadFile(hFile,BmpInfo.ColorTable(), nColorTableSize,&nBytes,NULL);
        if (nBytes != nColorTableSize) 
        {
            error("Failed to read color table\n");
            return FALSE;
        }
    }

    // So how big the bitmap surface is.
    int nBitsSize = BmpFileHdr.bfSize - BmpFileHdr.bfOffBits;

    // Double check that the bitmap surface if ok (sometimes the file size is a
    // little larger than the bitmap itself, which may cause overflows)
    int nSurfaceSize = BytesPerLine(BmpInfo.bmiHeader.biWidth, 
                                    BmpInfo.bmiHeader.biBitCount) *    BmpInfo.bmiHeader.biHeight;
    if (nSurfaceSize < nBitsSize)
    {
        // In this case we don't need the entire file
        nBitsSize = nSurfaceSize;
    }

    // Allocate the memory for the bits and read the bits from the file.
    BYTE* pBits = (BYTE*) malloc(nBitsSize);
    if (!pBits) 
    {
        error("Out of memory for DIB bits\n");
        return FALSE;
    }

    // Seek to the bits in the file.
    SetFilePointer (hFile,dwFileStart + BmpFileHdr.bfOffBits, NULL, FILE_BEGIN);//file.GetPosition();
	//file.Seek(dwFileStart + BmpFileHdr.bfOffBits, CFile::begin);

    // read the bits
    ReadFile(hFile,pBits, nBitsSize,&nBytes,NULL);
    if (nBytes != nBitsSize) 
    {
        error("Failed to read bits\n");
        free(pBits);
        return FALSE;
    }

    // Everything went OK.
    BmpInfo.bmiHeader.biSizeImage = nBitsSize;

    if (!SetBitmap(hDC,(LPBITMAPINFO) BmpInfo, pBits))
    {
        error("Failed to set bitmap info\n");
        free(pBits);
        return FALSE;
    }



    free(pBits);

    return TRUE;
	 
}

// --- In  : bForceRelease - if TRUE, then the memory DC is forcibly released
// --- Out :
// --- Returns : TRUE on success
// --- Effect : Selects out the current bitmap and deletes the mem dc. If bForceRelease 
//              is FALSE, then the DC release will not actually occur. This is provided 
//              so you can have
//
//                 GetMemoryDC(...)
//                 ... do something
//                 ReleaseMemoryDC()
//
//               bracketed calls. If m_bReuseMemDC is subsequently set to FALSE, then 
//               the same code fragment will still work.
BOOL CImagex::ReleaseMemoryDC(BOOL bForceRelease /*=FALSE*/)
{
    if ( !m_MemDC 
#ifndef DIBSECTION_NO_MEMDC_REUSE
        || (m_bReuseMemDC && !bForceRelease) 
#endif // DIBSECTION_NO_MEMDC_REUSE
        )
        return TRUE; // Nothing to do

#ifndef _WIN32_WCE
    // Flush the GDI batch queue 
    GdiFlush();
#endif // _WIN32_WCE

    // Select out the current bitmap
    if (m_hOldBitmap)
        ::SelectObject(m_MemDC, m_hOldBitmap);
    m_hOldBitmap = NULL;

#ifndef DIBSECTION_NO_PALETTE
    // Select out the current palette
    if (m_pOldPalette)
        ::SelectPalette(m_MemDC,*m_pOldPalette, FALSE);
    m_pOldPalette = NULL;
#endif // DIBSECTION_NO_PALETTE

    // Delete the memory DC
    return ::DeleteDC(m_MemDC);
}

void CImagex::DeleteObject()
{
    // Unselect the bitmap out of the memory DC before deleting bitmap
    ReleaseMemoryDC(TRUE);

    if (m_hBitmap)
        ::DeleteObject(m_hBitmap);
    m_hBitmap = NULL;
    m_ppvBits = NULL;

#ifndef DIBSECTION_NO_PALETTE
    ::DeleteObject(m_Palette);
#endif

    memset(&m_DIBinfo, 0, sizeof(m_DIBinfo));

#ifndef DIBSECTION_NO_DITHER
    if (m_hDrawDib)
        DrawDibClose(m_hDrawDib);
    m_hDrawDib = NULL;
#endif

    m_iColorDataType = DIB_RGB_COLORS;
    m_iColorTableSize = 0;
}

#ifndef DIBSECTION_NO_PALETTE

// --- In  : palette - reference to a palette object which will be filled
//           nNumColors - number of color entries to fill
// --- Out :
// --- Returns : TRUE on success, false otherwise
// --- Effect : Creates a halftone color palette independant of screen color depth.
//              palette will be filled with the colors, and nNumColors is the No.
//              of colors to file. If nNumColorsis 0 or > 256, then 256 colors are used.
/*static*/ BOOL CImagex::CreateHalftonePalette(HPALETTE& palette, int nNumColors)
{
    ::DeleteObject(palette);

    // Sanity check on requested number of colours.
    if (nNumColors <= 0 || nNumColors > 256)
        nNumColors = 256;
    else if (nNumColors <= 2)
        nNumColors = 2;
    else if (nNumColors <= 16)
        nNumColors = 16;
    else if  (nNumColors <= 256)
        nNumColors = 256;

    PALETTEINFO pi;                   
    pi.palNumEntries = (WORD) nNumColors;

    if (nNumColors == 2)
    {
        // According to the MS article "The Palette Manager: How and Why"
        // monochrome palettes not really needed (will use B&W)
        pi.palPalEntry[0].peRed   = ms_StdColors[0].rgbRed;
        pi.palPalEntry[0].peGreen = ms_StdColors[0].rgbGreen;
        pi.palPalEntry[0].peBlue  = ms_StdColors[0].rgbBlue;
        pi.palPalEntry[0].peFlags = 0;
        pi.palPalEntry[1].peRed   = ms_StdColors[255].rgbRed;
        pi.palPalEntry[1].peGreen = ms_StdColors[255].rgbGreen;
        pi.palPalEntry[1].peBlue  = ms_StdColors[255].rgbBlue;
        pi.palPalEntry[1].peFlags = 0;
   }
   else if (nNumColors == 16)
   {
        // According to the MS article "The Palette Manager: How and Why"
        // 4-bit palettes not really needed (will use VGA palette)
       for (int i = 0; i < 8; i++)
       {
           pi.palPalEntry[i].peRed   = ms_StdColors[i].rgbRed;
           pi.palPalEntry[i].peGreen = ms_StdColors[i].rgbGreen;
           pi.palPalEntry[i].peBlue  = ms_StdColors[i].rgbBlue;
           pi.palPalEntry[i].peFlags = 0;
       }
       for (i = 8; i < 16; i++)
       {
           pi.palPalEntry[i].peRed   = ms_StdColors[248+i].rgbRed;
           pi.palPalEntry[i].peGreen = ms_StdColors[248+i].rgbGreen;
           pi.palPalEntry[i].peBlue  = ms_StdColors[248+i].rgbBlue;
           pi.palPalEntry[i].peFlags = 0;
       }
   }
   else // if (nNumColors == 256)
   {
       // Fill palette with full halftone palette
       for (int i = 0; i < 256; i++)
       {
           pi.palPalEntry[i].peRed   = ms_StdColors[i].rgbRed;
           pi.palPalEntry[i].peGreen = ms_StdColors[i].rgbGreen;
           pi.palPalEntry[i].peBlue  = ms_StdColors[i].rgbBlue;
           pi.palPalEntry[i].peFlags = 0;
       }
   }

   return (((palette=::CreatePalette((LPLOGPALETTE) pi))==NULL)?0:1);
}
#endif // DIBSECTION_NO_PALETTE


#ifndef DIBSECTION_NO_PALETTE

// --- In  :
// --- Out :
// --- Returns : TRUE on success
// --- Effect : Creates the palette from the DIBSection's color table. Assumes 
//              m_iColorTableSize has been set and the DIBsection m_hBitmap created
BOOL CImagex::CreatePalette()
{
    ::DeleteObject(m_Palette);

    if (!m_hBitmap)
        return FALSE;

    // Create a 256 color halftone palette if there is no color table in the DIBSection
    if (m_iColorTableSize == 0)
        return CreateHalftonePalette(m_Palette, 256);

    // Get space for the color entries
    RGBQUAD *pRGB = new RGBQUAD[m_iColorTableSize];
    if (!pRGB)
        return CreateHalftonePalette(m_Palette, m_iColorTableSize);

    HDC hDC = ::GetDC(NULL);
    if (!hDC)
    {
        delete [] pRGB;
        return FALSE;
    }

    // Create a memory DC compatible with the current DC
    HDC MemDC;
    MemDC=::CreateCompatibleDC(hDC);
    if (!MemDC)
    {
        delete [] pRGB;
        ::ReleaseDC(NULL, hDC);
        return CreateHalftonePalette(m_Palette, m_iColorTableSize);
    }
    ::ReleaseDC(NULL, hDC);
    
    HBITMAP hOldBitmap = (HBITMAP) ::SelectObject(MemDC, m_hBitmap);
    if (!hOldBitmap)
    {
        delete [] pRGB;
        return CreateHalftonePalette(m_Palette, m_iColorTableSize);
    }

    // Get the colors used. WinCE does not support GetDIBColorTable so if you
    // are using this on a CE device with palettes, then you need to replace
    // the call with code that manually gets the color table from the m_DIBinfo structure.
#ifdef _WIN32_WCE
    int nColors = ::CEGetDIBColorTable(MemDC.GetSafeHdc(), 0, m_iColorTableSize, pRGB);
#else
    int nColors = ::GetDIBColorTable(MemDC, 0, m_iColorTableSize, pRGB);
#endif

    // Clean up
    ::SelectObject(MemDC, hOldBitmap);

    if (!nColors)   // No colors retrieved => the bitmap in the DC is not a DIB section
    {
        delete [] pRGB;
        return CreateHalftonePalette(m_Palette, m_iColorTableSize);
    }   
    
    // Create and fill a LOGPALETTE structure with the colors used.
    PALETTEINFO PaletteInfo;
    PaletteInfo.palNumEntries = m_iColorTableSize;
                        
    for (int i = 0; i < nColors; i++)
    {
        PaletteInfo.palPalEntry[i].peRed   = pRGB[i].rgbRed;
        PaletteInfo.palPalEntry[i].peGreen = pRGB[i].rgbGreen;
        PaletteInfo.palPalEntry[i].peBlue  = pRGB[i].rgbBlue;
        PaletteInfo.palPalEntry[i].peFlags = 0;
    }

    delete [] pRGB;

    // Create Palette!
	
    return (((m_Palette=::CreatePalette(&PaletteInfo))==NULL)?0:1); 
}
#endif // DIBSECTION_NO_PALETTE

// --- In  : lpBitmapInfo - pointer to a BITMAPINFO structure
//           lpBits - pointer to image bits. Can be NULL to simply create empty bitmap
// --- Out :
// --- Returns : Returns TRUE on success, FALSE otherwise
// --- Effect : Initialises the bitmap using the information in lpBitmapInfo to determine
//              the dimensions and colors, and the then sets the bits from the bits in
//              lpBits. If failure, then object is initialised back to an empty bitmap.
BOOL CImagex::SetBitmap(HDC hdc,LPBITMAPINFO lpBitmapInfo, LPVOID lpBits)
{
    DeleteObject();

    if (!lpBitmapInfo || !lpBits)
        return FALSE;

    m_iHeight=lpBitmapInfo->bmiHeader.biHeight;
	m_iWidth=lpBitmapInfo->bmiHeader.biWidth;

    HDC hDC = NULL;
    try {
        BITMAPINFOHEADER& bmih = lpBitmapInfo->bmiHeader;

        // Compute the number of colors in the color table
        m_iColorTableSize = NumColorEntries(bmih.biBitCount, bmih.biCompression, bmih.biClrUsed);

        DWORD dwBitmapInfoSize = sizeof(BITMAPINFO) + m_iColorTableSize*sizeof(RGBQUAD);

        // Copy over BITMAPINFO contents
        memcpy(&m_DIBinfo, lpBitmapInfo, dwBitmapInfoSize);

        // Should now have all the info we need to create the sucker.
        //TRACE(_T("Width %d, Height %d, Bits/pixel %d, Image Size %d\n"),
        //      bmih.biWidth, bmih.biHeight, bmih.biBitCount, bmih.biSizeImage);

        // Create a DC which will be used to get DIB, then create DIBsection
        hDC = ::GetDC(NULL);
        if (!hDC) 
        {
            error("Unable to get DC\n");

           // ::AfxThrowResourceException();
        }

        m_hBitmap = CreateDIBSection(hDC, (const BITMAPINFO*) m_DIBinfo,
                                     m_iColorDataType, &m_ppvBits, NULL, 0);
        ::ReleaseDC(NULL, hDC);
        if (!m_hBitmap)
        {
            error("CreateDIBSection failed\n");
//            AfxThrowResourceException();
        }

        if (m_DIBinfo.bmiHeader.biSizeImage == 0)
        {
            int nBytesPerLine = BytesPerLine(lpBitmapInfo->bmiHeader.biWidth, 
                                             lpBitmapInfo->bmiHeader.biBitCount);
            m_DIBinfo.bmiHeader.biSizeImage = nBytesPerLine * lpBitmapInfo->bmiHeader.biHeight;
        }

#ifndef _WIN32_WCE
        // Flush the GDI batch queue 
        GdiFlush();
#endif
        // Only copy bits if they were provided
        if (lpBits != NULL)
            memcpy(m_ppvBits, lpBits, m_DIBinfo.bmiHeader.biSizeImage);

#ifndef DIBSECTION_NO_PALETTE
        if (!CreatePalette())
        {
            error("Unable to create palette\n");
           // AfxThrowResourceException();
        }
#endif // DIBSECTION_NO_PALETTE
    }
    catch (char *s)
    {
		error("Exception");
        if (hDC) 
            ::ReleaseDC(NULL, hDC);
        DeleteObject();
        return FALSE;
    }

    return TRUE;
}

int CImagex::NumColorEntries(int nBitsPerPixel, int nCompression, DWORD biClrUsed /*= 0*/)
{
    int nColors = 0;

    switch (nBitsPerPixel) 
    {
        case 1:  
            nColors = 2;   
            break;
#ifdef _WIN32_WCE
        case 2:  
            nColors = 4;   
            break;   // winCE only       
#endif
        case 4:  
            nColors = 16;  
            break;
        case 8:  
            nColors = 256; 
            break;
        case 24: 
            nColors = 0;
		break;
        case 16:
        case 32:
#ifdef _WIN32_WCE
            nColors = 3;     // I've found that PocketPCs need this regardless of BI_RGB or BI_BITFIELDS
#else
            if (nCompression == BI_BITFIELDS)
                nColors = 3; // 16 or 32 bpp have 3 colors(masks) in the color table if bitfield compression
            else
                nColors = 0; // 16 or 32 bpp have no color table if no bitfield compression
#endif
            break;

        default:
           error("Error");
    }

    // If biClrUsed is provided, and it is a legal value, use it
    if (biClrUsed > 0 && biClrUsed <= (DWORD)nColors)
        return biClrUsed;

    return nColors;
}

// 
// --- In  : nWidth - image width in pixels
//           nBitsPerPixel - bits per pixel
// --- Out :
// --- Returns : Returns the number of storage bytes needed for each scanline 
//               in the bitmap
// --- Effect : 
/*static*/ int CImagex::BytesPerLine(int nWidth, int nBitsPerPixel)
{
    return ( (nWidth * nBitsPerPixel + 31) & (~31) ) / 8;
}



BOOL CImagex::Create(HDC hDC, UINT uiResID, HINSTANCE hInstance)
{
return SetBitmap(hDC,hInstance,MAKEINTRESOURCE(uiResID));
}
BOOL CImagex::Create(HDC hDC, int iWidth, int iHeight, COLORREF crColor)
{
	 m_hBitmap=CreateCompatibleBitmap(hDC,iWidth,iHeight);

     HDC hMemDC = CreateCompatibleDC(hDC);

     // Select the bitmap into the device context
     HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemDC, m_hBitmap);

     // Draw the bitmap to the destination device context
	 HBRUSH br;
	 br=CreateSolidBrush(crColor);
	 Rectangle(hMemDC,0,0,iWidth,iHeight);
     BitBlt(hDC, 0, 0, iWidth,iHeight, hMemDC, 0, 0, SRCCOPY);

     // Restore and delete the memory device context
     SelectObject(hMemDC, hOldBitmap);
     DeleteDC(hMemDC);

 return true;
}


void CImagex::DrawPart(HDC hDC, int x, int y, int xPart, int yPart,
   int wPart, int hPart)
{
   if (m_hBitmap != NULL)
   {
     // Create a memory device context for the bitmap
     HDC hMemDC = CreateCompatibleDC(hDC);

     // Select the bitmap into the device context
     HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemDC, m_hBitmap);

     // Draw the bitmap to the destination device context
  //   if (bTrans)
//	 TransparentBlt(hDC, x, y, wPart, hPart, hMemDC, xPart, yPart,
  //     wPart, hPart, crTransColor);
  //   else
       BitBlt(hDC, x, y, wPart, hPart, hMemDC, xPart, yPart, SRCCOPY);

     // Restore and delete the memory device context
     SelectObject(hMemDC, hOldBitmap);
     DeleteDC(hMemDC);
  }
}

void CImagex::Draw(HDC hDC, int x, int y)
 {
   DrawPart(hDC, x, y, 0, 0, GetWidth(), GetHeight());
 }


// --- In  : hBitmap - handle to image
//           pPalette - optional palette to use when setting image
// --- Out :
// --- Returns : Returns TRUE on success, FALSE otherwise
// --- Effect : Initialises the bitmap from the HBITMAP supplied. If failure, then
//              object is initialised back to an empty bitmap.
BOOL CImagex::SetBitmap(HDC hdc,HBITMAP hBitmap
#ifndef DIBSECTION_NO_PALETTE
                                , HPALETTE* pPalette /*= NULL*/
#endif
                                )
{
    DeleteObject();

    if (!hBitmap)
        return FALSE;

    // Get dimensions of bitmap
    BITMAP bm;
    if (!::GetObject(hBitmap, sizeof(bm),(LPVOID)&bm))
        return FALSE;
    bm.bmHeight = abs(bm.bmHeight);

	m_iHeight=bm.bmHeight;
	m_iWidth=bm.bmWidth;
//    CWindowDC dc(NULL);
#ifndef DIBSECTION_NO_PALETTE
    HPALETTE* pOldPalette = NULL;
#endif // DIBSECTION_NO_PALETTE

    try {
        m_iColorTableSize = NumColorEntries(bm.bmBitsPixel, BI_RGB);

        // Initialize the BITMAPINFOHEADER in m_DIBinfo
        BITMAPINFOHEADER& bih = m_DIBinfo.bmiHeader;
        bih.biSize          = sizeof(BITMAPINFOHEADER);
        bih.biWidth         = bm.bmWidth;
        bih.biHeight        = bm.bmHeight;
        bih.biPlanes        = 1;                // Must always be 1 according to docs
        bih.biBitCount      = bm.bmBitsPixel;

#ifdef _WIN32_WCE
	  //DCR 4/02/01  I've found PocketPCs need BI_BITFIELDS for 16 bit dibs.
        if (bm.bmBitsPixel == 16  || bm.bmBitsPixel == 32)
            bih.biCompression = BI_BITFIELDS; 
        else
            bih.biCompression = BI_RGB;
#else
        bih.biCompression = BI_RGB;
#endif

        bih.biSizeImage     = BytesPerLine(bm.bmWidth, bm.bmBitsPixel) * bm.bmHeight;
        bih.biXPelsPerMeter = 0;
        bih.biYPelsPerMeter = 0;
        bih.biClrUsed       = 0;
        bih.biClrImportant  = 0;

        GetColorTableEntries(hdc, hBitmap);

#ifndef DIBSECTION_NO_PALETTE
        // If we have a palette supplied, then set the palette (and hance DIB color
        // table) using this palette
        if (pPalette)
            SetPalette(pPalette);

        if (m_Palette)
        {
            pOldPalette = (HPALETTE*) SelectPalette(hdc,m_Palette, FALSE);
            RealizePalette(hdc);
        }
#endif // DIBSECTION_NO_PALETTE

        // Create it!
        m_hBitmap = CreateDIBSection(hdc, 
                                     (const BITMAPINFO*) m_DIBinfo,
                                     m_iColorDataType,
                                     &m_ppvBits, 
                                     NULL, 0);
#ifndef DIBSECTION_NO_PALETTE
        if (pOldPalette)
            SelectPalette(hdc,*pOldPalette, FALSE);
        pOldPalette = NULL; 
#endif // DIBSECTION_NO_PALETTE

        if (!m_hBitmap)
        {
            error("Unable to CreateDIBSection\n");
        }

#ifndef DIBSECTION_NO_PALETTE
        // If palette was supplied then create a palette using the entries in the DIB
        // color table.
        if (!pPalette)
            CreatePalette();
#endif // DIBSECTION_NO_PALETTE
   
        // Need to copy the supplied bitmap onto the newly created DIBsection
        HDC memDC, CopyDC;
        if (!(CopyDC=CreateCompatibleDC(hdc)) || !(memDC=CreateCompatibleDC(hdc))) 
        {
            error("Unable to create compatible DC's\n");
            
        }

#ifndef DIBSECTION_NO_PALETTE
        if (m_Palette)
        {
            SelectPalette(memDC,m_Palette, FALSE);  RealizePalette(memDC);
            SelectPalette(CopyDC,m_Palette, FALSE); RealizePalette(CopyDC);
        }
#endif // DIBSECTION_NO_PALETTE

#ifndef _WIN32_WCE
        // Flush the GDI batch queue 
        GdiFlush();
#endif

        HBITMAP hOldMemBitmap  = (HBITMAP) SelectObject(memDC,  hBitmap);
        HBITMAP hOldCopyBitmap = (HBITMAP) SelectObject(CopyDC, m_hBitmap);

        BitBlt(CopyDC,0,0, bm.bmWidth, bm.bmHeight, memDC, 0,0, SRCCOPY);

        SelectObject(memDC, hOldMemBitmap);
        SelectObject(CopyDC, hOldCopyBitmap);

#ifndef DIBSECTION_NO_PALETTE
        if (m_Palette)
        {
            ::SelectObject(memDC,GetStockObject(DEFAULT_PALETTE));
            ::SelectObject(CopyDC,GetStockObject(DEFAULT_PALETTE));
        }
#endif // DIBSECTION_NO_PALETTE
    }
    catch (char *s)
    {
#ifndef DIBSECTION_NO_PALETTE
        if (pOldPalette)
            SelectPalette(hdc,*pOldPalette, FALSE);
 #endif // DIBSECTION_NO_PALETTE
        DeleteObject();
        return FALSE;
    }

    return TRUE;
}

// --- In  : hdc     - the Device Context in which the DIBSection is selected
//           hBitmap - the bitmap whose solor entries are to be queried
//           lpbi    - a pointer to a BITMAPINFO structure that will have it's
//                     color table filled.
// --- Out :
// --- Returns : the number of colors placed in the color table
// --- Effect : This function is a replacement for GetDIBits, in that it retrieves 
//              (or synthesizes) the color table from the given bitmap, and stores 
//              the values in the BITMAPINFO structure supplied.
UINT CImagex::GetColorTableEntries(HDC hdc, HBITMAP hBitmap)
{
#ifndef _WIN32_WCE

    // Call GetDIBits with NULL bits pointer to fill in the BITMAPINFOHEADER data
    // Basically we are just getting the color table entries with a minimum of
    // effort
    if (!::GetDIBits(hdc, hBitmap, 0, GetHeight(), NULL, m_DIBinfo, m_iColorDataType))
    {
        error("Unable to GetDIBits\n");
        //AfxThrowResourceException();
    }
    
    // If the driver did not fill in the biSizeImage field, then compute it
    // Each scan line of the image is aligned on a DWORD (32bit) boundary
    if (m_DIBinfo.bmiHeader.biSizeImage == 0)
        m_DIBinfo.bmiHeader.biSizeImage = BytesPerLine(m_DIBinfo.bmiHeader.biWidth, 
                                                       m_DIBinfo.bmiHeader.biBitCount) 
                                            * m_DIBinfo.bmiHeader.biHeight;

    return m_iColorTableSize;

#else

    if (!m_iColorTableSize)
        return 0;

    // Fill the color table with the colors from the bitmap's color table
    LPRGBQUAD pColorTable = GetColorTable();
    
#ifdef _WIN32_WCE
    //DCR 4/02/01  If you are dealing with a 16bpp bitmap in PocketPC, you must
    // set the 3 DWORD color mask. This mask will be applied to a 16bit value to find the 
    // RGB components.  Blue is lowest 5 bits, then Green, then Red.
    if (m_DIBinfo.bmiHeader.biBitCount == 16)
    {
        DWORD dw[3];
        dw[0] = 31744;  //RED bitmask  Bits: 0 11111 00000 00000
        dw[1] = 992;    //GREEN bitmask Bits:0 00000 11111 00000
        dw[2] = 31;     //BLUE bitmask  Bits:0 00000 00000 11111
        memcpy(pColorTable, dw, 3*sizeof(DWORD));

        return 3;
    }
#endif

    // Get the color table from the HBITMAP and copy them over.
    UINT nCount;
    RGBQUAD* pRGB = new RGBQUAD[m_iColorTableSize];
    if (pRGB)
    {
        HBITMAP hOldBitmap = (HBITMAP) SelectObject(hdc, hBitmap);
        nCount = CEGetDIBColorTable(hdc, 0, m_iColorTableSize, pRGB);
        SelectObject(hdc, hOldBitmap);
        if (nCount)
        {
            // m_iColorTableSize = nCount;
            memcpy(pColorTable, pRGB, nCount*sizeof(RGBQUAD));
        }
    }
    delete [] pRGB;

    // Didn't work - so synthesize one.
    if (!nCount)
    {       
        nCount = min( m_iColorTableSize, sizeof(ms_StdColors) / sizeof(ms_StdColors[0]) );
        memcpy(pColorTable, ms_StdColors, nCount*sizeof(RGBQUAD));
    }

    return nCount;
#endif
}

// --- In  : pPalette - new palette to use
// --- Out :
// --- Returns : TRUE on success
// --- Effect : Sets the current palette used by the image from the supplied CPalette,
//              and sets the color table in the DIBSection
BOOL CImagex::SetPalette(HPALETTE* pPalette)
{
    ::DeleteObject(m_Palette);

    if (!pPalette)
        return FALSE;

    UINT nColors = GetPaletteEntries(NULL,0,0,NULL);
    if (nColors <= 0 || nColors > 256)
        return FALSE;

    // Get palette entries
    PALETTEINFO pi;
    pi.palNumEntries = (WORD) ::GetPaletteEntries(*pPalette,0, nColors, (LPPALETTEENTRY) pi);
                          
    return SetLogPalette(&pi);
}

// --- In  : pLogPalette - new palette to use
// --- Out :
// --- Returns : TRUE on success
// --- Effect : Sets the current palette used by the image from the supplied LOGPALETTE
BOOL CImagex::SetLogPalette(LOGPALETTE* pLogPalette)
{
    if (!pLogPalette)
    {
        CreatePalette();
        return FALSE;
    }

//    ASSERT(pLogPalette->palVersion == (WORD) 0x300);

    UINT nColors = pLogPalette->palNumEntries;
    if (nColors <= 0 || nColors > 256)
    {
        CreatePalette();
        return FALSE;
    }

    // Create new palette
    ::DeleteObject(m_Palette);
    if (!(m_Palette=::CreatePalette(pLogPalette)))
    {
        CreatePalette();
        return FALSE;
    }

    if (m_iColorTableSize == 0)
        return TRUE;

    // Set the DIB colors
    RGBQUAD RGBquads[256]; 
    for (UINT i = 0; i < nColors; i++)
    {
        RGBquads[i].rgbRed   = pLogPalette->palPalEntry[i].peRed;
        RGBquads[i].rgbGreen = pLogPalette->palPalEntry[i].peGreen;
        RGBquads[i].rgbBlue  = pLogPalette->palPalEntry[i].peBlue;
        RGBquads[i].rgbReserved = 0;
    }
    
    return FillDIBColorTable(nColors, RGBquads);
}

// --- In  : nNumColors - number of colors to set
//           pRGB - colors to fill
// --- Out :
// --- Returns : Returns TRUE on success
// --- Effect : Sets the colors used by the image. Only works if # colors <= 256
BOOL CImagex::FillDIBColorTable(UINT nNumColors, RGBQUAD *pRGB)
{
    if (!pRGB || !nNumColors || !m_iColorTableSize || nNumColors > 256)
        return FALSE;

    // get the number of colors to return per BITMAPINFOHEADER docs
    UINT nColors;
    LPBITMAPINFOHEADER pBmih = GetBitmapInfoHeader();
    if (pBmih->biClrUsed)
        nColors = pBmih->biClrUsed;
    else
        nColors = 1 << (pBmih->biBitCount*pBmih->biPlanes);

    // Initialize the loop variables
    nColors = min(nNumColors, nColors);

    LPRGBQUAD pColorTable = GetColorTable();
    for (UINT iColor = 0; iColor < nColors; iColor++)
    {
        pColorTable[iColor].rgbReserved = 0;
        pColorTable[iColor].rgbBlue     = pRGB[iColor].rgbBlue;
        pColorTable[iColor].rgbRed      = pRGB[iColor].rgbRed;
        pColorTable[iColor].rgbGreen    = pRGB[iColor].rgbGreen;
    }

    return TRUE;
}

BYTE* CImagex::ConvertRGB()
{
 	//
	// Allocate memory for new DIB section. 
	// No color table is needed.
	//
	const int BITMAPINFOHEADER_SIZE = sizeof(BITMAPINFOHEADER) ;
	BYTE* abBitmapInfo[BITMAPINFOHEADER_SIZE] ;
    BITMAPINFOHEADER* pBMIH = (BITMAPINFOHEADER*)abBitmapInfo;
    memset(pBMIH, 0, BITMAPINFOHEADER_SIZE);

    // fill in the header info 
    pBMIH->biSize 			= sizeof(BITMAPINFOHEADER);
    pBMIH->biWidth 			= m_iWidth;
    pBMIH->biHeight 		= m_iHeight;
    pBMIH->biPlanes 		= 1;
    pBMIH->biBitCount 		= 32 ; // Use 32 bpp to avoid boundary alignment issues.
    pBMIH->biCompression  	= BI_RGB ; 

	//
	// Create the new 32 bpp DIB section.
	//
    HDC dc;
    dc=CreateCompatibleDC(NULL);
	BYTE* pBits ;
    HBITMAP hbmBuffer = CreateDIBSection(dc,
                                   (BITMAPINFO*)pBMIH,
                                   DIB_RGB_COLORS,
                                   (VOID **) &pBits,
                                   NULL,
                                   0);
	// Select DIB into DC.
    HBITMAP hbmOld = (HBITMAP)::SelectObject(dc, hbmBuffer);
   
	// Blt the Windows DIB into our new DIB    
//   	SelectPalette(dc,&aPalSrc,0) ;
	RealizePalette(dc) ;
	::SetDIBColorTable(dc,0,m_iColorTableSize,GetColorTable());
	::SetDIBits(dc,hbmBuffer,0,GetImageSize(),GetDIBits(),GetBitmapInfo(),DIB_RGB_COLORS);
//	Draw(&dc,0,0) ;
   	GdiFlush() ;

	//
	// Copy the bits out of the DIB Section. 
	// Change from 32 bpp BGR to 24 bpp RGB.
	//
	int iImageSize = m_iWidth * m_iHeight * sizeof(CGLRGBTRIPLE) ;
	BYTE* m_pBits = (BYTE*)malloc(iImageSize) ;

	RGBQUAD* pSrc = (RGBQUAD*)pBits ;
	CGLRGBTRIPLE* pDest = (CGLRGBTRIPLE*) m_pBits ;
	for (int i = 0 ; i < m_iWidth*m_iHeight ; i++)
	{
		pDest->rgbRed = pSrc->rgbRed ;
		pDest->rgbGreen = pSrc->rgbGreen ;
		pDest->rgbBlue = pSrc->rgbBlue ;
		pDest++ ;
		pSrc++ ;
	}

	//
	// Get rid of all the GDI stuff.
	//
    if (hbmOld)
        (HBITMAP)::SelectObject(dc, hbmOld);

	::DeleteObject(hbmBuffer) ;
	return m_pBits;

}

