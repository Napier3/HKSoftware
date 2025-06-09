#pragma once

#include "EdgeCmdMngrGlobal.h"

class CEdgeCmdErrorMngr : public CExBaseList
{
public:
	CEdgeCmdErrorMngr(){}
	virtual ~CEdgeCmdErrorMngr(){}

public:
	virtual UINT GetClassID() { return EDGECMDCLASSID_CEDGEERRORMNGR; }


	void AddErrorInfo(CJSON* pJson, long nValType);
	void AddErrorInfo(const BSTR strCodeKey, CXmlRWNodeBase &oNode, long nValType);

	//用于EdgeCmd,因为其已经继承一个类,多继承时使用父类指针无法获取父类内的成员
	static void AddErrorInfo(const BSTR strCodeKey, CXmlRWNodeBase &oNode, long nValType, CString& strErrorInfo);
	//由于部分节点是直接从保存的json报文中分析创建的,不经过EDGE类,所以需要外部分析
	static void AddErrorInfo(CJSON* pJson, long nValType, CString& strErrorInfo);
	static void CheckIsError(CJSON* pJson, CString& strErrorInfo);

public:
	CString m_strErrorInfo;//用于存放GetXml会出现的错误,仅用于边设备项目

	CString GetCmdErrorInfo() { return m_strErrorInfo; }
	void AddCmdErrorInfo(const CString& strErrorInfo) { m_strErrorInfo += strErrorInfo; }
	void ClearCmdErrorInfo() { m_strErrorInfo = _T(""); }

	void CheckIsError(CJSON* pJson);
};
