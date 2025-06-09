#ifndef DIFFADDSEARCHLINEDLG_H
#define DIFFADDSEARCHLINEDLG_H

#include "../Distance/DistanceCommonParasDlg.h"
#include "SttMultiMacroDiffParasDefine.h"
#include "DiffResultEstimateDlg.h"
namespace Ui {
	class QDiffAddSearchLineDlg;
}
#define TIPS_DISPLAY_TIME	3000
class QDiffAddSearchLineDlg : public QDialog
{
	Q_OBJECT

public:
	explicit QDiffAddSearchLineDlg(QWidget *parent = 0);
	virtual ~QDiffAddSearchLineDlg();

	private slots:

	void on_m_btnSave_clicked();
	void on_m_btnClose_clicked();

	void on_m_txtSL_BeginVal_editingFinished();
    void on_m_txtSL_EndVal_editingFinished();
	void on_m_txtSL_Step_editingFinished();
	void on_m_txtSL_Time_editingFinished();
	void on_m_txtSL_Points_editingFinished();
	void on_m_cmbErrorLogic_currentIndexChanged(int index);
	void on_m_editActAbsErr_editingFinished();
	void on_m_editActRelErr_editingFinished();

	void on_m_check_AN_clicked(bool checked);
	void on_m_check_BN_clicked(bool checked);
	void on_m_check_CN_clicked(bool checked);
	void on_m_check_AB_clicked(bool checked);
	void on_m_check_BC_clicked(bool checked);
	void on_m_check_CA_clicked(bool checked);
	void on_m_check_ABC_clicked(bool checked);
	void UpdateMinaxis(int nMinaxis);//0:����ֵ(A) 1:����ֵ(In)

public:
	CDataGroup *m_pCurrDataGroup;

	double m_dBeginVal;
	double m_dEndVal;
	double	m_dStep;
	double m_dTime;
	int m_nPoints;

	int m_nErrorLogic;			//����߼�
	double m_dAbsErr;			//���������-�������
	double m_dRelErr;			//���������-������
	bool m_Isbcheck_FaultType[7];

	

private:
	Ui::QDiffAddSearchLineDlg *m_pAddMult_UI;

	void SetValueToPage(CDvmData *pData);
	void GetPageToValue(CDvmData *pData);
	void InitUI();

	void SetApplyTips(CString strTips);
	void timerEvent(QTimerEvent* ev);

	bool CheckSectionState();
	void DiffCheckForPresence(CString strID);
	void CheckAllPresence();
	int m_nTipsTime;//ҳ����ʾ��ʱID
public:
	void SetDatas(CDataGroup *pParas);
	void GetDatas(CDataGroup *pParas);
	void UpdatePoints();//���²��Ե���
};

#endif // DIFFADDSEARCHLINEDLG_H
