//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

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

//���غ���
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

//˽�г�Ա����
private:
	/////////��ͼ�ж�Ӧ�ĵ�����
	CPoint	m_pointBegin;
	CPoint	m_pointEnd;

//˽�г�Ա�������ʷ���
public:

	//��ͼ��غ�������
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

	//���غ���
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