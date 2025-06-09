// EncryptSafeNet.h: interface for the CEncryptSafeNet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_EncryptSafeNet_H__)
#define _EncryptSafeNet_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\EncryptTool.h"

#ifdef use_Encrypt_SafeNetTool
#pragma comment(lib,"spromeps.lib")

class CEncryptSafeNet : public CEncryptTool
{
public:
	CEncryptSafeNet();
	virtual ~CEncryptSafeNet();

public:
	virtual void    OpenLocalEncryptFile();
	virtual BOOL IsEncrypt();

protected:
	BOOL m_bSafeNetCheck;
	void CheckDogState();
};


inline void Encrypt_RegisterSafeNetTool()
{
	Encrypt_RegisterTool(new CEncryptSafeNet());
}

#endif

#endif // !defined(_EncryptSafeNet_H__)
