//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//PdfDBInfo.h  CPdfDBInfo

#pragma once

#include "PdfHLParseGlobal.h"


#include "PdfDBTable.h"

class CPdfDBInfo : public CExBaseList
{
public:
	CPdfDBInfo();
	virtual ~CPdfDBInfo();


//���غ���
public:
	virtual UINT GetClassID() {    return PDF_CLASSID_CPDFDBINFO;   }
	virtual BSTR GetXmlElementKey()  {      return CPdfHLParseXmlRWKeys::CPdfDBInfoKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};

