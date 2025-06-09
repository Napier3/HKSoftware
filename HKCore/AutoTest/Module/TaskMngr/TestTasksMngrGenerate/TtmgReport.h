//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

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

//重载函数
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

//私有成员变量
private:

//私有成员变量访问方法
public:
	void InitReport(CXFile *pXFile);
};

