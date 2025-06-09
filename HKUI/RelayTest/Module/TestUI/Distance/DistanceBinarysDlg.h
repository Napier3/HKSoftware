#ifndef DISTANCEBINARYSDLG_H
#define DISTANCEBINARYSDLG_H

#include <QDialog>
#include "./DistanceCommonParasDlg.h"

namespace Ui {
class QDistanceBinarysDlg;
}

class QDistanceBinarysDlg : public QDialog
{
    Q_OBJECT

public:
    explicit QDistanceBinarysDlg(QWidget *parent = 0);
    ~QDistanceBinarysDlg();

	void GetDatas(CExBaseList *pParas);
	void SetDatas(CExBaseList *pParas);
	void UpdataAllBinarys(CExBaseList *pParas);
	BOOL CheckItemsModify(CExBaseList *pAllItems);
    void SetDisplayedByDefault(BOOL bDefault);
	virtual void SetPageFont(CFont oPageFont);
private slots:
	void on_m_cmb_SwitchMode_currentIndexChanged(int index);

	void on_m_txtDelayTime_editingFinished();
	void on_m_txtKeepTime_editingFinished();

	void on_m_btnOK_clicked();
	void on_m_btnCancel_clicked();
private:
    Ui::QDistanceBinarysDlg *ui;
	CExBaseList *m_pParas;
	int m_nModify;
    BOOL m_bDefault;
	void InitUI();
	virtual void InitLanuage();
	void CheckInputSel(int index);

	void SetValueToPage(CSttMacroTestParaData *pData);
	void GetPageToValue(CSttMacroTestParaData *pData);
	void CheckAllPresence(CExBaseList *pParas);
	void SetBinBoutName();//根据开入开出映射设置开关量界面显示值20240925 luozibing
};

extern bool Stt_Global_IsSetting(QObject *pObject);		//20240805 huangliang 

#endif // DISTANCEBINARYSDLG_H
