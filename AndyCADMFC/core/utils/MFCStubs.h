#ifndef MFC_STUBS_H
#define MFC_STUBS_H

#include <string>
#include <iostream>
#include <vector>

// using namespace std;

class CString : public std::string {
public:
    CString() {}
    CString(const char* s) : std::string(s) {}
    CString(const std::string& s) : std::string(s) {}
    void Format(const char* fmt, ...) {}
    const char* GetBuffer(int nMinBufLength) { return c_str(); }
    operator const char*() const { return c_str(); }
};
#ifndef _T
#define _T(x) x
#endif
//typedef std::string CString;
typedef int LONG;
typedef unsigned int UINT;
typedef unsigned char BYTE;
typedef void* LPVOID;
typedef const char* LPCTSTR;
typedef void* HDC;
typedef int32_t COLORREF;
#define PS_GEOMETRIC 0x00010000
#define PS_SOLID 0
#define R2_NOTXORPEN 7
typedef struct tagPOINT {
    LONG x;
    LONG y;
} POINT, *PPOINT, *NPPOINT, *LPPOINT;

typedef unsigned int DWORD;
typedef struct tagLOGBRUSH {
    UINT lbStyle;
    COLORREF lbColor;
    LONG lbHatch;
} LOGBRUSH, *PLOGBRUSH;

class CPen {
public:
    CPen() {}
    void CreatePen(int style, int width, COLORREF color) {}
    void CreatePen(int style, int width, const LOGBRUSH* lb, DWORD styleCount, const DWORD* lpStyle) {}
};

class CBrush {
public:
    CBrush() {}
    void CreateSolidBrush(COLORREF color) {}
};

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

#ifndef PI_DEF
#define PI_DEF
const double pi = 3.14159265358979323846;
#endif

class CFile {
public:
    CFile() {}
    virtual ~CFile() {}
    enum OpenFlags {
        modeRead = 0x0000,
        modeWrite = 0x0001,
        modeReadWrite = 0x0002
    };
    enum SeekPosition { begin = 0x0, current = 0x1, end = 0x2 };

    virtual LONG Seek(LONG lOff, UINT nFrom) { return 0; }
    virtual UINT Read(void* lpBuf, UINT nCount) { return 0; }
    virtual void Write(const void* lpBuf, UINT nCount) {}
    virtual void Save(CFile &file){}; // Stub
    virtual void Close() {}
};

inline void LPtoDP(HDC hdc, LPPOINT lpPoints, int nCount) {}
struct CPoint;
inline void LPtoDP(HDC hdc, CPoint* lpPoints, int nCount) {}

class CStdioFile : public CFile {
public:
    CStdioFile() {}
    void WriteString(LPCTSTR lpsz) {}
    void WriteString(const std::string& s) {}
};

class CArchive {
public:
    bool IsStoring() { return false; }
    CArchive& operator<<(int i) { return *this; }
    CArchive& operator>>(int& i) { return *this; }
};
#define CArchive_DEFINED

#endif // MFC_STUBS_H
