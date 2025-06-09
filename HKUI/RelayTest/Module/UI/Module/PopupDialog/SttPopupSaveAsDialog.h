#ifndef STTPOPUPSAVEASDIALOG_H
#define STTPOPUPSAVEASDIALOG_H

#include <QLabel>
#include "../../Controls/SttLineEdit.h"
#include "SttFileDlgBase.h"

class QSttPopupSaveAsDialog : public QSttFileDlgBase
{
	Q_OBJECT

public:
	QSttPopupSaveAsDialog(const CString &strFolderPath,QStringList &astrPostfix,const CString &strDefaultFileName,
		QWidget *parent= NULL,BOOL UseCodeConversion = TRUE);
	virtual ~QSttPopupSaveAsDialog();

	CString GetFilePath();
	BOOL ValidFileName();
	CString GetCurSelFolderPath();//获取当前选择的文件夹路径

	virtual void InitUI();
	virtual void EnableButtons();
	virtual long GetSelType(){return STT_FILE_MNGR_SEL_TYPE_FOLDER;}
	virtual void slot_TreeItemClicked(QTreeWidgetItem*, int);

public:
	CString m_strRelFolderPath;//文件夹相对路径(相对于跟目录)
	CString m_strFileName;//文件名

private:
	QLabel *m_pFileName_Label;
	QSttLineEdit *m_pFileName_LineEdit;
	QHBoxLayout *m_pFileHLayout;
	QLabel *m_pFolderPath_Label;//文件夹路径
	QSttLineEdit *m_pFolderPath_LineEdit;
	QHBoxLayout *m_pFolderPathHLayout;

public slots:
//	void slot_FileNameLineEditClicked();
	void on_FileName_textChanged(const QString &arg1);
	virtual void slot_ExternalPathStateChanged(int nState);
	virtual void slot_OKClicked();
};

extern CFont *g_pSttGlobalFont;  

#endif // STTPOPUPSAVEASDIALOG_H
