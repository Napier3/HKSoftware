#ifndef STTMULTIMACROPARAEDITVIEWDISTANCESEARCH_H
#define STTMULTIMACROPARAEDITVIEWDISTANCESEARCH_H

#include <QWidget>
#include "../QSttMultiMacroParaEditViewBase.h"
#include "../Module/CommonGrid/QSttMacroParaEditGrid.h"
#include "DistanceSearchItemParaEditWidget.h"
#include "DistanceSearchAddMultDlg.h"
#include "SttMultiMacroDistanceSearchParasDefine.h"

class QSttMultiMacroParaEditViewDistanceSearch : public QSttMultiMacroParaEditViewBase
{
    Q_OBJECT
public:
    explicit QSttMultiMacroParaEditViewDistanceSearch(const CString &strGridFile,QWidget *parent = 0);
    virtual ~QSttMultiMacroParaEditViewDistanceSearch();

    virtual void InitUI_OneMacro();
    virtual void InitDatas(CSttItems *pCurrRootItems);
	virtual void ConnectAll_SigSlot();
	virtual void DisConnectAll_SigSlot();
	virtual CSttItems* GetRootItems_CurrTestMacro(CSttMacroTest *pSttMacroTest);
    virtual void UpdateParas_To_ZTView();

	virtual char* GetMacroID(){ return STT_ORG_MACRO_DistanceSearchTest_I; }

    //更新特性曲线参数
    virtual void UpdateParasByCharEdit();
    virtual void UpdateCharacteristicParas(CSttMacroTest *pCurrMacroTest);

    virtual BOOL DeleteTestPoint_To_Charact(CSttMacroTest *pCurrMacroTest);
	virtual BOOL AddUpdateTestPoint_To_Charact(CSttMacroTest *pCurrMacroTest, int nState = CHAR_TEST_OBJECT_STATE_NORMAL);
    virtual BOOL AddItem_From_Charact(double dBegX, double dBegY, double dEndX, double dEndY);

protected:
	CSttGdGridInst *m_pGridInst;

private:
//	QDialog *m_pAddMultiItemSelectDlg;//放入基类  zhouhj 2024.9.15
	typedef enum{
		ADDMULTIITEM_DLG = 0,//添加系列
		DELETEITEM_DLG   = 1,//删除测试项目
		CLEARSELRESULT   = 2//清除测试结果
	}SELECTDLG_STATE;
    QVector<int> m_nQuickAddFaultTypeArr;    //快速添加界面故障类型
    QDistanceSearchAddMultDlg *m_pDistanceSearchMultDlg;    //添加系列-添加系列窗口

private:
	void InitAddMultiItemSelectDlg(QPoint pos,int nDlgState);
    void GetMacroTestDataToParas(CDataGroup *pParas, CExBaseList* pInnerTestmacro); //20240821 wanmj 从测试项获取公共参数给m_oTestMacroUI_Paras
    void SetValueToParas(CDataGroup *pParas, CSttMacroTestParaData *pData);  //20240821 wanmj
    void CheckAllPresence(CExBaseList *pParas);
    void CheckMacroTestAllPresence(CExBaseList *pListItems);
    void InitGridTitleLanguage();   //20241025 wanmj 表格表头多语言处理
    void SetValueToInstColName(CSttGdInst_Col *pSttGdInst_Col);
    //快速添加添加测试项
    void AddDistanceSearchItemQuick();

    //同步最大灵敏角到特性曲线
    void SetCharactMaxSensAng();

signals:

public slots:
	virtual void slot_AddOneItemBtnClick();//添加单个测试项
	virtual void slot_AddMultiItemBtnClick();//添加系列
	virtual void slot_CommonParasBtnClick();//通用参数
	virtual void slot_BinarysBtnClick();//开关量

	virtual void slot_AddMultiItemQuickBtnClick();//添加系列-快速添加
	virtual void slot_AddMultiItemDlgBtnClick();//添加系列-添加系列
	virtual void slot_AddMultiItemBatchDlgBtnClick();//添加系列-批量添加

	virtual void slot_DeleteItemBtnClick();//删除测试项
	virtual void slot_DeleteSelItemBtnClick();//删除当前选择
	virtual void slot_DeleteAllItemBtnClick();//删除全部

	virtual void slot_ClearResultBtnClick();//清除测试结果
	virtual void slot_ClearSelResultBtnClick();//清除全部结果
	virtual void slot_ClearAllResultBtnClick();//清除所有结果

	virtual void slot_ParaEditWidget_To_Grid(CSttMacroTest* pMacroTest);
    //表格参数修改后,更新到当前参数编辑界面
    virtual void slot_Grid_To_ParaEditWidget(CSttMacroTest* pMacroTest);

    //添加系列添加测试项
    void slot_AddDistanceSearchItem(int nFaultType, double dSettingTime, int nZoneType, double dBegZ, double dBegAng, double dEndZ, double dEndAng,
                                    double dFaultCur, double dFaultVolt, double dRelErr, double dAbsErr, int nErrType);

};

#endif // STTMULTIMACROPARAEDITVIEWDISTANCESEARCH_H
