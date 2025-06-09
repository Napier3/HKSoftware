//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//RptDataAlsDef.h  CRptDataAlsDef

#pragma once

#include "RptAnalysisGlobal.h"

typedef CArray<double> CDoubleArray;

class CRptDataAlsDef : public CExBaseObject
{
public:
	CRptDataAlsDef();
	virtual ~CRptDataAlsDef();

	CDoubleArray m_darrRptDataValue;

	CString  m_strItemPath;
	CString  m_strValueID;
//���غ���
public:
	virtual UINT GetClassID() {    return RPTALSCLASSID_CRPTDATAALSDEF;   }
	virtual BSTR GetXmlElementKey()  {      return CRptAnalysisXmlRWKeys::CRptDataAlsDefKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

//˽�г�Ա����
private:
	void SplitItemPath();
	CStringArray m_astrItemID;

//˽�г�Ա�������ʷ���
public:
	BOOL MatchItem(CExBaseObject *pItem);
	void AddDataValue(double dValue)	{	m_darrRptDataValue.Add(dValue);	}
};

