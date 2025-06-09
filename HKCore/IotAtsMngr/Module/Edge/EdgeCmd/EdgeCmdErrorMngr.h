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

	//����EdgeCmd,��Ϊ���Ѿ��̳�һ����,��̳�ʱʹ�ø���ָ���޷���ȡ�����ڵĳ�Ա
	static void AddErrorInfo(const BSTR strCodeKey, CXmlRWNodeBase &oNode, long nValType, CString& strErrorInfo);
	//���ڲ��ֽڵ���ֱ�Ӵӱ����json�����з���������,������EDGE��,������Ҫ�ⲿ����
	static void AddErrorInfo(CJSON* pJson, long nValType, CString& strErrorInfo);
	static void CheckIsError(CJSON* pJson, CString& strErrorInfo);

public:
	CString m_strErrorInfo;//���ڴ��GetXml����ֵĴ���,�����ڱ��豸��Ŀ

	CString GetCmdErrorInfo() { return m_strErrorInfo; }
	void AddCmdErrorInfo(const CString& strErrorInfo) { m_strErrorInfo += strErrorInfo; }
	void ClearCmdErrorInfo() { m_strErrorInfo = _T(""); }

	void CheckIsError(CJSON* pJson);
};
