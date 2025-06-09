#include "SwingSysDiagramWidget.h"
#include "ui_SwingSysDiagramWidget.h"

extern STT_SystemParas g_oSystemParas;
extern CFont *g_pSttGlobalFont;

QSwingSysDiagramWidget::QSwingSysDiagramWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QSwingSysDiagramWidget)
{
    ui->setupUi(this);
	m_pCurTest = NULL;
    InitUI();
    SetDatas();
}

QSwingSysDiagramWidget::~QSwingSysDiagramWidget()
{
    delete ui;
}

void QSwingSysDiagramWidget::InitUI()
{
	this->setStyleSheet("background-color: white;");

	CString strPngPath;
#ifdef _PSX_QT_WINDOWS_
	strPngPath = _P_GetResourcePath();

	strPngPath = strPngPath + _T("SwingSysDiag.png");
#else
	strPngPath =  ":/ctrls/images/SwingSysDiag.png";
#endif

	QPixmap pixmap(strPngPath);
	if(!pixmap.isNull())
	{
		pixmap = pixmap.scaled(QSize(this->width()-10,this->height()), Qt::KeepAspectRatio, Qt::SmoothTransformation);
		ui->m_labDiagram->setPixmap(pixmap);
		ui->m_labDiagram->show();
	}

    ui->m_tableWidget->setFixedSize(302,162);
    ui->m_tableWidget->setColumnWidth(0, 150);
    ui->m_tableWidget->setColumnWidth(1, 150);
//	ui->m_tableWidget->setStyleSheet("QTableWidget { background-color: lightblue; }"
//		"QHeaderView::section { background-color: lightblue; }");

	ui->m_tableWidget->setSelectionMode(QAbstractItemView::NoSelection); 

	for(int i = 0; i<4; i++)
	{
		ui->m_tableWidget->setRowHeight(i, 40);
	}

}

void QSwingSysDiagramWidget::SearchData()
{
	float m_fVNom = g_oSystemParas.m_fVNom/sqrt((float)3);
	Complex p1,p2;
	Complex pVs=p1.polar(m_fVNom,0.0);
	m_dIoscmax=0;
	m_dVoscmin=2.0*m_fVNom;
	m_dZoscmin=999999;
	m_dPhioscmax=0.0;
	for(int i=0;i<720;i++)
	{
		Complex pI=(p1.polar(m_fVNom*m_pCurTest->m_oSwingParas.m_fRate,i*360.0/720.0)-pVs)/(m_oZs+m_oXd+m_oZt);
		Complex pV=pI*(m_oZs+m_oZt)+pVs;
		Complex pZ=pV/pI;
		if(p1.norm(pI)>m_dIoscmax)
		{
			m_dIoscmax=p1.norm(pI);
			m_dPhioscmax=i*360.0/720.0;
			//m_dIPhi=p1.arg(pI);
		}
		if(p1.norm(pV)<m_dVoscmin)
		{
			m_dVoscmin=p1.norm(pV);
			//m_fVPhi=p1.arg(pV);
		}
		if(p1.norm(pZ)<m_dZoscmin)
			m_dZoscmin=p1.norm(pZ);
	}
	
}
void QSwingSysDiagramWidget::SetDatas()
{
	if(NULL != m_pCurTest)
	{
		m_oZs.SetParameter_ByAmpAng(m_pCurTest->m_oSwingParas.m_fImpSys, m_pCurTest->m_oSwingParas.m_fImpSysPh);
		m_oZt.SetParameter_ByAmpAng(m_pCurTest->m_oSwingParas.m_fImpTf, m_pCurTest->m_oSwingParas.m_fImpTfPh);
		m_oXd.SetParameter_ByAmpAng(m_pCurTest->m_oSwingParas.m_fImpTs, 90);

		SearchData();
	}

    QTableWidgetItem *pItem = new QTableWidgetItem(QString("%1V").arg(QString::number(m_dVoscmin, 'f', 3)));
    pItem->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
    pItem->setFont(*g_pSttGlobalFont);
    ui->m_tableWidget->setItem(0, 1, pItem);

    pItem = new QTableWidgetItem(QString("%1A").arg(QString::number(m_dIoscmax, 'f', 3)));
    pItem->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
    pItem->setFont(*g_pSttGlobalFont);
    ui->m_tableWidget->setItem(1, 1, pItem);

    pItem = new QTableWidgetItem(QString("%1%2").arg(QString::number(m_dZoscmin, 'f', 3), QString::fromLocal8Bit("Ω")));
    pItem->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
    pItem->setFont(*g_pSttGlobalFont);
    ui->m_tableWidget->setItem(2, 1, pItem);

    pItem = new QTableWidgetItem(QString("%1%2").arg(QString::number(m_dPhioscmax, 'f', 3), QString::fromLocal8Bit("°")));
    pItem->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
    pItem->setFont(*g_pSttGlobalFont);
    ui->m_tableWidget->setItem(3, 1, pItem);}
