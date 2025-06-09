#include <QFont>
#include "SttWgtText.h"
#include "SttWgtNativeMainLinux.h"
#include "../SttXuiData/SttXuiDataText.h"
#include "../../../../Module/API/GlobalConfigApi.h"
#include "../../../../Module/API/FileApi.h"
#include "../../../../Module/XLanguage/XLanguageMngr.h"

QSttWgtText::QSttWgtText(QWidget* pParent)
{
	m_pParent = pParent;
	setParent(pParent);
}

QSttWgtText::~QSttWgtText()
{

}

void QSttWgtText::SetWgtStyle(QSttWgtStyle* pStyle)
{
	if(!pStyle)
	{
		return;
	}

	QSttWgtBase::SetWgtStyle(this, pStyle);

	QPalette palette;
	if(pStyle->m_strBkColor.GetLength())
	{
		QColor bkColor(pStyle->m_strBkColor);
		palette.setColor(QPalette::Window, bkColor);
	}

	if(pStyle->m_strGdColor.GetLength())
	{
		QColor gdColor(pStyle->m_strGdColor);
		palette.setColor(QPalette::WindowText, gdColor);
	}
	

	setAutoFillBackground(true);
	setPalette(palette);
}

void QSttWgtText::InitUIOwn(CExBaseObject *pSttXuiData)
{
	if (pSttXuiData)
	{
		CSttXuiDataText* pData = (CSttXuiDataText*)pSttXuiData;
		if(pData->m_strPic.GetLength())
		{
			setScaledContents(true);
			CString strPath = _P_GetResourcePath() + pData->m_strPic;

#ifndef NOT_USE_XLANGUAGE
			if ((!xlang_IsCurrXLanguageChinese())&&
				((pData->m_strID == "Title") || (pData->m_strID == "Bottom")))//zhouhj 2024.1.31 增加对文件标题的图片多语言处理
			{
				CString strNewPath;
				long nIndex = strPath.ReverseFind('.');

				if (nIndex>0)
				{
					strNewPath = strPath.Left(nIndex);
					strNewPath.AppendFormat("-%s",xlang_GetCurrLanguageID().GetString());
					strNewPath += strPath.Mid(nIndex);

					if (IsFileExist(strNewPath))
					{
						strPath = strNewPath;					
					}

				}
			}
#endif

			QPixmap image(strPath);
			setPixmap(image);
			setGeometry(pData->m_nX*g_dUIShowCoef, pData->m_nY*g_dUIShowCoef, pData->m_nCx*g_dUIShowCoef, pData->m_nCy*g_dUIShowCoef);
		}
		else
		{
			setText(pData->m_strName/*m_strText*/);//20220713 zhouhj 为便于多语言转换,采用name属性值赋值
			//设置样式
			QSttWgtStyle* pStyle = GetWgtStyle(WGT_TYPE_FONT, pData->m_strFont);
			SetWgtStyle(pStyle);
			setGeometry(pData->m_nX*g_dUIShowCoef, pData->m_nY*g_dUIShowCoef, pData->m_nCx*g_dUIShowCoef, pData->m_nCy*g_dUIShowCoef);
			setObjectName(pData->m_strID);
		}
	}	
}
