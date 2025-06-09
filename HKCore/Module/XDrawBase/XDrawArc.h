//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XDrawArc.h  CXDrawArc

#pragma once

#include "XDrawGlobal.h"

#include "XDrawCircle.h"


class CXDrawArc : public CXDrawBase, public CXDrawData_Arc
{
public:
	CXDrawArc();
	virtual ~CXDrawArc();


// 	double  m_fXCenter;
// 	double  m_fYCenter;
// 	double  m_fXRadius;
// 	double  m_fYRadius;
// 	double  m_fAngleBegin;
// 	double  m_fAngleEnd;

//重载函数
public:
	virtual UINT GetClassID() {    return DWCLASSID_CXDRAWARC;   }
	virtual BSTR GetXmlElementKey()  {      return CXDrawXmlRWKeys::CXDrawArcKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

	virtual void SetBeginPoint(double x, double y)		{	CXDrawData_Arc::SetBeginPoint(x, y);	};
	virtual void SetEndPoint(double x, double y)		{	CXDrawData_Arc::SetEndPoint(x, y);	};

//私有成员变量
protected:
	CRect m_rcCircle;
	CPoint m_ptBegin,m_ptEnd;

//私有成员变量访问方法
public:

	//绘图相关函数定义
public:
	virtual void LogicPointToDevicePoint(CAxisInterface *pAxis);
	virtual void Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag=0xFFFFFFFF);
	virtual void Pick(const CPoint &point, CExBaseList &oList);
	virtual void GetLogicBorder(double &fMinX,double &fMinY,double &fMaxX,double &fMaxY);

};

