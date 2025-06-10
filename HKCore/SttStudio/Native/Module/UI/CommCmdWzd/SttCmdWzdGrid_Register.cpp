#include "SttCmdWzdGrid_Register.h"
#include "../../UI/Module/CommonCtrl_QT/QIecWidgetDelegate.h"
#include "../../../../AutoTest/Module/GbItemsGen/GbSmartGenWzd/GbSmartGenWzd.h"

#include "../../XLangResource_Native.h"

#define CMDWZD_GRID_REGISTER_COLS	6

#define CMDWZD_GRID_REGISTER_SELECT    0
#define CMDWZD_GRID_REGISTER_DATASET   1
#define CMDWZD_GRID_REGISTER_CHANGE    2
#define CMDWZD_GRID_REGISTER_QUALITY   3
#define CMDWZD_GRID_REGISTER_PERIOD    4
#define CMDWZD_GRID_REGISTER_PERIOD_T  5

QSttCmdWzdGrid_Register_CheckBoxDelegate::QSttCmdWzdGrid_Register_CheckBoxDelegate(QObject *parent)
: QExBaseListCheckBoxDelegate(parent)
{
	CString strEmptyPath;
	strEmptyPath =  _P_GetResourcePath();
	strEmptyPath += _T("Empty.png");
	m_oEmptyPixmap.load(strEmptyPath);
	m_oEmptyPixmap.scaled(20,20);

	m_pCmdGrpRef = NULL;
}

QSttCmdWzdGrid_Register_CheckBoxDelegate::~QSttCmdWzdGrid_Register_CheckBoxDelegate()
{

}

//��굥����Ԫ���ʱ���ػ��¼�����
void QSttCmdWzdGrid_Register_CheckBoxDelegate::paint(QPainter * painter,
										   const QStyleOptionViewItem & option,
										   const QModelIndex & index) const
{
	bool bChecked = index.model()->data(index, Qt::CheckStateRole).toBool();//����ͼƬ
	QRect rect = option.rect;
	QPoint pt = rect.center();

	QGV_ITEM* pCurItem = GetCurrItem(index);

	if ((pCurItem != NULL)&&(pCurItem->lParam != 0))
	{
		PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCurItem->lParam;
		CSttCmdWzd_CmdDataset *pDataset = (CSttCmdWzd_CmdDataset *)pVCellData->pObj;

		if (m_pCmdGrpRef->m_strID == _T("UnRegisterReport") || pDataset->m_nSelect == 0)
		{
			//			QItemDelegate::paint(painter,option,index);
			pt -= QPoint(m_oEmptyPixmap.width()/2,m_oSelectedPixmap.height()/2);
			painter->drawPixmap(pt, m_oEmptyPixmap);
			return;
		}
	}

	if(bChecked)
	{
		pt -= QPoint(m_oSelectedPixmap.width()/2,m_oSelectedPixmap.height()/2);
		painter->drawPixmap(pt, m_oSelectedPixmap);
	}
	else
	{
		pt -= QPoint(m_oUnselectedPixmap.width()/2,m_oUnselectedPixmap.height()/2);
		painter->drawPixmap(pt, m_oUnselectedPixmap);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
CSttCmdWzdGrid_Register::CSttCmdWzdGrid_Register(QWidget* pparent):QExBaseListGridBase(pparent)
{

}

CSttCmdWzdGrid_Register::~CSttCmdWzdGrid_Register()
{

}

void CSttCmdWzdGrid_Register::InitGrid()
{
 	QExBaseListGridBase::InitGrid();
	m_pSelect = new QExBaseListCheckBoxDelegate(this);
	setItemDelegateForColumn(0,m_pSelect);
	m_pChange = new QSttCmdWzdGrid_Register_CheckBoxDelegate(this);
	setItemDelegateForColumn(2,m_pChange);
	m_pQuality = new QSttCmdWzdGrid_Register_CheckBoxDelegate(this);
	setItemDelegateForColumn(3,m_pQuality);
	m_pPeriod = new QSttCmdWzdGrid_Register_CheckBoxDelegate(this);
	setItemDelegateForColumn(4,m_pPeriod);
}

void CSttCmdWzdGrid_Register::InitGridTitle()
{
	CString astrGridTitle[CMDWZD_GRID_REGISTER_COLS] = {/*"ѡ��"*/g_sLangTxt_Select, /*"���ݼ�·��"*/g_sLangTxt_datapath, /*"�Ƿ�仯����"*/g_sLangTxt_Native_SendChanges, /*"�Ƿ�Ʒ������"*/g_sLangTxt_quality, /*"�Ƿ���������"*/g_sLangTxt_period, /*"����ʱ��(ms)"*/g_sLangTxt_Native_CycleTm+"(ms)"};
	int iGridWidth[CMDWZD_GRID_REGISTER_COLS]={40, 200, 90, 90, 90, 90};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, CMDWZD_GRID_REGISTER_COLS);
}

//�ñ����ʾ�����ݼ���ָ�һ�ж�Ӧһ�����ݼ���
/*
m_pDatas = CSttCmdWzd_Step��ʵ��չʾ�����ݽṹ����
<group name="��������" id="RegisterReport" data-type="register" value="">
	<group name="ң�����ݼ�" id="PT2201ALD0$LLN0$dsAin" data-type="" value=""/>
	<group name="ģ����" id="PT2201APROT$LLN0$dsRelayAin" data-type="" value=""/>
</group>
*/
void CSttCmdWzdGrid_Register::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	CSttCmdWzd_CmdDataset *pDataset = (CSttCmdWzd_CmdDataset *)pData;
	//long *pCheck = reinterpret_cast<long*>(&pDataset->m_dwReserved);
	CSttCmdWzd_Step *pCurrStep = (CSttCmdWzd_Step *)m_pDatas;
	BOOL bEnable = TRUE;
	m_pChange->m_pCmdGrpRef = pCurrStep->m_pCmdGrpRef;
	m_pQuality->m_pCmdGrpRef = pCurrStep->m_pCmdGrpRef;
	m_pPeriod->m_pCmdGrpRef = pCurrStep->m_pCmdGrpRef;

	if (pCurrStep->m_pCmdGrpRef->m_strID == _T("UnRegisterReport") || pDataset->m_nSelect == 0)
	{
		bEnable = FALSE;
	}

	Show_Check(pDataset, nRow, CMDWZD_GRID_REGISTER_SELECT, &pDataset->m_nSelect, EndEditCell_Select); 
	Show_StaticString(pDataset, nRow, CMDWZD_GRID_REGISTER_DATASET, &pDataset->m_strID);

	Show_Check(pDataset, nRow, CMDWZD_GRID_REGISTER_CHANGE, &pDataset->m_nChange, NULL, bEnable);
	Show_Check(pDataset, nRow, CMDWZD_GRID_REGISTER_QUALITY, &pDataset->m_nQuqlity, NULL,bEnable);
	Show_Check(pDataset, nRow, CMDWZD_GRID_REGISTER_PERIOD, &pDataset->m_nPeriod, NULL, bEnable);  

	if (bEnable)
	{
		Show_Long(pDataset, nRow, CMDWZD_GRID_REGISTER_PERIOD_T, &pDataset->m_nPeriod_Time); 
	}
	else
	{
		CString strPeriodTime;
		strPeriodTime.Format(_T("%d"), pDataset->m_nPeriod_Time);
		Show_StaticString(pDataset, nRow, CMDWZD_GRID_REGISTER_PERIOD_T, strPeriodTime);
	}  

	nRow++;
}

void CSttCmdWzdGrid_Register::EndEditCell_Select(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL && pCell != NULL && pGrid != NULL);
	ASSERT(pVCellData->pObj != NULL);

	CSttCmdWzd_CmdDataset *pDataset = (CSttCmdWzd_CmdDataset *)pVCellData->pObj;
	CSttCmdWzdGrid_Register* pThis = (CSttCmdWzdGrid_Register *)pGrid;
	pThis->ShowData(pDataset, nRow, FALSE);

// 	Show_Check(pDataset, nRow, CMDWZD_GRID_REGISTER_SELECT, &pDataset->m_nSelect, EndEditCell_Select, FALSE);
// 
// 	Show_Check(pDataset, nRow, CMDWZD_GRID_REGISTER_CHANGE, &pDataset->m_nChange, NULL, bEnable);
// 	Show_Check(pDataset, nRow, CMDWZD_GRID_REGISTER_QUALITY, &pDataset->m_nQuqlity, NULL,bEnable);
// 	Show_Check(pDataset, nRow, CMDWZD_GRID_REGISTER_PERIOD, &pDataset->m_nPeriod, NULL, bEnable); 
}