#pragma once

#include "PpTemplateFile.h"

class CPpTemplateFolder : public CXFolder
{
public:
	CPpTemplateFolder();
	virtual ~CPpTemplateFolder();

public:
	virtual UINT GetClassID()		{		return PP_DEV_FOLDER;	}
	//virtual BSTR GetXmlElementKey()	{	return CFileMngrXMLKeys::g_pFileMngrXMLKeys->m_strFolderKey;	}
	
// 	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
};