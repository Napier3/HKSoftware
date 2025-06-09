#ifndef QDISTANCESEARCHBINARYSIGNALDLG
#define QDISTANCESEARCHBINARYSIGNALDLG

#include <QDialog>
#include "../../UI/Interface/SttMacroParaEditViewOriginal.h"

namespace Ui {
class QDistanceSearchBinarySignalDlg;
}

class QDistanceSearchBinarySignalDlg : public QDialog
{
    Q_OBJECT
public:
    explicit QDistanceSearchBinarySignalDlg(QWidget *parent = 0);
    ~QDistanceSearchBinarySignalDlg();
    void InitUI();
	void GetDatas(CExBaseList *pParas);
	void SetDatas(CExBaseList *pParas);
	void UpdateAllBinarys(CExBaseList *pAllItems);
	void UpdateCurrentBinarys(CExBaseList *pItem);
    BOOL CheckItemsModify(CExBaseList *pAllItems);
    void SetBinBoutName();

private:
    Ui::QDistanceSearchBinarySignalDlg *ui;
	CExBaseList *m_pParas;
    int m_nModify;
    int m_nInputWidgetWidth;     //20240725 wanmj lineEdit和comboBox固定宽度

public:
	CDataGroup *m_pCurrDataGroup;

signals:

public slots:
	void on_m_btnOk_clicked();
	void on_m_btnCancel_clicked();
	void on_m_editOutputKeepTime_editingFinished();
    void on_m_editOutputDelayTime_editingFinished();

private:
	void SetValueToPage(CSttMacroTestParaData *pData);
	void GetPageToValue(CSttMacroTestParaData *pData);
	void CheckAllPresence(CExBaseList *pParas);
    
};

#endif // QDISTANCESEARCHBINARYSIGNALDLG
