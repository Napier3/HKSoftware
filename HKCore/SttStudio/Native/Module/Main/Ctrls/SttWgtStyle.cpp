#include "SttWgtStyle.h"
#include "../SttXuiData/SttXuiDataFont.h"

QSttWgtStyle::QSttWgtStyle()
{
	m_nSize = 0;
}

QSttWgtStyle::~QSttWgtStyle()
{

}

void QSttWgtStyle::InitStyle(CSttXuiDataBase* pSttXuiDataBase)
{
	if (pSttXuiDataBase)
	{
		m_strID = pSttXuiDataBase->m_strID;
		m_strName = pSttXuiDataBase->m_strName;
		switch(pSttXuiDataBase->GetClassID())
		{
		case MNGRCLASSID_CSTTXUIDATAFONT: 
			m_strGdColor = ((CSttXuiDataFont*)pSttXuiDataBase)->m_strCr_Text;
			m_strBkColor = ((CSttXuiDataFont*)pSttXuiDataBase)->m_strCr_Back;
			m_nSize = ((CSttXuiDataFont*)pSttXuiDataBase)->m_nSize;
			m_strType = WGT_TYPE_FONT;
			break;
		default:
			break;
		}
	}
}