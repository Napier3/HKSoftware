#include "CharLibWidget.h"
#include <QComboBox>
#include "../../../../../Module/DataMngr/DvmDataset.h"
#include "../../../../../Module/DataMngr/DataGroup.h"
#include "../../../SttTest/Common/tmt_test_mngr.h"
#include "../../../../../AutoTest/Module/Characteristic/CharElementMho.h"
#include "../ZKCharaCurve/QZKFeatureAddDig.h"
#include "../../SttTestCntrFrameBase.h"
#include "../../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../SttTestCtrl/SttTestAppBase.h"
#include "CharInverseSet.h"
#include "../ZKCharaCurve/QCharElementDlg.h"

CString GetSetName(CString strID)	
{
	CDvmData *pFind = (CDvmData*)g_pTmt_SetsRef->FindByID(strID);

	CString strName;
	if (pFind != NULL)
	{
		strName = pFind->m_strName;
		return strName;
	}
	else
	{
		return _T("");
	}
}

CSettingDelegate::CSettingDelegate(QObject *parent /*= NULL*/ )
{

}

CSettingDelegate::~CSettingDelegate()
{
	
}

QWidget * CSettingDelegate::createEditor( QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index ) const
{
	QVariant variant = index.data();

	QComboBox *comboBox = new QComboBox(parent);
	return comboBox;
}

void CSettingDelegate::setEditorData( QWidget * editor, const QModelIndex &index ) const
{
	QString strItem = index.model()->data(index,Qt::EditRole).toString();
	QStringList strItemList;

	strItemList<<GetSetName("Zeset1")<<GetSetName("Zeset2")<<GetSetName("Zeset3")
		<<GetSetName("Zeset4")<<GetSetName("Zeset5")<<GetSetName("Zxset1")
		<<GetSetName("Zxset2")<<GetSetName("Zxset3")<<GetSetName("Zxset4")
		<<GetSetName("Zxset5");

	QComboBox *comboBox = qobject_cast<QComboBox *>(editor);
	comboBox->clear();
	int id = 0;
	for (int i=0; i<strItemList.size(); i++)
	{
		QString strValue = strItemList.at(i);
		if (strValue == strItem)
		{
			id = i;
		}
		comboBox->addItem(strValue);
	}
	comboBox->setCurrentIndex(id);
}

void CSettingDelegate::setModelData( QWidget *editor, QAbstractItemModel *model, const QModelIndex &index ) const
{
	QComboBox *comboBox = qobject_cast<QComboBox *>(editor);
	model->setData(index,comboBox->currentText(),Qt::EditRole);
}

void CSettingDelegate::updateEditorGeometry( QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index ) const
{
	editor->setGeometry(option.rect);
}

QCharLibWidget::QCharLibWidget(QWidget* pParent) : QWidget(pParent)
{
	ui.setupUi(this);

	m_pCharaObj = 0;
	m_pInterface = 0;
	m_pCharArea = 0;
	m_pInterfacebak = 0;
	m_pCharAreabak = 0;
	m_bSetting = TRUE;
	m_nZKCurrentRow = 0;
	m_pImpCharactWidget = NULL;

	//改到切换功能时打开相关文档：存在以下应用场景，不是每次测试都需要打开编辑曲线的界面的
// 	CCharacteristicXmlRWKeys::Create();
// 	CString strPath,strTemp;
// 	strTemp = g_pTheSttTestApp->m_pTestMacroUI->m_strCharlibFile;
// 	strTemp.Replace(_T("CharLib"), _T("Characteristics"));
// 	strPath = _P_GetConfigPath();
// 	strPath += strTemp;
// 	if (IsFileExist(strPath))
// 	{
// 		g_theTestCntrFrame->m_pCharacteristics->OpenXmlFile(strPath,CCharacteristicXmlRWKeys::CCharacteristicsKey(),CCharacteristicXmlRWKeys::g_pXmlKeys);
// 	}

	// 	InitAreaData();
	InitUI();
	InitConnect();
	UpdateCharacters();
    InitLanguage();
}

void QCharLibWidget::InitLanguage()
{
    xlang_SetLangStrToWidget_Txt(ui.m_btnAdd, g_sLangTxt_Add, XLang_Ctrls_QPushButton);
    xlang_SetLangStrToWidget_Txt(ui.m_btnDel, g_sLangTxt_Delete, XLang_Ctrls_QPushButton);
}

QCharLibWidget::~QCharLibWidget()
{
	//CCharacteristicXmlRWKeys::Release();

	if(m_pInterfacebak)
	{
		delete m_pInterfacebak;
		m_pInterfacebak = NULL;
	}

	if(m_pCharAreabak)
	{
		delete m_pCharAreabak;
		m_pCharAreabak = NULL;
	}
}

void QCharLibWidget::InitConnect()
{
	connect(ui.tableWidget_Info, SIGNAL(cellChanged ( int , int  )), this, SLOT(slot_Table_cellChanged ( int , int  )));
	connect(ui.tableWidget_Info2, SIGNAL(cellDoubleClicked ( int , int  )), this, SLOT(slot_Double_Clicked ( int , int  )));
	connect(ui.tableWidget_ZK, SIGNAL(cellClicked( int , int  )), this, SLOT(slot_ZKClicked(int,int)), Qt::UniqueConnection);
	connect(this, SIGNAL(sig_CharChanged()), m_pImpCharactWidget,SLOT(slot_UpdateDrawCharacters()));
	connect(m_pImpCharactWidget, SIGNAL(sig_UpdatePointLocation(float ,float)), this, SLOT(slot_ParaPointChange(float ,float)));
	connect(m_pImpCharactWidget, SIGNAL(sig_AddPointLocation(float ,float)), this, SLOT(slot_ParaAddPoint(float ,float)));
}

void QCharLibWidget::InitAreaData()
{
	ui.tableWidget_Info2->setRowCount(0);

	CCharElement *pCurObj = NULL;

	POS pos = m_pCharArea->GetHeadPosition();
	int i = 0;
	while(pos)
	{
		pCurObj = (CCharElementLined*)m_pCharArea->GetNext(pos);

		ui.tableWidget_Info2->insertRow(i);
		QTableWidgetItem* pitem1 = new QTableWidgetItem(QString::number(i+1));
		pitem1->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter );
		ui.tableWidget_Info2->setItem(i,0,pitem1);

        QTableWidgetItem *pitem2 = new QTableWidgetItem(/* QObject::tr("线段(lined)") */ g_sLangTxt_Lined);
        pitem2->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        ui.tableWidget_Info2->setItem(i, 1, pitem2);

		long *nTestPoint = pCurObj->GetTestPointsRef();
		QTableWidgetItem* pitem3 = new QTableWidgetItem(QString::number(*nTestPoint));
		pitem3->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter );
		ui.tableWidget_Info2->setItem(i,2,pitem3);

		QTableWidgetItem* pitem4 = new QTableWidgetItem(pCurObj->m_strErrLength);
		pitem4->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter );
		ui.tableWidget_Info2->setItem(i,3,pitem4);

		QString strInfo;
		if (pCurObj->GetClassID() == CHARCLASSID_CCHARELEMENTLINED)
		{
                        pitem2->setText(/* QObject::tr("线段(lined)") */ g_sLangTxt_Lined);
			CCharElementLined *pChar = (CCharElementLined *)pCurObj;
			strInfo = pChar->ReturnXml();
		}
		else if (pCurObj->GetClassID() == CHARCLASSID_CCHARELEMENTMHO)
		{
                        pitem2->setText(/* QObject::tr("圆(mho)") */ g_sLangTxt_Mho);
			CCharElementMho *pChar = (CCharElementMho *)pCurObj;
			strInfo = pChar->ReturnXml();
		}
		else if (pCurObj->GetClassID() == CHARCLASSID_CCHARELEMENTLENS)
		{
                        pitem2->setText(/* QObject::tr("透镜(lens)") */ g_sLangTxt_Lens);
			CCharElementLens *pChar = (CCharElementLens *)pCurObj;
			strInfo = pChar->ReturnXml();
		}
		else if (pCurObj->GetClassID() == CHARCLASSID_CCHARELEMENTLINER)
		{
                        pitem2->setText(/* QObject::tr("射线(liner)") */ g_sLangTxt_Liner);
			CCharElementLiner *pChar = (CCharElementLiner *)pCurObj;
			strInfo = pChar->ReturnXml();
		}
		else if (pCurObj->GetClassID() == CHARCLASSID_CCHARELEMENTLINE)
		{
                        pitem2->setText(/* QObject::tr("直线(line)") */ g_sLangTxt_Line);
			CCharElementLine *pChar = (CCharElementLine *)pCurObj;
			strInfo = pChar->ReturnXml();
		}
		else if (pCurObj->GetClassID() == CHARCLASSID_CCHARELEMENTARC)
		{
                        pitem2->setText(/* QObject::tr("圆弧(arc)") */ g_sLangTxt_Arc);
			CCharElementArc *pChar = (CCharElementArc *)pCurObj;
			strInfo = pChar->ReturnXml();
		}
		else if (pCurObj->GetClassID() == CHARCLASSID_CCHARELEMENTARCP)
		{
                        pitem2->setText(/* QObject::tr("圆弧(arcp)") */ g_sLangTxt_Arcp);
			CCharElementArcp *pChar = (CCharElementArcp *)pCurObj;
			strInfo = pChar->ReturnXml();
		}
		QTableWidgetItem* pitem5 = new QTableWidgetItem(strInfo);
		pitem5->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter );
		ui.tableWidget_Info2->setItem(i,4,pitem5);

		i++;
	}
}

void QCharLibWidget::UpdateCharacters()
{
	CCharacteristic *pChar = NULL;
	ui.tableWidget_ZK->setRowCount(0);
	int nCount = g_theTestCntrFrame->m_pCharacteristics->GetCount();

	if (nCount < 1)
	{
		return;
	}

	for (int i=0;i<nCount;i++)
	{
		pChar = (CCharacteristic *)g_theTestCntrFrame->m_pCharacteristics->GetAt(i);
		AddCharacter(pChar);
	}

	m_nZKCurrentRow = 0;
	UpdateZKFeature((CCharacteristic *)g_theTestCntrFrame->m_pCharacteristics->GetAtIndex(0), TRUE);
	UpdateInterfaceData();
	UpdateAreaData();
	ui.tableWidget_ZK->setCurrentCell(0,0);
	emit sig_CharChanged();

}

void QCharLibWidget::UpdateInterfaceData()
{
	CCharInterfaceVariable *pCurObj = NULL;
	disconnect(ui.tableWidget_Info, SIGNAL(cellChanged ( int , int  )), this, SLOT(slot_Table_cellChanged ( int , int  )));
	ui.tableWidget_Info->setRowCount(0);

	POS pos = m_pInterface->GetHeadPosition();
	int i = 0;
	while(pos)
	{
		pCurObj = (CCharInterfaceVariable*)m_pInterface->GetNext(pos);

		ui.tableWidget_Info->insertRow(i);
		QTableWidgetItem* pitem1 = new QTableWidgetItem(QString::number(i+1));
		pitem1->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter );
		pitem1->setFlags(Qt::ItemIsEditable);
		ui.tableWidget_Info->setItem(i,0,pitem1);

		QTableWidgetItem* pitem5 = new QTableWidgetItem(pCurObj->m_strName);
		pitem5->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter );
		pitem5->setFlags(Qt::ItemIsEditable);
		ui.tableWidget_Info->setItem(i,1,pitem5);

		QTableWidgetItem* pitem2 = new QTableWidgetItem(pCurObj->m_strID);
		pitem2->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter );
		pitem2->setFlags(Qt::ItemIsEditable);
		ui.tableWidget_Info->setItem(i,2,pitem2);

		QTableWidgetItem* pitem3 = new QTableWidgetItem(pCurObj->m_strValue);
		pitem3->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter );
		ui.tableWidget_Info->setItem(i,3,pitem3);

		if (m_bSetting)
		{
			QTableWidgetItem* pitem4 = new QTableWidgetItem(GetSetName(pCurObj->m_strScript));
			pitem4->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter );
			ui.tableWidget_Info->setItem(i,4,pitem4);
		}

		i++;
	}

	connect(ui.tableWidget_Info, SIGNAL(cellChanged ( int , int  )), this, SLOT(slot_Table_cellChanged ( int , int  )));
}

void QCharLibWidget::UpdateAreaData()
{
	ui.tableWidget_Info2->setRowCount(0);

	CCharElement *pCurObj = NULL;

	POS pos = m_pCharArea->GetHeadPosition();
	int i = 0;
	while(pos)
	{
		pCurObj = (CCharElementLined*)m_pCharArea->GetNext(pos);

		ui.tableWidget_Info2->insertRow(i);
		QTableWidgetItem* pitem1 = new QTableWidgetItem(QString::number(i+1));
		pitem1->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter );
		ui.tableWidget_Info2->setItem(i,0,pitem1);

                QTableWidgetItem *pitem2 = new QTableWidgetItem(/* QObject::tr("线段(lined)") */ g_sLangTxt_Lined);
                pitem2->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
                ui.tableWidget_Info2->setItem(i, 1, pitem2);

		long *nTestPoint = pCurObj->GetTestPointsRef();
		QTableWidgetItem* pitem3 = new QTableWidgetItem(QString::number(*nTestPoint));
		pitem3->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter );
		ui.tableWidget_Info2->setItem(i,2,pitem3);

		QTableWidgetItem* pitem4 = new QTableWidgetItem(pCurObj->m_strErrLength);
		pitem4->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter );
		ui.tableWidget_Info2->setItem(i,3,pitem4);

		QString strInfo;
		if (pCurObj->GetClassID() == CHARCLASSID_CCHARELEMENTLINED)
		{
                        pitem2->setText(/* QObject::tr("线段(lined)") */ g_sLangTxt_Lined);
			CCharElementLined *pChar = (CCharElementLined *)pCurObj;
			strInfo = pChar->ReturnXml();
		}
		else if (pCurObj->GetClassID() == CHARCLASSID_CCHARELEMENTMHO)
		{
                        pitem2->setText(/* QObject::tr("圆(mho)") */ g_sLangTxt_Mho);
			CCharElementMho *pChar = (CCharElementMho *)pCurObj;
			strInfo = pChar->ReturnXml();
		}
		else if (pCurObj->GetClassID() == CHARCLASSID_CCHARELEMENTLENS)
		{
                        pitem2->setText(/* QObject::tr("透镜(lens)") */ g_sLangTxt_Lens);
			CCharElementLens *pChar = (CCharElementLens *)pCurObj;
			strInfo = pChar->ReturnXml();
		}
		else if (pCurObj->GetClassID() == CHARCLASSID_CCHARELEMENTLINER)
		{
                        pitem2->setText(/* QObject::tr("射线(liner)") */ g_sLangTxt_Liner);
			CCharElementLiner *pChar = (CCharElementLiner *)pCurObj;
			strInfo = pChar->ReturnXml();
		}
		else if (pCurObj->GetClassID() == CHARCLASSID_CCHARELEMENTLINE)
		{
                        pitem2->setText(/* QObject::tr("直线(line)") */ g_sLangTxt_Line);
			CCharElementLine *pChar = (CCharElementLine *)pCurObj;
			strInfo = pChar->ReturnXml();
		}
		else if (pCurObj->GetClassID() == CHARCLASSID_CCHARELEMENTARC)
		{
                        pitem2->setText(/* QObject::tr("圆弧(arc)") */ g_sLangTxt_Arc);
			CCharElementArc *pChar = (CCharElementArc *)pCurObj;
			strInfo = pChar->ReturnXml();
		}
		else if (pCurObj->GetClassID() == CHARCLASSID_CCHARELEMENTARCP)
		{
                        pitem2->setText(/* QObject::tr("圆弧(arcp)") */ g_sLangTxt_Arcp);
			CCharElementArcp *pChar = (CCharElementArcp *)pCurObj;
			strInfo = pChar->ReturnXml();
		}
		QTableWidgetItem* pitem5 = new QTableWidgetItem(strInfo);
		pitem5->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter );
		ui.tableWidget_Info2->setItem(i,4,pitem5);

		i++;
	}
}

void QCharLibWidget::UpdateZKFeature(CCharacteristic *pObj,BOOL bSetting)
{
	if (pObj == NULL)
	{
		return;
	}

	m_bSetting = bSetting;
	m_pCharaObj = pObj;
	m_pInterface = (CCharInterface*)m_pCharaObj->GetCharInterface();
	m_pCharArea = (CCharacterArea *)m_pCharaObj->GetCharacterArea();
	m_pInterfacebak = (CCharInterface*)m_pCharaObj->GetCharInterface()->Clone();
	m_pCharAreabak = (CCharacterArea *)m_pCharaObj->GetCharacterArea()->Clone();
	UpdateInterfaceData();
	UpdateAreaData();
}

void QCharLibWidget::InitUI()
{
	InitTableWidget();
	InitCharactWidget();
}

void QCharLibWidget::InitTableWidget()
{
	CString strZoomIndex, strName, strFaultPhase, strIndex, strValue,
		strEdgeType, strPoints, strErrorBand, strEdgeInfo, strAttachSetting;
	xlang_GetLangStrByFile(strZoomIndex, "CharLib_ZoomIndex");
	xlang_GetLangStrByFile(strName, "CharLib_Name");
	xlang_GetLangStrByFile(strFaultPhase, "CharLib_FaultPhase");
	xlang_GetLangStrByFile(strIndex, "CharLib_Index");
	xlang_GetLangStrByFile(strValue, "CharLib_Value");
	xlang_GetLangStrByFile(strEdgeType, "CharLib_EdgeType");
	xlang_GetLangStrByFile(strPoints, "CharLib_Points");
	xlang_GetLangStrByFile(strErrorBand, "CharLib_ErrorBand");
	xlang_GetLangStrByFile(strEdgeInfo, "CharLib_EdgeInfo");
	xlang_GetLangStrByFile(strAttachSetting, "CharLib_AttachSetting");

	//表一
	QHeaderView* pTop = ui.tableWidget_ZK->horizontalHeader();
	pTop->setClickable(false);
	pTop->setMovable(false);
	QHeaderView* pLeft = ui.tableWidget_ZK->verticalHeader();
	pLeft->setDefaultSectionSize(25);
	pLeft->setVisible(false);

	ui.tableWidget_ZK->horizontalHeader()->setStretchLastSection(true); //设置充满表宽度
	ui.tableWidget_ZK->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	ui.tableWidget_ZK->setColumnCount(3);

	QStringList headers;
	headers<<strZoomIndex<<strFaultPhase<<strName;
	ui.tableWidget_ZK->setHorizontalHeaderLabels(headers);
	ui.tableWidget_ZK->setColumnWidth(0,80);
	ui.tableWidget_ZK->setColumnWidth(1,100);
	ui.tableWidget_ZK->setColumnWidth(2,100);

	connect(ui.m_btnAdd, SIGNAL(clicked ()), this, SLOT(slot_ZkPbnAddClicked()));
	connect(ui.m_btnDel, SIGNAL(clicked ()), this, SLOT(slot_ZkPbnDelClicked()));

	//表二表三
	pTop = ui.tableWidget_Info->horizontalHeader();
	pTop->setClickable(false);
	pTop->setMovable(false);
	pLeft = ui.tableWidget_Info->verticalHeader();
	pLeft->setDefaultSectionSize(25);
	pLeft->setVisible(false);

	ui.tableWidget_Info->horizontalHeader()->setStretchLastSection(true); //设置充满表宽度
	ui.tableWidget_Info->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

	pTop = ui.tableWidget_Info2->horizontalHeader();
	pTop->setClickable(false);
	pTop->setMovable(false);
	pLeft = ui.tableWidget_Info2->verticalHeader();
	pLeft->setDefaultSectionSize(25);
	pLeft->setVisible(false);

	ui.tableWidget_Info2->horizontalHeader()->setStretchLastSection(true); //设置充满表宽度
	ui.tableWidget_Info2->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui.tableWidget_Info2->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

	headers.clear();
	if (m_bSetting)
	{
		ui.tableWidget_Info->setColumnCount(5);

		headers<<strIndex<<strName<<"ID"<<strValue<<strAttachSetting;
		ui.tableWidget_Info->setHorizontalHeaderLabels(headers);
		ui.tableWidget_Info->setColumnWidth(0,40);
		ui.tableWidget_Info->setColumnWidth(1,80);
		ui.tableWidget_Info->setColumnWidth(2,80);
		ui.tableWidget_Info->setColumnWidth(3,80);
		ui.tableWidget_Info->setColumnWidth(4,100);

		CSettingDelegate *comboBox = new CSettingDelegate();
		ui.tableWidget_Info->setItemDelegateForColumn(4,comboBox);
	}
	else
	{
		ui.tableWidget_Info->setColumnCount(4);

		headers<<strIndex<<strName<<"ID"<<strValue;
		ui.tableWidget_Info->setHorizontalHeaderLabels(headers);
		ui.tableWidget_Info->setColumnWidth(0,40);
		ui.tableWidget_Info->setColumnWidth(1,80);
		ui.tableWidget_Info->setColumnWidth(2,80);
		ui.tableWidget_Info->setColumnWidth(3,80);
	}

	QStringList headers_2;
	ui.tableWidget_Info2->setColumnCount(5);

	headers_2<<strIndex<<strEdgeType<<strPoints<<strErrorBand<<strEdgeInfo;
	ui.tableWidget_Info2->setHorizontalHeaderLabels(headers_2);
	ui.tableWidget_Info2->setColumnWidth(0,40);
	ui.tableWidget_Info2->setColumnWidth(1,80);
	ui.tableWidget_Info2->setColumnWidth(2,60);
	ui.tableWidget_Info2->setColumnWidth(3,100);
	ui.tableWidget_Info2->setColumnWidth(4,100);
}

void QCharLibWidget::InitCharactWidget()
{
	m_pImpCharactWidget = new QImpCharactWidget(this,true,true);

	if (g_pTheSttTestApp->m_pTestMacroUI->m_strID == _T("CurrInverseTimeTest"))
	{
		m_pImpCharactWidget->setObjectName(QString::fromUtf8("QInverseCharactWidget"));
		m_pImpCharactWidget->SetAxisName(_T("I/In"),_T("t(s)"),_T("I* - t"));
		m_pImpCharactWidget->m_pCharacterDrawView->SetXYUnitShow(_T(""),_T("s"));
		m_pImpCharactWidget->m_pCharacterDrawView->SetIsShowText(false);
		m_pImpCharactWidget->IsHaveAddAct();
	}
	else
	{
	m_pImpCharactWidget->setObjectName(QString::fromUtf8("QImpCharactWidget"));
		m_pImpCharactWidget->SetAxisName(_T("R"),_T("X"),_T("R-X(omg)"));
	}
// 	long id = g_pTheSttTestApp->m_pTestMacroUI->GetClassID();
// 	if (m_pCharArea)
// 	{
// 		CCharElement *pObj = (CCharElement*)m_pCharArea->GetAtIndex(0);
// 		if (pObj != NULL)
// 		{
// 			if (pObj->GetClassID()>=CHARCLASSID_CCHARELEMENTI2T && pObj->GetClassID()<=CHARCLASSID_CCHARELEMENTIEEE)
// 			{
// 				m_pImpCharactWidget->setObjectName(QString::fromUtf8("QInverseCharactWidget"));
// 				m_pImpCharactWidget->SetAxisName(_T("I/In"),_T("t(s)"),_T("I* - t"));
// 				m_pImpCharactWidget->m_pCharacterDrawView->SetXYUnitShow(_T(""),_T("s"));
// 				m_pImpCharactWidget->m_pCharacterDrawView->SetIsShowText(false);
// 				m_pImpCharactWidget->IsHaveAddAct();
// 			}
// 			else
// 			{
// 				m_pImpCharactWidget->setObjectName(QString::fromUtf8("QImpCharactWidget"));
// 				m_pImpCharactWidget->SetAxisName(_T("R"),_T("X"),_T("R-X(omg)"));
// 			}
// 		}
// 		InitAreaData();
// 	}
// 	else
// 		m_pImpCharactWidget->setObjectName(QString::fromUtf8("QImpCharactWidget"));

	ui.m_wgtCharLib->insertTab(-1, m_pImpCharactWidget, "ImpCharactWidget");
	ui.m_wgtCharLib->findChildren<QTabBar*>().at(0)->hide();
}

void QCharLibWidget::slot_ZkPbnAddClicked()
{
	ui.m_btnDel->setDisabled(false);

	if (ui.tableWidget_Info2->hasFocus() && ui.tableWidget_Info2->rowCount()>0)
	{
		if (m_pCharaObj->GetClassID() == CHARCLASSID_CCHARELEMENTLINED)
		{
			QCharElementDlg dlg(NULL,this);
			dlg.exec();

			if (dlg.m_nIsOK == 1)
			{
				CCharElement *pNew = dlg.GetNewElement();
				if (pNew->GetClassID() == CHARCLASSID_CCHARELEMENTMHO)
				{
					m_pCharArea->DeleteChildren();
				}
				m_pCharArea->AddTail(pNew);
				InitAreaData();
				emit sig_CharChanged();
			}
		}
	}
	else
	{
	QZKFeatureAddDig dig(g_pTheSttTestApp->m_pTestMacroUI->m_strCharlibFile);
	connect(&dig,SIGNAL(sig_clickOK(CCharacteristic*)),this,SLOT(slot_ZkAddChar(CCharacteristic*)));
	dig.exec();
		disconnect(&dig,SIGNAL(sig_clickOK(CCharacteristic*)),this,SLOT(slot_ZkAddChar(CCharacteristic*)));
	}

}

void QCharLibWidget::slot_ZkPbnDelClicked()
{
	//g_theSttXTestMngrBaseApp->SetModifyPara();

	if (ui.tableWidget_Info2->hasFocus() && ui.tableWidget_Info2->rowCount()>0)
	{
		if (m_pCharaObj->GetClassID() == CHARCLASSID_CCHARELEMENTLINED)
		{
			CCharElement *pObj = (CCharElement*)m_pCharArea->GetAtIndex(ui.tableWidget_Info2->currentRow());
			m_pCharArea->Delete(pObj);
			InitAreaData();
			emit sig_CharChanged();
		}
	}
	else
	{
	int row = ui.tableWidget_ZK->currentRow();
	CCharacteristic* pObj = (CCharacteristic*)g_theTestCntrFrame->m_pCharacteristics->GetAtIndex(row);
	g_theTestCntrFrame->m_pCharacteristics->DeleteByID(pObj->m_strID);

	if (row != -1)
	{
		ui.tableWidget_ZK->removeRow(row);
	}
	if (row <= 0)
	{
		if (ui.tableWidget_ZK->rowCount() > 0)
		{
			ui.tableWidget_ZK->setCurrentCell(0,0);
		}
		else
		{
			ui.m_btnDel->setDisabled(true);
		}
	}
		emit sig_CharChanged();
	}

}

void QCharLibWidget::AddCharacter(CCharacteristic *pChar)
{
	int rowCount = ui.tableWidget_ZK->rowCount();
	QComboBox *item1 = new QComboBox();
	item1->addItems(m_PeriodList);
	QComboBox *item2 = new QComboBox();
	item2->addItems(m_ErrorPhaseList);

	item1->setCurrentIndex(pChar->m_strIndex.toInt() - 1);
	int i;
	for (i = 0; i < m_ErrorPhaseList.size();i++ )
	{
		if (pChar->m_strID == m_ErrorPhaseList.at(i))
		{
			break;
		}
	}
	if (i >= m_ErrorPhaseList.size())
	{
		i = 0;
	}
	pChar->m_strID = _T("ALL");
	item2->setCurrentIndex(i);

	QTableWidgetItem *item3 = new QTableWidgetItem();
	item3->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	item3->setText(pChar->m_strName);

	ui.tableWidget_ZK->insertRow(rowCount);
	ui.tableWidget_ZK->setCellWidget (rowCount,0,item1);
	ui.tableWidget_ZK->setCellWidget (rowCount,1,item2);

	m_CmbListParaNo.append(item1);
	m_CmbListFaultPha.append(item2);

	connect(item1,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_ParaNoChanegd(int)));
	connect(item2,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_FaultPhaChanegd(int)));
	ui.tableWidget_ZK->setItem(rowCount, 2, item3); 

	ui.tableWidget_ZK->setFocus();
	ui.tableWidget_ZK->setCurrentCell(rowCount,2);
	m_nZKCurrentRow = rowCount;
}

void QCharLibWidget::slot_ZkAddChar(CCharacteristic *pObj)
{
	CCharacteristic *pNew = (CCharacteristic*)pObj->Clone();
	CCharacterArea *pCharArea = (CCharacterArea *)pNew->GetCharacterArea();
	CCharElement *pElement = (CCharElement*)pCharArea->GetAtIndex(0);
	if (pElement != NULL)
	{
		if (pElement->GetClassID()>=CHARCLASSID_CCHARELEMENTI2T && pElement->GetClassID()<=CHARCLASSID_CCHARELEMENTIEEE)
		{
			g_theTestCntrFrame->m_pCharacteristics->RemoveAll();
			g_theTestCntrFrame->m_pCharacteristics->AddNewChild(pNew);
			UpdateCharacters();
		}
		else
	{
			g_theTestCntrFrame->m_pCharacteristics->AddNewChild(pNew);
			AddCharacter(pNew);
		}
	}
	UpdateZKFeature(pNew, TRUE);

	emit sig_CharChanged();
}

void QCharLibWidget::slot_ParaNoChanegd(int nIndex)
{
	QComboBox *pCbo = (QComboBox*)sender();
	int i;
	for(i = 0; i < m_CmbListParaNo.size();i++)
	{
		if (pCbo == m_CmbListParaNo.at(i))
		{
			break;
		}
	}
	CCharacteristic* pObj = (CCharacteristic*)g_theTestCntrFrame->m_pCharacteristics->GetAtIndex(i);
	pObj->m_strIndex = QString::number(nIndex);
}

void QCharLibWidget::slot_FaultPhaChanegd(int nIndex)
{
	QComboBox *pCbo = (QComboBox*)sender();
	int i;
	for(i = 0; i < m_CmbListFaultPha.size();i++)
	{
		if (pCbo == m_CmbListFaultPha.at(i))
		{
			break;
		}
	}
	CCharacteristic* pObj = (CCharacteristic*)g_theTestCntrFrame->m_pCharacteristics->GetAtIndex(i);
	pObj->m_strID = m_ErrorPhaseList.at(nIndex);
}

void QCharLibWidget::slot_ZKClicked( int nRow,int nCol )
{
	if (nRow < 0)
	{
		return;
	}
	
	if (m_nZKCurrentRow != nRow)
	{
		m_nZKCurrentRow = nRow;
		CCharacteristic* pObj = (CCharacteristic*)g_theTestCntrFrame->m_pCharacteristics->GetAtIndex(nRow);
		UpdateZKFeature(pObj, TRUE);
// 		ZKFeatureDig dig(pObj,TRUE);
// 
// 		connect(&dig,SIGNAL(sig_CharChanged()),this,SIGNAL(sig_CharChanged()));
// 		dig.exec();
// 		disconnect(&dig,SIGNAL(sig_CharChanged()),this,SIGNAL(sig_CharChanged()));
// 
// 		emit sig_CharChanged();
	}
}

void QCharLibWidget::slot_Table_cellChanged( int nRow, int nCol)
{
	if (nRow < 0)
	{
		return;
	}

	disconnect(ui.tableWidget_Info, SIGNAL(cellChanged ( int , int  )), this, SLOT(slot_Table_cellChanged ( int , int  )));
	CCharInterfaceVariable *pObj = (CCharInterfaceVariable*)m_pInterface->GetAtIndex(nRow);

	if (m_bSetting)
	{
		if (nCol == 3)
		{
			QTableWidgetItem *pItem2 = ui.tableWidget_Info->item(nRow, 3);
			QTableWidgetItem *pItem3 = ui.tableWidget_Info->item(nRow, 4);
			pItem3->setText(QString(tr("")));
			pObj->m_strValue = pItem2->text();
			pObj->m_strScript = _T("");
		}
		else if (nCol == 4)
		{
			QTableWidgetItem *pItem2 = ui.tableWidget_Info->item(nRow, 3);
			QTableWidgetItem *pItem3 = ui.tableWidget_Info->item(nRow, 4);

			CDvmData *pData = (CDvmData*)g_pTmt_SetsRef->FindByName(pItem3->text());
			if (pData != NULL)
			{
				pObj->m_strScript = pData->m_strID;
				pObj->m_strValue = pData->m_strValue;
			}
			else
			{
				pObj->m_strScript = _T("");
				pObj->m_strValue = _T("0");
			}
			pItem3->setText(GetSetName(pObj->m_strScript));
			pItem2->setText(pObj->m_strValue);

		}
	}
	else
	{
		if (nCol == 3)
		{
			QTableWidgetItem *pItem2 = ui.tableWidget_Info->item(nRow, 3);
			pObj->m_strValue = pItem2->text();
		}
	}

	emit sig_CharChanged();

	connect(ui.tableWidget_Info, SIGNAL(cellChanged ( int , int  )), this, SLOT(slot_Table_cellChanged ( int , int  )));

}

void QCharLibWidget::slot_Double_Clicked( int nRow, int nCol)
{
	if (nRow < 0)
	{
		return;
	}

	CCharElement *pObj = (CCharElement*)m_pCharArea->GetAtIndex(nRow);
	if (pObj != NULL)
	{
		if (pObj->GetClassID()>=CHARCLASSID_CCHARELEMENTI2T && pObj->GetClassID()<=CHARCLASSID_CCHARELEMENTIEEE)
		{
			QCharInverseSet dlg(pObj,this);
			CCharElement *pOld = (CCharElement *)pObj->Clone();
// 			connect(&dlg,SIGNAL(sig_CharChanged()),this,SIGNAL(sig_CharChanged()));
			dlg.exec();
// 			disconnect(&dlg,SIGNAL(sig_CharChanged()),this,SIGNAL(sig_CharChanged()));

			if (dlg.m_nIsOK == 2)
			{
				pObj->Copy(pOld);
			}
			else
			{
				emit sig_CharChanged();
			}
			delete pOld;
		}
		else if (pObj->GetClassID() == CHARCLASSID_CCHARELEMENTLINED)
		{
			QCharElementDlg dlg(pObj,this);
			dlg.exec();

			if (dlg.m_nIsOK == 1)
			{
				if (dlg.GetNewElement()->GetClassID() == CHARCLASSID_CCHARELEMENTMHO)
				{
					m_pCharArea->DeleteChildren();
					m_pCharArea->AddNewChild(dlg.GetNewElement());
				}
				else
				{
					if (pObj->GetClassID() == dlg.GetNewElement()->GetClassID())
					{
						dlg.GetNewElement()->Copy(pObj);
					}
					else
					{
						m_pCharArea->Delete(pObj);
						m_pCharArea->AddNewChild(dlg.GetNewElement());
					}
				}
				emit sig_CharChanged();
			}
			InitAreaData();
		}
	}
}

void QCharLibWidget::slot_ParaAddPoint( float fx,float fy )
{
	CCharElementTestLines* pLines = m_pCharArea->GetCharElementTestLines();
	CCharElementTestLine *pNew = new CCharElementTestLine;
	pNew->m_strType = _T("user");
	pNew->m_fPos = fx;
	pLines->AddNewChild(pNew);
}

void QCharLibWidget::slot_ParaPointChange( float fx,float fy )
{
	CPoint pt(fx,fy);
// 	int nRow = m_TestTable->currentRow();
// 	tmt_CurrInverseTimeTest *pTest = (tmt_CurrInverseTimeTest *)(m_oTmtTestMngr.m_pParasBuffer[nRow]);
// 
// 	if (pTest->m_nTestState)
// 	{
// 		pTest->m_oActionTimeParas.m_fFaultCur = fx;
// 		pTest->m_fCurrCal = fx;
// 
// 		CalCharYAxis(pTest);
// 
// 		m_TestTable->UpdateItem(nRow);
// 		m_ParaSetWidget->m_pActionTimeWidget->UpdateActTime();
// 	}	
}

CXDrawList* QCharLibWidget::GetDrawListByID(const CString& strID)
{
	CCharacteristic* pCChar = (CCharacteristic*)g_theTestCntrFrame->m_pCharacteristics->FindByID(strID);
	CCharacterArea* pArea = pCChar->GetCharacterArea();
	CXDrawList* pList = (CXDrawList*)pArea->GetDrawListRef();
	return pList;
}

void QCharLibWidget::DrawSearchPointLine(CPoint ptBegin, CPoint ptEnd, const CString& strCharLib)
{
	if(m_strLastCharaID.GetLength() && m_strLastCharaID != strCharLib)
	{
		//如果正在测试的特性曲线进行了切换
		CXDrawList* pList = GetDrawListByID(m_strLastCharaID);
		POS pos = pList->GetHeadPosition();
		CXDrawLine* pCurLine = NULL;
		while (pos)
		{
			CXDrawBase* pBase = (CXDrawBase*)pList->GetNext(pos);
			if(pBase->GetClassID() != DWCLASSID_CXDRAWLINE)
			{
				continue;
			}
			CXDrawLine* pLine = (CXDrawLine*)pBase;
			pLine->m_crForeColor = RGB(0, 255, 0);
		}
	}

	CXDrawList* pList = GetDrawListByID(strCharLib);
	POS pos = pList->GetHeadPosition();
	CXDrawLine* pCurLine = NULL;
	while (pos)
	{
		CXDrawBase* pBase = (CXDrawBase*)pList->GetNext(pos);

		if(pBase->GetClassID() != DWCLASSID_CXDRAWLINE)
		{
			continue;
		}

		CXDrawLine* pLine = (CXDrawLine*)pBase;
		//查找报文对应的线段
		if(pLine->m_fXb == ptBegin.x
			&& pLine->m_fYb == ptBegin.y
			&& pLine->m_fXe == ptEnd.x
			&& pLine->m_fYe == ptEnd.y)
		{
			pCurLine = pLine;
		}
		pLine->m_crForeColor = RGB(0, 255, 0);
	}
	pCurLine->m_crForeColor = RGB(255,255,0);
}

void QCharLibWidget::DrawSearchPointPoint(CPoint ptCur, const CString& strCharLib)
{
	if(m_strLastCharaID.GetLength() && m_strLastCharaID != strCharLib)
	{
		//如果正在测试的特性曲线进行了切换
		CXDrawList* pList = GetDrawListByID(m_strLastCharaID);
		CXDrawPoint* pt = (CXDrawPoint*)pList->FindByID("CurSearchPoint");
		pt->m_dwDrawStyle = 8;
		pt->m_strID = "";//将临时点转换为固定点
	}

	CXDrawList* pList = GetDrawListByID(strCharLib);
	CXDrawPoint* pBase = (CXDrawPoint*)pList->FindByID("CurSearchPoint");
	if(pBase)
	{
		pList->DeleteByID("CurSearchPoint");
	}

	CXDrawPoint* pt = pList->AddPoint(ptCur.x, ptCur.y);
	pt->m_strID = "CurSearchPoint";
	pt->m_crForeColor = RGB(255, 0, 0);
	pt->m_dwDrawStyle = 12;
}

void QCharLibWidget::SaveCharacteristicsFile()
{
	CString strFile;
	g_theTestCntrFrame->GetCharacteristicsFile(g_pTheSttTestApp->m_pTestMacroUI, strFile);
// 	CString strPath,strTemp;
// 	strTemp = g_pTheSttTestApp->m_pTestMacroUI->m_strCharlibFile;
// 	strTemp.Replace(_T("CharLib"), _T("Characteristics"));
// 	strPath = _P_GetConfigPath();
// 	strPath += strTemp;
	g_theTestCntrFrame->m_pCharacteristics->SaveXmlFile(strFile,CCharacteristicXmlRWKeys::g_pXmlKeys);
}
