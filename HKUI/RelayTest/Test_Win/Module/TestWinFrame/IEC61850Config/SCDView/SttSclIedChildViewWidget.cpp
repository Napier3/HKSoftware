#include "SttSclIedChildViewWidget.h"
#include <qwt_plot_renderer.h>
#include "../Module/TestWinFrame/ReportView/XLangResource_PowerTestWin.h"
	
//QScrollArea

QSttSclIedChildViewWidget::QSttSclIedChildViewWidget(QWidget *parent,QWidget *root)
: QWidget(parent),m_coordHeight(520),m_coordWidth(930),m_minCoordHeight(610),m_pRoot(root)
{
	//QScroller tes;
	////ptest->scrollArea;
	//QScrollBar* scrBarTem=temscrollArea->verticalScrollBar();
//	InitScrollCtrl(scrBarTem);

	InitUI();

	QFont font = m_plot->axisFont(QwtPlot::yLeft);
	m_pointFWidth = font.pointSizeF();
	m_plot->setAxisFont(QwtPlot::xBottom, font);
}

QSttSclIedChildViewWidget::~QSttSclIedChildViewWidget()
{
	Clear();
}

//---------------------
void QSttSclIedChildViewWidget::InitScrollData(QScrollBar* pScollBar)
{
#ifdef _PSX_QT_LINUX_
	InitScrollCtrl(pScollBar);
#endif

}

void QSttSclIedChildViewWidget::mousePressEvent(QMouseEvent *ev)
{
#ifdef _PSX_QT_LINUX_
	mousePressEvent_ScrollBase(ev);
#endif
	QWidget::mousePressEvent( ev );
}


void QSttSclIedChildViewWidget::mouseMoveEvent(QMouseEvent *ev)
{
#ifdef _PSX_QT_LINUX_
	if (!mouseMoveEvent_ScrollBase(ev))
	{
		//emit sig_MouseMoveGbTree(ev);
		return;
	}
#endif
	QWidget::mouseMoveEvent( ev );
}

void QSttSclIedChildViewWidget::mouseReleaseEvent(QMouseEvent *ev)
{
#ifdef _PSX_QT_LINUX_
	if (!mouseReleaseEvent_ScrollBase(ev))
	{
		return;
	}
#endif
	QWidget::mouseReleaseEvent( ev );
}
/////----------------------------------

bool isExistInRecList(_CONNECT_PUB_INFO* conPubInfo,QList<_CONNECT_PUB_INFO> recPubList)
{
	for (int i=0;i<recPubList.size();i++)
	{
		_CONNECT_PUB_INFO info=recPubList.at(i);
		if ((info.index_IED==conPubInfo->index_IED)&&(info.index_Rec==conPubInfo->index_Rec))
		{
			return true;
		}
	}
	return false;
}

void lastFillGseRecInexList()
{
	int sizeTotal=g_oTotalIEDList.size();
	for(int id=0;id<sizeTotal;id++)
	{

		_IED_INFO *pOutInfo =  (_IED_INFO*)(g_oTotalIEDList.at(id));
		int gseSize=pOutInfo->GSEList.size(); //.push_back(*pub);
		for (int sendgseId=0;sendgseId<gseSize;sendgseId++)
		{
			_GSE_INFO*psingGSe=(_GSE_INFO*)&(pOutInfo->GSEList.at(sendgseId));
			CString crtAPPIDGse=psingGSe->APPID;
			int pubsize=psingGSe->pubList.size();
			for (int sendPubID=0;sendPubID<pubsize;sendPubID++)
			{
				_PUB_REC_INFO* pSendckfcda=(_PUB_REC_INFO*)&(psingGSe->pubList.at(sendPubID));
				///////////----
				for (int jdx=0;jdx<sizeTotal;jdx++)
				{
					_IED_INFO *innerinfo=g_oTotalIEDList.at(jdx);
					if (innerinfo->name==pOutInfo->name)
					{
						continue;
					}
					_IED_INFO *pSubTem =  (_IED_INFO*)(g_oTotalIEDList.at(jdx));
					int lstgosSize=pSubTem->GOSubList.size();
					for (int gsSubId=0;gsSubId<lstgosSize;gsSubId++)
					{
						_SUB_REC_INFO* subRecInfo=(_SUB_REC_INFO*)&pSubTem->GOSubList.at(gsSubId);
						QString testName=subRecInfo->sub_IED_name+subRecInfo->sub_ref;
						//(crtAPPIDGse==subRec.ExtMineOutAppid
						//if ((crtAPPIDGse.length()>0)&&(subRecInfo->ExtMineOutAppid.length()>0))
						//{
						//	//if (crtAPPIDGse!=subRecInfo->ExtMineOutAppid)
						//	{
						//		//continue;
						//	}
						//}
						if ((subRecInfo->sub_IED_name==pOutInfo->name)&&
							((subRecInfo->sub_ref==pSendckfcda->ref)||(testName==pSendckfcda->ref))
							
							)
						{
							//-------
							if (crtAPPIDGse!=subRecInfo->ExtMineOutAppid)
							{
								continue;
							}
							///---------------------
							//更新信息
							subRecInfo->index_GSE_SMV=sendgseId; //sendgseId
							//subRecInfo->index_Rec=index_pubRec;
							subRecInfo->index_Rec=sendPubID;
							//---------
							_CONNECT_PUB_INFO* conPubInfo=new _CONNECT_PUB_INFO;
							////conPubInfo->index_IED=subRec.index_IED;  //findCrtIedIdex(innerinfo.name);  //jieshou
							conPubInfo->index_IED=Global_FindSclIedIndex(pSubTem->name); 
							//conPubInfo->index_Rec=subRec.index_Rec; gsId
							conPubInfo->index_Rec=gsSubId; 
							if (!isExistInRecList(conPubInfo,pSendckfcda->recPubList))
							{
								pSendckfcda->recPubList.push_back(*conPubInfo);
							}
							
						}
					}


				}
			}
		}

	}

}

void lastFillSmvRecInexList()
{
	int sizeTotal=g_oTotalIEDList.size();
	for(int id=0;id<sizeTotal;id++)
	{
		_IED_INFO *pOutInfo =  (_IED_INFO*)(g_oTotalIEDList.at(id));
		int smvSize=pOutInfo->SMVList.size(); //.push_back(*pub);
		for (int sendsmvId=0;sendsmvId<smvSize;sendsmvId++)
		{
			_SMV_INFO*psingSmv=(_SMV_INFO*)&(pOutInfo->SMVList.at(sendsmvId));
			int pubsize=psingSmv->pubList.size();
			for (int sendPubID=0;sendPubID<pubsize;sendPubID++)
			{
				_PUB_REC_INFO* pSendckfcda=(_PUB_REC_INFO*)&(psingSmv->pubList.at(sendPubID));
				///////////----
				for (int jdx=0;jdx<sizeTotal;jdx++)
				{
					_IED_INFO *innerRecvinfo=g_oTotalIEDList.at(jdx);
					if (innerRecvinfo->name==pOutInfo->name)
					{
						continue;
					}
					_IED_INFO *pRevTem =  (_IED_INFO*)(g_oTotalIEDList.at(jdx));
					int lstsmvSubSize=pRevTem->SVSubList.size();
					for (int gsId=0;gsId<lstsmvSubSize;gsId++)
					{
						_SUB_REC_INFO* subRecInfo=(_SUB_REC_INFO*)&pRevTem->SVSubList.at(gsId);
						QString testName=subRecInfo->sub_IED_name+subRecInfo->sub_ref;
						if ((subRecInfo->sub_IED_name==pOutInfo->name)&&
							((subRecInfo->sub_ref==pSendckfcda->ref)||(testName==pSendckfcda->ref))
							)
						{
							///---------------------
							//更新信息
							////subRecInfo->index_IED=index_pubIED;
							subRecInfo->index_GSE_SMV=sendsmvId;
							subRecInfo->index_Rec=sendPubID;
							//---------
							_CONNECT_PUB_INFO* conPubInfo=new _CONNECT_PUB_INFO;
							////conPubInfo->index_IED=subRec.index_IED;  //findCrtIedIdex(innerinfo.name);  //jieshou
							conPubInfo->index_IED=Global_FindSclIedIndex(pRevTem->name); 
							//conPubInfo->index_Rec=subRec.index_Rec;
							conPubInfo->index_Rec=gsId;
							if (!isExistInRecList(conPubInfo,pSendckfcda->recPubList))
							{
								pSendckfcda->recPubList.push_back(*conPubInfo);
							}
	
						}
					}


				}
			}
		}

	}

}

void QSttSclIedChildViewWidget::InitData(CSclIed *pSclIed, double &_canvasHeight)
{
	if (NULL==pSclIed)
	{
		return;
	}

	//初始化数据
	Clear();

	int indexTem=Global_FindSclIedIndex(pSclIed->m_strID);
	if (-1==indexTem)
	{
		return;
	}
	int _iIED=indexTem;
	m_data.ied_index = _iIED;

	bool bPos = true;

// 	lastFillGseRecInexList();
// 	lastFillSmvRecInexList();

	//先构造所有的连线
	_IED_INFO *iedInfo = g_oTotalIEDList.at(indexTem);
//	int sizeTest=g_oTotalIEDList.size();

	//Goose Sub
	for(int iBlock = 0; iBlock< iedInfo->GOSubList.size(); iBlock++)
	{
		_SUB_REC_INFO subRec = iedInfo->GOSubList.at(iBlock);

		//查看是否已经存在
		bool isExist = false;
		foreach(Arrow_Struct *preArrowStru, m_data.arrowList)
		{
			//如果前面出现过同一个IED，同一个控制块的，则不需要新建连线
			if (preArrowStru->dat.sub.subIED == subRec.index_IED 
				&& preArrowStru->dat.sub.subBlock == subRec.index_GSE_SMV 
				&& preArrowStru->type == Arrow_Struct::ARROW_GOOSE_SUB)
			{
				isExist = true;
				break;
			}
		}
		if (!isExist)
		{
			//过滤那些订阅找不到的连线
			if(subRec.index_IED == -1 || subRec.index_GSE_SMV == -1)
				continue;

			Arrow_Struct *arrowStru = new Arrow_Struct;
			arrowStru->ied_index = _iIED;
			arrowStru->type = Arrow_Struct::ARROW_GOOSE_SUB;
			arrowStru->dat.sub.subBlock = subRec.index_GSE_SMV;
			arrowStru->dat.sub.subIED = subRec.index_IED;
			m_data.arrowList.append(arrowStru);
		}
	}

	//smv Sub
	for(int iBlock = 0; iBlock< iedInfo->SVSubList.size(); iBlock++)
	{
		_SUB_REC_INFO subRec = iedInfo->SVSubList.at(iBlock);

		//查看是否已经存在
		bool isExist = false;
		foreach(Arrow_Struct *preArrowStru, m_data.arrowList)
		{
			//如果前面出现过同一个IED，同一个控制块的，则不需要新建连线
			if (preArrowStru->dat.sub.subIED == subRec.index_IED 
				&& preArrowStru->dat.sub.subBlock == subRec.index_GSE_SMV 
				&& preArrowStru->type == Arrow_Struct::ARROW_SMV_SUB)
			{
				isExist = true;
				break;
			}
		}
		if (!isExist)
		{
			//过滤那些订阅找不到的连线
			if(subRec.index_IED == -1 || subRec.index_GSE_SMV == -1)
				continue;

			Arrow_Struct *arrowStru = new Arrow_Struct;
			arrowStru->ied_index = _iIED;
			arrowStru->type = Arrow_Struct::ARROW_SMV_SUB;
			arrowStru->dat.sub.subBlock = subRec.index_GSE_SMV;
			arrowStru->dat.sub.subIED = subRec.index_IED;
			m_data.arrowList.append(arrowStru);
		}
	}

	for(int iBlock = 0; iBlock< iedInfo->GSEList.size(); iBlock++)
	{
		_GSE_INFO gseInfo = iedInfo->GSEList.at(iBlock);
		//不管有没有连线，都先保存
		Block_Struct blockStru;
		blockStru.block_index = iBlock;
		blockStru.type = Block_Struct::BLOCK_GSE;
		m_data.blockList.append(blockStru);

		//获取当前GSE被哪个IED订阅了
		foreach(_PUB_REC_INFO pubInfo, gseInfo.pubList)
		{
			foreach(_CONNECT_PUB_INFO conInfo, pubInfo.recPubList)
			{
				//查看是否已经存在
				bool isExist = false;
				foreach(Arrow_Struct *preArrowStru, m_data.arrowList)
				{
					//如果前面出现过同一个IED，同一个控制块的索引，且控制块类型相同，则不需要新建连线
					if (preArrowStru->dat.pub.subIED == conInfo.index_IED 
						&& preArrowStru->dat.pub.block == iBlock
						&& preArrowStru->type == Arrow_Struct::ARROW_GSE)
					{
						isExist = true;
						break;
					}
				}

				if (!isExist)
				{
					Arrow_Struct *arrowStru = new Arrow_Struct;
					arrowStru->ied_index = _iIED;
					arrowStru->type = Arrow_Struct::ARROW_GSE;
					arrowStru->dat.pub.block = iBlock;
					arrowStru->dat.pub.subIED = conInfo.index_IED;
					m_data.arrowList.append(arrowStru);
				}
			}
		}
	}
	
	//SMV
	for(int iBlock = 0; iBlock< iedInfo->SMVList.size(); iBlock++)
	{
		_SMV_INFO gseInfo = iedInfo->SMVList.at(iBlock);
		//不管有没有连线，都先保存
		Block_Struct blockStru;
		blockStru.block_index = iBlock;
		blockStru.type = Block_Struct::BLOCK_SMV;
		m_data.blockList.append(blockStru);

		//获取当前GSE被哪个IED订阅了
		foreach(_PUB_REC_INFO pubInfo, gseInfo.pubList)
		{
			foreach(_CONNECT_PUB_INFO conInfo, pubInfo.recPubList)
			{
				//查看是否已经存在
				bool isExist = false;
				foreach(Arrow_Struct *preArrowStru, m_data.arrowList)
				{
					//如果前面出现过同一个IED，同一个控制块的，则不需要新建连线
					if (preArrowStru->dat.pub.subIED == conInfo.index_IED 
						&& preArrowStru->dat.pub.block == iBlock 
						&& preArrowStru->type == Arrow_Struct::ARROW_SMV)
					{
						isExist = true;
						break;
					}
				}

				if (!isExist)
				{
					Arrow_Struct *arrowStru = new Arrow_Struct;
					arrowStru->ied_index = _iIED;
					arrowStru->type = Arrow_Struct::ARROW_SMV;
					arrowStru->dat.pub.block = iBlock;
					arrowStru->dat.pub.subIED = conInfo.index_IED;

					m_data.arrowList.append(arrowStru);
				}
			}
		}
	}

	//遍历连线，看有多少个IED
	foreach (Arrow_Struct *arrowStru, m_data.arrowList)
	{
		//发布类型的控制块，对于smallRect为接收
		if (arrowStru->type == Arrow_Struct::ARROW_GSE 
			|| arrowStru->type == Arrow_Struct::ARROW_SMV)
		{
			bool rectFlag = true; //判断IED是否存在
			for(int iRect = 0; iRect < m_data.smallBlockList.size(); iRect++)
			{
				SmallRect_Struct &smallRectStru = m_data.smallBlockList[iRect];
				if (smallRectStru.ied_index == arrowStru->dat.pub.subIED)
				{
					rectFlag = false;
					bool blockFalg = true; //判断接收控制块是否存在
					for (int iBlock = 0; iBlock<smallRectStru.blockList.size(); iBlock++)
					{
						Block_Struct &blockStru = smallRectStru.blockList[iBlock];
						if (blockStru.type == Block_Struct::BLOCK_SUB)
						{
							//箭头的左右位置，由小矩形的位置决定
							arrowStru->pos = smallRectStru.pos == SmallRect_Struct::POSITION_LEFT ? 
								Arrow_Struct::POSITION_LEFT : Arrow_Struct::POSITION_RIGHT;
							blockStru.arrowList.append(arrowStru);
							blockFalg = false;
							break;
						}
					}
					if (blockFalg)
					{
						//只能是接收类型的控制块
						Block_Struct blockStru;
						blockStru.block_index = -1;
						blockStru.type = Block_Struct::BLOCK_SUB;
						arrowStru->pos = smallRectStru.pos == SmallRect_Struct::POSITION_LEFT ? 
							Arrow_Struct::POSITION_LEFT : Arrow_Struct::POSITION_RIGHT;
						blockStru.arrowList.append(arrowStru);
						smallRectStru.blockList.append(blockStru);
					}
					break;
				}
			}

			if (rectFlag)
			{
				SmallRect_Struct rectStru;
				rectStru.pos = bPos ? SmallRect_Struct::POSITION_LEFT : SmallRect_Struct::POSITION_RIGHT;
				bPos = bPos ? false : true;
				rectStru.ied_index = arrowStru->dat.pub.subIED;
				
				//只能是接收类型的控制块
				Block_Struct blockStru;
				blockStru.block_index = -1;
				blockStru.type = Block_Struct::BLOCK_SUB;
				arrowStru->pos = 
					rectStru.pos == SmallRect_Struct::POSITION_LEFT ? 
					Arrow_Struct::POSITION_LEFT : Arrow_Struct::POSITION_RIGHT;
				blockStru.arrowList.append(arrowStru);
				rectStru.blockList.append(blockStru);

				m_data.smallBlockList.append(rectStru);
			}

			//为控制块添加连线信息
			for (int iBlock = 0; iBlock<m_data.blockList.size(); iBlock++)
			{
				Block_Struct &blockStru = m_data.blockList[iBlock];
				if (blockStru.block_index == arrowStru->dat.pub.block)
				{
					//索引相同，不一定是同一个控制块，还得类型一致
					if(blockStru.type == Block_Struct::BLOCK_GSE 
						&& arrowStru->type == Arrow_Struct::ARROW_GSE)
						blockStru.arrowList.append(arrowStru);

					if(blockStru.type == Block_Struct::BLOCK_SMV 
						&& arrowStru->type == Arrow_Struct::ARROW_SMV)
						blockStru.arrowList.append(arrowStru);
				}
			}
		}
		else
		{
			bool rectFlag = true; //判断IED是否存在
			for(int iRect = 0; iRect < m_data.smallBlockList.size(); iRect++)
			{
				SmallRect_Struct &smallRectStru = m_data.smallBlockList[iRect];
				if (smallRectStru.ied_index == arrowStru->dat.sub.subIED)
				{
					rectFlag = false;
					bool blockFalg = true; //发送控制块，一个控制块一条线
					for (int iBlock = 0; iBlock<smallRectStru.blockList.size(); iBlock++)
					{
						Block_Struct &blockStru = smallRectStru.blockList[iBlock];
						if (blockStru.block_index == arrowStru->dat.sub.subIED)
						{
							if(blockStru.type == Block_Struct::BLOCK_GSE 
								&& arrowStru->type == Arrow_Struct::ARROW_GSE)
								QMessageBox::information(this, /*tr("错误")*/g_sLangTxt_Native_error, /*tr("一个控制块对应多个线条")*/g_sLangTxt_Native_oneToMany);

							if(blockStru.type == Block_Struct::BLOCK_SMV 
								&& arrowStru->type == Arrow_Struct::ARROW_SMV)
								QMessageBox::information(this, /*tr("错误")*/g_sLangTxt_Native_error, /*tr("一个控制块对应多个线条")*/g_sLangTxt_Native_oneToMany);

							break;
						}
					}
					if (blockFalg)
					{
						//只能是接收类型的控制块
						Block_Struct blockStru;
						blockStru.block_index = arrowStru->dat.sub.subBlock;
						blockStru.type = 
							arrowStru->type == Arrow_Struct::ARROW_GOOSE_SUB ? Block_Struct::BLOCK_GSE : Block_Struct::BLOCK_SMV;
						arrowStru->pos = 
							smallRectStru.pos == SmallRect_Struct::POSITION_LEFT ? Arrow_Struct::POSITION_LEFT : Arrow_Struct::POSITION_RIGHT;
						blockStru.arrowList.append(arrowStru);
						smallRectStru.blockList.append(blockStru);
					}
					break;
				}
			}
			if (rectFlag)
			{
				SmallRect_Struct rectStru;
				rectStru.pos = bPos ? SmallRect_Struct::POSITION_LEFT : SmallRect_Struct::POSITION_RIGHT;
				bPos = bPos ? false : true;
				rectStru.ied_index = arrowStru->dat.sub.subIED;

				//只能是发送类型
				Block_Struct blockStru;
				blockStru.block_index = arrowStru->dat.sub.subBlock;
				blockStru.type = 
					arrowStru->type == Arrow_Struct::ARROW_GOOSE_SUB ? Block_Struct::BLOCK_GSE : Block_Struct::BLOCK_SMV;
				arrowStru->pos = 
					rectStru.pos == SmallRect_Struct::POSITION_LEFT ? Arrow_Struct::POSITION_LEFT : Arrow_Struct::POSITION_RIGHT;
				blockStru.arrowList.append(arrowStru);
				rectStru.blockList.append(blockStru);

				m_data.smallBlockList.append(rectStru);
			}
		}
	}

	m_coordHeight = rectMark->InitData();
	m_coordHeight = m_coordHeight > m_minCoordHeight ? m_coordHeight : m_minCoordHeight;
	m_plot->setAxisScale(QwtPlot::yLeft, m_coordHeight, 0);
	m_plot->setAxisScale(QwtPlot::xBottom, 0, m_coordWidth);

	_canvasHeight = m_coordHeight;
	//_canvasWidth = m_coordWidth;

	m_plot->replot();
}

void QSttSclIedChildViewWidget::Clear()
{
	foreach(Block_Struct blockStru, m_data.blockList)
	{
		blockStru.arrowList.clear();
	}
	m_data.blockList.clear();

	foreach(SmallRect_Struct smallRectStru, m_data.smallBlockList)
	{
		foreach(Block_Struct blockStru, smallRectStru.blockList)
		{
			blockStru.arrowList.clear();
		}
		smallRectStru.blockList.clear();
	}
	m_data.smallBlockList.clear();

	foreach(Arrow_Struct *arrowStru, m_data.arrowList)
	{
		delete arrowStru;
	}
	m_data.arrowList.clear();

	QFont font = m_plot->axisFont(QwtPlot::yLeft);
	m_pointFWidth = font.pointSizeF();
	m_plot->setAxisFont(QwtPlot::xBottom, font);
}

void QSttSclIedChildViewWidget::InitUI()
{
	m_plot = new QwtPlot(this);

	//先设定坐标轴的范围
	rectMark = new CRectMark(&m_data,this->m_pRoot);
	rectMark->attach(m_plot);

	m_plot->enableAxis(QwtPlot::yLeft, false);
	m_plot->enableAxis(QwtPlot::xBottom, false);

	QHBoxLayout *hBoxLayout = new QHBoxLayout;
	hBoxLayout->setMargin(0);
	hBoxLayout->addWidget(m_plot);
	setLayout(hBoxLayout);

	// canvas
	QwtPlotCanvas *m_canvas = new QwtPlotCanvas();
	m_canvas->setFocusIndicator( QwtPlotCanvas::CanvasFocusIndicator );
	m_canvas->setFocusPolicy( Qt::StrongFocus );
	m_canvas->setPalette( Qt::white );
	m_canvas->setCursor(QCursor(Qt::ClosedHandCursor));
	m_plot->setCanvas(m_canvas);

	QwtPicker *picker = new QwtPicker(m_canvas);
	picker->setStateMachine(new QwtPickerTrackerMachine);
	picker->setTrackerMode(QwtPicker::AlwaysOff);
	picker->setRubberBand(QwtPicker::NoRubberBand);
	connect(picker, SIGNAL(moved(const QPoint &)), SLOT(OnMoved(const QPoint &)));

	QwtPicker *picker1 = new QwtPicker(m_canvas);
	picker1->setStateMachine(new QwtPickerClickPointMachine);
	picker1->setTrackerMode(QwtPicker::AlwaysOff);
	picker1->setRubberBand(QwtPicker::NoRubberBand);
	connect(picker1, SIGNAL(appended(const QPoint &)), SLOT(OnAppand(const QPoint &)));
}

void QSttSclIedChildViewWidget::OnMoved(const QPoint &pos)
{
	rectMark->Contains(pos);
}

void QSttSclIedChildViewWidget::OnAppand(const QPoint &pos)
{
	int index = rectMark->LeftButtonClicked(pos);
	if (index != -1)
	{
		emit IEDClickedSignal(index);
	}
}

void QSttSclIedChildViewWidget::ZoomIn(float _factor)
{
	QFont font = m_plot->axisFont(QwtPlot::xBottom);
	m_pointFWidth *= _factor;
	font.setPointSizeF(m_pointFWidth);
	m_plot->setAxisFont(QwtPlot::xBottom, font);
}

void QSttSclIedChildViewWidget::ExportPicture(double _width, double _height)
{
	if(m_data.ied_index == -1)
		return;

	QwtPlotRenderer renderer;
	renderer.setDiscardFlag(QwtPlotRenderer::DiscardTitle,true);
	renderer.setDiscardFlag(QwtPlotRenderer::DiscardLegend,true);
	renderer.setDiscardFlag(QwtPlotRenderer::DiscardFooter,true);

	// flags to make the document look like the widget  
	renderer.setDiscardFlag(QwtPlotRenderer::DiscardBackground, true);  
	//renderer.setLayoutFlag(QwtPlotRenderer::KeepFrames, true);

	_IED_INFO *iedInfo = g_oTotalIEDList.at(m_data.ied_index);
	QString fileName = iedInfo->name + "-" + iedInfo->desc;

	if(!renderer.exportTo(m_plot, fileName+".png",QSizeF(_width, _height)))
	{
		QMessageBox::information(this,/*tr("错误")*/g_sLangTxt_Native_error,/*tr("保存失败！\n")*/g_sLangTxt_Native_saveFailed);
	}
}