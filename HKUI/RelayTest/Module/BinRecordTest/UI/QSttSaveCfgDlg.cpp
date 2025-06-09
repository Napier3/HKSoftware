#include "QSttSaveCfgDlg.h"
//#include <QStandardPaths>
#include <QDir>
#include <QDateTime>
#include <QFileDialog>

#include "../../../../Module/XLanguage/XLanguageResource.h"

#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
#include <QStandardPaths>
#else
#include <QDesktopServices>
#endif

QSttSaveCfgDlg::QSttSaveCfgDlg(QString strFilePath,QString strFileName,QWidget *parent /*= 0*/)
{
	ui.setupUi(this);
	InitData(strFilePath, strFileName);
}

QSttSaveCfgDlg::~QSttSaveCfgDlg()
{

}

void QSttSaveCfgDlg::InitData(QString strFilePath, QString strFileName)
{
	connect(ui.m_pBtnSelPath, SIGNAL(clicked()), this, SLOT(slot_m_pBtnSelPath()));
	connect(ui.m_pBtnOk, SIGNAL(clicked()), this, SLOT(slot_m_pBtnOk()));
	connect(ui.m_pBtnCancel, SIGNAL(clicked()), this, SLOT(slot_m_pBtnCancel()));

	ui.m_pEditSavePath->setText(strFilePath);
	ui.m_pEditFileName->setText(strFileName);
}

void QSttSaveCfgDlg::slot_m_pBtnSelPath()
{
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
	QString directory = QFileDialog::getExistingDirectory(this, g_sLangTxt_SelFolder,
		QStandardPaths::writableLocation(QStandardPaths::DesktopLocation),
		QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
#else
	QString directory = QFileDialog::getExistingDirectory(this, g_sLangTxt_SelFolder,
		QDesktopServices::storageLocation(QDesktopServices::DesktopLocation),
		QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
#endif

	if (!directory.isEmpty())
	{
		ui.m_pEditSavePath->setText(directory);
	}
}

void QSttSaveCfgDlg::slot_m_pBtnOk()
{
	this->done(Accepted);
}

void QSttSaveCfgDlg::slot_m_pBtnCancel()
{
	this->close();
}

