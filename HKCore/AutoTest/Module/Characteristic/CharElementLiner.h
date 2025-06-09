//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CharElementLiner.h  CCharElementLiner

#pragma once

#include "CharElementLineBase.h"



class CCharElementLiner : public CCharElementLineBase
{
public:
	CCharElementLiner();
	virtual ~CCharElementLiner();


	CString  m_strXb;
	CString  m_strYb;
	CString  m_strAngle;
	CString  m_strLengthUse;

	double  m_fLengthUse;

//重载函数
public:
	virtual UINT GetClassID() {    return CHARCLASSID_CCHARELEMENTLINER;   }
	virtual BSTR GetXmlElementKey()  {      return CCharacteristicXmlRWKeys::CCharElementLinerKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);

	virtual CString ReturnXml();
	virtual void Draw(CDC *pDC);
	
	virtual void GetBeginPoint(CString &strX, CString &strY);
	virtual void SetBeginPoint(const CString &strX, const CString &strY);
	virtual void BeforeCalTestLines();//2023.6.2 zhouhj   增加更新m_fLengthUse  m_strLengthUse 数值

//私有成员变量
private:
	void UpdateLengthUse();

//私有成员变量访问方法
public:
	virtual void CalByExpression(BOOL bCalLines, CExBaseList *pDrawList);
	virtual void CalTestLines_Plumb();
	virtual void CalTestLines_Vert();
	virtual void CalTestLines_Horz();

	void GetXeYe(double &dXe, double &dYe);
};

