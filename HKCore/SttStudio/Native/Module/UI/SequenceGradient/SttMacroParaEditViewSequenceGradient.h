#ifndef STTMACROPARAEDITVIEWSEQUENCEGRIDENT_H
#define STTMACROPARAEDITVIEWSEQUENCEGRIDENT_H

#include "../Interface/SttMacroParaEditViewOriginal.h"
#include "../Controls/SttLineEdit.h"
#include <QWidget>
#include "../Module/GooseParaWidget/qgooseparawidget.h"
#include "../SttTestCntrCmdDefine.h"
#include "../Module/FT3Widget/FT3OutParaWidget.h"
//#include "SequenceGradientGroupWidget.h"
#include "SequenceGradientWidget.h"
//#include "../Gradient/GradientEstimateDlg.h"
#include "SequenceGradientEstimateDlg.h"
#include "../Gradient/GradientSettingValueDlg.h"
#include "../../SttTest/Common/Sequence/tmt_sequence_gradient_test.h"

#define STT_RSLTEXPR_MACROID_COMMON _T("Common")

#define STT_GRADIENT_CHANNEL_TYPE_G1_CURR    0
#define STT_GRADIENT_CHANNEL_TYPE_G1_VOLT    1

#define FILE_GRADIENT		"SequenceGradient"
#define POSTFIX_GRADIENT    "grtxml"

namespace Ui{
class QSttMacroParaEditViewSequenceGradient;
}

class QSttMacroParaEditViewSequenceGradient : public CSttMacroParaEditViewOriginal
{
	Q_OBJECT

public:
	Ui::QSttMacroParaEditViewSequenceGradient *ui;

	explicit QSttMacroParaEditViewSequenceGradient(QWidget *parent = 0);
	virtual ~QSttMacroParaEditViewSequenceGradient();

	tmt_SequenceGradientTestEx *m_pCurTest;
	tmt_GradientParasEx *m_pCurPara;
	tmt_GradientResult *m_pCurResult;

	CDataType m_oSequenceGradientChs;
	QStringList m_ChangeTypeList;
	QStringList m_listTestMode2;//���ֲ���ģʽѡ��
	QStringList m_listTestMode3;//���ֲ���ģʽѡ��
	
	QSequenceGradientWidget* m_pSequenceGradientWidget;
	QGooseParaWidget* m_pGooseParaWidget;
	QFT3OutParaWidget* m_pFT3OutParaWidget;
	//�Զ���������
	tmt_channel m_uiVOL[MAX_VOLTAGE_COUNT];
	tmt_channel m_uiCUR[MAX_CURRENT_COUNT];

private:
	CString m_strVoltage;
	CString m_strCurrent;
	CString m_strFreq;
	void SetSequenceGradientFont();

public:
	virtual void InitLanuage();
	void InitUI();
	void InitParas();
	void InitConnections();
	void InitStyle();
	void CopyBinaryConfig(BOOL b=TRUE);
	void InitMannualparas();//�仯ǰʱ��͹���ǰʱ��ĳ�ʼ��
	void InitQList();//��ʼ������������
	void UpdateSequenceGradientChs();//���±���ֵ��������
	void InitSequenceGradientChannel(Sequence_type vartype);//��ʼ������ֵ
	void getYRange(float ftime,float fv,float v1,float v2,float fstart,float fend,float &down,float &up);//��ȡ���ֵ����Сֵ
	void InitUI_AfterSequenceGridentSel();//���������;ݱ����ͱ������ͣ��޸ĵ�λ
	void EnableRadientType();//���ݱ������ͣ�ʹ�ܵݱ䷽���ʧ������
	long GetSttSequenceGradientChannelType(long nChannel);//���ݱ�����ȡֵ����
	void updateLabName();
	void AddUnSequenceGradientSettingWidget();
	void RemoveUnSequenceGradientSettingWidget();
	void InitEnableButtons();
	

	void SetData(PTMT_PARAS_HEAD pCurr);//�������ƽṹ����Ҫ�޸�
	virtual void startInit();//�Խ���Ŀؼ�����ʧ��״̬����
	virtual void stopInit();
	virtual PTMT_PARAS_HEAD CreateTestParas(const char * pszMacroID);//�½��������Ҫ�õ��ṹ��
	virtual PTMT_PARAS_HEAD CreateTestParas(PTMT_PARAS_HEAD pCurr);//��¡������
	virtual void SerializeTestParas(CSttXmlSerializeBase *pMacroParas, PTMT_PARAS_HEAD pParas,
		long nVolRsNum,long nCurRsNum,long nBinExNum,long nBoutExNum,BOOL bHasGoosePub);//���л����Բ����ṹ��,������Ҫ����
	
	virtual void OnViewTestLink(BOOL b);
	virtual void OnViewTestStart();//���Կ�ʼ�������Ӧ
	virtual void OnViewTestStop();//����ֹͣ�������Ӧ

	//CSttTestResourceBase* CreateTestResource();ֱ���ڹ��캯���д��������Դ����
	void slot_edit_changed(QSttLineEdit* pEditLine, bool bIsNor = FALSE);//��Ҫ����ui�������
	virtual PTMT_PARAS_HEAD GetTestParas() { return m_pCurTest;}
	virtual char* GetMacroID(){ return STT_ORG_MACRO_SequenceGradientTest; }

	virtual void ShowReport(CDvmValues *pValues);//����id��ȡֵ
	virtual void GetDatas(CDataGroup *pParas);
	virtual void SetDatas(CDataGroup *pParas);//��Ҫ�Ľṹ�������Լ������е�����
	
	virtual CString GetDefaultParaFile(); //����·����ȡ�����ļ�
	virtual bool IsValidTestParasFile(const CString& strParasFile,bool bOpen = true);//�ж��ļ��Ƿ����
	virtual void UpdateTestResource(BOOL bCreateChMaps);//���²���

	virtual void UpdateGoutTab(BOOL bUpdateList = FALSE);//�����Ҫ�����������ʼ��gooseҳ���Լ�����tabҳ��
	void UpdateGoutTab_UI(CIecCfgGoutDatas* pCfgGoutDatas);
	void UpdateFT3Tab_UI(CIecCfgDatasSMV* pIecCfgDatasSMV);
	virtual void UpdateFT3Tab(BOOL bUpdateList = FALSE);
	virtual void UpdateBinBoutExTab();//���¿�������չ����

	void AddGooseParaWidget(CIecCfgGoutDatas* pCfgGoutDatas);
	void RemoveGooseParaWidget();
	void EnableGooseParaWidget(bool b);
	bool ExistGooseParaWidget();

	void AddFT3OutParaWidget(CIecCfgDatasSMV* pIecCfgDatasSMV);
	void RemoveFT3OutParaWidget(); 
	void EnableFT3OutParaWidget(bool b);
	bool ExistFT3OutParaWidget();

signals:
	void sig_Para_ChangeIndexChanged(int);
	void sig_Para_ChangeIsAll();
	void sig_Para_ChangeTypeIndexChanged(int);
	void sig_Para_G1CurrentChanged(float);
	void sig_Para_G1VoltChanged(float);
	void sig_Para_DiffAngleChanged(float);	
	void sig_Para_HzChanged(float);
	void sig_Para_StartChanged(float);
	void sig_Para_EndChanged(float);
	void sig_Para_StepChanged(float);
	void sig_Para_ErrorTimeChanged(float);
	void sig_Para_ReturnTypeIndexChanged(int);
	void sig_YRangeChanged(changed_type type,QString strTitle,float fdown,float fup);

private slots:

 	void on_m_cbbVar_currentIndexChanged(int index);
 	void on_m_cbbVarType_currentIndexChanged(int index);
 	void on_m_cbbType_currentIndexChanged(int index);
 	void on_m_cbbDirection_currentIndexChanged(int index);
 	void on_m_editTimeBeforeChangeChanged();
 	void on_m_editTimeBeforeFailChanged();
 	void slot_edit_changed2(QSttLineEdit* pEditLine, long nType);
	void on_m_cbBefore_clicked(int nState);//����״̬��Ӧ�仯
	void slot_Estimate();
	void slot_SettingValue();



 	//void on_m_editFreqChanged();
 	void on_m_editInitChanged();
 	void on_m_editFinishChanged();
 	void on_m_editStepChanged();
 	void on_m_editTimeChanged();
	void on_m_editInit_clicked();
	void on_m_editFinish_clicked();
	void on_m_editStep_clicked();
	void on_m_editTime_clicked();
	void on_m_editTimeBeforeChange_clicked();
	void on_m_editTimeBeforeFail_clicked();

	void slot_chb_InPutA_StateChanged(int);
	void slot_chb_InPutB_StateChanged(int);
	void slot_chb_InPutC_StateChanged(int);
	void slot_chb_InPutD_StateChanged(int);
	void slot_chb_InPutE_StateChanged(int);
	void slot_chb_InPutF_StateChanged(int);
	void slot_chb_InPutG_StateChanged(int);
	void slot_chb_InPutH_StateChanged(int);
	void slot_chb_InPutI_StateChanged(int);
	void slot_chb_InPutJ_StateChanged(int);

	void slot_radio_AndStateChanged(bool);
	void slot_radio_OrStateChanged(bool);

	void slot_chb_OutPut1StateChanged(int);
	void slot_chb_OutPut2StateChanged(int);
	void slot_chb_OutPut3StateChanged(int);
	void slot_chb_OutPut4StateChanged(int);

	void slot_chb_OutPut1_EStateChanged(int);
	void slot_chb_OutPut2_EStateChanged(int);
	void slot_chb_OutPut3_EStateChanged(int);
	void slot_chb_OutPut4_EStateChanged(int);

	void on_m_btnManual_clicked();
	

};

extern QSttMacroParaEditViewSequenceGradient* g_SequenceGradientMain;

#endif