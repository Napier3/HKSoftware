#include "QSettingGlobal.h"

extern void  Stt_Global_SettingSelect(QObject *parent, const CString &sFormat, const CString &sName);

QSettingGlobal *g_pQSettingGlobal_Object = NULL;

QSettingGlobal::QSettingGlobal() 
{
	m_pParent = NULL;
	ConnectForSettingDlg();
}

QSettingGlobal::~QSettingGlobal()
{
    if(g_pSettingSelectModalDlg != NULL)
    {
		QObject::disconnect(g_pSettingSelectModalDlg, SIGNAL(sig_ShowSetting(QString, QString)), this, SLOT(slot_ShowSetting(QString, QString)));
		QObject::disconnect(this, SIGNAL(sig_SettingSelect(CExBaseObject *)), g_pSettingSelectModalDlg, SLOT(slot_SelectModeData(CExBaseObject *)));
		QObject::disconnect(this, SIGNAL(sig_SettingSelect(QString)), g_pSettingSelectModalDlg, SLOT(slot_SelectModeData(QString)));
        QObject::disconnect(g_pSettingSelectModalDlg, SIGNAL(sig_ClearAll()), this, SLOT(slot_ClearAllMap()));

        delete g_pSettingSelectModalDlg;
        g_pSettingSelectModalDlg = NULL;
    }	
}

//20241018 huangliang 模态对话框定值后，返回模态对话框已经消失
void QSettingGlobal::SetParent(QWidget *pParent)
{
	if (pParent == NULL)
	{
		if (mlist_HisParent.size() <= 1)	//模态对话框时，一定大于1
		{
			m_pParent = NULL;
		}
		else
		{
			mlist_HisParent.removeLast();	//去掉最后的模态对话框
			m_pParent = mlist_HisParent.last();
		}
		return;
	}
	if (pParent->inherits("CSttMacroParaEditViewOriginal"))
	{
		mlist_HisParent.clear();	//认为是对上一个层级
	}

	mlist_HisParent.append(pParent);
	m_pParent = pParent;
}

bool QSettingGlobal::ConnectForSettingDlg()
{
	if (g_pSettingSelectModalDlg == NULL)
	{
		g_pSettingSelectModalDlg = new SettingSelectDlg();
	}

	QObject::connect(g_pSettingSelectModalDlg, SIGNAL(sig_ShowSetting(QString, QString)), this, SLOT(slot_ShowSetting(QString, QString)), Qt::UniqueConnection);
	QObject::connect(this, SIGNAL(sig_SettingSelect(CExBaseObject *)), g_pSettingSelectModalDlg, SLOT(slot_SelectModeData(CExBaseObject *)), Qt::UniqueConnection);
	QObject::connect(this, SIGNAL(sig_SettingSelect(QString)), g_pSettingSelectModalDlg, SLOT(slot_SelectModeData(QString)), Qt::UniqueConnection);

    QObject::connect(g_pSettingSelectModalDlg, SIGNAL(sig_ClearAll()), this, SLOT(slot_ClearAllMap()), Qt::UniqueConnection);
    return true;
}

void QSettingGlobal::slot_ShowSetting(QString sFormat, QString sName)
{
	Stt_Global_SettingSelect(this, sFormat, sName);
}

void QSettingGlobal::SettingSelect(CExBaseObject *pItem)
{
	emit sig_SettingSelect(pItem);
}
void QSettingGlobal::SettingSelect(const CString &sValue)	
{
	emit sig_SettingSelect(sValue);
}

void QSettingGlobal::slot_ClearAllMap()
{
    ClearAllMaps();
}
void QSettingGlobal::ClearAllMaps()
{
    if(m_pParent == NULL)
        return ;
    ChildInitMaps(m_pParent, 1);	//20240805 huangliang 是当前编辑界面里所有控件的遍历
}
void QSettingGlobal::ChildInitMaps(QObject *pParent, int iOperation)
{
    if (pParent->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
    {
        switch(iOperation)
        {
        case 0:
            ((QSettingLineEdit*)pParent)->RefushData();
            break;
        case 1:
            ((QSettingLineEdit*)pParent)->DlgReturnClear();
            break;
        }
        return ;
    }
    else if(pParent->inherits("QTableWidget"))
    {
        ChildInitTable((QTableWidget*)pParent, iOperation);
        return ;
    }

    foreach (QObject *child, pParent->findChildren<QObject*>()) {
        ChildInitMaps(child, iOperation);
    }
}
void QSettingGlobal::ChildInitTable(QTableWidget *table, int iOperation)
{
    int iRow = table->rowCount();
    int iCol = table->columnCount();
    for(int i=0; i<iRow; i++)
    {
        for(int j=0; j<iCol; j++)
        {
            QTableWidgetItem *tBitem = table->item(i,j);
            QSettingItem* derivedPtr = dynamic_cast<QSettingItem*>(tBitem);		
            if(derivedPtr != NULL)
            {
                switch(iOperation)
                {
                case 0:
                    ((QSettingItem*)tBitem)->RefushData();
                    break;
                case 1:
                    ((QSettingItem*)tBitem)->DlgReturnClear();
                    break;
                }
            }
        }
    }
}
