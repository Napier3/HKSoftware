//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//PdfDBTable.h  CPdfDBTable

#pragma once

#include "PdfHLParseGlobal.h"


#include "PdfDBHead.h"

class CPdfDBTable : public CExBaseList
{
public:
	CPdfDBTable();
	virtual ~CPdfDBTable();


//���غ���
public:
	virtual UINT GetClassID() {    return PDF_CLASSID_CPDFDBTABLE;   }
	virtual BSTR GetXmlElementKey()  {      return CPdfHLParseXmlRWKeys::CPdfDBTableKey();     }
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};

