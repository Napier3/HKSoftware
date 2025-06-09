#pragma once
#include "gbitembase.h"
#include "GuideBookDefine.h"

class CJobGuide :public CGbItemBase
{
public:
	CJobGuide(void);
	virtual ~CJobGuide(void);

public:
	//Serialize mathods
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual UINT GetClassID()				{		return GBCLASSID_JOBGUIDE;										};
	virtual BSTR GetXmlElementKey()	{      return CGbXMLKeys::g_pGbXMLKeys->m_strJobGuideKey;	}

	virtual CBaseObject* Clone(); 
	virtual BOOL CanPaste(CExBaseObject *pObj);

protected:

private:

};