//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CharElementIUF.h  CCharElementIUF

#pragma once
#include "CharElementInverse.h"


class CCharElementIUF : public CCharElementInverse
{
public:
	CCharElementIUF();
	virtual ~CCharElementIUF();


	CString  m_strD;
	CString  m_strP;
	CString  m_strPickup;
	CString  m_strK;//Vnom/Fs额定电压和额定频率的比值
	
	double  m_fD;
	double  m_fP;
	double  m_fPickup;//对应界面参数Pickup
	double  m_fK;//Vnom/Fs额定电压和额定频率的比值

//重载函数
public:
	virtual UINT GetClassID() {    return CHARCLASSID_CCHARELEMENTIUF;   }
	virtual BSTR GetXmlElementKey()  {      return CCharacteristicXmlRWKeys::CCharElementIUFKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);

	virtual CString ReturnXml();
	virtual void Draw(CDC *pDC);

//私有成员变量
protected:
	virtual BOOL IncreaseX(double &dValX);
	virtual void CalInversePolyline();

//私有成员变量访问方法
public:
	virtual void CalByExpression(BOOL bCalLines, CExBaseList *pDrawList);
	virtual double CalInverse(double dVal);
};

