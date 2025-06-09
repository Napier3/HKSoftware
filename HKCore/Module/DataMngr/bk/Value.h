//Value.h  CValue

#pragma once

class CValue : public CExBaseObject
{
public:
	CValue();
	virtual ~CValue();


	CString  m_strValue;
//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_VALUE;   }
	virtual BSTR GetXmlElementKey()  {      return CMNGRXmlRWKeys::ValueKey();     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual long UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};

