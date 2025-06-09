#ifndef STTEXPORTPCAPFILEDIALOG_H
#define STTEXPORTPCAPFILEDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class QSttExportPcapFileDialog : public QDialog
{
	Q_OBJECT

public:
	QSttExportPcapFileDialog(QWidget *parent);
	virtual ~QSttExportPcapFileDialog();

	void InitUI();

private:
	QVBoxLayout *m_pMainVLayout;

	QHBoxLayout *m_pSrcFilePathHLayout;
	QLabel *m_pSrcFile_Label;//
	QLineEdit *m_pSrcFilePath_LineEdit;
	QPushButton *m_pSelSrcFile_Btn;

	QHBoxLayout *m_pDstFileHLayout;
	QLabel *m_pDstFile_Label;//
	QLineEdit *m_pDstFile_LineEdit;

	QPushButton *m_pStartTrans_PushButton;
	QPushButton *m_pOK_PushButton;
	QHBoxLayout *m_pOK_CancelHLayout;

public slots:
	void slot_SelSrcFileClicked();
	void slot_StartTransClicked();
	void slot_OKClicked();
	
};

#endif // STTEXPORTPCAPFILEDIALOG_H
