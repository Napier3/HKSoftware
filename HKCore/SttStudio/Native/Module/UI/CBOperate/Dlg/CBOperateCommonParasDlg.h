#ifndef QCBOPERATEADDMULTCOMMONPARAS_H
#define QCBOPERATEADDMULTCOMMONPARAS_H

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QLabel>
#include <QTabWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include "../../../SttTest/Common/Impedance/tmt_cb_operate_test.h"

class CBOperateCommonParasDlg : public QDialog
{
	Q_OBJECT

public:
	CBOperateCommonParasDlg(tmt_CBOperateParas *pCBOperateParas ,QWidget *parent = 0);
	virtual ~CBOperateCommonParasDlg();            

public:
	QLabel *m_pLabPreFaultTime;        //����ǰʱ��(s)
	QLabel *m_pLabTimeAfterTrigger;    //�������������ʱ��(s)
	QLabel *m_pLabFaultTrigMode;       //���ϴ�����ʽ
	QLabel *m_pLabPTPos;			   //TV��װλ��
	QLabel *m_pLabCTPos;               //TA������
	QLabel *m_pLabTestProcess;		   //�������
	QLabel *m_pLabRecloseMode;         //�غϷ�ʽ
	QLabel *m_pLabAfterOpenTime;	   //�������������ʱ��(s)
	QLabel *m_pLabRecloseTime;         //�غϳ���ʱ��(s)
	QLabel *m_pLabAfterAccTime;        //����ٿ������������ʱ��(s)
	QLabel *m_pLabK0Mode;			   //���򲹳�ϵ����﷽ʽ
	QLabel *m_pLabKlKr;				   //���򲹳�ϵ��RMRL
	QLabel *m_pLabAngKx;               //���򲹳�ϵ��XMXL
	QLabel *m_pLabCalMode;             //���㷽ʽ
	QLabel *m_pLabZs;                  //ϵͳ�迹(��)
	QLabel *m_pLabZsPh;                //ϵͳ�迹��(��)
	QLabel *m_pLabSimulateBreakerDelay;//��·��ģ��
	QLabel *m_pLabBrkBreakTime;        //��բʱ�䣨s��
	QLabel *m_pLabBrkCloseTime;        //��բʱ�䣨s��
	QLabel *m_pLabFaultIncMode;        //��բ��ѡ��
	QLabel *m_pLabFaultAngle;          //��բ�ǣ��㣩
	QLabel *m_pLabBIPlusDC;            //���ӷ����ڷ���
	QLabel *m_pLabVzDefine;            //��ȡ��ѹ�������
	QLabel *m_pLabPsuVzRefPhase;       //��ȡ��ѹ�ο��ඨ��
	QLabel *m_pLabVzPh;                //��ȡ��ѹ���
	QLabel *m_pLabBinSelect;           //������ѡ��
	QLabel *m_pLabBinA;                //����A
	QLabel *m_pLabBinB;                //����B
	QLabel *m_pLabBinC;                //����C
	QLabel *m_pLabBinD;                //����D
	QLabel *m_pLabBinE;                //����E
	QLabel *m_pLabBinF;                //����F
	QLabel *m_pLabBinG;                //����G
	QLabel *m_pLabBinH;                //����H
	QLabel *m_pLabBoutA;               //����A
	QLabel *m_pLabBoutB;               //����B
	QLabel *m_pLabBoutC;               //����C
	QLabel *m_pLabBoutD;               //����D
	QLabel *m_pLabBoutE;               //����E
	QLabel *m_pLabBoutF;               //����F
	QLabel *m_pLabBoutG;               //����G
	QLabel *m_pLabBoutH;               //����H
	QLabel *m_pLabOutputSwitchMode;    //������ת������ʽ
	QLabel *m_pLabOutputKeepTime;      //��������ʱ��
	QLabel *m_pLabOutputDelayTime;     //������תʱ��

	QLineEdit *m_pEditPreFaultTime;    //����ǰʱ��(s)
	QLineEdit *m_pEditTimeAfterTrigger;//�������������ʱ��(s)
	QLineEdit *m_pEditAfterOpenTime;   //�������������ʱ��(s)
	QLineEdit *m_pEditRecloseTime;     //�غϳ���ʱ��(s)
	QLineEdit *m_pEditAfterAccTime;    //����ٿ������������ʱ��(s)
	QLineEdit *m_pEditKlKr;			   //���򲹳�ϵ��RMRL
	QLineEdit *m_pEditAngKx;           //���򲹳�ϵ��XMXL
	QLineEdit *m_pEditZs;              //ϵͳ�迹(��)
	QLineEdit *m_pEditZsPh;            //ϵͳ�迹��(��)
	QLineEdit *m_pEditBrkBreakTime;    //��բʱ�䣨s��
	QLineEdit *m_pEditBrkCloseTime;    //��բʱ�䣨s��
	QLineEdit *m_pEditFaultAngle;      //��բ�ǣ��㣩
	QLineEdit *m_pEditVzPh;            //��ȡ��ѹ���
	QLineEdit *m_pEditOutputKeepTime;  //��������ʱ��
	QLineEdit *m_pEditOutputDelayTime; //������תʱ��

	QComboBox *m_pCmbFaultTrigMode;       //���ϴ�����ʽ
	QComboBox *m_pCmbPTPos;			   //TV��װλ��
	QComboBox *m_pCmbCTPos;               //TA������
	QComboBox *m_pCmbTestProcess;		   //�������
	QComboBox *m_pCmbRecloseMode;         //�غϷ�ʽ
	QComboBox *m_pCmbK0Mode;			   //���򲹳�ϵ����﷽ʽ
	QComboBox *m_pCmbCalMode;             //���㷽ʽ
	QComboBox *m_pCmbSimulateBreakerDelay;//��·��ģ��
	QComboBox *m_pCmbFaultIncMode;        //��բ��ѡ��
	QComboBox *m_pCmbBIPlusDC;            //���ӷ����ڷ���
	QComboBox *m_pCmbVzDefine;            //��ȡ��ѹ�������
	QComboBox *m_pCmbPsuVzRefPhase;       //��ȡ��ѹ�ο��ඨ��
	QComboBox *m_pCmbBinSelect;           //������ѡ��
	QComboBox *m_pCmbBinA;                //����A
	QComboBox *m_pCmbBinB;                //����B
	QComboBox *m_pCmbBinC;                //����C
	QComboBox *m_pCmbBinD;                //����D
	QComboBox *m_pCmbBinE;                //����E
	QComboBox *m_pCmbBinF;                //����F
	QComboBox *m_pCmbBinG;                //����G
	QComboBox *m_pCmbBinH;                //����H
	QComboBox *m_pCmbBoutA;               //����A
	QComboBox *m_pCmbBoutB;               //����B
	QComboBox *m_pCmbBoutC;               //����C
	QComboBox *m_pCmbBoutD;               //����D
	QComboBox *m_pCmbBoutE;               //����E
	QComboBox *m_pCmbBoutF;               //����F
	QComboBox *m_pCmbBoutG;               //����G
	QComboBox *m_pCmbBoutH;               //����H
	QComboBox *m_pCmbOutputSwitchMode;    //������ת������ʽ

	QTabWidget *m_pCommonParas;
	QWidget *m_pGeneralParas;
	QWidget *m_pBinBout;

	QPushButton *m_pBtnOKCommonParas;
	QPushButton *m_pBtnCancelCommonParas;
	QPushButton *m_pBtnOKBinBout;
	QPushButton *m_pCancelBinBout;

	QGridLayout *m_pBinBoutLayout;
	QGridLayout *m_pGeneralParasLayout;
	QVBoxLayout *m_pMainLayout;
	QHBoxLayout *m_pBtnResultAssessLayout;
	QHBoxLayout *m_pBtnCommonParasLayout;

	QSpacerItem *m_pSpacerLeft;
	QSpacerItem *m_pSpacerRight;

	tmt_CBOperateTest m_oCBOperateTest;
	tmt_CBOperateParas *m_oCBOperateParas;

public:
	void InitUI();
	void InitFont();
	void Initdates();
	void InitConnections();

public slots:
	void slot_BinSelect(int nIndex);
	void slot_OutputSwitchMode(int nIndex);
	void slot_FaultTrigMode(int nIndex);
	void slot_TestProcess(int nIndex);
	void slot_CalMode(int nIndex);
	void slot_SimulateBreakerDelay(int nIndex);
	void slot_FaultIncMode(int nIndex);
	void slot_VzDefine(int nIndex);

	void slot_BtnOKCommonParas();
	void slot_BtnCancelCommonParas();
	void slot_BtnOKBinBout();
	void slot_CancelBinBout();

	void slot_EditPreFaultTime();
	void slot_EditTimeAfterTrigger();
	void slot_EditAfterOpenTime();
	void slot_EditRecloseTime();
	void slot_EditAfterAccTime();
	void slot_EditKlKr();
	void slot_EditAngKx();
	void slot_EditZs();
	void slot_EditZsPh();
	void slot_EditBrkBreakTime();
	void slot_EditBrkCloseTime();
	void slot_EditFaultAngle();
	void slot_EditVzPh();
	void slot_EditOutputKeepTime();
	void slot_EditOutputDelayTime();
	void slot_EditK0Mode(int nValue);
};

#endif