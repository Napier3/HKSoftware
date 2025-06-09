#ifndef CharEditWidget_Distance_Eng_H
#define CharEditWidget_Distance_Eng_H

#include "../CharEditWidget_Distance.h"
#include "CharactEditWidget_Eng.h"
#include <QCheckBox>
//曲线分段表

class QCharEditGrid_Character_Eng : public QCharEditGrid_Character
{
public:
	QCharEditGrid_Character_Eng(QWidget* pParent);
	virtual ~QCharEditGrid_Character_Eng();
	
	static void EndEditCell_ZoomIndex_Eng(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);
	static void EndEditCell_FaultPhase_Eng(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);
	static void EndEditCell_Check_UseZone_Eng(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);
public:
	virtual void InitGridTitle();
	virtual void InitDataTypes();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual void ShowDatas(CExBaseList *pDatas, BOOL bResetScrollBars=TRUE);
protected:
	int FindTheSameZoomAndFault(int nRow,QExBaseListGridBase *pGrid);
	CExBaseList m_oInitCharacter;//当前选中项初始区段与故障相
};
//////////////////////////////////////////////////////////////////////////
//曲线参数接口表
class QCharEditGrid_Param_Eng : public QCharEditGrid_Param
{
	Q_OBJECT

public:
	QCharEditGrid_Param_Eng(QWidget* pParent);
	virtual ~QCharEditGrid_Param_Eng();

public:
	virtual void InitGridTitle();
	virtual void InitDataTypes();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

	static void EndEditCell_CheckBit(int nRow, int nCol, QGV_ITEM *pCell, QExBaseListGridBase *pGrid);
	static void EndEditCell_CheckBit_RelError(int nRow, int nCol, QGV_ITEM *pCell, QExBaseListGridBase *pGrid);
	static void EndEditCell_CheckBit_AbsError(int nRow, int nCol, QGV_ITEM *pCell, QExBaseListGridBase *pGrid);
protected:
	void InitDistance_ErrorDataType(const CString &strErrorZone);
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//距离widget
class QCharEditWidget_DistanceSearch_Eng : public QWidget, public QCharEditWidgetBase ,public CExBaseListGridOptrInterface
{
	Q_OBJECT
private:
	QCharEditGrid_Character_Eng* m_pGridCharacter;
	QCharEditGrid_Param_Eng* m_pGridParam;
	CExBaseList m_oLineCache;//add wangtao 20240615创建一个元素对象，防止没有初始化就使用导致崩溃

public:
	QCharEditWidget_DistanceSearch_Eng(QWidget* pParent = NULL);
	virtual ~QCharEditWidget_DistanceSearch_Eng();

public:
	void InitUI();
	void InitConnect();
	void InitChar();
	void AddCharacter();
	void ShowGridDatas_CharVariables();
	void UpdateZKFeature(BOOL bSetting);
	void SetDistanceFont();
	void UpdateBtnEnable();

	virtual void UpdateCharacters(BOOL bCharChaged);
	virtual void OnDataSelChanged(QTableWidget *pGridCtrl, int nRow, int nCol);

	CExBaseObject* FindTSeting(CExBaseList *pParas);
	CExBaseObject* FindAbsErr_Plus(CExBaseList *pParas);
	CExBaseObject* FindAbsErr_Minus(CExBaseList *pParas);
	CExBaseObject* FindRelErr(CExBaseList *pParas);
	CExBaseObject* FindErrorLogic(CExBaseList *pParas);

	virtual void CheckZoneParas();
	virtual void CharToGroupDatas(CDataGroup *pDatas);//将特性曲线界面参数数据赋值给模板视图数据

    void UpdateCharacterErrBand();  //20241013 wanmj 特性曲线编辑界面误差带仅显示选中曲线的

public:
    CString m_strUI_ID;     //界面功能ID 20240828 wanmj


protected:
	QVBoxLayout *m_pMain_VLayout;
	QHBoxLayout *m_pCharAddHLayout;
	QPushButton *m_pAddCharPushButton;
	QPushButton *m_pDeleteCharPushButton;
	QPushButton *m_pEditCharPushButton;

	CCharacteristics *m_pCharacteristics_Inner;//特性曲线编辑页面参数
	CExBaseList m_oTestPoint_Inner;//保存最初单个特性曲线编辑页面参数

	void CheckZoneParas(CExBaseList *pParas);
	void SetZoneParas(CCharacteristic *pCurrCharaObj);
signals:
	void sig_CharChanged(CExBaseObject *,int);

private slots:
	void slot_ZkAddChar(CCharacteristic *pObj);
	void slot_ZkPbnAddClicked();
	void slot_btnEditCharClicked();
	void slot_ZkPbnDelClicked();
};

#endif//!CharEditWidget_Distance_Eng_H