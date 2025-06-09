#pragma once

#include "../GbDev/GuideBookDevGlobalDefine.h"

#ifdef GB_USE_XFILEMNGRBASE
#include "../../../Module/XFileMngrBase/XFile.h"
#else
#include "../../../Module/FileMngr/FileBase.h"
#endif



class CGuideBookFile : public CXFile
{
public:
	CGuideBookFile();
	virtual ~CGuideBookFile();

private:
	CString m_strGbName;
	CString m_strFactory;

public:
	void SetGbName(const CString& strGbName)					{		m_strGbName = strGbName;		}
	CString GetGbName()																	{		return m_strGbName;					}
	void SetFactory(const CString& strFactory)						{		m_strFactory = strFactory;			}
	CString GetFactory()																		{		return m_strFactory;						}

	virtual UINT GetClassID()															{		return GB_DEV_GUIDEBOOK_FILE;									}
	virtual CXFileMngr* GetXFileMngr();

// 	virtual BSTR GetXmlElementKey()										{		return CFileMngrXMLKeys::g_pFileMngrXMLKeys->m_strFileKey;		}
// 
	//virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	//virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	//virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElemen, CXmlRWKeys *pXmlRWKeys);


};