//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CharElementInverse.h  CCharElementInverse

#pragma once

#include "CharElement.h"

#define CharElementInverse_ErrorLenth   0.05  //20230313 zhouhj 反时限特性曲线误差带长度



class CCharElementInverse : public CCharElement, public CXDrawData_Points
{
public:
	CCharElementInverse();
	virtual ~CCharElementInverse();

	//数组编号说明：
	//3=启动；   2=3段   1=2段    0=1段
	long m_nUseSection[4];
	CString m_strValSection[4];
	CString m_strTmSection[4];

	double	m_fValSection[4];	
	double	m_fTmSection[4];	

	CString m_strTmax;
	CString m_strXmax;
	double m_fTmax;
	double m_fXmax;

//重载函数
public:
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);

	virtual CString ReturnXml();
	virtual void Draw(CDC *pDC);

//私有成员变量
private:

protected:
	virtual BOOL IncreaseX(double &dValX);
	virtual void CalInversePolyline();
	virtual void AddSectionPoints();

//私有成员变量访问方法
public:
	virtual void CalByExpression(BOOL bCalLines, CExBaseList *pDrawList);
	virtual void CalTestLines(UINT nTestLineMode);

	virtual double CalInverse(double dVal) = 0;
	virtual CXDrawBase* CreateDrawElement()	;

	virtual void BeforeCalTestLines();
};

