//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XDrawCircle.h  CXDrawCircle

#pragma once

#include "XDrawGlobal.h"

#include "XDrawBase.h"


class CXDrawCircle : public CXDrawBase, public CXDrawData_Circle
{
public:
	CXDrawCircle();
	virtual ~CXDrawCircle();


// 	double  m_fXCenter;
// 	double  m_fYCenter;
// 	double  m_fXRadius;
// 	double  m_fYRadius;

//重载函数
public:
	virtual UINT GetClassID() {    return DWCLASSID_CXDRAWCIRCLE;   }
	virtual BSTR GetXmlElementKey()  {      return CXDrawXmlRWKeys::CXDrawCircleKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

//私有成员变量
protected:
	CRect m_rcCircle;

//私有成员变量访问方法
public:

	//绘图相关函数定义
public:
	virtual void LogicPointToDevicePoint(CAxisInterface *pAxis);
	virtual void Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag=0xFFFFFFFF);
	virtual void Pick(const CPoint &point, CExBaseList &oList);
	virtual void GetLogicBorder(double &fMinX,double &fMinY,double &fMaxX,double &fMaxY);
};

