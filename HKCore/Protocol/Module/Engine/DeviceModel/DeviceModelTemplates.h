#pragma  once
#include"../../../Module/BaseClass/ExBaseList.h"
#include "DeviceModelTemplate.h"

class CDeviceModelTemplates : public CExBaseList
{
public:
	CDeviceModelTemplates();
	~CDeviceModelTemplates();

public:
	//��������
	virtual void Init();
	virtual void InitAfterRead();
	virtual UINT GetClassID(){return DMCLASSID_DEVICEMODELTEMPLATES;};
	virtual BSTR GetXmlElementKey()  {      return CDeviceModelXmlKeys::g_pXmlRWKeys->m_strDeviceModelTemplatesKey;     }

	//���л�
	//virtual long BinarySerializeOwn(SysTool::IBinarySerialBufferPtr &oBinaryBuff);
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode,CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);

	//�༭
	virtual BOOL IsEqualOwn(CExBaseObject* pObj);
	virtual BOOL CopyOwn(CExBaseObject* pDesObj);
	virtual CExBaseObject* Clone();

	//�����Ӷ���
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);


};