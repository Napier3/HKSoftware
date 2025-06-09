//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//DsvElemAttr.h  CDsvElemAttr

#pragma once


#include "DsvBase.h"

#define DSV_OPTR_NONE    0xFF

//����==
#define DSV_OPTR_EQ      0

//С��<
#define DSV_OPTR_LT      1

//С�ڵ���<=
#define DSV_OPTR_LTEQ    2

//����>
#define DSV_OPTR_GT      3

//���ڵ���>=
#define DSV_OPTR_GTEQ    4

//������!=
#define DSV_OPTR_NOTEQ   5

//����[]
#define DSV_OPTR_HAS     6

//������![]
#define DSV_OPTR_HASNOT  7

//��Χ<>
#define DSV_OPTR_INRANGE 8

//��Χ���߽�<=>
#define DSV_OPTR_EQRANGE 9

//���ݱ�����ֵ
#define DSV_OPTR_GETVALUE 10

#define DSV_OPTR_COUNT   11

#define DSV_ATTR_TYPE_INT     0
#define DSV_ATTR_TYPE_FLOAT   1
#define DSV_ATTR_TYPE_STRING  2
#define DSV_ATTR_TYPE_DATE    3
#define DSV_ATTR_TYPE_COUNT   4

class CDsvElemAttr : public CExBaseObject
{
public:
	CDsvElemAttr();
	virtual ~CDsvElemAttr();
	static const CString g_astrAttrOptrID[DSV_OPTR_COUNT];
	static const CString g_astrAttrDataTypeID[DSV_ATTR_TYPE_COUNT];

	CString  m_strOptr;
	DWORD    m_dwOptr;

	CString  m_strDataType;
	DWORD    m_dwDataType;

	CString  m_strValue;
	CString  m_strValue2;
	CString  m_strVariable;
	
//���غ���
public:
	virtual UINT GetClassID() {    return DVMCLASSID_CDSVELEMATTR;   }
	virtual BSTR GetXmlElementKey()  {      return CDataMngrXmlRWKeys::CDsvElemAttrKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
//	virtual BOOL CanPaste(UINT nClassID);
//	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
//	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//˽�г�Ա����
private:
	void InitOptrString();
	void InitOptrDWORD();
	void InitDataTypeString();
	void InitDataTypeDWORD();

//˽�г�Ա�������ʷ���
public:
	virtual BOOL ValidateData(CDvmData *pDvmData);
	virtual BOOL SetValuesByData(CDvmData *pDvmData, CValues *pRptValues);

	void SetOptr(const CString &strOptr);
	void SetDataType(const CString &strDataType);

protected:
	virtual BOOL Validate_Int(const CString &strValue);
	virtual BOOL Validate_Float(const CString &strValue);
	virtual BOOL Validate_String(const CString &strValue);
	virtual BOOL Validate_Date(const CString &strValue);

};

