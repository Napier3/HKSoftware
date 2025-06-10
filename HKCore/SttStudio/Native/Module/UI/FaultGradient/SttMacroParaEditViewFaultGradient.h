#ifndef STTMACROPARAEDITVIEWFAULT_GRADIENT_H
#define STTMACROPARAEDITVIEWFAULT_GRADIENT_H

#include <QWidget>
#include "ui_SttMacroParaEditViewFaultGradient.h"

#include "../Interface/SttMacroParaEditViewOriginal.h"
#include "../Controls/SttLineEdit.h"
#include "../Module/GooseParaWidget/qgooseparawidget.h"
#include "../SttTestCntrCmdDefine.h"
#include "../Module/FT3Widget/FT3OutParaWidget.h"

#include "../../SttTest/Common/Gradient/tmt_fault_gradient_test.h"

#define FILE_FAULTGRADIENT		"FaultGradientTest"
#define POSTFIX_FAULTGRADIENT    "grtxml"

namespace Ui
{
	class QSttMacroParaEditViewFaultGradient;
}

class QSttMacroParaEditViewFaultGradient : public CSttMacroParaEditViewOriginal
{
	Q_OBJECT

public:
	QSttMacroParaEditViewFaultGradient(QWidget *parent = 0);
	~QSttMacroParaEditViewFaultGradient();

public:
	//�����ʼ�� ���� ���� ���ֵ�
	void SetUIFont(QWidget* pWidget);
	void SetStyleStateValue(QGroupBox* pGroup,int nState = -1,int nVFlag = -1);
	void InitComboBox();
	void InitUI();
	//���ݳ�ʼ������
	void SetParas();
	void InitConnections();
	void SetData(PTMT_PARAS_HEAD pCurr);
	//�ı䵥λ ����
	void SetLableTextUnit(int nFaultIndex,int nChangIndex);
	void SetUnit(int nFaultMode,int nValueType,QString strUnit);
	//��ȡedit ����ֵ
	void GetEditFloatValue(QSttLineEdit* pLine,float& fValue);
	//���ñ仯���ı� �Ӷ��ı� ��·����/��ѹ �迹�Ǳ仯 
	void SetShortVaVmAngle(int nFaultIndex,int nChangIndex);
	void SetShortVaVmAngleEnable(int nShortVmFlag = 1,int nShortVmTypeFlag = 1,int nShortVaFlag = 1,int nAngleFlag = 1);
	//����edit ֵ���� 1 ʱ��  2 ����  3 ��ѹ  4 �Ƕ� 5 HZ
	float SetEditValueControl(float fValue,int nFlag = -1,QSttLineEdit* pLine = NULL);
	//�л���λ  ��������edit������������ֵ
	void SetAllEditValueControl();
	///////////////////////////////////////////////////
	//FT3 goose ���ݸ���
	virtual void UpdateGoutTab(BOOL bUpdateList = FALSE);//�����Ҫ�����������ʼ��gooseҳ���Լ�����tabҳ��
	virtual void UpdateFT3Tab(BOOL bUpdateList = FALSE);

	void UpdateGoutTab_UI(CIecCfgGoutDatas* pCfgGoutDatas);
	void UpdateFT3Tab_UI(CIecCfgDatasSMV* pIecCfgDatasSMV);
	//void UpdateBinBoutExTab();//���¿�������չ���� ��ʱû��
	//goose ���� ��� ɾ��
	void AddGooseParaWidget(CIecCfgGoutDatas* pCfgGoutDatas);
	void RemoveGooseParaWidget();
	void EnableGooseParaWidget(bool b);
	bool ExistGooseParaWidget();
	// FT3 ������� ɾ��
	void AddFT3OutParaWidget(CIecCfgDatasSMV* pIecCfgDatasSMV);
	void RemoveFT3OutParaWidget(); 
	void EnableFT3OutParaWidget(bool b);
	bool ExistFT3OutParaWidget();

signals:


public slots:
	void on_ReturnType_currentIndexChanged(int nIndex);
	//���ݹ���ģʽ �ı�仯����comombox����
	void on_FaultMode_currentIndexChanged(int nIndex);
	void on_ChangeValue_currentIndexChanged(int nIndex);
	void on_VMType_currentIndexChanged(int nIndex);
	//�������Ϳ��� ���� ����
	void on_GrpBin_ButtonClick(QAbstractButton * pCurrBtn);
	void on_GrpOutNormalError_ButtonClick(QAbstractButton * pCurrBtn);
	//�߼����
	void on_AndStateChanged(bool);
	//���࿪��   �����ͽ������
	void on_MoreOut_ButtonClick();
	void on_Estimate_ButtonClick();
	//edit ������Ӧ
	void on_EditInit_Finish();            //�仯ʼֵ
	void on_EditFinish_Finish();		  //�仯��ֵ
	void on_EditStep_Finish();			  //�仯����
	void on_EditFaultTime_Finish();		  //����ʱ��
	void on_EditShortVm_Finish();		  //��·��ѹ
	void on_EditShortVa_Finish();		  //��·����
	void on_EditAngle_Finish();			  //�迹��
	void on_EditTimeBeforeChange_Finish();//�仯ǰʱ��
	void on_EditTimeBeforeFail_Finish();  //����ǰʱ��
	void on_EditFaultBeforeVm_Finish();	  //����ǰ��ѹ
	void on_EditFaultBeforeVa_Finish();	  //����ǰ����
	void on_EditFaultBeforeAngle_Finish();//����ǰ���

public:
	virtual void InitLanuage();
	//��ȡ���л�
	virtual void SerializeTestParas(CSttXmlSerializeBase *pMacroParas, PTMT_PARAS_HEAD pParas,
		long nVolRsNum,long nCurRsNum,long nBinExNum,long nBoutExNum,BOOL bHasGoosePub);
	//�����ṹ��ָ�룬����ֱ��new
	virtual PTMT_PARAS_HEAD CreateTestParas(const char * pszMacroID);
	//���ڷ��ش����Ľṹ��ָ��
	virtual PTMT_PARAS_HEAD GetTestParas() { return m_pCurFGTest;}
	virtual char* GetMacroID(){ return STT_ORG_MACRO_FaultGradientTest; }
	//���ԺͿ�ʼ�ͽ��� ����
	virtual void OnViewTestStart();
	virtual void OnViewTestStop();
	virtual void ShowReport(CDvmValues *pValues);
	//�޸ĺͻ�ȡ�ṹ�� ���µ�ֵ 
	virtual void GetDatas(CDataGroup *pParas);
	virtual void SetDatas(CDataGroup *pParas);
	//����
	virtual void UpdateTestResource(BOOL bCreateChMaps);
	//����·����ȡ�����ļ�  grtxml �����ļ�
	virtual CString GetDefaultParaFile(); 
	virtual bool IsValidTestParasFile(const CString& strParasFile,bool bOpen = true);


private:
	//�����ṹ��
	tmt_fault_gradient_test*			 m_pCurFGTest;
	//goose ��FT3 ����
	QGooseParaWidget* m_pGooseParaWidget;
	QFT3OutParaWidget* m_pFT3OutParaWidget;
	//��ʼ��  commbox �б�ֵ
	QStringList							 m_lstGradientType;
	QStringList							 m_lstFaultMode;
	QMap<int,QStringList>				 m_mapChangValue;
	//���ݹ���ģʽ�ı�  ��¼��һ��Indexֵ�������л��仯����comomboxֵ 
	int									 m_nLastFaultModeIndex;
	QStringList							 m_lstShortVm;
	//������ btn�����м�ֵ
	int									 m_nOutNormalError;
	//��ǰ�� edit ���Ƶ����� ����commbox ѡ���ѹ��������
	int									 m_nEditControlType;

private:
	Ui::QSttMacroParaEditViewFaultGradient *ui;
};
#endif // STTMACROPARAEDITVIEWFAULT_GRADIENT_H
