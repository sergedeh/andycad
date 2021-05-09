// Crypt.h: interface for the CCrypt class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CRYPT_H__BACFF3D4_1705_48C1_A2B7_23FC98A5F2D3__INCLUDED_)
#define AFX_CRYPT_H__BACFF3D4_1705_48C1_A2B7_23FC98A5F2D3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCrypt  
{
public:
    CCrypt();
    virtual ~CCrypt() {
        if ( m_hKey )  CryptDestroyKey( m_hKey ); 
        if ( m_hHash ) CryptDestroyHash( m_hHash ); 
        if ( m_hProv ) CryptReleaseContext( m_hProv, 0); 
    }
    BOOL SetKey( LPCSTR szKey= 0, LPCSTR pszSalt= 0 );

    BOOL EncryptDecrypt( BYTE* pData, DWORD* dwDataLen, LPCSTR pKey, BOOL fEncrypt );

    CString EncryptStrToHex(   LPCSTR szText, LPCSTR pKey= 0, LPCSTR pszSalt= 0 );
    CString DecryptStrFromHex( LPCSTR szHex,  LPCSTR pKey= 0, LPCSTR pszSalt= 0 );

    CString EncodeToHex(   BYTE* p, int nLen );
    int     DecodeFromHex( LPCSTR pSrc, BYTE* pDest, int nBufLen );

private:
    HCRYPTPROV  m_hProv;
    HCRYPTHASH  m_hHash;
    HCRYPTKEY   m_hKey;

    BOOL        m_fOK;
    DWORD       m_nLastErr;
    CString     m_sErrMsg;
    char*       m_pszDefaultKeyRaw;
};

#endif // !defined(AFX_CRYPT_H__BACFF3D4_1705_48C1_A2B7_23FC98A5F2D3__INCLUDED_)
