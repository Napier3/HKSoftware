#ifndef QSttCommCfgPointTblFileImportDlg_H
#define  QSttCommCfgPointTblFileImportDlg_H

#include <QDialog>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QStringList>
#include <QGridLayout>
#include <QTimerEvent>
#include <QLineEdit>
#include "SttCommCfgPointTblFileImportGrid.h"
#include "../../../../../../Module/DataMngr/DataGroup.h"
#include "SttCommCfgPointTblFileImportTreeCtrl.h"
 
class QSttCommCfgPointTblFileImportDlg : public QDialog, public CExBaseListTreeOptrInterface
{
	Q_OBJECT

public:
	QSttCommCfgPointTblFileImportDlg(QWidget *parent = 0);
	virtual ~QSttCommCfgPointTblFileImportDlg();

	void initUI();
	void SetDialogFont();
	void ReleaseUI();
	void InitDatas();
	void initTreeDatas();
	void initGridData();
	BOOL CheckPpSttCommConfigFile();
	CDataGroup* ScanDataDir(CString strScanPath,CString argFileSuffix);

	virtual void OnItemSelChanged(CExBaseListTreeCtrl *pTreeCtrl, CExBaseObject *pSelObj);
	virtual BOOL OnItemBDblClk(CExBaseListTreeCtrl  *pTreeCtrl, CExBaseObject *pSelObj);

	QSttCommCfgPointTblFileImportTreeCtrl *m_pPpXmlTreeCtrl;  //规约元素树控件
	SttCCommCfgPointTblFileImportGrid *m_pPointTbImportGrid; //导入点表表格
	QPushButton *m_pImportPointFile_PushButton;	   	 //导入
	QPushButton *m_pEditPointFile_PushButton;	     //点表编辑
	CString m_strPointTbFileDir;	                 //点表文件路径
	QPushButton* m_pOK_PushButton;                   //确定按钮
	QPushButton* m_pCancel_PushButton;                //取消按钮

public slots:
	void slot_ImportPointBtnClicked();	   //导入按钮槽函数
	void slot_EditPointBtnClicked();	   //点表编辑按钮槽函数
	void slot_OKClicked();
	void slot_CancelClicked();
	
};

#endif // QSttCommCfgPointTblFileImportDlg
