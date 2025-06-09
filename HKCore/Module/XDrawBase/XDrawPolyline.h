//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XDrawPolyline.h  CXDrawPolyline

#pragma once

#include "XDrawGlobal.h"

#include "XDrawBase.h"


class CXDrawPolyline : public CXDrawBase, public CXDrawData_Points
{
public:
	CXDrawPolyline();
	virtual ~CXDrawPolyline();

//重载函数
public:
	virtual UINT GetClassID() {    return DWCLASSID_CXDRAWPOLYLINE;   }
	virtual BSTR GetXmlElementKey()  {      return CXDrawXmlRWKeys::CXDrawPolylineKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

	virtual void SetBeginPoint(double x, double y)		{	CXDrawData_Points::SetBeginPoint(x, y);	};
	virtual void SetEndPoint(double x, double y)		{	CXDrawData_Points::SetEndPoint(x, y);	};

//私有成员变量
private:
	/////////作图中对应的点坐标
	CPoint	*m_pPointBuffer;
	long m_nPointBuffer;

	void FreePointBuffer();
//私有成员变量访问方法
public:

	//绘图相关函数定义
public:
	virtual void LogicPointToDevicePoint(CAxisInterface *pAxis);
	virtual void Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag=0xFFFFFFFF);
	virtual void Pick(const CPoint &point, CExBaseList &oList);
	virtual void GetLogicBorder(double &fMinX,double &fMinY,double &fMaxX,double &fMaxY);

};
