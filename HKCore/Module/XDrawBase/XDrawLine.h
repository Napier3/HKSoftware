//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XDrawLine.h  CXDrawLine

#pragma once

#include "XDrawGlobal.h"

#include "XDrawBase.h"


class CXDrawLine : public CXDrawBase, public CXDrawData_Line
{
public:
	CXDrawLine();
	virtual ~CXDrawLine();


// 	double  m_fXb;
// 	double  m_fYb;
// 	double  m_fXe;
// 	double  m_fYe;

//重载函数
public:
	virtual UINT GetClassID() {    return DWCLASSID_CXDRAWLINE;   }
	virtual BSTR GetXmlElementKey()  {      return CXDrawXmlRWKeys::CXDrawLineKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

	virtual void SetBeginPoint(double x, double y)		{	CXDrawData_Line::SetBeginPoint(x, y);	};
	virtual void SetEndPoint(double x, double y)		{	CXDrawData_Line::SetEndPoint(x, y);	};

//私有成员变量
private:
	/////////作图中对应的点坐标
	CPoint	m_pointBegin;
	CPoint	m_pointEnd;

//私有成员变量访问方法
public:

	//绘图相关函数定义
public:
	virtual void LogicPointToDevicePoint(CAxisInterface *pAxis);
	virtual void Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag=0xFFFFFFFF);
	virtual void Pick(const CPoint &point, CExBaseList &oList);
	virtual void GetLogicBorder(double &fMinX,double &fMinY,double &fMaxX,double &fMaxY);

};

class CXDrawLineR : public CXDrawLine
{
public:
	CXDrawLineR();
	virtual ~CXDrawLineR();

	double m_fAngle;

	//重载函数
public:
	virtual UINT GetClassID() {    return DWCLASSID_CXDRAWLINER;   }
	virtual BSTR GetXmlElementKey()  {      return CXDrawXmlRWKeys::CXDrawLineRKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

public:
	virtual void LogicPointToDevicePoint(CAxisInterface *pAxis);

};