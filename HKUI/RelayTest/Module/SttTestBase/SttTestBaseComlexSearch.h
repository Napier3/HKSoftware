#pragma once

#include "SttTestBaseSearch.h"
#include "SttComplexCalApi.h"

//CSttTestBaseComlexSearch的Angle为角度单位
class CSttTestBaseComlexSearch : public CSttTestBaseSearch
{
public:
	CSttTestBaseComlexSearch(void);
	virtual ~CSttTestBaseComlexSearch(void);

protected:
	float m_fScanFromAngle;   //搜索的起始值、终止值  原始数据
	float m_fScanToAngle;
	float m_fCurrScanValAngle;
	float m_fSearchBeginAngle;  //搜索中间值，起始值、终止值
	float m_fSearchEndAngle;
	float m_fActValueAngle;  //动作值
	BOOL m_bCurrSearchSwitch;		//当前动作的是起始值还是终止值	

public:
	virtual void InitSearch();
	float GetActValueAngle();

private:
	virtual float CalLenForCurrToFromAndTo();
	virtual float CalLenForCurrToEnd();
	virtual void  GetBinarySearchArea();
	virtual void CalLineSearchNextPoint();

	virtual void SearchSetFromAsCurr();
	virtual void SearchSetToAsCurr();
	virtual void SearchSetCurrAsBegin();
	virtual void SearchSetCurrAsEnd();
	virtual void BinarySearchCalCurrByBeginEnd();

	virtual void SetSearchBeginValAsActVal();
	virtual void SetSearchEdnValAsActVal();
	virtual void SetSearchCurrValAsActVal();

private:
	double  m_fLineAngle;              //搜索线的角度
};
