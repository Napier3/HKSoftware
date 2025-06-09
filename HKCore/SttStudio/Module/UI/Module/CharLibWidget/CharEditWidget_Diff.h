#ifndef CharEditWidget_Diff_H
#define CharEditWidget_Diff_H

#include <QWidget>
#include <QLabel>
#include "ui_CharEditWidget_Diff.h"
#include "CharEditWidgetBase.h"
#include "CharEditMainWidget.h"
#include "../../../../../Module/FaultCal/DiffCharCal.h"
#include "../../../../../AutoTest/Module/Characteristic/Characteristic.h"
#include <QStackedWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QRadioButton>
class QCharEditRadioNormalWidget;
class QCharEditRadioHarmWidget;


#define DIFF_GRID_CLOS 4
#define CharDiff_ID_StartCurr_Check              _T("StartCurr_Check")//启动电流选择
#define CharDiff_ID_RateCoef1_Check              _T("RateCoef1_Check")//比率指定系数1选择
#define CharDiff_ID_RateCoef2_Check              _T("RateCoef2_Check")//比率指定系数2选择
#define CharDiff_ID_RateCoef3_Check              _T("RateCoef3_Check")//比率指定系数3选择
#define CharDiff_ID_QuickCurr_Check              _T("QuickCurr_Check")//差动速断选择
#define CharDiff_ID_IDoor                        _T("IDoor")//差动门槛值
#define CharDiff_ID_IQuickSetting                _T("IQuickSetting")//差动速断定值
#define CharDiff_ID_Limp1                        _T("Limp1")//拐点1电流值
#define CharDiff_ID_Limp2                        _T("Limp2")//拐点2电流值
#define CharDiff_ID_Limp3                        _T("Limp3")//拐点3电流值
#define CharDiff_ID_StartCurr_Kid                _T("StartCurr_Kid")//启动段斜率
#define CharDiff_ID_RateCoef_Kid1                _T("RateCoef_Kid1")//差动斜率1
#define CharDiff_ID_RateCoef_Kid2                _T("RateCoef_Kid2")//差动斜率2
#define CharDiff_ID_RateCoef_Kid3                _T("RateCoef_Kid3")//差动斜率3
#define CharDiff_ID_RateHarm                      _T("RateHarm")//谐波制动系数
#define CharDiff_ID_CTPoint							_T("CTPoint")//CT极性

#define CharDiff_ID_MinAxis                      _T("MinAxis")//定值整定方式
#define CharDiff_ID_Insel                        _T("Insel")//基准电流选择
#define CharDiff_ID_In                           _T("In")//基准电流(其它)
#define CharDiff_ID_HarmIndex                    _T("HarmIndex")//谐波次数

#define CharDiff_RateCoef1_Index                 1
#define CharDiff_RateCoef2_Index                 2
#define CharDiff_RateCoef3_Index                 3
#define CharDiff_QuickCurr_Index                 4

#define CharDiff_ID_StartCurrPointNum              _T("StartCurrPointNum")
#define CharDiff_ID_RateCoef1PointNum              _T("RateCoef1PointNum")   
#define CharDiff_ID_RateCoef2PointNum              _T("RateCoef2PointNum")   
#define CharDiff_ID_RateCoef3PointNum              _T("RateCoef3PointNum")   
#define CharDiff_ID_QuickCurrPointNum              _T("QuickCurrPointNum")   

#define CharDiff_ID_StartCurrErrorBand              _T("StartCurrErrorBand")
#define CharDiff_ID_RateCoef1ErrorBand              _T("RateCoef1ErrorBand")
#define CharDiff_ID_RateCoef2ErrorBand              _T("RateCoef2ErrorBand")
#define CharDiff_ID_RateCoef3ErrorBand              _T("RateCoef3ErrorBand")
#define CharDiff_ID_QuickCurrErrorBand              _T("QuickCurrErrorBand")


#define ElecRailway_TransType_0_YV                         0
#define ElecRailway_TransType_1_YD11                       1//无转角
#define ElecRailway_TransType_2_Single                     2
#define ElecRailway_TransType_3_YDD                        3
#define ElecRailway_TransType_4_Scott1                     4
#define ElecRailway_TransType_5_VV1                        5
#define ElecRailway_TransType_6_VX                         6
#define ElecRailway_TransType_7_YA                         7
#define ElecRailway_TransType_8_ThreeVV                    8
#define ElecRailway_TransType_9_Scott2                     9
#define ElecRailway_TransType_10_Scott3                    10
#define ElecRailway_TransType_11_VV2                       11
#define ElecRailway_TransType_12_Scott4                    12
#define ElecRailway_TransType_13_ThreeVV2                  13
#define ElecRailway_TransType_14_ThreeVV3                  14
#define ElecRailway_TransType_15_ThreeYV2                  15//无转角
#define ElecRailway_TransType_16_Scott5                    16
#define ElecRailway_TransType_17_YD11_YT                   17//在Y侧进行转角
#define ElecRailway_TransType_18_ThreeYV2_YT               18//在Y侧进行转角

//QCharEditGrid_DiffLine表格
class QCharEditGrid_DiffLine : public QCharEditGridBase
{
	Q_OBJECT

public:
	QCharEditGrid_DiffLine(QWidget* pParent);
	virtual ~QCharEditGrid_DiffLine();

public:
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual void EmitCharChanged();
	void GridDoubleClicked_ShowKeyBoard(int nRow,int nCol);
	static void EndEditCell_TestPoints(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);
	static void EndEditCell_ErrorBand(int nRow, int nCol, QGV_ITEM *pCell, QExBaseListGridBase *pGrid);

	void EmitTestPointsErrorBandChanged();
	virtual void slot_CurrentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);

signals:
	void sig_TestPointsErrorBandChanged();
	void sig_DiffCharChanged();

private slots:
	void slot_doubleClicked(int nRow,int nCol);
};

////////////////////////////////////////////////////////线路差动///////////////////////////////////////////////////////////////////////////////////////
class QCharEditWidget_LineDiff : public QWidget, public QCharEditWidgetBase, public CExBaseListGridOptrInterface
{
	Q_OBJECT

public:
	QCharEditWidget_LineDiff(BOOL bShowIp2,QWidget *parent = 0);//参数1确认是否显示斜率2
	~QCharEditWidget_LineDiff();

	QCharEditGrid_DiffLine *m_pGridCharLine;
	QCharEditMainWidget* m_pMainWidget; 

signals:
	void sig_CharChanged(CExBaseObject *,int);

private:
//	Ui::QCharEditWidget_Diff ui;
	QVBoxLayout *m_pMain_VLayout;
	QGridLayout *m_pDiffChar_GridLayout;
	QHBoxLayout *m_pCustomAdd_HLayout;

	//特性曲线相关控件
	QLabel *m_pCharName_Label;
	QLabel *m_pCharSetting_Label;
	QLabel *m_pCharCurrent_Label;
	QLabel *m_pCharK_Label;

	QLabel *m_pIcdqd_Label;
	QLabel *m_pK1_Label;
	QCheckBox *m_pK2_CheckBox;

	QLabel *m_pIcdqd_SettingLabel;
	QLabel *m_pK1_SettingLabel;
	QLabel *m_pK2_SettingLabel;
	QLabel *m_pMaxId_Label;//差流极值

	QSttLineEdit *m_pIcdqd_Edit;
	QSttLineEdit *m_pIp1_Edit;
	QSttLineEdit *m_pIp2_Edit;
	QSttLineEdit *m_pMaxId_Edit;//差流极值

	QSttLineEdit *m_pKcdqd_Edit;
	QSttLineEdit *m_pKp1_Edit;
	QSttLineEdit *m_pKp2_Edit;
	BOOL m_bShowIp2;


	//添加自定义点相关控件
	QLabel *m_pIdCustom_Label;
	QSttLineEdit *m_pIdCustom_Edit;
	QSpacerItem *m_pAddCustom_HorizontalSpacer;
	QPushButton *m_pAddCustomPoint_PushButton;
	QPushButton *m_pClearCustomPoint_PushButton;

	CDiffCharCal m_oDiffCharCal;

public:
	void InitUI();
	void InitConnect();
	void InitChar();
	void UpdateChar(BOOL bUpdateTable = FALSE,BOOL bCharTypeChanged = FALSE,BOOL bParasChanged = TRUE);//参数2位是否比率制动和谐波制动切换,参数3为是否参数改变更新
	void InitDiffData();
	void InitUI_Unit();//更新界面单位
	float SetParaI(QLineEdit* pEdit, float& fv);
	float SetParaK(QLineEdit* pEdit, float& fv);
	float SetLimit(float min,float max,float val);
	float CalLineK(CCharElementLined* pLine);

	void SetDiffFont(); //2022-10-31 sy  设置字体
	virtual void OnLeftButtonDown();

	virtual void GroupDatasToChar(CDataGroup *pDatas);//将模板视图数据赋值给特性曲线界面
	virtual void CharToGroupDatas(CDataGroup *pDatas);//将特性曲线界面参数数据赋值给模板视图数据
	void UpdateEdit_IrValueUserPoint();//更新用户自定义点制动电流值
	virtual void OnDataSelChanged(QTableWidget *pGridCtrl, int nRow, int nCol);//20230731 wxy 激活线段


protected:
	void UpdateEditsDisEnable();//更新编辑框控件的非使能状态
	void ShowDatas_Table();//把线段显示到表格里,并对线段重新命名
	void GetTestPointNumErrorBand();
	CCharacteristic* GetCurrentCharacter();//比例制动or谐波制动

private slots:
	void on_m_chkLine2_clicked();
	void on_m_edtSet_Istart_editingFinished();
	void on_m_edtSet_Kstart_editingFinished();
	void on_m_edtSet_Ip1_editingFinished();
	void on_m_edtSet_K1_editingFinished();
	void on_m_edtSet_Ip2_editingFinished();
	void on_m_edtSet_K2_editingFinished();
	void on_m_onlineEdit_Changed();
	void slot_TestPointsErrorBandChanged();
	void slot_DiffCharChanged();
	void slot_IdValue_editingFinished();
	void slot_MaxIdEditingFinished();

	void slot_btnUserAdd(bool bState);
	void slot_btnUserClear(bool bState);
};

////////////////////////////////////////////////////////变压器差动//////////////////////////////////////////////////////////////////////////////////////
class QCharEditWidget_Diff : public QWidget, public QCharEditWidgetBase, public CExBaseListGridOptrInterface
{
	Q_OBJECT

public:
	QCharEditWidget_Diff(QWidget *parent = 0);
	~QCharEditWidget_Diff();

	QCharEditGrid_DiffLine *m_pGridCharLine;

signals:
	void sig_CharChanged(CExBaseObject *,int);

private:
	Ui::QCharEditWidget_Diff ui;

	CDiffCharCal m_oDiffCharCal;
	
public:
	void InitUI();
	void InitConnect();
	void InitChar();
	void UpdateChar(BOOL bUpdateTable = FALSE,BOOL bCharTypeChanged = FALSE,BOOL bParasChanged = TRUE);//参数2位是否比率制动和谐波制动切换
	void InitDiffData();
	void InitUI_Unit();//更新界面单位
	void EnableEdit(long nIndex);
	void DisableEdit(long nIndex);
	float SetParaI(QLineEdit* pEdit, float& fv);
	float SetParaK(QLineEdit* pEdit, float& fv);
	float SetLimit(float min,float max,float val);
	float CalLineK(CCharElementLined* pLine);

	void SetDiffFont(); //2022-10-31 sy  设置字体

//	virtual void AddTestPoint(CExBaseList* pValue);
	virtual void OnLeftButtonDown();

	virtual void GroupDatasToChar(CDataGroup *pDatas);//将模板视图数据赋值给特性曲线界面
	virtual void CharToGroupDatas(CDataGroup *pDatas);//将特性曲线界面参数数据赋值给模板视图数据
	void UpdateEdit_IrValueUserPoint();//更新用户自定义点制动电流值
	virtual void OnDataSelChanged(QTableWidget *pGridCtrl, int nRow, int nCol);
	
	QCharEditMainWidget* m_pMainWidget;//20230808 suyang 多处设置为父窗口 使用全局变量不用多次设置

protected:
	void UpdateEditsDisEnable();//更新编辑框控件的非使能状态
	void ShowDatas_Table();//把线段显示到表格里,并对线段重新命名
	void GetTestPointNumErrorBand();
	CCharacteristic* GetCurrentCharacter();//比例制动or谐波制动
	bool IsNotHarm();

private slots:
    void on_m_chkStart_clicked();
    void on_m_chkLine1_clicked();
    void on_m_chkLine2_clicked();
    void on_m_chkLine3_clicked();
    void on_m_chkLineSd_clicked();
    void on_m_edtSet_Istart_editingFinished();
    void on_m_edtSet_Kstart_editingFinished();
    void on_m_edtSet_Ip1_editingFinished();
    void on_m_edtSet_K1_editingFinished();
    void on_m_edtSet_Ip2_editingFinished();
    void on_m_edtSet_K2_editingFinished();
    void on_m_edtSet_Ip3_editingFinished();
    void on_m_edtSet_K3_editingFinished();
    void on_m_edtSet_Isd_editingFinished();
	void on_m_onlineEdit_Changed();
	void slot_TestPointsErrorBandChanged();
	void slot_DiffCharChanged();
	void slot_IdValue_editingFinished();

	void slot_btnUserAdd(bool bState);
	void slot_btnUserClear(bool bState);

	void slot_radioNormal_Clicked();
	void slot_radioHarm_Clicked();
	void slot_CmbSettingMinAxisIndexChanged(int nIndex);
	void slot_CmbInSeIndexChanged(int nIndex);
	void slot_CmbHarmIndexChanged(int nIndex);
	void slot_InSet_editingFinished();
	void slot_HarmCoef_editingFinished();
};

//////////////////////////////////////////////////////牵引变差动//////////////////////////////////////////////////////////////////////////////////////
class QCharEditWidget_ElecRailwayDiff : public QWidget, public QCharEditWidgetBase
{
	Q_OBJECT

public:
	QCharEditWidget_ElecRailwayDiff(QWidget *parent = 0);
	~QCharEditWidget_ElecRailwayDiff();

	QCharEditRadioNormalWidget *m_qCharRadioNormalWidget;
	QCharEditRadioHarmWidget *m_qCharRadioHarmWidget;
	QCharEditMainWidget* m_pMainWidget; 
	CDiffCharCal m_oDiffCharCal;

signals:
	void sig_CharChanged(CExBaseObject *,int);	

public:
	void InitUI();
	void InitConnect();
	void InitChar();
	void InitUI_Unit();//更新界面单位
	void UpdateChar(BOOL bUpdateTable = FALSE,BOOL bCharTypeChanged = FALSE,BOOL bParasChanged = TRUE);//参数2位是否比率制动和谐波制动切换
	float SetParaI(QLineEdit* pEdit, float& fv);
	float SetParaK(QLineEdit* pEdit, float& fv);
	float SetLimit(float min,float max,float val);
	float CalLineK(CCharElementLined* pLine);

	void SetDiffFont(); //2022-10-31 sy  设置字体
	virtual void OnLeftButtonDown();
	virtual void GroupDatasToChar(CDataGroup *pDatas);//将模板视图数据赋值给特性曲线界面
	virtual void CharToGroupDatas(CDataGroup *pDatas);//将特性曲线界面参数数据赋值给模板视图数据

protected:
	void ShowDatas_Table();//把线段显示到表格里,并对线段重新命名
	void GetTestPointNumErrorBand();
	CCharacteristic* GetCurrentCharacter();//比例制动or谐波制动
	bool IsNotHarm();

private slots:
	void on_m_onlineEdit_Changed();
	void IdValue_NormalEditing(CString strIdValue);
	void ChangeMainWin_Char();
	void slot_TestPointsErrorBandChanged();
	void slot_DiffCharChanged();
	void slot_radioNormal_Clicked();
	void slot_radioHarm_Clicked();
	void slot_ChangeICMAxisName();
	void slot_UpdateChar(bool bUpdateTable,bool bCharTypeChanged,bool bParasChanged);
	void slot_ActiveSegment(CCharElement *pCurrSelElement);

public:
	CDataGroup *m_pDataGroup;
	long m_nCTPoint;//2023-07-13 wxy CT极性 1-一侧指向变压器 0-两侧指向变压器
	long m_nTranSort;//2023-07-14 wxy 变压器接线形式

private:
	QVBoxLayout *m_mainQVBoxLayout;
	QHBoxLayout *m_QHBoxLayout;
	QWidget *m_QHBoxWidget;
	QRadioButton *m_radioNormal,*m_radioHarm;
	QStackedWidget *m_stackedWidget;
	
};

#endif // CharEditWidget_Diff_H
