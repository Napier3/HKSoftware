//Values.h  CValues

#pragma once

class CValues : public CExBaseList
{
public:
	CValues();
	virtual ~CValues();


//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_VALUES;   }
	virtual BSTR GetXmlElementKey()  {      return CMNGRXmlRWKeys::ValuesKey();     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual long UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//˽�г�Ա����
private:
	CValue *m_pValue;

//˽�г�Ա�������ʷ���
public:
	CValue* GetValue();
	void SetValue(CValue* pValue);
};

