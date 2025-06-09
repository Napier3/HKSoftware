#pragma once

#include "../GbDev/GuideBookDevGlobalDefine.h"
#include "../../../Module/XFileMngrBase/XFileMngr.h"


class CGbDevItemFile : public CXFile
{
public:
	CGbDevItemFile();
	virtual ~CGbDevItemFile();

private:
	CString m_strItemName;
	CString m_strItemID;

public:
	void SetItemName(const CString& strItemName)					{		m_strItemName = strItemName;		}
	CString GetItemName()																		{		return m_strItemName;						}
	void SetItemID(const CString& strItemID)									{		m_strItemID = strItemID;					}
	CString GetItemID()																				{		return m_strItemID;								}

	virtual UINT GetClassID()									{			return GB_DEV_ITEM_FILE;		}
// 	virtual BSTR GetXmlElementKey()				{			return CFileMngrXMLKeys::g_pFileMngrXMLKeys->m_strFileKey;		}

// 	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
// 	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
// 	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElemen, CXmlRWKeys *pXmlRWKeys);

};