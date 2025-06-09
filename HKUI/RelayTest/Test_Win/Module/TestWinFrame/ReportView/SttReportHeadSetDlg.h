#ifndef STTREPORTHEADSETDLG_H
#define STTREPORTHEADSETDLG_H

#include <QDialog>
#include <QLabel>
#include <QTreeWidgetItem>
#include "SttDvmEdit.h"
#include "../../../Module/DataMngr/DataGroup.h"

#define STT_REPORTHEAD_Vnom                     "Vnom"    //额定电压
#define STT_REPORTHEAD_Inom                     "Inom"    //额定电流
#define STT_REPORTHEAD_Fnom                     "Fnom"    //额定频率
#define STT_REPORTHEAD_SureTime                 "SureTime"    //开入防抖时间

#define STT_REPORTHEAD_AppModel                 "AppModel"    //型号
#define STT_REPORTHEAD_AppSN                    "AppSN"    //序列号
#define STT_REPORTHEAD_Imax                    "Imax"    //电流最大值
#define STT_REPORTHEAD_Vmax                    "Vmax"    //电压最大值
#define STT_REPORTHEAD_TestStartTime            "TestStartTime"//测试开始时间
#define STT_REPORTHEAD_TestEndTime              "TestEndTime"//测试终止时间

namespace Ui {
class QSttReportHeadSetDlg;
}

class QTreeWidgetItemEx : public QTreeWidgetItem
{
public:
	QTreeWidgetItemEx(QTreeWidget *pParent, CExBaseObject *pDataRef);
	QTreeWidgetItemEx(QTreeWidgetItem *pParent, CExBaseObject *pDataRef);

	CExBaseObject *m_pDataRef;
};

class QSttReportHeadSetDlg : public QDialog
{
    Q_OBJECT

public:
    explicit QSttReportHeadSetDlg(CDataGroup* pDataGroup,QWidget *parent = 0);
    ~QSttReportHeadSetDlg();
	void languageProcessing();
	void SetData();
	void UpdateParentItem(QTreeWidgetItem *pitem);
	void SetTreeItem( CDataGroup *pData,QTreeWidgetItem *pParent );
	CString StrAddPre(CString strID);
// 	void UpdateShow(CString strName);
	void UpdateShow(CExBaseObject *pSel);
	void AddObjToGroup(CDvmData* pData,int nRow);

	CString GetCtrlDesc(const CString& strID);
	void InitObjValue(CDataGroup *pData);
public:
	int m_nOkFlag;

public:
	CDataGroup *m_pSttReports;
	CDataGroup *m_pTempData;
	CDataGroup *m_pCurrSelGroup;

	QList<QSttDvmEdit*> m_editList;
	QList<QLabel*> m_labelList;
	QList<CString> m_strValue;
	bool m_bUpataHeadHtml;

private:
    Ui::QSttReportHeadSetDlg *ui;

public slots:
	void slot_TreeItemChanged(QTreeWidgetItem* pItem,int nCol);
	void slot_OKClick();
	void slot_CancelClick();
};




////////////////

#endif // STTREPORTHEADSETDLG_H
