#pragma once

#include "GbDevItemFile.h"

class CGbDevItemFolder : public CXFolder
{
public:
	CGbDevItemFolder();
	virtual ~CGbDevItemFolder();

public:
// 	virtual UINT GetClassID()											{		return GB_DEV_ITEM_FOLDER;		}
// 	virtual BSTR GetXmlElementKey()						{		return CFileMngrXMLKeys::g_pFileMngrXMLKeys->m_strFolderKey;}
// 
// 	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
// 	virtual CExBaseObject* CreateNewChild(long nClassID);
};