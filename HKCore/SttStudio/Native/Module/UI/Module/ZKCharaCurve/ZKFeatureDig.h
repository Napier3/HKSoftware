#ifndef ZKFEATUREDIG_H
#define ZKFEATUREDIG_H

#include <QItemDelegate>
#include <QDialog>
#include <QComboBox>
#include "ui_ZKFeatureDig.h"
#include "../../Module/Define.h"
#include "../../Module/TestWinFrame/testwinbase.h"

class CSettingDelegate : public QItemDelegate
{
public:
	CSettingDelegate(QObject *parent = NULL);
	~CSettingDelegate();

	virtual QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
		const QModelIndex &index) const;

	virtual void setEditorData(QWidget * editor, const QModelIndex &index) const;

	virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

	virtual void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
		const QModelIndex &index) const;
};

class ZKFeatureDig : public QDialog
{
	Q_OBJECT

public:
	ZKFeatureDig(CCharacteristic *pObj, BOOL bSetting, QWidget *parent = 0);
	~ZKFeatureDig();
private slots:
	void slot_Table_cellChanged ( int , int  );
	void slot_Double_Clicked ( int , int  );
	void slot_PbnAddClicked();
	void slot_PbnDelClicked();
	void slot_PbnDelAllClicked();
	void slot_PbnOkClicked();
	void slot_PbnCancelClicked();
signals:
	void sig_ZKChanged();
private:
	CCharacteristic *m_pCharaObj;
	CCharInterface *m_pInterface;
	CCharacterArea *m_pCharArea;
	CCharInterface *m_pInterfacebak;
	CCharacterArea *m_pCharAreabak;
	QComboBox *m_cmbSetting; 
	QStringList m_strList;
	BOOL m_bSetting;
private:
	Ui::ZKFeatureDig ui;
private:
	void InitTableWidget();
	void InitConnections();
	void InitInterfaceData();
        void InitLanguage();
	void InitAreaData();
};

#endif // ZKFEATUREDIG_H
