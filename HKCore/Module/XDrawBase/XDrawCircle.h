//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

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

//���غ���
public:
	virtual UINT GetClassID() {    return DWCLASSID_CXDRAWCIRCLE;   }
	virtual BSTR GetXmlElementKey()  {      return CXDrawXmlRWKeys::CXDrawCircleKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

//˽�г�Ա����
protected:
	CRect m_rcCircle;

//˽�г�Ա�������ʷ���
public:

	//��ͼ��غ�������
public:
	virtual void LogicPointToDevicePoint(CAxisInterface *pAxis);
	virtual void Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag=0xFFFFFFFF);
	virtual void Pick(const CPoint &point, CExBaseList &oList);
	virtual void GetLogicBorder(double &fMinX,double &fMinY,double &fMaxX,double &fMaxY);
};

