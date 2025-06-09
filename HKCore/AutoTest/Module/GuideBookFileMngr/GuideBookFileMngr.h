#pragma once

#include "../GbDev/GuideBookDevGlobalDefine.h"
#include "GuideBookFolder.h"

#ifdef GB_USE_XFILEMNGRBASE
#include "../../../Module/XFileMngrBase/XFileMngr.h"
#else
#include "../../../Module/FileMngr/FileMngrBase.h"
#endif


#ifdef GB_USE_XFILEMNGRBASE
class CGuideBookFileMngr : public CXFileMngr
#else
class CGuideBookFileMngr : public CFileMngrBase
#endif
{
private:
	CGuideBookFileMngr(BOOL bUseAts=FALSE);
	virtual ~CGuideBookFileMngr();

	static long g_nGuideBookFileMngr;

public:
	static CGuideBookFileMngr* g_pGuideBookFileMngr;
	static CGuideBookFileMngr* CreateGuideBookFileMngr(BOOL bYun, BOOL bUseAts=FALSE);
	static void Release();

	static void InitGuideBookFileMngr(const CString &strGbFileType, BOOL bYun);

public:
	virtual UINT GetClassID()															{		return CLASSID_XFILEMNGR;		}
	//virtual BSTR GetXmlElementKey()										{		return CFileMngrXMLKeys::g_pFileMngrXMLKeys->m_strGbFileMngrKey;		}

// 	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
// 	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
// 	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElemen, CXmlRWKeys *pXmlRWKeys);
// 
// 	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
// 	virtual CExBaseObject* CreateNewChild(long nClassID);

	virtual BOOL SaveXMLFile();
	virtual BOOL OpenXMLFile(const CString &strFileType, BOOL bYun=FALSE);
	virtual BOOL OpenXMLFile(const CString &strFileType, const CString &strFileType2, BOOL bYun=FALSE);

protected:
	void AddGbFileType(const CString &strFileType);
};