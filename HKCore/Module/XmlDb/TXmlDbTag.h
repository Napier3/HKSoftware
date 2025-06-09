#pragma once
#include "..\baseclass\exbaseobject.h"
#include "XmlDbDefine.h"

class CTXmlDbTag :
	public CExBaseObject
{
public:
	CTXmlDbTag(void);
	virtual ~CTXmlDbTag(void);

	//����
	CString m_strDataType;
	LONG    m_nIsKey;

	//����
	virtual UINT GetClassID()	{	return CLASSID_TXMLDBTAG;	}
	virtual void Init();
	virtual long InitAfterSerialize();

	//���л�
	virtual long SerializeOwn(SystemTool::IBinarySerialBufferPtr &oBinaryBuffer);
	virtual BSTR GetXmlElementKey()  {      return CXmlDbKeys::g_pXmlDbKeys->m_strTagKey;     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElemen, CXmlRWKeys *pXmlRWKeys);
	
	//�༭
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
};
