#include "StdAfx.h"
#include "DvmAnlsGrid.h"
#include "DvmDataAnalyse.h"
#include "..\..\Module\KeyDb\XMatchObject.h"

//////////////////////////////////////////////////////////////////////////
//CDvmAnlsDatasetGrid
CDvmAnlsDatasetGrid::CDvmAnlsDatasetGrid()
{
	m_nAdjustBeginCol = 0;

}


CDvmAnlsDatasetGrid::~CDvmAnlsDatasetGrid(void)
{

}




void CDvmAnlsDatasetGrid::InitGrid()
{
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(DVM_ANLS_COLS);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}

void CDvmAnlsDatasetGrid::InitGridTitle()
{
	CString cTempStr[DVM_ANLS_COLS]={_T("序号"),_T("名称"),_T("包含的关键字"),_T("测试子模板")};
	int iWidth[DVM_ANLS_COLS]={60,320, 320,320};

	CExBaseListGrid::InitGridTitle(cTempStr, iWidth, DVM_ANLS_COLS);
}	

CString CDvmAnlsDatasetGrid::InitDataKey(CExBaseObject *pExBaseObject)
{
	CString   KeyWords;
// 	CXMatchObject oXMatchObj;
// 
// 	oXMatchObj.m_listMatchXKeys.DeleteAll();
// 	oXMatchObj.Init(pExBaseObject,CTempFuncXmlRWFuncs::GetXKeyDB());
// 
// 	POS pos1 = oXMatchObj.m_listMatchXKeys.GetHeadPosition();
// 	CXKeyMatchRef  *p1 = NULL;
// 
// 	while (pos1 != NULL)
// 	{	
// 		p1=oXMatchObj.m_listMatchXKeys.GetNext(pos1);
// 		if (p1->m_pXKeyRef !=NULL)
// 		{
// 			if (p1->m_pXKeyRef->IsArrayKey())
// 			{
// 				KeyWords.AppendFormat(_T("%s[%d]"), p1->m_pXKeyRef->m_strName, p1->m_nArrayIndex);
// 			}
// 			else
// 			{
// 				KeyWords+=p1->m_pXKeyRef->m_strName;
// 			}
// 
// 			KeyWords+="     ";
// 		}
// 	}

	return KeyWords;
}


void CDvmAnlsDatasetGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	UINT nClassID = pData->GetClassID();

	Show_Index(pData, nRow, DVM_ANLS_COL_INDEX);
	//#################
	//修改为CDvmDataAnalyse的显示，即调用GetKeys获得Keys
	CDvmDataAnalyse *pDataAnls = (CDvmDataAnalyse*)pData;
	CString   strText, strTempName;
	strText=pDataAnls->GetKeys();

	Show_StaticString(pData, nRow, DVM_ANLS_COL_NAME, &pDataAnls->m_pDvmDataRef->m_strName);
	Show_StaticString(pData, nRow, DVM_ANLS_COL_KEYS, strText);

	//添加显示子模板的代码  GetTemps
	strTempName = pDataAnls->GetTemps();   //#################
	Show_StaticString(pData, nRow, DVM_ANLS_COL_STXML, strTempName);

	nRow++;
}
