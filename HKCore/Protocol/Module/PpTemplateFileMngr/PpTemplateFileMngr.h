#pragma once

#include "../../../Module/XFileMngrBase/XFileMngr.h"
#include "PpTemplateFile.h"
#include "..\Engine\PpGlobalDefine.h"


class CPpTemplateFileMngr : public CXFileMngr
{
private:
	CPpTemplateFileMngr(const CString &strPath, BOOL bYun);
	CPpTemplateFileMngr();
	virtual ~CPpTemplateFileMngr();

	static long g_nPpTemplateFileMngr;
	void InitFileMngr(const CString &strPath);

public:
	static CPpTemplateFileMngr* g_pPpTemplateFileMngr;
	static CPpTemplateFileMngr* CreatePpTemplateFileMngr(BOOL bYun, const CString &strPath=_T(""));
	static CPpTemplateFileMngr* Create();
	static void Release();
	static void InitPpTemplateFileMngr();

public:
	virtual UINT GetClassID()	{	return PP_DEV_FILE_MNGR;	}
	//virtual BSTR GetXmlElementKey()	{	return CFileMngrXMLKeys::g_pFileMngrXMLKeys->m_strPpTemplateMngrkey;	}

// 	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
// 	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElemen, CXmlRWKeys *pXmlRWKeys);
// 
// 	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);

};

BOOL pp_GetPpTemplateFile(CWnd *pParent, CString &strPpFile, BOOL bHasFullPath=FALSE);
CString pp_GetProtocolPath();
CString pp_GetProtocolTemplatePath();
