#ifndef QSTTMACROPARAEDITGRID_H
#define QSTTMACROPARAEDITGRID_H

#include "../../../UI/Module/QExBaseListGridBase/QExBaseListGridBase.h"
#include "../SttTestGridDefine/SttGdGridInst.h"
#include "../../../SttCmd/GuideBook/SttMacroTest.h"
#include "../../../Module/TestMacro/TestMacro.h"
#include "../../../AutoTest/Module/AutoTestGlobalDefine.h"
#include "../../../UI/Controls/SettingCtrls/QSettingItem.h"
#include "../../../../../AutoTest/Module/Characteristic/Characteristics.h"

//选择、状态、测试结果展示是3个特殊列
#define STT_MACRO_PARA_EDIT_GRID_ID_Select                 "Select"
#define STT_MACRO_PARA_EDIT_GRID_ID_State                  "State"
#define STT_MACRO_PARA_EDIT_GRID_ID_TestRslt               "TestRslt"

class QSttMacroParaEditGrid : public QExBaseListGridBase
{
	Q_OBJECT
public:
	explicit QSttMacroParaEditGrid(QWidget *parent);
	virtual ~QSttMacroParaEditGrid();
public:
	void InitColDef(CSttGdGridInst *pCurrGridInst,CTestMacro *pSingleMacroRef,CDataTypes *pMacroDataTypes);

	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

	virtual void DisConnectAll_SigSlot();
	virtual void ConnectAll_SigSlot();
	virtual void SetModifiedFlag(CExBaseObject *pData, BOOL bModified=TRUE);
	virtual void  Show_StatePic(CExBaseObject *pData, const int& nRow, const int& nCol, long *pnState, GRID_CELL_EDIT_FUNC pFunc=NULL);
	virtual void  Show_TestResult(CSttMacroTest *pSttMacroTest, const int& nRow, const int& nCol, long nState, CSttGdInst_Col *pSttGdInst_Col);
	virtual void  Show_RateDouble(CExBaseObject *pData, const int& nRow, const int& nCol, long nPrecision, CString *pstrValue, DWORD nReserved,BOOL bCanEdit = TRUE);
	virtual void  Show_Double_Zsetting(CExBaseObject *pData, const int& nRow, const int& nCol, long nPrecision, CString *pstrValue,
		DWORD nReserved,BOOL bCanEdit = TRUE);
	//用于定值关联数据对象的界面显示
	virtual void  Show_Double_SettingAttach(CExBaseObject *pData, const int& nRow, const int& nCol, long nPrecision, CString *pstrValue, BOOL bCanEdit = TRUE,
		GRID_CELL_EDIT_FUNC pFunc = NULL, BOOL bUnitConversion = TRUE);
	virtual CDataType* FindDataType(const CString &strDataType);
	virtual CExBaseObject* GetCurrSelData(long nStateForCol=0);
	CSttMacroTest* GetCurrSelSttMacroTest();//获取当前选择测试项目对象

//	virtual void SelectSttMacroTest(CSttMacroTest *pCurrSelData);
	virtual void SelectRow(CExBaseObject *pCurrSelData);
	virtual void SelectRow(int nRow);

	//20240808 huangliang	
	virtual void UpdateObjectText(const int& nRow, const int& nCol, CExBaseObject *pData); //CVariantDataAddress oVarAddress);	//20240923 huangliang 是使用对象，不是结构体
	virtual BOOL IsAttachSettingItem(QGV_ITEM *pCell);//20240926 huangliang 当前单元格是否关联了定值

public:
	void ShowDataGdUI(CSttMacroTestPara* pMacroPara,CSttGdColDef *pColDef,int nRow,int nCol);

	static void EndEditCell_RateDoubleString(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);
	static void EndEditCell_ZSettingDoubleString(int nRow, int nCol, QGV_ITEM *pCell, QExBaseListGridBase *pGrid);
	static void EndEditCell_SelectStateCheck(int nRow, int nCol, QGV_ITEM *pCell, QExBaseListGridBase *pGrid);//zhouhj 2024.10.12
//	static void EndEditCell_DoubleString_ParaEdit(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);
	static void EndEditCell_ZAngDoubleString(int nRow, int nCol, QGV_ITEM *pCell, QExBaseListGridBase *pGrid);//luozibing 20241014

	CSttGdGridInst *m_pCurrGridInst;
	CCharacteristics *m_pCharacteristics_Items;//该测试功能关联的特性曲线集合对象

protected:
	void ShowData_ImpedanceCustomItem(CSttMacroTestPara* pMacroPara, CSttMacroTestParaData *pSttMacroTestParaData,
		CSttGdColDef *pColDef, int nRow, int nCol);
	CString GetDataTypeValueName(CString strDataTypeID, CString strIndex);

	virtual long GetDataRowEx(CExBaseObject *pData, long nFromRow, long nCol);
	QWidget *m_pParentWidget;
	CTestMacro *m_pSingleMacroRef;//
	CDataTypes* m_pMacroDataTypes;

signals:
	void sig_UpdateParaEditWidget(CSttMacroTest* pSttMacroTest);
	
};

CSttMacroTestParaData *Global_FindAddMacroTestParaData(CSttMacroTestPara* pMacroPara,CTestMacro *pSingleMacro, const CString &strParaID);
CSttMacroTestParaData *Global_FindAddMacroTestParaData(CSttMacroTest* pSttMacroTest,CTestMacro *pSingleMacro, const CString &strParaID);
void Global_CreateAllParaDatas(CSttMacroTestParaDatas* pSttTestParaDatas, CTestMacro *pSingleMacro);//创建全部的参数数据,对于不存在的参数数据从CTestMacro中获取

#endif // QSTTMACROPARAEDITGRID_H
