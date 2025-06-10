#ifndef STTFILEDLGBASE_H
#define STTFILEDLGBASE_H

#include <QDialog>
#include <QGroupBox>
#include <QRadioButton>
#include <QScrollArea>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QLabel>
#include <QStringList>
#include "../../Controls/SttCheckBox.h"
#include "SttFileMngrTree.h"

#define STT_FILE_MNGR_SEL_TYPE_FILE                         0
#define STT_FILE_MNGR_SEL_TYPE_FOLDER                       1
#define STT_FILE_MNGR_SEL_TYPE_FILEFOLDER                   2



class QSttFileDlgBase : public QDialog
{
	Q_OBJECT

public:
	QSttFileDlgBase(const CString &strFolderPath,QStringList &astrPostfix,QWidget *parent= NULL,BOOL UseCodeConversion = TRUE);
	virtual ~QSttFileDlgBase();

	virtual void InitUI();
	virtual void EnableButtons();
	virtual void UpdateFileMngrTree();//根据当前内部及外部路径选择状态,显示文件夹路径
	virtual long GetSelType(){return STT_FILE_MNGR_SEL_TYPE_FILE;}
	CString GetCurrRootFolderPath();//获取当前根目录路径
	void InitTitle(const CString &strText);
	void IniOpenSavetBtn(const CString &strText);

	QVBoxLayout *m_pMain_VLayout;
	QHBoxLayout *m_pOK_CancelHLayout;
	CString m_strInnerFolderPath;
	QStringList m_astrPostfix;
	QPushButton *m_pOpenSave_PushButton;
	QPushButton *m_pCancel_PushButton;
	QSttCheckBox *m_pExternalPathCheckBox;//外部路径,选中后,代表显示U盘对应的文件夹路径


	QSttFileMngrTree *m_pSttFileMngrTree;
	CExBaseObject *m_pCurrSelObj;//当前选择的文件/文件夹; 对于打开文件对话框对应选中的文件,对于另存为对话框对应选中的文件夹

//	BOOL m_bUseCodeConversion;//是否使用编码转换,即UTF8转GBK

public slots:
	virtual void slot_TreeItemClicked(QTreeWidgetItem*, int);
	virtual void slot_ExternalPathStateChanged(int nState);
	virtual void slot_OKClicked();
	virtual void slot_CancelClicked();
};


#endif // STTFILEDLGBASE_H
