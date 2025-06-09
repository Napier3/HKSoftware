#include "QChMapsAnalogQuickGrid.h"
#include "../../../../Module/SttTestResourceMngr/SttTestResourceMngr.h"

#include <QHeaderView>
#include <QLineEdit>

CChMapsAnalogQuickGrid::CChMapsAnalogQuickGrid(int nType, QWidget *parent)
: QTableWidget(parent)
{
	m_pSttChMaps = new CSttChMaps;
	m_nType = nType;
}

CChMapsAnalogQuickGrid::~CChMapsAnalogQuickGrid()
{

}

void CChMapsAnalogQuickGrid::InitGrid(long nType, CSttChMaps *pChMaps)
{
	QStringList HStrList, VStrList;//水平表头 竖直表头
	QString strText;
	int nRowCount = 0;
	int nAnalogUChCount, nAnalogIChCount, nAnalogUIChCount;

	nAnalogUChCount = g_oSttTestResourceMngr.m_oAnalogU_Tags.GetCount();
	nAnalogIChCount = g_oSttTestResourceMngr.m_oAnalogI_Tags.GetCount();
	nAnalogUIChCount = g_oSttTestResourceMngr.m_oAnalogUI_Tags.GetCount();

	if (nType == AnalogMoudle_U)
	{
		int nCurrIndex = 0;//记录当前模块号
		for (int nIndex = 0; nIndex < nAnalogUChCount; nIndex++)
		{
			int nGroupCount = g_oSttTestResourceMngr.m_oAnalogU_Tags[nIndex]->m_nChCountU / 3;
			nRowCount += nGroupCount;
			for (int nGroupIndex = 0; nGroupIndex < nGroupCount; nGroupIndex++)
			{
				strText = QString("电压模块%1-第%2组").arg(nIndex + 1).arg(nGroupIndex + 1);
				VStrList << strText;
				ModuleGroupInfo info;
				info.moduleNumber = nIndex + 1;
				info.groupNumber = nGroupIndex + 1;
				m_nModuleVolGroupInfo.append(info);
			}
			nCurrIndex = nIndex + 1;
		}

		for (int nIndex = nCurrIndex; nIndex < nAnalogUIChCount + nAnalogUChCount; nIndex++)
		{
			int nGroupCount = g_oSttTestResourceMngr.m_oAnalogUI_Tags[nIndex]->m_nChCountU / 3;
			nRowCount += nGroupCount;
			for (int nGroupIndex = 0; nGroupIndex < nGroupCount; nGroupIndex++)
			{
				strText = QString("电压模块%1-第%2组").arg(nIndex + 1).arg(nGroupIndex + 1);
				VStrList << strText;
				ModuleGroupInfo info;
				info.moduleNumber = nIndex + 1;
				info.groupNumber = nGroupIndex + 1;
				m_nModuleVolGroupInfo.append(info);
			}
		}
	}
	else if (nType == AnalogMoudle_I)
	{
		int nCurrIndex = 0;//记录当前模块号
		for (int nIndex = 0; nIndex < nAnalogIChCount; nIndex++)
		{
			int nGroupCount = g_oSttTestResourceMngr.m_oAnalogI_Tags[nIndex]->m_nChCountI / 3;
			nRowCount += nGroupCount;
			for (int nGroupIndex = 0; nGroupIndex < nGroupCount; nGroupIndex++)
			{
				strText = QString("电流模块%1-第%2组").arg(nIndex + 1).arg(nGroupIndex + 1);
				VStrList << strText;
				ModuleGroupInfo info;
				info.moduleNumber = nIndex + 1;
				info.groupNumber = nGroupIndex + 1;
				m_nModuleCurGroupInfo.append(info);
			}
			nCurrIndex = nIndex + 1;
		}

		for (int nIndex = nCurrIndex; nIndex < nAnalogUIChCount + nAnalogIChCount; nIndex++)
		{
			int nGroupCount = g_oSttTestResourceMngr.m_oAnalogUI_Tags[nIndex]->m_nChCountI / 3;
			nRowCount += nGroupCount;
			for (int nGroupIndex = 0; nGroupIndex < nGroupCount; nGroupIndex++)
			{
				strText = QString("电流模块%1-第%2组").arg(nIndex + 1).arg(nGroupIndex + 1);
				VStrList << strText;
				ModuleGroupInfo info;
				info.moduleNumber = nIndex + 1;
				info.groupNumber = nGroupIndex + 1;
				m_nModuleCurGroupInfo.append(info);
			};
		}
	}
	setRowCount(nRowCount);
	
	HStrList.push_back(QString(tr("模块名称")));
	if (g_oSttTestResourceMngr.m_pTestResouce->GetTestRsType() == STT_TEST_RESOURCE_TYPE_4U3I)
	{
		setColumnCount(2);
		if (nType == AnalogMoudle_U)
		{
			HStrList.push_back(QString(tr("Ua1、Ub1、Uc1")));

		}
		else if (nType == AnalogMoudle_I)
		{
			HStrList.push_back(QString(tr("Ia1、Ib1、Ic1")));
		}
		
	}
	else if (g_oSttTestResourceMngr.m_pTestResouce->GetTestRsType() == STT_TEST_RESOURCE_TYPE_6U6I)
	{
		setColumnCount(3);
		if (nType == AnalogMoudle_U)
		{
			HStrList.push_back(QString(tr("Ua1、Ub1、Uc1")));
			HStrList.push_back(QString(tr("Ua2、Ub2、Uc2")));
		}
		else if (nType == AnalogMoudle_I)
		{
			HStrList.push_back(QString(tr("Ia1、Ib1、Ic1")));
			HStrList.push_back(QString(tr("Ia2、Ib2、Ic2")));
		}
	}
	setHorizontalHeaderLabels(HStrList);
	
	for (int nIndex = 0; nIndex < this->columnCount(); nIndex++)
	{
		if (nIndex == 0)//给前两列设置一个比较大的值，使其能正常显示
		{
			setColumnWidth(nIndex, 130);
		}
		else
		{
			 resizeColumnToContents(nIndex);
		}
	}
	this->horizontalHeader()->setStretchLastSection(true); //设置充满表宽度
	this->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}");
	this->setStyleSheet("selection-background-color: grey;selection-color: black");
	InsertItem(nType, VStrList);
	InitChMapsState(nType, pChMaps);
}

void CChMapsAnalogQuickGrid::InsertItem(long nType, QStringList strList)
{	
	for (int i = 0; i < this->rowCount(); i++)
	{
		QString strText = strList.at(i);
		setItem(i, 0, new QTableWidgetItem(strText));
		m_pComboBoxList1.append(NewErrorType());
		setCellWidget(i, 1, m_pComboBoxList1[i]);
		ComboxModelStyle(m_pComboBoxList1[i]);
		connect(m_pComboBoxList1[i], SIGNAL(currentIndexChanged(QString)), this, SLOT(slot_comboxIndexChanged(QString)));

		if (this->columnCount() > 2)
		{
			m_pComboBoxList2.append(NewErrorType());
			setCellWidget(i, 2, m_pComboBoxList2[i]);
			ComboxModelStyle(m_pComboBoxList2[i]);
			connect(m_pComboBoxList2[i], SIGNAL(currentIndexChanged(QString)), this, SLOT(slot_comboxIndexChanged(QString)));
		}

	}
}

void CChMapsAnalogQuickGrid::InitChMapsState(long nType, CSttChMaps *pChMaps)
{
	m_pSttChMaps = pChMaps;
	CSttChMap *pSttChMap = NULL;
	CSttModuleTag *pSttModuleTag = NULL;
	CString strSoftRsID;
	long nVolModuleIndex = 1, nCurModuleIndex = 1;
	POS posU = g_oSttTestResourceMngr.m_oAnalogU_Tags.GetHeadPosition();
	POS posI = g_oSttTestResourceMngr.m_oAnalogI_Tags.GetHeadPosition();
	POS posUI = g_oSttTestResourceMngr.m_oAnalogUI_Tags.GetHeadPosition();

	if (nType == AnalogMoudle_U)
	{
		m_nVolChIsMap.clear();
		m_nVolChIsMap.resize(this->rowCount());
		m_nVolChIsMap2.clear();
		m_nVolChIsMap2.resize(this->rowCount());
		m_nVolChIsNullNum.clear();
		m_nVolChIsNullNum2.clear();
		while (posU)//遍历混合插件每一个模块
		{
			pSttModuleTag = (CSttModuleTag *)g_oSttTestResourceMngr.m_oAnalogU_Tags.GetNext(posU);
			if (pSttModuleTag == NULL)
			{
				break;
			}

			for (int nIndex = 0; nIndex < g_oSttTestResourceMngr.m_pTestResouce->m_oVolChRsListRef.GetCount(); nIndex++)
			{//模块中的每一个电压U1 U2 U3
				strSoftRsID.Format(_T("U%ld"),nIndex + 1);
				pSttChMap = m_pSttChMaps->GetChMap(strSoftRsID);
				if (pSttChMap != NULL)
				{
					CSttHdChs *pSttHdChs = (CSttHdChs *)pSttChMap->FindByID(STT_MODULETYPE_ID_ANALOG);
					if (pSttHdChs == NULL)
					{
						if (nIndex + 1 <= 3)
						{
							m_nVolChIsNullNum.push_back(1);//若为空，则往对应的数组中添加1，用以计数，无其他含义
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
								for (int nChGroupIndex = 0; nChGroupIndex < pSttModuleTag->m_nChCountU / 3; nChGroupIndex++)
								{
									//U1 区分对应U1_1 U1_4 U2_1 U2_4
									strText.Format(_T("U%d_%d"), nVolModuleIndex, nChGroupIndex * 3 + nIndex + 1 - 3*(nIndex/3));
									int nChGroupIndexTmt = nChGroupIndex * 3 + nIndex + 1 - 3*(nIndex/3);
									nGroupIndex = (nChGroupIndexTmt - 1) / 3 + (nVolModuleIndex - 1) * 3;
									if (pObj->m_strName == strText)
									{
										//nGroupIndex = (nChGroupIndex * 3 + nVolChIndex - 1 -3*((nVolChIndex-1)/3)) / 3;					
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
										CString str = pObj->m_strName;
										int underPos = str.Find(_T("_")); // 找到下划线的位置
 										if (underPos != -1) {
 											CString nChModuleIndexTmt = str.Mid(1, underPos - 1);
 											CString nChGroupIndexTmt = str.Mid(underPos + 1);
 											int nGroupIndexTmt = (nChGroupIndexTmt.toInt() - 1) / 3 + (nChModuleIndexTmt.toInt() - 1) * 3;
											if (nGroupIndexTmt < this->rowCount())
											{
												nGroupIndex = nGroupIndexTmt;
												if (nIndex + 1 <= 3)
												{
													m_nVolChIsMap[nGroupIndex].push_back(0);//记录U1 U2 U3是否都对应上
												}
												else
												{
													m_nVolChIsMap2[nGroupIndex].push_back(0);
												}

											}
 										}
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
			nVolModuleIndex++;
		}
	}

	else if (nType == AnalogMoudle_I)
	{
		m_nCurChIsMap.clear();
		m_nCurChIsMap.resize(this->rowCount());
		m_nCurChIsMap2.clear();
		m_nCurChIsMap2.resize(this->rowCount());
		m_nCurChIsNullNum.clear();
		m_nCurChIsNullNum2.clear();
		while (posI)//遍历电流插件每一个模块
		{
			pSttModuleTag = (CSttModuleTag *)g_oSttTestResourceMngr.m_oAnalogI_Tags.GetNext(posI);
			if (pSttModuleTag == NULL)
			{
				break;
			}

			for (int nIndex = 0; nIndex < g_oSttTestResourceMngr.m_pTestResouce->m_oCurChRsListRef.GetCount(); nIndex++)
			{//模块中的每一个电压I1 I2 I3
				strSoftRsID.Format(_T("I%ld"), nIndex + 1);
				pSttChMap = m_pSttChMaps->GetChMap(strSoftRsID);
				if (pSttChMap != NULL)
				{
					CSttHdChs *pSttHdChs = (CSttHdChs *)pSttChMap->FindByID(STT_MODULETYPE_ID_ANALOG);
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
								for (int nChGroupIndex = 0; nChGroupIndex < pSttModuleTag->m_nChCountI / 3; nChGroupIndex++)
								{
									strText.Format(_T("I%d_%d"), nCurModuleIndex, nChGroupIndex * 3 + nIndex + 1 - 3*(nIndex/3));
									int nChGroupIndexTmt = nChGroupIndex * 3 + nIndex + 1 - 3*(nIndex/3);
									nGroupIndex = (nChGroupIndexTmt - 1) / 3 + (nCurModuleIndex - 1) * 3;
									if (pObj->m_strName == strText)
									{
										//nGroupIndex = (nChGroupIndex * 3 + nCurChIndex - 1 -3*((nCurChIndex-1)/3)) / 3;
										
										if (nIndex + 1 <= 3)
										{
											m_nCurChIsMap[nGroupIndex].push_back(1);
										}
										else
										{
											m_nCurChIsMap2[nGroupIndex].push_back(1);
										}
									}
									else
									{//软件资源中有内容，但是映射不对应
										CString str = pObj->m_strName;
										int underPos = str.Find(_T("_")); // 找到下划线的位置
										if (underPos != -1) {
											CString nChModuleIndexTmt = str.Mid(1, underPos - 1);
											CString nChGroupIndexTmt = str.Mid(underPos + 1);
											int nGroupIndexTmt = (nChGroupIndexTmt.toInt() - 1) / 3 + (nChModuleIndexTmt.toInt() - 1) * 3;
											if (nGroupIndexTmt < this->rowCount())
											{
												nGroupIndex = nGroupIndexTmt;
												if (nIndex + 1 <= 3)
												{
													m_nCurChIsMap[nGroupIndex].push_back(0);
												}
												else
												{
													m_nCurChIsMap2[nGroupIndex].push_back(0);
												}
											}
										}

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
			nCurModuleIndex++;
		}
	}

	while(posUI)//遍历混合插件每一个模块
	{
		pSttModuleTag = (CSttModuleTag *)g_oSttTestResourceMngr.m_oAnalogUI_Tags.GetNext(posUI);
		if (pSttModuleTag == NULL)
		{
			break;
		}

		if (nType == AnalogMoudle_U)
		{
			for (int nIndex = 0; nIndex < g_oSttTestResourceMngr.m_pTestResouce->m_oVolChRsListRef.GetCount(); nIndex++)
			{
				//模块中的每一个电压U1 U2 U3
				strSoftRsID.Format(_T("U%ld"),nIndex + 1);
				pSttChMap = m_pSttChMaps->GetChMap(strSoftRsID);
				if (pSttChMap != NULL)
				{
					CSttHdChs *pSttHdChs = (CSttHdChs *)pSttChMap->FindByID(STT_MODULETYPE_ID_ANALOG);
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
								for (int nChGroupIndex = 0; nChGroupIndex < pSttModuleTag->m_nChCountU / 3; nChGroupIndex++)
								{
									//U1 区分对应U1_1 U1_4 U2_1 U2_4
									strText.Format(_T("U%d_%d"), nVolModuleIndex, nChGroupIndex * 3 + nIndex + 1 - 3*(nIndex/3));
									int nChGroupIndexTmt = nChGroupIndex * 3 + nIndex + 1 - 3*(nIndex/3);
									nGroupIndex = (nChGroupIndexTmt - 1) / 3 + (nVolModuleIndex - 1) * 3;
									if (pObj->m_strName == strText)
									{
										//nGroupIndex = (nChGroupIndex * 3 + nVolChIndex - 1 -3*((nVolChIndex-1)/3)) / 3;
										
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
										CString str = pObj->m_strName;
										int underPos = str.Find(_T("_")); // 找到下划线的位置
										if (underPos != -1) {
											CString nChModuleIndexTmt = str.Mid(1, underPos - 1);
											CString nChGroupIndexTmt = str.Mid(underPos + 1);
											int nGroupIndexTmt = (nChGroupIndexTmt.toInt() - 1) / 3 + (nChModuleIndexTmt.toInt() - 1) * 3;
											if (nGroupIndexTmt < this->rowCount())
											{
												nGroupIndex = nGroupIndexTmt;
												if (nIndex + 1 <= 3)
												{
													m_nVolChIsMap[nGroupIndex].push_back(0);//记录U1 U2 U3是否都对应上
												}
												else
												{
													m_nVolChIsMap2[nGroupIndex].push_back(0);
												}
											}
										}
										
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
			nVolModuleIndex++;
		}
		else if (nType == AnalogMoudle_I)
		{
			for (int nIndex = 0; nIndex < g_oSttTestResourceMngr.m_pTestResouce->m_oCurChRsListRef.GetCount(); nIndex++)
			{
				//模块中的每一个电压U1 U2 U3
				strSoftRsID.Format(_T("I%ld"),nIndex + 1);
				pSttChMap = m_pSttChMaps->GetChMap(strSoftRsID);
				if (pSttChMap != NULL)
				{
					CSttHdChs *pSttHdChs = (CSttHdChs *)pSttChMap->FindByID(STT_MODULETYPE_ID_ANALOG);
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
						else
						{
							while (pos1)
							{
								pObj = (CSttHdCh *)pSttHdChs->GetNext(pos1);
								if (pObj != NULL)
								{
									CString strText;
									int nGroupIndex;
									for (int nChGroupIndex = 0; nChGroupIndex < pSttModuleTag->m_nChCountI / 3; nChGroupIndex++)
									{
										strText.Format(_T("I%d_%d"), nCurModuleIndex, nChGroupIndex * 3 + nIndex + 1 - 3*(nIndex/3));
										int nChGroupIndexTmt = nChGroupIndex * 3 + nIndex + 1 - 3*(nIndex/3);
										nGroupIndex = (nChGroupIndexTmt - 1) / 3 + (nCurModuleIndex - 1) * 3;
										if (pObj->m_strName == strText)
										{
											//nGroupIndex = (nChGroupIndex * 3 + nCurChIndex - 1 -3*((nCurChIndex-1)/3)) / 3;
											if (nIndex + 1 <= 3)
											{
												m_nCurChIsMap[nGroupIndex].push_back(1);
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
												CString nChModuleIndexTmt = str.Mid(1, underPos - 1);
												CString nChGroupIndexTmt = str.Mid(underPos + 1);
												int nGroupIndexTmt = (nChGroupIndexTmt.toInt() - 1) / 3 + (nChModuleIndexTmt.toInt() - 1) * 3;
												if (nGroupIndexTmt < this->rowCount())
												{
													nGroupIndex = nGroupIndexTmt;
													if (nIndex + 1 <= 3)
													{
														m_nCurChIsMap[nGroupIndex].push_back(0);
													}
													else
													{
														m_nCurChIsMap2[nGroupIndex].push_back(0);
													}
												}
											}

										}
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
			nCurModuleIndex++;
		}
	}
	UpdateComboxIndex(nType);
}

void CChMapsAnalogQuickGrid::UpdateComboxIndex(long nType)
{
	if (nType == AnalogMoudle_U)
	{
		for (int i = 0; i < m_nVolChIsMap.size(); i++)
		{
			QWidget *widget = this->cellWidget(i, 1);
			QCenterComboBox *pComboBox = qobject_cast<QCenterComboBox*>(widget);
			if (!pComboBox)
			{
				break;
			}
			if (m_nVolChIsNullNum.size() >= 3)
			{
				pComboBox->setCurrentIndex(1);
			}
			else
			{
				int nIsNotMapCount = 0;
				int nIsMapCount = 0;
				for (int nIndex = 0; nIndex < m_nVolChIsMap[i].size(); nIndex++)
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
		for (int i = 0; i < m_nVolChIsMap2.size(); i++)
		{
			QWidget *widget = this->cellWidget(i, 2);
			QCenterComboBox *pComboBox = qobject_cast<QCenterComboBox*>(widget);
			if (!pComboBox)
			{
				break;
			}
			if (m_nVolChIsNullNum2.size() >= 3)
			{
				pComboBox->setCurrentIndex(1);
			}
			else
			{
				int nIsNotMapCount = 0;
				int nIsMapCount = 0;
				for (int nIndex = 0; nIndex < m_nVolChIsMap2[i].size(); nIndex++)
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
	else if (nType == AnalogMoudle_I)
	{
		for (int i = 0; i < m_nCurChIsMap.size(); i++)
		{
			QWidget *widget = this->cellWidget(i, 1);
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
			QWidget *widget = this->cellWidget(i, 2);
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


}

QCenterComboBox* CChMapsAnalogQuickGrid::NewErrorType()
{
	QCenterComboBox *pCbbError = new QCenterComboBox(this);
	QStringList strTextList;
	strTextList << "映射" << "不映射" << "自定义";
	pCbbError->addItems(strTextList);

	return pCbbError;
}

void CChMapsAnalogQuickGrid::ComboxModelStyle(QCenterComboBox *pCombox)
{
	QLineEdit *pLineEdit = new QLineEdit;
	pLineEdit->setReadOnly(true); 
	pLineEdit->setAlignment(Qt::AlignCenter);
	pLineEdit->installEventFilter(pCombox);
	pCombox->setLineEdit(pLineEdit);
}

void CChMapsAnalogQuickGrid::slot_comboxIndexChanged(QString strText)
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
		QModelIndex Moudleindex = this->indexAt(QPoint(x, y));
		int nRow = Moudleindex.row();
		int nColumn = Moudleindex.column();
		int nType, MoudleIndex, GroupIndex;
		bool bIsAppendState = false;
		QTableWidgetItem *item = this->item(nRow, 0);
		if (m_nType == 0)
		{
			nType = AnalogMoudle_U;
		}
		else
		{
			nType = AnalogMoudle_I;
		}

		if ((index == 0))
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

		}
		if (nType == AnalogMoudle_U)
		{
			MoudleIndex = m_nModuleVolGroupInfo.at(nRow).moduleNumber;
			GroupIndex = m_nModuleVolGroupInfo.at(nRow).groupNumber;
		}
		else if (nType == AnalogMoudle_I)
		{
			MoudleIndex = m_nModuleCurGroupInfo.at(nRow).moduleNumber;
			GroupIndex = m_nModuleCurGroupInfo.at(nRow).groupNumber;
		}
		emit sig_ChMapStateIsChanged(nType, MoudleIndex, GroupIndex, (nColumn - 1) * 3 + 1, index, bIsAppendState);
	}
}

void CChMapsAnalogQuickGrid::slot_UpdateAnalogUComboxState(CSttChMaps *pSttChMaps)
{
	InitChMapsState(AnalogMoudle_U, pSttChMaps);
}

void CChMapsAnalogQuickGrid::slot_UpdateAnalogIComboxState(CSttChMaps *pSttChMaps)
{
	InitChMapsState(AnalogMoudle_I, pSttChMaps);
}

QCenterComboBox::QCenterComboBox(QWidget *parent) : QComboBox(parent)
{
	m_bPopupVisible = false;
}

QCenterComboBox::~QCenterComboBox()
{

}

bool QCenterComboBox::eventFilter(QObject *watched, QEvent *event)
{
	QString str = watched->metaObject()->className();
	if(QString(watched->metaObject()->className()) == "QLineEdit")
	{
		QLineEdit* lineEdit = static_cast<QLineEdit*>(watched);
		if (event->type() == QEvent::MouseButtonPress
			|| event->type() == QEvent::MouseButtonDblClick)
		{

			QCenterComboBox*  box = qobject_cast<QCenterComboBox*>(watched->parent());
			if(box && box == this && box->isEnabled())
			{
				if (m_bPopupVisible) // 如果下拉框已显示，则隐藏
				{
					box->hidePopup();
					m_bPopupVisible = false;
				}
				else // 如果下拉框未显示，则显示
				{
					box->showPopup();
					m_bPopupVisible = true;
				}
			}
			return true;
		}
	}
	else
	{
		QComboBox::eventFilter(watched, event);
		return true;
	}
	return false;
}