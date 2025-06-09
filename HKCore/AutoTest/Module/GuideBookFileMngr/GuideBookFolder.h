#pragma once

#include "../GbDev/GuideBookDevGlobalDefine.h"

#ifdef GB_USE_XFILEMNGRBASE
#include "../../../Module/XFileMngrBase/XFolder.h"
#else
#include "../../../Module/FileMngr/FolderBase.h"
#endif

#include "GuideBookFile.h"

#ifdef GB_USE_XFILEMNGRBASE
class CGuideBookFolder : public CXFolder
#else
class CGuideBookFolder : public CXFolder
#endif
{
public:
	CGuideBookFolder();
	virtual ~CGuideBookFolder();

public:
	virtual UINT GetClassID()															{		return GB_DEV_GUIDEBOOK_FOLDER;									}
	//virtual BSTR GetXmlElementKey()										{		return CFileMngrXMLKeys::g_pFileMngrXMLKeys->m_strFolderKey;		}

// 	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
// 	virtual CExBaseObject* CreateNewChild(long nClassID);
};