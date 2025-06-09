#pragma  once
#include"../../../Module/BaseClass/ExBaseList.h"
#include "PpDeviceNodeType.h"
#include "DeviceModelXmlKeys.h"

class CDeviceModelTemplate : public CExBaseList
{
public:
	CDeviceModelTemplate();
	~CDeviceModelTemplate();

public:
	//基本方法
	virtual void Init();
	virtual void InitAfterRead();
	virtual UINT GetClassID(){return DMCLASSID_DEVICEMODELTEMPLATE;};
	virtual BSTR GetXmlElementKey()  {      return CDeviceModelXmlKeys::g_pXmlRWKeys->m_strDeviceModelTemplateKey;     }

	//串行化
	//virtual long BinarySerializeOwn(SysTool::IBinarySerialBufferPtr &oBinaryBuff);
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode,CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);

	//编辑
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDesObj);
	virtual CExBaseObject* Clone();

	//创建子对象
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);

public:
	CString m_strRemark;

public:
	void GetAllNodeTypes(CExBaseList &oList);
};

CPpDeviceNodeType* Pp_FindDeviceNodeType(CExBaseList *pList, const CString &strNodeType);
