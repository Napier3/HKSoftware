#ifndef _PPTAG_VALUE_DEFINE_H__
#define _PPTAG_VALUE_DEFINE_H__
#include "..\..\..\Module\BaseClass\ExBaseObject.h"
#include "devicemodelxmlkeys.h"

class CPpTagValueDefine :public CExBaseObject
{
public:
	CPpTagValueDefine();
	virtual ~CPpTagValueDefine();

public:
	//基本方法
	virtual void Init();
	virtual void InitAfterRead();
	virtual UINT GetClassID()	{return DMCLASSID_TAG_VALUE_DEFINE;};
	virtual BSTR GetXmlElementKey()  {      return CDeviceModelXmlKeys::g_pXmlRWKeys->m_strTagValueKey;     }


	//串行化
	//virtual long BinarySerializeOwn(SysTool::IBinarySerialBufferPtr &oBinaryBuff);
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode,CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);

	//编辑
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDesObj);
	virtual CExBaseObject* Clone();

	//创建子对象
// 	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
// 	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	void SetValue(const CString &strValue);

public:
	CString m_strValue;
};
#endif