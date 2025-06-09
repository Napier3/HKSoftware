#ifndef DIFFADDBATCHDLG_H
#define DIFFADDBATCHDLG_H

#include "SttMultiMacroDiffParasDefine.h"
#include "DiffResultEstimateDlg.h"
#include "../Distance/DistanceCommonParasDlg.h"
#include "../../UI/Module/QExBaseListGridBase/QExBaseListGridBase.h"
namespace Ui {
	class QDiffAddBatchDlg;
}
#define TIPS_DISPLAY_TIME	3000
//////////////////////////////////////////////////////////////////////////
//表格显示的结构体
class QDiffRateData : public CExBaseList
{
public:
	long* 	m_nPointNum;//记录每条线上的测试点数量
	float* m_fErrorBand;//记录误差带;

public:
	QDiffRateData() { m_nPointNum = m_nPointNum = NULL; }
	virtual ~QDiffRateData() {} //绑定值的地址,所以不需要析构
};

//曲线参数接口表
class QDiffCharGrid : public QExBaseListGridBase
{
	Q_OBJECT
private:

public:
	QDiffCharGrid(QWidget* pParent);
	virtual ~QDiffCharGrid();

public:
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow = TRUE);
};
//////////////////////////////////////////////////////////////////////////
class QDiffAddBatchDlg : public QDialog
{
	Q_OBJECT

public:
	explicit QDiffAddBatchDlg(QWidget *parent = 0);
	virtual ~QDiffAddBatchDlg();

private slots:

	void on_m_btnSave_clicked();
	void on_m_btnClose_clicked();

	void on_m_txtTime_lr_editingFinished();
    void on_m_txtTime_ld_editingFinished();
	void on_m_txtMaxFaultTime_editingFinished();

	void on_m_check_Rate_clicked(bool checked);
	void on_m_check_Harm_clicked(bool checked);
	void on_m_check_Time_clicked(bool checked);

	void on_m_check_AN_clicked(bool checked);
	void on_m_check_BN_clicked(bool checked);
	void on_m_check_CN_clicked(bool checked);
	void on_m_check_AB_clicked(bool checked);
	void on_m_check_BC_clicked(bool checked);
	void on_m_check_CA_clicked(bool checked);
	void on_m_check_ABC_clicked(bool checked);
	void UpdateMinaxis(int nMinaxis);//0:有名值(A) 1:标幺值(In)

	void on_m_btnResEvaluat_clicked();
	void on_tabWidget_currentChanged(int index);
public:
	CDataGroup *m_pCurrDataGroup;
	QDiffCharGrid *m_pRateGrid;
	QDiffCharGrid *m_pHarmGrid;
	CExBaseList m_oRateList;
	CExBaseList m_oHarmList;
	long  m_nHarmCustomPoint;
	long m_nPointNum[5];//记录每条线上的测试点数量
	float m_fErrorBand[5];//记录误差带
	long m_nLineChecked[5];//记录每条线是否在特性曲线中被选中
private:
	Ui::QDiffAddBatchDlg *m_pAddMult_UI;

	void SetValueToPage(CDvmData *pData);
	void GetPageToValue(CDvmData *pData);
	void InitUI();
	void SetApplyTips(CString strTips);
	void timerEvent(QTimerEvent* ev);
	bool CheckSectionState();
	bool CheckFuncState();
	void CheckAllPresence();
	int m_nTipsTime;//页面提示计时ID
	void DiffCheckForPresence(CString strID);
	void SetDiffCharGrid();
	void GetDateFromCurrDataGroup(CDataGroup *pParas);

public:
	void SetDatas(CDataGroup *pParas);
	void GetDatas(CDataGroup *pParas);

};

#endif // DIFFADDBATCHDLG_H
