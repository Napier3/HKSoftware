#ifndef CTTAG_H_H_H
#define CTTAG_H_H_H
#include "..\..\..\Module\BaseClass\ExBaseList.h"
#include "PpTagValueDefine.h"
#include "PpTags.h"

class CPpTagDefine :public CExBaseList
{
public:
	CPpTagDefine();
	virtual ~CPpTagDefine();
public:

	//基本方法
	virtual void Init();
	virtual void InitAfterRead();
	virtual UINT GetClassID()	{return DMCLASSID_TAGDEFINE;};
	virtual BSTR GetXmlElementKey()  {      return CDeviceModelXmlKeys::g_pXmlRWKeys->m_strTagKey;     }


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

	//创建CPpTag
	void CreateTag(CPpTags **pNewTags);

	CPpTagValueDefine* FindTagValue(const CString &strValue);
	CPpTagValueDefine* AddTagValue(const CString &strValue);

public:
	CString m_strType;
	CString m_strIsKey;
	CString m_strCtrlType;
};
#endif