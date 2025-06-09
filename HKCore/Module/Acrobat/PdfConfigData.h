#pragma once

#include "../DataMngr/DataTypes.h"
#include "../BaseClass/ExBaseListTreeCtrl.h"

using namespace std;

#define TALBE_TYPE_PARAMETER		_T("�豸����")
#define TALBE_TYPE_SETTING			_T("������ֵ")
#define TALBE_TYPE_ENA				_T("��ѹ��")
#define TALBE_TYPE_MATRIX			_T("��բ����")

#define HEAD_NAME_COL			_T("������ȫ��")
#define HEAD_DW_COL				_T("��λ��ȫ��")
#define HEAD_VALUE_COL			_T("��ֵ��ȫ��")

#define DEL_TILTE_ROW			_T("ɾ�������������")
#define DEL_ROW_DATA			_T("ɾ���а�������")


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
