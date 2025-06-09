//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//TtmgReport.h  CTtmgReport

#pragma once

#include "TestTasksMngrGenerateGlobal.h"
#include "..\..\..\..\Module\XfileMngrBase\XFile.h"

class CTtmgReport : public CExBaseObject
{
public:
	CTtmgReport();
	virtual ~CTtmgReport();

	CString m_strReportType;
	CXFile *m_pXFile;

//���غ���
public:
	virtual UINT GetClassID() {    return TTMGCLASSID_CTTMGREPORT;   }
	virtual BSTR GetXmlElementKey()  {      return CTestTasksMngrGenerateXmlRWKeys::CTtmgReportKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
	void InitReport(CXFile *pXFile);
};

