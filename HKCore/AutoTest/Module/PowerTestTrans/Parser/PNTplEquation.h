//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//PNTplEquation.h  CPNTplEquation

#pragma once

#include "PNTplMngrGlobal.h"



class CPNTplEquation : public CExBaseObject
{
public:
	CPNTplEquation();
	virtual ~CPNTplEquation();


	CString  m_strValue;
//重载函数
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CPNTPLEQUATION;   }
	virtual BSTR GetXmlElementKey()  {      return CPNTplMngrXmlRWKeys::CPNTplEquationKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

//私有成员变量
private:
	double m_fValueCal;
	BOOL m_bHasCal;

//私有成员变量访问方法
public:
	double GetValue();
	BOOL HasCal()	{	return m_bHasCal;	}
	void SetValueCal(double dCal);
};

