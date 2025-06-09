#include "SttCommCfgDeviceAttrsGrid.h"
#include "../../../../../../Module/DataMngr/DvmData.h"
#include "../../../../XLangResource_Native.h"
#include "../../../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../ScrollCtrl/ScrollComboBox.h"
#include <QApplication>

extern CFont *g_pSttGlobalFont;

SttCCommCfgDeviceAttrsGrid::SttCCommCfgDeviceAttrsGrid(QWidget* pparent):QExBaseListGridBase(pparent)
{
	m_bRunning = FALSE;

	//horizontalHeader()->setFont(/*oFont*/*g_pSttGlobalFont);
	setFont(*g_pSttGlobalFont);
}

SttCCommCfgDeviceAttrsGrid::~SttCCommCfgDeviceAttrsGrid()
{

}

void SttCCommCfgDeviceAttrsGrid::InitGrid()
{
 	InitGridTitle();
	//SetEditable(FALSE);

	//this->columnCount();
	for (int i=0; i<columnCount(); i++)
	{
		horizontalHeaderItem(i)->setFont(*g_pSttGlobalFont);
	}
	
}

void SttCCommCfgDeviceAttrsGrid::InitGridTitle()
{
	CString astrGridTitle[STTCCOMMCFGDEVICEATTR_COLS] = { g_sLangTxt_Name, g_sLangTxt_State_Datavalue};
	int  iColType[STTCCOMMCFGDEVICEATTR_COLS] = {QT_GVET_NOEDIT, QT_GVET_NOEDIT};
	int iGridWidth[STTCCOMMCFGDEVICEATTR_COLS] = {200, 100};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, STTCCOMMCFGDEVICEATTR_COLS);
}

void Global_SetComCfgTableHeight(QTableWidget *pGrid)
{
	int nRowHeight = 40;
	for (int row=0; row<pGrid->rowCount(); row++)
	{
		pGrid->setRowHeight(row,nRowHeight);
	}
}

void SttCCommCfgDeviceAttrsGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	ASSERT(pData);
	CDvmValue *pDvmValue = (CDvmValue *)pData;
	CDvmData *pParentData = (CDvmData*)pData->GetParent();
	BOOL bIsSerial = FALSE;
	if (pParentData != NULL)
	{
		int nPos = pParentData->m_strID.Find(CString("serials"));
		if (nPos >= 0)
		{
			bIsSerial = TRUE;
		}
	}
	CString strVlueID = TranslateID(pDvmValue->m_strID);
	Show_StaticString(pData,nRow,0,&strVlueID); 
	//Show_StaticString(pData,nRow,1,&pDvmValue->m_strValue); 
	//Show_String(pData,nRow,1,&pDvmValue->m_strValue);
	if (nRow == 0)
	{
		int nDevAdr = (int)(pDvmValue->m_strValue.toInt());
		CString strDevAddr;
		//int test=CString_To_long(appidStr);
		strDevAddr.Format(_T("0X%04X"), nDevAdr);

		//Show_StaticString(pData, nRow, 1, &strDevAddr);
		//Show_Hex(pData,nRow,1,(DWORD*)(&nDevAdr),2,TRUE,TRUE,EndEditCell_Long);
		Show_String(pData, nRow, 1, &strDevAddr, EndEditCellDevAddr_String);
	}else{
		Show_String(pData, nRow, 1, &pDvmValue->m_strValue, EndEditCell_String);
		//Show_StaticString(pData, nRow, 1, &pDvmValue->m_strValue);
	}

	nRow++;

	Global_SetComCfgTableHeight(this);
}

void SttCCommCfgDeviceAttrsGrid::EndEditCellDevAddr_String(int nRow, int nCol, QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL);
	ASSERT(pVCellData->pObj != NULL);
	//if(*(pVCellData->pnValue) != CString_To_long(pCell->text()))
	//{
	//	*(pVCellData->pnValue) = CString_To_long(pCell->text());
	//	//((QCharEditGridBase*)pGrid)->EmitCharChanged();

	//	CDvmValue *pDvmValue = (CDvmValue *)pVCellData->pObj;
	//	pDvmValue->m_strValue = pCell->text();
	//}

	CDvmValue *pDvmValue = (CDvmValue *)pVCellData->pObj;

	//if(*(pVCellData->pString) != pCell->text())
	{
		CString strCellText=pCell->text();
		strCellText.MakeUpper();
		int nPos = strCellText.Find(CString("0X"));
		CString strTableAddr;
		long lLastRes = 0;
		if (nPos < 0) //非十六进制
		{	
			long lValue = CString_To_long(pCell->text());
			strTableAddr.Format(_T("0X%04X"),lValue);
			lLastRes = lValue;
			pDvmValue->m_strValue = pCell->text();

		}else{ //十六进制
			strTableAddr=pCell->text();

			CString strTmp=pCell->text();
			long nValue=0;
			char *pzfTmp = NULL;
			CString_to_char(strTmp,&pzfTmp);
			HexToLong(pzfTmp,nValue);
			delete pzfTmp;
			lLastRes = nValue;

			//===========
			CString strValueMdy;
			strValueMdy.Format("%ld",nValue);
			pDvmValue->m_strValue = strValueMdy;
		}

		pCell->setText(strTableAddr);
		//if (lLastRes > 0)
		{
			((SttCCommCfgDeviceAttrsGrid*)pGrid)->EmitDevAddrChange(lLastRes);
		}
		
		//*(pVCellData->pString) = strTableAddr;

		//((SttCCommCfgDeviceAttrsGrid*)pGrid)->EmitCharChanged();
	}
}

void SttCCommCfgDeviceAttrsGrid::EmitDevAddrChange(long res)
{
	emit sig_ChangedDevAddr(res);
}

void SttCCommCfgDeviceAttrsGrid::EmitNetTableChange()
{
	emit sig_ChangedNetTable();
}

BOOL SttCCommCfgDeviceAttrsGrid::CheckIPValid(CString strIp)
{
	char chFindDot = '.';
	QStringList ipsList = strIp.split(".");
	if (ipsList.size() < 4)
	{
		return FALSE;
	}

	for (int i=0; i<ipsList.size(); i++)
	{
		CString strCrtIp = ipsList.at(i);
		bool isDigital = strCrtIp.contains(QRegExp("^\\d+$"));
		if (!isDigital)
		{
			return FALSE;
		}
		long nipVal = CString_To_long(strCrtIp);
		if ((0 > nipVal) || (nipVal>255))
		{
			return FALSE;
		}
	}

	return TRUE;
}

void SttCCommCfgDeviceAttrsGrid::EndEditCell_String(int nRow, int nCol, QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL);
	ASSERT(pVCellData->pObj != NULL);
	SttCCommCfgDeviceAttrsGrid *pGridCrt = ((SttCCommCfgDeviceAttrsGrid*)pGrid);
	CDvmValue *pValue = (CDvmValue*)(pVCellData->pObj);
	if (pValue == NULL)
	{
		return;
	}
	CString strID = pValue->m_strID;
	if ((strID == CString("local-ip")) || (strID == CString("remote-ip")) || (strID == "SubnetMask"))
	{
		BOOL isValidIp = pGridCrt->CheckIPValid(pCell->text());
		if (!isValidIp)
		{
			pCell->setText(*pVCellData->pString);
			return;
		}
	}
	else if ((strID == CString("local-port")) || (strID == CString("remote-port")))
	{
		CString strPortVl = pCell->text();
		long lProtVl = CString_To_long(strPortVl);
		if ((lProtVl<0) || (lProtVl>65535))
		{
			pCell->setText(*pVCellData->pString);
			return;
		}
	}

	if(*(pVCellData->pString) != pCell->text())
	{
		*(pVCellData->pString) = pCell->text();
		//((QCharEditGridBase*)pGrid)->EmitCharChanged();
		((SttCCommCfgDeviceAttrsGrid*)pGrid)->EmitNetTableChange();
	}

	if (strID == CString("local-ip")) 
	{
		CDvmData *pParentData = (CDvmData*)pValue->GetParent();
		if (pParentData != NULL)
		{
			CDvmValue *pVlSubnet = (CDvmValue*)pParentData->FindByID("SubnetMask");
			CString strSubnet = pVlSubnet->m_strValue;
			//pGridCrt->ModifyTestDeviceIP(pCell->text(), strSubnet);
		}
	}
	else if (strID == CString("SubnetMask"))
	{
		CDvmData *pParentData = (CDvmData*)pValue->GetParent();
		if (pParentData != NULL)
		{
			CDvmValue *pVlLocIp = (CDvmValue*)pParentData->FindByID("local-ip");
			if (pVlLocIp != NULL)
			{
				CString strIp = pVlLocIp->m_strValue;
				//pGridCrt->ModifyTestDeviceIP(strIp,pCell->text());
			}
		}
	}
	
}
 
void SttCCommCfgDeviceAttrsGrid::SelectRow(int nRow)
{

}

CString SttCCommCfgDeviceAttrsGrid::TranslateID(CString strID)
{
	if (strID == CString("DeviceAddr"))
	{
		return CString("装置地址");
	}
	else if (strID == CString("port_number"))
	{
		return CString("串口号");
	}
	else if (strID == CString("baud-rate"))
	{
		return CString("波特率");
	}
	else if (strID == CString("byte-size"))
	{
		return CString("数据位");
	} 
	else if (strID == CString("stop-bit"))
	{
		return CString("停止位");
	}
	else if (strID == CString("parity"))
	{
		return CString("校验位");
	}
	else if (strID == CString("local-ip"))
	{
		return CString("测试仪IP地址");
	}
	else if (strID == CString("local-port"))
	{
		return CString("测试仪端口号");
	}
	else if (strID == CString("remote-ip"))
	{
		return CString("终端IP地址");
	}
	else if (strID == CString("remote-port"))
	{
		return CString("终端端口号");
	}
	else if (strID == CString("SubnetMask"))
	{
		return CString("子网掩码");
	}
	return strID;
}

void SttCCommCfgDeviceAttrsGrid::RemoveAllRowCellWgtInSerial()
{
	removeCellWidget(1, 1);
	removeCellWidget(2, 1);
	removeCellWidget(3, 1);
	removeCellWidget(4, 1);
	removeCellWidget(5, 1);

}

void SttCCommCfgDeviceAttrsGrid::setComboSelIndex(QComboBox* pCombo, CString strNameFind)
{
	for (int i=0; i<pCombo->count(); i++)
	{
		if (pCombo->itemText(i) == strNameFind)
		{
			pCombo->setCurrentIndex(i);
			break;
		}
	}

}

void SttCCommCfgDeviceAttrsGrid::InitData(CDvmData* pDataTable)
{
	//m_pParas=pParas;
	CString oBoudRateVl[9] = {CString("1200"),CString("2400"),CString("4800"),CString("9600"),CString("19200"),CString("38400"),CString("43000"),CString("57600"),CString("115200")};
	QStringList oBoudRateList;
	int nArrSize = sizeof(oBoudRateVl) / sizeof(oBoudRateVl[0]);
	for (int i=0; i<nArrSize; i++)
	{
		oBoudRateList << oBoudRateVl[i];
	}
	QStringList oPortNumsList;
	for (int i=0; i<6; i++)
	{
		CString strPort;
		strPort.Format("COM%d", i);
		oPortNumsList << strPort;
	}
	QStringList oByteSizeList;
	for (int i=4; i<=8; i++)
	{
		CString strByteSize;
		strByteSize.Format("%d", i);
		oByteSizeList << strByteSize;
	}
	QScrollComboBox *pCbPortNum = new QScrollComboBox(this);
	pCbPortNum->addItems(oPortNumsList);
	CDvmValue *pPtNmDvmValue = (CDvmValue*)pDataTable->FindByID(CString("port_number"));
	CString strPortNum = CString("COM") + pPtNmDvmValue->m_strValue;
	setComboSelIndex(pCbPortNum, strPortNum);
	pCbPortNum->setFixedWidth_All(510, 510);
	//pCbbError1->setCurrentIndex(pParas->m_nTimeValue_ErrorLogic);
	QScrollComboBox *pCbBoudRate =  new QScrollComboBox(this);
	pCbBoudRate->addItems(oBoudRateList);
	CDvmValue *pBdRtDvmValue = (CDvmValue*)pDataTable->FindByID(CString("baud-rate"));
	setComboSelIndex(pCbBoudRate, pBdRtDvmValue->m_strValue);
	pCbBoudRate->setFixedWidth_All(510, 510);
	//pCbbError2->setCurrentIndex(pParas->m_nUActVal_ErrorLogic);
	QScrollComboBox *pCbByteSize =  new QScrollComboBox(this);
	//pCbByteSize->addItem(CString("8"));
	pCbByteSize->addItems(oByteSizeList);
	CDvmValue *pBtSzDvmValue = (CDvmValue*)pDataTable->FindByID(CString("byte-size"));
	setComboSelIndex(pCbByteSize, pBtSzDvmValue->m_strValue);
	pCbByteSize->setFixedWidth_All(510, 510);
	//pCbbError3->setCurrentIndex(pParas->m_nIActVal_ErrorLogic);

	QScrollComboBox *pCbStopBit =  new QScrollComboBox(this);
	pCbStopBit->addItem(CString("1"));
	pCbStopBit->addItem(CString("2"));
	CDvmValue *pStpBtDvmValue = (CDvmValue*)pDataTable->FindByID(CString("stop-bit"));
	setComboSelIndex(pCbStopBit, pStpBtDvmValue->m_strValue);
	pCbStopBit->setFixedWidth_All(510, 510);
	//pCbbError4->setCurrentIndex(pParas->m_nHzActVal_ErrorLogic);
	QScrollComboBox *pCbParity = new QScrollComboBox(this);
	pCbParity->addItem(CString("None"));
	pCbParity->addItem(CString("Even"));
	pCbParity->addItem(CString("Odd"));
	pCbParity->setFixedWidth_All(510, 510);
	CDvmValue *pParityDvmValue = (CDvmValue*)pDataTable->FindByID(CString("parity"));
	//setComboSelIndex(pCbStopBit,pStpBtDvmValue->m_strValue);
	pCbParity->setCurrentIndex(pParityDvmValue->m_strValue.toInt());

	setCellWidget(1, 1, pCbPortNum);
	setCellWidget(2, 1, pCbBoudRate);
	setCellWidget(3, 1, pCbByteSize);
	setCellWidget(4, 1, pCbStopBit);
	setCellWidget(5, 1, pCbParity);

	connect(pCbPortNum, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(slot_CbPortNumChanged(const QString &)));
	connect(pCbBoudRate, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(slot_CbBoudRateChanged(const QString &)));
	connect(pCbByteSize, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(slot_CbByteSizeChanged(const QString &)));
	connect(pCbStopBit, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(slot_CbStopBitChanged(const QString &)));
	connect(pCbParity, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_CbParityChanged(int)));

	
}

void SttCCommCfgDeviceAttrsGrid::slot_CbPortNumChanged(const QString& strText)
{
	//CExBaseObject *pItem = GetCurrSelData();
	CDvmData *pData = (CDvmData*)GetDatas();
	CDvmValue *pValue = (CDvmValue*)pData->FindByID("port_number");
	CString strResult = strText;
	int nPos = strResult.Find("M");
	if (nPos >= 0)
	{
		strResult = strResult.right(nPos-1);
	}
	pValue->m_strValue = strResult;
	//EmitNetTableChange();
	emit sig_ChangedSerialTable();
}

void SttCCommCfgDeviceAttrsGrid::slot_CbBoudRateChanged(const QString& strText)
{
	//CExBaseObject *pItem = GetCurrSelData();
	CDvmData *pData = (CDvmData*)GetDatas();
	CDvmValue *pValue = (CDvmValue*)pData->FindByID("baud-rate");
	pValue->m_strValue = strText;
	//EmitNetTableChange();
	emit sig_ChangedSerialTable();
}

void SttCCommCfgDeviceAttrsGrid::slot_CbByteSizeChanged(const QString& strText)
{
	//CExBaseObject *pItem = GetCurrSelData();
	CDvmData *pData = (CDvmData*)GetDatas();
	CDvmValue *pValue = (CDvmValue*)pData->FindByID("byte-size");
	pValue->m_strValue = strText;
	//EmitNetTableChange();
	emit sig_ChangedSerialTable();
}

void SttCCommCfgDeviceAttrsGrid::slot_CbStopBitChanged(const QString& strText)
{
	//CExBaseObject *pItem = GetCurrSelData();
	CDvmData *pData = (CDvmData*)GetDatas();
	CDvmValue *pValue = (CDvmValue*)pData->FindByID("stop-bit");
	pValue->m_strValue = strText;
	//EmitNetTableChange();
	emit sig_ChangedSerialTable();
}

void SttCCommCfgDeviceAttrsGrid::slot_CbParityChanged(int index)
{
	//CExBaseObject *pItem = GetCurrSelData();
	CDvmData *pData = (CDvmData*)GetDatas();
	CDvmValue *pValue = (CDvmValue*)pData->FindByID("parity");
	CString resValue;
	resValue.Format("%d",index);
	pValue->m_strValue = resValue;
	//EmitNetTableChange();
	emit sig_ChangedSerialTable();
}

bool SttCCommCfgDeviceAttrsGrid::eventFilter(QObject *obj, QEvent *event)
{
	if (event->type() == QEvent::MouseButtonDblClick)
	{
		QMouseEvent *pMouseEvent = (QMouseEvent *)event;
		m_bRunning = TRUE;
		mouseDoubleClickEvent((QMouseEvent *)pMouseEvent);
		m_bRunning = FALSE;
		return  true;
	}
#ifdef _PSX_QT_LINUX_
	return QScrollTableWidget::eventFilter(obj,event);
#else
	return QTableWidget::eventFilter(obj,event);
#endif
	return  true;

}

void SttCCommCfgDeviceAttrsGrid::mousePressEvent(QMouseEvent * event)
{

	if (m_bRunning)
	{
#ifdef _PSX_QT_LINUX_
		QScrollTableWidget::mousePressEvent(event);
#else
		QTableWidget::mousePressEvent(event);
#endif
		return;
	}

	QMouseEvent *pEvent = new QMouseEvent(QEvent::MouseButtonDblClick,event->pos(),Qt::LeftButton,Qt::LeftButton,Qt::NoModifier);
	QApplication::postEvent(this,pEvent);

#ifdef _PSX_QT_LINUX_
	QScrollTableWidget::mousePressEvent(event);
#else
	QTableWidget::mousePressEvent(event);
#endif

}
