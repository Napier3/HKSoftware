//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

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

//重载函数
public:
	virtual UINT GetClassID() {    return ECDMCLASSID_CECDMDATA;   }
	virtual BSTR GetXmlElementKey()  {      return CEpCapDeviceModelXmlRWKeys::CEcdmDataKey();     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual long UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex);
	static long InitListCtrlColumnsFunc(CListCtrl *pListCtrl);

//私有成员变量
private:

//私有成员变量访问方法
public:
	BOOL FindData(long nDataType,long nItemIndex);
	void InitOffset(long nYxAddr, long nYcAddr, long nYtAddr);
	long GetItemIndex()	{	return m_nIndex;	}
	long GetItemIndexEx()	{	return m_nOffset + m_nIndex;	}
	void SetIndex(long nIndex)	{	m_nIndex = nIndex;	}
	long GetIndex()				{	return m_nIndex;	}
};

