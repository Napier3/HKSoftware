#ifndef QCURRINVERBINARYSDLG_H
#define QCURRINVERBINARYSDLG_H

#include <QDialog>
#include <QWidget>
//#include "../../../../Module/DataMngr/DataGroup.h"
#include "SttMultiMacroCurrInverseTimeParasDefine.h"
#include "../../SttCmd/GuideBook/SttMacroTest.h"

namespace Ui {
class QCurrInverBinarysDlg;
}

class QCurrInverBinarysDlg : public QDialog
{
    Q_OBJECT
public:
    explicit QCurrInverBinarysDlg(QWidget *parent = 0);
    ~QCurrInverBinarysDlg();
    void InitUI();
	void SetDatas(CExBaseList *pParas);
	void SetValueToPage(CSttMacroTestParaData *pData);
	void GetDatas(CExBaseList *pParas);
	void GetPageToValue(CSttMacroTestParaData *pData);

	void CheckAllPresence(CExBaseList *pParas);
    //void UpdateCurrentBinarys(CExBaseList *pItem);
	void UpdataAllBinarys(CExBaseList *pParas);
    BOOL CheckItemsModify(CExBaseList *pAllItems);

	void SetBinBoutName();//根据开入开出映射设置开关量界面显示值20240930 gongyiping
private:
    Ui::QCurrInverBinarysDlg *ui;
	virtual void InitLanuage();

public:
	//CDataGroup *m_pCurrDataGroup;
	CExBaseList *m_pParas;
    int m_nModify;

signals:

public slots:
	void on_pushButton_clicked();
	void on_pushButton_2_clicked();

};

#endif // QCURRINVERBINARYSDLG_H
