#pragma once

#include "../SttCmd/SttCmdDefineGlobal.h"
#include "SttXmlSerializeBase.h"

class CSttXmlSerializeTool : CExBaseList
{
public:
	CSttXmlSerializeTool();
	virtual ~CSttXmlSerializeTool();

	CXmlRWDocBase* GetXmlDoc()	{	return m_pRWDoc;	}
	
	CXmlRWElementBase* GetDocElelemt()		
	{
		if (m_pSttXmlSerialize != NULL)
		{
			return m_pSttXmlSerialize->GetElement();
		}
		else
		{
			return NULL;
		}
	}

public:
	//read
	CSttXmlSerializeBase* CreateXmlSerializeRead(CExBaseObject *pSttObj, const char *pszXmlBuffer, long nLen);
	CSttXmlSerializeBase* CreateXmlSerializeRead(BSTR bstrXmlRootKey, const CString &strFile);
	CSttXmlSerializeBase* CreateXmlSerializeRead(CExBaseObject *pSttObj, const CString &strFile);
	long SttXmlSerializeRead(CExBaseObject *pSttObj);
	CSttXmlSerializeBase* CreateXmlSerializeWrite(CExBaseObject *pSttObj);
	CSttXmlSerializeBase* CreateXmlSerializeRegister(CExBaseObject *pSttObj);

	//2021-5-30  lijunqing
	CSttXmlSerializeBase* CreateXmlSerializeWrite(BSTR bstrXmlRootKey);
	CSttXmlSerializeBase* CreateXmlSerializeRegister(BSTR bstrXmlRootKey);

	//2021-8-12  lijunqing
	CSttXmlSerializeBase* CreateXmlSerializeRead(const CString &strFile);
	CSttXmlSerializeBase* CreateXmlSerializeRead_String(const CString &strXML);
	CSttXmlSerializeBase* CreateXmlSerializeRead_String_UTF8(char *pszBuffer, long nLen);
	CSttXmlSerializeBase* CreateXmlSerializeWrite();
	CSttXmlSerializeBase* CreateXmlSerializeRegister();

	CSttXmlSerializeBase* GetCmdChild(BSTR bstrElementKey);
	CSttXmlSerializeBase* GetMacro();
	CSttXmlSerializeBase* GetMacroChild(BSTR bstrElementKey);
	CSttXmlSerializeBase* GetMacroParas();
	CSttXmlSerializeBase* GetMacroResults();
	CSttXmlSerializeBase* GetMacroSearchResults();//zhouhj 20210925 增加用于搜索类返回结果
	CSttXmlSerializeBase* GetParas();

	CString GetMacroID(BSTR bstrElementKey);

    long Stt_GetXml(char **ppszXmlBuffer, long nOffset);
	BOOL Stt_WriteFile(const CString &strFile);

public:
	void Release();
	BOOL is_serialize_mode_read();
	BOOL is_serialize_mode_write();
	BOOL is_serialize_mode_register();

protected:
	CXmlRWDocBase *m_pRWDoc;
	CSttXmlSerializeBase *m_pSttXmlSerialize;
};
