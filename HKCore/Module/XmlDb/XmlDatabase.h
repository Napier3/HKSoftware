#pragma once
#include "..\baseclass\exbaselist.h"
#include "XmlDbDefine.h"

class CXmlDatabase :
	public CExBaseList
{
public:
	CXmlDatabase(void);
	virtual ~CXmlDatabase(void);

	//����
	CString m_strUserName;
	CString m_strUserID;

	//����
	virtual UINT GetClassID()	{	return CLASSID_XMLDATABASE;	}
	virtual void Init();
	virtual long InitAfterSerialize();

	//���л�
	virtual long SerializeOwn(SystemTool::IBinarySerialBufferPtr &oBinaryBuffer);
	virtual BSTR GetXmlElementKey()  {      return CXmlDbKeys::g_pXmlDbKeys->m_strDbKey;     }
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

	//�ļ���/����
	BOOL OpenXmlDbFile(const CString& strFile);
	BOOL SaveXmlDbFile(const CString& strFile);
};
