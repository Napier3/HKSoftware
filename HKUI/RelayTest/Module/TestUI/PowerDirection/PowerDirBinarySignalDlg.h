#ifndef QPOWERDIRBINARYSIGNALDLG
#define QPOWERDIRBINARYSIGNALDLG

#include <QDialog>
#include "../../UI/Interface/SttMacroParaEditViewOriginal.h"

namespace Ui {
class QPowerDirBinarySignalDlg;
}

class QPowerDirBinarySignalDlg : public QDialog
{
    Q_OBJECT
public:
    explicit QPowerDirBinarySignalDlg(QWidget *parent = 0);
    ~QPowerDirBinarySignalDlg();
    void InitUI();
	/*void SetDatas(CDataGroup *pParas);
	void GetDatas(CDataGroup *pParas);*/
	void GetDatas(CExBaseList *pParas);
	void SetDatas(CExBaseList *pParas);
	void UpdateAllBinarys(CExBaseList *pAllItems);
	void UpdateCurrentBinarys(CExBaseList *pItem);
    BOOL CheckItemsModify(CExBaseList *pItem);
    void SetBinBoutName();

private:
    Ui::QPowerDirBinarySignalDlg *ui;
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

#endif // QPOWERDIRBINARYSIGNALDLG
