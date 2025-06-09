//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//ToolObject.h  CToolObject

#pragma once

#include "ToolsConfigGlobal.h"



class CToolObject : public CExBaseObject
{
public:
	CToolObject();
	virtual ~CToolObject();


	CString  m_strType;
	CString  m_strMode;
	CString  m_strPara;
	CString  m_strTitle;
	CString  m_strServerName;

	UINT   m_nCmdID;

	static const CString g_strToolType_cmd;
	static const CString g_strToolType_exe;

	static const CString g_strToolServer_macrotest;
	static const CString g_strToolServer_ppengine;

//���غ���
public:
	virtual UINT GetClassID() {    return TCFCLASSID_CTOOLOBJECT;   }
	virtual BSTR GetXmlElementKey()  {      return CToolsConfigXmlRWKeys::CToolObjectKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

	BOOL IsType_cmd()	{	return m_strType == g_strToolType_cmd;	}
	BOOL IsType_exe()	{	return m_strType == g_strToolType_exe;	}

	BOOL IsServer_macrotest()	{	return m_strServerName == g_strToolServer_macrotest;	}
	BOOL IsServer_ppengine()	{	return m_strServerName == g_strToolServer_ppengine;	}

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};

