#ifndef STTREPORTHEADSETDLG_H
#define STTREPORTHEADSETDLG_H

#include <QDialog>
#include <QLabel>
#include <QTreeWidgetItem>
#include "../../SttCmd/GuideBook/SttReports.h"
#include "SttLineEdit.h"
#include "SttDvmEdit.h"

#include "../../../../Module/API/GlobalConfigApi.h"

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

	void SetData();
	void UpdateParentItem(QTreeWidgetItem *pitem);
	void SetTreeItem( CDataGroup *pData,QTreeWidgetItem *pParent );
	void OpenEngKeyboard(QSttLineEdit* pEditLine);
    void UpdateShow(CExBaseObject *pSel);
	void AddObjToGroup(CDvmData* pData,int nRow);
	void setReportHeadFont();
	void InitObjValue(CDataGroup *pData);
public:
	int m_nOkFlag;

public:
	CDataGroup *m_pSttReports;
	CDataGroup *m_pTempData;
    CDataGroup *m_pCurrSelGroup;

	QList<QSttDvmEdit*> m_editList;
	QList<QLabel*> m_labelList;
	bool m_bUpataHeadHtml;

private:
    Ui::QSttReportHeadSetDlg *ui;
	void InitStyleSheet();

public slots:
	void slot_TreeItemChanged(QTreeWidgetItem* pItem,int nCol);
	void slot_OKClick();
	void slot_CancelClick();
};




////////////////

extern CFont *g_pSttGlobalFont;  

#endif // STTREPORTHEADSETDLG_H
