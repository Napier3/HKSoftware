#ifndef CharEditWidget_Diff_Eng_H
#define CharEditWidget_Diff_Eng_H

#include "../CharEditWidget_Diff.h"
#include "ui_CharEditWidget_Diff_Eng.h"
#include "CharEditMainDialog.h"
#include "CharactEditWidget_Eng.h"

#define DIFF_GRID_PARAM_CLOS 3
#define DIFF_GRID_SECTION_CLOS 2
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
#define CharDiff_ID_RateHarm                     _T("RateHarm")//谐波制动系数
#define CharDiff_ID_CTPoint						 _T("CTPoint")//CT极性
#define CharDiff_ID_CustomChar					 _T("_bCustomChar")//是否自定义曲线
#define CharDiff_ID_ComBineFeature				 _T("CombineFeature")//组合特性
#define CharDiff_ID_ZeroSeqElimiType			 _T("ZeroSeqElimiType")//零序消除方式
#define CharDiff_ID_FaultType					 _T("FaultType")//故障类型
#define CharDiff_ID_TransGroupMode				 _T("TransGroupMode")//钟点数

#define CharDiff_ID_MinAxis                      _T("MinAxis")//定值整定方式
#define CharDiff_ID_Insel                        _T("Insel")//基准电流选择
#define CharDiff_ID_In                           _T("In")//基准电流(其它)
#define CharDiff_ID_HarmIndex                    _T("HarmIndex")//谐波次数

#define CharDiff_ID_HarmRate_AbsErrPlus                    _T("HarmRate_AbsErrPlus")//谐波制动搜索值正绝对误差限
#define CharDiff_ID_HarmRate_AbsErrMinus                    _T("HarmRate_AbsErrMinus")//谐波制动搜索值负绝对误差限
#define CharDiff_ID_ActTime_AbsErrPlus                    _T("ActTime_AbsErrPlus")//比率制动动作时间正绝对误差限
#define CharDiff_ID_ActTime_AbsErrMinus                    _T("ActTime_AbsErrMinus")//比率制动动作时间负绝对误差限

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

//QCharEditGrid_DiffLine_Eng表格
class QCharEditGrid_DiffLine_Eng : public QCharEditGridBase
{
	Q_OBJECT

public:
	QCharEditGrid_DiffLine_Eng(QWidget* pParent);
	virtual ~QCharEditGrid_DiffLine_Eng();

public:
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow = TRUE);
	virtual void EmitCharChanged();
	void GridDoubleClicked_ShowKeyBoard(int nRow, int nCol);
	static void EndEditCell_TestPoints(int nRow, int nCol, QGV_ITEM *pCell, QExBaseListGridBase *pGrid);
	static void EndEditCell_ErrorBand(int nRow, int nCol, QGV_ITEM *pCell, QExBaseListGridBase *pGrid);

	void EmitTestPointsErrorBandChanged();
	virtual void slot_CurrentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);

signals:
	void sig_TestPointsErrorBandChanged();
	void sig_DiffCharChanged();

	private slots:
	void slot_doubleClicked(int nRow, int nCol);
};
//////////////////////////////////////////////////////////////////////////
//曲线参数接口表
class QCharEditGrid_Param_Diff : public QCharEditGridBase
{
	Q_OBJECT

public:
	QCharEditGrid_Param_Diff(QWidget* pParent);
	virtual ~QCharEditGrid_Param_Diff();

public:
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow = TRUE);
	void GridDoubleClicked_ShowKeyBoard(int nRow, int nCol);
	CExBaseObject *m_CurrentCharacter;

private slots:
	void slot_doubleClicked(int nRow, int nCol);
};
//////////////////////////////////////////////////////////////////////////
//曲线区段参数接口表
class QCharEditGrid_Section_Diff : public QCharEditGridBase
{
	Q_OBJECT

public:
	QCharEditGrid_Section_Diff(QWidget* pParent);
	virtual ~QCharEditGrid_Section_Diff();

public:
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow = TRUE);
	void GridDoubleClicked_ShowKeyBoard(int nRow, int nCol);
	CExBaseObject *m_CurrentCharacter;

	private slots:
	void slot_doubleClicked(int nRow, int nCol);
};
////////////////////////////////////////////////////////差动(国际版)曲线编辑//////////////////////////////////////////////////////////////////////////////////////
class QCharEditWidget_Diff_Eng : public QWidget, public QCharEditWidgetBase, public CExBaseListGridOptrInterface
{
	Q_OBJECT

public:
	QCharEditWidget_Diff_Eng(QWidget *parent = 0);
	~QCharEditWidget_Diff_Eng();

	QCharEditGrid_DiffLine_Eng *m_pGridCharLine;
	QCharEditGrid_Param_Diff *m_pGridParam;
	QCharEditGrid_Section_Diff * m_pGridSection;

signals:
	void sig_CharChanged(CExBaseObject *, int);

private:
	Ui::QCharEditWidget_Diff_Eng ui;

	CDiffCharCal m_oDiffCharCal;

	float	m_nInSet2; //谐波基准电流
	float	m_nActAbsErr;//动作值绝对误差
	float	m_nActRelErr;//动作值相对误差
	float	m_nActTimeRelErr;//时间相对误差
	float	m_nActTimeAbsErrPlus;//时间绝对误差
	float	m_nActTimeAbsErrMinus;//时间绝对误差
	float	m_nSearchBegin;//搜索始值
	float	m_nSearchEnd;//搜索终值
	float	m_nIDoor;//门槛值
	float	m_nIQuick;//速断值
	CString m_strIDPath;//自定义曲线的路径
	bool    m_bIsCustomswitch;//判断是否从自定义曲线切换至整定定值
	long	m_nComBineFeature;//组合特性
	long	m_nZeroSeqElimiType;//零序消除方式
	long     m_nFaultType;//记录当前主界面选中行的故障类型
	long		m_nTransGroupMode;//记录钟点数
	bool  m_bIsCharRaised;//记录曲线是否已经被抬高过
	long	m_nCustomChar;//记录是否为自定义曲线
	CCharacteristic* m_pCurrCharacteristic;//记录打开曲线编辑时的自定义曲线
public:
	void InitUI();
	void InitConnect();
	void InitChar();
	void UpdateChar(BOOL bUpdateTable = FALSE, BOOL bCharTypeChanged = FALSE, BOOL bParasChanged = TRUE);//参数2位是否比率制动和谐波制动切换
	void InitDiffData();
	void InitUI_Unit();//更新界面单位
	void EnableEdit(long nIndex);
	void DisableEdit(long nIndex);
	float SetParaI(QLineEdit* pEdit, float& fv);
	float SetLimit(float min, float max, float val);
	float CalLineK(CCharElementLined* pLine);

	void SetDiffFont(); //2022-10-31 sy  设置字体

	//	virtual void AddTestPoint(CExBaseList* pValue);
	virtual void OnLeftButtonDown();

	virtual void GroupDatasToChar(CDataGroup *pDatas);//将模板视图数据赋值给特性曲线界面
	virtual void CharToGroupDatas(CDataGroup *pDatas);//将特性曲线界面参数数据赋值给模板视图数据
	void UpdateEdit_IrValueUserPoint();//更新用户自定义点制动电流值
	virtual void OnDataSelChanged(QTableWidget *pGridCtrl, int nRow, int nCol);

	QCharEditMainDialog* m_pMainWidget;//20230808 suyang 多处设置为父窗口 使用全局变量不用多次设置

	void UpDataParas();
	void ImportChar();
	void ShowGridDatas_CharVariables();

protected:
	void UpdateEditsDisEnable();//更新编辑框控件的非使能状态
	void ShowDatas_Table();//把线段显示到表格里,并对线段重新命名
	void GetTestPointNumErrorBand();
	CCharacteristic *GetCurrentCharacter();//比例制动or谐波制动
	CCharacteristics *m_pCharacteristics_Inner;//特性曲线编辑页面参数
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
	void slot_m_cbTypeSel_currentIndexChanged(const QString &strText);
	void slot_TestPointsErrorBandChanged();
	void slot_DiffCharChanged();

	void slot_radioNormal_Clicked();
	void slot_radioHarm_Clicked();
	void slot_CmbSettingMinAxisIndexChanged(int nIndex);
	void slot_CmbInSeIndexChanged(int nIndex);
	void slot_CmbHarmIndexChanged(int nIndex);
	void slot_InSet_editingFinished();
	void slot_HarmCoef_editingFinished();
	void slot_Currm_DiffTypeTabChanged(int);
	void slot_m_radioUser_toggled(bool checked);

	void slot_CmbSettingMinAxis2IndexChanged(int nIndex);
	void slot_CmbInSe2IndexChanged(int nIndex);
	void slot_InSet2_editingFinished();
	void slot_m_editIDoor_editingFinished();
	void slot_m_editIQuick_editingFinished();
	void slot_ShowGridDatas_EmitCharChanged(CExBaseObject *);
	void on_m_editCustomHarmIndex_editingFinished();

	void slot_CmbCombinedFeatureIndexChanged(int nIndex);
	void slot_CmbCombinedFeature2IndexChanged(int nIndex);
	void slot_CmbZeroSeqElimiTypeIndexChanged(int nIndex);
	void slot_CmbZeroSeqElimiType2IndexChanged(int nIndex);
	void slot_UpdateCharByCombinedFeature();//根据组合特性更新曲线
	void CalByCombinedFeature(BOOL bIsCharRaise);//根据组合特性更新界面数值
};

#endif // CharEditWidget_Diff_Eng_H
