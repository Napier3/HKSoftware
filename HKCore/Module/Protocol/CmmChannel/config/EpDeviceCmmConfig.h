#pragma once
#include "..\..\..\..\module\baseclass\exbaselist.h"

#include "EpCmmNetConfig.h"
#include "EpCmmSerialConfig.h"

class CEpDeviceCmmConfig :	public CExBaseList
{
public:
	CEpDeviceCmmConfig(void);
	~CEpDeviceCmmConfig(void);

public:
	//��������
	virtual void Init();
	virtual long InitAfterSerialize();
	virtual UINT GetClassID(){return EPCLASSID_DEVICE_CMM_CONFIG;};

	//���л�
	virtual BSTR GetXmlElementKey()  {      return CEpCmmConfigXmlKeys::g_pXmlRWKeys->m_strCmmConfigKey;     }
	virtual long BinarySerializeOwn(CBinarySerialBuffer &oBinaryBuff);
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode,CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);

	//�༭
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

	//�����Ӷ���
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);

public:
	//���ļ�
	BOOL OpenPpTemplateXmlFile(const CString &strFile);

	/************************************************************************/
	/* 2011-01-13 ��� ���ڵ��༭
	*/
	/************************************************************************/
	virtual long InsertChildrenTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent);

	CExBaseObject* GetChildByClassID(UINT nClassID);
};
