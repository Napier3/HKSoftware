//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XDrawText.h  CXDrawText

#pragma once

#include "XDrawGlobal.h"

#include "XDrawBase.h"


class CXDrawText : public CXDrawBase
{
public:
	CXDrawText();
	virtual ~CXDrawText();


 	double  m_fX;
 	double  m_fY;
 	double  m_fWidth;
 	double  m_fHeight;
	CString  m_strText;

//���غ���
public:
	virtual UINT GetClassID() {    return DWCLASSID_CXDRAWTEXT;   }
	virtual BSTR GetXmlElementKey()  {      return CXDrawXmlRWKeys::CXDrawTextKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

//˽�г�Ա����
private:
	CPoint m_ptPoint;
	CPoint m_ptWidthHeight;

//˽�г�Ա�������ʷ���
public:

	//��ͼ��غ�������
public:
	virtual void LogicPointToDevicePoint(CAxisInterface *pAxis);
	virtual void Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag=0xFFFFFFFF);
	virtual void Pick(const CPoint &point, CExBaseList &oList);
	virtual void GetLogicBorder(double &fMinX,double &fMinY,double &fMaxX,double &fMaxY);

};

