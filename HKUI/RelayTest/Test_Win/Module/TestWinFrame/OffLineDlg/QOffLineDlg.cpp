#include "QOffLineDlg.h"
#include "../../../../Module/SttTestResourceMngr/SttTestResourceMngr.h"
#include <QDirIterator>
#include "../../../../Module/SttSystemConfig/SttSystemConfig.h"
#include "../Module/TestWinFrame/ReportView/XLangResource_PowerTestWin.h"

QOffLineDlg::QOffLineDlg(QWidget *parent)
	: QDialog(parent)
{
	setWindowIcon (QPixmap( ":/images/Sys.png"));
	setWindowFlags(Qt::WindowCloseButtonHint);
	setWindowTitle(/*tr("脱机选择")*/g_sLangTxt_Native_OfflineSelection);
}

QOffLineDlg::~QOffLineDlg()
{

}

void QOffLineDlg::initUI()
{
	ReleaseUI();
	resize(300, 100);
	setMinimumSize(QSize(0, 0));
	setMaximumSize(QSize(16777215, 16777215));

	QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	sizePolicy.setHorizontalStretch(30);
	sizePolicy.setVerticalStretch(30);

	m_pAllVLayout = new QVBoxLayout(this);

	m_pOfflLineSelGroupBox = new QGroupBox(this);
	m_pOfflLineSelGroupBox->setTitle(/*tr("测试仪型号类型选择")*/g_sLangTxt_Native_TestModelTypeSelect);//TestModelTypeSelect
	m_pVBoxLayout1 = new QGridLayout(m_pOfflLineSelGroupBox);
	m_pModelLabel = new QLabel(m_pOfflLineSelGroupBox);
	m_pModelLabel->setText(/*tr("型号:")*/g_sLangTxt_Report_AppModel+tr(":"));
	m_pVBoxLayout1->addWidget(m_pModelLabel,0,0,1,1);

	m_pModelSelCombobox = new QComboBox(m_pOfflLineSelGroupBox);

	sizePolicy.setHeightForWidth(m_pModelSelCombobox->sizePolicy().hasHeightForWidth());
	m_pModelSelCombobox->setSizePolicy(sizePolicy);

	m_pVBoxLayout1->addWidget(m_pModelSelCombobox,0,1,1,1);

	m_pSN_Label = new QLabel(m_pOfflLineSelGroupBox);
	m_pSN_Label->setText(/*tr("编号:")*/g_sLangTxt_State_AppNumber);
	m_pVBoxLayout1->addWidget(m_pSN_Label,1,0,1,1);

	m_pSN_SelCombobox = new QComboBox(m_pOfflLineSelGroupBox);

	sizePolicy.setHeightForWidth(m_pSN_SelCombobox->sizePolicy().hasHeightForWidth());
	m_pSN_SelCombobox->setSizePolicy(sizePolicy);

	m_pVBoxLayout1->addWidget(m_pSN_SelCombobox,1,1,1,1);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	m_pOK_PushButton = new QPushButton(this);
	m_pOK_PushButton->setText(/*tr("确定")*/g_sLangTxt_OK);
	m_pOK_PushButton->setIcon (QPixmap( "./images/Check.png"));

	m_pCancel_PushButton = new QPushButton(this);
	m_pCancel_PushButton->setText(/*tr("取消")*/g_sLangTxt_Cancel);
	m_pCancel_PushButton->setIcon (QPixmap( "./images/Cancel.png"));

	m_pHBoxLayout2 = new QHBoxLayout(this);
	m_pHBoxLayout2->addStretch();
	m_pHBoxLayout2->addWidget(m_pOK_PushButton);
	m_pHBoxLayout2->addSpacing(20);
	m_pHBoxLayout2->addWidget(m_pCancel_PushButton);
	m_pHBoxLayout2->addStretch();
//	m_pHBoxLayout2->setContentsMargins(3,3,3,3);
	m_pHBoxLayout2->setDirection(QBoxLayout::LeftToRight);
	m_pAllVLayout->addWidget(m_pOfflLineSelGroupBox);
	m_pAllVLayout->addLayout(m_pHBoxLayout2);
	InitDatas();
	this->setLayout(m_pAllVLayout);

	connect(m_pModelSelCombobox,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_changeModelSel(int)));
	connect(m_pOK_PushButton, SIGNAL(clicked()), this, SLOT(slot_OKClicked()));
	connect(m_pCancel_PushButton, SIGNAL(clicked()), this, SLOT(slot_CancelClicked()));
}

void QOffLineDlg::ReleaseUI()
{

}

void QOffLineDlg::InitDatas()
{
	QString strPath = g_oSttTestResourceMngr.GetRsDirPath_Device();
	m_astrModels.clear();
	m_astrSNs.clear();
	GetAllChildFolder(strPath,m_astrModels);
	m_pModelSelCombobox->clear();
	m_pSN_SelCombobox->clear();
	m_pModelSelCombobox->insertItems(0,m_astrModels);
	long nModelIndex = m_astrModels.indexOf(g_oSttSystemConfig.GetDevModel());

	if (nModelIndex>=0)
	{
		m_pModelSelCombobox->setCurrentIndex(nModelIndex);
		QString strCurDevPath;
		strCurDevPath = QString(tr("%1/%2/")).arg(strPath).arg(m_astrModels.at(nModelIndex));
		GetAllChildFolder(strCurDevPath,m_astrSNs);
		m_pSN_SelCombobox->insertItems(0,m_astrSNs);

		long nSnIndex = m_astrSNs.indexOf(g_oSttTestResourceMngr.GetCurrSelSN());

		if (nSnIndex>=0)
		{
			m_pSN_SelCombobox->setCurrentIndex(nSnIndex);
		}
	}
}

void QOffLineDlg::GetAllChildFolder(const QString &strParentFolderPath,QStringList &astrChildFolders)
{
	QDir dir(strParentFolderPath);

	//将过滤后的文件名称存入到files列表中
	QStringList nameFilters;
	astrChildFolders = dir.entryList(nameFilters, QDir::Dirs| QDir::NoDotAndDotDot);
// 	QDirIterator it(strParentFolderPath,QDir::Dirs | QDir::NoDotAndDotDot ,QDirIterator::Subdirectories);
// 	QFileInfo oFileInfo;
// 
// 	while (it.hasNext()) 
// 	{
// 		it.next();
// 		oFileInfo = it.fileInfo();
// 
// 		if (oFileInfo.isDir())
// 		{
// 			astrChildFolders << oFileInfo.absoluteFilePath/*fileName*/();
// 		}
// 	}
}

void QOffLineDlg::slot_changeModelSel(int nCurComboxIndex)
{
	QString strPath = g_oSttTestResourceMngr.GetRsDirPath_Device();
	QString strCurDevPath;
	strCurDevPath = QString(tr("%1/%2/")).arg(strPath).arg(m_astrModels.at(nCurComboxIndex));
	GetAllChildFolder(strCurDevPath,m_astrSNs);
	m_pSN_SelCombobox->clear();
	m_pSN_SelCombobox->insertItems(0,m_astrSNs);
}

void QOffLineDlg::slot_OKClicked()
{
	QString strOldModel = g_oSttSystemConfig.GetDevModel();
	QString strOldSN = g_oSttTestResourceMngr.GetCurrSelSN();
	QString strCurModel = m_astrModels.at(m_pModelSelCombobox->currentIndex());
	QString strCurSN = m_astrSNs.at(m_pSN_SelCombobox->currentIndex());

	if ((strOldModel != strCurModel)||(strOldSN != strCurSN))
	{
		g_oSttTestResourceMngr.SetCurSelDevice(strCurModel,strCurSN);
		g_oSttTestResourceMngr.m_oChMaps.DeleteAll();
		emit sig_OffLineSelChanged();
	}

	close();
}

void QOffLineDlg::slot_CancelClicked()
{
	close();
}