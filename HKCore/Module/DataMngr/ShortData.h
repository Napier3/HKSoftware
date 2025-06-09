//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//ShortData.h  CShortData

#pragma once

#include "DataMngrGlobal.h"
#include "../BaseClass/StringSerializeBuffer.h"

//2021-5-18  shaolei,lijunqing 
//AtsWorkBench��������61850�Ĵ�����CValue���ڳ�ͻ�����±������
//��˽�CValue��ΪCXValue��ͬʱ���ּ�����
#ifdef _use_cxvalue_
#include "XValue.h"
#else
#include "Value.h"
#endif

class CShortData : public CExBaseObject
{
public:
	CShortData();
	virtual ~CShortData();

	static CShortData* _New(CBaseObject *pParent=NULL)
	{
		CShortData *pNew = new CShortData();
		return pNew;
	}

	CString  m_strDataTypeID;
	CString  m_strUnit;
	CString  m_strValue;
	CString  m_strFormat;
	CString  m_strRemark;
	CString  m_strDefaultValue;
	long  m_nReserved;
	double   m_dTime;

//���غ���
public:
	virtual UINT GetClassID() {    return DTMCLASSID_CSHORTDATA;   }
	virtual BSTR GetXmlElementKey()  {      return CDataMngrXmlRWKeys::CShortDataKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
    virtual long InitListCtrlColumns(CListCtrl *pListCtrl);
	virtual long UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex);

	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:


//��������
public:
	void PutID(const CString &strID)	{		m_strID = strID;	}
	void PutName(const CString &strName)	{		m_strName = strName;	}
	void PutValue(const CString &strValue)	{		m_strValue = strValue;	}
	void PutUnit(const CString &strUnit)	{		m_strUnit = strUnit;	}
	void PutDataTypeID(const CString &strDataTypeID)	{	m_strDataTypeID = strDataTypeID;	}
	void PutFormat(const CString &strFormat)	{	m_strFormat = strFormat;	}
	void PutDefaultValue(const CString &strDefValue)	{	m_strDefaultValue = strDefValue;	}

	void ResetData();

	void StringSerialize(CStringSerializeBuffer &oBinaryBuffer);

	//20210417 xxy ���ڱ����ʾ
	CString GetAttrValue(const CString &strValueID);
};

