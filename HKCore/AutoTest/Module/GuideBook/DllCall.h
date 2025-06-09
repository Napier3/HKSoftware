#pragma once

#include "../../../Module/BaseClass/ExBaseList.h"
#include "gbxmlkeys.h"
#include "GuideBookDefine.h"

#include "GbParaTypeMngr.h"

class CDllCall : public CExBaseObject
{
public:
	CDllCall();
	virtual ~CDllCall();

	static const CString g_strDllPathSubID;
	static const CString g_strDllFilePostfix;
	
public:
	virtual UINT GetClassID()		{		return GBCLASSID_DLLCALL;			}

	//ReadXML
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);

	//WriteXML
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElemen, CXmlRWKeys *pXmlRWKeys);

	//���������л�
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);

	virtual BSTR GetXmlElementKey()		{	return CGbXMLKeys::g_pGbXMLKeys->m_strDllCallKey;	}

	virtual BOOL IsEqual(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDesObj);
	virtual CBaseObject* Clone();

public:
	//m_strID����DLL�ļ�����
	CString m_strParaType;
	CString m_strFuncName;
	CString m_strParaData;
	CString m_strResultFile;

public:
	BOOL IsParaTypeNone()	{	return Gb_IsSafetyDllCallParaNone(m_strParaType);	}
	BOOL IsParaTypeText()	{	return Gb_IsSafetyDllCallParaText(m_strParaType);	}
	BOOL IsParaTypeFile()		{	return Gb_IsSafetyDllCallParaFile(m_strParaType);	}

	BOOL IsDllCallDefined()		{	return m_strID.GetLength() > 0;							}
	CString GetDllFilePath();
	BOOL IsDllPathValid(CString &strPath);
	BOOL IsDllPathValid();

	CString GetParaFilePath();
	BOOL IsParaFilePathValid(CString &strPath);
	BOOL IsParaFilePathValid();
};