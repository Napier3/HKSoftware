#include "CBOperateCommonParasDlg.h"

#include "../Module/SttGlobalDef.h"
#include "../../SttTestCntrFrameBase.h"

CBOperateCommonParasDlg::CBOperateCommonParasDlg(tmt_CBOperateParas *pCBOperateParas ,QWidget *parent) : QDialog(parent)
{

	m_oCBOperateParas = pCBOperateParas;

	InitUI();
	InitFont();
	InitConnections();
}

CBOperateCommonParasDlg::~CBOperateCommonParasDlg()
{

}

void CBOperateCommonParasDlg::InitUI()
{
	setWindowFlags(Qt::CustomizeWindowHint|Qt::WindowTitleHint| Qt::Dialog);
	m_pCommonParas = new QTabWidget(this);
	m_pGeneralParas = new QWidget(this);
	m_pBinBout = new QWidget(this);

    m_pCommonParas->addTab(m_pGeneralParas, _T("ͨ�ò���"));

    m_pLabPreFaultTime = new QLabel(_T("����ǰʱ��(s)"),this);                //����ǰʱ��(s)
    m_pLabTimeAfterTrigger = new QLabel(_T("�������������ʱ��(s)"),this);    //�������������ʱ��(s)
    m_pLabFaultTrigMode = new QLabel(_T("���ϴ�����ʽ"),this);                //���ϴ�����ʽ
    m_pLabPTPos = new QLabel(_T("TV��װλ��"),this);			              //TV��װλ��
    m_pLabCTPos = new QLabel(_T("TA������"),this);                            //TA������
    m_pLabTestProcess = new QLabel(_T("�������"),this);		              //�������
    m_pLabRecloseMode = new QLabel(_T("�غϷ�ʽ"),this);                      //�غϷ�ʽ
    m_pLabAfterOpenTime = new QLabel(_T("�������������ʱ��(s)"),this);	      //�������������ʱ��(s)
    m_pLabRecloseTime = new QLabel(_T("�غϳ���ʱ��(s)"),this);               //�غϳ���ʱ��(s)
    m_pLabAfterAccTime = new QLabel(_T("����ٿ������������ʱ��(s)"),this);  //����ٿ������������ʱ��(s)
    m_pLabK0Mode = new QLabel(_T("���򲹳�ϵ����﷽ʽ"),this);			      //���򲹳�ϵ����﷽ʽ
	m_pLabKlKr = new QLabel(this);				      //���򲹳�ϵ��RMRL
	m_pLabAngKx = new QLabel(this);               //���򲹳�ϵ��XMXL

	m_pEditPreFaultTime = new QLineEdit(this);    //����ǰʱ��(s)
	m_pEditTimeAfterTrigger = new QLineEdit(this);//�������������ʱ��(s)
	m_pCmbFaultTrigMode = new QComboBox(this);    //���ϴ�����ʽ
    m_pCmbFaultTrigMode->addItem("ʱ�䴥��");
    m_pCmbFaultTrigMode->addItem("�ֶ�����");
    m_pCmbFaultTrigMode->addItem("����������");
    m_pCmbFaultTrigMode->addItem("GPS��B�봥��");

	m_pCmbPTPos = new QComboBox(this);			  //TV��װλ��
    m_pCmbPTPos->addItem("ĸ�߲�");
    m_pCmbPTPos->addItem("��·��");

	m_pCmbCTPos = new QComboBox(this);	          //TA������
    m_pCmbCTPos->addItem("ָ��ĸ��");
    m_pCmbCTPos->addItem("ָ����·");

	m_pCmbTestProcess = new QComboBox(this);	  //�������
    m_pCmbTestProcess->addItem("�����źſ���");
    m_pCmbTestProcess->addItem("ʱ�����");

	m_pCmbRecloseMode = new QComboBox(this);	  //�غϷ�ʽ
    m_pCmbRecloseMode->addItem("����");
    m_pCmbRecloseMode->addItem("����");
    m_pCmbRecloseMode->addItem("���غ�");

	m_pEditAfterOpenTime = new QLineEdit(this);   //�������������ʱ��(s)
	m_pEditRecloseTime = new QLineEdit(this);     //�غϳ���ʱ��(s)
	m_pEditAfterAccTime = new QLineEdit(this);    //����ٿ������������ʱ��(s)
	m_pCmbK0Mode = new QComboBox(this);			  //���򲹳�ϵ����﷽ʽ
	m_pCmbK0Mode->addItem("|K0|,Phi(K0)");
	m_pCmbK0Mode->addItem("RERL,XEXL");
	m_pCmbK0Mode->addItem("|Z0/Z1|,Phi(Z0/Z1)");

	m_pEditKlKr = new QLineEdit(this);			  //���򲹳�ϵ��RMRL
	m_pEditAngKx = new QLineEdit(this);           //���򲹳�ϵ��XMXL

    m_pLabCalMode = new QLabel(_T("���㷽ʽ"),this);                  //���㷽ʽ
    m_pLabZs = new QLabel(_T("ϵͳ�迹(��)"),this);                  //ϵͳ�迹(��)
    m_pLabZsPh = new QLabel(_T("ϵͳ�迹��(��)"),this);                //ϵͳ�迹��(��)
    m_pLabSimulateBreakerDelay = new QLabel(_T("��·��ģ��"),this);//��·��ģ��
    m_pLabBrkBreakTime = new QLabel(_T("��բʱ��(ms)"),this);        //��բʱ��(ms)
    m_pLabBrkCloseTime = new QLabel(_T("��բʱ��(ms)"),this);        //��բʱ��(ms)
    m_pLabFaultIncMode = new QLabel(_T("��բ��ѡ��"),this);        //��բ��ѡ��
    m_pLabFaultAngle = new QLabel(_T("��բ��(��)"),this);          //��բ��(��)
    m_pLabBIPlusDC = new QLabel(_T("���ӷ����ڷ���"),this);            //���ӷ����ڷ���
    m_pLabVzDefine = new QLabel(_T("��ȡ��ѹ�������"),this);            //��ȡ��ѹ�������
    m_pLabPsuVzRefPhase = new QLabel(_T("��ȡ��ѹ�ο��ඨ��"),this);       //��ȡ��ѹ�ο��ඨ��
    m_pLabVzPh = new QLabel(_T("��ȡ��ѹ���"),this);                //��ȡ��ѹ���

	m_pCmbCalMode = new QComboBox(this);             //���㷽ʽ
    m_pCmbCalMode->addItem("��������");
    m_pCmbCalMode->addItem("��ѹ����");
    m_pCmbCalMode->addItem("ϵͳ�迹����");

	m_pEditZs = new QLineEdit(this);              //ϵͳ�迹(��)
	m_pEditZsPh = new QLineEdit(this);            //ϵͳ�迹��(��)
	m_pCmbSimulateBreakerDelay = new QComboBox(this);//��·��ģ��
    m_pCmbSimulateBreakerDelay->addItem("ģ��");
    m_pCmbSimulateBreakerDelay->addItem("��ģ��");

	m_pEditBrkBreakTime = new QLineEdit(this);    //��բʱ��(ms)
	m_pEditBrkCloseTime = new QLineEdit(this);    //��բʱ��(ms)
	m_pCmbFaultIncMode = new QComboBox(this);        //��բ��ѡ��
    m_pCmbFaultIncMode->addItem("���");
    m_pCmbFaultIncMode->addItem("��ֵ");

	m_pEditFaultAngle = new QLineEdit(this);      //��բ��(��)
	m_pCmbBIPlusDC = new QComboBox(this);            //���ӷ����ڷ���
    m_pCmbBIPlusDC->addItem("��");
    m_pCmbBIPlusDC->addItem("��");

	m_pCmbVzDefine = new QComboBox(this);            //��ȡ��ѹ�������
	m_pCmbVzDefine->addItem("0");
	m_pCmbVzDefine->addItem("Ua");
	m_pCmbVzDefine->addItem("Ub");
	m_pCmbVzDefine->addItem("Uc");
	m_pCmbVzDefine->addItem("��3x3U0");
	m_pCmbVzDefine->addItem("-��3x3U0");
	m_pCmbVzDefine->addItem("3U0");
	m_pCmbVzDefine->addItem("-3U0");

	m_pCmbPsuVzRefPhase = new QComboBox(this);       //��ȡ��ѹ�ο��ඨ��
    m_pCmbPsuVzRefPhase->addItem("Ua��λ");
    m_pCmbPsuVzRefPhase->addItem("Ub��λ");
    m_pCmbPsuVzRefPhase->addItem("Uc��λ");
    m_pCmbPsuVzRefPhase->addItem("Uab��λ");
    m_pCmbPsuVzRefPhase->addItem("Ubc��λ");
    m_pCmbPsuVzRefPhase->addItem("Uca��λ");

	m_pEditVzPh = new QLineEdit(this);            //��ȡ��ѹ���
	m_pGeneralParasLayout = new QGridLayout(m_pGeneralParas);

	m_pGeneralParasLayout->addWidget(m_pLabPreFaultTime, 0, 0);
	m_pGeneralParasLayout->addWidget(m_pLabTimeAfterTrigger, 1, 0);
	m_pGeneralParasLayout->addWidget(m_pLabFaultTrigMode, 2, 0);
	m_pGeneralParasLayout->addWidget(m_pLabPTPos, 3, 0);
	m_pGeneralParasLayout->addWidget(m_pLabCTPos, 4, 0);
	m_pGeneralParasLayout->addWidget(m_pLabTestProcess, 5, 0);
	m_pGeneralParasLayout->addWidget(m_pLabRecloseMode, 6, 0);
	m_pGeneralParasLayout->addWidget(m_pLabAfterOpenTime, 7, 0);
	m_pGeneralParasLayout->addWidget(m_pLabRecloseTime, 8, 0);
	m_pGeneralParasLayout->addWidget(m_pLabAfterAccTime, 9, 0);
	m_pGeneralParasLayout->addWidget(m_pLabK0Mode, 10, 0);
	m_pGeneralParasLayout->addWidget(m_pLabKlKr, 11, 0);
	m_pGeneralParasLayout->addWidget(m_pLabAngKx, 12, 0);


	m_pGeneralParasLayout->addWidget(m_pEditPreFaultTime, 0, 1);
	m_pGeneralParasLayout->addWidget(m_pEditTimeAfterTrigger, 1, 1);
	m_pGeneralParasLayout->addWidget(m_pCmbFaultTrigMode, 2, 1);
	m_pGeneralParasLayout->addWidget(m_pCmbPTPos, 3, 1);
	m_pGeneralParasLayout->addWidget(m_pCmbCTPos, 4, 1);
	m_pGeneralParasLayout->addWidget(m_pCmbTestProcess, 5, 1);
	m_pGeneralParasLayout->addWidget(m_pCmbRecloseMode, 6, 1);
	m_pGeneralParasLayout->addWidget(m_pEditAfterOpenTime, 7, 1);
	m_pGeneralParasLayout->addWidget(m_pEditRecloseTime, 8, 1);
	m_pGeneralParasLayout->addWidget(m_pEditAfterAccTime, 9, 1);
	m_pGeneralParasLayout->addWidget(m_pCmbK0Mode, 10, 1);
	m_pGeneralParasLayout->addWidget(m_pEditKlKr, 11, 1);
	m_pGeneralParasLayout->addWidget(m_pEditAngKx, 12, 1);

	m_pGeneralParasLayout->addWidget(m_pLabCalMode, 0, 2);
	m_pGeneralParasLayout->addWidget(m_pLabZs, 1, 2);
	m_pGeneralParasLayout->addWidget(m_pLabZsPh, 2, 2);
	m_pGeneralParasLayout->addWidget(m_pLabSimulateBreakerDelay, 3, 2);
	m_pGeneralParasLayout->addWidget(m_pLabBrkBreakTime, 4, 2);
	m_pGeneralParasLayout->addWidget(m_pLabBrkCloseTime, 5, 2);
	m_pGeneralParasLayout->addWidget(m_pLabFaultIncMode, 6, 2);
	m_pGeneralParasLayout->addWidget(m_pLabFaultAngle, 7, 2);
	m_pGeneralParasLayout->addWidget(m_pLabBIPlusDC, 8, 2);
	m_pGeneralParasLayout->addWidget(m_pLabVzDefine, 9, 2);
	m_pGeneralParasLayout->addWidget(m_pLabPsuVzRefPhase, 10, 2);
	m_pGeneralParasLayout->addWidget(m_pLabVzPh, 11, 2);

	m_pGeneralParasLayout->addWidget(m_pCmbCalMode, 0, 3);
	m_pGeneralParasLayout->addWidget(m_pEditZs, 1, 3);
	m_pGeneralParasLayout->addWidget(m_pEditZsPh, 2, 3);
	m_pGeneralParasLayout->addWidget(m_pCmbSimulateBreakerDelay, 3, 3);
	m_pGeneralParasLayout->addWidget(m_pEditBrkBreakTime, 4, 3);
	m_pGeneralParasLayout->addWidget(m_pEditBrkCloseTime, 5, 3);
	m_pGeneralParasLayout->addWidget(m_pCmbFaultIncMode, 6, 3);
	m_pGeneralParasLayout->addWidget(m_pEditFaultAngle, 7, 3);
	m_pGeneralParasLayout->addWidget(m_pCmbBIPlusDC, 8, 3);
	m_pGeneralParasLayout->addWidget(m_pCmbVzDefine, 9, 3);
	m_pGeneralParasLayout->addWidget(m_pCmbPsuVzRefPhase, 10, 3);
	m_pGeneralParasLayout->addWidget(m_pEditVzPh, 11, 3);

    m_pBtnOKCommonParas = new QPushButton(_T("ȷ��"));
    m_pBtnCancelCommonParas = new QPushButton(_T("ȡ��"));
	m_pBtnCommonParasLayout = new QHBoxLayout;
	m_pBtnOKCommonParas->setFixedWidth(100);
	m_pBtnCancelCommonParas->setFixedWidth(100);
	m_pBtnCommonParasLayout->addWidget(m_pBtnOKCommonParas);
	m_pBtnCommonParasLayout->addWidget(m_pBtnCancelCommonParas);

	m_pGeneralParasLayout->addLayout(m_pBtnCommonParasLayout, 13, 1, 1, 2, Qt::AlignCenter);
	m_pGeneralParas->setLayout(m_pGeneralParasLayout);

    m_pCommonParas->addTab(m_pBinBout, _T("������"));
	m_pBinBoutLayout = new QGridLayout();
	QStringList BinList;
    BinList  << "����" << "����" << "�غ�";
	QStringList BoutList;
    BoutList  << "�Ͽ�" << "�պ�";
    m_pLabBinSelect= new QLabel(_T("����ѡ��"),this);            //������ѡ��
    m_pLabBinA= new QLabel(_T("����A"),this);                      //����A
    m_pLabBinB= new QLabel(_T("����B"),this);                      //����B
    m_pLabBinC= new QLabel(_T("����C"),this);                      //����C
    m_pLabBinD= new QLabel(_T("����D"),this);                      //����D
    m_pLabBinE= new QLabel(_T("����E"),this);                      //����E
    m_pLabBinF= new QLabel(_T("����F"),this);                      //����F
    m_pLabBinG= new QLabel(_T("����G"),this);                      //����G
    m_pLabBinH= new QLabel(_T("����H"),this);                      //����H

	m_pCmbBinSelect = new QComboBox(this);           //������ѡ��
    m_pCmbBinSelect->addItem("����A-B-C-D");
    m_pCmbBinSelect->addItem("����E-F-G-H");
	m_pCmbBinA = new QComboBox(this);                //����A
	m_pCmbBinB = new QComboBox(this);                //����B
	m_pCmbBinC = new QComboBox(this);                //����C
	m_pCmbBinD = new QComboBox(this);                //����D
	m_pCmbBinE = new QComboBox(this);                //����E
	m_pCmbBinF = new QComboBox(this);                //����F
	m_pCmbBinG = new QComboBox(this);                //����G
	m_pCmbBinH = new QComboBox(this);                //����H
	m_pCmbBinA->addItems(BinList);
	m_pCmbBinB->addItems(BinList);
	m_pCmbBinC->addItems(BinList);
	m_pCmbBinD->addItems(BinList);
	m_pCmbBinE->addItems(BinList);
	m_pCmbBinF->addItems(BinList);
	m_pCmbBinG->addItems(BinList);
	m_pCmbBinH->addItems(BinList);

    m_pLabBoutA= new QLabel(_T("����1"),this);               //����1
    m_pLabBoutB= new QLabel(_T("����2"),this);               //����2
    m_pLabBoutC= new QLabel(_T("����3"),this);               //����3
    m_pLabBoutD= new QLabel(_T("����4"),this);               //����4
    m_pLabBoutE= new QLabel(_T("����5"),this);               //����5
    m_pLabBoutF= new QLabel(_T("����6"),this);               //����6
    m_pLabBoutG= new QLabel(_T("����7"),this);               //����7
    m_pLabBoutH= new QLabel(_T("����8"),this);               //����8
    m_pLabOutputSwitchMode= new QLabel(_T("������ת������ʽ"),this);//������ת������ʽ
    m_pLabOutputKeepTime= new QLabel(_T("��������ʱ��"),this);      //��������ʱ��
    m_pLabOutputDelayTime= new QLabel(_T("������תʱ��"),this);     //������תʱ��

	m_pCmbBoutA = new QComboBox(this);               //����A
	m_pCmbBoutB = new QComboBox(this);               //����B
	m_pCmbBoutC = new QComboBox(this);               //����C
	m_pCmbBoutD = new QComboBox(this);               //����D
	m_pCmbBoutE = new QComboBox(this);               //����E
	m_pCmbBoutF = new QComboBox(this);               //����F
	m_pCmbBoutG = new QComboBox(this);               //����G
	m_pCmbBoutH = new QComboBox(this);               //����H
	m_pCmbBoutA->addItems(BoutList);
	m_pCmbBoutB->addItems(BoutList);
	m_pCmbBoutC->addItems(BoutList);
	m_pCmbBoutD->addItems(BoutList);
	m_pCmbBoutE->addItems(BoutList);
	m_pCmbBoutF->addItems(BoutList);
	m_pCmbBoutG->addItems(BoutList);
	m_pCmbBoutH->addItems(BoutList);

	m_pCmbOutputSwitchMode = new QComboBox(this);    //������ת������ʽ
    m_pCmbOutputSwitchMode->addItem("ʱ������");
    m_pCmbOutputSwitchMode->addItem("����������");
	m_pEditOutputKeepTime = new QLineEdit(this);     //��������ʱ��
	m_pEditOutputDelayTime = new QLineEdit(this);    //������תʱ��

	m_pBinBoutLayout->addWidget(m_pLabBinSelect, 0, 0);
	m_pBinBoutLayout->addWidget(m_pLabBinA, 1, 0);
	m_pBinBoutLayout->addWidget(m_pLabBinB, 2, 0);
	m_pBinBoutLayout->addWidget(m_pLabBinC, 3, 0);
	m_pBinBoutLayout->addWidget(m_pLabBinD, 4, 0);
	m_pBinBoutLayout->addWidget(m_pLabBinE, 5, 0);
	m_pBinBoutLayout->addWidget(m_pLabBinF, 6, 0);
	m_pBinBoutLayout->addWidget(m_pLabBinG, 7, 0);
	m_pBinBoutLayout->addWidget(m_pLabBinH, 8, 0);

	m_pCmbBinSelect->setMinimumWidth(270);

	m_pBinBoutLayout->addWidget(m_pCmbBinSelect, 0, 1);
	m_pBinBoutLayout->addWidget(m_pCmbBinA, 1, 1);
	m_pBinBoutLayout->addWidget(m_pCmbBinB, 2, 1);
	m_pBinBoutLayout->addWidget(m_pCmbBinC, 3, 1);
	m_pBinBoutLayout->addWidget(m_pCmbBinD, 4, 1);
	m_pBinBoutLayout->addWidget(m_pCmbBinE, 5, 1);
	m_pBinBoutLayout->addWidget(m_pCmbBinF, 6, 1);
	m_pBinBoutLayout->addWidget(m_pCmbBinG, 7, 1);
	m_pBinBoutLayout->addWidget(m_pCmbBinH, 8, 1);

	m_pBinBoutLayout->addWidget(m_pLabBoutA, 0, 2);
	m_pBinBoutLayout->addWidget(m_pLabBoutB, 1, 2);
	m_pBinBoutLayout->addWidget(m_pLabBoutC, 2, 2);
	m_pBinBoutLayout->addWidget(m_pLabBoutD, 3, 2);
	m_pBinBoutLayout->addWidget(m_pLabBoutE, 4, 2);
	m_pBinBoutLayout->addWidget(m_pLabBoutF, 5, 2);
	m_pBinBoutLayout->addWidget(m_pLabBoutG, 6, 2);
	m_pBinBoutLayout->addWidget(m_pLabBoutH, 7, 2);
	m_pBinBoutLayout->addWidget(m_pLabOutputSwitchMode, 8, 2);
	m_pBinBoutLayout->addWidget(m_pLabOutputKeepTime, 9, 2);
	m_pBinBoutLayout->addWidget(m_pLabOutputDelayTime, 10, 2);

	m_pBinBoutLayout->addWidget(m_pCmbBoutA, 0, 3);
	m_pBinBoutLayout->addWidget(m_pCmbBoutB, 1, 3);
	m_pBinBoutLayout->addWidget(m_pCmbBoutC, 2, 3);
	m_pBinBoutLayout->addWidget(m_pCmbBoutD, 3, 3);
	m_pBinBoutLayout->addWidget(m_pCmbBoutE, 4, 3);
	m_pBinBoutLayout->addWidget(m_pCmbBoutF, 5, 3);
	m_pBinBoutLayout->addWidget(m_pCmbBoutG, 6, 3);
	m_pBinBoutLayout->addWidget(m_pCmbBoutH, 7, 3);
	m_pBinBoutLayout->addWidget(m_pCmbOutputSwitchMode, 8, 3);
	m_pBinBoutLayout->addWidget(m_pEditOutputKeepTime, 9, 3);
	m_pBinBoutLayout->addWidget(m_pEditOutputDelayTime, 10, 3);
	
    m_pBtnOKBinBout = new QPushButton(_T("ȷ��"));
    m_pCancelBinBout = new QPushButton(_T("ȡ��"));
	m_pBtnOKBinBout->setFixedWidth(100);
	m_pCancelBinBout->setFixedWidth(100);
	m_pBtnResultAssessLayout = new QHBoxLayout;
	m_pSpacerLeft = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed);
	m_pSpacerRight = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed);

	// �����൯�ɿؼ���ȷ����ť��ȡ����ť���Ҳ൯�ɿؼ���ˮƽ������
	m_pBtnResultAssessLayout->addItem(m_pSpacerLeft);
	m_pBtnResultAssessLayout->addWidget(m_pBtnOKBinBout);
	m_pBtnResultAssessLayout->addWidget(m_pCancelBinBout);
	m_pBtnResultAssessLayout->addItem(m_pSpacerRight);

	m_pMainLayout = new QVBoxLayout;
	m_pMainLayout->addLayout(m_pBinBoutLayout);
    m_pMainLayout->addLayout(m_pBtnResultAssessLayout);

	m_pBinBout->setLayout(m_pMainLayout);

	m_pCommonParas->setFixedSize(800, 600); // ���ù̶���С

	m_pCmbBinA->setEnabled(true);                
	m_pCmbBinB->setEnabled(true);                
	m_pCmbBinC->setEnabled(true);               
	m_pCmbBinD->setEnabled(true);               
	m_pCmbBinE->setEnabled(false);               
	m_pCmbBinF->setEnabled(false);                
	m_pCmbBinG->setEnabled(false);               
	m_pCmbBinH->setEnabled(false);    

	m_pCmbRecloseMode->setEnabled(false);
	m_pEditAfterOpenTime->setEnabled(false);
	m_pEditRecloseTime->setEnabled(false);
	m_pEditAfterAccTime->setEnabled(false);

	m_pEditZs->setEnabled(false);
	m_pEditZsPh->setEnabled(false);
	m_pEditFaultAngle->setEnabled(false);
	m_pCmbPsuVzRefPhase->setEnabled(false);
	m_pEditVzPh->setEnabled(false);
	Initdates();
}

void CBOperateCommonParasDlg::InitFont()
{
	m_pCommonParas->setFont(*g_pSttGlobalFont);
	m_pGeneralParas->setFont(*g_pSttGlobalFont);
	m_pBinBout->setFont(*g_pSttGlobalFont);
	m_pLabPreFaultTime->setFont(*g_pSttGlobalFont);        //����ǰʱ��(s)
	m_pLabTimeAfterTrigger->setFont(*g_pSttGlobalFont);    //�������������ʱ��(s)
	m_pLabFaultTrigMode->setFont(*g_pSttGlobalFont);       //���ϴ�����ʽ
	m_pLabPTPos->setFont(*g_pSttGlobalFont);			   //TV��װλ��
	m_pLabCTPos->setFont(*g_pSttGlobalFont);               //TA������
	m_pLabTestProcess->setFont(*g_pSttGlobalFont);		   //�������
	m_pLabRecloseMode->setFont(*g_pSttGlobalFont);         //�غϷ�ʽ
	m_pLabAfterOpenTime->setFont(*g_pSttGlobalFont);	   //�������������ʱ��(s)
	m_pLabRecloseTime->setFont(*g_pSttGlobalFont);         //�غϳ���ʱ��(s)
	m_pLabAfterAccTime->setFont(*g_pSttGlobalFont);        //����ٿ������������ʱ��(s)
	m_pLabK0Mode->setFont(*g_pSttGlobalFont);			   //���򲹳�ϵ����﷽ʽ
	m_pLabKlKr->setFont(*g_pSttGlobalFont);				   //���򲹳�ϵ��RMRL
	m_pLabAngKx->setFont(*g_pSttGlobalFont);               //���򲹳�ϵ��XMXL
	m_pLabCalMode->setFont(*g_pSttGlobalFont);             //���㷽ʽ
	m_pLabZs->setFont(*g_pSttGlobalFont);                  //ϵͳ�迹(��)
	m_pLabZsPh->setFont(*g_pSttGlobalFont);                //ϵͳ�迹��(��)
	m_pLabSimulateBreakerDelay->setFont(*g_pSttGlobalFont);//��·��ģ��
	m_pLabBrkBreakTime->setFont(*g_pSttGlobalFont);        //��բʱ�䣨s��
	m_pLabBrkCloseTime->setFont(*g_pSttGlobalFont);        //��բʱ�䣨s��
	m_pLabFaultIncMode->setFont(*g_pSttGlobalFont);        //��բ��ѡ��
	m_pLabFaultAngle->setFont(*g_pSttGlobalFont);          //��բ�ǣ��㣩
	m_pLabBIPlusDC->setFont(*g_pSttGlobalFont);            //���ӷ����ڷ���
	m_pLabVzDefine->setFont(*g_pSttGlobalFont);            //��ȡ��ѹ�������
	m_pLabPsuVzRefPhase->setFont(*g_pSttGlobalFont);       //��ȡ��ѹ�ο��ඨ��
	m_pLabVzPh->setFont(*g_pSttGlobalFont);                //��ȡ��ѹ���
	m_pLabBinSelect->setFont(*g_pSttGlobalFont);           //������ѡ��
	m_pLabBinA->setFont(*g_pSttGlobalFont);                //����A
	m_pLabBinB->setFont(*g_pSttGlobalFont);                //����B
	m_pLabBinC->setFont(*g_pSttGlobalFont);                //����C
	m_pLabBinD->setFont(*g_pSttGlobalFont);                //����D
	m_pLabBinE->setFont(*g_pSttGlobalFont);                //����E
	m_pLabBinF->setFont(*g_pSttGlobalFont);                //����F
	m_pLabBinG->setFont(*g_pSttGlobalFont);                //����G
	m_pLabBinH->setFont(*g_pSttGlobalFont);                //����H
	m_pLabBoutA->setFont(*g_pSttGlobalFont);               //����A
	m_pLabBoutB->setFont(*g_pSttGlobalFont);               //����B
	m_pLabBoutC->setFont(*g_pSttGlobalFont);               //����C
	m_pLabBoutD->setFont(*g_pSttGlobalFont);               //����D
	m_pLabBoutE->setFont(*g_pSttGlobalFont);               //����E
	m_pLabBoutF->setFont(*g_pSttGlobalFont);               //����F
	m_pLabBoutG->setFont(*g_pSttGlobalFont);               //����G
	m_pLabBoutH->setFont(*g_pSttGlobalFont);               //����H
	m_pLabOutputSwitchMode->setFont(*g_pSttGlobalFont);    //������ת������ʽ
	m_pLabOutputKeepTime->setFont(*g_pSttGlobalFont);      //��������ʱ��
	m_pLabOutputDelayTime->setFont(*g_pSttGlobalFont);     //������תʱ��

	m_pEditPreFaultTime->setFont(*g_pSttGlobalFont);    //����ǰʱ��(s)
	m_pEditTimeAfterTrigger->setFont(*g_pSttGlobalFont);//�������������ʱ��(s)
	m_pEditAfterOpenTime->setFont(*g_pSttGlobalFont);   //�������������ʱ��(s)
	m_pEditRecloseTime->setFont(*g_pSttGlobalFont);     //�غϳ���ʱ��(s)
	m_pEditAfterAccTime->setFont(*g_pSttGlobalFont);    //����ٿ������������ʱ��(s)
	m_pEditKlKr->setFont(*g_pSttGlobalFont);			//���򲹳�ϵ��RMRL
	m_pEditAngKx->setFont(*g_pSttGlobalFont);           //���򲹳�ϵ��XMXL
	m_pEditZs->setFont(*g_pSttGlobalFont);              //ϵͳ�迹(��)
	m_pEditZsPh->setFont(*g_pSttGlobalFont);            //ϵͳ�迹��(��)
	m_pEditBrkBreakTime->setFont(*g_pSttGlobalFont);    //��բʱ�䣨s��
	m_pEditBrkCloseTime->setFont(*g_pSttGlobalFont);    //��բʱ�䣨s��
	m_pEditFaultAngle->setFont(*g_pSttGlobalFont);      //��բ�ǣ��㣩
	m_pEditVzPh->setFont(*g_pSttGlobalFont);            //��ȡ��ѹ���
	m_pEditOutputKeepTime->setFont(*g_pSttGlobalFont);  //��������ʱ��
	m_pEditOutputDelayTime->setFont(*g_pSttGlobalFont); //������תʱ��

	m_pCmbFaultTrigMode->setFont(*g_pSttGlobalFont);       //���ϴ�����ʽ
	m_pCmbPTPos->setFont(*g_pSttGlobalFont);			   //TV��װλ��
	m_pCmbCTPos->setFont(*g_pSttGlobalFont);               //TA������
	m_pCmbTestProcess->setFont(*g_pSttGlobalFont);		   //�������
	m_pCmbRecloseMode->setFont(*g_pSttGlobalFont);         //�غϷ�ʽ
	m_pCmbK0Mode->setFont(*g_pSttGlobalFont);			   //���򲹳�ϵ����﷽ʽ
	m_pCmbCalMode->setFont(*g_pSttGlobalFont);             //���㷽ʽ
	m_pCmbSimulateBreakerDelay->setFont(*g_pSttGlobalFont);//��·��ģ��
	m_pCmbFaultIncMode->setFont(*g_pSttGlobalFont);        //��բ��ѡ��
	m_pCmbBIPlusDC->setFont(*g_pSttGlobalFont);            //���ӷ����ڷ���
	m_pCmbVzDefine->setFont(*g_pSttGlobalFont);            //��ȡ��ѹ�������
	m_pCmbPsuVzRefPhase->setFont(*g_pSttGlobalFont);       //��ȡ��ѹ�ο��ඨ��
	m_pCmbBinSelect->setFont(*g_pSttGlobalFont);           //������ѡ��
	m_pCmbBinA->setFont(*g_pSttGlobalFont);                //����A
	m_pCmbBinB->setFont(*g_pSttGlobalFont);                //����B
	m_pCmbBinC->setFont(*g_pSttGlobalFont);                //����C
	m_pCmbBinD->setFont(*g_pSttGlobalFont);                //����D
	m_pCmbBinE->setFont(*g_pSttGlobalFont);                //����E
	m_pCmbBinF->setFont(*g_pSttGlobalFont);                //����F
	m_pCmbBinG->setFont(*g_pSttGlobalFont);                //����G
	m_pCmbBinH->setFont(*g_pSttGlobalFont);                //����H
	m_pCmbBoutA->setFont(*g_pSttGlobalFont);               //����A
	m_pCmbBoutB->setFont(*g_pSttGlobalFont);               //����B
	m_pCmbBoutC->setFont(*g_pSttGlobalFont);               //����C
	m_pCmbBoutD->setFont(*g_pSttGlobalFont);               //����D
	m_pCmbBoutE->setFont(*g_pSttGlobalFont);               //����E
	m_pCmbBoutF->setFont(*g_pSttGlobalFont);               //����F
	m_pCmbBoutG->setFont(*g_pSttGlobalFont);               //����G
	m_pCmbBoutH->setFont(*g_pSttGlobalFont);               //����H
	m_pCmbOutputSwitchMode->setFont(*g_pSttGlobalFont);    //������ת������ʽ

	m_pBtnOKCommonParas->setFont(*g_pSttGlobalFont);
	m_pBtnCancelCommonParas->setFont(*g_pSttGlobalFont);
	m_pBtnOKBinBout->setFont(*g_pSttGlobalFont);
	m_pCancelBinBout->setFont(*g_pSttGlobalFont);

}

void CBOperateCommonParasDlg::Initdates()
{
	m_pEditPreFaultTime->setText(QString::number(m_oCBOperateParas->m_fPreFaultTime, 'f', 3)); 
	m_pEditTimeAfterTrigger->setText(QString::number(m_oCBOperateParas->m_fPostFaultTime, 'f', 3));
	m_pCmbFaultTrigMode->setCurrentIndex(m_oCBOperateParas->m_nFaultTrigMode); 
	m_pCmbPTPos->setCurrentIndex(m_oCBOperateParas->m_nPTPoint); 
	m_pCmbCTPos->setCurrentIndex(m_oCBOperateParas->m_nCTPoint); 
	m_pCmbTestProcess->setCurrentIndex(m_oCBOperateParas->m_nTestProcCtrlMode); 
	m_pCmbRecloseMode->setCurrentIndex(m_oCBOperateParas->m_nRecloseMode); 
	m_pEditAfterOpenTime->setText(QString::number(m_oCBOperateParas->m_fPostFaultTime, 'f', 3));
	m_pEditRecloseTime->setText(QString::number(m_oCBOperateParas->m_fRecloseTime, 'f', 3));
	m_pEditAfterAccTime->setText(QString::number(m_oCBOperateParas->m_fTAfterAccTrig, 'f', 3));
	m_pCmbK0Mode->setCurrentIndex(m_oCBOperateParas->m_nK0CalMode); 
	m_pEditKlKr->setText(QString::number(m_oCBOperateParas->m_fK0Amp, 'f', 3));
	m_pEditAngKx->setText(QString::number(m_oCBOperateParas->m_fK0Angle, 'f', 3));
	m_pCmbCalMode->setCurrentIndex(m_oCBOperateParas->m_nCalMode); 
	m_pEditZs->setText(QString::number(m_oCBOperateParas->m_fZs, 'f', 3));
	m_pEditZsPh->setText(QString::number(m_oCBOperateParas->m_fPhis, 'f', 3));
	m_pCmbSimulateBreakerDelay->setCurrentIndex(m_oCBOperateParas->m_bCBSimulation);
	m_pEditBrkBreakTime->setText(QString::number(m_oCBOperateParas->m_fCBTripTime, 'f', 3));
	m_pEditBrkCloseTime->setText(QString::number(m_oCBOperateParas->m_fCBCloseTime, 'f', 3));
	m_pCmbFaultIncMode->setCurrentIndex(m_oCBOperateParas->m_nFaultIncMode);
	m_pEditFaultAngle->setText(QString::number(m_oCBOperateParas->m_fFaultAngle, 'f', 3));
	m_pCmbBIPlusDC->setCurrentIndex(m_oCBOperateParas->m_bIPlusDC);
	m_pCmbVzDefine->setCurrentIndex(m_oCBOperateParas->m_nVzDefine);
	m_pCmbPsuVzRefPhase->setCurrentIndex(m_oCBOperateParas->m_nVzPhDefine);
	m_pEditVzPh->setText(QString::number(m_oCBOperateParas->m_fUxInput_Ang, 'f', 3));
	m_pCmbBinSelect->setCurrentIndex(m_oCBOperateParas->m_nBinSelect);
	m_pCmbBinA->setCurrentIndex(m_oCBOperateParas->m_nDInputState[0]);
	m_pCmbBinB->setCurrentIndex(m_oCBOperateParas->m_nDInputState[1]);
	m_pCmbBinC->setCurrentIndex(m_oCBOperateParas->m_nDInputState[2]);
	m_pCmbBinD->setCurrentIndex(m_oCBOperateParas->m_nDInputState[3]);
	m_pCmbBinE->setCurrentIndex(m_oCBOperateParas->m_nDInputState[4]);
	m_pCmbBinF->setCurrentIndex(m_oCBOperateParas->m_nDInputState[5]);
	m_pCmbBinG->setCurrentIndex(m_oCBOperateParas->m_nDInputState[6]);
	m_pCmbBinH->setCurrentIndex(m_oCBOperateParas->m_nDInputState[7]);
	m_pCmbBoutA->setCurrentIndex(m_oCBOperateParas->m_nStateBOut[0]);
	m_pCmbBoutB->setCurrentIndex(m_oCBOperateParas->m_nStateBOut[1]);
	m_pCmbBoutC->setCurrentIndex(m_oCBOperateParas->m_nStateBOut[2]);
	m_pCmbBoutD->setCurrentIndex(m_oCBOperateParas->m_nStateBOut[3]);
	m_pCmbBoutE->setCurrentIndex(m_oCBOperateParas->m_nStateBOut[4]);
	m_pCmbBoutF->setCurrentIndex(m_oCBOperateParas->m_nStateBOut[5]);
	m_pCmbBoutG->setCurrentIndex(m_oCBOperateParas->m_nStateBOut[6]);
	m_pCmbBoutH->setCurrentIndex(m_oCBOperateParas->m_nStateBOut[7]);
	m_pCmbOutputSwitchMode->setCurrentIndex(m_oCBOperateParas->m_nOutputSwitchMode);
	m_pEditOutputKeepTime->setText(QString::number(m_oCBOperateParas->m_fBoutHoldTime, 'f', 3));
	m_pEditOutputDelayTime->setText(QString::number(m_oCBOperateParas->m_fBoutTimeTrig, 'f', 3));
	slot_EditK0Mode(m_oCBOperateParas->m_nK0CalMode);
	slot_BinSelect(m_oCBOperateParas->m_nBinSelect);
}


void CBOperateCommonParasDlg::InitConnections()
{
	connect(m_pCmbBinSelect,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_BinSelect(int)));
	connect(m_pCmbOutputSwitchMode,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_OutputSwitchMode(int)));
	connect(m_pCmbFaultTrigMode,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_FaultTrigMode(int)));
	connect(m_pCmbTestProcess,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_TestProcess(int)));
    connect(m_pCmbCalMode,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_CalMode(int)));
	connect(m_pCmbSimulateBreakerDelay,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_SimulateBreakerDelay(int)));
	connect(m_pCmbFaultIncMode,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_FaultIncMode(int)));
	connect(m_pCmbVzDefine,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_VzDefine(int)));

	connect(m_pBtnOKCommonParas,SIGNAL(clicked()),this,SLOT(slot_BtnOKCommonParas()));
	connect(m_pBtnCancelCommonParas,SIGNAL(clicked()),this,SLOT(slot_BtnCancelCommonParas()));
	connect(m_pBtnOKBinBout,SIGNAL(clicked()),this,SLOT(slot_BtnOKBinBout()));
	connect(m_pCancelBinBout,SIGNAL(clicked()),this,SLOT(slot_CancelBinBout()));

	connect(m_pEditPreFaultTime,SIGNAL(editingFinished()),this,SLOT(slot_EditPreFaultTime()));
	connect(m_pEditTimeAfterTrigger,SIGNAL(editingFinished()),this,SLOT(slot_EditTimeAfterTrigger()));
	connect(m_pEditAfterOpenTime,SIGNAL(editingFinished()),this,SLOT(slot_EditAfterOpenTime()));
	connect(m_pEditRecloseTime,SIGNAL(editingFinished()),this,SLOT(slot_EditRecloseTime()));
	connect(m_pEditAfterAccTime,SIGNAL(editingFinished()),this,SLOT(slot_EditAfterAccTime()));
	connect(m_pEditKlKr,SIGNAL(editingFinished()),this,SLOT(slot_EditKlKr()));
	connect(m_pEditAngKx,SIGNAL(editingFinished()),this,SLOT(slot_EditAngKx()));
	connect(m_pEditZs,SIGNAL(editingFinished()),this,SLOT(slot_EditZs()));
	connect(m_pEditZsPh,SIGNAL(editingFinished()),this,SLOT(slot_EditZsPh()));
	connect(m_pEditBrkBreakTime,SIGNAL(editingFinished()),this,SLOT(slot_EditBrkBreakTime()));
	connect(m_pEditBrkCloseTime,SIGNAL(editingFinished()),this,SLOT(slot_EditBrkCloseTime()));
	connect(m_pEditFaultAngle,SIGNAL(editingFinished()),this,SLOT(slot_EditFaultAngle()));
	connect(m_pEditVzPh,SIGNAL(editingFinished()),this,SLOT(slot_EditVzPh()));
	connect(m_pEditOutputKeepTime,SIGNAL(editingFinished()),this,SLOT(slot_EditOutputKeepTime()));
	connect(m_pEditOutputDelayTime,SIGNAL(editingFinished()),this,SLOT(slot_EditOutputDelayTime()));
	connect(m_pCmbK0Mode,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_EditK0Mode(int)));
}

void CBOperateCommonParasDlg::slot_BinSelect(int nIndex)
{
	if (nIndex == 0)
	{
		m_pCmbBinA->setEnabled(true);                
		m_pCmbBinB->setEnabled(true);                
		m_pCmbBinC->setEnabled(true);               
		m_pCmbBinD->setEnabled(true);               
		m_pCmbBinE->setEnabled(false);               
		m_pCmbBinF->setEnabled(false);                
		m_pCmbBinG->setEnabled(false);               
		m_pCmbBinH->setEnabled(false);               
	}
	if (nIndex == 1)
	{
		m_pCmbBinA->setEnabled(false);                
		m_pCmbBinB->setEnabled(false);                
		m_pCmbBinC->setEnabled(false);               
		m_pCmbBinD->setEnabled(false);               
		m_pCmbBinE->setEnabled(true);               
		m_pCmbBinF->setEnabled(true);                
		m_pCmbBinG->setEnabled(true);               
		m_pCmbBinH->setEnabled(true); 
	}
}

void CBOperateCommonParasDlg::slot_OutputSwitchMode(int nIndex)
{
	if (nIndex == 0)
	{
		m_pEditOutputDelayTime->setEnabled(true);
	}
	if (nIndex == 1)
	{
		m_pEditOutputDelayTime->setEnabled(false);
	}
}

void CBOperateCommonParasDlg::slot_FaultTrigMode(int nIndex)
{
	if (nIndex == 0)
	{
		m_pEditPreFaultTime->setEnabled(true);
	}
	if (nIndex == 1)
	{
		m_pEditPreFaultTime->setEnabled(false);
	}
	if (nIndex == 2)
	{
		m_pEditPreFaultTime->setEnabled(false);
	}
	if (nIndex == 3)
	{
		m_pEditPreFaultTime->setEnabled(false);
	}
}

void CBOperateCommonParasDlg::slot_TestProcess(int nIndex)
{
	if (nIndex == 0)
	{
		m_pCmbRecloseMode->setEnabled(false);
		m_pEditAfterOpenTime->setEnabled(false);
		m_pEditRecloseTime->setEnabled(false);
		m_pEditAfterAccTime->setEnabled(false);
		m_pEditTimeAfterTrigger->setEnabled(true);
	}
	if (nIndex == 1)
	{
		m_pCmbRecloseMode->setEnabled(true);
		m_pEditAfterOpenTime->setEnabled(true);
		m_pEditRecloseTime->setEnabled(true);
		m_pEditAfterAccTime->setEnabled(true);
		m_pEditTimeAfterTrigger->setEnabled(false);
	}

}

void CBOperateCommonParasDlg::slot_CalMode(int nIndex)
{
	if (nIndex == 0)
	{
		m_pEditZs->setEnabled(false);
		m_pEditZsPh->setEnabled(false);
	}
	if (nIndex == 1)
	{
		m_pEditZs->setEnabled(false);
		m_pEditZsPh->setEnabled(false);
	}
	if (nIndex == 2)
	{
		m_pEditZs->setEnabled(true);
		m_pEditZsPh->setEnabled(true);
	}
}

void CBOperateCommonParasDlg::slot_SimulateBreakerDelay(int nIndex)
{
	if (nIndex == 0)
	{
		m_pEditBrkBreakTime->setEnabled(true);
		m_pEditBrkCloseTime->setEnabled(true);
	}
	if (nIndex == 1)
	{
		m_pEditBrkBreakTime->setEnabled(false);
		m_pEditBrkCloseTime->setEnabled(false);
	}
}

void CBOperateCommonParasDlg::slot_FaultIncMode(int nIndex)
{
	if (nIndex == 0)
	{
		m_pEditFaultAngle->setEnabled(false);
	}
	if (nIndex == 1)
	{
		m_pEditFaultAngle->setEnabled(true);
	}
}

void CBOperateCommonParasDlg::slot_VzDefine(int nIndex)
{
	if (nIndex == 0 || nIndex == 4 || nIndex == 5 || nIndex == 6 || nIndex == 7)
	{
		m_pCmbPsuVzRefPhase->setEnabled(false);
		m_pEditVzPh->setEnabled(false);
	}
	if (nIndex == 1 || nIndex == 2 || nIndex == 3)
	{
		m_pCmbPsuVzRefPhase->setEnabled(true);
		m_pEditVzPh->setEnabled(true);
	}
}

void CBOperateCommonParasDlg::slot_BtnOKCommonParas()
{
	m_oCBOperateParas->m_fPreFaultTime = m_pEditPreFaultTime->text().toFloat(); 
	m_oCBOperateParas->m_fPostFaultTime = m_pEditTimeAfterTrigger->text().toFloat();
	m_oCBOperateParas->m_nFaultTrigMode = m_pCmbFaultTrigMode->currentIndex();
	m_oCBOperateParas->m_nPTPoint = m_pCmbPTPos->currentIndex();
	m_oCBOperateParas->m_nCTPoint = m_pCmbCTPos->currentIndex();
	m_oCBOperateParas->m_nTestProcCtrlMode = m_pCmbTestProcess->currentIndex();
	m_oCBOperateParas->m_nRecloseMode = m_pCmbRecloseMode->currentIndex();
	m_oCBOperateParas->m_fPostFaultTime  = m_pEditAfterOpenTime->text().toFloat();;
	m_oCBOperateParas->m_fRecloseTime = m_pEditRecloseTime->text().toFloat();
	m_oCBOperateParas->m_fAfterAcceTime = m_pEditAfterAccTime->text().toFloat();
	m_oCBOperateParas->m_nK0CalMode = m_pCmbK0Mode->currentIndex();
	m_oCBOperateParas->m_fK0Amp = m_pEditKlKr->text().toFloat();
	m_oCBOperateParas->m_fK0Angle = m_pEditAngKx->text().toFloat();
	m_oCBOperateParas->m_nCalMode = m_pCmbCalMode->currentIndex();

	m_oCBOperateParas->m_fZs = m_pEditZs->text().toFloat();
	m_oCBOperateParas->m_fPhis = m_pEditZsPh->text().toFloat();
	int nValue = m_pCmbSimulateBreakerDelay->currentIndex();
	m_oCBOperateParas->m_bCBSimulation = nValue;

	m_oCBOperateParas->m_fCBTripTime = m_pEditBrkBreakTime->text().toFloat();
	m_oCBOperateParas->m_fCBCloseTime = m_pEditBrkCloseTime->text().toFloat();
	m_oCBOperateParas->m_nFaultIncMode = m_pCmbFaultIncMode->currentIndex();
	m_oCBOperateParas->m_fFaultAngle = m_pEditFaultAngle->text().toFloat();
	m_oCBOperateParas->m_bIPlusDC = m_pCmbBIPlusDC->currentIndex();
	m_oCBOperateParas->m_nVzDefine = m_pCmbVzDefine->currentIndex();
	m_oCBOperateParas->m_nVzPhDefine = m_pCmbPsuVzRefPhase->currentIndex();
	m_oCBOperateParas->m_fUxInput_Ang = m_pEditVzPh->text().toFloat();

	accept();
}

void CBOperateCommonParasDlg::slot_BtnCancelCommonParas()
{
	reject();
}

void CBOperateCommonParasDlg::slot_BtnOKBinBout()
{
	m_oCBOperateParas->m_nBinSelect = m_pCmbBinSelect->currentIndex();
	m_oCBOperateParas->m_nDInputState[0] = m_pCmbBinA->currentIndex();
	m_oCBOperateParas->m_nDInputState[1] = m_pCmbBinB->currentIndex();
	m_oCBOperateParas->m_nDInputState[2] = m_pCmbBinC->currentIndex();
	m_oCBOperateParas->m_nDInputState[3] = m_pCmbBinD->currentIndex();
	m_oCBOperateParas->m_nDInputState[4] = m_pCmbBinE->currentIndex();
	m_oCBOperateParas->m_nDInputState[5] = m_pCmbBinF->currentIndex();
	m_oCBOperateParas->m_nDInputState[6] = m_pCmbBinG->currentIndex();
	m_oCBOperateParas->m_nDInputState[7] = m_pCmbBinH->currentIndex();

	m_oCBOperateParas->m_nStateBOut[0] = m_pCmbBoutA->currentIndex();
	m_oCBOperateParas->m_nStateBOut[1] = m_pCmbBoutB->currentIndex();
	m_oCBOperateParas->m_nStateBOut[2] = m_pCmbBoutC->currentIndex();
	m_oCBOperateParas->m_nStateBOut[3] = m_pCmbBoutD->currentIndex();
	m_oCBOperateParas->m_nStateBOut[4] = m_pCmbBoutE->currentIndex();
	m_oCBOperateParas->m_nStateBOut[5] = m_pCmbBoutF->currentIndex();
	m_oCBOperateParas->m_nStateBOut[6] = m_pCmbBoutG->currentIndex();
	m_oCBOperateParas->m_nStateBOut[7] = m_pCmbBoutH->currentIndex();

	m_oCBOperateParas->m_nOutputSwitchMode = m_pCmbOutputSwitchMode->currentIndex();
	m_oCBOperateParas->m_fBoutHoldTime = m_pEditOutputKeepTime->text().toFloat();
	m_oCBOperateParas->m_fBoutTimeTrig = m_pEditOutputDelayTime->text().toFloat();

	accept();
}

void CBOperateCommonParasDlg::slot_CancelBinBout()
{
	reject();
}

void CBOperateCommonParasDlg::slot_EditPreFaultTime()
{
	float fv = m_pEditPreFaultTime->text().toFloat();
	fv = setLimit(0,100000.000,fv);
	m_pEditPreFaultTime->setText(QString::number(fv, 'f', 3));
}
void CBOperateCommonParasDlg::slot_EditTimeAfterTrigger()
{
	float fv = m_pEditTimeAfterTrigger->text().toFloat();
	fv = setLimit(0,100000.000,fv);
	m_pEditTimeAfterTrigger->setText(QString::number(fv, 'f', 3));
}
void CBOperateCommonParasDlg::slot_EditAfterOpenTime()
{
	float fv = m_pEditAfterOpenTime->text().toFloat();
	fv = setLimit(0,100000.000,fv);
	m_pEditAfterOpenTime->setText(QString::number(fv, 'f', 3));
}
void CBOperateCommonParasDlg::slot_EditRecloseTime()
{
	float fv = m_pEditRecloseTime->text().toFloat();
	fv = setLimit(0,100000.000,fv);
	m_pEditRecloseTime->setText(QString::number(fv, 'f', 3));
}
void CBOperateCommonParasDlg::slot_EditAfterAccTime()
{
	float fv = m_pEditAfterAccTime->text().toFloat();
	fv = setLimit(0,100000.000,fv);
	m_pEditAfterAccTime->setText(QString::number(fv, 'f', 3));
}
void CBOperateCommonParasDlg::slot_EditKlKr()
{
	float fv = m_pEditKlKr->text().toFloat();
	fv = setLimit(0,100000.000,fv);
	m_pEditKlKr->setText(QString::number(fv, 'f', 3));
}
void CBOperateCommonParasDlg::slot_EditAngKx()
{
	float fv = m_pEditAngKx->text().toFloat();
	fv = setLimit(0,100000.000,fv);
	m_pEditAngKx->setText(QString::number(fv, 'f', 3));
}
void CBOperateCommonParasDlg::slot_EditZs()
{
	float fv = m_pEditZs->text().toFloat();
	fv = setLimit(0,10000.000,fv);
	m_pEditZs->setText(QString::number(fv, 'f', 3));
}
void CBOperateCommonParasDlg::slot_EditZsPh()
{
	float fv = m_pEditZsPh->text().toFloat();
	fv = setLimit(-360.0,360.0,fv);
	m_pEditZsPh->setText(QString::number(fv, 'f', 3));
}
void CBOperateCommonParasDlg::slot_EditBrkBreakTime()
{
	int fv = m_pEditBrkBreakTime->text().toInt();
	fv = setLimit(0,100000,fv);
	m_pEditBrkBreakTime->setText(QString::number(fv));
}
void CBOperateCommonParasDlg::slot_EditBrkCloseTime()
{
	int fv = m_pEditBrkCloseTime->text().toInt();
	fv = setLimit(0,100000,fv);
	m_pEditBrkCloseTime->setText(QString::number(fv));
}
void CBOperateCommonParasDlg::slot_EditFaultAngle()
{
	float fv = m_pEditFaultAngle->text().toFloat();
	fv = setLimit(-360.0,360.0,fv);
	m_pEditFaultAngle->setText(QString::number(fv, 'f', 3));
}
void CBOperateCommonParasDlg::slot_EditVzPh()
{
	float fv = m_pEditVzPh->text().toFloat();
	fv = setLimit(-360.0,360.0,fv);
	m_pEditVzPh->setText(QString::number(fv, 'f', 3));
}
void CBOperateCommonParasDlg::slot_EditOutputKeepTime()
{
	float fv = m_pEditOutputKeepTime->text().toFloat();
	fv = setLimit(0,100000.000,fv);
	m_pEditOutputKeepTime->setText(QString::number(fv, 'f', 3));
}
void CBOperateCommonParasDlg::slot_EditOutputDelayTime()
{
	float fv = m_pEditOutputDelayTime->text().toFloat();
	fv = setLimit(0,100000.000,fv);
	m_pEditOutputDelayTime->setText(QString::number(fv, 'f', 3));
}

void CBOperateCommonParasDlg::slot_EditK0Mode(int nValue)
{
	if (nValue == 0)
	{
		m_pLabKlKr->setText(_T("|KO|"));
		m_pLabAngKx->setText(_T("Phi(KO)"));
	}
	if (nValue == 1)
	{
		m_pLabKlKr->setText(_T("RERL"));
		m_pLabAngKx->setText(_T("XEXL"));
	}
	if (nValue == 2)
	{
		m_pLabKlKr->setText(_T("|Z0/Z1|"));
		m_pLabAngKx->setText(_T("phi(Z0/Z1)"));
	}
}
