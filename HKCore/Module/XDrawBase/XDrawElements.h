//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XDrawList.h  CXDrawElements

#pragma once

#include "XDrawElement.h"


class CXDrawElements : public CXDrawElement
{
public:
	CXDrawElements();
	virtual ~CXDrawElements();

//重载函数
public:
// 	virtual UINT GetClassID() {    return DWCLASSID_CXDrawElements;   }
// 	virtual BSTR GetXmlElementKey()  {      return CXDrawXmlRWKeys::CXDrawElementsKey();     }
// 	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
// 	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
// 	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
// 	virtual BOOL IsEqualOwn(CBaseObject* pObj);
// 	virtual BOOL CopyOwn(CBaseObject* pDest);
// 	virtual CBaseObject* Clone();
// 	virtual BOOL CanPaste(UINT nClassID);
// 	virtual CBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
// 	virtual CBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//私有成员变量
private:

//私有成员变量访问方法
public:

//消息函数
public:


//绘图相关函数定义
public:
// 	virtual void LogicPointToDevicePoint(CAxisInterface *pAxis);
	virtual void Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag=0xFFFFFFFF);
	virtual void Pick(const CPoint &point, CExBaseList &oList);
// 	virtual void GetLogicBorder(double &fMinX,double &fMinY,double &fMaxX,double &fMaxY);

public:
	virtual DWORD XCreateElementChildren(CExBaseList *pDatas, CWnd *pParentWnd);


public:
	virtual CSize CalLayoutChildren(CSize &szDraw);
	virtual void  GetSize(CSize &sz, DWORD dwMode);
	virtual CXDrawElement* QueryChildrenByXDrawDataRef(CExBaseObject *pDrawDataRef);
};

