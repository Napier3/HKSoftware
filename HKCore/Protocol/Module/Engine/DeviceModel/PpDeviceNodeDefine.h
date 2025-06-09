#pragma once
#include"../../../Module/BaseClass/ExBaseList.h"
#include "PpTagDefineMngr.h"
#include "PpDeviceNode.h"

#include "PpDeviceNodeDataDefine.h"

class CPpDeviceNodeDefine :public CExBaseList
{
public:
	CPpDeviceNodeDefine();
	~CPpDeviceNodeDefine();

public:
	//基本方法
	virtual void Init();
	virtual void InitAfterRead();
	virtual UINT GetClassID(){return DMCLASSID_DEVICENODEDEFINE;};
	virtual BSTR GetXmlElementKey()  {      return CDeviceModelXmlKeys::g_pXmlRWKeys->m_strDeviceNodeDefineKey;     }


	//串行化
	//virtual long BinarySerializeOwn(SysTool::IBinarySerialBufferPtr &oBinaryBuff);
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode,CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	
	//创建子对象
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);

	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CExBaseObject* Clone();

	CPpDeviceNodeDataDefine* GetDeviceNodeDataDefine();

	//创建CPpDeviceNode对象
	virtual CPpDeviceNode *CreateDeviceNode();

public:
	CPpTagDefineMngr *m_pTags;
	CString m_strNodeType;
	CString m_strMaxOccurs;
	CString m_strTemplateFile;
	
};