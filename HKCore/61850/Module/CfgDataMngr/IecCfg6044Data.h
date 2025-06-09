//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgData6044.h  CIecCfgData6044

#pragma once

#include "IecCfgDataMngrGlobal.h"

#include "IecCfgSmvDataBase.h"

#include "IecCfg6044Chs.h"

class CIecCfg6044Data : public CIecCfgSmvDataBase
{
public:
	CIecCfg6044Data();
	virtual ~CIecCfg6044Data();


	DWORD  m_dwLDName;
	DWORD  m_dwLNName;
	DWORD  m_dwDataSetName;
	long   m_dwDelayTime;
	DWORD  m_dwTransSpeed;
	DWORD  m_dwStateWord;
// 	DWORD  m_dwINomPh;
// 	DWORD  m_dwUNomPh;
// 	DWORD  m_dwINomNeutral;
	long   m_nCheckSum;
	long   m_nPolarity;

//重载函数
public:
	virtual UINT GetClassID() {    return CFGCLASSID_CIECCFG6044DATA;   }
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CIecCfgData6044Key();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual void InitAfterRead();
	virtual CString GetCfgDefaultConfigFile()	{	return _T("Cfg6044.xml");	}

//私有成员变量
private:

//私有成员变量访问方法
public:
	virtual CString GetCfgDataName(long nIndex)
	{
		CString strName;
		strName.Format(_T("6044-8(%d)"), nIndex);
		return strName;
	}
	virtual CString GetCfgDataShortName(long nIndex)
	{
		CString strName;
		strName.Format(_T("FT3第%d组"), nIndex+1);
		return strName;
	}

	BYTE GetSpeed()
	{
		if (0 <= m_dwTransSpeed && m_dwTransSpeed <= 2)
		{
			return (BYTE)m_dwTransSpeed;
		}
		else
		{
			return 1;
		}
	}
	BYTE GetChecksum()
	{
		if (0 <= m_nCheckSum && m_nCheckSum <= 1)
		{
			return (BYTE)m_nCheckSum;
		}
		else
		{
			return 0;
		}
	}
	BYTE GetPolarity()
	{
		if (0 <= m_nPolarity && m_nPolarity <= 1)
		{
			return (BYTE)m_nPolarity;
		}
		else
		{
			return 0;
		}
	}

#ifdef _PSX_IDE_QT_
	virtual BOOL SetCfgDataValue(long nDataID, unsigned long long &vValuee);
	virtual BOOL GetCfgDataValue(long nDataID, unsigned long long &vValue);
	virtual BOOL IsEqualCfgDataValue(long nDataID, unsigned long long &vValue);
#else
	virtual BOOL SetCfgDataValue(long nDataID, VARIANT &vValuee);
	virtual BOOL GetCfgDataValue(long nDataID, VARIANT &vValue);
	virtual BOOL IsEqualCfgDataValue(long nDataID, VARIANT &vValue);
#endif

};

