// Crypto1.h: interface for the CCrypto class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CRYPTO1_H__6BC2CBFC_6A5B_4972_B4C2_5872AB48EEE0__INCLUDED_)
#define AFX_CRYPTO1_H__6BC2CBFC_6A5B_4972_B4C2_5872AB48EEE0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//	Include the standard cryptography header.
#include <wincrypt.h>


	//	A simple class to wrap the Crypto API.
	class CCrypto
	{
	public:

		//	All of the Cryptography API initialisation is done in the 
		//	constructor, so constructing this object is expensive. I recommend having
		//	only one instance only, and keep it in your application class.
		CCrypto();
		virtual ~CCrypto();

		//	These functions are essential to using the crypto object- you must
		//	have a key from some source or other.

		//	Derive a key from a password.
		virtual bool DeriveKey(CString strPassword);

		//	These functions handle encryption and decryption.

		virtual bool Encrypt(const CObject& serializable, CByteArray& arData);
		virtual bool Decrypt(const CByteArray& arData, CObject& serializable);

		virtual bool Encrypt(const CString& str, CByteArray& arData);
		virtual bool Decrypt(const CByteArray& arData, CString& str);


	protected:

		//	Encrypt the contents of the memory file and store in the passed array.
		virtual bool InternalEncrypt(CByteArray& arDestination);

		//	Decrypt the contents of the passed array and store in the memory file.
		virtual bool InternalDecrypt(const CByteArray& arSource);

		//	Handle to the cryptography provider.
		HCRYPTPROV m_hCryptProv;
	
		//	Handle to the cryptography key.
		HCRYPTKEY m_hKey;

		//	Handle to the hash object.
		HCRYPTHASH m_hHash;

		//	Internally, the encryption and decryption of data is done with
		//	a CMemFile intermediate.
		CMemFile m_file;
	};
#endif // !defined(AFX_CRYPTO1_H__6BC2CBFC_6A5B_4972_B4C2_5872AB48EEE0__INCLUDED_)
