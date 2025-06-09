#include "SttCommCmdWzdGrid.h"
#include "../../UI/Module/CommonCtrl_QT/QIecWidgetDelegate.h"
//#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../../Module/DataMngr/DataGroup.h"
#include "../../../../AutoTest/Module/GbItemsGen/GbSmartGenWzd/GbSmartGenWzd.h"
#include "../Config/MacroTestUI/SttTestCtrrlMacroTestUIMngrGlobal.h"

#include "../../XLangResource_Native.h"

#define COMMCMDWZD_GRID_COLS	2

#define COMMCMDWZD_GRID_INDEX	0
#define COMMCMDWZD_GRID_STEP    0
#define COMMCMDWZD_GRID_CMD		1

CSttCommCmdWzdGrid::CSttCommCmdWzdGrid(QWidget* pparent):QExBaseListGridBase(pparent)
{

}

CSttCommCmdWzdGrid::~CSttCommCmdWzdGrid()
{

}

void CSttCommCmdWzdGrid::InitGrid()
{
 	QExBaseListGridBase::InitGrid();
}

void CSttCommCmdWzdGrid::InitGridTitle()
{
	CString astrGridTitle[COMMCMDWZD_GRID_COLS] = {/*"步骤"*/g_sLangTxt_step, /*"向导"*/g_sLangTxt_Native_Wizard};
	int iGridWidth[COMMCMDWZD_GRID_COLS]={40, 120};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, COMMCMDWZD_GRID_COLS);
}

long CSttCommCmdWzdGrid::GetDatasCount()
{
	long nCount = 0;

	CDataGroup *pROOT = (CDataGroup *)m_pDatas->GetHead();

	if (pROOT == NULL)
	{
		return nCount;
	}

	nCount = 1;
	POS pos = pROOT->GetHeadPosition();

	while (pos != NULL)
	{
		nCount++;
		CDataGroup *pGrp = (CDataGroup *)pROOT->GetNext(pos);//这一级是针对BFT和AFT，是需要合并单元格的

		nCount += pGrp->GetCount();
	}

	return nCount;
}

void CSttCommCmdWzdGrid::ShowDatas(CExBaseList *pDatas, BOOL bResetScrollBars)
{
	DisConnectAll_SigSlot();
	m_pCurrData = NULL;

	if (pDatas == NULL)
	{
		SetRowCount(0);
		return;
	}

	m_pDatas = pDatas;
	CExBaseObject *pObj = NULL;	
	POS pos = pDatas->GetHeadPosition();
	int nRowIndex = 0;//zhouhj Qt中不包括标题行
	long nCalRows = GetDatasCount();//zhouhj Qt中不包括标题行
	SetRowCount(nCalRows, bResetScrollBars);

	while (pos != NULL)
	{
		pObj = pDatas->GetNext(pos);
		ShowData(pObj, nRowIndex, FALSE);
	}

	SetRowCount(nCalRows, bResetScrollBars);
	AfterShowDatas(1, bResetScrollBars);
}

//该表格显示cmd-wzd指令的应答。
/*
m_pDatas 的结构如下
<group name="" id="">
	<group name="选择测试功能和通讯命令" id="ROOT">
		<group id="_BeforeTest_" data-type="" value="">   //这一级需要合并
			<group id="ReadSetting" data-type="read" value="">
				<group id="PT2201APROT$LLN0$dsSetting1" data-type="string"/>
				<group id="PT2201APROT$LLN0$dsSetting2" data-type="string"/>   //显示到表格的最后一级
			</group>
		</group>
		<group id="_AfterTest_" data-type="" value="">   //这一级需要合并
			<group id="WriteSetting" data-type="write" value="">   //显示到表格的最后一级
				<group id="PT2201APROT$LLN0$dsSetting1" data-type="">
					<data id="PDIF1$SG$StrValSG" data-type="STRUCT" value="">
						<value id="PDIF1$SG$StrValSG$setMag$f" data-type="FLOAT" value=""/>
					</data>
				</group>
			</group>
		</group>
	</group>
</group>
*/
void CSttCommCmdWzdGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	//根据上述数据结构，pData为ID == ROOT的对象，且ShowDatas只会循环一次
	CDataGroup *pROOT = (CDataGroup *)pData;
	CString strStep;
	long nSetp = 1;
	strStep.Format(_T("%d"), nSetp);
	//Show_Index(pROOT, nRow, COMMCMDWZD_GRID_INDEX);
	Show_StaticString(pROOT, nRow, COMMCMDWZD_GRID_STEP, strStep);
	Show_StaticString(pROOT, nRow, COMMCMDWZD_GRID_CMD, &pROOT->m_strName);

	POS pos1 = pROOT->GetHeadPosition();
	
	while (pos1 != NULL)
	{
		CDataGroup *pGrp = (CDataGroup *)pROOT->GetNext(pos1);
		if(pGrp->m_strID == STT_CMD_PARA_CMDAFT
			|| pGrp->m_strID == STT_ITEMS_ID_AFTERTEST)
		{
			continue;
		}

		nRow++;
		setSpan(nRow, COMMCMDWZD_GRID_STEP, 1, 2);   //这一级是针对BFT和AFT，是需要合并单元格的（同一行，两列合并）
		Show_StaticString(pGrp, nRow, COMMCMDWZD_GRID_STEP, &pGrp->m_strName); 


		CDataGroup oTempIDList;

		POS pos2 = pGrp->GetHeadPosition();
		while (pos2 != NULL)
		{
			CDataGroup *pCmd = (CDataGroup *)pGrp->GetNext(pos2);
			if(pCmd->m_strID == "ReadSetting"
				|| pCmd->m_strID == "ReadEna")
			{
				//跳过读操作和通信后操作
				continue;
			}

			if(oTempIDList.FindByID(pCmd->m_strID))
			{
				//跳过同ID写操作
				continue;
			}

			nRow++;
			nSetp++;
			strStep.Format(_T("%d"), nSetp);
			Show_StaticString(pCmd, nRow, COMMCMDWZD_GRID_STEP, strStep);
			CString strCmd;

			if (pCmd->m_strDataType == COMMCMD_RWOPTR_WRITE)
			{
				CDataGroup *pDataset = (CDataGroup *)pCmd->GetHead();  //写指令只有一个子对象，记录数据集路径
				strCmd = pCmd->m_strName;
				CString strID = pDataset->m_strID;
				long nPos = pDataset->m_strID.ReverseFind('$');

				if (nPos > 0)
				{
					strID = strID.Mid(nPos + 1);
				}

				strCmd.AppendFormat(_T(" [%s]"), strID.GetString());
				Show_StaticString(pCmd, nRow, COMMCMDWZD_GRID_CMD, strCmd);
			}
			else
			{
				//read和register
				strCmd = pCmd->m_strName;
				strCmd.AppendFormat(_T(" [%s]"), pCmd->m_strID.GetString());
				Show_StaticString(pCmd, nRow, COMMCMDWZD_GRID_CMD, strCmd);
			}

			oTempIDList.AddNewData(pCmd->m_strID, pCmd->m_strName);
		}
	}

	nRow++;
}

//bReset = 1：表示重新显示白色。
void CSttCommCmdWzdGrid::Update_ShowCurr(CExBaseObject *pData, BOOL bReset)
{
	long nRow = GetDataRow(pData);

	if (!bReset)
	{	
		QColor crBlue(0,255,255);  //青色
		SetItemBkColour(nRow, COMMCMDWZD_GRID_STEP, crBlue);
		SetItemBkColour(nRow, COMMCMDWZD_GRID_CMD, crBlue);

		long nRowCount = rowCount();

		if (nRowCount >= nRow + 5)
		{
			nRow += 5;
		}

		QTableWidgetItem *pItem = item(nRow, 0);
		QModelIndex oIndex = indexFromItem(pItem);
		scrollTo(oIndex);
	}
	else
	{
		QColor crWhite(255,255,255);
		SetItemBkColour(nRow, COMMCMDWZD_GRID_STEP, crWhite);
		SetItemBkColour(nRow, COMMCMDWZD_GRID_CMD, crWhite);
	}
}