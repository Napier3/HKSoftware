#pragma once
#include "..\baseclass\exbaselist.h"
#include "XmlDbDefine.h"
#include "XmlDbTags.h"

class CXmlDbData :
	public CExBaseList
{
public:
	CXmlDbData(void);
	virtual ~CXmlDbData(void);

	//����
	CXmlDbTags *m_pTags;

	//����
	virtual UINT GetClassID()	{	return CLASSID_XMLDBDATA;	}
	virtual void Init();
	virtual long InitAfterSerialize();
	
	//���л�
	virtual long SerializeOwn(SystemTool::IBinarySerialBufferPtr &oBinaryBuffer);
	virtual BSTR GetXmlElementKey()  {      return CXmlDbKeys::g_pXmlDbKeys->m_strDataKey;     }
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
	virtual void InsertTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent);

	//��ȡ������������
	BOOL GetAttribute(const CString &strTID, CString &strAttrData);
	BOOL GetAttribute(UINT nTIDIndex, CString &strAttrData);

	//�����Ӷ�������
	CXmlDbData* Find(UINT nTIDIndex, const CString& strAttData);
};
