//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XDrawPolyline.h  CXDrawPolyline

#pragma once

#include "XDrawGlobal.h"

#include "XDrawBase.h"


class CXDrawPolyline : public CXDrawBase, public CXDrawData_Points
{
public:
	CXDrawPolyline();
	virtual ~CXDrawPolyline();

//���غ���
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

//˽�г�Ա����
private:
	/////////��ͼ�ж�Ӧ�ĵ�����
	CPoint	*m_pPointBuffer;
	long m_nPointBuffer;

	void FreePointBuffer();
//˽�г�Ա�������ʷ���
public:

	//��ͼ��غ�������
public:
	virtual void LogicPointToDevicePoint(CAxisInterface *pAxis);
	virtual void Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag=0xFFFFFFFF);
	virtual void Pick(const CPoint &point, CExBaseList &oList);
	virtual void GetLogicBorder(double &fMinX,double &fMinY,double &fMaxX,double &fMaxY);

};
