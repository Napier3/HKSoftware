#ifndef CharEditWidget_Distance_H
#define CharEditWidget_Distance_H

#include <QWidget>
#include <QItemDelegate>
#include "CharEditWidgetBase.h"
#include "../../../../../AutoTest/Module/Characteristic/Characteristic.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QGroupBox>
#include <QRadioButton>
#include "../../Controls/SttLineEdit.h"
#include "Grid/ImpCustomPointsGrid.h"

//////////////////////////////////////////////////////////////////////////
//曲线分段表

class QCharEditGrid_Character : public QCharEditGridBase
{
public:
	QCharEditGrid_Character(QWidget* pParent);
	virtual ~QCharEditGrid_Character();

public:
	static void EndEditCell_ZoomIndex(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);
	static void EndEditCell_FaultPhase(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);

public:
	virtual void InitGridTitle();
	virtual void InitDataTypes();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual void slot_CurrentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);
};

//////////////////////////////////////////////////////////////////////////
//曲线参数接口表
class QCharEditGrid_Param : public QCharEditGridBase
{
	Q_OBJECT

public:
	QCharEditGrid_Param(QWidget* pParent);
	virtual ~QCharEditGrid_Param();

public:
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	void GridDoubleClicked_ShowKeyBoard(int nRow,int nCol);

private slots:
		void slot_doubleClicked(int nRow,int nCol);
};

//////////////////////////////////////////////////////////////////////////
//曲线测试点定义表
class QCharEditGrid_TestPoint : public QCharEditGridBase
{
	Q_OBJECT

public:
	QCharEditGrid_TestPoint(QWidget* pParent);
	virtual ~QCharEditGrid_TestPoint();

public:
	virtual void InitGridTitle();
	virtual void InitDataTypes();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

	static void EndEditCell_EdgeType(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);
	void GridDoubleClicked_ShowKeyBoard(int nRow,int nCol);

private slots:
		
		void slot_doubleClicked(int nRow,int nCol);
};

//////////////////////////////////////////////////////////////////////////
//距离widget
class QCharEditWidget_Distance : public QWidget, public QCharEditWidgetBase ,public CExBaseListGridOptrInterface
{
	Q_OBJECT
public:
	QCharEditWidget_Distance(QWidget* pParent = NULL);
	virtual ~QCharEditWidget_Distance();

public:
	void InitUI();
	void InitConnect();
	void InitChar();
	void AddCharacter();
	void UpdateZKFeature(BOOL bSetting);
	void SetDistanceFont();
	void UpdateBtnEnable();

	virtual void UpdateCharacters(BOOL bCharChaged);
	virtual void OnDataSelChanged(QTableWidget *pGridCtrl, int nRow, int nCol);
protected:
	QVBoxLayout *m_pMain_VLayout;
	QHBoxLayout *m_pCharAddHLayout;
	QPushButton *m_pAddCharPushButton;
	QPushButton *m_pDeleteCharPushButton;
	QPushButton *m_pEditCharPushButton;

	QCharEditGrid_Character* m_pGridCharacter;
	QImpCustomPointsGrid* m_pImpCustomPointsGrid;
	QGroupBox *m_pCustom_GroupBox;
	QVBoxLayout *m_pCustom_VLayout;
	QHBoxLayout *m_pCustomAdd_HLayout;
	QPushButton *m_pAddCustomPoint_PushButton;
	QLabel *m_pRXType_Label;
	QRadioButton *m_pZPhi_Radio;
	QRadioButton *m_pRX_Radio;

signals:
	void sig_CharChanged(CExBaseObject *,int);

	private slots:
		void slot_ZkAddChar(CCharacteristic *pObj);
		void slot_ZkPbnAddClicked();
		void slot_btnEditCharClicked();
		void slot_ZkPbnDelClicked();
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//距离widget
class QCharEditWidget_DistanceSearch : public QWidget, public QCharEditWidgetBase ,public CExBaseListGridOptrInterface
{
	Q_OBJECT
private:
	QCharEditGrid_Character* m_pGridCharacter;
	QCharEditGrid_Param* m_pGridParam;
	QCharEditGrid_TestPoint* m_pGridTestPoint;
	CExBaseList m_oLineCache;//add wangtao 20240615创建一个元素对象，防止没有初始化就使用导致崩溃
public:
	QCharEditWidget_DistanceSearch(QWidget* pParent = NULL);
	virtual ~QCharEditWidget_DistanceSearch();

public:
	void InitUI();
	void InitConnect();
	void InitChar();
	void AddCharacter();
	void ShowGridDatas_CharElements();
	void ShowGridDatas_CharVariables();
	void UpdateZKFeature(BOOL bSetting);
	void SetDistanceFont();
	void UpdateBtnEnable();

	virtual void UpdateCharacters(BOOL bCharChaged);
	virtual void OnDataSelChanged(QTableWidget *pGridCtrl, int nRow, int nCol);
protected:
	QVBoxLayout *m_pMain_VLayout;
	QHBoxLayout *m_pCharAddHLayout;
	QHBoxLayout *m_pCharElementHLayout;
	QPushButton *m_pAddCharPushButton;
	QPushButton *m_pDeleteCharPushButton;
	QPushButton *m_pEditCharPushButton;
	QPushButton *m_pInsert_Button;
	QPushButton *m_pModify_Button;
	QPushButton *m_pDelete_Button;

signals:
	void sig_CharChanged(CExBaseObject *,int);

private slots:
	void slot_ZkAddChar(CCharacteristic *pObj);
	void slot_ZkPbnAddClicked();
	void slot_btnEditCharClicked();
	void slot_ZkPbnDelClicked();
	void slot_ZkPbnInsertClicked();//插入元素
	void slot_ZkPbnRemoveClicked();//删除元素
	void slot_ZkPbnEditClicked();//修改元素
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class QCharEditWidget_DistSearchOne : public QWidget, public QCharEditWidgetBase ,public CExBaseListGridOptrInterface
{
	Q_OBJECT
private:
	QCharEditGrid_Param* m_pGridParam;
	QCharEditGrid_TestPoint* m_pGridTestPoint;
	CExBaseList m_oLineCache;

public:
	QCharEditWidget_DistSearchOne(QWidget* pParent = NULL);
	virtual ~QCharEditWidget_DistSearchOne();

public:
	void InitUI();
	CCharacteristic* GetCharacteristic();

	void InitConnect();
	void InitChar();
	void ShowGridDatas_CharElements();
	void ShowGridDatas_CharVariables();
	void UpdateZKFeature(BOOL bSetting);
	void SetDistanceFont();
	void UpdateBtnEnable();
	virtual void UpdateCharacters(BOOL bCharChaged);
	virtual void OnDataSelChanged(QTableWidget *pGridCtrl, int nRow, int nCol);

protected:
	QVBoxLayout *m_pMain_VLayout;
	QHBoxLayout *m_pSelectHLayout;
	QHBoxLayout *m_pCharElementHLayout;
	QLabel *m_pNameLabel;
	QSttLineEdit *m_pNameEdit;
	QPushButton *m_pSelectPushButton;
	QPushButton *m_pInsert_Button;
	QPushButton *m_pModify_Button;
	QPushButton *m_pDelete_Button;

signals:
	void sig_CharChanged(CExBaseObject *,int);

private slots:
	void slot_ZkAddChar(CCharacteristic *pObj);
	void slot_ZkPbnAddClicked();
	void slot_btnEditCharClicked();
	void slot_ZkPbnInsertClicked();//插入元素
	void slot_ZkPbnRemoveClicked();//删除元素
	void slot_ZkPbnEditClicked();//修改元素
	void slot_Name_editingFinished();//更新名称
};


#endif//!CharEditWidget_Distance_H