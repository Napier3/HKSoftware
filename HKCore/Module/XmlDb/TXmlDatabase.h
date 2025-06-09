#pragma once
#include "..\baseclass\exbaselist.h"
#include "XmlDbDefine.h"
#include "TXmlDbTable.h"

class CTXmlDatabase :
	public CExBaseList
{
public:
	CTXmlDatabase(void);
	virtual ~CTXmlDatabase(void);

	//����
	CString m_strDbName;
	CString m_strDbID;

	//����
	virtual UINT GetClassID()	{	return CLASSID_TXMLDATABASE;	}
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
	BOOL OpenXmlFile(const CString& strFile);
	BOOL SaveXmlFile(const CString& strFile);

	//����
	CTXmlDbTable *GetTDbTable(const CString &strID);
};
