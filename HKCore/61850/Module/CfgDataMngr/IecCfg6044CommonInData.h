//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgData6044.h  CIecCfgData6044

#pragma once

#include "IecCfg6044CommonData.h"

class CIecCfg6044CommonInData : public CIecCfg6044CommonData
{
public:
	CIecCfg6044CommonInData();
	virtual ~CIecCfg6044CommonInData();

//重载函数
public:
	virtual UINT GetClassID() {    return CFGCLASSID_CIECCFG6044COMMONINDATA;   }
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CIecCfgData6044CommonInKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual void InitAfterRead();
	virtual CString GetCfgDefaultConfigFile()	{	return _T("Cfg6044CommonIn.xml");	}

//私有成员变量
private:

//私有成员变量访问方法
public:
	virtual CString GetCfgDataName(long nIndex)
	{
		CString strName;
		strName.Format(_T("6044-8-CommonIn(%d)"), nIndex);
		return strName;
	}
	virtual CString GetCfgDataShortName(long nIndex)
	{
		CString strName;
		strName.Format(_T("FT3CommonIn第%d组"), nIndex+1);
		return strName;
	}

	long GetPkgLength();//suyang 20240822 增加获取crc为1（末尾校验）时的通道长度，下发给底层

};

