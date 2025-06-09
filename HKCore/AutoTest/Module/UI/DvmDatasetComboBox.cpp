// D:\WorkPM\Source\PMTest\GuideBookDev\UI\CommCmd\DvmDatasetComboBox.cpp : 实现文件
//

#include "stdafx.h"
#include "DvmDatasetComboBox.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDvmDatasetComboBox

IMPLEMENT_DYNAMIC(CDvmDatasetComboBox, CComboBox)

CDvmDatasetComboBox::CDvmDatasetComboBox()
{
}

CDvmDatasetComboBox::~CDvmDatasetComboBox()
{
}


BEGIN_MESSAGE_MAP(CDvmDatasetComboBox, CComboBox)
END_MESSAGE_MAP()


BOOL CDvmDatasetComboBox::GetSelectID(CString &strID)
{
	CExBaseObject *pSel = GetSelectObject();

	if (pSel == NULL)
	{
		return FALSE;
	}
	else
	{
		CExBaseObject *pCpu = NULL;
		pCpu = (CExBaseObject*)pSel->GetParent();
		strID.Format(_T("%s$%s"), pCpu->m_strID, pSel->m_strID);
		return TRUE;
	}
}

CExBaseObject* CDvmDatasetComboBox::SetCurrSelByID(const CString &strID)
{
	int nCount = GetCount();
	CExBaseObject* pObj = NULL;
	CExBaseObject* pFind = NULL;
	long nFind = CB_ERR;
	CExBaseObject *pCpu = NULL;
	CString strPath;

	for (int i=0;i<nCount;i++)
	{
		pObj = (CExBaseObject*)GetItemDataPtr(i);

		if (pObj != NULL)
		{
			pCpu = (CExBaseObject*)pObj->GetParent();
			strPath.Format(_T("%s$%s"), pCpu->m_strID, pObj->m_strID);

			if (strPath == strID)
			{
				nFind = i;
				pFind = pObj;
				break;
			}
		}
	}

	SetCurSel(nFind);

	return pFind;//(nFind != CB_ERR);
}

// CDvmDatasetComboBox 消息处理程序

void CDvmDatasetComboBox::InitComboBox(CExBaseObject* pItem, const CString &strCpuID, const CString &strDataset)
{
	ResetContent();
	ASSERT(pItem != NULL);

	if(pItem == NULL)
	{
		return;
	}

	//获取设备节点
	CExBaseList oListDataset;
	CDevice* pDevice = (CDevice*) pItem->GetAncestor(GBCLASSID_DEVICE);
	ASSERT(pDevice != NULL);
	pDevice->GetDataSetList(strDataset, oListDataset, DSID_ALL_DVM);
	
	InitComboBox(oListDataset, strCpuID);

	oListDataset.RemoveAll();
}

void CDvmDatasetComboBox::InitComboBox(CExBaseList &oListDataset, const CString &strIDPath)
{
	ResetContent();
	POS pos = oListDataset.GetHeadPosition();
	CExBaseObject *pDataset = NULL;
	CExBaseObject *pCpu = NULL;
	CString strText;
	long nItem = 0;

	while (pos != NULL)
	{
		pDataset = (CExBaseObject *)oListDataset.GetNext(pos);
		AddObj(pDataset);
	}

	//选中当前项目
	SetSelByID(strIDPath);
}


long CDvmDatasetComboBox::AddObj(CExBaseObject *pObj)
{
	CExBaseObject *pCpu = NULL;
	CString strText;
	long nItem = 0;

	pCpu = (CExBaseObject *)pObj->GetParent();
	strText.Format(_T("%s $ %s"), pCpu->m_strName, pObj->m_strName);
	nItem = AddString(strText);
	SetItemDataPtr(nItem, pObj);

	return nItem;
}
