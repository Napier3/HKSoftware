#ifndef QSttCommCfgProtocolTemplateDlg_H
#define QSttCommCfgProtocolTemplateDlg_H

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
#include "SttCommCfgProtocolTemplateGrid.h"
#include "../../../../../../Module/DataMngr/DataGroup.h"


class QSttCommCfgProtocolTemplateDlg : public QDialog
{
	Q_OBJECT

public:
	QSttCommCfgProtocolTemplateDlg(QWidget *parent = 0);
	virtual ~QSttCommCfgProtocolTemplateDlg();

	void initUI();
	void SetDialogFont();
	void ReleaseUI();
	void InitDatas();
	CDataGroup* ScanDataDir(CString strScanPath, CString argFileSuffix);

	SttCCommCfgProtocolTemplateGrid *m_pProtocolTmplGrid;   //规约模板管理表格
	QPushButton *m_pImportProtocol_PushButton;	            //规约导入按钮
	QPushButton *m_pOK_PushButton;	            //确定按钮
	QPushButton *m_pCancel_PushButton;	            //取消按钮
	
public slots:
	void slot_ImportProtocolBtnClicked();                 //规约导入按钮槽函数
	void slot_OKClicked();
	void slot_CancelClicked();
	
};

#endif // QSttCommCfgProtocolTemplateDlg_H
