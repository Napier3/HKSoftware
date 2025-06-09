#pragma once

#include "../DataMngr/DataTypes.h"
#include "../BaseClass/ExBaseListTreeCtrl.h"

using namespace std;

#define TALBE_TYPE_PARAMETER		_T("设备参数")
#define TALBE_TYPE_SETTING			_T("保护定值")
#define TALBE_TYPE_ENA				_T("软压板")
#define TALBE_TYPE_MATRIX			_T("跳闸矩阵")

#define HEAD_NAME_COL			_T("名称列全称")
#define HEAD_DW_COL				_T("单位列全称")
#define HEAD_VALUE_COL			_T("定值列全称")

#define DEL_TILTE_ROW			_T("删除单列相等数据")
#define DEL_ROW_DATA			_T("删除行包含数据")


class CPdfConfigData
{
public:
	CPdfConfigData(void);
	~CPdfConfigData(void);

	void LoadPdfConfig(const CString &strFile);
	void SavePdfConfig();

	BOOL IsDatasetTitle(const CString &strText, CString &strTileName);

	CDataType *GetDelRowTilte();
	CDataType *GetDelRowData();

	BOOL IsCheckHead(const CString &strKey, const CString &strText);

	CDataTypes m_oPdfConfigDTS;

private:
	CString m_strFileName;	

	CDataType *GetPdfDataType(CString strKey);

	BOOL IsCheckTitle(const CString &strKey, const CString &strText);

};
