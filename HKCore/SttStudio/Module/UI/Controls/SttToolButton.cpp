#include "SttToolButton.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../SttTestCntrCmdDefine.h"

extern long SttFrame_Vert_Gap;  //框架按钮垂直方向上的间隔，系统为工具栏、状态栏绘制边框
extern long SttFrame_Line_Pix;    //绘制边框的像素点

QSttToolButton::QSttToolButton(CExBaseObject *pCfgData,QFont font,QWidget *parent)
    : QSttToolButtonBase(pCfgData,parent)
{
    CSttFrame_Button *pButton = (CSttFrame_Button*)pCfgData;

    CSttFrame_BarBase *pParent = (CSttFrame_BarBase*)(pButton->GetParent()->GetParent());

    this->setText(pButton->m_strName);
	this->setFont(font);
#ifdef _PSX_QT_LINUX_
	setStyleSheet(g_strQToolButtonStyleSheet);
#endif
//	setStyleSheet("QToolButton:focus{background-color:rgb(255,0,0); color:white; border-radius:10px; border:3px groove gray; border-style:outset;}");

	//xlang_SetLangStrToWidget(this, pCfgData->m_strID, XLang_Ctrls_QToolButton);

    m_nHeight = pParent->GetBtnHeight();
    if(pButton->m_nWidth == 0)
    {
        QFontMetrics fm(font);
        QRect rec = fm.boundingRect(this->text());
        m_nWidth = rec.width() + 20;
    }
    else
        m_nWidth = pButton->m_nWidth;

    this->setFixedSize(m_nWidth,m_nHeight);

    if(pButton->m_strIcon != "")
    {
        if(pParent->m_strIconPos != "None" && pParent->m_strIconPos != "")
        {
			//2022-12-02  lijunqing
			if (pButton->m_strName.GetLength() > 0)
			{//有名称
				//QPixmap pixmap(pButton->m_strIcon);
				//this->setIcon(pixmap);
				SetBtnIcon(pButton);   //2022-12-02  lijunqing
	     
				if(pParent->m_strIconPos == "top")
				{
					this->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
				}
				else if(pParent->m_strIconPos == "left")
				{
					this->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
				}
			}
			else
			{
				this->setToolButtonStyle(Qt::ToolButtonIconOnly);
				FillBtnIcon(pButton);   //2022-12-02  lijunqing
			}
        }
        else
        {
            this->setToolButtonStyle(Qt::ToolButtonTextOnly);
        }
    }
    else
    {
        this->setToolButtonStyle(Qt::ToolButtonTextOnly);
    }

	connect(this,SIGNAL(clicked()),this,SLOT(slot_Click()),Qt::AutoConnection);
}

QSttToolButton::~QSttToolButton()
{

}

void QSttToolButton::slot_Click()
{
	if (m_pCfgData->m_strID == STT_CNTR_CMD_Exit)
	{
		setEnabled(FALSE);
	}

    emit sig_clicked(m_pCfgData->m_strID);
}

void QSttToolButton::UpdateEnableState(const CString &strState)
{
	if (m_pCfgData == NULL)
	{
		return;
	}

	if (m_pCfgData->GetClassID() != MNGRCLASSID_CSTTFRAME_BUTTON)
	{
		return;
	}

	CSttFrame_Button *pButton = (CSttFrame_Button*)m_pCfgData;
	
	if (pButton->m_strEnableState.GetLength() < 2)
	{
		return;
	}

	if (pButton->m_strEnableState == strState)
	{
		setEnabled(TRUE);
	}
	else
	{
		setEnabled(FALSE);
	}
}

