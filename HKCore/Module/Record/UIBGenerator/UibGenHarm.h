//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//UibGenHarm.h  CUibGenHarm

#pragma once

#include "UIBGeneratorGlobal.h"



class CUibGenHarm : public CExBaseObject
{
public:
	CUibGenHarm();
	virtual ~CUibGenHarm();

	float  m_fValCoef;

	long  m_nUse;
	long  m_nIndex;
	float  m_fValue;
	float  m_fAngle;
//重载函数
public:
	virtual UINT GetClassID() {    return UIBGCLASSID_CUIBGENHARM;   }
	virtual BSTR GetXmlElementKey()  {      return CUIBGeneratorXmlRWKeys::CUibGenHarmKey();     }
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
	void Generate(long &nUibGenIndex, double &dCoef_FreqAngleT, double &dGenValue);

};

