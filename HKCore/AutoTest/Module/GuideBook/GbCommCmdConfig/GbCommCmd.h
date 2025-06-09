#pragma once
#include "../../../../Module/DataMngr/Values.h"

/*
通讯命令配置对象
从CExBaseList派生是为了将来的扩展
例如：为通讯命令添加一些结果描述的变量
例如：读保护动作信息
*/

//注意include路径
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
	CString m_strDataType;   //通讯命令对应的数据集的数据类型，value，struct两个值
	long    m_nUseConnect;   //是否需要进行连接状态
	CString m_strWzdEditMode; //向导编辑模式

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