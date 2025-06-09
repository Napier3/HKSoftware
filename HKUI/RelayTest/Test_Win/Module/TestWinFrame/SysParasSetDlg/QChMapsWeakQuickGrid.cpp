#include "QChMapsWeakQuickGrid.h"
#include "../../../../Module/SttTestResourceMngr/SttTestResourceMngr.h"

#include <QHeaderView>
#include <QLineEdit>

CChMapsWeakQuickGrid::CChMapsWeakQuickGrid(QWidget *parent)
: QTableWidget(parent)
{
	m_pSttChMaps = new CSttChMaps;
}

CChMapsWeakQuickGrid::~CChMapsWeakQuickGrid()
{

}

void CChMapsWeakQuickGrid::InitGrid(CSttChMaps *pChMaps)
{
	int WeakMoudleCount, nUGroupCount, nIGroupCount;//分别标识硬件模块个数，软件资源电压电流组数
	QStringList HStrList, VStrList;//每一列表头
	QString strText;
	int nUChCount = g_oSttTestResourceMngr.m_pTestResouce->m_oVolChRsListRef.GetCount();
	int nIChCount = g_oSttTestResourceMngr.m_pTestResouce->m_oCurChRsListRef.GetCount();
	WeakMoudleCount = g_oSttTestResourceMngr.m_oWeak_Tags.GetCount();//弱信号硬件资源

	int nRowCount = 0;
	for (int nIndex = 0; nIndex < WeakMoudleCount; nIndex++)
	{
		int nChUGroupCount = g_oSttTestResourceMngr.m_oWeak_Tags[nIndex]->m_nChCountU_Week / 3;
		int nChIGroupCount = g_oSttTestResourceMngr.m_oWeak_Tags[nIndex]->m_nChCountI_Week / 3;
		int nTotalChGroupCount = nChIGroupCount + nChUGroupCount;

		nRowCount += nChUGroupCount;
		nRowCount += nChIGroupCount;
		for (int nGroupIndex = 0; nGroupIndex < nTotalChGroupCount; nGroupIndex++)
		{
			strText = QString("弱信号模块%1-第%2组").arg(nIndex + 1).arg(nGroupIndex + 1);
			VStrList << strText;
			ModuleGroupInfo info;
			info.moduleNumber = nIndex + 1;
			info.groupNumber = nGroupIndex + 1;
			m_nModuleGroupInfo.append(info);
		}
	}
	setRowCount(nRowCount);

	nUGroupCount = nUChCount / 3;//6U6I 分两组， 4U3I按3个电压/电流一组(第四路电压不设置快捷映射)
	nIGroupCount = nIChCount / 3;
	setColumnCount(nUGroupCount + nIGroupCount + 1);
	HStrList.push_back(QString(tr("模块名称")));

	if (g_oSttTestResourceMngr.m_pTestResouce->GetTestRsType() == STT_TEST_RESOURCE_TYPE_4U3I)
	{
		HStrList.push_back(QString(tr("Ua1、Ub1、Uc1")));
		HStrList.push_back(QString(tr("Ia1、Ib1、Ic1")));
	}
	else if (g_oSttTestResourceMngr.m_pTestResouce->GetTestRsType() == STT_TEST_RESOURCE_TYPE_6U6I)
	{
		HStrList.push_back(QString(tr("Ua1、Ub1、Uc1")));
		HStrList.push_back(QString(tr("Ua2、Ub2、Uc2")));
		HStrList.push_back(QString(tr("Ia1、Ib1、Ic1")));
		HStrList.push_back(QString(tr("Ia2、Ib2、Ic2")));
	}

	setHorizontalHeaderLabels(HStrList);

	for (int nIndex = 0; nIndex < this->columnCount(); nIndex++)
	{
		if (nIndex == 0)
		{
			setColumnWidth(nIndex, 150);
		}
		else
		{
		setColumnWidth(nIndex, 130);
	}
	}
	this->horizontalHeader()->setStretchLastSection(true); //设置充满表宽度
	this->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}");
	this->setStyleSheet("selection-background-color: grey;selection-color: black");
	InsertItem(VStrList);
	InitChMapsState(pChMaps);
}

void CChMapsWeakQuickGrid::InsertItem(QStringList strList)
{
	for (int i = 0; i < this->rowCount(); i++)
	{
		setItem(i, 0, new QTableWidgetItem(strList.at(i)));
		for (int j = 1; j < this->columnCount(); j++)
		{
			QCenterComboBox *pCbbError = NewErrorType();
			ComboxModelStyle(pCbbError);
			setCellWidget(i, j, pCbbError);
			connect(pCbbError, SIGNAL(currentIndexChanged(QString)), this, SLOT(slot_comboxIndexChanged(QString)));
		}
	}
}

void CChMapsWeakQuickGrid::InitChMapsState(CSttChMaps *pChMaps)
{
	m_pSttChMaps = pChMaps;
	CSttModuleTag *pSttModuleTag = NULL;
	CSttChMap *pSttChMap = NULL;
	CString strSoftRsID;
	long nWeakModuleIndex = 1;//弱信号的模块号
	
	m_nVolChIsMap.clear();
	m_nVolChIsMap.resize(this->rowCount());
	m_nVolChIsMap2.clear();
	m_nVolChIsMap2.resize(this->rowCount());
	m_nCurChIsMap.clear();
	m_nCurChIsMap.resize(this->rowCount());
	m_nCurChIsMap2.clear();
	m_nCurChIsMap2.resize(this->rowCount());
	m_nVolChIsNullNum.clear();
	m_nVolChIsNullNum2.clear();
	m_nCurChIsNullNum.clear();
	m_nCurChIsNullNum2.clear();

	POS pos = g_oSttTestResourceMngr.m_oWeak_Tags.GetHeadPosition();
	while (pos)
	{
		pSttModuleTag = (CSttModuleTag *)g_oSttTestResourceMngr.m_oWeak_Tags.GetNext(pos);
		if (pSttModuleTag == NULL)
		{
			break;
		}

		for (int nIndex = 0; nIndex < g_oSttTestResourceMngr.m_pTestResouce->m_oVolChRsListRef.GetCount(); nIndex++)
		{
			strSoftRsID.Format(_T("U%ld"),nIndex + 1);
			pSttChMap = m_pSttChMaps->GetChMap(strSoftRsID);
			if (pSttChMap != NULL)
			{
				CSttHdChs *pSttHdChs = (CSttHdChs *)pSttChMap->FindByID(STT_MODULETYPE_ID_WEEK);
				if (pSttHdChs == NULL)
				{
					if (nIndex + 1 <= 3)
					{
						m_nVolChIsNullNum.push_back(1);
					}
					else
					{
						m_nVolChIsNullNum2.push_back(1);
					}
				}
				else
				{
					POS pos1 = pSttHdChs->GetHeadPosition();
					CSttHdCh *pObj = NULL;
					int nNum = pSttHdChs->GetCount();
					if (nNum == 0)
					{
						if (nIndex + 1 <= 3)
						{
							m_nVolChIsNullNum.push_back(1);
						}
						else
						{
							m_nVolChIsNullNum2.push_back(1);
						}
					}
					while (pos1)
					{
						pObj = (CSttHdCh *)pSttHdChs->GetNext(pos1);
						if (pObj != NULL)
						{
							CString strText;
							int nGroupIndex;
							int nChCount = pSttModuleTag->m_nChCountU_Week / 3 + pSttModuleTag->m_nChCountI_Week / 3;
							for (int nChGroupIndex = 0; nChGroupIndex < nChCount; nChGroupIndex++)
							{
								//U1 区分对应Uw1_1 Uw1_4 Uw1_7 Uw1_10
								strText.Format(_T("Uw%d_%d"), nWeakModuleIndex, nChGroupIndex * 3 + nIndex + 1 - 3*(nIndex/3));
								int nChGroupIndexTmt = nChGroupIndex * 3 + nIndex + 1 - 3*(nIndex/3);
								nGroupIndex = (nChGroupIndexTmt - 1) / 3 + (nWeakModuleIndex - 1) * 3;
								if (pObj->m_strName == strText)
								{
									if (nIndex + 1 <= 3)
									{
										m_nVolChIsMap[nGroupIndex].push_back(1);//记录U1 U2 U3是否都对应上
									}
									else
									{
										m_nVolChIsMap2[nGroupIndex].push_back(1);
									}
								}
								else
								{
									//当前组不映射，通过通道找到对应映射通道
									CString str = pObj->m_strName;
									int underPos = str.Find(_T("_")); // 找到下划线的位置
									if (underPos != -1) {
										CString nChModuleIndexTmt = str.Mid(2, underPos - 2);
										CString nChGroupIndexTmt = str.Mid(underPos + 1);
										int nGroupIndexTmt = (nChGroupIndexTmt.toInt() - 1) / 3 + (nChModuleIndexTmt.toInt() - 1) * 3;
										if (nGroupIndexTmt < this->rowCount())
										{
											if (nIndex + 1 <= 3)
											{
												m_nVolChIsMap[nGroupIndexTmt].push_back(0);//记录U1 U2 U3是否都对应上
											}
											else
											{
												m_nVolChIsMap2[nGroupIndexTmt].push_back(0);
											}
										}
									}
								}
							}
						}
						else
						{
							if (nIndex + 1 <= 3)
							{
								m_nVolChIsNullNum.push_back(1);
							}
							else
							{
								m_nVolChIsNullNum2.push_back(1);
							}
						}
					}
				}

			}
		}

		for (int nIndex = 0; nIndex < g_oSttTestResourceMngr.m_pTestResouce->m_oCurChRsListRef.GetCount(); nIndex++)
		{
			strSoftRsID.Format(_T("I%ld"),nIndex + 1);
			pSttChMap = m_pSttChMaps->GetChMap(strSoftRsID);
			if (pSttChMap != NULL)
			{
				CSttHdChs *pSttHdChs = (CSttHdChs *)pSttChMap->FindByID(STT_MODULETYPE_ID_WEEK);
				if (pSttHdChs == NULL)
				{
					if (nIndex + 1 <= 3)
					{
						m_nCurChIsNullNum.push_back(1);
					}
					else
					{
						m_nCurChIsNullNum2.push_back(1);
					}
				}
				else
				{
					POS pos1 = pSttHdChs->GetHeadPosition();
					CSttHdCh *pObj = NULL;
					int nNum = pSttHdChs->GetCount();
					if (nNum == 0)
					{
						if (nIndex + 1 <= 3)
						{
							m_nCurChIsNullNum.push_back(1);
						}
						else
						{
							m_nCurChIsNullNum2.push_back(1);
						}
					}
					while (pos1)
					{
						pObj = (CSttHdCh *)pSttHdChs->GetNext(pos1);
						if (pObj != NULL)
						{
							CString strText;
							int nGroupIndex;
							int nChCount = pSttModuleTag->m_nChCountU_Week / 3 + pSttModuleTag->m_nChCountI_Week / 3;
							for (int nChGroupIndex = 0; nChGroupIndex < nChCount; nChGroupIndex++)
							{
								//U1 区分对应Uw1_1 Uw1_4 Uw1_7 Uw1_10
								strText.Format(_T("Uw%d_%d"), nWeakModuleIndex, nChGroupIndex * 3 + nIndex + 1 - 3*(nIndex/3));
								int nChGroupIndexTmt = nChGroupIndex * 3 + nIndex + 1 - 3*(nIndex/3);
								nGroupIndex = (nChGroupIndexTmt - 1) / 3 + (nWeakModuleIndex - 1) * 3;
								if (pObj->m_strName == strText)
								{
									if (nIndex + 1 <= 3)
									{
										m_nCurChIsMap[nGroupIndex].push_back(1);//记录U1 U2 U3是否都对应上
									}
									else
									{
										m_nCurChIsMap2[nGroupIndex].push_back(1);
									}
								}
								else
								{
									CString str = pObj->m_strName;
									int underPos = str.Find(_T("_")); // 找到下划线的位置
									if (underPos != -1) {
										CString nChModuleIndexTmt = str.Mid(2, underPos - 2);
										CString nChGroupIndexTmt = str.Mid(underPos + 1);
										int nGroupIndexTmt = (nChGroupIndexTmt.toInt() - 1) / 3 + (nChModuleIndexTmt.toInt() - 1) * 3;
										if (nGroupIndexTmt < this->rowCount())
										{
											if (nIndex + 1 <= 3)
											{
												m_nCurChIsMap[nGroupIndexTmt].push_back(0);//记录U1 U2 U3是否都对应上
											}
											else
											{
												m_nCurChIsMap2[nGroupIndexTmt].push_back(0);
											}
										}
									}
								}
							}
						}
						else
						{
							if (nIndex + 1 <= 3)
							{
								m_nCurChIsNullNum.push_back(1);
							}
							else
							{
								m_nCurChIsNullNum2.push_back(1);
							}
						}
					}
				}
			}
		}
		nWeakModuleIndex++;
	}
	UpdateComboxIndex();
}

void CChMapsWeakQuickGrid::UpdateComboxIndex()
{
	for (int i = 0; i < m_nVolChIsMap.size(); i++)
	{
		QWidget *widget = this->cellWidget(i, 1);
		QCenterComboBox *pComboBox = qobject_cast<QCenterComboBox*>(widget);
		if (!pComboBox)
		{
			break;
		}
		if (m_nVolChIsNullNum.size() >= 3)// U1 U2 U3映射为空
		{
			pComboBox->setCurrentIndex(1);
		}
		else
		{
			int nIsNotMapCount = 0;
			int nIsMapCount = 0;
			for (int nIndex = 0; nIndex < m_nVolChIsMap[i].size(); nIndex++)//每一行中映射上的个数
			{
				if (m_nVolChIsMap[i][nIndex] == 1)
				{
					nIsMapCount++;
				}
				else
				{
					nIsNotMapCount++;
				}
			}
			
			if (nIsMapCount >= 3)//三个都能对应上,则为映射
			{
				// 获取(1, 1)位置的QCenterComboBox
				pComboBox->setCurrentIndex(0);
			}
			else if (nIsMapCount > 0) // 小于3但大于0
			{
				pComboBox->setCurrentIndex(2); // 设置索引为0
			}
			else if (nIsMapCount == 0)//表示没有映射通道
			{
				if (nIsNotMapCount >= 1)//没有映射上但是有内容
				{
					pComboBox->setCurrentIndex(2);
				}
				else
				{
					pComboBox->setCurrentIndex(1);
				}
			}
			
		}
	}


	for (int i = 0; i < m_nVolChIsMap2.size(); i++)
	{
		QWidget *widget = this->cellWidget(i, 2);
		QCenterComboBox *pComboBox = qobject_cast<QCenterComboBox*>(widget);
		if (!pComboBox)
		{
			break;
		}
		if (m_nVolChIsNullNum2.size() >= 3)// U1 U2 U3映射为空
		{
			pComboBox->setCurrentIndex(1);
		}
		else
		{
			int nIsNotMapCount = 0;
			int nIsMapCount = 0;
			for (int nIndex = 0; nIndex < m_nVolChIsMap2[i].size(); nIndex++)//每一行中映射上的个数
			{
				if (m_nVolChIsMap2[i][nIndex] == 1)
				{
					nIsMapCount++;
				}
				else
				{
					nIsNotMapCount++;
				}
			}
			
			if (nIsMapCount >= 3)//三个都能对应上,则为映射
			{
				// 获取(1, 1)位置的QCenterComboBox
				pComboBox->setCurrentIndex(0);
			}
			else if (nIsMapCount > 0) // 小于3但大于0
			{
				pComboBox->setCurrentIndex(2); // 设置索引为0
			}
			else if (nIsMapCount == 0)//表示没有映射通道
			{
				if (nIsNotMapCount >= 1)//没有映射上但是有内容
				{
					pComboBox->setCurrentIndex(2);
				}
				else
				{
					pComboBox->setCurrentIndex(1);

				}
			}
			
		}
	}


	for (int i = 0; i < m_nCurChIsMap.size(); i++)
	{
		QWidget *widget = NULL;
		if (g_oSttTestResourceMngr.m_pTestResouce->GetTestRsType() == STT_TEST_RESOURCE_TYPE_6U6I)
		{
			widget = this->cellWidget(i, 3);
		}
		else
		{
			widget = this->cellWidget(i, 2);
		}
		QCenterComboBox *pComboBox = qobject_cast<QCenterComboBox*>(widget);
		if (!pComboBox)
		{
			break;
		}
		if (m_nCurChIsNullNum.size() >= 3)
		{
			pComboBox->setCurrentIndex(1);
		}
		else
		{
			int nIsMapCount = 0;
			int nIsNotMapCount = 0;
			for (int nIndex = 0; nIndex < m_nCurChIsMap[i].size(); nIndex++)
			{
				if (m_nCurChIsMap[i][nIndex] == 1)
				{
					nIsMapCount++;
				}
				else
				{
					nIsNotMapCount++;
				}
			}
			if (nIsMapCount >= 3)//三个都能对应上,则为映射
			{
				// 获取(1, 1)位置的QCenterComboBox
				pComboBox->setCurrentIndex(0);
			}
			else if (nIsMapCount > 0) // 小于3但大于0
			{
				pComboBox->setCurrentIndex(2); // 设置索引为0
			}
			else if (nIsMapCount == 0)//表示没有映射通道
			{
				if (nIsNotMapCount >= 1)
				{
					pComboBox->setCurrentIndex(2);
				}
				else
				{
					pComboBox->setCurrentIndex(1);
				}
			}
		}

	}
	for (int i = 0; i < m_nCurChIsMap2.size(); i++)
	{
		QWidget *widget = this->cellWidget(i, 4);
		QCenterComboBox *pComboBox = qobject_cast<QCenterComboBox*>(widget);
		if (!pComboBox)
		{
			break;
		}
		if (m_nCurChIsNullNum2.size() >= 3)
		{
			pComboBox->setCurrentIndex(1);
		}
		else
		{
			int nIsNotMapCount = 0;
			int nIsMapCount = 0;
			for (int nIndex = 0; nIndex < m_nCurChIsMap2[i].size(); nIndex++)
			{
				if (m_nCurChIsMap2[i][nIndex] == 1)
				{
					nIsMapCount++;
				}
				else
				{
					nIsNotMapCount++;
				}
			}
			if (nIsMapCount >= 3)//三个都能对应上,则为映射
			{
				// 获取(1, 1)位置的QCenterComboBox
				pComboBox->setCurrentIndex(0);
			}
			else if (nIsMapCount > 0) // 小于3但大于0
			{
				pComboBox->setCurrentIndex(2); // 设置索引为0
			}
			else if (nIsMapCount == 0)//表示没有映射通道
			{
				if (nIsNotMapCount >= 1)
				{
					pComboBox->setCurrentIndex(2);
				}
				else
				{
					pComboBox->setCurrentIndex(1);
				}

			}

		}

	}

}

QCenterComboBox* CChMapsWeakQuickGrid::NewErrorType()
{
	QCenterComboBox *pCbbError = new QCenterComboBox(this);
	QStringList strTextList;
	strTextList << "映射" << "不映射" << "自定义";
	pCbbError->addItems(strTextList);
	return pCbbError;
}

void CChMapsWeakQuickGrid::ComboxModelStyle(QCenterComboBox *pCombox)
{
	QLineEdit *pLineEdit = new QLineEdit();
	pLineEdit->setReadOnly(true); 
	pLineEdit->setAlignment(Qt::AlignCenter);
	pLineEdit->installEventFilter(pCombox);
	pCombox->setLineEdit(pLineEdit);
}

void CChMapsWeakQuickGrid::slot_comboxIndexChanged(QString strText)
{
	QCenterComboBox *comBox = dynamic_cast<QCenterComboBox*>(this->sender());

	if (NULL == comBox)
	{
		return;
	}

	int index = comBox->findText(strText); // 找到文本字符串在下拉框中的索引

	if (index != -1)
	{
		int x = comBox->frameGeometry().x();
		int y = comBox->frameGeometry().y();
		QModelIndex nMoudleindex = this->indexAt(QPoint(x, y));
		int nRow = nMoudleindex.row();
		int nColumn = nMoudleindex.column();
		int MoudleIndex, GroupIndex;
		bool bIsAppendState = false;
		QTableWidgetItem *item = this->item(nRow, 0);

		if (index == 0)
		{
			//遍历当前行的其他下拉框
			for (int i = 0; i < this->columnCount(); i++)
			{
				if (i != nColumn)
				{
					QCenterComboBox *otherComboBox = qobject_cast<QCenterComboBox*>(this->cellWidget(nRow, i));
					if (otherComboBox)
					{
						otherComboBox->setCurrentIndex(1);
					}
				}
			}
		}
		if ((index == 0) || (index == 1))
		{
			for (int i = 0; i < this->rowCount(); i++)
			{
				if (i != nRow)
				{
					QCenterComboBox *otherComboBox = qobject_cast<QCenterComboBox*>(this->cellWidget(i, nColumn));
					int index = otherComboBox->currentIndex();
					if ((index == 0) || (index == 2))
					{
						bIsAppendState = true;
					}
				}
			}
			MoudleIndex = m_nModuleGroupInfo.at(nRow).moduleNumber;
			GroupIndex = m_nModuleGroupInfo.at(nRow).groupNumber;
			int nUChGroupCount = g_oSttTestResourceMngr.m_pTestResouce->m_oVolChRsListRef.GetCount() / 3;

			if (nColumn - 1 < nUChGroupCount)
			{
				emit sig_WeakChMapStateIsChanged(WeakMoudle_U, MoudleIndex, GroupIndex, (nColumn - 1) * 3 + 1, index, bIsAppendState);
			}
			else
			{
				emit sig_WeakChMapStateIsChanged(WeakMoudle_I, MoudleIndex, GroupIndex, (nColumn - 1) / 3 * 3 + 1, index, bIsAppendState);
			}
		}

	}
}

void CChMapsWeakQuickGrid::slot_UpdateWeakComboxState(CSttChMaps *pSttChMaps)
{
	InitChMapsState(pSttChMaps);
}