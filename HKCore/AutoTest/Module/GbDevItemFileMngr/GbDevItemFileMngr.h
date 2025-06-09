#pragma  once

#include "../GbDev/GuideBookDevGlobalDefine.h"

#include "GbDevItemFolder.h"

class CGbDevItemFileMngr : public CXFileMngr
{
private:
	CGbDevItemFileMngr();
	virtual ~CGbDevItemFileMngr()	;

	static long g_nGbDevItemFileMngrRef;
	
public:
	static CGbDevItemFileMngr* g_pGbDevItemFileMngr;
	static CGbDevItemFileMngr* CreateGbDevItemFileMngr();
	static void Release();

public:
// 	virtual UINT GetClassID()												{		return GB_DEV_ITEM_FILE_MNGR;		}
// 	virtual BSTR GetXmlElementKey()							{		return CFileMngrXMLKeys::g_pFileMngrXMLKeys->m_strGbDevItemFileMngrKey;		}
// 
// 	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
// 	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
// 	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElemen, CXmlRWKeys *pXmlRWKeys);
// 	
// 	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
// 	virtual CExBaseObject* CreateNewChild(long nClassID);

	virtual BOOL SaveXMLFile();
	virtual BOOL OpenXMLFile(const CString &strTypeName, const CString &strTypeID);
};