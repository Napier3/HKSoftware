#ifndef STATEBUTTONWIDGET_H
#define STATEBUTTONWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QComboBox>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "../Module/SttTest/Common/tmt_state_test.h"
#include "../Module/ScrollCtrl/ScrollComboBox.h"



class QStateButtonWidget : public QWidget
{
	Q_OBJECT

public:
	QStateButtonWidget(bool bHorizontal = true,QWidget *parent = 0);
	~QStateButtonWidget();
   
	bool m_bHorizontal;
	int  *m_pnCurStateIndex;//插入状态指针
	
	tmt_state_test* m_pStateTest;
	void setData(tmt_state_test* pStateTest);

	void initUI();
	void initBaseData();

	void startInit();
	void stopInit(BOOL bHasPasteState);

	void AddPushButton(QPushButton** ppBtn,QString strName,int nFontSize);
	void AddComBox(QScrollComboBox** ppComBox,int nFontSize);

	void UpdateStateCombox();
	void SetStateButtonFont();
	void EnableButtons();

public:
	//QPushButton* m_pPasteStateBF;
	//QPushButton* m_pInsertStateBF;
	//QPushButton* m_pInsertStateAF;
	//QPushButton* m_pPasteStateAF;
	//QPushButton* m_pCopyState;
	//QPushButton* m_pDeleteState;
	QPushButton* m_pPreviosState;//上一状态
	QPushButton* m_pNextState;//下一状态
	QPushButton* m_pInsertStateBF;//插入状态—前
	QPushButton* m_pInsertStateAF;//插入状态—后
	QPushButton* m_pDeleteState;//删除当前状态
	QScrollComboBox* m_pStatesComBox;

	QPushButton* m_pBtnEditState;//状态编辑按钮

	//2023-2-3  lijunqing 避免初始化时多次调用  slot_StatesIndexChanged
	bool m_bEnable_slot_StatesIndexChanged;
};
extern QFont *g_pSttGlobalFont;  

#endif // STATEBUTTONWIDGET_H
