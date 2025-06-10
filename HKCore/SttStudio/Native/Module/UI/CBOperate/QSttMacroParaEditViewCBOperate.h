#ifndef QCBOPERATEADDMULTDLG_H
#define QCBOPERATEADDMULTDLG_H

#include "../Interface/SttMacroParaEditViewOriginal.h"
#include "../Controls/SttCheckBox.h"
#include "Grid/CBOperateResultAssessGrid.h"
#include "Dlg/CBOperateCommonParasDlg.h"
#include "../../SttTest/Common/Impedance/tmt_cb_operate_test.h"

class QSttMacroParaEditViewCBOperate : public CSttMacroParaEditViewOriginal
{
	Q_OBJECT

public:
	QSttMacroParaEditViewCBOperate(QWidget *parent = 0);
	virtual ~QSttMacroParaEditViewCBOperate();

public:
	virtual char* GetMacroID(){return STT_ORG_MACRO_CBOperateTest; }

	void InitUI();						 //��ʼ������
	void InitFont();                     //��ʼ������
	void InitConnections();     
	void Initdates();
	virtual void GetDatas(CDataGroup *pParas);
	virtual void SetDatas(CDataGroup *pParas);
	virtual void startInit();
	virtual void stopInit();
	virtual void OnViewTestStart();
	virtual void OnViewTestStop();
	virtual void SerializeTestParas(CSttXmlSerializeBase *pMacroParas, PTMT_PARAS_HEAD pParas,
		long nVolRsNum,long nCurRsNum,long nBinExNum,long nBoutExNum,BOOL bHasGoosePub);
	virtual PTMT_PARAS_HEAD GetTestParas() { return &m_oCBOperateTest;}

	CString GetXYByImpedance(QString strXY,QString strAmp,QString strAngle);//���ݷ�ֵ��λ��xy����
	CString GetImpedanceByXY(QString strAmpAngle,CString strAmp,CString strAngle);//����xy�������ֵ��λ
public:
	QLabel *m_pLabFaultType;               //��������
	QLabel *m_pLabCurShortCircuit;		   //��·����
	QLabel *m_pLabZ;			           //|Z|
	QLabel *m_pLabVolShortCircuit;		   //��·��ѹ
	QLabel *m_pLabImpedanceAngle;		   //�迹��
	QLabel *m_pLabFaultDirection;          //���Ϸ���
	QLabel *m_pLabCurLoad;				   //���ɵ���
	QLabel *m_pLabFaultQuality;			   //��������
	QLabel *m_pLabPowerAngleLoad;		   //���ɹ���
	QLabel *m_pLabLarFaultTime;			   //������ʱ��
	QLabel *m_pLabFaultTrigTime;		   //���ϴ���ʱ��
	QLabel *m_pLabImpedanceWay;            //�迹��ʾ��ʽ
	QLabel *m_pLabConversionTime;		   //ת��ʱ��
	QLabel *m_pLabHour;					   //ʱ
	QLabel *m_pLabMinute;		           //��
	QLabel *m_pLabSecond;		           //��

	QRadioButton *m_pChkAmpAngle;          //��ֵ��λ
	QRadioButton *m_pChkRX;				   //R-X
	QSttCheckBox *m_pChkConversionFault;   //ת���Թ���
	QButtonGroup* m_ButtonGroup;

	QComboBox *m_pCmbFaultType;			   //��������
	QComboBox *m_pCmbFaultDirection;       //���Ϸ���
	QComboBox *m_pCmbFaultQuality;         //��������

	QLineEdit *m_pEditCurShortCircuit;	  //��·����
	QLineEdit *m_pEditZ;			      //|Z|
	QLineEdit *m_pEditVolShortCircuit;    //��·��ѹ
	QLineEdit *m_pEditImpedanceAngle;     //�迹��
	QLineEdit *m_pEditCurLoad;			  //���ɵ���
	QLineEdit *m_pEditPowerAngleLoad;	  //���ɹ���
	QLineEdit *m_pEditLarFaultTime;		  //������ʱ��
	QLineEdit *m_pEditConversionTime;	  //ת��ʱ��
	QLineEdit *m_pEditHour;               //ʱ
	QLineEdit *m_pEditMinute;		      //��
	QLineEdit *m_pEditSecond;		      //��

	QPushButton *m_pBtnResultAssess;      //�������
	QPushButton *m_pBtnCommonParas;       //ͨ�ò���

	QLabel *m_pLabRFaultType;               //��������
	QLabel *m_pLabRCurShortCircuit;		   //��·����
	QLabel *m_pLabRZ;			           //|Z|
	QLabel *m_pLabRVolShortCircuit;		   //��·��ѹ
	QLabel *m_pLabRImpedanceAngle;		   //�迹��
	QLabel *m_pLabRFaultDirection;          //���Ϸ���

	QComboBox *m_pCmbRFaultType;			   //��������
	QComboBox *m_pCmbRFaultDirection;       //���Ϸ���
	QLineEdit *m_pEditRCurShortCircuit;	  //��·����
	QLineEdit *m_pEditRZ;			      //|Z|
	QLineEdit *m_pEditRVolShortCircuit;    //��·��ѹ
	QLineEdit *m_pEditRImpedanceAngle;     //�迹��

	QWidget *m_pLeftWidget;
	QWidget *m_pRightWidget;
	QWidget *m_pBottomWidget;

	QGridLayout *m_pVlayout;
	QGridLayout *m_pLeftGridLayout;
	QGridLayout *m_pRightGridLayout;
	QGridLayout *m_pBottomGridLayout;
	QGroupBox *m_pGroupBox;
	QVBoxLayout *m_pGroupBoxLayout;

	CBOperateResultAssessGrid *m_pResultAssessWidget;
	CBOperateCommonParasDlg *m_pCommonParas;

	tmt_CBOperateTest m_oCBOperateTest;
	tmt_CBOperateParas *m_oCBOperateParas;
	tmt_Time m_oCBOTime;
	QStringList m_ItemsList;

	tmt_channel m_uiVOL[MAX_VOLTAGE_COUNT];
	tmt_channel m_uiCUR[MAX_CURRENT_COUNT];

public slots:
	void slot_ResultAssess();
	void slot_CommonParas();
	void slot_ConversionFault();
	void slot_ImpedanceChanged(bool);
	void slot_AmpAngle();
	void slot_RX();

	void slot_CmbFaultType(int nIndex);
	void slot_EditZ();
	void slot_EditImpedanceAngle();
	void slot_EditCurLoad();
	void slot_EditPowerAngleLoad();
	void slot_EditCurShortCircuit();
	void slot_EditVolShortCircuit();
	void slot_CmbFaultDirection(int nIndex);
	void slot_CmbFaultQuality(int nIndex);
	void slot_EditLarFaultTime();
	void slot_EditHour();
	void slot_EditMinute();
	void slot_EditSecond();
	void slot_ChkConversionFault();
	void slot_CmbRFaultType(int nIndex);
	void slot_EditConversionTime();
	void slot_EditRZ();
	void slot_EditRImpedanceAngle();
	void slot_EditRCurShortCircuit();
	void slot_EditRVolShortCircuit();
	void slot_CmbRFaultDirection(int nIndex);
};


#endif