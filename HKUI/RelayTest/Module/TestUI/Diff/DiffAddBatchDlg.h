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
//�����ʾ�Ľṹ��
class QDiffRateData : public CExBaseList
{
public:
	long* 	m_nPointNum;//��¼ÿ�����ϵĲ��Ե�����
	float* m_fErrorBand;//��¼����;

public:
	QDiffRateData() { m_nPointNum = m_nPointNum = NULL; }
	virtual ~QDiffRateData() {} //��ֵ�ĵ�ַ,���Բ���Ҫ����
};

//���߲����ӿڱ�
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
	void UpdateMinaxis(int nMinaxis);//0:����ֵ(A) 1:����ֵ(In)

	void on_m_btnResEvaluat_clicked();
	void on_tabWidget_currentChanged(int index);
public:
	CDataGroup *m_pCurrDataGroup;
	QDiffCharGrid *m_pRateGrid;
	QDiffCharGrid *m_pHarmGrid;
	CExBaseList m_oRateList;
	CExBaseList m_oHarmList;
	long  m_nHarmCustomPoint;
	long m_nPointNum[5];//��¼ÿ�����ϵĲ��Ե�����
	float m_fErrorBand[5];//��¼����
	long m_nLineChecked[5];//��¼ÿ�����Ƿ������������б�ѡ��
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
	int m_nTipsTime;//ҳ����ʾ��ʱID
	void DiffCheckForPresence(CString strID);
	void SetDiffCharGrid();
	void GetDateFromCurrDataGroup(CDataGroup *pParas);

public:
	void SetDatas(CDataGroup *pParas);
	void GetDatas(CDataGroup *pParas);

};

#endif // DIFFADDBATCHDLG_H
