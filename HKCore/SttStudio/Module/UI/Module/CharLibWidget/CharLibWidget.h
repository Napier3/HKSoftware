#ifndef CHARLIBVIEW_H
#define CHARLIBVIEW_H

#include <QWidget>
#include <QItemDelegate>
#include "ui_CharLibWidget.h"
#include "../../../../../Module/OSInterface/OSInterface.h"
#include "QImpCharactWidget.h"


class CSettingDelegate : public QItemDelegate
{
public:
	CSettingDelegate(QObject *parent = NULL);
	~CSettingDelegate();

public:
	virtual QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
		const QModelIndex &index) const;

	virtual void setEditorData(QWidget * editor, const QModelIndex &index) const;

	virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

	virtual void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
		const QModelIndex &index) const;
};

class QCharLibWidget : public QWidget
{
	Q_OBJECT
public:
	QCharLibWidget(QWidget* pParent = NULL);
	virtual ~QCharLibWidget();

	Ui::QCharLibWidget ui;

signals:
	void sig_PbnAddClicked(); //Ìí¼Ó
	void sig_PbnDelClicked(); //É¾³ý
	void sig_CharChanged();
// 	void sig_UpdataCheck(bool, bool, bool);

private:
	BOOL m_bSetting;
	CCharacteristic *m_pCharaObj;
	CCharInterface *m_pInterface;
	CCharacterArea *m_pCharArea;
	CCharInterface *m_pInterfacebak;
	CCharacterArea *m_pCharAreabak;

	QStringList m_PeriodList;
	QStringList m_ErrorPhaseList;
	QList<QComboBox*> m_CmbListParaNo;
	QList<QComboBox*> m_CmbListFaultPha;

	QImpCharactWidget* m_pImpCharactWidget;
	CString m_strLastCharaID;

	int m_nZKCurrentRow;

private:
	void InitUI();
	void InitTableWidget();
	void InitCharactWidget();
	void InitConnect();
	void InitAreaData();
         void InitLanguage();

	void UpdateInterfaceData();
	void UpdateAreaData();
	void UpdateCharacters();

	void AddCharacter(CCharacteristic *pChar);
	CXDrawList* GetDrawListByID(const CString& strID);

private slots:
	void slot_ZkAddChar(CCharacteristic *pObj);
	void slot_ZkPbnAddClicked();
	void slot_ZkPbnDelClicked();
	void slot_ParaNoChanegd(int);
	void slot_FaultPhaChanegd(int);
	void slot_ZKClicked( int nRow,int nCol );
	void slot_Table_cellChanged ( int , int  );
	void slot_Double_Clicked ( int , int  );
	void slot_ParaAddPoint(float fx,float fy);
	void slot_ParaPointChange(float fx,float fy);

public:
	void UpdateZKFeature(CCharacteristic *pObj,BOOL bSetting);
	void DrawSearchPointLine(CPoint ptBegin, CPoint ptEnd, const CString& strCharLib);
	void DrawSearchPointPoint(CPoint ptCur, const CString& strCharLib);
	void SaveCharacteristicsFile();
};

#endif//!CHARLIBVIEW_H