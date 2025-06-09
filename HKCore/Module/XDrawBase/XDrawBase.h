//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XDrawBase.h  CXDrawBase

#pragma once

#include "XDrawGlobal.h"
#include "../Axis/AxisInterface.h"
#include "XDrawElement.h"
#include "../API/MathApi.h"

#include "XDrawDataDef.h"

// #define XDRAW_STATE_NORMAL  0
// #define XDRAW_STATE_PICKED  1

class CXDrawBase : public CXDrawElement
{
public:
	CXDrawBase();
	virtual ~CXDrawBase();

	long  m_nStyle;

//���غ���
public:
	virtual UINT GetClassID() {    return DWCLASSID_CXDRAWBASE;   }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);

	virtual void SetBeginPoint(double x, double y);
	virtual void SetEndPoint(double x, double y);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
// 	void SetPickState(BOOL bPick=FALSE);
// 	BOOL IsPicked()	{	return (m_dwState == XDRAW_STATE_PICKED);	}

//��ͼ��غ�������
public:
	virtual void LogicPointToDevicePoint(CAxisInterface *pAxis) = 0;
// 	virtual void Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag) = 0;
// 	virtual void Pick(const CPoint &point, CExBaseList &oList) = 0;
	virtual void GetLogicBorder(double &fMinX,double &fMinY,double &fMaxX,double &fMaxY) = 0;

};

// CString XDraw_GetLineStype(UINT nStyle);
// UINT XDraw_GetLineStyle(const CString &strStyle);
