#include "StdAfx.h"
#include "GridDeviceComCfg.h"
#include "..\..\ProcotolProject\PpCfgDevices.h"

#define COMCFG_COL_STRUCT_VALUE   14

CGridDeviceComCfg::CGridDeviceComCfg(void)
{
	//各种通讯配置对象的起始列
	m_nTcpServerCol = -1;
	m_nTcpClientCol = -1;
	m_nUdpServerCol = -1;
	m_nUdpClientCol = -1;
	m_nSerialCol = -1;
}

CGridDeviceComCfg::~CGridDeviceComCfg(void)
{
}

#define width_ip_col     120
#define width_port_col  60

long CGridDeviceComCfg::InitCmmCfgColIndex_TcpServer(long &nColIndex, GV_ITEM &Item)
{
	m_nTcpServerCol = nColIndex;
	InsertColumn(_T(""));
	InsertColumn(_T(""));

	Item.row = 0;
	Item.col = nColIndex;
	Item.szText = _T("TCP Server");
	SetItem(&Item);
	Merge(0, nColIndex, 0, nColIndex+1);

	SetColumnWidth(nColIndex, width_ip_col);
	Item.row = 1;
	Item.col = nColIndex++;
	Item.szText = _T("IP");
	SetItem(&Item);

	SetColumnWidth(nColIndex, width_port_col);
	Item.col = nColIndex++;
	Item.szText = _T("Port");
	SetItem(&Item);

	return nColIndex;
}

long CGridDeviceComCfg::InitCmmCfgColIndex_TcpClient(long &nColIndex, GV_ITEM &Item)
{
	m_nTcpClientCol = nColIndex;
	InsertColumn(_T(""));
	InsertColumn(_T(""));
	InsertColumn(_T(""));
	InsertColumn(_T(""));

	Item.row = 0;
	Item.col = nColIndex;
	Item.szText = _T("TCP Client");
	SetItem(&Item);
	Merge(0, nColIndex, 0, nColIndex+3);

	SetColumnWidth(nColIndex, width_ip_col);
	Item.row = 1;
	Item.col = nColIndex++;
	Item.szText = _T("Local IP");
	SetItem(&Item);

	SetColumnWidth(nColIndex, width_port_col);
	Item.col = nColIndex++;
	Item.szText = _T("Local Port");
	SetItem(&Item);

	SetColumnWidth(nColIndex, width_ip_col);
	Item.row = 1;
	Item.col = nColIndex++;
	Item.szText = _T("Remote IP");
	SetItem(&Item);

	SetColumnWidth(nColIndex, width_port_col);
	Item.col = nColIndex++;
	Item.szText = _T("Remote Port");
	SetItem(&Item);

	return nColIndex;
}

long CGridDeviceComCfg::InitCmmCfgColIndex_UdpServer(long &nColIndex, GV_ITEM &Item)
{
	m_nUdpServerCol = nColIndex;
	InsertColumn(_T(""));
	InsertColumn(_T(""));

	Item.row = 0;
	Item.col = nColIndex;
	Item.szText = _T("Udp Server");
	SetItem(&Item);
	Merge(0, nColIndex, 0, nColIndex+1);

	SetColumnWidth(nColIndex, width_ip_col);
	Item.row = 1;
	Item.col = nColIndex++;
	Item.szText = _T("IP");
	SetItem(&Item);

	SetColumnWidth(nColIndex, width_port_col);
	Item.col = nColIndex++;
	Item.szText = _T("Port");
	SetItem(&Item);

	return nColIndex;
}

long CGridDeviceComCfg::InitCmmCfgColIndex_UdpClient(long &nColIndex, GV_ITEM &Item)
{
	m_nUdpClientCol = nColIndex;
	InsertColumn(_T(""));
	InsertColumn(_T(""));
	InsertColumn(_T(""));
	InsertColumn(_T(""));

	Item.row = 0;
	Item.col = nColIndex;
	Item.szText = _T("Udp Client");
	SetItem(&Item);
	Merge(0, nColIndex, 0, nColIndex+3);

	SetColumnWidth(nColIndex, width_ip_col);
	Item.row = 1;
	Item.col = nColIndex++;
	Item.szText = _T("Local IP");
	SetItem(&Item);

	SetColumnWidth(nColIndex, width_port_col);
	Item.col = nColIndex++;
	Item.szText = _T("Local Port");
	SetItem(&Item);

	SetColumnWidth(nColIndex, width_ip_col);
	Item.row = 1;
	Item.col = nColIndex++;
	Item.szText = _T("Remote IP");
	SetItem(&Item);

	SetColumnWidth(nColIndex, width_port_col);
	Item.col = nColIndex++;
	Item.szText = _T("Remote Port");
	SetItem(&Item);

	return nColIndex;
}

long CGridDeviceComCfg::InitCmmCfgColIndex_Serial(long &nColIndex, GV_ITEM &Item)
{
	m_nSerialCol = nColIndex;
	InsertColumn(_T(""));
	InsertColumn(_T(""));
	InsertColumn(_T(""));
	InsertColumn(_T(""));
	InsertColumn(_T(""));

	Item.row = 0;
	Item.col = nColIndex;
	Item.szText = _T("Serial");
	SetItem(&Item);
	Merge(0, nColIndex, 0, nColIndex+4);

	SetColumnWidth(nColIndex, width_ip_col);
	Item.row = 1;
	Item.col = nColIndex++;
	Item.szText = _T("Port");
	SetItem(&Item);

	SetColumnWidth(nColIndex, width_port_col);
	Item.col = nColIndex++;
	Item.szText = _T("Baund Rate");
	SetItem(&Item);

	SetColumnWidth(nColIndex, width_port_col);
	Item.col = nColIndex++;
	Item.szText = _T("Data Bit");
	SetItem(&Item);

	SetColumnWidth(nColIndex, width_port_col);
	Item.col = nColIndex++;
	Item.szText = _T("Parity");
	SetItem(&Item);

	SetColumnWidth(nColIndex, width_port_col);
	Item.col = nColIndex++;
	Item.szText = _T("Stop Bit");
	SetItem(&Item);

	return nColIndex;
}


long CGridDeviceComCfg::InitCmmCfgColIndex()
{
	//CPpProjectConfig *pPrjCfg = (CPpProjectConfig*)m_pDatas;
	CPpCfgDevices *pCfgDevices = (CPpCfgDevices*)m_pDatas;
	CExBaseList *pList = &pCfgDevices->m_listCmmCfgChannel;

	POS pos  = pList->GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;
	BOOL bTcpServerCol = FALSE;
	BOOL bTcpClientCol = FALSE;
	BOOL bUdpServerCol = FALSE;
	BOOL bUdpClientCol = FALSE;
	BOOL bSerialCol = FALSE;
	long nColIndex = 1;

	 while (pos != NULL)
	 {
		p = (CExBaseObject *)pList->GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == DMCLASSID_CMM_UDP_SERVER_CONFIG)
		{
			bTcpServerCol = TRUE;
		}
		else if( nClassID == DMCLASSID_CMM_UDP_CLIENT_CONFIG)
		{
			bTcpServerCol = TRUE;
		}
		else if( nClassID == DMCLASSID_CMM_TCP_CLIENT_CONFIG)
		{
			bTcpServerCol = TRUE;
		}
		else if(nClassID == DMCLASSID_CMM_TCP_SERVER_CONFIG)
		{
			bTcpServerCol = TRUE;
		}
		else if(nClassID == DMCLASSID_CMM_SERIAL_CONFIG)
		{
			bSerialCol = TRUE;
		}
	 }

	 GV_ITEM Item;
	 Item.mask = GVIF_FORMAT|GVIF_TEXT|GVIF_PARAM;
	 Item.row = 0;
	 Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;

	 if (bTcpServerCol)
	 {
		 InitCmmCfgColIndex_TcpServer(nColIndex, Item);
	 }

	if (bTcpClientCol)
	{
		InitCmmCfgColIndex_TcpClient(nColIndex, Item);
	}

	if (bUdpServerCol)
	{
		InitCmmCfgColIndex_UdpServer(nColIndex, Item);
	}

	if (bUdpClientCol)
	{
		InitCmmCfgColIndex_UdpServer(nColIndex, Item);
	}

	if (bSerialCol)
	{
		InitCmmCfgColIndex_Serial(nColIndex, Item);
	}

	Merge(0,0,1,0);

	 return nColIndex;
}

void CGridDeviceComCfg::InitGridTitle()
{

}

void CGridDeviceComCfg::InitGrid()
{
	long nRows = m_pDatas->GetCount() + 2;

	SetListMode(FALSE);
	SetRowCount(nRows);
	SetColumnCount(1);
	long nCols = InitCmmCfgColIndex();

	SetColumnCount(nCols);
	
	SetFixedRowCount(2);
	SetFixedColumnCount(1);
}

void CGridDeviceComCfg::ShowDatas(CExBaseList *pDatas, BOOL bResetScrollBars)
{
	m_pDatas = pDatas;
	InitGrid();

	CExBaseObject *pObj = NULL;	
	POS pos = pDatas->GetHeadPosition();
	int nRowIndex = 2;

	while (pos != NULL)
	{
		pObj = pDatas->GetNext(pos);
		ShowData(pObj, nRowIndex, FALSE);
	}

	SetRowCount(nRowIndex, bResetScrollBars);

	for (nRowIndex=0; nRowIndex<m_nRows; nRowIndex++)
	{
		SetRowHeight(nRowIndex, EXBASEGRID_ROWHEIGHT);
	}

	AdjustAllCols(bResetScrollBars);

	if (bResetScrollBars)
	{
		ResetScrollBars();
	}

	Invalidate(FALSE);
}

//index, name,item-index,datatype,unit,min,max,value//,format
void CGridDeviceComCfg::ShowData(CExBaseObject *pObj, int &nRow, BOOL bInsertRow)
{
	CPpCfgDevice *pCfgDevice = (CPpCfgDevice *)pObj;
	POS pos = pCfgDevice->m_listCmmCfg.GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;
	CString strIndex;

	strIndex.Format(_T("%d"), nRow-1);
	Show_StaticString(p, nRow, 0, strIndex);

	while (pos != NULL)
	{
		p = (CExBaseObject *)pCfgDevice->m_listCmmCfg.GetNext(pos);
		nClassID = p->GetClassID();


		if (nClassID == DMCLASSID_CMM_UDP_SERVER_CONFIG)
		{
			ShowData_UdpServer((CCmmUdpServerConfig*)p, nRow);
		}
		else if( nClassID == DMCLASSID_CMM_UDP_CLIENT_CONFIG)
		{
			ShowData_UdpClient((CCmmUdpClientConfig*)p, nRow);
		}
		else if( nClassID == DMCLASSID_CMM_TCP_CLIENT_CONFIG)
		{
			ShowData_TcpClient((CCmmTcpClientConfig*)p, nRow);
		}
		else if(nClassID == DMCLASSID_CMM_TCP_SERVER_CONFIG)
		{
			ShowData_TcpServer((CCmmTcpServerConfig*)p, nRow);
		}
		else if(nClassID == DMCLASSID_CMM_SERIAL_CONFIG)
		{
			ShowData_Serial((CCmmSerialConfig*)p, nRow);
		}
	}

	nRow++;
}


void CGridDeviceComCfg::ShowData_TcpServer(CCmmTcpServerConfig *pCmmConfig, long nRow)
{
	//使用m_dwItemData记录当前的数据列编号
	pCmmConfig->m_dwItemData = m_nTcpServerCol;
	Show_String(pCmmConfig, nRow, m_nTcpServerCol, &pCmmConfig->m_strLocalIP);
	Show_Long(pCmmConfig, nRow, m_nTcpServerCol+1, &pCmmConfig->m_nLocalPort);
}

void CGridDeviceComCfg::ShowData_TcpClient(CCmmTcpClientConfig *pCmmConfig, long nRow)
{

}

void CGridDeviceComCfg::ShowData_UdpServer(CCmmUdpServerConfig *pCmmConfig, long nRow)
{

}

void CGridDeviceComCfg::ShowData_UdpClient(CCmmUdpClientConfig *pCmmConfig, long nRow)
{
	//CDvmData *pData = (CDvmData *)pObj;
// 	CDeviceCmmConfig *pData = (CDeviceCmmConfig *)pObj;
// 	long nColIndex = 0;
// 	Show_Index(pData, nRow, nColIndex++);
// 	Show_String(pData, nRow, nColIndex++, &pData->m_strName);
// 	Show_String(pData, nRow, nColIndex++, &pData->m_net->m_tcpserver->m_localIP);
// 	Show_Long(pData, nRow, nColIndex++, &pData->m_net->m_tcpserver->m_localPORT);
// 	Show_String(pData, nRow, nColIndex++, &pData->m_net->m_tcpclient->m_localIP);
// 	Show_Long(pData, nRow, nColIndex++, &pData->m_net->m_tcpclient->m_localPORT);
// 	Show_String(pData, nRow, nColIndex++, &pData->m_net->m_tcpclient->m_remoteIP);
// 	Show_Long(pData, nRow, nColIndex++, &pData->m_net->m_tcpclient->m_remotePORT);
// 
// 	Show_String(pData, nRow, nColIndex++, &pData->m_net->m_udpserver->m_localIP);
// 	Show_Long(pData, nRow, nColIndex++, &pData->m_net->m_udpserver->m_localPORT);
// 	Show_String(pData, nRow, nColIndex++, &pData->m_net->m_udpclient->m_localIP);
// 	Show_Long(pData, nRow, nColIndex++, &pData->m_net->m_udpclient->m_localPORT);
// 	Show_String(pData, nRow, nColIndex++, &pData->m_net->m_udpclient->m_remoteIP);
// 	Show_Long(pData, nRow, nColIndex++, &pData->m_net->m_udpclient->m_remotePORT);
	

	/*
	GV_ITEM Item;
	Item.mask=GVIF_FORMAT|GVIF_PARAM|GVIF_TEXT | GVIF_FGCLR|GVIF_BKCLR | GVIF_DATATYPE | GVIF_PARAM | GVIF_VALUE;	
	Item.nFormat = DT_LEFT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
	Item.lParam = (LPARAM)pData;
	Item.row = nRow;	
	Item.dwValue = 0;
	Item.crFgClr = RGB(0, 0, 0);
	Item.crBkClr = RGB(255, 255, 255);

	////"编号"
	Item.col = 0;
	Item.szText.Format(_T("%d"), nRow);
	Item.nDataType = GVET_NOEDIT;
	SetItemText(nRow, 0, Item.szText);	

	//"名称", 
	Item.col++;
	Item.nDataType = GVET_EDITBOX;
	Item.szText =pData->m_strName;
	SetItem(&Item);	

	//"ID", 
	Item.col++;
	Item.nDataType = GVET_EDITBOX;
	Item.szText =pData->m_strID;
	SetItem(&Item);	

	//"index", 
	Item.col++;
	Item.nDataType = GVET_EDITBOX;
	Item.szText.Format(_T("%d"), pData->m_nIndex);
	SetItem(&Item);	

	//"datatype", 
	Item.col++;
	Item.nDataType = GVET_EDITBOX;
	Item.szText.Format(_T("%d"), pData->m_nDataTypeID);
	SetItem(&Item);	

	//"value", 
	Item.col++;
	Item.nDataType = GVET_EDITBOX;
	Item.szText =pData->m_strValue;
	SetItem(&Item);	

	//"unit", 
	Item.col++;
	Item.nDataType = GVET_EDITBOX;
	Item.szText =pData->m_strUnit;
	SetItem(&Item);	

	//"min", 
	Item.col++;
	Item.nDataType = GVET_EDITBOX;
	Item.szText =pData->m_strMin;
	SetItem(&Item);	

	//"min", 
	Item.col++;
	Item.nDataType = GVET_EDITBOX;
	Item.szText =pData->m_strMax;
	SetItem(&Item);	

	//"change", 
	Item.col++;
	Item.nDataType = GVET_CHECKBOX;
	Item.szText.Format(_T("%d"), pData->m_nChange);
	Item.dwValue = pData->m_nChange;
	SetItem(&Item);	

	//"change", 
	Item.col++;
	Item.nDataType = GVET_EDITBOX;
	Item.szText = pData->m_strFormat;
	Item.dwValue = 0;
	SetItem(&Item);	
	*/
	SetRowHeight(nRow, 20);

	nRow++;

}

void CGridDeviceComCfg::ShowData_Serial(CCmmSerialConfig *pCmmConfig, long nRow)
{
	pCmmConfig->m_dwItemData = m_nSerialCol;
	Show_Long(pCmmConfig, nRow, m_nSerialCol,     &pCmmConfig->m_nPortNum);
	Show_Long(pCmmConfig, nRow, m_nSerialCol+1, &pCmmConfig->m_nBaudRate);
	Show_Long(pCmmConfig, nRow, m_nSerialCol+2, &pCmmConfig->m_nDataBit);
	Show_Long(pCmmConfig, nRow, m_nSerialCol+3, &pCmmConfig->m_nParity);
	Show_Float(pCmmConfig, nRow, m_nSerialCol+4, &pCmmConfig->m_fStopBit);
}

