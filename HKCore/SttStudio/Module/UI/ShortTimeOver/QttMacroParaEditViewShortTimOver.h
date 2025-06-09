#ifndef QTTMACROPARAEDITVIEWSHORTTIMOVER_H
#define QTTMACROPARAEDITVIEWSHORTTIMOVER_H

#include <QDialog>
#include "../Interface/SttMacroParaEditViewOriginal.h"
#include "../../Module/SttTest/Common/tmt_short_time_over_test.h"
#include "../Module/ScrollCtrl/ScrollComboBox.h"
#include "../Module/ChannelParaset/QBasicTestParaSet.h"

#include "../Interface/SttMacroParaEditViewOriginal.h"
#include "../Controls/SttLineEdit.h"
#include "../Module/CommonCtrl_QT/SttDiffCurrCalDlg.h"
#include <QWidget>
#include <QTabWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QRadioButton>
#include <QLabel>
#include <QGroupBox>

#include "../Controls/SttCheckBox.h"
#include "../Module/ScrollCtrl/ScrollComboBox.h"


namespace Ui
{ 
	class QttMacroParaEditViewShortTimOver; 
}

#define FILE_SHORTTIMEOVERTEST		"ShortTimeOverTest"
#define POSTFIX_SHORTTIMEOVERTEST    "sttxml"

class QttMacroParaEditViewShortTimOver : public CSttMacroParaEditViewOriginal
{
    Q_OBJECT

public:
    explicit QttMacroParaEditViewShortTimOver(QWidget *parent = 0);
    ~QttMacroParaEditViewShortTimOver();

public:
    Ui::QttMacroParaEditViewShortTimOver *ui;

public:
	CSttTestResourceBase *m_pParaSetSttTestResource;
	tmt_ShortTimeOver_Test m_oSTOverTest;
	tmt_ShortTimeOver_Para* m_pSTOverPara;

	float m_fCurrentAmp;

	int m_nVolChRsNum,m_nCurChRsNum;

	float m_fVolInflictFload,				m_fCurInflictFload;			//ʩ�ӱ���
	long m_nVolInflictCount,				m_nCurInflictCount;			//ʩ�Ӵ���
	float m_fVolOnceInflictTime,			m_fCurOnceInflictTime;	//����ʩ��ʱ��
	float m_fVolIntervalTime,				m_fCurIntervalTime;			//����ʩ�Ӽ��
	float m_fVolTotalTime,					m_fCurTotalTime;				//������ʱ��


	virtual PTMT_PARAS_HEAD GetTestParas(){ return &m_oSTOverTest;};
	virtual void SerializeTestParas(CSttXmlSerializeBase *pMacroParas, PTMT_PARAS_HEAD pParas,
		long nVolRsNum,long nCurRsNum,long nBinExNum,long nBoutExNum,BOOL bHasGoosePub);

	virtual void SerializeTestParas_Base(CSttXmlSerializeBase *pMacroParas, PTMT_PARAS_HEAD pParas,
		long nVolRsNum,long nCurRsNum,long nBinExNum,long nBoutExNum,BOOL bHasGoosePub, BOOL bSmvAbnormal,BOOL bGooseAbnormal);

	virtual void OnViewTestLink(BOOL b=FALSE);
	virtual void OnViewTestStart();
	virtual void OnViewTestStop();
	virtual void UpdatePrimParaSetUI(){}//20240923 suyang ���½���һ��ֵ/����ֵ��ʾ
	virtual BOOL IsUseSecondParaSet(){ return TRUE; }//20240923 suyang �Ƿ���ʾ����ֵ	


public:
	int m_nVChNums,m_nIChNums;
	//QTabWidget* m_tabWidget;
	QBasicTestParaSet* m_pUIParaWidget;		//��ѹ��������
	void InitUI();
	void InitTab_UI();
	//void InitUIGrid();

	void InitData();
	void UpdateData();
	virtual void UpdateTestResource(BOOL bCreateChMaps);

	/*virtual void initUI_Paras(bool bSmvAbnormal);*/
	virtual void UpdateStateParas_Base();
	virtual void UpdateStateParas();

	virtual void GetDatas(CDataGroup *pParas);
	virtual void SetDatas(CDataGroup *pDataset);
	virtual void ShowReport(CDvmValues *pValues);


public:
	virtual char* GetMacroID(){ return "ShortTimeOverTest"; }
	/*virtual CString GetDefaultParaFile();
	virtual bool IsValidTestParasFile(const CString& strParasFile,bool bOpen = true);*/

	void UpdateChsAmp(tmt_Channel* pChannel, float fFload, BOOL isVol);
	void UpdateChsAmpEx(tmt_Channel* pChannel);
	void UpdateTotalTime();
	void SetParasFont();
	void ChsAmpInRange();


public slots:

	void on_m_edtInflictFloadChanged();
	void om_m_btnSTOverStateChanged();
	void on_m_cmbInflictCount_currentIndexChanged(int index);
	void on_m_edtOnceInflictTimeChanged();
	void on_m_edtIntervalTimeChanged();
	void slot_updateParas();
};

extern QttMacroParaEditViewShortTimOver* g_pShortTimeOverTest;

#endif // QTTMACROPARAEDITVIEWSHORTTIMOVER_H
