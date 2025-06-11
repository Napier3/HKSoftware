#include "QModalDlgInterface.h"

//extern void  Stt_Global_SettingSelect(QWidget *parent);

//QModalDlgInterface::QModalDlgInterface(QWidget *parent) : QDialog(parent)
//{
//    if(g_pSettingSelectModalDlg == NULL)
//    {
//        g_pSettingSelectModalDlg = new SettingSelectDlg();
//    }
//	ConnectForSettingDlg();
//}

//QModalDlgInterface::~QModalDlgInterface()
//{
//    if(g_pSettingSelectModalDlg != NULL)
//    {
//        QObject::disconnect(g_pSettingSelectModalDlg, SIGNAL(sig_ClearAll()), this, SLOT(slot_ClearAllMap()));

//        delete g_pSettingSelectModalDlg;
//        g_pSettingSelectModalDlg = NULL;
//    }
//}

//bool QModalDlgInterface::ConnectForSettingDlg()
//{
//    if(g_pSettingSelectModalDlg == NULL)
//        return false;
//	QObject::connect(g_pSettingSelectModalDlg, SIGNAL(sig_ShowSetting()), this, SLOT(slot_ShowSetting()), Qt::UniqueConnection);
//	QObject::connect(this, SIGNAL(sig_SettingSelect(CExBaseObject *)), g_pSettingSelectModalDlg, SLOT(slot_SelectModeData(CExBaseObject *)), Qt::UniqueConnection);
//	QObject::connect(this, SIGNAL(sig_SettingSelect(QString)), g_pSettingSelectModalDlg, SLOT(slot_SelectModeData(QString)), Qt::UniqueConnection);

//	QObject::connect(g_pSettingSelectModalDlg, SIGNAL(sig_ClearAll()), this, SLOT(slot_ClearAllMap()), Qt::UniqueConnection);
//    return true;
//}

//void QModalDlgInterface::slot_ShowSetting()
//{
//	//((QSttTestCntrFrameBase*)g_pSettingMianWind)->OnCmd_SettingSelect(this);
//// 	if (g_pSettingSelectFun != NULL)
//// 		g_pSettingSelectFun(this);
//	Stt_Global_SettingSelect(this);
//}

//void QModalDlgInterface::SettingSelect(CExBaseObject *pItem)
//{
//	emit sig_SettingSelect(pItem);
//}
//void QModalDlgInterface::SettingSelect(const CString &sValue)	//20240730 huangliang
//{
//	emit sig_SettingSelect(sValue);
//}

//void QModalDlgInterface::slot_ClearAllMap()
//{
//    ClearAllMaps();
//}
//void QModalDlgInterface::ClearAllMaps()
//{
//    ChildInitMaps(this, 1);
//}
//void QModalDlgInterface::ChildInitMaps(QObject *pParent, int iOperation)
//{
//    if (pParent->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
//    {
//        switch(iOperation)
//        {
//        case 0:
//            ((QSettingLineEdit*)pParent)->RefushData();
//            break;
//        case 1:
//            ((QSettingLineEdit*)pParent)->DlgReturnClear();
//            break;
//        }
//        return ;
//    }
//    else if(pParent->inherits("QTableWidget"))
//    {
//        ChildInitTable((QTableWidget*)pParent, iOperation);
//        return ;
//    }

//    foreach (QObject *child, pParent->findChildren<QObject*>()) {
//        ChildInitMaps(child, iOperation);
//    }
//}
//void QModalDlgInterface::ChildInitTable(QTableWidget *table, int iOperation)
//{
//    int iRow = table->rowCount();
//    int iCol = table->columnCount();
//    for(int i=0; i<iRow; i++)
//    {
//        for(int j=0; j<iCol; j++)
//        {
//            QTableWidgetItem *tBitem = table->item(i,j);
//            QSettingItem* derivedPtr = dynamic_cast<QSettingItem*>(tBitem);		//20240719 huangliang 改为一个类型只判断一种
//            if(derivedPtr != NULL)
//            {
//                switch(iOperation)
//                {
//                case 0:
//                    ((QSettingItem*)tBitem)->RefushData();
//                    break;
//                case 1:
//                    ((QSettingItem*)tBitem)->DlgReturnClear();
//                    break;
//                }
//            }
//        }
//    }
//}
