#pragma once

#include "IecCfgDataMngrGlobal.h"

#include "IecCfgSmvDataBase.h"

#include "IecCfg92Chs.h"
#include "IecCfg92ChQuality.h"

typedef CTLinkListEx<CIecCfg92ChQuality>  CIecCfg92ChQualityList;

class CIecCfg92InputData : public CIecCfgDataBase
{
public:
	CIecCfg92InputData();
	virtual ~CIecCfg92InputData();

	CString m_strSVID;


//重载函数
public:
	virtual UINT GetClassID() {    return CFGCLASSID_CIECCFG92INPUTDATA;   }
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CIecCfgData92InKey();     }

	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);


	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual void InitAfterRead();

	virtual CString GetCfgDefaultConfigFile()	{	return _T("Cfg92Input.xml");	}
	virtual BOOL OpenCfgDefaultConfigFile();

//私有成员变量
private:

//私有成员变量访问方法
public:
	void GetQualityList(CIecCfg92ChQualityList *pList);

	virtual CString GetCfgDataName(long nIndex)
	{
		CString strName;
//		strName.Format(_T("9-2(%d): %s"), nIndex, m_strDestAddress);
		return strName;
	}
	virtual CString GetCfgDataShortName(long nIndex)
	{
		CString strName;
		strName.Format(_T("9-2第%d组"), nIndex+1);
		return strName;
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

