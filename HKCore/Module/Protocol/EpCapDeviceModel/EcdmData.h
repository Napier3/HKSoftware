//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//EcdmData.h  CEcdmData

#pragma once

#include "EpCapDeviceModelGlobal.h"

#define ECDMDATA_TYPE_YX    0
#define ECDMDATA_TYPE_YC    1
#define ECDMDATA_TYPE_YT    2


class CEcdmData : public CExBaseObject
{
public:
	CEcdmData();
	virtual ~CEcdmData();


	CString  m_strUnit;
	long  m_nDataType;
	float  m_fMin;
	float  m_fMax;
	long  m_nDead;

private:
	long  m_nIndex;
	long  m_nOffset;

//���غ���
public:
	virtual UINT GetClassID() {    return ECDMCLASSID_CECDMDATA;   }
	virtual BSTR GetXmlElementKey()  {      return CEpCapDeviceModelXmlRWKeys::CEcdmDataKey();     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual long UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex);
	static long InitListCtrlColumnsFunc(CListCtrl *pListCtrl);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
	BOOL FindData(long nDataType,long nItemIndex);
	void InitOffset(long nYxAddr, long nYcAddr, long nYtAddr);
	long GetItemIndex()	{	return m_nIndex;	}
	long GetItemIndexEx()	{	return m_nOffset + m_nIndex;	}
	void SetIndex(long nIndex)	{	m_nIndex = nIndex;	}
	long GetIndex()				{	return m_nIndex;	}
};

