#pragma once
#include"../../../Module/BaseClass/ExBaseList.h"
#include "DeviceModelTemplate.h"
#include "PpDeviceDefine.h"

//设备数据模型文件的格式
/*
<device-model-def xsi:noNamespaceSchemaLocation="DeviceMode.xsd">
	<device-model-template name="测控装置数据模型" id="monitor" remark="描述测控装置的模型，适用于测控装置的模拟、自动测试">
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
		//基本方法
		virtual void Init();
		virtual void InitAfterRead();
		virtual UINT GetClassID(){return DMCLASSID_DEVICEMODELDEFINE;};
		virtual BSTR GetXmlElementKey()  {      return CDeviceModelXmlKeys::g_pXmlRWKeys->m_strDeviceModelDefineKey;     }

		//串行化
		//virtual long BinarySerializeOwn(SysTool::IBinarySerialBufferPtr &oBinaryBuff)
		virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode,CXmlRWKeys *pXmlRWKeys);
		virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
		
		//编辑
		virtual BOOL IsEqualOwn(CBaseObject* pObj);
		virtual BOOL CopyOwn(CBaseObject* pDesObj);
		virtual CExBaseObject* Clone();
		
		//创建子对象
		virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
		virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);

		//打开文件
		virtual BOOL OpenXmlFile(const CString &strFile, BSTR bstrElementKey, CXmlRWKeys *pXmlRWKeys);

public:
	CDeviceModelTemplate *m_pDvTemplate;  //装置数据模型模板
	CPpDeviceDefine *m_pDeviceModel;          //装置数据模型

	BOOL SaveXmlFile(const CString &strFile);
public:
	void GetAllNodeTypes(CExBaseList &oList)		{		m_pDvTemplate->GetAllNodeTypes(oList);	}

};