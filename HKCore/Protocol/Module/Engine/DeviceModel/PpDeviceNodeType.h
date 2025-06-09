#pragma  once

#include"../../../Module/BaseClass/ExBaseList.h"
#include "DeviceClassIDDefine.h"
#include "DeviceModelXmlKeys.h"
#include "PpDeviceNodeDefine.h"

class CPpDeviceNodeType :public CExBaseList
{
public:
	CPpDeviceNodeType();
	~CPpDeviceNodeType();

public:

	//基本方法
	virtual void Init();
	virtual void InitAfterRead();
	virtual UINT GetClassID(){return DMCLASSID_DEVICENODETYPE;};
	virtual BSTR GetXmlElementKey()  {      return CDeviceModelXmlKeys::g_pXmlRWKeys->m_strNodeTypeKey;     }


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

	BOOL IsLeafNodeType();
	CPpDeviceNodeDefine* CreateDeviceNodeDefine();

public:

//	CString m_strName;
//	CString m_strID;	
	long m_nTypeID;
	long m_nMinOccurs;
	long m_nMaxOccurs;

public:
	void GetAllNodeTypes(CExBaseList &oList);
};

