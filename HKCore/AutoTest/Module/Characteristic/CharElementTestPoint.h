//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

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

//公有成员变量访问方法
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
