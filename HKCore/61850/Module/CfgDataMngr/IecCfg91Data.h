//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//IecCfgData91.h  CIecCfgData91

#pragma once

#include "IecCfgDataMngrGlobal.h"

#include "IecCfgSmvDataBase.h"

#include "IecCfg91StatusDataSet.h"
#include "IecCfg91Chs.h"

class CIecCfg91Data : public CIecCfgSmvDataBase
{
public:
	CIecCfg91Data();
	virtual ~CIecCfg91Data();


	CString  m_strDestAddress;
	CString  m_strSrcAddress;
	DWORD  m_dwAppID;
	long  m_nPriority;
	DWORD  m_dwVID;
	DWORD  m_dwVersion;
	DWORD  m_dwDataSet;
	DWORD  m_dwLNName;
	DWORD  m_dwLDName;
	DWORD  m_dwStateWord;
	long  m_nUseStateWord;
	long  m_nUseStateDataSet;

// 	DWORD  m_dwINomPh;
// 	DWORD  m_dwUNomPh;
// 	DWORD  m_dwINomNeutral;
	DWORD  m_dwDelayTime;

	CIecCfg91StatusDataSet *m_pStatusDataSet;


	//2020-6-29 lijunqing ���ӵ㳤�ȣ����ַ���ת����ʱ������ڴ����
	BYTE m_byteDestAddress[10];
	BYTE m_byteSrcAddresss[10];

//���غ���
public:
	virtual UINT GetClassID() {    return CFGCLASSID_CIECCFG91DATA;   }
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CIecCfgData91Key();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual void InitAfterRead();
	virtual CString GetCfgDefaultConfigFile()	{	return _T("Cfg91.xml");	}

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
	CIecCfg91StatusDataSet* GetStatusDataSet();

	virtual CString GetCfgDataName(long nIndex)
	{
		CString strName;
        strName.Format(_T("9-1(%d): %s"), nIndex, m_strDestAddress.GetString());
		return strName;
	}
	virtual CString GetCfgDataShortName(long nIndex)
	{
		CString strName;
		strName.Format(_T("9-1��%d��"), nIndex+1);
		return strName;
	}

#ifdef _PSX_IDE_QT_
	virtual BOOL SetCfgDataValue(long nDataID, unsigned long long &vValue);
	virtual BOOL GetCfgDataValue(long nDataID, unsigned long long &vValue);
	virtual BOOL IsEqualCfgDataValue(long nDataID, unsigned long long &vValue);
#else
	virtual BOOL SetCfgDataValue(long nDataID, VARIANT &vValue);
	virtual BOOL GetCfgDataValue(long nDataID, VARIANT &vValue);
	virtual BOOL IsEqualCfgDataValue(long nDataID, VARIANT &vValue);
#endif
};

