#pragma once

//×¢ÒâincludeÂ·¾¶
#include "CommCmdConfigXMLKeys.h"
#include "GbCommCmd.h"

class CGbCommCmdConfig : public CExBaseList
{
public:
	CGbCommCmdConfig();
	virtual ~CGbCommCmdConfig();

	static const CString g_strCommCmdConfigFile;// = _T("CommCmdConfig.xml");

public:
//	static long g_nGbCommCmdConfig;
// 	static CGbCommCmdConfig* g_pGbCommCmdConfig;
// 	static CGbCommCmdConfig* CreateGbCommCmdConfig();
// 	static void Release();

public:
	virtual UINT GetClassID()	{ return CLASSID_COMM_CMD_CONFIG;}
	virtual BSTR GetXmlElementKey()	{	return CCommCmdConfigXMLKeys::g_pConfigXMLKeys->m_strCommCmdConfigKey; }

	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElemen, CXmlRWKeys *pXmlRWKeys);

	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);

	virtual BOOL SaveXMLFile();
//	virtual BOOL OpenXmlFile();
	virtual BOOL OpenXmlFile(const CString &strFile);
	CGbCommCmdMms* FindCmd_Read(const CString &strDsID);
	CGbCommCmdMms* FindCmd_Write(const CString &strDsID);
};