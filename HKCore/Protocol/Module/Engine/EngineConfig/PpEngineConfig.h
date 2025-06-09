//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//PpEngineConfig.h  CPpEngineConfig

#pragma once

#include "PpEngineConfigGlobal.h"


class CPpEngineConfig : public CExBaseList
{
public:
	CPpEngineConfig();
	virtual ~CPpEngineConfig();

	long m_nDebugMode;
	long m_nLogDataBind;
	long m_nLogPkgInfor;
	long m_nLogPkg;
	long m_nLogDebugInfor;
	long m_nNoChangeWhenSame;

//重载函数
public:
	virtual UINT GetClassID() {    return MSCFGCLASSID_CPPENGINECONFIG;   }
	virtual BSTR GetXmlElementKey()  {      return CPpEngineConfigXmlRWKeys::CPpEngineConfigKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual CBaseObject* Clone();
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	virtual void InitAfterRead();

//私有成员变量
private:
	CString GetPpEngineConfigFile();

//私有成员变量访问方法
public:
	void ReadPpEngineConfig();
	void SavePpEngineConfig();
};

