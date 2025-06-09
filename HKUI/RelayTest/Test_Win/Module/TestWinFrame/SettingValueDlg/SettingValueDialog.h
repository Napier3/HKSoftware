#ifndef SETTINGVALUEDIALOG_H
#define SETTINGVALUEDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QHBoxLayout> 
#include <QGridLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTableWidget>
#include <QItemDelegate>
#include "../../SttXTestMngrBaseApp.h"
#include "../Module/CommonMethod/commonMethod.h"
#include "../../../../../Module/DataMngr/DataGroup.h"
#include "../../Module/SttCmd/SttCmdDefineGlobal.h"
#include "../SysParasSetDlg/QDvmDataLineEdit.h"
#include "../SysParasSetDlg/QValueComboBox.h"

class CCmbSettingDelegate : public QItemDelegate
{
public:
	CCmbSettingDelegate(QObject *parent = NULL);
	~CCmbSettingDelegate();

	virtual QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
		const QModelIndex &index) const;

	virtual void setEditorData(QWidget * editor, const QModelIndex &index) const;

	virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

	virtual void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
		const QModelIndex &index) const;
	virtual void paint(QPainter * painter, const QStyleOptionViewItem & option,
		const QModelIndex & index) const;//dxy 20240223 界面初始化时能将下拉框箭头显示出来


	void SetListValue(CDataType *pList);
	void SetUseEditCtrl(BOOL bUseEditCtrl = TRUE)       { m_bUseEditCtrl = bUseEditCtrl;          }

private:
	BOOL m_bUseEditCtrl;
	QStringList m_strList;
};

class SettingValueDialog : public QDialog
{
	Q_OBJECT

public:
	SettingValueDialog(QWidget *parent);
	~SettingValueDialog();
	
//	void setData(CDataGroup* pDataset);
	void InitTable();
	virtual void initUI();

	CString GetTextByIndex(CString strID, CString nIndex);
	CString GetIndexByText(CString strID, CString nText);

	void ChangeTableItemTextByID(const CString &strID, const CString &strText,int nCol);

signals:
	void sig_ClickOk();  //信号预留使用,供外部调用
private slots:
	void slot_Table_cellClicked ( int , int  );
	void slot_Table_cellChanged ( int , int  );
	void slot_ClickOk();
	void slot_ClickCancel();

public:
	QVBoxLayout *m_MainLayout;
	QHBoxLayout *m_buttonLayout;

	QPushButton *m_BtnOk;
	QPushButton *m_BtnCancel;
	
	CCmbSettingDelegate *m_Cmb;
public:
	QTableWidget *m_table;
	QVector<int> m_combIndexList;//记录combox在表格中的行号
};

#endif // SETTINGVALUEDIALOG_H
