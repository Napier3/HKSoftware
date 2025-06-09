//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XDrawList.h  CXDrawList

#pragma once

#include "XDrawGlobal.h"


#include "XDrawArc.h"
#include "XDrawCircle.h"
#include "XDrawLine.h"
#include "XDrawPoint.h"
#include "XDrawElements.h"
#include "XDrawPolyline.h"
#include "XDrawText.h"

class CXDrawList : public CXDrawBase
{
public:
	CXDrawList();
	virtual ~CXDrawList();

//���غ���
public:
	virtual UINT GetClassID() {    return DWCLASSID_CXDRAWLIST;   }
	virtual BSTR GetXmlElementKey()  {      return CXDrawXmlRWKeys::CXDrawListKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	virtual void SetPickState(BOOL bPick=FALSE);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:

	//��ͼ��غ�������
public:
	virtual void LogicPointToDevicePoint(CAxisInterface *pAxis);
	virtual void Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag=0xFFFFFFFF);
	virtual void Pick(const CPoint &point, CExBaseList &oList);
	virtual void GetLogicBorder(double &fMinX,double &fMinY,double &fMaxX,double &fMaxY);

	//2021-2-19  lijunqing
	CXDrawPoint* AddPoint(double x, double y);
	CXDrawText* AddText(double x, double y, double w, double h, const CString &strText);
	void InitDrawLineColor(const COLORREF &oColor);//zhouhj 20210202 ��ʼ���������������õ���ɫ
};

