#ifndef QACTIONTIMEBINARYSIGNALDLG
#define QACTIONTIMEBINARYSIGNALDLG

#include <QDialog>
#include "../../UI/Interface/SttMacroParaEditViewOriginal.h"

namespace Ui {
class QActionTimeBinarySignalDlg;
}

class QActionTimeBinarySignalDlg : public QDialog
{
    Q_OBJECT
public:
    explicit QActionTimeBinarySignalDlg(QWidget *parent = 0);
    ~QActionTimeBinarySignalDlg();
    void InitUI();
	void GetDatas(CExBaseList *pParas);
	void SetDatas(CExBaseList *pParas);
	void UpdateAllBinarys(CExBaseList *pAllItems);
	void UpdateCurrentBinarys(CExBaseList *pItem);
    BOOL CheckItemsModify(CExBaseList *pAllItems);
    void SetBinBoutName();

private:
    Ui::QActionTimeBinarySignalDlg *ui;
	CExBaseList *m_pParas;
    int m_nModify;

public:
	CDataGroup *m_pCurrDataGroup;

signals:

public slots:
	void on_m_btnOk_clicked();
	void on_m_btnCancel_clicked();
	
private:
	void SetValueToPage(CSttMacroTestParaData *pData);
	void GetPageToValue(CSttMacroTestParaData *pData);
	void CheckAllPresence(CExBaseList *pParas);

};

#endif // QACTIONTIMEBINARYSIGNALDLG
