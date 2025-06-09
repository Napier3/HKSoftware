#ifndef SYNBINARYSDLG_H
#define SYNBINARYSDLG_H

#include <QDialog>
#include "SttMultiMacroSynParasDefine.h"
#include "../../../../Module/DataMngr/DataGroup.h"
#include "../../SttCmd/GuideBook/SttMacroTest.h"

namespace Ui {
class QSynBinarysDlg;
}

class QSynBinarysDlg : public QDialog
{
    Q_OBJECT

public:
    explicit QSynBinarysDlg(QWidget *parent = 0);
    ~QSynBinarysDlg();

	void SetDatas(CExBaseList *pParas);
	void GetDatas(CExBaseList *pParas);
	void UpdataAllBinarys(CExBaseList *pParas);
    BOOL CheckItemsModify(CExBaseList *pAllItems);
	void SetBinBoutName();//根据开入开出映射设置开关量界面显示值20240930 gongyiping

	int nBinSyn; //20241017 gongyiping 同期信号
private slots:
    void on_m_cmbKStart_currentIndexChanged(int index);
    void on_m_lineCloseTime_editingFinished();
    void on_m_cmbBout1_currentIndexChanged(int index);
    void on_m_cmbBout2_currentIndexChanged(int index);
    void on_m_cmbBout3_currentIndexChanged(int index);
    void on_m_cmbBinSyn_currentIndexChanged(int index);
    void on_m_cmbBinIncV_currentIndexChanged(int index);
    void on_m_cmbBinDecV_currentIndexChanged(int index);
    void on_m_cmbBinIncF_currentIndexChanged(int index);
    void on_m_cmbBinDecF_currentIndexChanged(int index);
    void on_m_btnOK_clicked();
    void on_m_btnCancel_clicked();

private:
    Ui::QSynBinarysDlg *ui;

	CExBaseList *m_pParas;
    int m_nModify;

	void SetValueToPage(CSttMacroTestParaData *pData);
	void GetPageToValue(CSttMacroTestParaData *pData);

	void InitUI();
	void InitLanuage();
	void CheckAllPresence(CExBaseList *pParas);
};
CString CheckDataMinMax(CString strValue,float nMax,float nMin,int nAfterPoint);
void CheckForPresence(CExBaseList *pParas,CString strID);
#endif // SYNBINARYSDLG_H
