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
	QScrollComboBox *m_pInitPositionCombox;//��ʼλ��
	QScrollComboBox *m_pClosePulseCombox;//��բ����
	QScrollComboBox *m_pOpenPulseCombox;//��բ����

	QScrollComboBox *m_pCloseSignalCombox;//��λ�ź�
	QScrollComboBox *m_pOpenSiganlCombox;//��λ�ź�
	QScrollComboBox *m_pEnergyCombox;//δ�����ź�

	QList<QScrollComboBox*> m_pBoutComboBoxList;
	QList<QScrollComboBox*> m_pBinComboBoxList;
	QLineEdit *m_pCloseDelayEdit; //��բ�ӳ�ʱ��
	QLineEdit *m_pOpenDelayEdit;//��բ��ʱʱ��

	QLabel *m_pActionCloseLabel;	//�����źź�բ
	QLabel *m_pActionOpenLabel;	//�����źŷ�բ
	QLabel *m_pPosCloseLabel;	//λ���źź�λ
	QLabel *m_pPosOpenLabel;	//λ���źŷ�λ
	QLabel *m_pPosUnEnergyLabel;	//λ���ź�δ����
	QLabel *m_pCurPosCloseLabel;	//��ǰλ���źź�λ
	QLabel *m_pCurPosOpenLabel;	//��ǰλ���źŷ�λ

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