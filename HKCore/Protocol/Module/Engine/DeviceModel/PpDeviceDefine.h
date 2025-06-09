#pragma once

#include"../../../Module/BaseClass/ExBaseList.h"
#include"PpDeviceNodeDefine.h"
#include"PpDeviceNodeDataDefine.h"
#include "PpDevice.h"

class CPpDeviceDefine :public CExBaseList
{
public:
	CPpDeviceDefine();
	~CPpDeviceDefine();

public:

	//��������;
	virtual void Init();
	virtual void InitAfterRead();
	virtual UINT GetClassID(){return DMCLASSID_DEVICEDEFINE;};
	virtual BSTR GetXmlElementKey()  {      return CDeviceModelXmlKeys::g_pXmlRWKeys->m_strDeviceModelKey;     }

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

	//����CPpDevice
	CPpDevice *CreateDevice(const CString &strTemplateFile);

	CPpDeviceNodeDefine* FindNodeDefine(const CString &strNodeDefID);

public:
	CPpTagDefineMngr *m_pTags;

};