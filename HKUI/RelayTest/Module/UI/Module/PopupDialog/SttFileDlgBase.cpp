#include "SttFileDlgBase.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../XLangResource_Native.h"
#include "../../../Module/OSInterface/QT/XMessageBox.h"
#include <QFile>  
#include <QTextStream>  

// qint64 getAvailableMemoryLinux() {  
// 	QFile file("/proc/meminfo");  
// 	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {  
// 		return -1; // 或者处理错误  
// 	}  
// 
// 	QTextStream in(&file);  
// 	while (!in.atEnd()) {  
// 		QString line = in.readLine();  
// 		if (line.startsWith("MemAvailable:")) {  
// 			QStringList parts = line.split(" ");  
// 			if (parts.size() > 1) {  
// 				return parts[1].toLongLong() * 1024; // MemAvailable是以kB为单位的，转换为字节  
// 			}  
// 		}  
// 	}  
// 	return -1; // 如果没有找到或者出现其他错误，返回-1  
// }  



QSttFileDlgBase::QSttFileDlgBase(const CString &strFolderPath,QStringList &astrPostfix,QWidget *parent,BOOL UseCodeConversion)
	: QDialog(parent)
{
	setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);

	m_strInnerFolderPath = strFolderPath;
	m_astrPostfix = astrPostfix;
	m_pMain_VLayout = NULL;
	m_pOK_CancelHLayout = NULL;
	m_pOpenSave_PushButton = NULL;
	m_pCancel_PushButton = NULL;
	m_pExternalPathCheckBox = NULL;
	m_pSttFileMngrTree = NULL;
	m_pCurrSelObj = NULL;
// 	long nLenth = getAvailableMemoryLinux();
// 	CString strTitle,strMsg;
// 	strTitle = "提示";
// 	strMsg = "剩余内存(";
// 	strMsg.AppendFormat("%ld",nLenth);
// 	strMsg += ").";
// 	CXMessageBox::information(NULL,strTitle,strMsg);

//	m_bUseCodeConversion = FALSE;
//	InitUI();
}

QSttFileDlgBase::~QSttFileDlgBase()
{

}

void QSttFileDlgBase::InitUI()
{
	resize(850,550);
	this->setFixedWidth(850);
	this->setFixedHeight(550);

	m_pSttFileMngrTree = new QSttFileMngrTree(this);
	//m_pSttFileMngrTree->setFont(font());

	if (g_pSttGlobalFont != NULL)
	{
		m_pSttFileMngrTree->setFont(*g_pSttGlobalFont);
	}

//	m_pSttFileMngrTree->m_bUseCodeConversion = m_bUseCodeConversion;

	CXFileType *pXFileType = m_pSttFileMngrTree->m_oFileMngr.AddFileType(_T(""), _T("Files"), _T(""), _T(""));
	long nCount = m_astrPostfix.size();
	CString strPostfix;

	for (int nIndex = 0;nIndex<nCount;nIndex++)
	{
		strPostfix = m_astrPostfix.at(nIndex);
		strPostfix.Replace("*.","");
		pXFileType->AddNewPostfix(_T(""), strPostfix);
	}

	CString strTemp;
	m_pSttFileMngrTree->m_oFileMngr.InitByXFileTypes();
	//strTemp = _T("显示U盘路径");
//	xlang_GetLangStrByFile(g_sLangTxt_Gradient_ShowUpath,"Gradient_ShowUpath");
	m_pExternalPathCheckBox = new QSttCheckBox(g_sLangTxt_Gradient_ShowUpath,this);
	m_pOpenSave_PushButton = new QPushButton(this);

	if (g_pSttGlobalFont != NULL)
	{
		m_pOpenSave_PushButton->setFont(*g_pSttGlobalFont);
	}

	m_pCancel_PushButton = new QPushButton(this);
	xlang_GetLangStrByFile(strTemp,"sCancel");
	m_pCancel_PushButton->setText(strTemp);

	if (g_pSttGlobalFont != NULL)
	{
		m_pCancel_PushButton->setFont(*g_pSttGlobalFont);
	}

	m_pOK_CancelHLayout = new QHBoxLayout;
	m_pOK_CancelHLayout->addWidget(m_pExternalPathCheckBox);
	m_pOK_CancelHLayout->addStretch();
	m_pOK_CancelHLayout->addWidget(m_pOpenSave_PushButton);
	m_pOK_CancelHLayout->addWidget(m_pCancel_PushButton);
	m_pOK_CancelHLayout->setContentsMargins(3,3,3,3);
	m_pOK_CancelHLayout->setDirection(QBoxLayout::LeftToRight);

	m_pOpenSave_PushButton->setFixedWidth(80);
	m_pCancel_PushButton->setFixedWidth(80);
	//main

	CString strUsbPath;

	if (GetUsbRootFolderPath(strUsbPath))
	{
		m_pExternalPathCheckBox->setChecked(true);
		m_pExternalPathCheckBox->setEnabled(true);
	} 
	else
	{
		m_pExternalPathCheckBox->setChecked(false);
		m_pExternalPathCheckBox->setEnabled(false);
	}
}

void QSttFileDlgBase::slot_TreeItemClicked(QTreeWidgetItem* pItem, int nIndex)
{
	if (pItem == NULL)
	{
		return;
	}

	QExBaseTreeWidgetItem *pExBaseTreeWidgetItem = (QExBaseTreeWidgetItem*)pItem;

	if (pExBaseTreeWidgetItem->m_pItemData == NULL)
	{
		return;
	}

	CExBaseObject *pItemData = pExBaseTreeWidgetItem->m_pItemData;

	if ((pItemData->GetClassID() == CLASSID_XFOLDER)&&(GetSelType() == STT_FILE_MNGR_SEL_TYPE_FILE))
	{
		return;
	}
	else if ((pItemData->GetClassID() == CLASSID_XFILE)&&(GetSelType() == STT_FILE_MNGR_SEL_TYPE_FOLDER))
	{
		return;
	}

	m_pCurrSelObj = pItemData;
	EnableButtons();
}

void QSttFileDlgBase::slot_ExternalPathStateChanged(int nState)
{
	UpdateFileMngrTree();
	EnableButtons();
}


void QSttFileDlgBase::slot_OKClicked()
{
	accept();
}

void QSttFileDlgBase::slot_CancelClicked()
{
	close();
}

void QSttFileDlgBase::EnableButtons()
{

}

void QSttFileDlgBase::UpdateFileMngrTree()
{
	disconnect(m_pSttFileMngrTree, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(slot_TreeItemClicked(QTreeWidgetItem*, int)));
	disconnect(m_pExternalPathCheckBox, SIGNAL(stateChanged(int)), this, SLOT(slot_ExternalPathStateChanged(int)));
	disconnect(m_pOpenSave_PushButton, SIGNAL(clicked()), this, SLOT(slot_OKClicked()));
	disconnect(m_pCancel_PushButton, SIGNAL(clicked()), this, SLOT(slot_CancelClicked()));
	m_pCurrSelObj = NULL;//熟悉控件更新时,当前选择对象清空

	if (m_pExternalPathCheckBox->checkState() == Qt::Checked)
	{
		CString strExternalPath;

		if (GetUsbRootFolderPath(strExternalPath))
		{
			if (strExternalPath == m_strInnerFolderPath)//如果内部路径和U盘路径相同,则只能选择U盘路径,不再可以选择内部路径
			{
				m_pExternalPathCheckBox->setEnabled(false);
			}

			m_pSttFileMngrTree->InitShowFolderViewTree(strExternalPath);
		}
		else
		{
			m_pExternalPathCheckBox->setChecked(false);
			m_pExternalPathCheckBox->setEnabled(false);
			m_pSttFileMngrTree->InitShowFolderViewTree(m_strInnerFolderPath);
		}
	} 
	else
	{
		m_pSttFileMngrTree->InitShowFolderViewTree(m_strInnerFolderPath);
	}

	connect(m_pSttFileMngrTree, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(slot_TreeItemClicked(QTreeWidgetItem*, int)));
	connect(m_pExternalPathCheckBox, SIGNAL(stateChanged(int)), this, SLOT(slot_ExternalPathStateChanged(int)));
	connect(m_pOpenSave_PushButton, SIGNAL(clicked()), this, SLOT(slot_OKClicked()));
	connect(m_pCancel_PushButton, SIGNAL(clicked()), this, SLOT(slot_CancelClicked()));
}

CString QSttFileDlgBase::GetCurrRootFolderPath()
{
	return m_pSttFileMngrTree->m_oFileMngr.m_strRootPath;
}

void QSttFileDlgBase::InitTitle(const CString &strText)
{
	setWindowTitle(strText);
}

void QSttFileDlgBase::IniOpenSavetBtn(const CString &strText)
{
	m_pOpenSave_PushButton->setText(strText);
}
