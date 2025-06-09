#include "SttToolButtonBase.h"
#include "../../../../Module/API/GlobalConfigApi.h"

QSttToolButtonBase::QSttToolButtonBase(CExBaseObject *pCfgData,QWidget *parent)
: QToolButton(parent)
{
	setFocusPolicy(Qt::StrongFocus);
	m_pCfgData = pCfgData;
	m_bShow = true;
	show();
	setParent(parent);
}

QSttToolButtonBase::~QSttToolButtonBase()
{

}

//2022-6-9  lijunqing
void QSttToolButtonBase::UpdateState(CDataGroup *pDataGroup)
{
	if (pDataGroup == NULL)
	{
		//初始状态，永远设置为0  2022-6-10  lijunqing
		SetPic(0);
		return ;
	}

	CDvmData *pFind = FindData(pDataGroup);
	UpdateState(pFind);
}

void QSttToolButtonBase::UpdateState(CDvmData *pData)
{
	if (pData == NULL || m_pCfgData == NULL)
	{
		return;
	}

	if (pData->m_strID != m_pCfgData->m_strID)
	{
		if (pData->m_strID.CompareNoCase(m_pCfgData->m_strID) != 0)
		{//2022-6-10  lijunqing 兼容大小写：配置文件和测试仪底层上送的数据，大小写不一致
			return;
		}
	}
	
    SetPic(pData->m_strValue.toInt());
}

void QSttToolButtonBase::UpdateEnableState(const CString &strState)
{
	
}

void QSttToolButtonBase::ShowBtn(bool bShow)
{
	m_bShow = bShow;

	setVisible(bShow);
}

CDvmData* QSttToolButtonBase::FindData(CDataGroup *pDataGroup)
{
	if (m_pCfgData == NULL)
	{
		return NULL;
	}

	return FindData(pDataGroup, m_pCfgData->m_strID);
}

CDvmData* QSttToolButtonBase::FindData(CDataGroup *pDataGroup, const CString strID)
{
	POS pos = pDataGroup->GetHeadPosition();
	CExBaseObject *p = NULL;
	CDvmData *pFind = NULL;

	while (pos != NULL)
	{
		p = pDataGroup->GetNext(pos);

		if (p->m_strID.CompareNoCase(strID) == 0)
		{
			pFind = (CDvmData *)p;
			break;
		}
	}

	return pFind;
}

void QSttToolButtonBase::SetBtnIcon(CSttFrame_Button *pBtnData)
{
	if (pBtnData->m_strIcon.GetLength() < 3)
	{
		return;
	}

	QString strPath = _P_GetResourcePath();
	strPath += pBtnData->m_strIcon;
/*
	QIcon oIcon = QIcon(strPath);

	//QPixmap pixmap = oIcon.pixmap(QSize(pBtnData->m_nWidth, pBtnData->m_nWidth));
	//QIcon tempIcon = QIcon(pixmap.scaled(pButton->width(), pButton->height()));
	setIcon(oIcon);
*/
	QPixmap pixmap(strPath);
	this->setIcon(pixmap);
}

void QSttToolButtonBase::FillBtnIcon(CSttFrame_Button *pBtnData)
{
	if (pBtnData->m_strIcon.GetLength() < 3)
	{
		return;
	}

	QString strPath = _P_GetResourcePath();
	strPath += pBtnData->m_strIcon;

	QPixmap pixmap(strPath);
	QIcon tempIcon = QIcon(pixmap.scaled(width(), height()));
	setIcon(tempIcon);
	setIconSize(QSize(width(), height()));
}


