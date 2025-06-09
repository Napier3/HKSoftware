//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//CharElementArcBase.h  CCharElementArcBase

#pragma once

#include "CharElement.h"

class CCharElementArcBase : public CCharElement, public CXDrawData_Arc
{
public:
	CCharElementArcBase();
	virtual ~CCharElementArcBase();


	CString  m_strRadius;
	CString  m_strAngleBegin;
	CString  m_strAngleEnd;
	CString  m_strClockwise;

//���غ���
public:
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
	virtual void CalByExpression(BOOL bCalLines, CExBaseList *pDrawList);
	virtual void CalTestLines(UINT nTestLineMode);
	virtual CXDrawDataBase* GetCXDrawDataBase();
	virtual CXDrawBase* CreateDrawElement();

};

