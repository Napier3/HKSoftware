#include "qsmvpacketanalysistreeview.h"
#include "../../../SVPacketDealMngr.h"
#include "../../../QFpgaThreadMngr.h"
#include "../../../ui/SMVSniffer/qsmvsnifferchildcontainerdlg.h"
QSMVPacketAnalysisTreeView::QSMVPacketAnalysisTreeView(QWidget *parent) :
	QTreeView(parent)
{
	m_model = NULL;
	InitPara();

	QString styleThree = "QTreeView{color:white ;}";
	setStyleSheet(styleThree);
	setGeometry(0,TOPHIGHT_XXY,TOTALWIDTH,TOTALHIGHT-TOPHIGHT_XXY-FKEYWIDTH);

	InitTreeMode();
}

void QSMVPacketAnalysisTreeView::InitTreeMode()
{
	QSVPacketDealMngr* pDataMngr = QSVPacketDealMngr::g_pSVPacketDealMngr;
	if(pDataMngr->m_vPackageAnalysis.size() <= 0)
	{
		return;
	}
	if(m_model != NULL)
	{
		delete m_model;
	}

	m_model = new TreeModel(pDataMngr->m_vPackageAnalysis);
	setModel(m_model);

	setColumnWidth (0,200 );
	setColumnWidth (1,300 );
	setColumnWidth (2,TOTALWIDTH-800 );
	setColumnWidth (3,300 );

	setEditTriggers(QTreeView::NoEditTriggers);			//单元格不能编辑
	setSelectionBehavior(QTreeView::SelectRows);			//一次选中整行
	setSelectionMode(QTreeView::SingleSelection);        //单选，配合上面的整行就是一次选单行
	setColumnHidden(4,true);
	setColumnHidden(5,true);
	expandAll();
}

void QSMVPacketAnalysisTreeView::Updatedata()
{
	InitTreeMode();
}

void QSMVPacketAnalysisTreeView::showEvent(QShowEvent *)
{
	QSVPacketDealMngr* pDataMngr = QSVPacketDealMngr::g_pSVPacketDealMngr;
	if(pDataMngr->m_nSMVorFT3 == 0)
	{
		QFpgaThreadMngr::g_pFpgaThreadMngr->startSVPcapCompareThead();
	}
	else
	{
 //       pTestControl->setMode(DealDataThreadMode_CRC_RawDataToFFT);
	}
}
void QSMVPacketAnalysisTreeView::hideEvent(QHideEvent *)
{
	QFpgaThreadMngr::g_pFpgaThreadMngr->stopThead();
}

void QSMVPacketAnalysisTreeView::mousePressEvent( QMouseEvent * event )
{
	QTreeView::mousePressEvent(event);

	if (event->button() != Qt::LeftButton)
		return;

	QModelIndex Index = currentIndex();
	if(Index.isValid())
	{
		m_rowHeight = rowHeight(Index);
	}

	m_TotalRow = GetTotalRowCount();
	m_lastPoint = event->pos();
	m_ptPressed = event->globalPos();
	m_mousePressing = true;

	m_bMove = false;
}

void QSMVPacketAnalysisTreeView::mouseMoveEvent(QMouseEvent *event)
{
//	QTreeView::mouseMoveEvent(event);

	QPoint pt = event->globalPos();
	if(abs(pt.ry() - m_ptPressed.ry())>10)
	{
		m_bMove = true;
	}

	if ((event->buttons() & Qt::LeftButton) && m_mousePressing)
	{
		m_scribbling = true;
		m_currentPoint = event->pos();
		UpdateScroll();
	}
}

void QSMVPacketAnalysisTreeView::mouseReleaseEvent( QMouseEvent * event )
{
	if (m_bMove)
	{
		if (event->button() == Qt::LeftButton && m_scribbling && m_mousePressing)
		{
			m_currentPoint = event->pos();
			UpdateScroll();
			m_scribbling = false;
		}
	}
	else
	{

	}

	m_mousePressing = false;
	m_scribbling = false;
}
//按键事件处理
void QSMVPacketAnalysisTreeView::keyPressEvent(QKeyEvent *e)
{
    switch (e->key() )
    {
    case Qt::Key_F1:
        {
            ((QSMVSnifferChildContainerDlg*)parentWidget()->parentWidget())->clickF1();
        }
        break;
    case Qt::Key_F2:
        {
            ((QSMVSnifferChildContainerDlg*)parentWidget()->parentWidget())->clickF2();
        }
        break;
    case Qt::Key_F3:
        {
            ((QSMVSnifferChildContainerDlg*)parentWidget()->parentWidget())->clickF3();
        }
        break;
    case Qt::Key_F4:
        {
            ((QSMVSnifferChildContainerDlg*)parentWidget()->parentWidget())->clickF4();
        }
        break;
    case Qt::Key_Home:
        {
            homeActive(this);
        }
        break;
    case Qt::Key_Escape:
        {
            ((QSMVSnifferChildContainerDlg*)parentWidget()->parentWidget())->OnKeyEscape();
        }
        break;
    default:
        QTreeView::keyPressEvent(e);
        break;
    }
}
void QSMVPacketAnalysisTreeView::UpdateScroll()
{
	if (m_scribbling)
	{
		//setEnabled(false);
	}
	if (m_TotalRow <= 0)
	{
		return;
	}
	m_scrDis = m_currentPoint.y() - m_lastPoint.y();
	if (abs(m_scrDis) < abs(m_rowHeight))
	{
		return;
	}

	m_diff = (int)m_scrDis/m_rowHeight;
	int v = verticalScrollBar()->value();

	verticalScrollBar()->setValue(v- m_diff);
	m_lastPoint.setY(m_currentPoint.y());
}

void QSMVPacketAnalysisTreeView::InitPara()
{
	m_TotalRow = 0;
	m_scribbling = false;
	m_mousePressing = false;
	m_scrDis = 0;       //滑动距离
	m_diff = 0;
	m_rowHeight = TABLEHEIGHT;
}

int QSMVPacketAnalysisTreeView::GetTotalRowCount()
{
	QSVPacketDealMngr* pDataMngr = QSVPacketDealMngr::g_pSVPacketDealMngr;
	return pDataMngr->m_vPackageAnalysis.size();
}

int QSMVPacketAnalysisTreeView::GetTotalChildCount(QModelIndex parent)
{
	int nChildCnt = m_model->rowCount(parent);
	if(nChildCnt == 0)
		return 0;

	QModelIndex tmpIndex;
	int nCnt = nChildCnt;
	for(int i=0; i<nCnt; i++)
	{
		tmpIndex = m_model->index(i,0,parent);
		nChildCnt += GetTotalChildCount(tmpIndex);
	}
	return nChildCnt;
}

int QSMVPacketAnalysisTreeView::GetTotalChildCount(QModelIndex parent, QModelIndex toChild, bool &bReach)
{
	if(parent == toChild)
	{
		bReach = true;
		return 0;
	}
	bReach = false;

	int nChildCnt = m_model->rowCount(parent);
	if(nChildCnt == 0)
		return 0;

	QModelIndex tmpIndex;
	int nCnt = 0;
	for(int i=0; i<nChildCnt; i++)
	{
		nCnt++;
		tmpIndex = m_model->index(i,0,parent);
		nCnt += GetTotalChildCount(tmpIndex,toChild,bReach);

		if(bReach)
		{
			break;
		}
	}
	return nCnt;
}

int QSMVPacketAnalysisTreeView::GetCurrentRow()
{
	QModelIndex Index = currentIndex();
	QModelIndex ParentIndex,preParentIndex;

	if(!Index.isValid())
		return 0;

	Index = Index.sibling(Index.row(),0);
	m_rowHeight = rowHeight(Index);
	qDebug()<<"currentIndex:"<<Index.row()<<Index.column()<<m_rowHeight;

	int nCurRow = 0;
	bool bReach = false;

	ParentIndex = Index;
	while(ParentIndex.isValid())
	{
		preParentIndex = ParentIndex;
		ParentIndex = m_model->parent(ParentIndex);
	}

	nCurRow = GetTotalChildCount(preParentIndex,Index,bReach);
	if(!bReach)
	{
		return nCurRow;
	}

	QSVPacketDealMngr* pDataMngr = QSVPacketDealMngr::g_pSVPacketDealMngr;
	QVariant var = m_model->data(preParentIndex);
	CElementPos elem;
	for (int i=0;i<pDataMngr->m_vPackageAnalysis.size();i++)
	{
		elem = pDataMngr->m_vPackageAnalysis.at(i);
		if (elem.m_Name == var)
		{
			nCurRow += i;
			break;
		}
	}

	return nCurRow;
}
