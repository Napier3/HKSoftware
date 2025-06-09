#include "QGooseTable.h"
#include <QDateTime>
#include "WidgetDelegate.h"
#include <QtGui>
#include "../../../XLangResource_Native.h"

#pragma execution_character_set("utf-8")

QGooseTable::QGooseTable(QWidget* pparent):QTableWidget(pparent),m_pData(NULL)
{
	initUI();
	
	QTextCodec *codec = QTextCodec::codecForName("utf-8");    //获取系统编码
	QTextCodec::setCodecForCStrings(codec);

	initData();
}

QGooseTable::~QGooseTable(void)
{

}

void QGooseTable::setGooseData(CIecCfgGoutData *pCfgGoutData)
{
	m_pData = pCfgGoutData;
	initData();
}

void QGooseTable::enablechangedsignal(bool bchanged)
{
	if(bchanged){
		connect(this,SIGNAL(cellChanged( int,int)),SLOT(on_cellChanged( int , int )));
	}
	else{
		disconnect(SIGNAL(cellChanged( int,int)),this,SLOT(on_cellChanged( int , int )));
	}
}

void QGooseTable::initData()
{
	enablechangedsignal(false);
	if(m_pData== NULL){
		return;
	}
	clearContents();
	setRowCount(0);
	initDataHash();
	
	int nRow = m_pData->GetChannelNum();
	for(int i=0;i<nRow;i++)
	{
		InsertDataAtom(m_pData->GetCfgDataCh(i),i);
	}

	enablechangedsignal(true);
}

QString QGooseTable::getDataValue(CIecCfgGoutCh* pChannel)
{
	if(pChannel == NULL)
	{
		return "";
	}

	CString strDataType = pChannel->m_strDataType;
	CString strDefaultValue = pChannel->m_strDefaultValue;
	
	if(strDataType == _T("FLOAT32"))
	{
		float fValue = strDefaultValue.toFloat();
		QString str = QString::number(fValue,'f',3);
		strDefaultValue = str;
	}
	else if(strDataType == _T("Quality"))
	{
		unsigned int nValue = strDefaultValue.toUInt();
		QString str = QString::number(nValue,16);
		for(int i=str.size();i<4;i++){
			str.prepend("0");
		}
		str.prepend("0x");
		strDefaultValue = str;
	}
	else if(strDataType == _T("INT32"))
	{
		int nValue = strDefaultValue.toInt();
		QString str = QString::number(nValue,10);
		strDefaultValue = str;
	}
	else if(strDataType == _T("INT32U"))
	{
		int nValue = strDefaultValue.toUInt();
		QString str = QString::number(nValue,10);
		strDefaultValue = str;
	}

	pChannel->m_strDefaultValue = strDefaultValue;

	return strDefaultValue;
}

void QGooseTable::reverseValue(int nrow,int ncol)
{
	QTableWidgetItem  *pItem  = item(nrow,3);
	if(pItem == NULL){
		return;
	}

	int iChan = m_rowChannelHash.value(nrow);
	if(m_pData->GetCfgDataCh(iChan)== NULL){
		return;
	}
	QString str = pItem->text();
	if (str == tr("TRUE"))
	{
		pItem->setText(tr("FALSE"));
		if(m_rowdata.find(nrow) != m_rowdata.end()){
			((CIecCfgGoutCh*)m_rowdata[nrow])->m_strDefaultValue = tr("FALSE");
		}
	}
	else if (str==tr("FALSE"))
	{
		pItem->setText(tr("TRUE"));

		if(m_rowdata.find(nrow) != m_rowdata.end()){
			((CIecCfgGoutCh*)m_rowdata[nrow])->m_strDefaultValue = tr("TRUE");
		}
	}
	else if (str==tr("[00]"))
	{
		pItem->setText(tr("[11]"));
		if(m_rowdata.find(nrow) != m_rowdata.end()){
			((CIecCfgGoutCh*)m_rowdata[nrow])->m_strDefaultValue = tr("[11]");
		}
	}
	else if (str==tr("[01]"))
	{
		pItem->setText(tr("[10]"));
		if(m_rowdata.find(nrow) != m_rowdata.end()){
			((CIecCfgGoutCh*)m_rowdata[nrow])->m_strDefaultValue = tr("[10]");
		}
	}
	else if (str==tr("[10]"))
	{
		pItem->setText(tr("[01]"));
		if(m_rowdata.find(nrow) != m_rowdata.end()){
			((CIecCfgGoutCh*)m_rowdata[nrow])->m_strDefaultValue = tr("[01]");
		}
	}
	else if (str==tr("[11]"))
	{
		pItem->setText(tr("[00]"));
		if(m_rowdata.find(nrow) != m_rowdata.end()){
			((CIecCfgGoutCh*)m_rowdata[nrow])->m_strDefaultValue = tr("[00]");
		}
	}
}

void QGooseTable::InsertDataAtom(CIecCfgDataChBase* pChannel,int nIndex)
{	
	int nRow = rowCount();
	insertRow(nRow);

	CIecCfgGoutCh* pTempChannel = (CIecCfgGoutCh*)pChannel->Clone();

	QFontMetrics fontMetrics = QFontMetrics(font());
	int fontHeight = fontMetrics.height() + 10;

	QTableWidgetItem* pitem ;

	pitem = new QTableWidgetItem(pTempChannel->m_strName);
	pitem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	setItem(nRow,0,pitem);
	pitem = new QTableWidgetItem(getDataType(pTempChannel->m_strDataType));
	pitem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	setItem(nRow,1,pitem);

	QString strMap = pTempChannel->m_strAppChID;
	if(strMap.length()>4 && strMap.left(4)==_T("bout"))
	{
        strMap = strMap.replace("bout", /* tr("开出") */ g_sLangTxt_Native_BoutX);
	}
	else
	{
		strMap = _T("---");
	}
	pitem = new QTableWidgetItem(strMap);
	pitem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	setItem(nRow,2,pitem);

	pitem = new QTableWidgetItem(getDataValue(pTempChannel));
	pitem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	setItem(nRow,3,pitem);

	pitem = new QTableWidgetItem();
	pitem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

	CDataType* pGooseChDataType = CCfgDataMngrConstGlobal::FindIecRtdDataType(_T("GooseChDataType"));
	if (pGooseChDataType)
	{
        CDataTypeValue *pTypeValue1 = (CDataTypeValue *)pGooseChDataType->FindByName(/* _T("单点") */ g_sLangTxt_GOOSE_Single);
        CDataTypeValue *pTypeValue2 = (CDataTypeValue *)pGooseChDataType->FindByName(/* _T("双点") */ g_sLangTxt_GOOSE_Double);
        if (pTempChannel->m_strDataType == pTypeValue1->m_strID || pTempChannel->m_strDataType == pTypeValue2->m_strID)
		{
			pitem->setCheckState(Qt::Unchecked);
			pitem->setFlags((pitem->flags() & ~Qt::ItemIsEditable));
		}
		else
		{
			pitem->setFlags(Qt::NoItemFlags);
		}
	}
	else
	{
		pitem->setFlags(Qt::NoItemFlags);
	}

	setItem(nRow,4,pitem);
	setRowHeight(nRow,fontHeight);
}

void QGooseTable::initDataHash()
{
	m_rowdata.clear();
	m_rowChannelHash.clear();

	CIecCfgGoutCh* pTempChannel = NULL;
	int nsize = m_pData->GetChannelNum();
	int nrow = 0;
	for(int i=0;i<nsize;i++){
		pTempChannel = (CIecCfgGoutCh*)m_pData->GetCfgDataCh(i);
		m_rowChannelHash.insert(nrow,i);
		m_rowdata.insert(nrow,pTempChannel);
		nrow++;
	}
}

void QGooseTable::InsertDataAtomByIndex(CIecCfgDataChBase* pChannel,int nIndex,int nRow)
{
	CIecCfgGoutCh* pTempChannel = (CIecCfgGoutCh*)pChannel->Clone();

	insertRow(nRow);
	QTableWidgetItem* pitem ;
	pitem = new QTableWidgetItem(pTempChannel->m_strName);
	pitem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	setItem(nRow,0,pitem);

	pitem = new QTableWidgetItem(getDataType(pTempChannel->m_strDataType));
	pitem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	setItem(nRow,1,pitem);

	pitem = new QTableWidgetItem(pTempChannel->m_strAppChID);
	pitem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	setItem(nRow,2,pitem);

	pitem = new QTableWidgetItem(getDataValue(pTempChannel));
	pitem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	setItem(nRow,3,pitem);

	pitem = new QTableWidgetItem();
	pitem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

	CDataType* pGooseChDataType = CCfgDataMngrConstGlobal::FindIecRtdDataType(_T("GooseChDataType"));
	if (pGooseChDataType)
	{
        CDataTypeValue *pTypeValue1 = (CDataTypeValue *)pGooseChDataType->FindByName(/* _T("单点") */ g_sLangTxt_GOOSE_Single);
        CDataTypeValue *pTypeValue2 =(CDataTypeValue *)pGooseChDataType->FindByName(/* _T("双点") */ g_sLangTxt_GOOSE_Double);
        if (pTempChannel->m_strDataType == pTypeValue1->m_strID || pTempChannel->m_strDataType == pTypeValue2->m_strID)
		{
			pitem->setCheckState(Qt::Unchecked);
			pitem->setFlags((pitem->flags() & ~Qt::ItemIsEditable));
		}
		else
		{
			pitem->setFlags(Qt::NoItemFlags);
		}
	}
	else
	{
		pitem->setFlags(Qt::NoItemFlags);
	}

	setItem(nRow,4,pitem);
}

void QGooseTable::initUI()
{
	QHeaderView* pTop =horizontalHeader();
	pTop->setClickable(false);
	pTop->setMovable(false);
	QHeaderView* pLeft = verticalHeader();
	pLeft->setDefaultSectionSize(25);

	horizontalHeader()->setStretchLastSection(true); //设置充满表宽度
	setEditTriggers(QAbstractItemView::NoEditTriggers);
	setSelectionBehavior(QAbstractItemView::SelectRows);
	setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

	horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}"); //设置表头背景色
	QStringList headers;
    headers << /* tr("描述") */ g_sLangTxt_State_Description << /* tr("数据类型") */ g_sLangTxt_DataType
            << /* tr("映射") */ g_sLangTxt_Native_Maps << /* tr("数值") */ g_sLangTxt_Value
            << /* tr("取反") */ g_sLangTxt_Native_Reverse;
	setColumnCount(headers.size());
	setHorizontalHeaderLabels(headers);
	
	QFontMetrics fontMetrics = QFontMetrics(font());
    int nLabelWidth1 = fontMetrics.width(/* tr("描述") */ g_sLangTxt_State_Description) + 200;
    int nLabelWidth2 = fontMetrics.width(/* tr("数据类型") */ g_sLangTxt_DataType) + 80;
    int nLabelWidth3 = fontMetrics.width(/* tr("映射") */ g_sLangTxt_Native_Maps) + 80;
    int nLabelWidth4 = fontMetrics.width(/* tr("数值") */ g_sLangTxt_Value) + 80;
    int nLabelWidth5 = fontMetrics.width(/* tr("取反") */ g_sLangTxt_Native_Reverse) + 50;

	setColumnWidth(0,nLabelWidth1);
	setColumnWidth(1,nLabelWidth2);
	setColumnWidth(2,nLabelWidth3);
	setColumnWidth(3,nLabelWidth4);
	setColumnWidth(4,nLabelWidth5);

	setEditTriggers(QAbstractItemView::DoubleClicked);
	CComboBoxDelegate* comboBox = new CComboBoxDelegate(GOPUB_CHAN);
	setItemDelegateForColumn(1,comboBox);

	comboBox = new CComboBoxDelegate(GOPUB_CHAN);
	setItemDelegateForColumn(2,comboBox);

	CComplexDelegate *complex = new CComplexDelegate(GOPUB_CHAN);
	setItemDelegateForColumn(3, complex);

	connect(this,SIGNAL(sigUpdateData()),this,SLOT(on_updateData()));
}

QString QGooseTable::getDataType(QString strDataType)
{
	QString strDataTypeName = ""; 

	CDataType* pGooseChDataType = CCfgDataMngrConstGlobal::FindIecRtdDataType(_T("GooseChDataType"));
	if (pGooseChDataType)
	{
		CDataTypeValue* pTypeValue = (CDataTypeValue*)pGooseChDataType->FindByID(strDataType);
		if (pTypeValue)
		{
			strDataTypeName = pTypeValue->m_strName;
		}
	}

	return strDataTypeName;
}

void QGooseTable::chanelTypeChanged(int nrow,int ncol)
{
	if (!m_rowChannelHash.contains(nrow))
		return;

	int iChan = m_rowChannelHash.value(nrow);
	int iparent = -1;
	if(m_rowChannelHash.find(nrow-1) != m_rowChannelHash.end()){
		iparent= m_rowChannelHash.value(nrow-1);
	}

	CIecCfgGoutCh* pTempChannel = (CIecCfgGoutCh*)m_pData->GetCfgDataCh(iChan);
	QString strType = item(nrow,ncol)->text();

	CDataType* pGooseChDataType = CCfgDataMngrConstGlobal::FindIecRtdDataType(_T("GooseChDataType"));
	if (pGooseChDataType)
	{
		CDataTypeValue* pDataTypeValue = NULL;
		POS pos = pGooseChDataType->GetHeadPosition();
		while(pos)
		{
			pDataTypeValue = (CDataTypeValue*)pGooseChDataType->GetNext(pos);
			if (pDataTypeValue->m_strName == strType)
			{
				pTempChannel->m_strDataType = pDataTypeValue->m_strID;
			}
		}
	}

	initData();
}

void QGooseTable::OnChanDataChanged( QTableWidgetItem * current)
{
	int nRow = current->row();
	if (!m_rowChannelHash.contains(current->row()))
		return;
	int iChan = m_rowChannelHash.value(current->row());

	CIecCfgGoutCh* pTempChannel = (CIecCfgGoutCh*)m_pData->GetCfgDataCh(iChan);
	if (current->column() == 0)
	{
		pTempChannel->m_strName = item(current->row(),current->column())->text();
	}

	if (current->column() == 2)
	{
		QString strMap = current->text();
		strMap = strMap.replace(tr("开出"),"bout");
		pTempChannel->m_strAppChID = strMap;
	}
	else if (current->column() == 3)
	{
		pTempChannel = (CIecCfgGoutCh*)m_rowdata.value(nRow);
		if(pTempChannel)
		{
			pTempChannel->m_strDefaultValue = current->text();
		}

		Q_EMIT sigdatachanged();
		
	}
	else if (current->column() == 4)
	{
		reverseValue(current->row(),current->column());
	}
}

void QGooseTable::on_cellChanged(int nrow,int ncol)
{
	QTableWidgetItem* pitem = item(nrow,ncol);
	if(pitem == NULL){
		return;
	}

	OnChanDataChanged(pitem);
}

void  QGooseTable::on_updateData()
{
	initData();
}

void QGooseTable::setEnableChangeValue(bool bEdit)
{
	disconnect(SIGNAL(cellChanged( int,int)),this,SLOT(on_cellChanged( int , int )));
	int nRow = rowCount();
	for(int i=0;i<nRow;i++){
		if(item(i,1)!= NULL&&item(i,2)!= NULL)
			if(!bEdit){
				item(i,3)->setFlags((item(i,3)->flags() & ~Qt::ItemIsEditable));
				if (item(i,4)!= NULL)
				{
					item(i,4)->setFlags((item(i,4)->flags() & ~Qt::ItemIsUserCheckable));
				}
				
			}
			else{
				item(i,3)->setFlags((item(i,3)->flags() | Qt::ItemIsEditable));
				if (item(i,4)!= NULL)
				{
					item(i,4)->setFlags((item(i,4)->flags() | Qt::ItemIsUserCheckable));
				}
			}
	}
	connect(this,SIGNAL(cellChanged( int,int)),SLOT(on_cellChanged( int , int )));
}

void QGooseTable::setEnableChangedType(bool bEdit)
{
	disconnect(SIGNAL(cellChanged( int,int)),this,SLOT(on_cellChanged( int , int )));
	int nRow = rowCount();
	for(int i=0;i<nRow;i++){
		if(item(i,1)!= NULL&&item(i,2)!= NULL)
		if(!bEdit){
			item(i,1)->setFlags((item(i,1)->flags() & ~Qt::ItemIsEditable));
			item(i,2)->setFlags((item(i,2)->flags() & ~Qt::ItemIsEditable));
		}
		else{
			item(i,1)->setFlags((item(i,1)->flags() | Qt::ItemIsEditable));
			item(i,2)->setFlags((item(i,2)->flags() | Qt::ItemIsEditable));
		}
		
	}
	connect(this,SIGNAL(cellChanged( int,int)),SLOT(on_cellChanged( int , int )));
}