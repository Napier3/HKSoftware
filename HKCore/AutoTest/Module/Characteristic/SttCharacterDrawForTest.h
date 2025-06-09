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
	CCharacteristics       *m_pCharacteristics;  //�������߹���
	CCharacteristic        *m_pCharacteristic;   //��ǰʹ�õ���������
	CCharacterDrawView *m_pCharDrawView;//zhouhj 2023.8.28 ���ƸĶ�,�������������Ա�����ظ�,�����ڲ�������
	CSttMacroCharItemLineDef *m_pMacroCharItemLineDef;
	long m_nType;

	void CreateCharacterDrawView();

public:
	//�����������ߵ�ID����ʼ���������߶���
	void InitCharDrawTest(CExBaseObject *pItem);  
	virtual void InitCharDrawTest(const CString &strCharID, long nIndex);  
	void InitCharDrawTestAxis(long nType);

	//���������Ŀ�����Լ��������м䱨�����ݣ�������������������״̬
	CSttMacroCharItemLineDef* UpdateMacroTest(CExBaseObject *pMacroTest, CDataGroup *pSearchReport, CDataGroup *pSearchLine);
	CSttMacroCharItemLineDef* UpdateMacroTest(CExBaseObject *pMacroTest, CValues *pSearchReport);

	//���������Ŀ�����Լ������߱������ݣ���������������״̬
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


