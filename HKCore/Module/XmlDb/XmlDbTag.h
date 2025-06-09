#pragma once
#include "..\baseclass\exbaseobject.h"
#include "XmlDbDefine.h"

class CXmlDbTag :
	public CExBaseObject
{
public:
	CXmlDbTag(void);
	virtual ~CXmlDbTag(void);

	//����
	CString m_strData;
	
	//����
	virtual UINT GetClassID()	{	return CLASSID_XMLDBTAG;	}
	virtual void Init();
	virtual void InitAfterSerialize();
	
	//���л�
	virtual long SerializeOwn(SystemTool::IBinarySerialBufferPtr &oBinaryBuffer);
	virtual BSTR GetXmlElementKey()  {      return CXmlDbKeys::g_pXmlDbKeys->m_strTagKey;     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElemen, CXmlRWKeys *pXmlRWKeys);
	
	//�༭
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	
	//���οؼ���صĲ���
	virtual void InsertTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent);
};
