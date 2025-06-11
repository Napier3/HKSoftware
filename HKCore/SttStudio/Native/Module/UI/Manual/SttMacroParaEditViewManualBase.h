#ifndef SttMacroParaEditViewManualBase_H
#define SttMacroParaEditViewManualBase_H

#include "../Interface/SttMacroParaEditViewOriginal.h"
#include "../Controls/SttLineEdit.h"
#include "ManualView_Paras.h"
#include "ManualView_IV.h"
#include "QSttManualBinBoutDlg.h"
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QRadioButton>
#include <QLabel>
#include <QGroupBox>
#include "../Controls/SttCheckBox.h"
#include "../Module/ScrollCtrl/ScrollComboBox.h"
#include "../Controls/SttGroupBox.h"

class QSttMacroParaEditViewManualBase : public CSttMacroParaEditViewOriginal
{
    Q_OBJECT

public:
	QManualView_Paras m_oParas;
	QManualView_IV m_oIV;

	tmt_ManualParas *m_pManualParas;
	bool m_bIsChanging;//判断+和-按钮所造成的更改是否已经完成,未完成时不允许发送下一次SetItemPara
	CString m_strCbbChannel;//通道选择

public:
    explicit QSttMacroParaEditViewManualBase(QWidget *parent = 0);
    virtual ~QSttMacroParaEditViewManualBase();

private:
	virtual void SendUpdateParameter();
	virtual void InitBinaryInBinaryOutUI();
	virtual void InitOtherParasUI();
	virtual void SetManualOtherParasFont();
	virtual void InitStyle();

public:
	virtual void InitLanuage(){};
	virtual void CopyBinaryConfig(BOOL b=TRUE);
	virtual void InitBinStateOnStarting();
	virtual void InitConnect();
	virtual CSttTestResourceBase* CreateTestResource();
	virtual void SerializeTestParas(CSttXmlSerializeBase *pMacroParas, PTMT_PARAS_HEAD pParas,
		long nVolRsNum,long nCurRsNum,long nBinExNum,long nBoutExNum,BOOL bHasGoosePub);
	virtual bool PrepStartTest();//zhouhj 20230704 开始测试前的准备工作

	virtual void ClearResult(PTMT_PARAS_HEAD pHead);
	virtual void OnTestResults(CDataGroup *pResults);
	virtual void UpdateTestResource(BOOL bCreateChMaps);

	virtual void UpdateManualParas(bool bUpdateParasData = TRUE);

	virtual CString GetDefaultParaFile(){return _T("");}
	virtual bool IsValidTestParasFile(const CString& strParasFile,bool bOpen = true){return false;}
	virtual PTMT_PARAS_HEAD GetTestParas() { return NULL;}
	virtual char* GetMacroID() = 0;

	virtual void InitParasView(){};
    virtual void InitIVView();
	virtual void slot_SwitchStateChanged();

	virtual void OnViewTestLink(BOOL b);
	virtual void OnViewTestStart();
	virtual void OnViewTestStop();

	virtual void ShowReport(CDvmValues *pValues);
	virtual void GetDatas(CDataGroup *pParas);
	virtual void SetDatas(CDataGroup *pParas);

	virtual BOOL SetValues_dsRcdStep6U6I(CDvmDataset *pDsRcdStep6U6I);

	virtual CString GetMacroTestResultUnit();

signals:
	void sig_updataParas();

private slots:
	virtual void slot_currentChangedTabWidget(int nCurrIndex);
	void on_m_editIintVal_editingFinished();
	void on_m_editFinishVal_editingFinished();
	void on_m_editTime_editingFinished();
	void on_m_editStep_editingFinished();

protected slots:
	virtual void slot_updateParas();
	virtual void slot_ChannelTableItemValue(QString str,float fstep,int valueFlag,int AddOrMinus,bool bDC);
	virtual void slot_BinBoutStateChanged();
};


#endif // SttMacroParaEditViewManualBase_H
