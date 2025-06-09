//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//UibGenState.h  CUibGenState

#pragma once

#include "UIBGeneratorGlobal.h"


#include "UibGenAnalog.h"
#include "UibGenBinary.h"

#define HARM_VALUE_MODE_ABS   0
#define HARM_VALUE_MODE_REL   1

class CUibGenState : public CExBaseList
{
public:
	CUibGenState();
	virtual ~CUibGenState();


	float  m_fTimeLong;
	long  m_nMode;
//重载函数
public:
	virtual UINT GetClassID() {    return UIBGCLASSID_CUIBGENSTATE;   }
	virtual BSTR GetXmlElementKey()  {      return CUIBGeneratorXmlRWKeys::CUibGenStateKey();     }
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
	BOOL IsModeAbs()	{	return m_nMode == HARM_VALUE_MODE_ABS;	}
	BOOL IsModeRel()	{	return m_nMode == HARM_VALUE_MODE_REL;	}

	virtual void Generate(long &nUibGenIndex, long nSampRate);
	virtual void InitGenerate(double dCoef_FreqAngleT);
	virtual void InitGenerate(long nChIndex, unsigned short *pnAttachBuffer);

	void GetAnalogs(CExBaseList &listAnalogs);
	void GetBinarys(CExBaseList &listBinarys);
};

