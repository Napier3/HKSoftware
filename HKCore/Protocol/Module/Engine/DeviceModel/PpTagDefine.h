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

	//��������
	virtual void Init();
	virtual void InitAfterRead();
	virtual UINT GetClassID()	{return DMCLASSID_TAGDEFINE;};
	virtual BSTR GetXmlElementKey()  {      return CDeviceModelXmlKeys::g_pXmlRWKeys->m_strTagKey;     }


	//���л�
	//virtual long BinarySerializeOwn(SysTool::IBinarySerialBufferPtr &oBinaryBuff);
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode,CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);

	//�༭
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDesObj);
	virtual CExBaseObject* Clone();

	//�����Ӷ���
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);

	//����CPpTag
	void CreateTag(CPpTags **pNewTags);

	CPpTagValueDefine* FindTagValue(const CString &strValue);
	CPpTagValueDefine* AddTagValue(const CString &strValue);

public:
	CString m_strType;
	CString m_strIsKey;
	CString m_strCtrlType;
};
#endif