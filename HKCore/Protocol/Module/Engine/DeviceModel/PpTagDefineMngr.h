#pragma once
#include"../../Module/BaseClass/ExBaseList.h"
#include "DeviceClassIDDefine.h"
#include "PpTagDefine.h"

class CPpTagDefineMngr :public CExBaseList
{
public:
	CPpTagDefineMngr();
	virtual ~CPpTagDefineMngr();

public:
	//��������
	virtual void Init();
	virtual void InitAfterRead();
	virtual UINT GetClassID(){return DMCLASSID_TAGDEFINEMNGR;};
	virtual BSTR GetXmlElementKey()  {      return CDeviceModelXmlKeys::g_pXmlRWKeys->m_strTagsKey;     }


	//���л�
	//virtual long BinarySerializeOwn(SysTool::IBinarySerialBufferPtr &oBinaryBuff);
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode,CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);

	//�༭
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CExBaseObject* Clone();

	//�����Ӷ���
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);

	//����PpTags
	CPpTags *CreateTags();

	//���TagsDef
	CPpTagDefine* NewTagDef(CPpTagDefine *pSrcTagDef);

	//GetIndexTagDefine
	CPpTagDefine* GetIndexTagDef();
};