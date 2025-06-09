#ifndef STTMULTIMACROPARAEDITVIEWCURRINVERSETIME_H
#define STTMULTIMACROPARAEDITVIEWCURRINVERSETIME_H

#include <QWidget>
#include "../QSttMultiMacroParaEditViewBase.h"
#include "../Module/CommonGrid/QSttMacroParaEditGrid.h"
#include "../../../../Module/TestMacro/TestMacro.h"
#include "../../UI/SttTestCntrFrameBase.h"

#include "CurrInverTimeItemParaEditWidget.h"
#include "CurrInverAddMultDlg.h"
#include "CurrInverCommonParasDlg.h"
#include "CurrInverBinarysDlg.h"

class QSttMultiMacroParaEditViewCurrInverseTime : public QSttMultiMacroParaEditViewBase
{
    Q_OBJECT

public:
    explicit QSttMultiMacroParaEditViewCurrInverseTime(const CString &strGridFile,QWidget *parent = 0);
    virtual ~QSttMultiMacroParaEditViewCurrInverseTime();

	virtual void InitUI_OneMacro();
	virtual void InitDatas(CSttItems *pCurrRootItems);
	virtual void ConnectAll_SigSlot();
	virtual void DisConnectAll_SigSlot();
	virtual char* GetMacroID(){ return STT_ORG_MACRO_CurrInverseTimeTest_I; }

	//添加单个测试项时,获取当前项目需要添加的父节点,如距离保护,需要按故障类型进行分类,如当前父节点Items不存在需要单独创建
	virtual CSttItems* GetRootItems_CurrTestMacro(CSttMacroTest *pSttMacroTest);

//	virtual BOOL AddTestPoint_To_Charact(CSttMacroTest *pCurrMacroTest);//添加测试项时,在特性曲线界面添加对应测试点
	virtual BOOL DeleteTestPoint_To_Charact(CSttMacroTest *pCurrMacroTest);
	virtual BOOL AddUpdateTestPoint_To_Charact(CSttMacroTest *pCurrMacroTest, int nState = CHAR_TEST_OBJECT_STATE_NORMAL);

	//从特性曲线添加测试项
	virtual BOOL AddItem_From_Charact(double dX, double dY);
	virtual BOOL UpdateCurrItem_From_Charact(double dX, double dY);

public slots:
	virtual void slot_AddOneItemBtnClick();//添加单项
	virtual void slot_AddMultiItemBtnClick();//添加系列
	virtual void slot_CommonParasBtnClick();//通用参数
	virtual void slot_BinarysBtnClick();//开关量
	virtual void slot_DeleteItemBtnClick();//删除测试项
	virtual void slot_ClearResultBtnClick();//清除测试结果

	virtual void slot_DeleteSelItemBtnClick();//删除当前
	virtual void slot_DeleteAllItemBtnClick();//删除全部

	virtual void slot_ClearSelResultBtnClick();//清除当前
	virtual void slot_ClearAllResultBtnClick();//清除全部

	//void slot_ParaEditWidget_To_Draw(CSttMacroTest* pMacroTest);

protected:
	CSttGdGridInst *m_pCurrInst;

private:

//	QDialog *m_pAddMultiItemSelectDlg;//添加系列选择页面//放入基类  zhouhj 2024.9.15
	void InitAddMultiItemSelectDlg(QPoint pos,int nDlgState);
	void CheckAllPresence();

	void GetMacroTestDataToParas(CDataGroup *pParas, CExBaseList* pInnerTestmacro); //20240805 wanmj 从测试项获取公共参数给m_oTestMacroUI_Paras

	//添加系列-电流相位不使用模版生成添加
	void AddMultiItems(CDataGroup *pParas, CExBaseList* pInnerTestmacro);//故障类型的测试点循环
	void GetValueToData(CDataGroup *pParas, CSttMacroTestParaData *pData);  //20241016 gongyiping
	void CloneMacroTestPage(CString str);//20241017 gongyiping 克隆当前页面
	void UpDataMacroTestPage();//20241017 gongyiping 更新下发参数
	void GetMacroTestParasToData(CDataGroup *pParas, CExBaseList* pInnerTestmacro);//20241016 gongyiping 从m_oTestMacroUI_Paras给测试项,添加系列电流相位

	void CheckAllPresence(CExBaseList *pParas);
	void CurrInverseCheckExist(CExBaseList *pParas, CString strID);
	void SetValueToParas(CDataGroup *pParas, CSttMacroTestParaData *pData);  //20240805 wanmj

	//参数编辑界面修改后,更新到当前选择表格
	virtual void slot_ParaEditWidget_To_Grid(CSttMacroTest* pMacroTest);

	typedef enum{
		DELETEITEM_DLG   = 0,//删除测试项目
		CLEARSELRESULT   = 1//清除测试结果
	}SELECTDLG_STATE;
};

#endif // STTMULTIMACROPARAEDITVIEWCURRINVERSETIME_H
