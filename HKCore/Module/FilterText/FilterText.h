//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//FilterText.h  CFilterText

#pragma once

#include "FilterTextGlobal.h"



class CFilterText : public CExBaseObject
{
public:
	CFilterText();
	virtual ~CFilterText();


//���غ���
public:
	virtual UINT GetClassID() {    return FLTCLASSID_CFILTERTEXT;   }
	virtual BSTR GetXmlElementKey()  {      return CFilterTextXmlRWKeys::CFilterTextKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
	CString GetFile();
	void SetFile(const CString &strFile);
};

