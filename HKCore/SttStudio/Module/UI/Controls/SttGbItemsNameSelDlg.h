#ifndef SttGbItemsNameSelDlg_H
#define SttGbItemsNameSelDlg_H

#include <QDialog>
#include "../../SttCmd/GuideBook/SttItems.h"

namespace Ui {
class QSttGbItemsNameSelDlg;
}

class QSttGbItemsNameSelDlg : public QDialog
{
    Q_OBJECT

public:
    explicit QSttGbItemsNameSelDlg(QWidget *parent = 0);
    virtual ~QSttGbItemsNameSelDlg();

	CString m_strName;
	CString m_strID;

private slots:
        void on_m_Btn_OK_clicked();
        void on_m_Btn_Cancel_clicked();

        void on_m_cmbItemsName_currentIndexChanged(int index);

private:
    Ui::QSttGbItemsNameSelDlg *ui;
};

#endif // SttGbItemsNameSelDlg_H
