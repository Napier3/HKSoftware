#include "QSaveComTradeCfgDlg.h"
#include <QFileDialog>
#include "../../../../61850/Module/XLanguageResourcePp_Mms.h"

QSaveComTradeCfgDlg::QSaveComTradeCfgDlg(QWidget *parent)
: QDialog(parent)
{
	ui.setupUi(this);
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
	connect(ui.m_Btn_OK, SIGNAL(clicked()), this, SLOT(On_Btn_OK_clicked()));
	connect(ui.m_Btn_Cancel, SIGNAL(clicked()), this, SLOT(On_Btn_Cancel_clicked()));
	connect(ui.m_Btn_ChoosePath, SIGNAL(clicked()), this, SLOT(On_Btn_ChoosePath_clicked()));
}

QSaveComTradeCfgDlg::~QSaveComTradeCfgDlg()
{

}

CString QSaveComTradeCfgDlg::OpenSelectDirectoryDlg(QWidget *parent, const CString &strTitle, const CString &strFolderPath)
{
	QFileDialog oFileDlg(parent);

	oFileDlg.setWindowTitle(strTitle);
	oFileDlg.setFileMode(QFileDialog::Directory);
	oFileDlg.setViewMode(QFileDialog::List);

	oFileDlg.setDirectory(strFolderPath);
	oFileDlg.show();

	CString strDirPath;

	if (oFileDlg.exec() == QFileDialog::Accepted)
	{
		strDirPath = oFileDlg.selectedFiles().first(); 
	}

	return strDirPath;
}

void QSaveComTradeCfgDlg::On_Btn_ChoosePath_clicked()
{
	m_strFilePath = OpenSelectDirectoryDlg(this, /*_T("Ñ¡ÔñÂ·¾¶")*/g_sLangTxt_SelPath, _T(""));
	ui.m_Edit_FilePath->setText(m_strFilePath);
}

void QSaveComTradeCfgDlg::On_Btn_OK_clicked()
{
	this->done(Accepted);
}

void QSaveComTradeCfgDlg::On_Btn_Cancel_clicked()
{
	this->close();
}

void QSaveComTradeCfgDlg::On_FileTypeChanged()
{

}
