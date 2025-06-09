//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//LongData.h  CLongData

#pragma once

#include "DataMngrGlobal.h"



class CLongData : public CExBaseObject
{
public:
	CLongData();
	virtual ~CLongData();


	CString  m_strDataTypeID;
	CString  m_strUnit;
	CString  m_strValue;
	CString  m_strFormat;
	CString  m_strRemark;
	CString  m_strDefaultValue;
	long  m_nReserved;
	CString  m_strValueName;
	CString  m_strScript;
	CString  m_strMessage;
	long  m_nType;
	long  m_nShow;
	long  m_nEnable;
	long  m_nReserved2;
//���غ���
public:
	virtual UINT GetClassID() {    return DTMCLASSID_CLONGDATA;   }
	virtual BSTR GetXmlElementKey()  {      return CDataMngrXmlRWKeys::CLongDataKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual long InitListCtrlColumns(CListCtrl *pListCtrl);
	virtual long UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};

