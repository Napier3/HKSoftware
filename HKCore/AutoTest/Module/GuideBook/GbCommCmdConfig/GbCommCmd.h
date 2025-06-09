#pragma once
#include "../../../../Module/DataMngr/Values.h"

/*
ͨѶ�������ö���
��CExBaseList������Ϊ�˽�������չ
���磺ΪͨѶ�������һЩ��������ı���
���磺������������Ϣ
*/

//ע��include·��
#include "CommCmdConfigXMLKeys.h"

#define COMMCMD_RW_OPTR_NONE    0
#define COMMCMD_RW_OPTR_READ    1
#define COMMCMD_RW_OPTR_WRITE   2

#define WZD_EDIT_MODE_NONE _T("none")
#define WZD_EDIT_MODE_AUTO  _T("auto")
#define WZD_EDIT_MODE_EDIT  _T("edit")

class CGbCommCmdPara : public CExBaseObject
{
public:
	CGbCommCmdPara();
	virtual ~CGbCommCmdPara();

public:
	CString m_strValue;
	CString m_strType;

public:
	virtual UINT GetClassID()	{ return CLASSID_COMM_CMDPARA;}
	virtual BSTR GetXmlElementKey() { return CCommCmdConfigXMLKeys::g_pConfigXMLKeys->m_strCmdParaKey; }

	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElemen, CXmlRWKeys *pXmlRWKeys);
};

class CGbCommCmdMms : public CExBaseList
{
public:
	CGbCommCmdMms();
	virtual ~CGbCommCmdMms();

public:
	CString m_strGbDataID;
	long m_nGbRwOptr;
	CString m_strGbRwOptr;
	CString m_strDataType;   //ͨѶ�����Ӧ�����ݼ����������ͣ�value��struct����ֵ
	long    m_nUseConnect;   //�Ƿ���Ҫ��������״̬
	CString m_strWzdEditMode; //�򵼱༭ģʽ

public:
	virtual UINT GetClassID()	{ return CLASSID_COMM_CMDMMS;}
	virtual BSTR GetXmlElementKey() { return CCommCmdConfigXMLKeys::g_pConfigXMLKeys->m_strCmdExKey; }

	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElemen, CXmlRWKeys *pXmlRWKeys);

	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);

	void GetValues(CValues *pValues);

public:
	BOOL IsWrite();//	{	return (m_strGbRwOptr == g_strDeviceModelOptr_Write);	}
	BOOL IsRead();//	{	return (m_strGbRwOptr == g_strDeviceModelOptr_Read);	}
	BOOL IsRegister();
	BOOL IsWzdEditMode_Edit()	{	return m_strWzdEditMode == WZD_EDIT_MODE_EDIT;	}
	BOOL IsWzdEditMode_Auto()	{	return m_strWzdEditMode == WZD_EDIT_MODE_AUTO;	}
	BOOL IsWzdEditMode_None()	{	return m_strWzdEditMode == WZD_EDIT_MODE_NONE;	}
};

class CGbCommCmd : public CGbCommCmdMms
{
public:
	CGbCommCmd();
	virtual ~CGbCommCmd();

public:
	CString m_strPpDvNodeID;
	CString m_strPpProcedureID;

public:
	virtual UINT GetClassID()	{ return CLASSID_COMM_CMD;}
	virtual BSTR GetXmlElementKey() { return CCommCmdConfigXMLKeys::g_pConfigXMLKeys->m_strCmdKey; }

	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElemen, CXmlRWKeys *pXmlRWKeys);

	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
};