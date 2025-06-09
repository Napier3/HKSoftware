#pragma once

#include "CharacteristicTmplate.h"
#include "CharacterDrawView.h"
#include "../../../SttStudio/Module/SttCmd/GuideBook/SttItems.h"

// CCharacterDrawForTest

class CSttCharacterDrawForTest
{
public:
	enum
	{
		CurrInverseTime,
		VolInverseTime, 
		DiffCurr6I,
		Distance, 
		DistanceSearch
	};

	CSttCharacterDrawForTest();
	virtual ~CSttCharacterDrawForTest();
	void SetCharacteristics(CCharacteristics *pCharacteristics)	{	m_pCharacteristics = pCharacteristics;	}

protected:
	CCharacteristics       *m_pCharacteristics;  //特性曲线管理
	CCharacteristic        *m_pCharacteristic;   //当前使用的特性曲线
	CCharacterDrawView *m_pCharDrawView;//zhouhj 2023.8.28 名称改短,避免与其它类成员变量重复,不便于查找问题
	CSttMacroCharItemLineDef *m_pMacroCharItemLineDef;
	long m_nType;

	void CreateCharacterDrawView();

public:
	//根据特性曲线的ID，初始化特性曲线对象
	void InitCharDrawTest(CExBaseObject *pItem);  
	virtual void InitCharDrawTest(const CString &strCharID, long nIndex);  
	void InitCharDrawTestAxis(long nType);

	//传入测试项目对象以及搜索线中间报告数据，更新搜索线搜索过程状态
	CSttMacroCharItemLineDef* UpdateMacroTest(CExBaseObject *pMacroTest, CDataGroup *pSearchReport, CDataGroup *pSearchLine);
	CSttMacroCharItemLineDef* UpdateMacroTest(CExBaseObject *pMacroTest, CValues *pSearchReport);

	//传入测试项目对象以及搜索线报告数据，更新搜索线最终状态
	CCharElementTestLine* UpdateMacroTest(CExBaseObject *pMacroTest, CSttReport *pReport);

protected:
	void InitMacroCharItemLineDef(const CString &strItemID);
	void InitByMacroTestPara_r_angle(CValues *pValues, const CString &strParaIDX, double &dValueX, const CString &strParaIDY, double &dValueY, const CString &strParaIDFlag, long &nValueFlag);

public:
	BOOL HasCharDrawCreated(CCharacteristic *pCharTemp);
	void InitCharacterDrawView(CCharacteristic *pCharTemp, BOOL bViewTestLines=TRUE, BOOL bCalCharTemp=TRUE);
	void InitCharacterDrawView(CCharacteristics *pChars, BOOL bViewTestLines=TRUE, BOOL bCalCharTemp=TRUE);
	void SetActiveElement(CCharElement *pElement);

	void UpdateCurrTestPoint(double dX, double dY);
	void FreeCurrTestPoint();

	void OnPaint(CDC *pDC);
	void OnSize(CDC *pDC, int cx, int cy);
};


