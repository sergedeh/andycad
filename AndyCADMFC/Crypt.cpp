// Crypt.cpp: implementation of the CCrypt class.
//
//////////////////////////////////////////////////////////////////////

#include "pch.h"
#include "Crypt.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCrypt::~CCrypt()
{

}
CCrypt::CCrypt()
{
 m_hProv= m_hHash= m_hKey= 0;
 m_pszDefaultKeyRaw= "fdC)Y%yum3ww09";
}
BOOL CCrypt::SetKey( LPCSTR szKey, LPCSTR szSalt/*=0*/ ) 
{
m_fOK= TRUE;
if ( 0 == m_hProv ) {
    m_fOK= CryptAcquireContext( &m_hProv, NULL,
        MS_DEF_PROV,
        PROV_RSA_FULL,
        CRYPT_VERIFYCONTEXT
    );
}
if (m_fOK && (0 != m_hHash)) {
}