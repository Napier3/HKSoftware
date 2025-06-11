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
	QStateButtonWidget(bool bHorizontal = true,QWidget *parent = 0, bool bFrimFreqModel = false);
	~QStateButtonWidget();
   
	bool m_bHorizontal;
	int  *m_pnCurStateIndex;//����״ָ̬��
	
	tmt_state_test* m_pStateTest;
	tmt_state_paras *m_pStateParas;
// 	void setData(tmt_state_test* pStateTest);
	void setData(tmt_state_paras* pStateParas, bool bFrimFreq = false);//����һ�ε�Ƶ����

	void initUI( bool bFrimFreq = false);
	void initBaseData( bool bFrimFreq = false);

	void startInit();
	void stopInit(BOOL bHasPasteState);

	void AddPushButton(QPushButton** ppBtn,QString strName,int nFontSize);
	void AddComBox(QScrollComboBox** ppComBox,int nFontSize);

	void UpdateStateCombox( bool bFrimFreq = false);
	void SetStateButtonFont();
	void EnableButtons();

public:
	//QPushButton* m_pPasteStateBF;
	//QPushButton* m_pInsertStateBF;
	//QPushButton* m_pInsertStateAF;
	//QPushButton* m_pPasteStateAF;
	//QPushButton* m_pCopyState;
	//QPushButton* m_pDeleteState;
	QPushButton* m_pPreviosState;//��һ״̬
	QPushButton* m_pNextState;//��һ״̬
	QPushButton* m_pInsertStateBF;//����״̬��ǰ
	QPushButton* m_pInsertStateAF;//����״̬����
	QPushButton* m_pDeleteState;//ɾ����ǰ״̬
	QScrollComboBox* m_pStatesComBox;

	QPushButton* m_pBtnEditState;//״̬�༭��ť

	//2023-2-3  lijunqing �����ʼ��ʱ��ε���  slot_StatesIndexChanged
	bool m_bEnable_slot_StatesIndexChanged;
};
extern QFont *g_pSttGlobalFont;  

#endif // STATEBUTTONWIDGET_H
