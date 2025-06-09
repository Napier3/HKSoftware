#pragma once

#include "GuideBookDefine.h"

class CAnalog :public CExBaseObject
{
public:
	CAnalog(void);
	virtual ~CAnalog(void);

	static CAnalog* _New(CBaseObject *pParent=NULL)
	{
		CAnalog *pNew = new CAnalog();
		return pNew;
	}

public:
	//attribute
	CString m_strUnit;
	CString m_strType;
	CString m_strValue;   //数据值，2011/8/29添加，用于手动录入模拟量数值

public:
	//Serialize mathods
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual UINT GetClassID()			{		return GBCLASSID_ANALOG;	}
	virtual BSTR GetXmlElementKey() ;

	virtual BOOL IsEqual(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDesObj);
	virtual CBaseObject* Clone();

protected:

private:

};