#pragma once

#include "GbWzdCmd.h"

//模板属性

class CGbWzdCmdGbAttr : public CGbWzdCmd
{
public:
	CGbWzdCmdGbAttr();
	virtual ~CGbWzdCmdGbAttr();

	virtual UINT GetClassID()			{		return GBWZDCLASSID_GBATTR;	} 
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BSTR GetXmlElementKey() ;

	virtual BOOL IsEqual(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDesObj);
	virtual CBaseObject* Clone();


	virtual BOOL IsCmdFinish();

	void InitByGuideBook(CGuideBook *pGuideBook);
	void InitGuideBook(CGuideBook *pGuideBook);

public:
	CString m_strGbName;
	CString m_strGbID;
	CString m_strDevBy;
	CString m_strVersion;
	CString m_strPpTemplateFile;      //规约模板文件
	CString m_strCommCmdConfigFile;		//通讯配置文件
	CString m_strScriptMngrFile;
	CString m_strTestMacroFile;
	CString m_strTestTypeFile;
	CString m_strPpEngineProgID;
	CString m_strDvmFile;

	CString m_strDeviceModelFile;		//点表文件
	CString m_strDevID;
	CString m_strStandNameFile;

public:
	virtual BOOL Execute(DWORD dwExecMode);
	virtual void GetCmdInfor(CString &strText);
	long m_nGbWzdCmdGbAttrIndex;


};