//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XDrawPoint.h  CXDrawPoint_Ex

#pragma once

#include "XDrawGlobal.h"

#include "XDrawBase.h"

//2021-9-7  lijunqing
//���ܱ������ݣ����Ƕ�̬����
class CXDrawPoint_Ex : public CXDrawBase, public CXDrawData_Point_Ex
{
public:
	CXDrawPoint_Ex();
	CXDrawPoint_Ex(double *x, double *y);
	virtual ~CXDrawPoint_Ex();


	long  m_nPixel;
	DWORD  m_dwDrawStyle;

//���غ���
public:
	virtual UINT GetClassID() {    return DWCLASSID_CXDRAWPOINT_EX;   }
//	virtual BSTR GetXmlElementKey()  {      return CXDrawXmlRWKeys::CXDrawPoint_ExKey();     }
// 	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
// 	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
// 	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

//˽�г�Ա����
private:
	CPoint m_ptPoint;

//˽�г�Ա�������ʷ���
public:

	//��ͼ��غ�������
public:
	virtual void LogicPointToDevicePoint(CAxisInterface *pAxis);
	virtual void Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag=0xFFFFFFFF);
	virtual void Pick(const CPoint &point, CExBaseList &oList);
	virtual void GetLogicBorder(double &fMinX,double &fMinY,double &fMaxX,double &fMaxY);

};

