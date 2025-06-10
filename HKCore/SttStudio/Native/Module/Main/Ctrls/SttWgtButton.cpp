#include <QMouseEvent>
#include "SttWgtButton.h"
#include "../SttXuiData/SttXuiDataButton.h"
#include "../Module/SttWgtCmdExecTool.h"
#include "../../../../Module/API/GlobalConfigApi.h"
#include "SttWgtNativeMainLinux.h"

QSttWgtButton::QSttWgtButton(QWidget* pParent)
{
	m_pParent = pParent;
	setParent(pParent);
//	setWordWrap(false);
}

QSttWgtButton::~QSttWgtButton()
{

}

void QSttWgtButton::CalcGeometry(long& nX, long nCy, long nInset)
{
	CSttXuiDataButton* pData = (CSttXuiDataButton*)m_pXuiData;
	long nTempCy = nCy - 2 * nInset;
	long nWidth = 0;
	if(pData->m_strPic.GetLength())
	{
		setGeometry(nX, nInset, nTempCy, nTempCy);
		setIconSize(QSize(nTempCy / 2 + 2 * nInset, nTempCy / 2 + 2 * nInset));
		nWidth = nTempCy;
	}
	else
	{
		long nCount = pData->m_strName.GetLength();
		setGeometry(nX, nInset, (nCount + 2) * 20, nTempCy);
		nWidth = (nCount + 2) * 20;
	}
	nX = nX + nWidth + nInset;
}

void QSttWgtButton::InitUIOwn(CExBaseObject *pSttXuiData)
{
	//本体是CSttXuiDataButton
	if(pSttXuiData)
	{
		CSttXuiDataButton* pData = (CSttXuiDataButton*)pSttXuiData;
		setObjectName(pData->m_strID);

		CSttXuiDataCmd *pChildCmd = (CSttXuiDataCmd*)pData->FindByClassID(MNGRCLASSID_CSTTXUIDATACMD);

		if ((pChildCmd != NULL)&&(pChildCmd->m_strID.IsEmpty()))//20220627 zhouhj 命令ID为空,按钮不可用
		{
			setEnabled(false);
		}
		
		if(pData->m_strPic.GetLength())
		{
			QIcon image;
			CString strPath = _P_GetResourcePath() + pData->m_strPic;
			image.addFile(strPath);
			setIcon(image);
			setAutoRaise(true);
			setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

		}

		setText(pData->m_strName);
	}
}

void QSttWgtButton::OnClick()
{
	CSttXuiDataBase* pXuiData = (CSttXuiDataBase*)m_pXuiData;
	if(pXuiData)
	{
		POS pos = pXuiData->GetHeadPosition();
		while (pos)
		{
			CSttXuiDataCmd* pCmd = (CSttXuiDataCmd*)pXuiData->GetNext(pos);
			QSttWgtCmdExecTool::ExecCmd(pCmd->m_strType, pCmd->m_strID, pCmd->m_strData_Src, pCmd->m_strArgv);
		}
	}
}

#ifdef _PSX_OS_CENTOS_
#include<QApplication>
#endif
void QSttWgtButton::mousePressEvent(QMouseEvent *e)
{
	if(e->button() == Qt::LeftButton)
	{
#ifdef _PSX_OS_CENTOS_
        QList<QWidget*> showWindows;
        foreach(QWidget *window,QApplication::topLevelWidgets())
        {
            if(window->isVisible())
            {
                window->hide();
                showWindows.append(window);
            }
        }
        OnClick();
        foreach(QWidget *window,showWindows)
        {
            window->show();
        }
#else
        m_gQSttWgtNativeMainLinux->setEnabled(false);
        OnClick();
        m_gQSttWgtNativeMainLinux->setEnabled(true);
#endif
	}
}
