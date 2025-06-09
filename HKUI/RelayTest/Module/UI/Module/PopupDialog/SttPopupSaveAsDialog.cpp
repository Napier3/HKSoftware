#include "SttPopupSaveAsDialog.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../XLangResource_Native.h"
#include <QStringList>
#include "../../../../../Module/OSInterface/QT/XMessageBox.h"

QSttPopupSaveAsDialog::QSttPopupSaveAsDialog(const CString &strFolderPath,QStringList &astrPostfix,const CString &strDefaultFileName,
									   QWidget *parent,BOOL UseCodeConversion)
	: QSttFileDlgBase(strFolderPath,astrPostfix,parent,UseCodeConversion)
{
	m_strRelFolderPath = _T("");
	m_strFileName = strDefaultFileName;

}

QSttPopupSaveAsDialog::~QSttPopupSaveAsDialog()
{
}

void QSttPopupSaveAsDialog::InitUI()
{
	QSttFileDlgBase::InitUI();
	CString strTemp;
	CString strTitle;
	strTitle = /*_T("文件另存为")*/g_sLangTxt_IEC_FileSaveAs; //lcq
	setWindowTitle(strTitle);
	strTitle = /*_T("文件名称：")*/g_sLangTxt_Gradient_FmFileName;  //lcq
	m_pFileName_Label = new QLabel(strTitle,this);
	m_pFileName_Label->setFont(*g_pSttGlobalFont);
	m_pFileName_LineEdit = new QSttLineEdit(this);
	m_pFileName_LineEdit->setFont(*g_pSttGlobalFont);
	m_pFileName_LineEdit->setText(m_strFileName);
	m_pFileHLayout = new QHBoxLayout;
	m_pFileHLayout->addWidget(m_pFileName_Label);
	m_pFileHLayout->addWidget(m_pFileName_LineEdit);

	strTitle = /*_T("文件目录：")*/g_sLangTxt_Gradient_DirectoryFile; //lcq
	m_pFolderPath_Label = new QLabel(strTitle,this);
	m_pFolderPath_Label->setFont(*g_pSttGlobalFont);
	m_pFolderPath_LineEdit = new QSttLineEdit(this);
	m_pFolderPath_LineEdit->setFont(*g_pSttGlobalFont);
	m_pFolderPath_LineEdit->setText(m_strRelFolderPath);
	m_pFolderPath_LineEdit->setEnabled(false);
	m_pFolderPathHLayout = new QHBoxLayout;
	m_pFolderPathHLayout->addWidget(m_pFolderPath_Label);
	m_pFolderPathHLayout->addWidget(m_pFolderPath_LineEdit);

	xlang_GetLangStrByFile(strTemp,"sSave");
	m_pOpenSave_PushButton->setText(strTemp);

	m_pMain_VLayout = new QVBoxLayout(this);
	m_pMain_VLayout->addWidget(m_pSttFileMngrTree);
	m_pMain_VLayout->addLayout(m_pFileHLayout);
	m_pMain_VLayout->addLayout(m_pFolderPathHLayout);
	m_pMain_VLayout->addLayout(m_pOK_CancelHLayout);

	UpdateFileMngrTree();
	EnableButtons();

//	connect(m_pFileName_LineEdit,SIGNAL(clicked()),this,SLOT(slot_FileNameLineEditClicked()));
	connect(m_pFileName_LineEdit,SIGNAL(textChanged(const QString&)),this,SLOT(on_FileName_textChanged(const QString&)));

}

void QSttPopupSaveAsDialog::slot_ExternalPathStateChanged(int nState)
{
	m_pFolderPath_LineEdit->setText("");
	m_strRelFolderPath = _T("");
	QSttFileDlgBase::slot_ExternalPathStateChanged(nState);
}

void QSttPopupSaveAsDialog::slot_TreeItemClicked(QTreeWidgetItem* pItem, int nIndex)
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

	if (pItemData->GetClassID() == CLASSID_XFOLDER)
	{
		m_pCurrSelObj = pItemData;
	}
	else 
	{
		m_pCurrSelObj = (CExBaseObject*)pItemData->GetParent();
	}

	CXFolder *pFolder = (CXFolder*)m_pCurrSelObj;

	if (pFolder == &m_pSttFileMngrTree->m_oFileMngr)
	{
		m_strRelFolderPath = _T("");
		m_pCurrSelObj = NULL;
	} 
	else
	{
		m_strRelFolderPath = pFolder->GetRelativePath() + "/";
	}

	m_pFolderPath_LineEdit->setText(m_strRelFolderPath);

	//chenling20231106 
	CString strName = pItemData->m_strName;
	int dotIndex = strName.lastIndexOf(".");
	if (dotIndex != -1)
	{
		strName.truncate(dotIndex);
	}
	m_pFileName_LineEdit->setText(strName);

	EnableButtons();
}

void QSttPopupSaveAsDialog::EnableButtons()
{
	if (ValidFileName()) 
	{
		m_pOpenSave_PushButton->setEnabled(true);
	}
	else
	{
		m_pOpenSave_PushButton->setEnabled(false);
	}
}

BOOL QSttPopupSaveAsDialog::ValidFileName()
{
	CString strFileName,strFilePath;
	strFileName = m_pFileName_LineEdit->text();

	if (strFileName.IsEmpty())
	{
		return FALSE;
	}

	CString strInfor;

	if (!CheckFileName(strFileName, strInfor))
	{
		strFileName = m_strFileName;
		m_pFileName_LineEdit->setText(strFileName);
	}

	m_strFileName = strFileName;
	strFilePath = GetFilePath();

// 	if (IsFileExist(strFilePath))
// 	{
// 		//CLogPrint::LogFormatString(XLOGLEVEL_ASSIST,_T("路径(%s)下存在同名的文件,请修改文件名."),strFilePath.GetString());
// 		CLogPrint::LogFormatString(XLOGLEVEL_ASSIST,g_sLangTxt_Gradient_SameeXist.GetString(),strFilePath.GetString()); //lcq
// 
// 		return FALSE;
// 	}

	return TRUE;
}

void QSttPopupSaveAsDialog::slot_OKClicked()//chenling20231106 
{
	CString strFilePath;
	strFilePath = GetFilePath();

	CString strText,strText1,strText2;
	xlang_GetLangStrByFile(strText, "sMessage");
	xlang_GetLangStrByFile(strText1, "Native_FileExist");
	xlang_GetLangStrByFile(strText2, "Native_FileSave");

	bool bMessageBox = true;

	if (IsFileExist(strFilePath))
	{
		int nRet = CXMessageBox::information(this, strText, strText1, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

		if (nRet == QMessageBox::No)
		{
			return ;
		}
		else
		{
			bMessageBox = true;
		}
	}

	if (bMessageBox)
	{
		CXMessageBox::information(this, strText, strText2);
	}
	accept();
}


CString QSttPopupSaveAsDialog::GetCurSelFolderPath()
{
	CString strFolderPath;

	if (m_pCurrSelObj == NULL)//如果当前未选择子文件夹，则当前处于根目录下
	{
		strFolderPath = GetCurrRootFolderPath();
	}
	else
	{
		CXFolder *pXFileFolder = (CXFolder *)m_pCurrSelObj;
		strFolderPath = pXFileFolder->GetFolderPath(TRUE);
	}

	return strFolderPath;
}

CString QSttPopupSaveAsDialog::GetFilePath()
{
	CString strFilePath;
	strFilePath = GetCurrRootFolderPath();

// 	if (m_bUseCodeConversion)//需要进行编码转换,则进行转换
// 	{
// 		CString strGbk;
// 		utf8_to_gbk(strFilePath,strGbk);
// 		strFilePath = strGbk;
// 	}

	strFilePath += m_pFolderPath_LineEdit->text();
	strFilePath += m_pFileName_LineEdit->text();

	if (m_astrPostfix.size()>0)//如果指定扩展名,则按指定扩展名处理
	{
		CString strCurrPostfix;
		strCurrPostfix = m_astrPostfix.at(0);
		strCurrPostfix.Replace("*.","");
		strFilePath = ChangeFilePostfix(strFilePath,strCurrPostfix);
	}

	return strFilePath;
}

// void QSttFileSaveDialog::slot_FileNameLineEditClicked()
// {
// 	QString strValue = m_pFileName_LineEdit->text();
// 	m_pFileName_LineEdit->setText(strValue);
// }

void QSttPopupSaveAsDialog::on_FileName_textChanged(const QString &arg1)
{
	EnableButtons();
}