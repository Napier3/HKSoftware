//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfg2MInData.h  IecCfg2MInData

#pragma once

#include "IecCfg2MData.h"


class CIecCfg2MInData : public CIecCfg2MData
{
public:
	CIecCfg2MInData();
	virtual ~CIecCfg2MInData();

//重载函数
public:
	virtual UINT GetClassID() {    return CFGCLASSID_CIECCFG2MINDATA;   }
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CIecCfgData2MInKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual void InitAfterRead();
	virtual CString GetCfgDefaultConfigFile()	{	return _T("Cfg2MIn.xml");	}

//私有成员变量
private:

//私有成员变量访问方法
public:
	virtual CString GetCfgDataName(long nIndex)
	{
		CString strName;
		strName.Format(_T("2MIn(%d)"), nIndex);
		return strName;
	}
	virtual CString GetCfgDataShortName(long nIndex)
	{
		CString strName;
		strName.Format(_T("2MIn第%d组"), nIndex+1);
		return strName;
	}

	virtual void GetCommData(CIecCfgDataSmvCommon *pCommon);
	virtual void InitByCommData(CIecCfgDataSmvCommon *pCommon);

};

