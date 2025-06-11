#ifndef STTMACROPARAEDITVIEWANALOGCIRBREAKER_H
#define STTMACROPARAEDITVIEWANALOGCIRBREAKER_H

#include "../Interface/SttMacroParaEditViewOriginal.h"
#include "AnalogCirBreakerParaset.h"
#include "../Module/ScrollCtrl/ScrollComboBox.h"

class QSttMacroParaEditViewAnalogCirBreaker : public CSttMacroParaEditViewOriginal
{
	Q_OBJECT

public:
	explicit QSttMacroParaEditViewAnalogCirBreaker(QWidget *parent = 0);
	virtual ~QSttMacroParaEditViewAnalogCirBreaker();

	void InitUI();
	void InitData();
	void InitConnection();
	virtual void UpdateTestResource(BOOL bCreateChMaps);
	virtual char* GetMacroID(){ return STT_ORG_MACRO_AnalogCirBreakerTest; }
	virtual CSttTestResourceBase* CreateTestResource();
	virtual void GetDatas(CDataGroup *pParas);
	virtual void SetDatas(CDataGroup *pParas);
	virtual void OnViewTestStart();
	virtual void OnViewTestStop();
	QIcon SetIconPic(int nState);
	void UpdateComboBox(QStringList pList,QList<QScrollComboBox*> pComboBoxList,bool b );
	void UpdateIconState(CDataGroup *pDataGroup);  
	virtual BOOL OpenTestTestMngrFile(const CString& strParasFile);
	virtual void UpdateEventMsg(CEventResult *pCurrEventResult);
	void SaveParasXml();
	void UpdateParas();


private:
	tmt_channel m_uiCUR[MAX_CURRENT_COUNT];
	CDataGroup m_pAnalogCirBreakerData;

    QList< QPair <QLabel*, CString> > m_pBinLabelList;
    QList< QPair <QLabel*, CString> > m_pBoutLabelList;


	AnalogCirBreakerParaset *m_pAnalogCirBreakerParaset;
	QScrollComboBox *m_pInitPositionCombox;//初始位置
	QScrollComboBox *m_pClosePulseCombox;//合闸脉冲
	QScrollComboBox *m_pOpenPulseCombox;//分闸脉冲

	QScrollComboBox *m_pCloseSignalCombox;//合位信号
	QScrollComboBox *m_pOpenSiganlCombox;//分位信号
	QScrollComboBox *m_pEnergyCombox;//未储能信号

	QList<QScrollComboBox*> m_pBoutComboBoxList;
	QList<QScrollComboBox*> m_pBinComboBoxList;
	QLineEdit *m_pCloseDelayEdit; //合闸延迟时间
	QLineEdit *m_pOpenDelayEdit;//分闸延时时间

	QLabel *m_pActionCloseLabel;	//动作信号合闸
	QLabel *m_pActionOpenLabel;	//动作信号分闸
	QLabel *m_pPosCloseLabel;	//位置信号合位
	QLabel *m_pPosOpenLabel;	//位置信号分位
	QLabel *m_pPosUnEnergyLabel;	//位置信号未储能
	QLabel *m_pCurPosCloseLabel;	//当前位置信号合位
	QLabel *m_pCurPosOpenLabel;	//当前位置信号分位

protected slots:
	void slot_InitPositionComboBoxChanged(int index);
	void slot_BinComboBoxChanged(int index);
	void slot_BoutComboBoxChanged(int index);
	void slot_CloseDelay_editingFinished();
	void slot_OpenDelay_editingFinished();
	void slot_updateParas(int channelNum,int valueFlag,float datavalue);
	void slot_updateParas();

};	
extern QSttMacroParaEditViewAnalogCirBreaker* g_pAnalogCirBreaker;

#endif