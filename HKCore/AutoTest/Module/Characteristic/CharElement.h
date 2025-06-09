//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//CharElement.h  CCharElement

#pragma once

#include "CharacteristicGlobal.h"
#include "CharElementTestLine.h"
#include "CharElementTestPoint.h"
#include "../../../Module/XDrawBase/XDrawLine.h"
#include "../../../Module/BaseClass/ComplexNumber.h"
#include "../../../Module/API/MathApi.h"

#include "../../../Module/XDrawBase/XDrawDataDef.h"
#include "../../../Module/XDrawBase/XDrawList.h"

#define CHAR_ERROR_LENGTH_TYPE_ABS   0
#define CHAR_ERROR_LENGTH_TYPE_ABS   0

class CCharElement : public CExBaseList
{
public:
	CCharElement();
	virtual ~CCharElement();

	CString  m_strDir;
	CString  m_strErrLength;
	long m_nErrorLengthType;   //0=���ԣ�1=���
	double   m_dErrLength;

	//��������������
	CExBaseObject *m_pDataRef;

	//CharElement��ţ����ڱ�ʶ��ƽ����
	long m_nCharElementID;  

	//����㣬ʹ�ü��������������磺linep��arcp��circlep�������ʱ���ã�����Ϊxrio�ļ�ʱ�����õ�
	long m_nPointUsePolorAxis;  

//���غ���
public:
	virtual UINT GetClassID() {    return CHARCLASSID_CCHARELEMENT;   }
	virtual BSTR GetXmlElementKey()  {      return CCharacteristicXmlRWKeys::CCharElementKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);

	virtual long InsertToListCtrl(CListCtrl *pListCtrl,long lItemIndex);
	virtual long UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex);

	virtual void Draw(CDC *pDC);
	virtual void GetBeginPoint(CString &strX, CString &strY);
	virtual void GetEndPoint(CString &strX, CString &strY);
	virtual void SetBeginPoint(const CString &strX, const CString &strY);
	virtual void SetEndPoint(const CString &strX, const CString &strY);

	virtual void SetTestPoint(long nPoints);
	virtual void SetUserTestPoint(long nPoints);
	virtual long GetUserTestPoints();
//˽�г�Ա����
private:

protected:
	long     m_nTestPoints;
	long m_nUserTestPoints;

//˽�г�Ա�������ʷ���
public:
	virtual CString ReturnXml();
	virtual void CalByExpression(BOOL bCalLines, CExBaseList *pDrawList);

	virtual CXDrawDataBase* GetCXDrawDataBase();
	virtual CXDrawBase* CreateDrawElement();

	BOOL CalCharElementExpression(CString &strExpression, double &dVAlue, BOOL bLogError);
	double GetErrorLength();
	long* GetTestPointsRef()	{	return &m_nTestPoints;	}

//�����߶��������
public:
	virtual void CalTestLines_Plumb_Arc(CXDrawData_Arc *pOwnArc);
	virtual void CalTestLines_Plumb_Line(CXDrawData_Line *pOwnLine);

	////CalTestLines:�ܵĽӿڣ�CalTestLines_####Ϊ������������͵Ľӿڣ�Ҳ����ֱ�ӱ�����
	//����m_nTestPoints���м���
	virtual void BeforeCalTestLines();
	virtual void CalTestLines(UINT nTestLineMode); 
	virtual void CalTestLines_Plumb();
	virtual void CalTestLines_Vert();
	virtual void CalTestLines_Horz();

	//���ݴ����ʼֵ����ֵ���м��㣺����һ���εĲ�����
	virtual void CalTestLines(CXDrawData_Line *pValRange, double dLenStep, UINT nTestLineMode); 
	virtual void CalTestLines_Plumb(CXDrawData_Line *pValRange, double dLenStep);
	virtual void CalTestLines_Vert(CXDrawData_Line *pValRange, double dLenStep);
	virtual void CalTestLines_Horz(CXDrawData_Line *pValRange, double dLenStep);

	//���ݴ����ʼֵ����ֵ���м��㣺����һ���εĲ�����
	virtual void CalTestLine(CXDrawData_Line *pCurrValLine, UINT nTestLineMode); 
	virtual void CalTestLine_Plumb(CXDrawData_Line *pCurrValLine);
	virtual void CalTestLine_Vert(CXDrawData_Line *pCurrValLine);
	virtual void CalTestLine_Horz(CXDrawData_Line *pCurrValLine);

	long GetTestLines_Sys();
	void SelectLines(CExBaseList &oListSys, CExBaseList &oListOther);
};

inline long char_GetTestLineID(CCharElement *pChar1, CCharElement *pChar2)
{
	return (pChar1->m_nCharElementID << 16) + pChar2->m_nCharElementID;
}

inline long char_GetTestLineID(CCharElement *pChar1, long nIndex)
{
	return pChar1->m_nCharElementID * 255 + nIndex;
}
