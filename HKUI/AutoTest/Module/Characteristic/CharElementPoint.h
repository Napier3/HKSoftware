//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CharElementPoint.h  CCharElementPoint

#pragma once

#include "CharacteristicGlobal.h"
#include "../../../Module/XDrawBase/XDrawList.h"

#include "../../../Module/Expression/EpExpression.h"

#ifndef NOT_USE_XLANGUAGE
#include "../XLanguageResourceAts.h"
#endif

#define MAXPOINTCOUNT 200

class CCharElementPoint : public CXDrawData_Point, public CExBaseObject
{
public:
    CCharElementPoint();
    virtual ~CCharElementPoint();

	CString m_strX;
	CString m_strY;
	int  m_nFaultType;//保存测试项故障类型
	int  m_nZoneType;//保存测试项段号，对应非距离类区段为-1,缺省为-1
	int  m_nTestState; //当前测试项的状态   初始/选中/合格/不合格/测试完成

//公有成员变量访问方法
public:
	virtual UINT GetClassID() { return CHARCLASSID_CCharElementPoint; }
	virtual BSTR GetXmlElementKey()  { return CCharacteristicXmlRWKeys::CCharElementPointKey(); }
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

public:
	void CalByExpression(BOOL bCalLines);
	//20240823 luozibing 新增测试点 参数1传递当前测试项路径,参数2、3对应电阻值、电抗值、参数4对应故障类型，参数5对应区段 参数6对应当前测试点状态
	void SetTestPoint(CString strIDPath, float fX, float fY, int  nFaultType = -1, int nTestState = -1, int  nZoneType = -1);
	long GetXDrawElement(CXDrawList *pDrawList);
};

class CCharElementPoints : public CExBaseList
{
public:
    CCharElementPoints();
    virtual ~CCharElementPoints();

public:
	void InitPoints(const CString &strPoints);
	void GetPointsString(CString &strPoints);

	void CalByExpression(BOOL bCalLines);

    CCharElementPoint* FindObj(CCharElementPoint *pSel);
    POS GetPos(CCharElementPoint *pSel);
};
