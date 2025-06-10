#include "SttSclIedDrawViewWidget.h"
#include <QResizeEvent>
#include "../../../XLangResource_Native.h"

QSttSclIedDrawViewWidget::QSttSclIedDrawViewWidget( QWidget *parent)
{
	m_pCustomRect = NULL;
	m_pGraphicsScene = NULL;
	m_pGraphicsView = NULL;
	m_nHeightLeft = 220;
	m_nHeightRight = 220;
}

QSttSclIedDrawViewWidget::~QSttSclIedDrawViewWidget()
{

}

void QSttSclIedDrawViewWidget::InitUI()
{
	if (m_pGraphicsScene == NULL)// 检查是否已有场景和视图
	{
		m_pGraphicsScene = new QGraphicsScene();
		m_pGraphicsView = new QCustomGraphicsView();
		m_pGraphicsView->setMouseTracking(true);
		m_pGraphicsView->setScene(m_pGraphicsScene);
		QVBoxLayout* pMainLayout = new QVBoxLayout;
		pMainLayout->addWidget(m_pGraphicsView);
		setLayout(pMainLayout);
	}
 	else
	{
		m_pGraphicsScene->clear();// 清空现有场景
		//m_pGraphicsView->viewport()->update();// 重新绘制视图
		 m_pGraphicsView->scene()->update(); // 局部更新视图

// 		if (m_pGraphicsScene && m_pCustomRect) //调整场景布局
// 		{
// 			int nHeight = m_pCustomRect->getHeight();
// 			QRectF sceneRect = m_pGraphicsScene->sceneRect();
// 			sceneRect.setHeight(nHeight + 10);
// 			m_pGraphicsScene->setSceneRect(sceneRect);
// 		}
	}

	// 检查是否有有效的 CustomRect
	if (m_pCustomRect != NULL)
	{
		m_pGraphicsScene->addItem(m_pCustomRect);
	}

	for (int i = 0; i < m_pSmvOutBlockRect.size(); ++i)
	{
		if (m_pSmvOutBlockRect[i] != NULL)
		{
			m_pGraphicsScene->addItem(m_pSmvOutBlockRect[i]);
		}
	}
	for (int i = 0; i < m_pGooseoutBlockRect.size(); ++i)
	{
		if (m_pGooseoutBlockRect[i] != NULL)
		{
			m_pGraphicsScene->addItem(m_pGooseoutBlockRect[i]);
		}
	}

	for (int i = 0; i < m_pSmvInBlockRect.size(); ++i)
	{
		if (m_pSmvInBlockRect[i] != NULL)
		{
			m_pGraphicsScene->addItem(m_pSmvInBlockRect[i]);
		}
	}

	for (int i = 0; i < m_pGooseInBlockRect.size(); ++i)
	{
		if (m_pGooseInBlockRect[i] != NULL)
		{
			m_pGraphicsScene->addItem(m_pGooseInBlockRect[i]);
		}
	}

	for (int i = 0; i < m_pInputLeftRect.size(); ++i)
	{
		if (m_pInputLeftRect[i] != NULL)
		{
			m_pGraphicsScene->addItem(m_pInputLeftRect[i]);
		}
	}

	for (int i = 0; i < m_pInputRightRect.size(); ++i)
	{
		if (m_pInputRightRect[i] != NULL)
		{
			m_pGraphicsScene->addItem(m_pInputRightRect[i]);
		}
	}

	for (int i = 0; i < m_pArrowLine.size(); ++i)
	{
		if (m_pArrowLine[i] != NULL)
		{
			m_pGraphicsScene->addItem(m_pArrowLine[i]);
		}
	}

	for (int i = 0; i < m_pReceiveRect.size(); ++i)
	{
		if (m_pReceiveRect[i] != NULL)
		{
			m_pGraphicsScene->addItem(m_pReceiveRect[i]);
		}
	}
	for (int i = 0; i < m_pReceiveArrowLine.size(); ++i)
	{
		if (m_pReceiveArrowLine[i] != NULL)
		{
			m_pGraphicsScene->addItem(m_pReceiveArrowLine[i]);
		}
	}
}

void QSttSclIedDrawViewWidget::InitConnect()
{
 	for (int i = 0; i < m_pArrowLine.size(); ++i)
 	{	
		connect(m_pArrowLine[i],SIGNAL(arrowClicked()),this,SLOT(slot_Subend()));
	}

	for (int i = 0; i < m_pReceiveArrowLine.size(); ++i)
	{	
		connect(m_pReceiveArrowLine[i],SIGNAL(arrowClicked()),this,SLOT(slot_Subend()));
	}
}

void QSttSclIedDrawViewWidget::InitData( CSclIed *pSclIed )
{
	if (pSclIed == NULL)
	{
		return;
	}

	CString strName;
	strName = pSclIed->m_strID + "\n" + pSclIed->m_strName;
	
	Release();
	int nHeightOut = 210;

	m_pCustomRect = new QSttCustomRect(QPointF(400, 0), 170, 800, strName, NULL);
	m_pCustomRect->setFillColor(QColor(196,243,196));
	m_pCustomRect->setTextOffset(0, nHeightOut - 50); 
	m_pCustomRect->setCenterText(false);
	m_pCustomRect->setText(strName);

	
	m_nHeightRight = 195,m_nHeightLeft = 195;
	m_pReceiveBlockRect.clear();
	m_pReceiveInputRect.clear();

	for (int nIndex = 0; nIndex < m_strAppIdSmvOut.size(); ++nIndex)
	{
		QPair<CString, CString> dataPair = m_strAppIdSmvOut[nIndex];
		if (dataPair.first == strName)
		{
			QSttCustomRect *pSmvOutRect  = new QSttCustomRect(QPointF(420, nHeightOut), 130, 40, dataPair.second, NULL);
			pSmvOutRect->setFillColor(QColor(250, 167, 243));
			pSmvOutRect->setText(dataPair.second);
			m_pSmvOutBlockRect.append(pSmvOutRect);
			nHeightOut = nHeightOut + 50;

			QPair<CString, CString> dataPairOut(strName,dataPair.second);
			CompareSmv(dataPairOut);
		}
	}


	for (int nIndex = 0; nIndex < m_strAppIdGsOut.size(); ++nIndex)
	{
		QPair<CString, CString> dataPair = m_strAppIdGsOut[nIndex];
		if (dataPair.first == strName)
		{ 
			QSttCustomRect *pGooseoutRect = new QSttCustomRect(QPointF(420, nHeightOut), 130, 40, dataPair.second, NULL);
			pGooseoutRect->setFillColor(QColor(153, 204, 255));
			pGooseoutRect->setText(dataPair.second);

			m_pGooseoutBlockRect.append(pGooseoutRect);
			nHeightOut = nHeightOut + 50;

			QPair<CString, CString> dataPairOut(strName,dataPair.second);
			CompareGoose(dataPairOut);
		}
	}


	long nCount = 0;
	CString strAppID;
	m_pInputRect.clear();
	m_pInputBlockRect.clear();


	//for (int nIndex = 0; nIndex < m_strAppIdSmvIn.size(); ++nIndex)
	{
		//QPair<CString, CString> dataPair = m_strAppIdSmvIn[nIndex];
		CSclCtrlsSmvIn* pSclCtrlsSmvIn = pSclIed->GetSmvIns();
		POS posSmvIn = pSclCtrlsSmvIn->GetHeadPosition();
		CSclCtrlSmvIn* pSclCtrlSmvIn = NULL;
		while(posSmvIn)
		{
			pSclCtrlSmvIn = (CSclCtrlSmvIn*)pSclCtrlsSmvIn->GetNext(posSmvIn);
			
			CString strExtName = FindSclIedName(pSclCtrlSmvIn->iedExtName);

			//if (dataPair.first == pSclIed->m_strID)
			{
				//if(dataPair.second == strExtName)
				{
					nCount ++;
// 					strName = pSclCtrlSmvIn->m_strName;
// 					strName.replace("--", "\n");

					strAppID.Format(_T("0x%04X"),pSclCtrlSmvIn->m_dwAppID); 
					strAppID = _T("SMV ") + strAppID;

					if (nCount % 2 == 1)
					{
						QSttCustomRect *pInputLeftRect = new QSttCustomRect(QPointF(-50, m_nHeightLeft), 150, 70, strExtName, NULL);
						pInputLeftRect->setFillColor(QColor(229,242,196));
						pInputLeftRect->setText(strExtName);
						m_pInputLeftRect.append(pInputLeftRect);
						m_pInputRect.append(pInputLeftRect);
				
						QSttCustomRect *pSmvInBlockRect = new QSttCustomRect(QPointF(100, m_nHeightLeft+15), 130, 40, strAppID, NULL);
						pSmvInBlockRect->setFillColor(QColor(250, 167, 243));
						pSmvInBlockRect->setText(strAppID);
						m_pSmvInBlockRect.append(pSmvInBlockRect);
						
						m_pInputBlockRect.append(pSmvInBlockRect);


						QPointF start = pSmvInBlockRect->getRightCenter();
						QPointF end(m_pCustomRect->getPosition().x(), start.y());
						QSttCustomArrowLine *pSmvInArrow = new QSttCustomArrowLine(start,end,NULL);
						pSmvInArrow->setLineColor(QColor(72, 118, 255));
						pSmvInArrow->setHoverColor(QColor(102, 255, 51));
						m_pArrowLine.append(pSmvInArrow);

						m_nHeightLeft = m_nHeightLeft + 90;	
					}
					else
					{
						QSttCustomRect *pInputRightRect = new QSttCustomRect(QPointF(900, m_nHeightRight), 150, 70, /*strName*/strExtName, NULL);
						pInputRightRect->setFillColor(QColor(229,242,196));
						pInputRightRect->setText(strExtName);
						m_pInputRightRect.append(pInputRightRect);
						m_pInputRect.append(pInputRightRect);


						QSttCustomRect *pSmvInBlockRect = new QSttCustomRect(QPointF(780, m_nHeightRight+15), 130, 40, strAppID, NULL);
						pSmvInBlockRect->setFillColor(QColor(250, 167, 243));
						pSmvInBlockRect->setText(strAppID);
						m_pSmvInBlockRect.append(pSmvInBlockRect);
						m_pInputBlockRect.append(pSmvInBlockRect);


						QPointF start = pSmvInBlockRect->getLeftCenter();
						double width = m_pCustomRect->getWidth();
						QPointF end(m_pCustomRect->getPosition().x()+width, start.y());
						QSttCustomArrowLine *pSmvInArrow = new QSttCustomArrowLine(start,end,NULL);
						pSmvInArrow->setLineColor(QColor(72, 118, 255));
						pSmvInArrow->setHoverColor(QColor(102, 255, 51));
						m_pArrowLine.append(pSmvInArrow);

						m_nHeightRight = m_nHeightRight +90;
					} 
				}
			}
		}
	}

	//for (int nIndex = 0; nIndex < m_strAppIdGsIn.size(); ++nIndex)
	{
		//QPair<CString, CString> dataPair = m_strAppIdGsIn[nIndex];
		CSclCtrlsGsIn* pSclCtrlsGsIn = pSclIed->GetGsIns();
		POS posGsIn = pSclCtrlsGsIn->GetHeadPosition();
		while(posGsIn)
		{
			CSclCtrlGsIn* pSclCtrlGsIn = (CSclCtrlGsIn*)pSclCtrlsGsIn->GetNext(posGsIn);
			
			CString strExtName = FindSclIedName(pSclCtrlGsIn->m_strIedID);

			//if (dataPair.first == pSclIed->m_strID)
			{
				//if(dataPair.second == strExtName)
				{
					nCount ++;
// 					strName = pSclCtrlGsIn->m_strName;
// 					strName.replace("--", "\n");

					strAppID.Format(_T("0x%04X"),pSclCtrlGsIn->m_dwAppID); 
					strAppID = _T("GOOSE ") + strAppID;


					if (nCount % 2 == 1)
					{
						QSttCustomRect *pInputLeftRect = new QSttCustomRect(QPointF(-50, m_nHeightLeft), 150, 70, /*strName*/strExtName, NULL);
						pInputLeftRect->setFillColor(QColor(229,242,196));
						pInputLeftRect->setText(strExtName);
						m_pInputLeftRect.append(pInputLeftRect);
						m_pInputRect.append(pInputLeftRect);

						QSttCustomRect *pGsBlockRect = new QSttCustomRect(QPointF(100, m_nHeightLeft+15), 130, 40, strAppID, NULL);
						pGsBlockRect->setFillColor(QColor(153, 204, 255));
						pGsBlockRect->setText(strAppID);
						m_pGooseInBlockRect.append(pGsBlockRect);
						m_pInputBlockRect.append(pGsBlockRect);


						QPointF start = pGsBlockRect->getRightCenter();
						QPointF end(m_pCustomRect->getPosition().x(), start.y());
						QSttCustomArrowLine *pSmvInArrow = new QSttCustomArrowLine(start,end,NULL);
						pSmvInArrow->setLineColor(QColor(72, 118, 255));
						pSmvInArrow->setHoverColor(QColor(102, 255, 51));
						m_pArrowLine.append(pSmvInArrow);

						m_nHeightLeft = m_nHeightLeft + 90;
					}
					else
					{
						QSttCustomRect *pInputRightRect = new QSttCustomRect(QPointF(900, m_nHeightRight), 150, 70, /*strName*/strExtName, NULL);
						pInputRightRect->setFillColor(QColor(229,242,196));
						pInputRightRect->setText(strExtName);
						m_pInputRightRect.append(pInputRightRect);
						m_pInputRect.append(pInputRightRect);

						QSttCustomRect *pGsBlockRect = new QSttCustomRect(QPointF(780, m_nHeightRight+15), 130, 40, strAppID, NULL);
						pGsBlockRect->setFillColor(QColor(153, 204, 255));
						pGsBlockRect->setText(strAppID);
						m_pGooseInBlockRect.append(pGsBlockRect);
						m_pInputBlockRect.append(pGsBlockRect);


						QPointF start = pGsBlockRect->getLeftCenter();
						double width = m_pCustomRect->getWidth();
						QPointF end(m_pCustomRect->getPosition().x()+width, start.y());
						QSttCustomArrowLine *pSmvInArrow = new QSttCustomArrowLine(start,end,NULL);
						pSmvInArrow->setLineColor(QColor(72, 118, 255));
						pSmvInArrow->setHoverColor(QColor(102, 255, 51));
						m_pArrowLine.append(pSmvInArrow);

						m_nHeightRight = m_nHeightRight +90;
					} 
				}
			}
		}
	}

	if (m_pCustomRect->getHeight() <= m_nHeightRight || m_pCustomRect->getHeight() <= m_nHeightLeft)
	{
		int nMaxHeight = (m_nHeightLeft > m_nHeightRight) ? m_nHeightLeft : m_nHeightRight;
		m_pCustomRect->setHeight(nMaxHeight + 100);
	}
	
	InitUI();
	InitConnect();
} 


void QSttSclIedDrawViewWidget::IedDataInfo(CSclIed *pSclIed)
{
	CString strAppID ,strID ;
	strID = pSclIed->m_strID + "\n" + pSclIed->m_strName;

	CSclCtrlsGsOut* pSclCtrlsGsOut = pSclIed->GetGsOuts();
	POS posGsOut = pSclCtrlsGsOut->GetHeadPosition();
	while(posGsOut)
	{
		CSclCtrlGsOut* pSclCtrlGsOut = (CSclCtrlGsOut*)pSclCtrlsGsOut->GetNext(posGsOut);
		strAppID.Format(_T("0x%04X"),pSclCtrlGsOut->m_dwAppID);
		strAppID = _T("GOOSE ") + strAppID;
		QPair<CString, CString> dataPairGsOut(strID,strAppID);
		m_strAppIdGsOut.append(dataPairGsOut);//Goose输出


		long totalChs = 0;
		POS posInner = pSclCtrlGsOut->GetHeadPosition();
		CSclChGsOut* pChGsOut = NULL;
		while(posInner)
		{
			pChGsOut = (CSclChGsOut*)pSclCtrlGsOut->GetNext(posInner);	
			GsSubInputInfos(pChGsOut,strID ,strAppID,totalChs);
			totalChs++;
		}
	}
	
	CSclCtrlsSmvOut* pSclCtrlsSmvOut = pSclIed->GetSmvOuts();
	POS posSmvOut = pSclCtrlsSmvOut->GetHeadPosition();
	while(posSmvOut)
	{
		CSclCtrlSmvOut* pSclCtrlSmvOut = (CSclCtrlSmvOut*)pSclCtrlsSmvOut->GetNext(posSmvOut);
		strAppID.Format(_T("0x%04X"),pSclCtrlSmvOut->m_dwAppID);
		strAppID = _T("SMV ") + strAppID;
		QPair<CString, CString> dataPairSmvOut(strID,strAppID);
		m_strAppIdSmvOut.append(dataPairSmvOut);//smv输出

		long totalChs = 0;
		POS posInner = pSclCtrlSmvOut->GetHeadPosition();
		CSclChSmvOut* pChSmvOut = NULL;
		while(posInner)
		{
			pChSmvOut=(CSclChSmvOut*)pSclCtrlSmvOut->GetNext(posInner);	
			SMVSubInputInfos(pChSmvOut,strID ,strAppID,totalChs);
			totalChs++;
		}
	}


	CSclCtrlsGsIn* pSclCtrlsGsIn = pSclIed->GetGsIns();
	CString strName;
	POS posGsIn = pSclCtrlsGsIn->GetHeadPosition();
	while(posGsIn)
	{
		strID = pSclIed->m_strID;
		CSclCtrlGsIn* pSclCtrlGsIn = (CSclCtrlGsIn*)pSclCtrlsGsIn->GetNext(posGsIn);
		CString strExtName = pSclCtrlGsIn->m_strIedID;	
		strName = FindSclIedName(strExtName);
		QPair<CString, CString> dataPairGsIn(strID,strName);
		m_strAppIdGsIn.append(dataPairGsIn);
		strAppID.Format(_T("0x%04X"),pSclCtrlGsIn->m_dwAppID);
		strAppID = _T("GOOSE ") + strAppID;
		QPair<CString, CString> dataPairGsIn1(strName,strAppID);
		if (!m_strRecvAppIdGs.contains(dataPairGsIn1))
		{
			m_strRecvAppIdGs.append(dataPairGsIn1);
		}
		strID = pSclIed->m_strID + "\n" + pSclIed->m_strName;
		QPair<CString, CString> dataPairGsIn2(strID,strAppID);
		if (!m_strRecvAppIdIedGs.contains(dataPairGsIn2))
		{
			m_strRecvAppIdIedGs.append(dataPairGsIn2);
		}

		CString strID = pSclIed->m_strID + "\n" + pSclIed->m_strName;
		POS posInner = pSclCtrlGsIn->GetHeadPosition();
		while(posInner)
		{
			CSclChGsIn* pChGsIn = (CSclChGsIn*)pSclCtrlGsIn->GetNext(posInner);
			GooseSubendInfo(pChGsIn,strID,strName,strAppID);
		}
	}
	
	CSclCtrlsSmvIn* pSclCtrlsSmvIn = pSclIed->GetSmvIns();
	CString strType = pSclCtrlsSmvIn->m_strName;
	POS posSmvIn = pSclCtrlsSmvIn->GetHeadPosition();
	while(posSmvIn)
	{
		CSclCtrlSmvIn* pSclCtrlSmvIn = (CSclCtrlSmvIn*)pSclCtrlsSmvIn->GetNext(posSmvIn);
		CString strExtName = pSclCtrlSmvIn->iedExtName;	
		strName = FindSclIedName(strExtName);

		strID = pSclIed->m_strID;
		QPair<CString, CString> dataPairSmvIn(strID,strName);
		m_strAppIdSmvIn.append(dataPairSmvIn);


		strAppID.Format(_T("0x%04X"),pSclCtrlSmvIn->m_dwAppID);
		strAppID = _T("SMV ") + strAppID;
		QPair<CString, CString> dataPairSmvIn1(strName,strAppID);
		
		
		if (!m_strRecvAppIdSmv.contains(dataPairSmvIn1))
		{
			m_strRecvAppIdSmv.append(dataPairSmvIn1);
		}

		strID = pSclIed->m_strID + "\n" + pSclIed->m_strName;
		QPair<CString, CString> dataPairSmvIn2(strID,strAppID);
		
		if (!m_strRecvAppIdIedSmv.contains(dataPairSmvIn2))
		{
			m_strRecvAppIdIedSmv.append(dataPairSmvIn2);
		}


		//20231225
		long totalChsTest = 0;
		CString strID = pSclIed->m_strID + "\n" + pSclIed->m_strName;
		POS posInner = pSclCtrlSmvIn->GetHeadPosition();
		while(posInner)
		{
			CSclChSmvIn* pChSmvIn=(CSclChSmvIn*)pSclCtrlSmvIn->GetNext(posInner);
			SMVSubendInfo(pChSmvIn,strID,strName,strAppID);
			totalChsTest++;
		}
	}
}

void QSttSclIedDrawViewWidget::GooseSubendInfo( CSclChGsIn* pChGsIn,CString strID ,CString strName,CString strAppID )
{
	CSclVirtualSubend pVirtualSubend;
	CSclVirtualSubend *pSubend = &pVirtualSubend;

	pSubend->m_strID = strID;
	pSubend->m_strName = strName;
	pSubend->strAppID = strAppID;
	int pos = pChGsIn->m_strID.indexOf("/");
	if (pos != -1)
	{
		pChGsIn->m_strID = pChGsIn->m_strID.mid(pos+1);
	}
	pSubend->strfcdaDesc = pChGsIn->m_strID;
	pSubend->strIndoDesc = pChGsIn->inDODesc;

	pSubend->nInIndex = pChGsIn->inIndex;
	pSubend->nOutIndex = pChGsIn->outIndex+1;

	CString strText = strID + strName + strAppID;
	if (m_GsSubList.contains(strText))
	{
 		QList<CSclVirtualSubend>& subendList = m_GsSubList[strText];
 		subendList.append(pVirtualSubend);
	} 
	else 
	{
		QList<CSclVirtualSubend> subendList;
		subendList.append(pVirtualSubend);
		m_GsSubList.insert(strText, subendList);
	}
}

void QSttSclIedDrawViewWidget::SMVSubendInfo( CSclChSmvIn* pChSmvIn ,CString strID,CString strName,CString strAppID )
{
	CSclVirtualSubend oVirtualSubend;
	CSclVirtualSubend *pSubend = &oVirtualSubend;

	pSubend->m_strID = strID;
	pSubend->m_strName = strName;
	pSubend->strAppID = strAppID;

	int pos = pChSmvIn->m_strID.indexOf("/");
	if (pos != -1)
	{
		pChSmvIn->m_strID = pChSmvIn->m_strID.mid(pos+1);
	}

	pSubend->strfcdaDesc = pChSmvIn->m_strID;
	pSubend->strIndoDesc = pChSmvIn->inDODesc;
	
	pSubend->nInIndex = pChSmvIn->inIndex;
	pSubend->nOutIndex = pChSmvIn->outIndex+1;

	CString strText = strID + strName + strAppID;
	if (m_SmvSubList.contains(strText))
	{
		QList<CSclVirtualSubend>& subendList = m_SmvSubList[strText];
		subendList.append(oVirtualSubend);
	} 
	else 
	{
		QList<CSclVirtualSubend> subendList;
		subendList.append(oVirtualSubend);
		m_SmvSubList.insert(strText, subendList);
	}
}

void QSttSclIedDrawViewWidget::SMVSubInputInfos( CSclChSmvOut* pChSmvOut ,CString strID ,CString strAppID,long nIndex)
{
	CSclVirtualSubend oVirtualSubend;
	CSclVirtualSubend *pSubend = &oVirtualSubend;

	pSubend->m_strName = strID;

	int pos = pChSmvOut->m_strID.indexOf("/");
	if (pos != -1)
	{
		pChSmvOut->m_strID = pChSmvOut->m_strID.mid(pos+1);
	}

	pSubend->m_strID = pChSmvOut->m_strID;
	pSubend->strAppID = strAppID;
	pSubend->strfcdaDesc = pChSmvOut->fcda_desc;
	pSubend->nOutIndex = nIndex+1;;

	CString strText = strID + strAppID;

	if (m_SmvInputLists.contains(strText))
	{
		QList<CSclVirtualSubend>& subendList = m_SmvInputLists[strText];
		subendList.append(oVirtualSubend);
	} 
	else 
	{
		QList<CSclVirtualSubend> subendList;
		subendList.append(oVirtualSubend);
		m_SmvInputLists.insert(strText, subendList);
	}
}

void QSttSclIedDrawViewWidget::GsSubInputInfos( CSclChGsOut* pChGsOut,CString strID ,CString strAppID,long nIndex)
{
	CSclVirtualSubend oVirtualSubend;
	CSclVirtualSubend *pSubend = &oVirtualSubend;

	pSubend->m_strName = strID;
	pSubend->strAppID = strAppID;
	int pos = pChGsOut->m_strID.indexOf("/");
	if (pos != -1)
	{
		pChGsOut->m_strID = pChGsOut->m_strID.mid(pos+1);
	}
	pSubend->m_strID = pChGsOut->m_strID;
	pSubend->strfcdaDesc = pChGsOut->fcda_dodesc;
	pSubend->nOutIndex = nIndex+1;;

	CString strText = strID + strAppID;
	if (m_GsInputLists.contains(strText))
	{
		QList<CSclVirtualSubend>& subendList = m_GsInputLists[strText];
		subendList.append(oVirtualSubend);
	} 
	else 
	{
		QList<CSclVirtualSubend> subendList;
		subendList.append(oVirtualSubend);
		m_GsInputLists.insert(strText, subendList);
	}
}

void QSttSclIedDrawViewWidget::Release()
{
	if (m_pCustomRect != NULL)
	{
		delete m_pCustomRect;
		m_pCustomRect = NULL;
	}

	for (int i = 0; i< m_pSmvOutBlockRect.size();i++)
	{
		delete m_pSmvOutBlockRect[i];
		m_pSmvOutBlockRect[i] = NULL;
	}
	m_pSmvOutBlockRect.removeAll(NULL);

	for (int i = 0; i< m_pSmvInBlockRect.size();i++)
	{
		delete m_pSmvInBlockRect[i];
		m_pSmvInBlockRect[i] = NULL;
	}
	m_pSmvInBlockRect.removeAll(NULL);

	for (int i = 0; i< m_pGooseInBlockRect.size();i++)
	{
		delete m_pGooseInBlockRect[i];
		m_pGooseInBlockRect[i] = NULL;
	}
	m_pGooseInBlockRect.removeAll(NULL);

	for (int i = 0; i< m_pGooseoutBlockRect.size();i++)
	{
		delete m_pGooseoutBlockRect[i];
		m_pGooseoutBlockRect[i] = NULL;
	}
	m_pGooseoutBlockRect.removeAll(NULL);

	for (int i = 0; i< m_pInputLeftRect.size();i++)
	{
		delete m_pInputLeftRect[i];
		m_pInputLeftRect[i] = NULL;
	}
	m_pInputLeftRect.removeAll(NULL);

	for (int i = 0; i< m_pInputRightRect.size();i++)
	{
		delete m_pInputRightRect[i];
		m_pInputRightRect[i] = NULL;
	}
	m_pInputRightRect.removeAll(NULL);

	for (int i = 0; i< m_pArrowLine.size();i++)
	{
		delete m_pArrowLine[i];
		m_pArrowLine[i] = NULL;
	}
	m_pArrowLine.removeAll(NULL);

	for (int i = 0; i< m_pReceiveArrowLine.size();i++)
	{
		delete m_pReceiveArrowLine[i];
		m_pReceiveArrowLine[i] = NULL;
	}
	m_pReceiveArrowLine.removeAll(NULL);

	for (int i = 0; i< m_pReceiveRect.size();i++)
	{
		delete m_pReceiveRect[i];
		m_pReceiveRect[i] = NULL;
	}
	m_pReceiveRect.removeAll(NULL);
}

void QSttSclIedDrawViewWidget::ReleaseList()
{
 	m_strAppIdGsOut.clear();
 	m_strAppIdGsIn.clear();
 	m_strAppIdSmvOut.clear();
 	m_strAppIdSmvIn.clear();
 	m_strRecvAppIdIedGs.clear();
 	m_strRecvAppIdIedSmv.clear();
 	m_strRecvAppIdGs.clear();
 	m_strRecvAppIdSmv.clear();
	m_SmvSubList.clear();
	m_GsSubList.clear();
	m_strNameList.clear();
 	m_SmvInputLists.clear();
 	m_GsInputLists.clear();
}


void QSttSclIedDrawViewWidget::OutPutDataPairs( CSclIed *pSclIed,const QList<QPair<CString, CString> >& dataPairs, QList<QSttCustomRect*>& blockRects, int& height )
{
	CString strID = pSclIed->m_strID + "\n" + pSclIed->m_strName;
	for (int nIndex = 0; nIndex < dataPairs.size(); ++nIndex)
	{
		QPair<CString, CString> dataPair = dataPairs[nIndex];
		if (dataPair.first == strID)
		{
			CString strName = dataPair.second;
			QSttCustomRect *pBlockRect = new QSttCustomRect(QPointF(420, height), 130, 40, strName, NULL);
			if (strName.Find(_T("SMV")) >= 0) 
			{	
				pBlockRect->setFillColor(QColor(250, 167, 243));
			} 
			else 
			{
				pBlockRect->setFillColor(QColor(153, 204, 255));
			}
			blockRects.append(pBlockRect);
			height = height + 50;

			QPair<CString, CString> dataPairOut(strID,strName);
			//CompareGoose(dataPairOut);
			//CompareSmv(dataPairOut);
		}
	}
}

void QSttSclIedDrawViewWidget::CompareSmv( QPair<CString, CString>& dataPairs )
{
	CString strName;
	for (int nIndex = 0; nIndex < m_strRecvAppIdSmv.size(); ++nIndex)
	{
		QPair<CString, CString> dataPair = m_strRecvAppIdSmv[nIndex];

		if (dataPairs.first == dataPair.first && dataPairs.second == dataPair.second)
		{
			for (int i =0 ; i < m_strRecvAppIdIedSmv.size() ; ++i)
			{
				CString str = m_strRecvAppIdIedSmv.at(i).second;
				if (str  == dataPairs.second)
				{
					strName = m_strRecvAppIdIedSmv.at(i).first; 
					
					QSttCustomRect *pRect = new QSttCustomRect(QPointF(-50, m_nHeightLeft), 150, 70, strName, NULL);
					pRect->setFillColor(QColor(229,242,196));
					pRect->setText(strName);
					m_pInputLeftRect.append(pRect);
					m_pReceiveInputRect.append(pRect);

					//CString strText;
					//xlang_GetLangStrByFile(strText,"saccept");
					QSttCustomRect *pReceiveRect = new QSttCustomRect(QPointF(100, m_nHeightLeft+15), 130, 40, g_sLangTxt_Native_Accept, NULL);
					pReceiveRect->setFillColor(QColor(255, 255, 255));
					pReceiveRect->setLineStyle(Qt::DashLine);
					m_pReceiveRect.append(pReceiveRect);

					QSttCustomRect* pFoundRect = NULL;
					for (int i = 0; i < m_pSmvOutBlockRect.size(); ++i) 
					{
						QSttCustomRect* pRect = m_pSmvOutBlockRect.at(i);
						if (pRect->getText() == dataPairs.second) 
						{
							pFoundRect = pRect;

							QPointF start = pFoundRect->getLeftCenter();
							QPointF end = pReceiveRect->getRightCenter();
							QSttCustomArrowLine *pArrow = new QSttCustomArrowLine(start,end,NULL);
							pArrow->setLineColor(QColor(238, 187, 107));
							pArrow->setHoverColor(QColor(102, 255, 51));
							m_pReceiveArrowLine.append(pArrow);
							m_pReceiveBlockRect.append(pFoundRect);
						}
					}

					m_nHeightLeft = m_nHeightLeft + 90;
				}
			}
		}
	}
}

void QSttSclIedDrawViewWidget::CompareGoose( QPair<CString, CString>& dataPairs)
{
	CString strName;

	for (int nIndex = 0; nIndex < m_strRecvAppIdGs.size(); ++nIndex)
	{
		QPair<CString, CString> dataPair = m_strRecvAppIdGs[nIndex];

		if (dataPairs.first == dataPair.first && dataPairs.second == dataPair.second)
		{
			for (int i =0 ; i < m_strRecvAppIdIedGs.size() ; ++i)
			{
				CString str = m_strRecvAppIdIedGs.at(i).second;
				if (str  == dataPairs.second)
				{
					 strName = m_strRecvAppIdIedGs.at(i).first; 

					 QSttCustomRect *pRect = new QSttCustomRect(QPointF(900, m_nHeightRight), 150, 70, strName, NULL);
					 pRect->setFillColor(QColor(229,242,196));
					 pRect->setText(strName);
					 m_pInputRightRect.append(pRect);
					 m_pReceiveInputRect.append(pRect);

					 //CString strText;
					 //xlang_GetLangStrByFile(strText,"saccept");
					 QSttCustomRect *pReceiveRect = new QSttCustomRect(QPointF(770, m_nHeightRight+15), 130, 40, g_sLangTxt_Native_Accept, NULL);
					 pReceiveRect->setFillColor(QColor(255, 255, 255));
					 pReceiveRect->setLineStyle(Qt::DashLine);
					 m_pReceiveRect.append(pReceiveRect);

					 QSttCustomRect* pFoundRect = NULL;
					 for (int i = 0; i < m_pGooseoutBlockRect.size(); ++i) 
					 {
						 QSttCustomRect* pRect = m_pGooseoutBlockRect.at(i);
						 if (pRect->getText() == dataPairs.second) 
						 {
							 pFoundRect = pRect;

							 QPointF start = pFoundRect->getRightCenter();
							 QPointF end = pReceiveRect->getLeftCenter();
							 QSttCustomArrowLine *pArrow = new QSttCustomArrowLine(start,end,NULL);
							 pArrow->setLineColor(QColor(238, 187, 107));
							 pArrow->setHoverColor(QColor(102, 255, 51));
							 m_pReceiveArrowLine.append(pArrow);
							 m_pReceiveBlockRect.append(pFoundRect);
						 }
					 }

					 m_nHeightRight = m_nHeightRight + 90;
				}
			}
		}
	}
}


void QSttSclIedDrawViewWidget::slot_Subend()
{
	QObject* senderObject = sender(); // 获取发送信号的对象
	bool found = false; // 判断是否找到对应的 key

	CString  BlockText;
	long nType;
    QMap<CString, QList<CSclVirtualSubend> > pSubList;
	QList<CSclVirtualSubend> subendList;
	QMap<CString, QList<CSclVirtualSubend> > pInputLists;
	QList<CSclVirtualSubend> pInputList;
	for (int i = 0; i < m_pArrowLine.size(); ++i)
	{
		if (m_pArrowLine[i] == senderObject)
		{
			QSttCustomRect* connectedRect = m_pCustomRect;

			if (connectedRect)
			{
				if (m_pInputBlockRect[i]->getText().contains("SMV"))
				{
					pSubList = m_SmvSubList;
					pInputLists = m_SmvInputLists;
				}
				else if (m_pInputBlockRect[i]->getText().contains("GOOSE"))
				{
					pSubList = m_GsSubList;
					pInputLists = m_GsInputLists;
				}
				 
				CString rectText = m_pCustomRect->getText() + m_pInputRect[i]->getText() + m_pInputBlockRect[i]->getText();

                QMap<CString, QList<CSclVirtualSubend> >::const_iterator it;

				for (it = pSubList.constBegin(); it != pSubList.constEnd(); ++it)
				{
					if (it.key() == rectText)
					{
						subendList = it.value();
						nType = 0;
						found = true; 
						break;
					}
				}
			}

			CString strText = m_pInputRect[i]->getText() + m_pInputBlockRect[i]->getText();
			QMap<CString, QList<CSclVirtualSubend> >::const_iterator it1;
			for (it1 = pInputLists.constBegin(); it1 != pInputLists.constEnd(); ++it1)
			{
				if (it1.key() == strText)
				{
					pInputList.append(it1.value());
					nType = 0;
					found = true; 
				}
			}
		}
	}

	CString strReceive;
    QMap<CString, QList<CSclVirtualSubend> >::const_iterator itetor;
	for (int i = 0; i < m_pReceiveArrowLine.size(); ++i)
	{
		if (m_pReceiveArrowLine[i] == senderObject)
		{
			strReceive = m_pReceiveInputRect[i]->getText();
			CString str = m_pReceiveBlockRect[i]->getText();
			str = strReceive + m_pCustomRect->getText() + str;

			if (m_pReceiveBlockRect[i]->getText().contains("SMV"))
			{
				pSubList = m_SmvSubList;
				pInputLists = m_SmvInputLists;
			}
			else if (m_pReceiveBlockRect[i]->getText().contains("GOOSE"))
			{
				pSubList = m_GsSubList;
				pInputLists = m_GsInputLists;
			}

			for (itetor = pSubList.constBegin(); itetor != pSubList.constEnd(); ++itetor)
			{
				if (itetor.key() == str)
				{
					subendList = itetor.value();
					nType = 1;
					found = true;
					break;
				}
			}

			QMap<CString, QList<CSclVirtualSubend> >::const_iterator itetor1;
			CString strText =  m_pCustomRect->getText()+ m_pReceiveBlockRect[i]->getText();
			for (itetor1 = pInputLists.constBegin(); itetor1 != pInputLists.constEnd(); ++itetor1)
			{
				if (itetor1.key() == strText)
				{
					pInputList.append(itetor1.value());
					nType = 1;
					found = true; 
				}
			}
		}
	}

	if (found)
	{
		QSttSclIedLineDialog pSttSclLineDialog(&subendList,&pInputList,nType); // 根据索引获取对应箭头的数据
		pSttSclLineDialog.exec();
	}
}

void QSttSclIedDrawViewWidget::resizeEvent( QResizeEvent * event )
{
	QWidget::resizeEvent(event);
#ifdef _PSX_QT_LINUX_
	QSize windowSize = event->size();
	// 设置 QGraphicsView 的大小为窗口大小
	m_pGraphicsView->setGeometry(0, 0, windowSize.width(), windowSize.height());
	qreal scaleFactor = 0.8; // 缩放因子
	m_pGraphicsView->scale(scaleFactor, scaleFactor);
#endif
}

CString QSttSclIedDrawViewWidget::FindSclIedName(CString search)
{
	for(int i=0;i < m_strNameList.size();i++)
 	{
		CString idIfoName = m_strNameList.at(i);
		int pos = idIfoName.Find(_T("\n"));
		if (pos != -1)
		{
			idIfoName = idIfoName.left(pos);

			if (idIfoName == search)
			{
				return m_strNameList.at(i);
			}
		}
 	}
 
 	return _T("");
}

void QSttSclIedDrawViewWidget::mousePressEvent( QMouseEvent* event )
{
#ifdef _PSX_QT_LINUX_
	if (event->button() == Qt::LeftButton) 
	{
		// 在这里进行判断点击的箭头线
		for (int i = 0; i < m_pArrowLine.size(); ++i) 
		{
			QSttCustomArrowLine* arrowLine = dynamic_cast<QSttCustomArrowLine*>(m_pArrowLine[i]); 
			if(arrowLine)
			{
			// 判断点击位置是否在箭头线的附近
				arrowLine->bClicked(m_pGraphicsView->m_lastScenePos);
			}
		}

		for (int i = 0; i < m_pReceiveArrowLine.size(); ++i) 
		{
			QSttCustomArrowLine* pReceiveArrowLine = dynamic_cast<QSttCustomArrowLine*>(m_pReceiveArrowLine[i]); 

			if(pReceiveArrowLine)
			{
				// 判断点击位置是否在箭头线的附近
				pReceiveArrowLine->bClicked(m_pGraphicsView->m_lastScenePos);
			}
		}
	}
#endif
	QWidget::mousePressEvent(event); // 保留原始的点击事件处理
}



