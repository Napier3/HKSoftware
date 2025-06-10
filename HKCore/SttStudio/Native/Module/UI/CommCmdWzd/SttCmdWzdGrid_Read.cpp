#include "SttCmdWzdGrid_Read.h"
#include "../../UI/Module/CommonCtrl_QT/QIecWidgetDelegate.h"
#include "../../../../AutoTest/Module/GbItemsGen/GbSmartGenWzd/GbSmartGenWzd.h"

#include "../../XLangResource_Native.h"

#define CMDWZD_GRID_READ_COLS	2

#define CMDWZD_GRID_READ_SELECT    0
#define CMDWZD_GRID_READ_DATASET   1

CSttCmdWzdGrid_Read::CSttCmdWzdGrid_Read(QWidget* pparent):QExBaseListGridBase(pparent)
{
	m_pSelect = NULL;
}

CSttCmdWzdGrid_Read::~CSttCmdWzdGrid_Read()
{

}

void CSttCmdWzdGrid_Read::InitGrid()
{
 	QExBaseListGridBase::InitGrid();
	m_pSelect = new QExBaseListCheckBoxDelegate(this);
	setItemDelegateForColumn(0,m_pSelect);
}

void CSttCmdWzdGrid_Read::InitGridTitle()
{
	CString astrGridTitle[CMDWZD_GRID_READ_COLS] = {/*"ѡ��"*/g_sLangTxt_Select, /*"���ݼ�·��"*/g_sLangTxt_datapath};
	int iGridWidth[CMDWZD_GRID_READ_COLS]={40, 120};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, CMDWZD_GRID_READ_COLS);
}

//�ñ����ʾ�����ݼ���ָ�һ�ж�Ӧһ�����ݼ���
/*
m_pDatas = CSttCmdWzd_Step��ʵ��չʾ�����ݽṹ����
<group name="����ֵ" id="ReadSetting" data-type="read" value="">
	<group name="������ֵ���ݼ�1" id="PT2201APROT$LLN0$dsSetting1" data-type="" value=""/>
	<group name="������ֵ���ݼ�2" id="PT2201APROT$LLN0$dsSetting2" data-type="" value=""/>
</group>
*/
void CSttCmdWzdGrid_Read::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	CSttCmdWzd_CmdDataset *pDataset = (CSttCmdWzd_CmdDataset *)pData;
// 	void* p = &pDataset->m_dwReserved;
// 	long *pCheck = reinterpret_cast<long*>(&pDataset->m_dwReserved);

	Show_Check(pDataset, nRow, CMDWZD_GRID_READ_SELECT, &pDataset->m_nSelect); 
	Show_StaticString(pDataset, nRow, CMDWZD_GRID_READ_DATASET, &pDataset->m_strID);

	nRow++;
}