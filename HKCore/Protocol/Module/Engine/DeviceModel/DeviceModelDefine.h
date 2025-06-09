#pragma once
#include"../../../Module/BaseClass/ExBaseList.h"
#include "DeviceModelTemplate.h"
#include "PpDeviceDefine.h"

//�豸����ģ���ļ��ĸ�ʽ
/*
<device-model-def xsi:noNamespaceSchemaLocation="DeviceMode.xsd">
	<device-model-template name="���װ������ģ��" id="monitor" remark="�������װ�õ�ģ�ͣ������ڲ��װ�õ�ģ�⡢�Զ�����">
	</device-model-template>
	<device-model>
	</device-model>
</device-model-def>
*/

class CPpDeviceModelDefine :public CExBaseList
{
public:
	CPpDeviceModelDefine();
	~CPpDeviceModelDefine();

public:
		//��������
		virtual void Init();
		virtual void InitAfterRead();
		virtual UINT GetClassID(){return DMCLASSID_DEVICEMODELDEFINE;};
		virtual BSTR GetXmlElementKey()  {      return CDeviceModelXmlKeys::g_pXmlRWKeys->m_strDeviceModelDefineKey;     }

		//���л�
		//virtual long BinarySerializeOwn(SysTool::IBinarySerialBufferPtr &oBinaryBuff)
		virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode,CXmlRWKeys *pXmlRWKeys);
		virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
		
		//�༭
		virtual BOOL IsEqualOwn(CBaseObject* pObj);
		virtual BOOL CopyOwn(CBaseObject* pDesObj);
		virtual CExBaseObject* Clone();
		
		//�����Ӷ���
		virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
		virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);

		//���ļ�
		virtual BOOL OpenXmlFile(const CString &strFile, BSTR bstrElementKey, CXmlRWKeys *pXmlRWKeys);

public:
	CDeviceModelTemplate *m_pDvTemplate;  //װ������ģ��ģ��
	CPpDeviceDefine *m_pDeviceModel;          //װ������ģ��

	BOOL SaveXmlFile(const CString &strFile);
public:
	void GetAllNodeTypes(CExBaseList &oList)		{		m_pDvTemplate->GetAllNodeTypes(oList);	}

};