#pragma once
#include "..\baseclass\exbaselist.h"
#include "XmlDbDefine.h"
#include "TXmlDbTags.h"
#include "TXmlDbTag.h"

class CTXmlDbTable :
	public CExBaseList
{
public:
	CTXmlDbTable(void);
	virtual ~CTXmlDbTable(void);

	//����
	CTXmlDbTags *m_pTags;

	//����
	virtual UINT GetClassID()	{	return CLASSID_TXMLDBTABLE;	}
	virtual void Init();
	virtual long InitAfterSerialize();

	//���л�
	virtual long SerializeOwn(SystemTool::IBinarySerialBufferPtr &oBinaryBuffer);
	virtual BSTR GetXmlElementKey()  {      return CXmlDbKeys::g_pXmlDbKeys->m_strDbTableKey;     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElemen, CXmlRWKeys *pXmlRWKeys);
	
	//�����Ӷ���
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail);
	virtual CExBaseObject* CreateNewChild(long nClassID);
	
	//�༭
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

	//���οؼ���صĲ���
	//virtual void InsertTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent);

	//����ģ���
	CTXmlDbTable *GetTDbTable(const CString &strTableID);

	//������������
	CTXmlDbTag *GetAttr(const CString &strTTagID);
	long GetAttrIndex(const CString &strTTagID);
};
