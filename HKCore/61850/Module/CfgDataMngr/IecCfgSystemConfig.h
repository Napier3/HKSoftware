//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgSystemConfig.h  CIecCfgSystemConfig

#pragma once

#include "IecCfgDataMngrGlobal.h"



class CIecCfgSystemConfig : public CExBaseObject
{
public:
	CIecCfgSystemConfig();
	virtual ~CIecCfgSystemConfig();


	CString  m_strDefaultCfgFile;
	CString  m_strLaIecCfgFile;
	CString  m_strUseDebug;
	CString  m_strAutoSetUIChIndex;
	
	BOOL m_bAutoSetUIChIndex;

	static const CString g_strIecCfgSystemConfigFile;

//重载函数
public:
	virtual UINT GetClassID() {    return CFGCLASSID_CIECCFGSYSTEMCONFIG;   }
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CIecCfgSystemConfigKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

//私有成员变量
private:
	void InitAutoSetUIChIndex()
	{
		m_bAutoSetUIChIndex = (m_strAutoSetUIChIndex != _T("manual"));
	}

//私有成员变量访问方法
public:
	long Save();
	long Open();

	CString GetInitFile();
	CString GetLastFile();
	void SetLaIecCfgFile(const CString &strFile);
	void SetAutoSetUIChIndex(BOOL b)
	{
		m_bAutoSetUIChIndex = b;
		if (m_bAutoSetUIChIndex)
		{
			m_strAutoSetUIChIndex = _T("auto");
		}
		else
		{
			m_strAutoSetUIChIndex = _T("manual");
		}
		Save();
	}

	BOOL GetAutoSetUIChIndex()
	{
		return m_bAutoSetUIChIndex;
	}
};

