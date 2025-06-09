//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//CharElementInverse.h  CCharElementInverse

#pragma once

#include "CharElement.h"

#define CharElementInverse_ErrorLenth   0.05  //20230313 zhouhj ��ʱ������������������



class CCharElementInverse : public CCharElement, public CXDrawData_Points
{
public:
	CCharElementInverse();
	virtual ~CCharElementInverse();

	//������˵����
	//3=������   2=3��   1=2��    0=1��
	long m_nUseSection[4];
	CString m_strValSection[4];
	CString m_strTmSection[4];

	double	m_fValSection[4];	
	double	m_fTmSection[4];	

	CString m_strTmax;
	CString m_strXmax;
	double m_fTmax;
	double m_fXmax;

//���غ���
public:
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);

	virtual CString ReturnXml();
	virtual void Draw(CDC *pDC);

//˽�г�Ա����
private:

protected:
	virtual BOOL IncreaseX(double &dValX);
	virtual void CalInversePolyline();
	virtual void AddSectionPoints();

//˽�г�Ա�������ʷ���
public:
	virtual void CalByExpression(BOOL bCalLines, CExBaseList *pDrawList);
	virtual void CalTestLines(UINT nTestLineMode);

	virtual double CalInverse(double dVal) = 0;
	virtual CXDrawBase* CreateDrawElement()	;

	virtual void BeforeCalTestLines();
};

