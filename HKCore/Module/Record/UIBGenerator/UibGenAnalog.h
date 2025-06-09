//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//UibGenAnalog.h  CUibGenAnalog

#pragma once

#include "UIBGeneratorGlobal.h"
#include "UibGenHarm.h"

#include "UibChGenInterface.h"

class CUibGenAnalog : public CUibChGenInterface
{
public:
	CUibGenAnalog();
	virtual ~CUibGenAnalog();


	float  m_fZero;
	float  m_fCoef;
	CString  m_strChID;
	long  m_nRand;
	CString  m_strUnit;
	float  m_fPrimary;
	float  m_fSecondary;

	double m_dCoef_FreqAngleT;

//重载函数
public:
	virtual UINT GetClassID() {    return UIBGCLASSID_CUIBGENANALOG;   }
	virtual BSTR GetXmlElementKey()  {      return CUIBGeneratorXmlRWKeys::CUibGenAnalogKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//私有成员变量
private:

//私有成员变量访问方法
public:
	virtual void Generate(long &nUibGenIndex, long &nCalIndex);
	virtual void InitGenerate(double dCoef_FreqAngleT);
};

