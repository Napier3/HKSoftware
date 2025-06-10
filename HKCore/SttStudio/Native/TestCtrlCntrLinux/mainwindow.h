#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "../../Module/UI/Webkit/SttMacroParaEditViewHtml.h"
#include "../../Module/UI/Webkit/SttReportViewHtml.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, public CLogBase
{
    Q_OBJECT

public:
	virtual void LogString(long nLevel, const CString &strMsg);
	virtual void LogString(long nLevel, const char *strMsg);

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

	QSttMacroParaEditViewHtml *m_pParaEditView;
	QSttReportViewHtml *m_pReportView;

private slots:
    void on_btnSetDatas_clicked();

    void on_btnParasEdit_clicked();

    void on_btnReportView_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
