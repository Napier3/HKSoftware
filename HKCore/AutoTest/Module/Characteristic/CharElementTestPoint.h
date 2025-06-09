//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//CharElementTestPoint.h  CCharElementTestPoint

#pragma once

#include "CharacteristicGlobal.h"
#include "../../../Module/XDrawBase/XDrawList.h"

#include "../../../Module/Expression/EpExpression.h"

#ifndef NOT_USE_XLANGUAGE
#include "../XLanguageResourceAts.h"
#endif

#define MAXPOINTCOUNT 200

class CCharElementTestPoint : public CXDrawData_Point, public CExBaseObject
{
public:
	CCharElementTestPoint();
	virtual ~CCharElementTestPoint();

	CString m_strX;
	CString m_strY;

//���г�Ա�������ʷ���
public:
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

public:
	void CalByExpression(BOOL bCalLines);
};

class CCharElementTestPoints : public CExBaseList
{
public:
	CCharElementTestPoints();
	virtual ~CCharElementTestPoints();

public:
	void InitPoints(const CString &strPoints);
	void GetPointsString(CString &strPoints);

	void CalByExpression(BOOL bCalLines);

	CCharElementTestPoint* FindObj(CCharElementTestPoint *pSel);
	POS GetPos(CCharElementTestPoint *pSel);
};
