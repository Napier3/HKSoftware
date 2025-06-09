// EncryptBase.h: interface for the CEncryptBase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_EncryptBase_H__)
#define _EncryptBase_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../API/HexTransApi.h"
#include "../API/GlobalApi.h"
#include "../API/FileApi.h"
#include "SystemCode.h"


// #define _ATS_SAC

#ifdef _ATS_SAC

#define ENCRYPTFILE_FILTER      _T("ATSע���ļ�(*.atsreg)|*.atsreg||")
#define ENCRYPTFILE_POSTFIX     _T("atsreg")
#define ENCRYPTFILE_FILTER_M    _T("ATSע��������ļ�(*.atsregm)|*.atsregm||")
#define ENCRYPTFILE_POSTFIX_M   _T("atsregm")
#define ENCRYPTFILE_NAME        _T("Ats.atsreg")
#define ENCRYPTFILE_GEN_NAME    _T("AtsRegisterGen.atsreg")
#define ENCRYPTFILE_REGISTER    _T("AtsRegister.exe")
#define ENCRYPTREG_KEY_ROOT     _T("SmartTest")

#else

#define ENCRYPTFILE_FILTER      _T("ע���ļ�(*.itsrg)|*.itsrg||")
#define ENCRYPTFILE_POSTFIX     _T("itsrg")
#define ENCRYPTFILE_FILTER_M    _T("ע��������ļ�(*.itsrgm)|*.itsrgm||")
#define ENCRYPTFILE_POSTFIX_M   _T("itsrgm")
#define ENCRYPTFILE_NAME        _T("iTest.itsrg")
#define ENCRYPTFILE_GEN_NAME    _T("iTestRegGen.itsrg")
#define ENCRYPTFILE_REGISTER    _T("iTestRegister.exe")
#define ENCRYPTREG_KEY_ROOT     _T("iTest")

#endif

#define ENCRYPTREG_VALUE_TIME          _T("Value1")
#define ENCRYPTREG_VALUE_DAYS          _T("Value2")
#define ENCRYPTREG_KEY                 _T("Register")

#define ENCRYPT_VERSION_1_0    0X00010000

////���Ӹ������Ȩ��
#define ENCRYPT_VERSION_1_1    0X00010001   

//MAC��ַ�����õ�����ַ�ж�
#define ENCRYPT_VERSION_1_2    0X00010002   

//���Ӹ�����û���Ϣ
#define ENCRYPT_VERSION_1_3    0X00010003   

//���ӣ�ע���ʱ�䣬ע�����Ϣ�ۺ��ж�
#define ENCRYPT_VERSION_1_4    0X00010004  

//���Ӱ�Ȩ
#define ENCRYPT_VERSION_1_5    0X00010005  

static DWORD g_dwEncryptCurrVersion = ENCRYPT_VERSION_1_5;

class CEncryptCode : public CExBaseObject
{
public:
	CEncryptCode();
	virtual ~CEncryptCode();

public:
	CString m_strCpu;
	CString m_strHdCode;
	CString m_strMac;
	CString m_strRegCode;
	CString m_strSN;

public:
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);

};

class CEncryptBase : public CExBaseList
{
public:
	CEncryptBase();
	virtual ~CEncryptBase();

//���Զ���
protected:
	CString m_strSysName;  //2021-7-30   lijunqing
	CString m_strOwnership;             //���֪ʶ��Ȩ����
	CString m_strDev;             //���֪ʶ��Ȩ����
	CString m_strUserName;        //��Ȩ�û���
	long    m_nMaxUseCount;       //���ʹ�ô���
	DWORD   m_nCurrUseCount;      //��ǰʹ�ô���
	CString m_strSN;              //���к�

	CString m_strDevCode;      //�Ƿ񿪷���MAC
	DWORD   m_dwDevStudio;     //Devƽ̨������Ȩ
	DWORD   m_dwAutoTest;      //AutoTest������Ȩ
	DWORD   m_dwUseDog;        //�Ƿ�ʹ��Ӳ�����ܹ�
	CString m_strUserCop;      //��Ȩ�û���λ
	CString m_strUserCode;     //��Ȩ�û�����
	CString   m_strMode;		//Demoe,Release,Debug
	CString m_strDemoTemplate[4];        //�Ƿ�Demo�汾

	BOOL m_bIsDevCode;
	DWORD m_dwTime;

	BOOL m_bRegistered;
	CExBaseList m_olistEncryptCode;

	//2023-4-27  lijunqing
	CString m_strUseTimeLong; //ʹ����ʱ��
	CString m_strTimeUsed;
protected:
	CString GetEncryptFile();

public:
	virtual long Serialize(CBinarySerialBuffer &oBinaryBuffer);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);

	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	CEncryptCode* FindCode(CEncryptCode *pCode);
	CEncryptCode* FindCodeSN(CEncryptCode *pCode);
	CEncryptCode* FindSN(const CString &strSN);

public:
	CString CodeString(const CString &strText);
	CString DisCodeString(const CString &strText);
	CString GetRegisterCode(const CString &strMachine);
	CString GetRegisterCodeEx(const CString &strMachine);
	CString GetMachineCode();
	CString CalMachineCode();
	CString GetMachineCodeEx();
	CString GetMachineCode(CEncryptCode *pCode);

	CString GetMode()		{	return DisCodeString(m_strMode);	}
	CString GetSysName()		{	return DisCodeString(m_strSysName);	}
	CString GetOwnership()		{	return DisCodeString(m_strOwnership);	}
	CString GetDev()		{	return DisCodeString(m_strDev);	}
	CString GetUser()			{	return DisCodeString(m_strUserName);		}
	long    GetMaxUseCount()	{	return m_nMaxUseCount;	}
	long    GetCurrUseCount()	{	return m_nCurrUseCount;	}
	CString GetSN()				{	return DisCodeString(m_strSN);			}
	CString GetSNEx();
	CString GetSN(const CString &strSN)				{	return DisCodeString(strSN);			}
	BOOL    IsDevCode()			{	return m_bIsDevCode;	}
	DWORD   GetUseDog()			{	return m_dwUseDog;	}
	CString GetUserCop()				{	return DisCodeString(m_strUserCop);			}
	CString GetUserCode()				{	return DisCodeString(m_strUserCode);			}
	BOOL    IsDemo();
	BOOL    CanUseTemplate(const CString &strTempate);

	void OpenEncryptFile();
	void OpenEncryptFile(const CString &strFile);
	BOOL OpenEncryptFile(CWnd *pParent, CString &strFile);
	BOOL OpenEncryptCodeFile(CWnd *pParent, CString &strFile);
	void SaveEncryptFile(const CString &strFile);
	void SaveEncryptFile(CWnd *pParent, const CString &strName);
	void SaveEncryptCodeFile(CWnd *pParent, const CString &strCode);
	void SaveEncryptFile();
	void SaveEncryptReg();
	BOOL CanRegister();
	void InitCurrTime();

	void SetMode(const CString &strMode)			{	m_strMode = CodeString(strMode);	}
	void SetDev(const CString &strCompany)		{	m_strDev = CodeString(strCompany);	}
	void SetSysName(const CString &strSysName)		{	m_strSysName = CodeString(strSysName);	}
	void SetOwnership(const CString &strOwnership)		{	m_strOwnership = CodeString(strOwnership);	}
	void SetUser(const CString &strUser)			{	m_strUserName = CodeString(strUser);		}
	void SetMaxUseCount(long nCount)				{	m_nMaxUseCount = nCount;	}
	void SetCurrUseCount(long nCount)				{	m_nCurrUseCount = nCount;	}
	void SetSN(const CString &strSN)				{	m_strSN = CodeString(strSN);			}
	void SetSNEx(const CString &strSN);
	void SetUseDog(long nUseDog)				    {	m_dwUseDog = nUseDog;	}
	void SetUserCop(const CString &str)				{	m_strUserCop = CodeString(str);	}
	void SetUserCode(const CString &str)			{	m_strUserCode = CodeString(str);		}
	void SetDemoTemplate(const CString &str, long nIndex);;

	void SetUseTimeLong(long nValue);
	void SetTimeUsed(long nValue);
	long GetUseTimeLong();
	long GetTimeUsed();

public:
	virtual BOOL IsEncrypt();
	virtual BOOL IsEncrypt(CEncryptCode *pCode);
	virtual BOOL CanUseAutoTest();
	virtual BOOL CanUseDevStudio();

	//2023-4-27  lijunqing
	virtual void IncreaseTimeUse(long nTimeAdd);
	
};


CString Encrypt_GetEncryptFile();
CString Encrypt_GetEncryptRegister();


#endif // !defined(_EncryptBase_H__)
