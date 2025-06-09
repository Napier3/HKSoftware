#ifndef STTMULTIMACROPARAEDITVIEWLOWVOL_H
#define STTMULTIMACROPARAEDITVIEWLOWVOL_H

#include <QWidget>
#include "./QLowVolAddMultDlg.h"
#include "./LowVolActItemParaEditWidget.h"
#include "./LowVolTimeItemParaEditWidget.h"
#include "./LowVolDvdtItemParaEditWidget.h"
#include "./LowVolILockItemParaEditWidget.h"
#include "../LowVol/LowVolCommonParasDlg.h"
#include "../LowVol/LowVolBinarysDlg.h"
#include "../QSttMultiMacroParaEditViewBase.h"
#include "../Module/CommonGrid/QSttMacroParaEditGrid.h"

#include "../../../../Module/TestMacro/TestMacro.h"
#include "../../../../Module/TestMacro/TestMacros.h"


class QSttMultiMacroParaEditViewLowVol : public QSttMultiMacroParaEditViewBase
{
    Q_OBJECT

public:
    explicit QSttMultiMacroParaEditViewLowVol(const CString &strGridFile,QWidget *parent = 0);
    virtual ~QSttMultiMacroParaEditViewLowVol();

	virtual void InitUI_OneMacro();
    virtual void InitUI_MultiMacro();
	virtual void InitDatas(CSttItems *pCurrRootItems);
	virtual void ConnectAll_SigSlot();
	virtual void DisConnectAll_SigSlot();

	virtual char* GetMacroID(){ return STT_ORG_MACRO_LowVolTest_I; }

	//添加单个测试项时,获取当前项目需要添加的父节点,如距离保护,需要按故障类型进行分类,如当前父节点Items不存在需要单独创建
	virtual CSttItems* GetRootItems_CurrTestMacro(CSttMacroTest *pSttMacroTest);

	virtual void Update_MultiMacroParaEditView();
protected:
	CSttGdGridInst *m_pGridInst_ActValue;
	CSttGdGridInst *m_pGridInst_ActTime;
	CSttGdGridInst *m_pGridInst_SlipTrip;
	CSttGdGridInst *m_pGridInst_IBlock;

public slots:

	virtual void slot_AddMultiItemBtnClick();//添加系列
	virtual void slot_CommonParasBtnClick();//通用参数
	virtual void slot_BinarysBtnClick();//开关量
	virtual void slot_DeleteItemBtnClick();//删除测试项
	virtual void slot_ClearResultBtnClick();//清除测试结果
	void slot_CurrMacroParaEditGridChanged(int);//当前显示测试项表格改变


	virtual void slot_DeleteSelItemBtnClick();//删除当前选择
	virtual void slot_DeleteAllItemBtnClick();//删除全部

	virtual void slot_ClearSelResultBtnClick();//清除全部结果
	virtual void slot_ClearAllResultBtnClick();//清除所有结果
private: 
	CDataGroup *m_pParas;
//	QDialog *m_pAddMultiItemSelectDlg;//添加系列选择页面//放入基类  zhouhj 2024.9.15
	QStringList m_strTabTitleList;

	void InitAddMultiItemSelectDlg(QPoint pos,int nDlgState);
	void InitGridTitleLanguage();   //表格表头多语言处理
	void SetValueToInstColName(CSttGdInst_Col *pSttGdInst_Col, int nLowFreqType = LOWVOL_ID_PsuLowVolAct);
	typedef enum{
		ADDMULTIITEM_DLG = 0,//添加系列
		DELETEITEM_DLG   = 1,//删除测试项目
		CLEARSELRESULT   = 2//清除测试结果
	}SELECTDLG_STATE;
	CExBaseList *m_pBinarysParas;//通用参数链表
	void SetBinarysParas(CExBaseList *pParas);
	void CheckForBinarys(CExBaseList *pParas, CString strID);
};
void Global_GetAllMacroTest(CExBaseList *pSingleMacroItemsRef,CSttItems *pMulitMacroRootItems,CTestMacro *pSingleMacroRef);
#endif // STTMULTIMACROPARAEDITVIEWLowVol_H
