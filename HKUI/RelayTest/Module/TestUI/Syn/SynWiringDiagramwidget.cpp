#include "SynWiringDiagramWidget.h"
#include "ui_SynWiringDiagramWidget.h"
#include "../../Module/UI/SttTestCntrFrameApi.h"
#include "SttMultiMacroSynParasDefine.h"
#include "../../SttCmd/GuideBook/SttMacroTest.h"
QSynWiringDiagramWidget::QSynWiringDiagramWidget(QWidget *parent) :
    QWidget(parent),
	ui(new Ui::QSynWiringDiagramWidget)
{
	ui->setupUi(this); 

	m_nType = 0;
	connect(this, SIGNAL(sizeChanged()), this, SLOT(slot_UpdateUIPosition()));
	emit sizeChanged();
}

QSynWiringDiagramWidget::~QSynWiringDiagramWidget()
{

    delete ui;
}

void QSynWiringDiagramWidget::SetRightPicLabel(const CString &strPicName)//设置接线图
{
	CString strTemp;
	strTemp = _P_GetResourcePath();
	strTemp += strPicName;
	QImage oPicMuTime(strTemp);
	ui->m_pRightPic_Label->setGeometry(0, 0, this->width()-20, this->height());
	oPicMuTime = oPicMuTime.scaled(ui->m_pRightPic_Label->width(), ui->m_pRightPic_Label->height());
	ui->m_pRightPic_Label->setPixmap(QPixmap::fromImage(oPicMuTime));
	
}

void QSynWiringDiagramWidget::UpdateWiringUI(int nType)//更新接线图
{
	m_nType = nType;
	switch (nType)
	{
	case SYN_WIRING_UDEFINEONE:
		SetRightPicLabel("SynUAToUB.png");
		break;

	case SYN_WIRING_UDEFINETWO:
		SetRightPicLabel("SynUAToUBC.png");
		break;

	case SYN_WIRING_UDEFINETHREE:
		SetRightPicLabel("SynUZToUABC.png");
		break;

	case SYN_WIRING_UDEFINEFOUR:
		SetRightPicLabel("SynUABCToUABC2.png");
		break;
	default:
		SetRightPicLabel("SynUAToUB.png");
		break;
	}
}
/*void QSynWiringDiagramWidget::setCommonData(CExBaseList* pCommonParaTest)
{
	ASSERT(pCommonParaTest != NULL);

	POS pos = pCommonParaTest->GetHeadPosition();
	while (pos != NULL)
	{
		CSttMacroTestParaData *pData = (CSttMacroTestParaData*)pCommonParaTest->GetNext(pos);
		if (pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_UgConnectDef)
		{
			m_nType = pData->m_strValue.toFloat();				//电压定义
		}
	}
	UpdateWiringUI(m_nType);

}*/

void QSynWiringDiagramWidget::resizeEvent(QResizeEvent *pReSizeEvent)
{
	emit sizeChanged();
}

//根据界面的大小，也随之改变
void QSynWiringDiagramWidget::slot_UpdateUIPosition()
{
	disconnect(this, SIGNAL(sizeChanged()), this, SLOT(slot_updateButtonPosition()));
	UpdateWiringUI(m_nType);
	connect(this, SIGNAL(sizeChanged()), this, SLOT(slot_updateButtonPosition()));
}
