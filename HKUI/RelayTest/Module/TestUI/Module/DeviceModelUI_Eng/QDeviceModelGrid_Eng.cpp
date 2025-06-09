#include "QDeviceModelGrid_Eng.h"

QDeviceModelGrid_Eng_CheckBox::QDeviceModelGrid_Eng_CheckBox(QWidget *parent):QWidget(parent)
{
//    m_bSingleClick = FALSE;
    m_bIsChecked = FALSE;
    m_nRowIndex = -1;
    m_nColIndex = -1;
    InitStyleSheet(); // 初始化样式
}

QDeviceModelGrid_Eng_CheckBox::~QDeviceModelGrid_Eng_CheckBox()
{

}

void QDeviceModelGrid_Eng_CheckBox::SetChecked(BOOL bIsChecked)
{
    m_bIsChecked = bIsChecked;
    update(); // 触发重绘
}

BOOL QDeviceModelGrid_Eng_CheckBox::IsChecked() const
{
    return m_bIsChecked;
}

void QDeviceModelGrid_Eng_CheckBox::SetEditable(BOOL bEditable)
{
    setEnabled(bEditable); // 控制勾选框是否可点击
}

void QDeviceModelGrid_Eng_CheckBox::SetRowIndexAndColIndex(const int &nRow, const int &nCol)
{
    if(nRow < 0 || nCol < 0)
    {
        return;
    }

    m_nRowIndex = nRow;
    m_nColIndex = nCol;
}

void QDeviceModelGrid_Eng_CheckBox::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QRect rect = this->rect();
    QPoint pt = rect.center();

    if (m_bIsChecked)
    {
        pt -= QPoint(m_oSelectedPixmap.width() / 2, m_oSelectedPixmap.height() / 2);
        painter.drawPixmap(pt, m_oSelectedPixmap);
    }
    else
    {
        pt -= QPoint(m_oUnselectedPixmap.width() / 2, m_oUnselectedPixmap.height() / 2);
        painter.drawPixmap(pt, m_oUnselectedPixmap);
    }
}

void QDeviceModelGrid_Eng_CheckBox::mousePressEvent(QMouseEvent *mouseEvent)
{
    if (Qt::LeftButton == mouseEvent->button())
    {
        SetChecked(!m_bIsChecked); // 切换状态
        emit CheckBoxStateChanged(m_bIsChecked); // 发出状态改变信号

        // 获取 QTableWidget
        QDeviceModelGrid_Eng *pDeviceModelGrid_Eng = qobject_cast<QDeviceModelGrid_Eng *>(this->parentWidget()->parentWidget());

        ASSERT(pDeviceModelGrid_Eng);

        // 触发 cellChanged 信号
        pDeviceModelGrid_Eng->slot_CellChanged(m_nRowIndex,m_nColIndex);

        // 触发 currentCellChanged 信号
        emit CheckBox_LeftClicked(m_nRowIndex, m_nColIndex);
    }
//    if (Qt::LeftButton == mouseEvent->button())
//    {
//       m_bSingleClick = TRUE; // 标记为单击
//       m_timer.start(QDEVICEMODELGRID_ENG_CHECKkBOX_SINGLE_CLICK_TIMEOUT, this); // 启动定时器
//    }
}

void QDeviceModelGrid_Eng_CheckBox::mouseDoubleClickEvent(QMouseEvent *mouseEvent)
{
    if (Qt::LeftButton == mouseEvent->button())
    {
        emit CheckBox_LeftClicked(m_nRowIndex, m_nColIndex);
        // 获取 QTableWidget
        QDeviceModelGrid_Eng *pDeviceModelGrid_Eng = qobject_cast<QDeviceModelGrid_Eng *>(this->parentWidget()->parentWidget());

        ASSERT(pDeviceModelGrid_Eng);

        pDeviceModelGrid_Eng->slot_cellDoubleClicked(m_nRowIndex,m_nColIndex);
    }
}

//void QDeviceModelGrid_Eng_CheckBox::timerEvent(QTimerEvent *event)
//{
//    if (event->timerId() == m_timer.timerId())
//    {
//       if (m_bSingleClick)
//    {
//           SetChecked(!m_bIsChecked); // 切换状态
//           emit CheckBoxStateChanged(m_bIsChecked); // 发出状态改变信号

//        // 获取 QTableWidget
//        QDeviceModelGrid_Eng *pDeviceModelGrid_Eng = qobject_cast<QDeviceModelGrid_Eng *>(this->parentWidget()->parentWidget());

//        ASSERT(pDeviceModelGrid_Eng);

////#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
////            // 触发 cellChanged 信号
////            emit pDeviceModelGrid_Eng->cellChanged(m_nRowIndex, m_nColIndex);
////#endif
//            pDeviceModelGrid_Eng->slot_CellChanged(m_nRowIndex,m_nColIndex);
//           // 触发 currentCellChanged 信号
//           emit CheckBox_LeftClicked(m_nRowIndex, m_nColIndex);
//       }
//       m_timer.stop(); // 停止定时器
//    }
//}

void QDeviceModelGrid_Eng_CheckBox::InitStyleSheet()
{
    CString strSelectPath,strUnSelectPath;
#ifdef _PSX_QT_WINDOWS_
    strSelectPath =  _P_GetResourcePath();
    strSelectPath += _T("checked.png");
    strUnSelectPath =  _P_GetResourcePath();
    strUnSelectPath += _T("unchecked.png");
#else
    strSelectPath =  ":/ctrls/images/checked.png";
    strUnSelectPath += ":/ctrls/images/unchecked.png";
#endif
    m_oSelectedPixmap.load(strSelectPath);
    m_oSelectedPixmap.scaled(20,20);
    m_oUnselectedPixmap.load(strUnSelectPath);
    m_oUnselectedPixmap.scaled(20,20);
}

QDeviceModelGrid_Eng_ComBoxDelegBase::QDeviceModelGrid_Eng_ComBoxDelegBase(QObject *parent):QExBaseListComBoxDelegBase(parent)
{

}

QDeviceModelGrid_Eng_ComBoxDelegBase::~QDeviceModelGrid_Eng_ComBoxDelegBase()
{

}

QWidget *QDeviceModelGrid_Eng_ComBoxDelegBase::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (!m_bEditable)
    {
        return NULL;
    }

    QGV_ITEM* pCurItem = GetCurrItem(index);

    if (pCurItem == NULL)
    {
        return NULL;
    }

    if (pCurItem->lParam == 0)
    {
        return NULL;
    }

    PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCurItem->lParam;
    CExBaseList* pList = pVCellData->pExBaseList;

    if (pList != NULL)
    {
        QScrollComboBox *pComboBox = new QScrollComboBox(parent);
#ifdef _PSX_QT_LINUX_//linux下需要特殊处理下
        pComboBox->SetIgnoreFirstHidePopup(true);
#endif
        return pComboBox;
    }
    else
    {
        return new QLineEdit(parent);
    }
}

void QDeviceModelGrid_Eng_ComBoxDelegBase::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if (!m_bEditable)
    {
        return;
    }

    QGV_ITEM* pCurItem = GetCurrItem(index);

    if (pCurItem == NULL)
    {
        return;
    }

    if (pCurItem->lParam == 0)
    {
        return;
    }

    PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCurItem->lParam;
    ASSERT(pVCellData->pExBaseList != NULL);
    CExBaseList *pList = pVCellData->pExBaseList;

    if (pList != NULL)
    {
        QScrollComboBox *pComboBox = qobject_cast<QScrollComboBox *>(editor);
        pComboBox->clear();
        int nCurIndex = -1,nIndex = 0;
        CString strItem = index.model()->data(index,Qt::EditRole).toString();
        CExBaseObject *pObj = NULL;
        POS pos = pList->GetHeadPosition();

        while (pos)
        {
            pObj = pList->GetNext(pos);

            if (pObj->m_strName == strItem)
            {
                nCurIndex = nIndex;
            }

            pComboBox->addItem(pObj->m_strName);
            nIndex++;
        }

        if (nCurIndex>=0)
        {
            pComboBox->setCurrentIndex(nCurIndex);

            if (pComboBox->isHidden())
            {
                pComboBox->showPopup();
            }
        }
    }
    else
    {
        QLineEdit *lineEdit =  static_cast <QLineEdit*>(editor);
        lineEdit->setText(index.model()->data(index, Qt::EditRole).toString());
    }
}

void QDeviceModelGrid_Eng_ComBoxDelegBase::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    if (!m_bEditable)
    {
        return;
    }

    QGV_ITEM* pCurItem = GetCurrItem(index);

    if (pCurItem == NULL)
    {
        return;
    }

    if (pCurItem->lParam == 0)
    {
        return;
    }

    PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCurItem->lParam;

    if (pVCellData->pExBaseList != NULL)
    {
        QComboBox *comboBox = qobject_cast<QComboBox *>(editor);
        model->setData(index,comboBox->currentText(),Qt::EditRole);
    }
    else
    {
        QLineEdit *pLineEdit = qobject_cast<QLineEdit *>(editor);
        QString text = pLineEdit->text();
        model->setData(index, text, Qt::EditRole);
//        *pVCellData->pString = text;
    }

    if (pCurItem->m_pEditFunc != NULL)
    {
        QExBaseListGridBase *pExBaseListGridBase = qobject_cast<QExBaseListGridBase *>(parent());
        pCurItem->m_pEditFunc(index.row(),index.column(),pCurItem,pExBaseListGridBase);
    }
}

QDeviceModelGrid_Eng::QDeviceModelGrid_Eng(QWidget *pparent):QExBaseListGridBase(pparent)
{
    m_nTitleType = XRIO_DEVICE_MODEL_GRID_TITLE_TYPE_NULL;
    m_pCheckBoxDelegateBase = NULL;
    m_pRefValueComBoxDeleBase = NULL;
    m_pValueComBoxDeleBase = NULL;
    InitConnect();
}

QDeviceModelGrid_Eng::~QDeviceModelGrid_Eng()
{
    FreeCellListAndWidget();
}

void QDeviceModelGrid_Eng::InitGrid()
{
//    m_pCheckBoxDelegateBase = new QExBaseListCheckBoxDelegate(this);
//    setItemDelegateForColumn(XRIO_PARAMETER_COL_STATE, m_pCheckBoxDelegateBase);

    m_pRefValueComBoxDeleBase = new QDeviceModelGrid_Eng_ComBoxDelegBase(this);
    setItemDelegateForColumn(XRIO_PARAMETER_COL_REFVALUE, m_pRefValueComBoxDeleBase);

    m_pValueComBoxDeleBase = new QDeviceModelGrid_Eng_ComBoxDelegBase(this);
    setItemDelegateForColumn(XRIO_PARAMETER_COL_VALUE, m_pValueComBoxDeleBase);

    QExBaseListGridBase::InitGrid();
}

void QDeviceModelGrid_Eng::UpdateTitle(long nTitleType)
{
    if (nTitleType == m_nTitleType)
    {
        return;
    }

    m_nTitleType = nTitleType;
    InitGrid();
}

BOOL QDeviceModelGrid_Eng::GetCurrObjIsEnabled(CExBaseObject *pObj, const CString &strID)
{
    CDvmValue *pEnabled= (CDvmValue*)GetAttrObj(pObj,strID);
    if(pEnabled != NULL)
    {
        CString strIsEnabled = pEnabled->m_strValue;
        return strIsEnabled == _T("true");
    }
    return TRUE;
}

void QDeviceModelGrid_Eng::GetDvmDataMinAndMax_DataType_Real(CDvmData *pDvmData, double &dMinValue, double &dMaxValue,CString &strMinValue,CString &strMaxValue)
{
    ASSERT(pDvmData);
    if(pDvmData == NULL)
    {
        return;
    }
    dMinValue = pDvmData->m_strMin.toDouble();
    dMaxValue = pDvmData->m_strMax.toDouble();
    strMinValue = pDvmData->m_strMin;
    strMaxValue = pDvmData->m_strMax;
}

void QDeviceModelGrid_Eng::GetDvmValueMinAndMax_DataType_Real(CDvmValue *pDvmValue, double &dMinValue, double &dMaxValue,CString &strMinValue,CString &strMaxValue)
{
    ASSERT(pDvmValue);
    if(pDvmValue == NULL)
    {
        return;
    }

    CDvmValue *pDvmValueMin = (CDvmValue*)GetAttrObj(pDvmValue,XRIO_DEVICE_MODEL_ID_MinValue);
    ASSERT(pDvmValueMin);

    if(pDvmValueMin != NULL)
    {
        dMinValue = pDvmValueMin->m_strValue.toDouble();
        strMinValue = pDvmValueMin->m_strValue;
    }

    CDvmValue *pDvmValueMax = (CDvmValue*)GetAttrObj(pDvmValue,XRIO_DEVICE_MODEL_ID_MaxValue);
    ASSERT(pDvmValueMax);

    if(pDvmValueMax != NULL)
    {
        dMaxValue = pDvmValueMax->m_strValue.toDouble();
        strMaxValue = pDvmValueMax->m_strValue;
    }
}

void QDeviceModelGrid_Eng::GetDvmDataMinAndMax_DataType_Integer(CDvmData *pDvmData, int &nMinValue, int &nMaxValue, CString &strMinValue, CString &strMaxValue)
{
    ASSERT(pDvmData);
    if(pDvmData == NULL)
    {
        return;
    }

    nMinValue = pDvmData->m_strMin.toInt();
    nMaxValue = pDvmData->m_strMax.toInt();
    strMinValue = pDvmData->m_strMin;
    strMaxValue = pDvmData->m_strMax;
}

void QDeviceModelGrid_Eng::GetDvmValueMinAndMax_DataType_Integer(CDvmValue *pDvmValue, int &nMinValue, int &nMaxValue, CString &strMinValue, CString &strMaxValue)
{
    ASSERT(pDvmValue);
    if(pDvmValue == NULL)
    {
        return;
    }

    CDvmValue *pDvmValueMin = (CDvmValue*)GetAttrObj(pDvmValue,XRIO_DEVICE_MODEL_ID_MinValue);
    ASSERT(pDvmValueMin);
    if(pDvmValueMin != NULL)
    {
        nMinValue = pDvmValueMin->m_strValue.toInt();
        strMinValue = pDvmValueMin->m_strValue;
    }

    CDvmValue *pDvmValueMax = (CDvmValue*)GetAttrObj(pDvmValue,XRIO_DEVICE_MODEL_ID_MaxValue);
    ASSERT(pDvmValueMax);
    if(pDvmValueMax != NULL)
    {
        nMaxValue = pDvmValueMax->m_strValue.toInt();
        strMaxValue = pDvmValueMax->m_strValue;
    }
}

BOOL QDeviceModelGrid_Eng::ModifyOwnAttrVal(CString &strOwnValue, const CString &strNewValue)
{
    strOwnValue = strNewValue;
    return TRUE;
}

BOOL QDeviceModelGrid_Eng::ModifyAddAttrVal(CExBaseList *pList, const CString &strID, const CString &strNewValue)
{
    CDvmValue *pDvmAttrValue = (CDvmValue*)GetAttrObj(pList,strID);
    if(pDvmAttrValue != NULL)
    {
        pDvmAttrValue->m_strValue = strNewValue;
        return TRUE;
    }
    return FALSE;
}

BOOL QDeviceModelGrid_Eng::ModifyDvmData_AttrVal(CDvmData *pDvmData, int nCol ,const CString& strNewValue)
{
    if(XRIO_PARAMETER_COL_NAME == nCol)
    {
        return ModifyOwnAttrVal(pDvmData->m_strName,strNewValue);
    }
    else if(XRIO_PARAMETER_COL_VALUE == nCol)
    {
        return ModifyOwnAttrVal(pDvmData->m_strValue,strNewValue);
    }
    else if(XRIO_PARAMETER_COL_UNIT == nCol)
    {
        return ModifyOwnAttrVal(pDvmData->m_strUnit,strNewValue);
    }
    else if(XRIO_PARAMETER_COL_MIN == nCol)
    {
        return ModifyOwnAttrVal(pDvmData->m_strMin,strNewValue);
    }
    else if(XRIO_PARAMETER_COL_MAX == nCol)
    {
        return ModifyOwnAttrVal(pDvmData->m_strMax,strNewValue);
    }
    else if(XRIO_PARAMETER_COL_FOREIGNID == nCol)
    {
        return ModifyAddAttrVal(pDvmData,XRIO_DEVICE_MODEL_ID_ForeignId,strNewValue);
    }
    else if(XRIO_PARAMETER_COL_DESCRIPTION == nCol)
    {
        return ModifyAddAttrVal(pDvmData,XRIO_DEVICE_MODEL_ID_Description,strNewValue);
    }
    else if(XRIO_PARAMETER_COL_REFVALUE == nCol)
    {
        return ModifyAddAttrVal(pDvmData,XRIO_DEVICE_MODEL_ID_RefValue,strNewValue);
    }
    else if(XRIO_PARAMETER_COL_VALUEFORMULA == nCol)
    {
        return ModifyAddAttrVal(pDvmData,XRIO_DEVICE_MODEL_ID_ValueFormula,strNewValue);
    }
    else
    {
        return FALSE;
    }
}

BOOL QDeviceModelGrid_Eng::ModifyDvmValue_AttrVal(CDvmValue *pDvmValue, int nCol ,const CString& strNewValue)
{
    if(XRIO_PARAMETER_COL_NAME == nCol)
    {
        return ModifyOwnAttrVal(pDvmValue->m_strName,strNewValue);
    }
    else if(XRIO_PARAMETER_COL_VALUE == nCol )
    {
        return ModifyOwnAttrVal(pDvmValue->m_strValue,strNewValue);
    }
    else if(XRIO_PARAMETER_COL_UNIT == nCol)
    {
        return ModifyAddAttrVal(pDvmValue,XRIO_DEVICE_MODEL_ID_ForeignId,strNewValue);
    }
    else if(XRIO_PARAMETER_COL_MIN == nCol)
    {
        return ModifyAddAttrVal(pDvmValue,XRIO_DEVICE_MODEL_ID_ForeignId,strNewValue);
    }
    else if(XRIO_PARAMETER_COL_MAX == nCol)
    {
        return ModifyAddAttrVal(pDvmValue,XRIO_DEVICE_MODEL_ID_ForeignId,strNewValue);
    }
    else if(XRIO_PARAMETER_COL_FOREIGNID == nCol)
    {
        return ModifyAddAttrVal(pDvmValue,XRIO_DEVICE_MODEL_ID_ForeignId,strNewValue);
    }
    else if(XRIO_PARAMETER_COL_DESCRIPTION == nCol)
    {
        return ModifyAddAttrVal(pDvmValue,XRIO_DEVICE_MODEL_ID_Description,strNewValue);
    }
    else if(XRIO_PARAMETER_COL_REFVALUE == nCol)
    {
        return ModifyAddAttrVal(pDvmValue,XRIO_DEVICE_MODEL_ID_RefValue,strNewValue);
    }
    else if(XRIO_PARAMETER_COL_VALUEFORMULA == nCol)
    {
        return ModifyAddAttrVal(pDvmValue,XRIO_DEVICE_MODEL_ID_ValueFormula,strNewValue);
    }
    else
    {
        return FALSE;
    }
}

BOOL QDeviceModelGrid_Eng::ShowDvmValue_AddAttrValue_String(CExBaseObject *pObj, int &nRow, int nCol, const CString &strID, BOOL bCanEdit)
{
    CDvmValue *pDvmValue = (CDvmValue*)GetAttrObj(pObj,strID);
    if(pDvmValue != NULL)
    {
        if(bCanEdit)
        {
            Show_String(pObj, nRow, nCol, &pDvmValue->m_strValue,EndEditCell_String);
        }
        else
        {
//            Show_StaticString(pObj, nRow, nCol, &pDvmValue->m_strValue);
            //默认情况处理时修改单位，最大值，最小值为空。
            if(XRIO_PARAMETER_COL_MIN == nCol || XRIO_PARAMETER_COL_MAX == nCol || XRIO_PARAMETER_COL_UNIT == nCol)
            {
                pDvmValue->m_strValue = pDvmValue->m_strValue.isEmpty()?pDvmValue->m_strValue:XRIO_DEVICE_MODEL_DEFAULTVALUE;
                Show_StaticString(pObj, nRow, nCol, &pDvmValue->m_strValue);
            }
            else
            {
                Show_StaticString(pObj, nRow, nCol, &pDvmValue->m_strValue);
            }
        }
    }
    else
    {
        if(bCanEdit)
        {
            ASSERT(FALSE);
//            CString *pStrTempDefValue = new CString(XRIO_DEVICE_MODEL_DEFAULTVALUE);
//            Show_String(pObj, nRow, nCol, pStrTempDefValue,NULL);
        }
        else
        {
            Show_StaticString(pObj, nRow, nCol, XRIO_DEVICE_MODEL_DEFAULTVALUE);
        }

    }
    return TRUE;
}

BOOL QDeviceModelGrid_Eng::ShowDvmValue_AddAttrValue_DoubleString(CExBaseObject *pObj, int &nRow, int nCol, const CString &strID, long nPrecision, BOOL bCanEdit)
{
    CDvmValue *pDvmValue = (CDvmValue*)GetAttrObj(pObj,strID);
    if(pDvmValue != NULL)
    {
        Show_Double(pObj,nRow,nCol,nPrecision,&pDvmValue->m_strValue,bCanEdit,EndEditCell_DoubleString,TRUE);
//        if(XRIO_PARAMETER_COL_REFVALUE == nCol)
//        {
//            Show_Double(pObj,nRow,nCol,nPrecision,&pDvmValue->m_strValue,bCanEdit,EndEditCell_DoubleString,TRUE);
//        }
//        else if(XRIO_PARAMETER_COL_MIN == nCol)
//        {
//            pDvmValue->m_strValue = pDvmValue->m_strValue.isEmpty()?XRIO_DEVICE_MODEL_NEGATIVE_INF_STRING:pDvmValue->m_strValue;
//            Show_Double(pObj,nRow,nCol,nPrecision,&pDvmValue->m_strValue,bCanEdit,EndEditCell_DoubleString,TRUE);
//        }
//        else if(XRIO_PARAMETER_COL_MAX == nCol)
//        {
//            pDvmValue->m_strValue = pDvmValue->m_strValue.isEmpty()?XRIO_DEVICE_MODEL_POSITIVE_INF_STRING:pDvmValue->m_strValue;
//            Show_Double(pObj,nRow,nCol,nPrecision,&pDvmValue->m_strValue,bCanEdit,EndEditCell_DoubleString,TRUE);
//        }
    }
    else
    {
        ASSERT(FALSE);
//        CString *pStrTempDefValue = new CString(XRIO_DEVICE_MODEL_DEFAULTVALUE);
//        Show_Double(pObj,nRow,nCol,nPrecision,pStrTempDefValue,bCanEdit,NULL,TRUE);
    }
    return TRUE;
}

BOOL QDeviceModelGrid_Eng::ShowDvmValue_AddAttrValue_IntString(CExBaseObject *pObj, int &nRow, int nCol, const CString &strID, BOOL bCanEdit)
{
    CDvmValue *pDvmValue = (CDvmValue*)GetAttrObj(pObj,strID);
    if(pDvmValue != NULL)
    {
        Show_Int(pObj,nRow,nCol,&pDvmValue->m_strValue,bCanEdit,EndEditCell_IntString);
//        if(XRIO_PARAMETER_COL_REFVALUE == nCol)
//        {
//            Show_Int(pObj,nRow,nCol,&pDvmValue->m_strValue,bCanEdit,EndEditCell_IntString);
//        }
//        else if(XRIO_PARAMETER_COL_MIN == nCol)
//        {
//            pDvmValue->m_strValue = pDvmValue->m_strValue.isEmpty()?XRIO_DEVICE_MODEL_INT_MIN:pDvmValue->m_strValue;
//            Show_Int(pObj,nRow,nCol,&pDvmValue->m_strValue,bCanEdit,EndEditCell_IntString);
//        }
//        else if(XRIO_PARAMETER_COL_MAX == nCol)
//        {
//            pDvmValue->m_strValue = pDvmValue->m_strValue.isEmpty()?XRIO_DEVICE_MODEL_INT_MAX:pDvmValue->m_strValue;
//            Show_Int(pObj,nRow,nCol,&pDvmValue->m_strValue,bCanEdit,EndEditCell_IntString);
//        }
    }
    else
    {
        ASSERT(FALSE);
//        CString *pStrTempDefValue = new CString(XRIO_DEVICE_MODEL_DEFAULTVALUE);
//        Show_Int(pObj,nRow,nCol,pStrTempDefValue,bCanEdit,NULL);
    }
    return TRUE;
}

BOOL QDeviceModelGrid_Eng::ShowDvmData(CDvmData *pDvmData, int &nRow)
{
    if(XRIO_CUSTOM_PARAMETER_DATATYPE_STRING == pDvmData->m_strDataType)
    {
        return ShowDvmData_DataType_String(pDvmData,nRow);
    }
    else if(XRIO_CUSTOM_PARAMETER_DATATYPE_REAL == pDvmData->m_strDataType)
    {
        return ShowDvmData_DataType_Real(pDvmData,nRow);
    }
    else if(XRIO_CUSTOM_PARAMETER_DATATYPE_ENUMERATION == pDvmData->m_strDataType)
    {
        return ShowDvmData_DataType_Enumeration(pDvmData,nRow);
    }
    else if(XRIO_CUSTOM_PARAMETER_DATATYPE_INTEGER == pDvmData->m_strDataType)
    {
        return ShowDvmData_DataType_Integer(pDvmData,nRow);
    }
    else if(XRIO_CUSTOM_PARAMETER_DATATYPE_BOOLEAN == pDvmData->m_strDataType)
    {
        return ShowDvmData_DataType_Boolean(pDvmData,nRow);
    }
    else
    {
        return ShowDvmData_DataType_Default(pDvmData,nRow);
    }
}

BOOL QDeviceModelGrid_Eng::ShowDvmData_DataType_String(CDvmData *pDvmData, int &nRow)
{
    ASSERT(pDvmData);
    if(pDvmData == NULL)
    {
        return FALSE;
    }
//    if(!GetCurrObjIsEnabled(pDvmData,_T("")));//待替换的Enable宏
//    long nIsEnabled = XRIO_DEVICE_MODEL_CHECK_ENABLED;
//    else
//    long nIsEnabled = XRIO_DEVICE_MODEL_CHECK_DISENABLED;

//    QExBaseListGridBase::Show_Check(pDvmData, nRow, XRIO_PARAMETER_COL_STATE, &nIsEnabled,NULL,FALSE);//状态
    Show_String(pDvmData, nRow, XRIO_PARAMETER_COL_NAME, &pDvmData->m_strName,EndEditCell_String);
    Show_StaticString(pDvmData, nRow, XRIO_PARAMETER_COL_ID, &pDvmData->m_strID);
    Show_StaticString(pDvmData, nRow, XRIO_PARAMETER_COL_DATATYPE, &pDvmData->m_strDataType);

    //字符串类型的单位，最大值，最小值一定为空而且不可以修改。
//    pDvmData->m_strUnit = pDvmData->m_strUnit.isEmpty()?pDvmData->m_strUnit:XRIO_DEVICE_MODEL_DEFAULTVALUE;
    Show_StaticString(pDvmData, nRow, XRIO_PARAMETER_COL_UNIT, &pDvmData->m_strUnit);

//    pDvmData->m_strMin = pDvmData->m_strMin.isEmpty()?pDvmData->m_strMin:XRIO_DEVICE_MODEL_DEFAULTVALUE;
    Show_StaticString(pDvmData, nRow, XRIO_PARAMETER_COL_MIN, &pDvmData->m_strMin);

//    pDvmData->m_strMax = pDvmData->m_strMax.isEmpty()?pDvmData->m_strMax:XRIO_DEVICE_MODEL_DEFAULTVALUE;
    Show_StaticString(pDvmData, nRow, XRIO_PARAMETER_COL_MAX, &pDvmData->m_strMax);

    ShowDvmValue_AddAttrValue_String(pDvmData,nRow,XRIO_PARAMETER_COL_REFVALUE,XRIO_DEVICE_MODEL_ID_RefValue);
    ShowDvmValue_AddAttrValue_String(pDvmData,nRow,XRIO_PARAMETER_COL_FOREIGNID,XRIO_DEVICE_MODEL_ID_ForeignId);
    ShowDvmValue_AddAttrValue_String(pDvmData,nRow,XRIO_PARAMETER_COL_DESCRIPTION,XRIO_DEVICE_MODEL_ID_Description);
    ShowDvmValue_AddAttrValue_String(pDvmData,nRow,XRIO_PARAMETER_COL_VALUEFORMULA,XRIO_DEVICE_MODEL_ID_ValueFormula);
    //String类型下不存在多个枚举值。
    CDvmValue *pDvmValue = (CDvmValue*)GetAttrObj(pDvmData,XRIO_DEVICE_MODEL_ID_ValueFormula);
    if(pDvmValue != NULL)
    {
        //公式不为空值就无法修改，否则可以修改。
        if(pDvmValue->m_strValue.isEmpty())
        {
            Show_String(pDvmData, nRow, XRIO_PARAMETER_COL_VALUE, &pDvmData->m_strValue,EndEditCell_String);
        }
        else
        {
            Show_StaticString(pDvmData, nRow, XRIO_PARAMETER_COL_VALUE, &pDvmData->m_strValue);
        }
    }
    return TRUE;
}

BOOL QDeviceModelGrid_Eng::ShowDvmData_DataType_Real(CDvmData *pDvmData, int &nRow)
{
    ASSERT(pDvmData);
    if(pDvmData == NULL)
    {
        return FALSE;
    }
//    if(!GetCurrObjIsEnabled(pDvmData,_T("")));//待替换的Enable宏
//    long nIsEnabled = XRIO_DEVICE_MODEL_CHECK_ENABLED;
//    else
//    long nIsEnabled = XRIO_DEVICE_MODEL_CHECK_DISENABLED;

//    QExBaseListGridBase::Show_Check(pDvmData, nRow, XRIO_PARAMETER_COL_STATE, &nIsEnabled,NULL,FALSE);//状态
    Show_String(pDvmData, nRow, XRIO_PARAMETER_COL_NAME, &pDvmData->m_strName,EndEditCell_String);
    Show_StaticString(pDvmData, nRow, XRIO_PARAMETER_COL_ID, &pDvmData->m_strID);
    Show_StaticString(pDvmData, nRow, XRIO_PARAMETER_COL_DATATYPE, &pDvmData->m_strDataType);

    //double类型的单位，最大值，最小值可以修改。
    Show_String(pDvmData, nRow, XRIO_PARAMETER_COL_UNIT, &pDvmData->m_strUnit ,EndEditCell_String);

    long nPrecision;
    CDvmValue *pDvmValue = NULL;
    pDvmValue = (CDvmValue*)GetAttrObj(pDvmData,XRIO_DEVICE_MODEL_ID_Unit_DecimalPlaces);
    if(pDvmValue != NULL)
    {
//        pDvmValue->m_strValue = pDvmValue->m_strValue.IsEmpty()?XRIO_DEVICE_MODEL_UNIT_DEFAULT_DECIMALPLACES:pDvmValue->m_strValue;
        nPrecision = CString_To_long(pDvmValue->m_strValue);
//        if(nPrecision < 0)
//        {
//            nPrecision = CString_To_long(XRIO_DEVICE_MODEL_UNIT_DEFAULT_DECIMALPLACES);
//        }
    }

    ShowDvmValue_AddAttrValue_DoubleString(pDvmData,nRow,XRIO_PARAMETER_COL_REFVALUE,XRIO_DEVICE_MODEL_ID_RefValue,nPrecision);

//    pDvmData->m_strMin = pDvmData->m_strMin.isEmpty()?XRIO_DEVICE_MODEL_NEGATIVE_INF_STRING:pDvmData->m_strMin;
    Show_Double(pDvmData,nRow,XRIO_PARAMETER_COL_MIN,nPrecision,&pDvmData->m_strMin,TRUE,EndEditCell_DoubleString,TRUE);

//    pDvmData->m_strMax = pDvmData->m_strMax.isEmpty()?XRIO_DEVICE_MODEL_POSITIVE_INF_STRING:pDvmData->m_strMax;
    Show_Double(pDvmData,nRow,XRIO_PARAMETER_COL_MAX,nPrecision,&pDvmData->m_strMax,TRUE,EndEditCell_DoubleString,TRUE);

    ShowDvmValue_AddAttrValue_String(pDvmData,nRow,XRIO_PARAMETER_COL_FOREIGNID,XRIO_DEVICE_MODEL_ID_ForeignId);
    ShowDvmValue_AddAttrValue_String(pDvmData,nRow,XRIO_PARAMETER_COL_DESCRIPTION,XRIO_DEVICE_MODEL_ID_Description);
    ShowDvmValue_AddAttrValue_String(pDvmData,nRow,XRIO_PARAMETER_COL_VALUEFORMULA,XRIO_DEVICE_MODEL_ID_ValueFormula);

    //double类型下不存在多个枚举值。
    BOOL bCanEdit;
    pDvmValue = (CDvmValue*)GetAttrObj(pDvmData,XRIO_DEVICE_MODEL_ID_ValueFormula);
    if(pDvmValue != NULL)
    {
        //公式不为空值就无法修改，否则可以修改。
        bCanEdit = pDvmValue->m_strValue.isEmpty()?TRUE:FALSE;
        Show_Double(pDvmData,nRow,XRIO_PARAMETER_COL_VALUE,nPrecision,&pDvmData->m_strValue,bCanEdit,EndEditCell_DoubleString,TRUE);
    }
    return TRUE;
}

BOOL QDeviceModelGrid_Eng::ShowDvmData_DataType_Enumeration(CDvmData *pDvmData, int &nRow)
{
    ASSERT(pDvmData);
    if(pDvmData == NULL)
    {
        return FALSE;
    }
//    if(!GetCurrObjIsEnabled(pDvmData,_T("")));//待替换的Enable宏
//    long nIsEnabled = XRIO_DEVICE_MODEL_CHECK_ENABLED;
//    else
//    long nIsEnabled = XRIO_DEVICE_MODEL_CHECK_DISENABLED;

//    QExBaseListGridBase::Show_Check(pDvmData, nRow, XRIO_PARAMETER_COL_STATE, &nIsEnabled,NULL,FALSE);//状态
    Show_String(pDvmData, nRow, XRIO_PARAMETER_COL_NAME, &pDvmData->m_strName,EndEditCell_String);
    Show_StaticString(pDvmData, nRow, XRIO_PARAMETER_COL_ID, &pDvmData->m_strID);
    Show_StaticString(pDvmData, nRow, XRIO_PARAMETER_COL_DATATYPE, &pDvmData->m_strDataType);

    //枚举类型的单位，最大值，最小值一定为空而且不可以修改。
    Show_StaticString(pDvmData, nRow, XRIO_PARAMETER_COL_UNIT, &pDvmData->m_strUnit);
    Show_StaticString(pDvmData, nRow, XRIO_PARAMETER_COL_MIN, &pDvmData->m_strMin);
    Show_StaticString(pDvmData, nRow, XRIO_PARAMETER_COL_MAX, &pDvmData->m_strMax);

    ShowDvmValue_AddAttrValue_String(pDvmData,nRow,XRIO_PARAMETER_COL_FOREIGNID,XRIO_DEVICE_MODEL_ID_ForeignId);
    ShowDvmValue_AddAttrValue_String(pDvmData,nRow,XRIO_PARAMETER_COL_DESCRIPTION,XRIO_DEVICE_MODEL_ID_Description);
    ShowDvmValue_AddAttrValue_String(pDvmData,nRow,XRIO_PARAMETER_COL_VALUEFORMULA,XRIO_DEVICE_MODEL_ID_ValueFormula);
    //枚举类型存在多个枚举值。

    CDvmValue *pDvmValue = NULL;

    CExBaseList *pValueList = new CExBaseList;
    long nIndex = 0;
    for(POS startPos = pDvmData->GetHeadPosition();startPos != pDvmData->GetTailPosition();++nIndex)
    {
        pDvmValue = (CDvmValue*)pDvmData->GetNext(startPos);

        if(XRIO_CUSTOM_PARAMETER_DATATYPE_ENUMERATION == pDvmValue->m_strDataType)
        {
            pValueList->AddTail(pDvmValue);
        }
    }

    pDvmValue = (CDvmValue*)GetAttrObj(pDvmData,XRIO_DEVICE_MODEL_ID_ValueFormula);
    if(pDvmValue != NULL)
    {
        //公式不为空值就无法修改，否则可以修改。
        if(pDvmValue->m_strValue.isEmpty())
        {
            Show_Enumeration(pDvmData,nRow,XRIO_PARAMETER_COL_VALUE,pValueList,&pDvmData->m_strValue,EndEditCell_Enumeration);
        }
        else
        {
            pDvmValue = (CDvmValue*)GetAttrObj(pDvmData,pDvmData->m_strValue);
            if(pDvmValue != NULL)
            {
                Show_StaticString(pDvmData, nRow, XRIO_PARAMETER_COL_VALUE, &pDvmValue->m_strValue);
            }
        }
    }

    //参考值的默认值为_T("")
    CExBaseList *pRefValueList = new CExBaseList;
    CDvmValue *pDefaultValue = new CDvmValue;
    pDefaultValue->m_strName = XRIO_DEVICE_MODEL_DEFAULTVALUE;
    pDefaultValue->m_strID = pDvmData->m_strID + _T("$");
    pDefaultValue->m_strDataType = XRIO_DEVICE_MODEL_DEFAULTVALUE;
    pDefaultValue->m_strValue = XRIO_DEVICE_MODEL_DEFAULTVALUE;
    pRefValueList->AddTail(pDefaultValue);

    nIndex = 0;
    for(POS startPos = pDvmData->GetHeadPosition();startPos != pDvmData->GetTailPosition();++nIndex)
    {
        pDvmValue = (CDvmValue*)pDvmData->GetNext(startPos);

        if(XRIO_CUSTOM_PARAMETER_DATATYPE_ENUMERATION == pDvmValue->m_strDataType)
        {
            pRefValueList->AddTail(pDvmValue);
        }
    }

    pDvmValue = (CDvmValue*)GetAttrObj(pDvmData,XRIO_DEVICE_MODEL_ID_RefValue);
    if(pDvmValue != NULL)
    {
        Show_Enumeration(pDvmData,nRow,XRIO_PARAMETER_COL_REFVALUE,pRefValueList,&pDvmValue->m_strValue,EndEditCell_Enumeration);
    }
    return TRUE;
}

BOOL QDeviceModelGrid_Eng::ShowDvmData_DataType_Integer(CDvmData *pDvmData, int &nRow)
{
    ASSERT(pDvmData);
    if(pDvmData == NULL)
    {
        return FALSE;
    }
//    if(!GetCurrObjIsEnabled(pDvmData,_T("")));//待替换的Enable宏
//    long nIsEnabled = XRIO_DEVICE_MODEL_CHECK_ENABLED;
//    else
//    long nIsEnabled = XRIO_DEVICE_MODEL_CHECK_DISENABLED;

//    QExBaseListGridBase::Show_Check(pDvmData, nRow, XRIO_PARAMETER_COL_STATE, &nIsEnabled,NULL,FALSE);//状态
    Show_String(pDvmData, nRow, XRIO_PARAMETER_COL_NAME, &pDvmData->m_strName,EndEditCell_String);
    Show_StaticString(pDvmData, nRow, XRIO_PARAMETER_COL_ID, &pDvmData->m_strID);
    Show_StaticString(pDvmData, nRow, XRIO_PARAMETER_COL_DATATYPE, &pDvmData->m_strDataType);

    //int类型单位一定为空。
//    pDvmData->m_strUnit = pDvmData->m_strUnit.isEmpty()?pDvmData->m_strUnit:XRIO_DEVICE_MODEL_DEFAULTVALUE;
    Show_StaticString(pDvmData, nRow, XRIO_PARAMETER_COL_UNIT, XRIO_DEVICE_MODEL_DEFAULTVALUE);

    ShowDvmValue_AddAttrValue_IntString(pDvmData,nRow,XRIO_PARAMETER_COL_REFVALUE,XRIO_DEVICE_MODEL_ID_RefValue);

    //int类型最大值，最小值可以修改。
//    pDvmData->m_strMin = pDvmData->m_strMin.isEmpty()?XRIO_DEVICE_MODEL_INT_MIN:pDvmData->m_strMin;
    Show_Int(pDvmData,nRow,XRIO_PARAMETER_COL_MIN,&pDvmData->m_strMin,TRUE,EndEditCell_IntString);

//    pDvmData->m_strMax = pDvmData->m_strMax.isEmpty()?XRIO_DEVICE_MODEL_INT_MAX:pDvmData->m_strMax;
    Show_Int(pDvmData,nRow,XRIO_PARAMETER_COL_MAX,&pDvmData->m_strMax,TRUE,EndEditCell_IntString);

    ShowDvmValue_AddAttrValue_String(pDvmData,nRow,XRIO_PARAMETER_COL_FOREIGNID,XRIO_DEVICE_MODEL_ID_ForeignId);
    ShowDvmValue_AddAttrValue_String(pDvmData,nRow,XRIO_PARAMETER_COL_DESCRIPTION,XRIO_DEVICE_MODEL_ID_Description);
    ShowDvmValue_AddAttrValue_String(pDvmData,nRow,XRIO_PARAMETER_COL_VALUEFORMULA,XRIO_DEVICE_MODEL_ID_ValueFormula);

    //int类型下不存在多个枚举值。
    CDvmValue *pDvmValue = NULL;
    BOOL bCanEdit;
    pDvmValue = (CDvmValue*)GetAttrObj(pDvmData,XRIO_DEVICE_MODEL_ID_ValueFormula);
    if(pDvmValue != NULL)
    {
        //公式不为空值就无法修改，否则可以修改。
        bCanEdit = pDvmValue->m_strValue.isEmpty()?TRUE:FALSE;
        Show_Int(pDvmData,nRow,XRIO_PARAMETER_COL_VALUE,&pDvmData->m_strValue,bCanEdit,EndEditCell_IntString);
    }
    return TRUE;
}

BOOL QDeviceModelGrid_Eng::ShowDvmData_DataType_Boolean(CDvmData *pDvmData, int &nRow)
{
    ASSERT(pDvmData);
    if(pDvmData == NULL)
    {
        return FALSE;
    }
//    if(!GetCurrObjIsEnabled(pDvmData,_T("")));//待替换的Enable宏
//    long nIsEnabled = XRIO_DEVICE_MODEL_CHECK_ENABLED;
//    else
//    long nIsEnabled = XRIO_DEVICE_MODEL_CHECK_DISENABLED;

//    QExBaseListGridBase::Show_Check(pDvmData, nRow, XRIO_PARAMETER_COL_STATE, &nIsEnabled,NULL,FALSE);//状态
    Show_String(pDvmData, nRow, XRIO_PARAMETER_COL_NAME, &pDvmData->m_strName,EndEditCell_String);
    Show_StaticString(pDvmData, nRow, XRIO_PARAMETER_COL_ID, &pDvmData->m_strID);
    Show_StaticString(pDvmData, nRow, XRIO_PARAMETER_COL_DATATYPE, &pDvmData->m_strDataType);

    //布尔类型的单位，最大值，最小值一定为空而且不可以修改。
//    pDvmData->m_strUnit = pDvmData->m_strUnit.isEmpty()?pDvmData->m_strUnit:XRIO_DEVICE_MODEL_DEFAULTVALUE;
    Show_StaticString(pDvmData, nRow, XRIO_PARAMETER_COL_UNIT, &pDvmData->m_strUnit);

//    pDvmData->m_strMin = pDvmData->m_strMin.isEmpty()?pDvmData->m_strMin:XRIO_DEVICE_MODEL_DEFAULTVALUE;
    Show_StaticString(pDvmData, nRow, XRIO_PARAMETER_COL_MIN, &pDvmData->m_strMin);

//    pDvmData->m_strMax = pDvmData->m_strMax.isEmpty()?pDvmData->m_strMax:XRIO_DEVICE_MODEL_DEFAULTVALUE;
    Show_StaticString(pDvmData, nRow, XRIO_PARAMETER_COL_MAX, &pDvmData->m_strMax);

    ShowDvmValue_AddAttrValue_String(pDvmData,nRow,XRIO_PARAMETER_COL_FOREIGNID,XRIO_DEVICE_MODEL_ID_ForeignId);
    ShowDvmValue_AddAttrValue_String(pDvmData,nRow,XRIO_PARAMETER_COL_DESCRIPTION,XRIO_DEVICE_MODEL_ID_Description);
    ShowDvmValue_AddAttrValue_String(pDvmData,nRow,XRIO_PARAMETER_COL_VALUEFORMULA,XRIO_DEVICE_MODEL_ID_ValueFormula);
    //布尔类型不存在多个枚举值。
    CDvmValue *pDvmValue = NULL;
    BOOL bCanEdit;
    pDvmValue = (CDvmValue*)GetAttrObj(pDvmData,XRIO_DEVICE_MODEL_ID_ValueFormula);
    if(pDvmValue != NULL)
    {
        //公式不为空值就无法修改，否则可以修改。
        bCanEdit = pDvmValue->m_strValue.isEmpty()?TRUE:FALSE;
        Show_Check(pDvmData,nRow,XRIO_PARAMETER_COL_VALUE,&pDvmData->m_strValue,EndEditCell_Check,bCanEdit);
    }

    pDvmValue = (CDvmValue*)GetAttrObj(pDvmData,XRIO_DEVICE_MODEL_ID_RefValue);
    if(pDvmValue != NULL)
    {
        bCanEdit = TRUE;
        Show_Check(pDvmValue,nRow,XRIO_PARAMETER_COL_REFVALUE,&pDvmValue->m_strValue,EndEditCell_Check,bCanEdit);
    }
    return TRUE;
}

BOOL QDeviceModelGrid_Eng::ShowDvmData_DataType_Default(CDvmData *pDvmData, int &nRow)
{
    ASSERT(pDvmData);
    if(pDvmData == NULL)
    {
        return FALSE;
    }
//    if(!GetCurrObjIsEnabled(pDvmData,_T("")));//待替换的Enable宏
//    long nIsEnabled = XRIO_DEVICE_MODEL_CHECK_ENABLED;
//    else
//    long nIsEnabled = XRIO_DEVICE_MODEL_CHECK_DISENABLED;

//    QExBaseListGridBase::Show_Check(pDvmData, nRow, XRIO_PARAMETER_COL_STATE, &nIsEnabled,NULL,FALSE);//状态
    Show_String(pDvmData, nRow, XRIO_PARAMETER_COL_NAME, &pDvmData->m_strName,EndEditCell_String);
    Show_StaticString(pDvmData, nRow, XRIO_PARAMETER_COL_ID, &pDvmData->m_strID);

    //修改数据类型为字符串类型。
    pDvmData->m_strDataType = XRIO_CUSTOM_PARAMETER_DATATYPE_STRING;
    Show_StaticString(pDvmData, nRow, XRIO_PARAMETER_COL_DATATYPE, &pDvmData->m_strDataType);

    //默认情况处理时修改单位，最大值，最小值为空。
    //字符串类型的单位，最大值，最小值一定为空而且不可以修改。
    pDvmData->m_strUnit = pDvmData->m_strUnit.isEmpty()?pDvmData->m_strUnit:XRIO_DEVICE_MODEL_DEFAULTVALUE;
    Show_StaticString(pDvmData, nRow, XRIO_PARAMETER_COL_UNIT, &pDvmData->m_strUnit);

    pDvmData->m_strMin = pDvmData->m_strMin.isEmpty()?pDvmData->m_strMin:XRIO_DEVICE_MODEL_DEFAULTVALUE;
    Show_StaticString(pDvmData, nRow, XRIO_PARAMETER_COL_MIN, &pDvmData->m_strMin);

    pDvmData->m_strMax = pDvmData->m_strMax.isEmpty()?pDvmData->m_strMax:XRIO_DEVICE_MODEL_DEFAULTVALUE;
    Show_StaticString(pDvmData, nRow, XRIO_PARAMETER_COL_MAX, &pDvmData->m_strMax);

    ShowDvmValue_AddAttrValue_String(pDvmData,nRow,XRIO_PARAMETER_COL_REFVALUE,XRIO_DEVICE_MODEL_ID_RefValue);
    ShowDvmValue_AddAttrValue_String(pDvmData,nRow,XRIO_PARAMETER_COL_FOREIGNID,XRIO_DEVICE_MODEL_ID_ForeignId);
    ShowDvmValue_AddAttrValue_String(pDvmData,nRow,XRIO_PARAMETER_COL_DESCRIPTION,XRIO_DEVICE_MODEL_ID_Description);
    ShowDvmValue_AddAttrValue_String(pDvmData,nRow,XRIO_PARAMETER_COL_VALUEFORMULA,XRIO_DEVICE_MODEL_ID_ValueFormula);
    //String类型下不存在多个枚举值。
    CDvmValue *pDvmValue = (CDvmValue*)GetAttrObj(pDvmData,XRIO_DEVICE_MODEL_ID_ValueFormula);
    if(pDvmValue != NULL)
    {
        //公式不为空值就无法修改，否则可以修改。
        if(pDvmValue->m_strValue.isEmpty())
        {
            Show_String(pDvmData, nRow, XRIO_PARAMETER_COL_VALUE, &pDvmData->m_strValue,EndEditCell_String);
        }
        else
        {
            Show_StaticString(pDvmData, nRow, XRIO_PARAMETER_COL_VALUE, &pDvmData->m_strValue);
        }
    }
    return TRUE;
}

BOOL QDeviceModelGrid_Eng::ShowDvmValue(CDvmValue *pDvmValue, int &nRow)
{
    if(XRIO_CUSTOM_PARAMETER_DATATYPE_STRING == pDvmValue->m_strDataType)
    {
        return ShowDvmValue_DataType_String(pDvmValue,nRow);
    }
    else if(XRIO_CUSTOM_PARAMETER_DATATYPE_REAL == pDvmValue->m_strDataType)
    {
        return ShowDvmValue_DataType_Real(pDvmValue,nRow);
    }
    else if(XRIO_CUSTOM_PARAMETER_DATATYPE_ENUMERATION == pDvmValue->m_strDataType)
    {
        return ShowDvmValue_DataType_Enumeration(pDvmValue,nRow);
    }
    else if(XRIO_CUSTOM_PARAMETER_DATATYPE_INTEGER == pDvmValue->m_strDataType)
    {
        return ShowDvmValue_DataType_Integer(pDvmValue,nRow);
    }
    else if(XRIO_CUSTOM_PARAMETER_DATATYPE_BOOLEAN == pDvmValue->m_strDataType)
    {
        return ShowDvmValue_DataType_Boolean(pDvmValue,nRow);
    }
    else
    {
        return ShowDvmValue_DataType_Default(pDvmValue,nRow);
    }
}

BOOL QDeviceModelGrid_Eng::ShowDvmValue_DataType_String(CDvmValue *pDvmValue, int &nRow)
{
    ASSERT(pDvmData);
    if(pDvmValue == NULL)
    {
        return FALSE;
    }
//    if(!GetCurrObjIsEnabled(pDvmData,_T("")));//待替换的Enable宏
//    long nIsEnabled = XRIO_DEVICE_MODEL_CHECK_ENABLED;
//    else
//    long nIsEnabled = XRIO_DEVICE_MODEL_CHECK_DISENABLED;

//    QExBaseListGridBase::Show_Check(pDvmValue, nRow, XRIO_PARAMETER_COL_STATE, &nIsEnabled,NULL,FALSE);//状态
    Show_String(pDvmValue, nRow, XRIO_PARAMETER_COL_NAME, &pDvmValue->m_strName,EndEditCell_String);
    Show_StaticString(pDvmValue, nRow, XRIO_PARAMETER_COL_ID, &pDvmValue->m_strID);
    Show_StaticString(pDvmValue, nRow, XRIO_PARAMETER_COL_DATATYPE, &pDvmValue->m_strDataType);

    //字符串类型的单位，最大值，最小值一定为空而且不可以修改。
    ShowDvmValue_AddAttrValue_String(pDvmValue, nRow, XRIO_PARAMETER_COL_UNIT, XRIO_DEVICE_MODEL_ID_Unit,FALSE);
    ShowDvmValue_AddAttrValue_String(pDvmValue, nRow, XRIO_PARAMETER_COL_MIN, XRIO_DEVICE_MODEL_ID_MinValue,FALSE);
    ShowDvmValue_AddAttrValue_String(pDvmValue, nRow, XRIO_PARAMETER_COL_MAX, XRIO_DEVICE_MODEL_ID_MaxValue,FALSE);

    ShowDvmValue_AddAttrValue_String(pDvmValue,nRow,XRIO_PARAMETER_COL_REFVALUE,XRIO_DEVICE_MODEL_ID_RefValue);
    ShowDvmValue_AddAttrValue_String(pDvmValue,nRow,XRIO_PARAMETER_COL_FOREIGNID,XRIO_DEVICE_MODEL_ID_ForeignId);
    ShowDvmValue_AddAttrValue_String(pDvmValue,nRow,XRIO_PARAMETER_COL_DESCRIPTION,XRIO_DEVICE_MODEL_ID_Description);
    ShowDvmValue_AddAttrValue_String(pDvmValue,nRow,XRIO_PARAMETER_COL_VALUEFORMULA,XRIO_DEVICE_MODEL_ID_ValueFormula);
    //String类型下不存在多个枚举值。
    CDvmValue *pAttrDvmValue = (CDvmValue*)GetAttrObj(pDvmValue,XRIO_DEVICE_MODEL_ID_ValueFormula);
    if(pAttrDvmValue != NULL)
    {
        //公式不为空值就无法修改，否则可以修改。
        if(pAttrDvmValue->m_strValue.isEmpty())
        {
            Show_String(pDvmValue, nRow, XRIO_PARAMETER_COL_VALUE, &pDvmValue->m_strValue,EndEditCell_String);
        }
        else
        {
            Show_StaticString(pDvmValue, nRow, XRIO_PARAMETER_COL_VALUE, &pDvmValue->m_strValue);
        }
    }
    return TRUE;
}

BOOL QDeviceModelGrid_Eng::ShowDvmValue_DataType_Real(CDvmValue *pDvmValue, int &nRow)
{
    ASSERT(pDvmValue);
    if(pDvmValue == NULL)
    {
        return FALSE;
    }
//    if(!GetCurrObjIsEnabled(pDvmData,_T("")));//待替换的Enable宏
//    long nIsEnabled = XRIO_DEVICE_MODEL_CHECK_ENABLED;
//    else
//    long nIsEnabled = XRIO_DEVICE_MODEL_CHECK_DISENABLED;

//    QExBaseListGridBase::Show_Check(pDvmValue, nRow, XRIO_PARAMETER_COL_STATE, &nIsEnabled,NULL,FALSE);//状态
    Show_String(pDvmValue, nRow, XRIO_PARAMETER_COL_NAME, &pDvmValue->m_strName,EndEditCell_String);
    Show_StaticString(pDvmValue, nRow, XRIO_PARAMETER_COL_ID, &pDvmValue->m_strID);
    Show_StaticString(pDvmValue, nRow, XRIO_PARAMETER_COL_DATATYPE, &pDvmValue->m_strDataType);

    //double类型的单位，最大值，最小值可以修改。
    ShowDvmValue_AddAttrValue_String(pDvmValue, nRow, XRIO_PARAMETER_COL_UNIT, XRIO_DEVICE_MODEL_ID_Unit);

    long nPrecision;
    CDvmValue *pAttrDvmValue = NULL;
    pAttrDvmValue = (CDvmValue*)GetAttrObj(pDvmValue,XRIO_DEVICE_MODEL_ID_Unit_DecimalPlaces);
    if(pAttrDvmValue != NULL)
    {
//        pAttrDvmValue->m_strValue = pAttrDvmValue->m_strValue.IsEmpty()?XRIO_DEVICE_MODEL_UNIT_DEFAULT_DECIMALPLACES:pAttrDvmValue->m_strValue;
        nPrecision = CString_To_long(pAttrDvmValue->m_strValue);
//        if(nPrecision < 0)
//        {
//            nPrecision = CString_To_long(XRIO_DEVICE_MODEL_UNIT_DEFAULT_DECIMALPLACES);
//        }
    }

    ShowDvmValue_AddAttrValue_DoubleString(pDvmValue,nRow,XRIO_PARAMETER_COL_REFVALUE,XRIO_DEVICE_MODEL_ID_RefValue,nPrecision);
    ShowDvmValue_AddAttrValue_DoubleString(pDvmValue,nRow,XRIO_PARAMETER_COL_MIN,XRIO_DEVICE_MODEL_ID_MinValue,nPrecision);
    ShowDvmValue_AddAttrValue_DoubleString(pDvmValue,nRow,XRIO_PARAMETER_COL_MAX,XRIO_DEVICE_MODEL_ID_MaxValue,nPrecision);

    ShowDvmValue_AddAttrValue_String(pDvmValue,nRow,XRIO_PARAMETER_COL_FOREIGNID,XRIO_DEVICE_MODEL_ID_ForeignId);
    ShowDvmValue_AddAttrValue_String(pDvmValue,nRow,XRIO_PARAMETER_COL_DESCRIPTION,XRIO_DEVICE_MODEL_ID_Description);
    ShowDvmValue_AddAttrValue_String(pDvmValue,nRow,XRIO_PARAMETER_COL_VALUEFORMULA,XRIO_DEVICE_MODEL_ID_ValueFormula);

    //double类型下不存在多个枚举值。
    BOOL bCanEdit;
    pAttrDvmValue = (CDvmValue*)GetAttrObj(pDvmValue,XRIO_DEVICE_MODEL_ID_ValueFormula);
    if(pAttrDvmValue != NULL)
    {
        //公式不为空值就无法修改，否则可以修改。
        bCanEdit = pAttrDvmValue->m_strValue.isEmpty()?TRUE:FALSE;
        Show_Double(pDvmValue,nRow,XRIO_PARAMETER_COL_VALUE,nPrecision,&pDvmValue->m_strValue,bCanEdit,EndEditCell_DoubleString,TRUE);
    }
    return TRUE;
}

BOOL QDeviceModelGrid_Eng::ShowDvmValue_DataType_Enumeration(CDvmValue *pDvmValue, int &nRow)
{
    ASSERT(pDvmValue);
    if(pDvmValue == NULL)
    {
        return FALSE;
    }
//    if(!GetCurrObjIsEnabled(pDvmData,_T("")));//待替换的Enable宏
//    long nIsEnabled = XRIO_DEVICE_MODEL_CHECK_ENABLED;
//    else
//    long nIsEnabled = XRIO_DEVICE_MODEL_CHECK_DISENABLED;

//    QExBaseListGridBase::Show_Check(pDvmValue, nRow, XRIO_PARAMETER_COL_STATE, &nIsEnabled,NULL,FALSE);//状态
    Show_String(pDvmValue, nRow, XRIO_PARAMETER_COL_NAME, &pDvmValue->m_strName,EndEditCell_String);
    Show_StaticString(pDvmValue, nRow, XRIO_PARAMETER_COL_ID, &pDvmValue->m_strID);
    Show_StaticString(pDvmValue, nRow, XRIO_PARAMETER_COL_DATATYPE, &pDvmValue->m_strDataType);

    //枚举类型的单位，最大值，最小值一定为空而且不可以修改。
    ShowDvmValue_AddAttrValue_String(pDvmValue, nRow, XRIO_PARAMETER_COL_UNIT, XRIO_DEVICE_MODEL_ID_Unit,FALSE);
    ShowDvmValue_AddAttrValue_String(pDvmValue, nRow, XRIO_PARAMETER_COL_MIN, XRIO_DEVICE_MODEL_ID_MinValue,FALSE);
    ShowDvmValue_AddAttrValue_String(pDvmValue, nRow, XRIO_PARAMETER_COL_MAX, XRIO_DEVICE_MODEL_ID_MaxValue,FALSE);

    ShowDvmValue_AddAttrValue_String(pDvmValue,nRow,XRIO_PARAMETER_COL_FOREIGNID,XRIO_DEVICE_MODEL_ID_ForeignId);
    ShowDvmValue_AddAttrValue_String(pDvmValue,nRow,XRIO_PARAMETER_COL_DESCRIPTION,XRIO_DEVICE_MODEL_ID_Description);
    ShowDvmValue_AddAttrValue_String(pDvmValue,nRow,XRIO_PARAMETER_COL_VALUEFORMULA,XRIO_DEVICE_MODEL_ID_ValueFormula);
    //枚举类型存在多个枚举值。

    CDvmValue *pAttrDvmValue = NULL;

    CExBaseList *pValueList = new CExBaseList;
    long nIndex = 0;
    for(POS startPos = pDvmValue->GetHeadPosition();startPos != pDvmValue->GetTailPosition();++nIndex)
    {
        pAttrDvmValue = (CDvmValue*)pDvmValue->GetNext(startPos);
        if(XRIO_CUSTOM_PARAMETER_DATATYPE_ENUMERATION == pAttrDvmValue->m_strDataType)
        {
            pValueList->AddTail(pAttrDvmValue);
        }
    }

    pAttrDvmValue = (CDvmValue*)GetAttrObj(pDvmValue,XRIO_DEVICE_MODEL_ID_ValueFormula);
    if(pAttrDvmValue != NULL)
    {
        //公式不为空值就无法修改，否则可以修改。
        if(pAttrDvmValue->m_strValue.isEmpty())
        {
            Show_Enumeration(pDvmValue,nRow,XRIO_PARAMETER_COL_VALUE,pValueList,&pDvmValue->m_strValue,EndEditCell_Enumeration);
        }
        else
        {
            pAttrDvmValue = (CDvmValue*)GetAttrObj(pDvmValue,pDvmValue->m_strValue);
            if(pAttrDvmValue != NULL)
            {
                Show_StaticString(pDvmValue, nRow, XRIO_PARAMETER_COL_VALUE, &pAttrDvmValue->m_strValue);
            }
        }
    }

    //参考值的默认值为_T("")
    CExBaseList *pRefValueList = new CExBaseList;
    CDvmValue *pDefaultValue = new CDvmValue;
    pDefaultValue->m_strName = XRIO_DEVICE_MODEL_DEFAULTVALUE;
    pDefaultValue->m_strID = pDvmValue->m_strID + _T("$");
    pDefaultValue->m_strDataType = XRIO_DEVICE_MODEL_DEFAULTVALUE;
    pDefaultValue->m_strValue = XRIO_DEVICE_MODEL_DEFAULTVALUE;
    pRefValueList->AddTail(pDefaultValue);

    nIndex = 0;
    for(POS startPos = pDvmValue->GetHeadPosition();startPos != pDvmValue->GetTailPosition();++nIndex)
    {
        pAttrDvmValue = (CDvmValue*)pDvmValue->GetNext(startPos);
        if(XRIO_CUSTOM_PARAMETER_DATATYPE_ENUMERATION == pAttrDvmValue->m_strDataType)
        {
            pRefValueList->AddTail(pAttrDvmValue);
        }
    }

    pAttrDvmValue = (CDvmValue*)GetAttrObj(pDvmValue,XRIO_DEVICE_MODEL_ID_RefValue);
    if(pAttrDvmValue != NULL)
    {
        Show_Enumeration(pDvmValue,nRow,XRIO_PARAMETER_COL_REFVALUE,pRefValueList,&pAttrDvmValue->m_strValue,EndEditCell_Enumeration);
    }
    return TRUE;
}

BOOL QDeviceModelGrid_Eng::ShowDvmValue_DataType_Integer(CDvmValue *pDvmValue, int &nRow)
{
    ASSERT(pDvmValue);
    if(pDvmValue == NULL)
    {
        return FALSE;
    }
//    if(!GetCurrObjIsEnabled(pDvmData,_T("")));//待替换的Enable宏
//    long nIsEnabled = XRIO_DEVICE_MODEL_CHECK_ENABLED;
//    else
//    long nIsEnabled = XRIO_DEVICE_MODEL_CHECK_DISENABLED;

//    QExBaseListGridBase::Show_Check(pDvmValue, nRow, XRIO_PARAMETER_COL_STATE, &nIsEnabled,NULL,FALSE);//状态
    Show_String(pDvmValue, nRow, XRIO_PARAMETER_COL_NAME, &pDvmValue->m_strName,EndEditCell_String);
    Show_StaticString(pDvmValue, nRow, XRIO_PARAMETER_COL_ID, &pDvmValue->m_strID);
    Show_StaticString(pDvmValue, nRow, XRIO_PARAMETER_COL_DATATYPE, &pDvmValue->m_strDataType);

    //int类型单位一定为空。
    ShowDvmValue_AddAttrValue_String(pDvmValue, nRow, XRIO_PARAMETER_COL_UNIT, XRIO_DEVICE_MODEL_ID_Unit,FALSE);

    ShowDvmValue_AddAttrValue_IntString(pDvmValue,nRow,XRIO_PARAMETER_COL_REFVALUE,XRIO_DEVICE_MODEL_ID_RefValue);

    //int类型最大值，最小值可以修改。
    ShowDvmValue_AddAttrValue_IntString(pDvmValue,nRow,XRIO_PARAMETER_COL_MIN,XRIO_DEVICE_MODEL_ID_MinValue);
    ShowDvmValue_AddAttrValue_IntString(pDvmValue,nRow,XRIO_PARAMETER_COL_MAX,XRIO_DEVICE_MODEL_ID_MaxValue);

    ShowDvmValue_AddAttrValue_String(pDvmValue,nRow,XRIO_PARAMETER_COL_FOREIGNID,XRIO_DEVICE_MODEL_ID_ForeignId);
    ShowDvmValue_AddAttrValue_String(pDvmValue,nRow,XRIO_PARAMETER_COL_DESCRIPTION,XRIO_DEVICE_MODEL_ID_Description);
    ShowDvmValue_AddAttrValue_String(pDvmValue,nRow,XRIO_PARAMETER_COL_VALUEFORMULA,XRIO_DEVICE_MODEL_ID_ValueFormula);

    //int类型下不存在多个枚举值。
    CDvmValue *pAttrDvmValue = NULL;
    BOOL bCanEdit;
    pAttrDvmValue = (CDvmValue*)GetAttrObj(pDvmValue,XRIO_DEVICE_MODEL_ID_ValueFormula);
    if(pAttrDvmValue != NULL)
    {
        //公式不为空值就无法修改，否则可以修改。
        bCanEdit = pAttrDvmValue->m_strValue.isEmpty()?TRUE:FALSE;
        Show_Int(pDvmValue,nRow,XRIO_PARAMETER_COL_VALUE,&pDvmValue->m_strValue,bCanEdit,EndEditCell_IntString);
    }
    return TRUE;
}

BOOL QDeviceModelGrid_Eng::ShowDvmValue_DataType_Boolean(CDvmValue *pDvmValue, int &nRow)
{
    ASSERT(pDvmValue);
    if(pDvmValue == NULL)
    {
        return FALSE;
    }
//    if(!GetCurrObjIsEnabled(pDvmData,_T("")));//待替换的Enable宏
//    long nIsEnabled = XRIO_DEVICE_MODEL_CHECK_ENABLED;
//    else
//    long nIsEnabled = XRIO_DEVICE_MODEL_CHECK_DISENABLED;

//    QExBaseListGridBase::Show_Check(pDvmValue, nRow, XRIO_PARAMETER_COL_STATE, &nIsEnabled,NULL,FALSE);//状态
    Show_String(pDvmValue, nRow, XRIO_PARAMETER_COL_NAME, &pDvmValue->m_strName,EndEditCell_String);
    Show_StaticString(pDvmValue, nRow, XRIO_PARAMETER_COL_ID, &pDvmValue->m_strID);
    Show_StaticString(pDvmValue, nRow, XRIO_PARAMETER_COL_DATATYPE, &pDvmValue->m_strDataType);

    //布尔类型的单位，最大值，最小值一定为空而且不可以修改。
    ShowDvmValue_AddAttrValue_String(pDvmValue, nRow, XRIO_PARAMETER_COL_UNIT, XRIO_DEVICE_MODEL_ID_Unit,FALSE);
    ShowDvmValue_AddAttrValue_String(pDvmValue, nRow, XRIO_PARAMETER_COL_MIN, XRIO_DEVICE_MODEL_ID_MinValue,FALSE);
    ShowDvmValue_AddAttrValue_String(pDvmValue, nRow, XRIO_PARAMETER_COL_MAX, XRIO_DEVICE_MODEL_ID_MaxValue,FALSE);

    ShowDvmValue_AddAttrValue_String(pDvmValue,nRow,XRIO_PARAMETER_COL_FOREIGNID,XRIO_DEVICE_MODEL_ID_ForeignId);
    ShowDvmValue_AddAttrValue_String(pDvmValue,nRow,XRIO_PARAMETER_COL_DESCRIPTION,XRIO_DEVICE_MODEL_ID_Description);
    ShowDvmValue_AddAttrValue_String(pDvmValue,nRow,XRIO_PARAMETER_COL_VALUEFORMULA,XRIO_DEVICE_MODEL_ID_ValueFormula);
    //布尔类型不存在多个枚举值。
    CDvmValue *pAttrDvmValue = NULL;
    BOOL bCanEdit;
    pAttrDvmValue = (CDvmValue*)GetAttrObj(pDvmValue,XRIO_DEVICE_MODEL_ID_ValueFormula);
    if(pAttrDvmValue != NULL)
    {
        //公式不为空值就无法修改，否则可以修改。
        bCanEdit = pAttrDvmValue->m_strValue.isEmpty()?TRUE:FALSE;
        Show_Check(pDvmValue,nRow,XRIO_PARAMETER_COL_VALUE,&pDvmValue->m_strValue,EndEditCell_Check,bCanEdit);
    }

    pAttrDvmValue = (CDvmValue*)GetAttrObj(pDvmValue,XRIO_DEVICE_MODEL_ID_RefValue);
    if(pAttrDvmValue != NULL)
    {
        bCanEdit = TRUE;
        Show_Check(pDvmValue,nRow,XRIO_PARAMETER_COL_REFVALUE,&pAttrDvmValue->m_strValue,EndEditCell_Check,bCanEdit);
    }

    return TRUE;
}

BOOL QDeviceModelGrid_Eng::ShowDvmValue_DataType_Default(CDvmValue *pDvmValue, int &nRow)
{
    ASSERT(pDvmData);
    if(pDvmValue == NULL)
    {
        return FALSE;
    }
//    if(!GetCurrObjIsEnabled(pDvmData,_T("")));//待替换的Enable宏
//    long nIsEnabled = XRIO_DEVICE_MODEL_CHECK_ENABLED;
//    else
//    long nIsEnabled = XRIO_DEVICE_MODEL_CHECK_DISENABLED;

//    QExBaseListGridBase::Show_Check(pDvmValue, nRow, XRIO_PARAMETER_COL_STATE, &nIsEnabled,NULL,FALSE);//状态
    Show_String(pDvmValue, nRow, XRIO_PARAMETER_COL_NAME, &pDvmValue->m_strName,EndEditCell_String);
    Show_StaticString(pDvmValue, nRow, XRIO_PARAMETER_COL_ID, &pDvmValue->m_strID);

    pDvmValue->m_strDataType = XRIO_CUSTOM_PARAMETER_DATATYPE_STRING;
    Show_StaticString(pDvmValue, nRow, XRIO_PARAMETER_COL_DATATYPE, &pDvmValue->m_strDataType);

    //字符串类型的单位，最大值，最小值一定为空而且不可以修改。
    ShowDvmValue_AddAttrValue_String(pDvmValue, nRow, XRIO_PARAMETER_COL_UNIT, XRIO_DEVICE_MODEL_ID_Unit,FALSE);
    ShowDvmValue_AddAttrValue_String(pDvmValue, nRow, XRIO_PARAMETER_COL_MIN, XRIO_DEVICE_MODEL_ID_MinValue,FALSE);
    ShowDvmValue_AddAttrValue_String(pDvmValue, nRow, XRIO_PARAMETER_COL_MAX, XRIO_DEVICE_MODEL_ID_MaxValue,FALSE);

    ShowDvmValue_AddAttrValue_String(pDvmValue,nRow,XRIO_PARAMETER_COL_REFVALUE,XRIO_DEVICE_MODEL_ID_RefValue);
    ShowDvmValue_AddAttrValue_String(pDvmValue,nRow,XRIO_PARAMETER_COL_FOREIGNID,XRIO_DEVICE_MODEL_ID_ForeignId);
    ShowDvmValue_AddAttrValue_String(pDvmValue,nRow,XRIO_PARAMETER_COL_DESCRIPTION,XRIO_DEVICE_MODEL_ID_Description);
    ShowDvmValue_AddAttrValue_String(pDvmValue,nRow,XRIO_PARAMETER_COL_VALUEFORMULA,XRIO_DEVICE_MODEL_ID_ValueFormula);
    //String类型下不存在多个枚举值。
    CDvmValue *pAttrDvmValue = (CDvmValue*)GetAttrObj(pDvmValue,XRIO_DEVICE_MODEL_ID_ValueFormula);
    if(pAttrDvmValue != NULL)
    {
        //公式不为空值就无法修改，否则可以修改。
        if(pAttrDvmValue->m_strValue.isEmpty())
        {
            Show_String(pDvmValue, nRow, XRIO_PARAMETER_COL_VALUE, &pDvmValue->m_strValue,EndEditCell_String);
        }
        else
        {
            Show_StaticString(pDvmValue, nRow, XRIO_PARAMETER_COL_VALUE, &pDvmValue->m_strValue);
        }
    }
    return TRUE;
}

void QDeviceModelGrid_Eng::Show_DataType_Val(CExBaseObject *pData, const int &nRow, const int &nCol, CDataType *pDataType, CString *pstrValue, GRID_CELL_EDIT_FUNC pFunc)
{
    CDataTypeValue *pValue = NULL;
    CString strTempIDPath;
    strTempIDPath = GetObjectIDPath(pData->m_strID,*pstrValue);

    if (pDataType != NULL)
    {
        pValue = (CDataTypeValue*)pDataType->FindByID(/**pstrValue*/strTempIDPath);

        if (pValue == NULL)
        {
            if(XRIO_PARAMETER_COL_REFVALUE == nCol)
            {
                *pstrValue = XRIO_DEVICE_MODEL_DEFAULTVALUE;
            }
            else
            {
                pValue = (CDataTypeValue*)pDataType->GetHead();

                if (pValue != NULL)
                {
                    *pstrValue = pValue->m_strID;
                }
            }
        }
    }

    QGV_ITEM *pItem = NULL;
    BOOL bHasSetItem = FALSE;

    if (pValue == NULL)
    {
        pItem = AddItem(nRow,nCol,*pstrValue,bHasSetItem);
    }
    else
    {
        pItem = AddItem(nRow,nCol,pValue->m_strName,bHasSetItem);
    }

    PEXBASECELLDATA pVCellData = CreateExBaseCellData(pItem->lParam, pstrValue, pData, NULL, pFunc);
    pVCellData->pExBaseList = pDataType;
    pVCellData->nVt = VCD_STRING;
    pItem->m_pEditFunc = pFunc;

    pItem->nDataType = QT_GVET_COMBOBOX;
    pItem->nReserved = QT_GRID_COMBOBOX_StringType_DataTypeID;
    pItem->lParam = (LPARAM)pVCellData;

    pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

    if (!(pItem->flags() & Qt::ItemIsEditable))
    {
        pItem->setFlags((pItem->flags()|Qt::ItemIsEditable));
    }

    if (!bHasSetItem)
    {
        setItem(nRow,nCol,pItem);
    }
}

void QDeviceModelGrid_Eng::Show_Enumeration(CExBaseObject *pData, const int &nRow, const int &nCol, CExBaseList *pList, CString *pstrValue, GRID_CELL_EDIT_FUNC pFunc)
{
    CExBaseObject *pObj = NULL;

    CString strTempIDPath;
    strTempIDPath = GetObjectIDPath(pData->m_strID,*pstrValue);

    if (pList != NULL)
    {
        pObj = pList->FindByID(strTempIDPath);

        if (pObj == NULL)
        {
//            if(XRIO_PARAMETER_COL_REFVALUE == nCol)
//            {
//                *pstrValue = XRIO_DEVICE_MODEL_DEFAULTVALUE;
//            }
//            else
//            {
                pObj = pList->GetHead();

                if (pObj != NULL)
                {
                    *pstrValue = pObj->m_strName;
                }
//            }
        }
    }

    QGV_ITEM *pItem = NULL;
    BOOL bHasSetItem = FALSE;

    if (pObj == NULL)
    {
        pItem = AddItem(nRow,nCol,*pstrValue,bHasSetItem);
    }
    else
    {
        pItem = AddItem(nRow,nCol,pObj->m_strName,bHasSetItem);
    }

    PEXBASECELLDATA pVCellData = CreateExBaseCellData(pItem->lParam, pstrValue, pData, NULL, pFunc);
    pVCellData->pExBaseList = pList;
    pVCellData->nVt = VCD_STRING;
    pItem->m_pEditFunc = pFunc;

    pItem->nDataType = QT_GVET_COMBOBOX;
    pItem->nReserved = QT_GRID_COMBOBOX_StringType_DataTypeID;
    pItem->lParam = (LPARAM)pVCellData;

    pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

    if (!(pItem->flags() & Qt::ItemIsEditable))
    {
        pItem->setFlags((pItem->flags()|Qt::ItemIsEditable));
    }

    if (!bHasSetItem)
    {
        setItem(nRow,nCol,pItem);
    }
}

void QDeviceModelGrid_Eng::Show_Double(CExBaseObject *pData, const int &nRow, const int &nCol, long nPrecision, CString *pstrValue, BOOL bCanEdit, GRID_CELL_EDIT_FUNC pFunc, BOOL bUnitConversion)
{
    BOOL bHasSetItem = FALSE;
    QGV_ITEM *pItem = NULL;
    if(pstrValue->isEmpty())
    {
        pItem = AddItem(nRow,nCol,XRIO_DEVICE_MODEL_DEFAULTVALUE,bHasSetItem);
    }
    else
    {
        double dValue = CString_To_double(*pstrValue);
            CString strFormat;
        strFormat.Format(_T("%%.%ldlf"), nPrecision);
            CString strTmp;
            strTmp.Format(strFormat.GetString(), dValue);
            pItem = AddItem(nRow,nCol,strTmp,bHasSetItem);
        }

    pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

    if (bCanEdit)
    {
        if (!(pItem->flags() & Qt::ItemIsEditable))
        {
            pItem->setFlags((pItem->flags()|Qt::ItemIsEditable));
        }
    }
    else
    {
        if ((pItem->flags() & Qt::ItemIsEditable))
        {
            pItem->setFlags((pItem->flags() & ~Qt::ItemIsEditable));
        }
    }

    PEXBASECELLDATA pVCellData = CreateExBaseCellData(pItem->lParam, pstrValue, pData,NULL, pFunc);
    pItem->lParam = (LPARAM)pVCellData;
    pItem->nDataType = QT_GVET_EDITBOX;
    pVCellData->nVt = VCD_STRING;
    pItem->dwValue =( nPrecision << 16) + bUnitConversion;

    if (pFunc != NULL)
    {
        pItem->m_pEditFunc = pFunc;
        pVCellData->pFunc = pFunc;
    }
    else
    {
        pItem->m_pEditFunc = EndEditCell_DoubleString;
        pVCellData->pFunc = EndEditCell_DoubleString;
    }

    if (!bHasSetItem)
    {
        setItem(nRow,nCol,pItem);
    }
}

void QDeviceModelGrid_Eng::Show_Int(CExBaseObject *pData, const int &nRow, const int &nCol, CString *pstrValue, BOOL bCanEdit, GRID_CELL_EDIT_FUNC pFunc)
{
    BOOL bHasSetItem = FALSE;
    QGV_ITEM *pItem = NULL;

    if(pstrValue->isEmpty())
    {
        pItem = AddItem(nRow,nCol,XRIO_DEVICE_MODEL_DEFAULTVALUE,bHasSetItem);
    }
    else
    {
        CString strTemp;
        int nValue = pstrValue->toInt();
        strTemp.Format(_T("%d"),nValue);
        pItem = AddItem(nRow,nCol,strTemp,bHasSetItem);
    }

    pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

    if (bCanEdit)
    {
        if (!(pItem->flags() & Qt::ItemIsEditable))
        {
            pItem->setFlags((pItem->flags()|Qt::ItemIsEditable));
        }
    }
    else
    {
        if ((pItem->flags() & Qt::ItemIsEditable))
        {
            pItem->setFlags((pItem->flags() & ~Qt::ItemIsEditable));
        }
    }

    PEXBASECELLDATA pVCellData = CreateExBaseCellData(pItem->lParam, pstrValue, pData,NULL, pFunc);
    pItem->lParam = (LPARAM)pVCellData;
    pItem->nDataType = QT_GVET_EDITBOX;
    pVCellData->nVt = VCD_STRING;

    if (pFunc != NULL)
    {
        pItem->m_pEditFunc = pFunc;
        pVCellData->pFunc = pFunc;
    }
    else
    {
        pItem->m_pEditFunc = EndEditCell_Value;
        pVCellData->pFunc = EndEditCell_Value;
    }

    if (!bHasSetItem)
    {
        setItem(nRow,nCol,pItem);
    }
}

void QDeviceModelGrid_Eng::Show_Check(CExBaseObject *pData, const int &nRow, const int &nCol, CString *pstrCheck, GRID_CELL_EDIT_FUNC pFunc, BOOL bCanEdit)
{
    BOOL bHasSetItem = FALSE;
    QGV_ITEM *pItem = AddItem(nRow,nCol,XRIO_DEVICE_MODEL_DEFAULTVALUE,bHasSetItem);
    pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    pItem->setFlags((Qt::ItemIsEnabled));

    QDeviceModelGrid_Eng_CheckBox *pCheckBox = new QDeviceModelGrid_Eng_CheckBox;
    pCheckBox->SetRowIndexAndColIndex(nRow,nCol);
    this->setCellWidget(nRow,nCol,pCheckBox);
    connect(pCheckBox, SIGNAL(CheckBox_LeftClicked(int&,int&)), this, SLOT(slot_CheckBox_LeftClicked(int&,int&)));

    pCheckBox->SetEditable(bCanEdit);

    PEXBASECELLDATA pVCellData = CreateExBaseCellData(pItem->lParam, pstrCheck, pData,NULL, NULL);
    pVCellData->nVt = VCD_STRING;
    pItem->lParam = (LPARAM)pVCellData;
    pItem->nDataType = QT_GVET_CHECKBOX;
    pItem->m_pEditFunc = NULL;

    ASSERT(0 == pstrCheck->CompareNoCase(XRIO_CUSTOM_PARAMETER_DATATYPE_BOOLEAN_TRUE) || 0 == pstrCheck->CompareNoCase(XRIO_CUSTOM_PARAMETER_DATATYPE_BOOLEAN_FALSE)
           || XRIO_CUSTOM_PARAMETER_DATATYPE_BOOLEAN_TRUE_NUMERIC == *pstrCheck || XRIO_CUSTOM_PARAMETER_DATATYPE_BOOLEAN_FALSE_NUMERIC == *pstrCheck)

    if(0 == pstrCheck->CompareNoCase(XRIO_CUSTOM_PARAMETER_DATATYPE_BOOLEAN_TRUE) || XRIO_CUSTOM_PARAMETER_DATATYPE_BOOLEAN_TRUE_NUMERIC == *pstrCheck)
    {
        pCheckBox->SetChecked(TRUE);
    }
    else if(0 == pstrCheck->CompareNoCase(XRIO_CUSTOM_PARAMETER_DATATYPE_BOOLEAN_FALSE) || XRIO_CUSTOM_PARAMETER_DATATYPE_BOOLEAN_FALSE_NUMERIC == *pstrCheck)
    {
        pCheckBox->SetChecked(FALSE);
    }

    pItem->m_pEditFunc = pFunc;
    pVCellData->pFunc = pFunc;

    if (!bHasSetItem)
    {
        setItem(nRow,nCol,pItem);
    }
}

BOOL QDeviceModelGrid_Eng::ShowDvmDataInTable(CDvmData *pDvmData, int &nRow)
{
    //2024-9-27现在对展示内容进行修改，原来的展示不严谨，现在改为根据对象的DataType分类进行处理。如果有问题可以注掉现有版本使用原来的。
    //现在除了ID不可以更改外，其余均可以更改。各种限制输入条件会根据不同DataType变化。
    return ShowDvmData(pDvmData,nRow);

    //--------------原来版本----------
//    long lEnabled = 1;
//    if(pDvmData != NULL)
//    {
//        QExBaseListGridBase::Show_Check(pDvmData, nRow, XRIO_PARAMETER_COL_STATE, &lEnabled,NULL,TRUE);//状态
//        Show_StaticString(pDvmData, nRow, XRIO_PARAMETER_COL_NAME, &pDvmData->m_strName);
//        Show_StaticString(pDvmData, nRow, XRIO_PARAMETER_COL_ID, &pDvmData->m_strID);
//        Show_StaticString(pDvmData, nRow, XRIO_PARAMETER_COL_DATATYPE, &pDvmData->m_strDataType);
//        Show_StaticString(pDvmData, nRow, XRIO_PARAMETER_COL_REFVALUE, XRIO_DEVICE_MODEL_DEFAULTVALUE);

//        Show_StaticString(pDvmData, nRow, XRIO_PARAMETER_COL_UNIT, &pDvmData->m_strUnit);
//        Show_StaticString(pDvmData, nRow, XRIO_PARAMETER_COL_MIN, &pDvmData->m_strMin);
//        Show_StaticString(pDvmData, nRow, XRIO_PARAMETER_COL_MAX, &pDvmData->m_strMax);
//    }
//    ShowObjectAttrs(pDvmData,nRow,XRIO_PARAMETER_COL_FOREIGNID,XRIO_DEVICE_MODEL_ID_ForeignId);
//    ShowObjectAttrs(pDvmData,nRow,XRIO_PARAMETER_COL_DESCRIPTION,XRIO_DEVICE_MODEL_ID_Description);
//    ShowObjectAttrs(pDvmData,nRow,XRIO_PARAMETER_COL_VALUEFORMULA,XRIO_DEVICE_MODEL_ID_ValueFormula);
//    ShowMultipleValues(pDvmData,nRow,XRIO_PARAMETER_COL_REFVALUE,XRIO_PARAMETER_COL_VALUE);
//    return TRUE;
}

BOOL QDeviceModelGrid_Eng::ShowCBDvmDataInTable(CDvmData *pDvmData, int &nRow)
{
    ASSERT(pDvmData);
    if(pDvmData == NULL)
    {
        return FALSE;
    }
//    if(!GetCurrObjIsEnabled(pDvmData,_T("")));//待替换的Enable宏
//    long nIsEnabled = XRIO_DEVICE_MODEL_CHECK_ENABLED;
//    else
//    long nIsEnabled = XRIO_DEVICE_MODEL_CHECK_DISENABLED;

//    QExBaseListGridBase::Show_Check(pDvmData, nRow, XRIO_RIO_CB_COL_STATE, &nIsEnabled,NULL,FALSE);//状态
    Show_StaticString(pDvmData, nRow, XRIO_RIO_CB_COL_NAME, &pDvmData->m_strName);
    Show_StaticString(pDvmData, nRow, XRIO_RIO_CB_COL_ID, &pDvmData->m_strID);
    Show_StaticString(pDvmData, nRow, XRIO_RIO_CB_COL_UNIT, &pDvmData->m_strUnit);
    Show_StaticString(pDvmData, nRow, XRIO_RIO_CB_COL_MIN, &pDvmData->m_strMin);
    Show_StaticString(pDvmData, nRow, XRIO_RIO_CB_COL_MAX, &pDvmData->m_strMax);

    ShowDvmValue_AddAttrValue_String(pDvmData,nRow,XRIO_RIO_CB_COL_DESCRIPTION,XRIO_DEVICE_MODEL_ID_Description,FALSE);
    ShowDvmValue_AddAttrValue_String(pDvmData,nRow,XRIO_RIO_CB_COL_VALUEFORMULA,XRIO_DEVICE_MODEL_ID_ValueFormula);
    long nPrecision;
    CString strPrecision = XRIO_DEVICE_MODEL_UNIT_DEFAULT_DECIMALPLACES;
    nPrecision = CString_To_long(strPrecision);
    Show_Double(pDvmData, nRow, XRIO_RIO_CB_COL_VALUE, nPrecision,&pDvmData->m_strValue,TRUE,EndEditCell_DoubleString,TRUE);
    return TRUE;


    //原本版本
//    long lEnabled = TRUE;

//    if(pDvmData != NULL)
//    {
//        QExBaseListGridBase::Show_Check(pDvmData, nRow, XRIO_RIO_CB_COL_STATE, &lEnabled,NULL,FALSE);//状态
//        Show_StaticString(pDvmData, nRow, XRIO_RIO_CB_COL_NAME, &pDvmData->m_strName);
//        Show_StaticString(pDvmData, nRow, XRIO_RIO_CB_COL_ID, &pDvmData->m_strID);
//        Show_StaticString(pDvmData, nRow, XRIO_RIO_CB_COL_UNIT, &pDvmData->m_strUnit);
//        Show_StaticString(pDvmData, nRow, XRIO_RIO_CB_COL_MIN, &pDvmData->m_strMin);
//        Show_StaticString(pDvmData, nRow, XRIO_RIO_CB_COL_MAX, &pDvmData->m_strMax);
//    }
//    ShowObjectAttrs(pDvmData,nRow,XRIO_RIO_CB_COL_DESCRIPTION,XRIO_DEVICE_MODEL_ID_Description);
//    ShowObjectAttrs(pDvmData,nRow,XRIO_RIO_CB_COL_VALUEFORMULA,XRIO_DEVICE_MODEL_ID_ValueFormula);

//    if (pDvmData->m_strDataType.Find("OutMatr") > 0)
//    {
//        pDvmData->m_dwReserved = CString_To_long(pDvmData->m_strValue);
//        Show_Hex(pDvmData, nRow, XRIO_RIO_CB_COL_VALUE, &pDvmData->m_dwReserved, 8);
//    }
//    else
//    {
//        Show_String(pDvmData, nRow, XRIO_RIO_CB_COL_VALUE, &pDvmData->m_strValue, EndEditCell_CmdDataValue);
//    }
//    return TRUE;
}

BOOL QDeviceModelGrid_Eng::ShowDvmValueInTable(CDvmValue *pDvmValue, int &nRow)
{
    //2024-9-27现在对展示内容进行修改，原来的展示不严谨，现在改为根据对象的DataType分类进行处理。如果有问题可以注掉现有版本使用原来的。
    //现在除了ID不可以更改外，其余均可以更改。各种限制输入条件会根据不同DataType变化。
    return ShowDvmValue(pDvmValue,nRow);

    //--------------原来版本----------
//    long lEnabled = 1;

//    if(pDvmValue != NULL)
//    {
//        QExBaseListGridBase::Show_Check(pDvmValue, nRow, XRIO_PARAMETER_COL_STATE, &lEnabled,NULL,TRUE);//状态  //可修改勾选状态
//        Show_StaticString(pDvmValue, nRow, XRIO_PARAMETER_COL_NAME, &pDvmValue->m_strName);
//        Show_StaticString(pDvmValue, nRow, XRIO_PARAMETER_COL_ID, &pDvmValue->m_strID);
//        Show_StaticString(pDvmValue, nRow, XRIO_PARAMETER_COL_DATATYPE, &pDvmValue->m_strDataType);
//        Show_StaticString(pDvmValue, nRow, XRIO_PARAMETER_COL_REFVALUE, XRIO_DEVICE_MODEL_DEFAULTVALUE);
//    }
//    ShowObjectAttrs(pDvmValue,nRow,XRIO_PARAMETER_COL_UNIT,XRIO_DEVICE_MODEL_ID_Unit);
//    ShowObjectAttrs(pDvmValue,nRow,XRIO_PARAMETER_COL_MIN,XRIO_DEVICE_MODEL_ID_MinValue);
//    ShowObjectAttrs(pDvmValue,nRow,XRIO_PARAMETER_COL_MAX,XRIO_DEVICE_MODEL_ID_MaxValue);
//    ShowObjectAttrs(pDvmValue,nRow,XRIO_PARAMETER_COL_FOREIGNID,XRIO_DEVICE_MODEL_ID_ForeignId);
//    ShowObjectAttrs(pDvmValue,nRow,XRIO_PARAMETER_COL_DESCRIPTION,XRIO_DEVICE_MODEL_ID_Description);
//    ShowObjectAttrs(pDvmValue,nRow,XRIO_PARAMETER_COL_VALUEFORMULA,XRIO_DEVICE_MODEL_ID_ValueFormula);
//    ShowMultipleValues(pDvmValue,nRow,XRIO_PARAMETER_COL_REFVALUE,XRIO_PARAMETER_COL_VALUE);
//    return TRUE;
}

BOOL QDeviceModelGrid_Eng::ShowObjectAttrs(CExBaseObject *pObj, int &nRow, int nCol, const CString &strID)
{
    CString strTempIDPath;
    strTempIDPath = GetObjectIDPath(pObj->m_strID,strID);
    CExBaseObject *pAttributeValue = ((CExBaseList*)pObj)->FindByID(strTempIDPath);
    if(pAttributeValue != NULL)
    {
        Show_StaticString(pObj, nRow, nCol, &((CDvmValue*)pAttributeValue)->m_strValue);
    }
    else
    {
        Show_StaticString(pObj, nRow, nCol, XRIO_DEVICE_MODEL_DEFAULTVALUE);
    }
    return TRUE;
}

BOOL QDeviceModelGrid_Eng::ShowMultipleValues(CExBaseList *pList, int &nRow, int nRefValueCol, int nValueCol)
{
    CExBaseListComboBox* pRefValueComBox = NULL;
    CExBaseListComboBox* pValueComBox = NULL;

    CDvmValue *pDvmValue = NULL;
    CDvmData *pDvmData = NULL;
    int nIndex = 0;

    for(POS startPos = pList->GetHeadPosition();startPos != pList->GetTailPosition();)
    {
        pDvmValue = (CDvmValue*)pList->GetNext(startPos);
        if(XRIO_CUSTOM_PARAMETER_DATATYPE_ENUMERATION == pDvmValue->m_strDataType)
        {
            ++nIndex;
            if(1 == nIndex)
            {
                pRefValueComBox = new CExBaseListComboBox(NULL);
                pValueComBox = new CExBaseListComboBox(NULL);
                this->setCellWidget(nRow,nRefValueCol,pRefValueComBox);
                this->setCellWidget(nRow,nValueCol,pValueComBox);
                QFont font("Microsoft YaHei",9);
                pRefValueComBox->setFont(font);
                pValueComBox->setFont(font);
            }
            pRefValueComBox->addItem(pDvmValue->m_strValue);
            pValueComBox->addItem(pDvmValue->m_strValue);
        }
    }

    if(nIndex > 0)
    {
        Show_StaticString(pDvmData, nRow, nRefValueCol, XRIO_DEVICE_MODEL_DEFAULTVALUE);
        Show_StaticString(pDvmData, nRow, nValueCol, XRIO_DEVICE_MODEL_DEFAULTVALUE);
        pRefValueComBox->setCurrentIndex(-1);
        if(DVMCLASSID_CDVMDATA == pList->GetClassID())
        {
            pDvmData = (CDvmData*)pList;
            pDvmValue = (CDvmValue*)GetAttrObj(pList,pDvmData->m_strValue);
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
            pValueComBox->setCurrentText(pDvmValue->m_strValue);
#else
			Stt_Global_SetComboBoxIndexByText(pValueComBox,pDvmValue->m_strValue);
#endif
        }
        else if(DVMCLASSID_CDVMVALUE == pList->GetClassID())
        {
            pDvmValue = (CDvmValue*)pList;
            pDvmValue = (CDvmValue*)GetAttrObj(pList,pDvmValue->m_strValue);
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
            pValueComBox->setCurrentText(pDvmValue->m_strValue);
#else
			Stt_Global_SetComboBoxIndexByText(pValueComBox,pDvmValue->m_strValue);
#endif
        }
    }
    else
    {
        if(DVMCLASSID_CDVMDATA == pList->GetClassID())
        {
            pDvmData = (CDvmData*)pList;
            Show_String(pDvmData, nRow, nValueCol, &pDvmData->m_strValue, EndEditCell_CmdDataValue);
        }
        else if(DVMCLASSID_CDVMVALUE == pList->GetClassID())
        {
            pDvmValue = (CDvmValue*)pList;
            Show_String(pDvmValue, nRow, nValueCol, &pDvmValue->m_strValue, EndEditCell_CmdDataValue);
        }
    }
    return TRUE;
}

BOOL QDeviceModelGrid_Eng::ShowDvmDataMultipleValues(CDvmData *pDvmData, int &nRow, int nRefValueCol, int nValueCol, const CString &strID)
{
    CExBaseObject *pObj = NULL;
    CString strTempIDPath;
    strTempIDPath = GetObjectIDPath(pDvmData->m_strID,strID);
    POS pComBoxValuePos = pDvmData->FindPosByID(strTempIDPath);
    if(pComBoxValuePos)
    {
        pDvmData->GetNext(pComBoxValuePos);
    }
    if(pComBoxValuePos)
    {
        Show_StaticString(pDvmData, nRow, nRefValueCol, XRIO_DEVICE_MODEL_DEFAULTVALUE);
        Show_StaticString(pDvmData, nRow, nValueCol, XRIO_DEVICE_MODEL_DEFAULTVALUE);

        CExBaseListComboBox* pRefValueComBox =  new CExBaseListComboBox(NULL);
        this->setCellWidget(nRow,nRefValueCol,pRefValueComBox);

        CExBaseListComboBox* pValueComBox =  new CExBaseListComboBox(NULL);
        this->setCellWidget(nRow,nValueCol,pValueComBox);
        QFont font("Microsoft YaHei",9);
        pRefValueComBox->setFont(font);
        pValueComBox->setFont(font);

        while(pComBoxValuePos)
        {
            pObj = pDvmData->GetNext(pComBoxValuePos);
            pRefValueComBox->addItem(QString("%1").arg(((CDvmValue*)pObj)->m_strValue));
            pValueComBox->addItem(QString("%1").arg(((CDvmValue*)pObj)->m_strValue));
        }
        pRefValueComBox->setCurrentIndex(-1);
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
        pValueComBox->setCurrentText(pDvmData->m_strValue);
#else
		Stt_Global_SetComboBoxIndexByText(pValueComBox,pDvmData->m_strValue);
#endif
    }
    else
    {
        if (pDvmData->m_strDataType.Find("OutMatr") > 0)
        {
            pDvmData->m_dwReserved = CString_To_long(pDvmData->m_strValue);
            Show_Hex(pDvmData, nRow, nValueCol, &pDvmData->m_dwReserved, 8);
        }
        else
        {
            Show_String(pDvmData, nRow, nValueCol, &pDvmData->m_strValue, EndEditCell_CmdDataValue);
        }
    }
    return TRUE;
}

BOOL QDeviceModelGrid_Eng::ShowDvmValueMultipleValues(CDvmValue *pDvmValue, int &nRow, int nRefValueCol, int nValueCol, const CString &strID)
{
    CExBaseObject *pObj = NULL;
    CString strTempIDPath;
    strTempIDPath = GetObjectIDPath(pDvmValue->m_strID,strID);
    POS pComBoxValuePos = pDvmValue->FindPosByID(strTempIDPath);
    if(pComBoxValuePos)
    {
        pDvmValue->GetNext(pComBoxValuePos);
    }
    if(pComBoxValuePos)
    {
        Show_StaticString(pDvmValue, nRow, nRefValueCol, XRIO_DEVICE_MODEL_DEFAULTVALUE);
        Show_StaticString(pDvmValue, nRow, nValueCol, XRIO_DEVICE_MODEL_DEFAULTVALUE);

        CExBaseListComboBox* pRefValueComBox =  new CExBaseListComboBox(NULL);
        this->setCellWidget(nRow,nRefValueCol,pRefValueComBox);

        CExBaseListComboBox* pValueComBox =  new CExBaseListComboBox(NULL);
        this->setCellWidget(nRow,nValueCol,pValueComBox);
        QFont font("Microsoft YaHei",9);
        pRefValueComBox->setFont(font);
        pValueComBox->setFont(font);

        while(pComBoxValuePos)
        {
            pObj = pDvmValue->GetNext(pComBoxValuePos);
            pRefValueComBox->addItem(QString("%1").arg(((CDvmValue*)pObj)->m_strValue));
            pValueComBox->addItem(QString("%1").arg(((CDvmValue*)pObj)->m_strValue));
        }
        pRefValueComBox->setCurrentIndex(-1);
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
        pValueComBox->setCurrentText(pDvmValue->m_strValue);
#else
		Stt_Global_SetComboBoxIndexByText(pValueComBox,pDvmValue->m_strValue);
#endif
    }
    else
    {
        if (pDvmValue->m_strDataType.Find("OutMatr") > 0)
        {
            pDvmValue->m_dwReserved = CString_To_long(pDvmValue->m_strValue);
            Show_Hex(pDvmValue, nRow, nValueCol, &pDvmValue->m_dwReserved, 8);
        }
        else
        {
            Show_String(pDvmValue, nRow, nValueCol, &pDvmValue->m_strValue, EndEditCell_CmdDataValue);
        }
    }
    return TRUE;
}

void QDeviceModelGrid_Eng::EndEditCell_String(int nRow, int nCol, QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
    PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
    ASSERT(pVCellData != NULL && pCell != NULL && pGrid != NULL);
    ASSERT(pVCellData->pObj != NULL);

    //20240708 huangliang
    if(pGrid->IsAttachSettingItem(pCell))
    {
        return ;
    }

    CString strCurrText,strOldText;
    strCurrText = pCell->text();
    strOldText = *pVCellData->pString;

    if(strOldText != strCurrText)
    {
        if(XRIO_PARAMETER_COL_NAME == nCol)
        {
            if(!SetNameInputRestr(pCell,strCurrText,strOldText,pGrid)) //名称输入限制
            {
                return ;
            }
        }

        *pVCellData->pString = strCurrText;
        ((QExBaseListGridBase*)pGrid)->SetModifiedFlag(pVCellData->pObj);
        emit ((QDeviceModelGrid_Eng* )pGrid)->sig_EndEditCellSuccess();

        CString strNamePath = pVCellData->pObj->GetNamePathEx(DVMCLASSID_CDVMDEVICE,FALSE,_T("/"));
        CString strIDPath = GetObjIDPathEx(DVMCLASSID_CDVMDEVICE,pVCellData->pObj,FALSE);
        if(XRIO_PARAMETER_COL_NAME == nCol)
        {
            //"参数修改:(提示信息)-,-Path =【名称路径-%s(ID路径-%s)】名称【%s】更新为【%s】。"
            CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("%s:(%s)-,-Path =【%s-%s(%s-%s)】%s【%s】%s【%s】"),g_sLangTxt_ParaMdf.GetString(),g_sLangTxt_PromptMessage.GetString(),g_sLangTxt_Xrio_LogInfo_NamePath.GetString(),
            strNamePath.GetString(),g_sLangTxt_Xrio_LogInfo_IDPath.GetString(),strIDPath.GetString(),g_sLangTxt_Name.GetString(),strOldText.GetString(),g_sLangTxt_Xrio_LogInfo_UpdateTo.GetString(),strCurrText.GetString());
        }
        else if(XRIO_PARAMETER_COL_FOREIGNID == nCol)
        {
            //"参数修改:(提示信息)-,-Path =【名称路径-%s(ID路径-%s)】不相关【%s】更新为【%s】。"
            CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("%s:(%s)-,-Path =【%s-%s(%s-%s)】%s【%s】%s【%s】"),g_sLangTxt_ParaMdf.GetString(),g_sLangTxt_PromptMessage.GetString(),g_sLangTxt_Xrio_LogInfo_NamePath.GetString(),
            strNamePath.GetString(),g_sLangTxt_Xrio_LogInfo_IDPath.GetString(),strIDPath.GetString(),g_sLangTxt_Xrio_Foreignid.GetString(),strOldText.GetString(),g_sLangTxt_Xrio_LogInfo_UpdateTo.GetString(),strCurrText.GetString());
        }
        else if(XRIO_PARAMETER_COL_DESCRIPTION == nCol)
        {
            //"参数修改:(提示信息)-,-Path =【名称路径-%s(ID路径-%s)】描述【%s】更新为【%s】。"
            CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("%s:(%s)-,-Path =【%s-%s(%s-%s)】%s【%s】%s【%s】"),g_sLangTxt_ParaMdf.GetString(),g_sLangTxt_PromptMessage.GetString(),g_sLangTxt_Xrio_LogInfo_NamePath.GetString(),
            strNamePath.GetString(),g_sLangTxt_Xrio_LogInfo_IDPath.GetString(),strIDPath.GetString(),g_sLangTxt_State_Description.GetString(),strOldText.GetString(),g_sLangTxt_Xrio_LogInfo_UpdateTo.GetString(),strCurrText.GetString());
        }
        else if(XRIO_PARAMETER_COL_VALUE == nCol)
        {
            //"参数修改:(提示信息)-,-Path =【名称路径-%s(ID路径-%s)】值【%s】更新为【%s】。"
            CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("%s:(%s)-,-Path =【%s-%s(%s-%s)】%s【%s】%s【%s】"),g_sLangTxt_ParaMdf.GetString(),g_sLangTxt_PromptMessage.GetString(),g_sLangTxt_Xrio_LogInfo_NamePath.GetString(),
            strNamePath.GetString(),g_sLangTxt_Xrio_LogInfo_IDPath.GetString(),strIDPath.GetString(),g_sLangTxt_Values.GetString(),strOldText.GetString(),g_sLangTxt_Xrio_LogInfo_UpdateTo.GetString(),strCurrText.GetString());
        }
        else if(XRIO_PARAMETER_COL_UNIT == nCol)
        {
            //"参数修改:(提示信息)-,-Path =【名称路径-%s(ID路径-%s)】单位【%s】更新为【%s】。"
            CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("%s:(%s)-,-Path =【%s-%s(%s-%s)】%s【%s】%s【%s】"),g_sLangTxt_ParaMdf.GetString(),g_sLangTxt_PromptMessage.GetString(),g_sLangTxt_Xrio_LogInfo_NamePath.GetString(),
            strNamePath.GetString(),g_sLangTxt_Xrio_LogInfo_IDPath.GetString(),strIDPath.GetString(),g_sLangTxt_Unit.GetString(),strOldText.GetString(),g_sLangTxt_Xrio_LogInfo_UpdateTo.GetString(),strCurrText.GetString());
        }
        else if(XRIO_PARAMETER_COL_VALUEFORMULA == nCol)
        {
            //"参数修改:(提示信息)-,-Path =【名称路径-%s(ID路径-%s)】公式【%s】更新为【%s】。"
            CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("%s:(%s)-,-Path =【%s-%s(%s-%s)】%s【%s】%s【%s】"),g_sLangTxt_ParaMdf.GetString(),g_sLangTxt_PromptMessage.GetString(),g_sLangTxt_Xrio_LogInfo_NamePath.GetString(),
            strNamePath.GetString(),g_sLangTxt_Xrio_LogInfo_IDPath.GetString(),strIDPath.GetString(),g_sLangTxt_Xrio_ValueFormula.GetString(),strOldText.GetString(),g_sLangTxt_Xrio_LogInfo_UpdateTo.GetString(),strCurrText.GetString());
        }
    }
}

void QDeviceModelGrid_Eng::EndEditCell_DataType_Val(int nRow, int nCol, QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
    //当前的nVt一定是String类型并且nReserved == QT_GRID_COMBOBOX_StringType_DataTypeID
    PEXBASECELLDATA pVCellData = (_ExBaseCellData*)pCell->lParam;
    ASSERT(pVCellData->nVt == VCD_STRING)
    ASSERT (pVCellData != NULL);
    ASSERT (pVCellData->pString != NULL);
    ASSERT (pVCellData->pObj != NULL);
    ASSERT(pCell->nReserved == QT_GRID_COMBOBOX_StringType_DataTypeID)

    if (pVCellData->pExBaseList == NULL)
    {
#ifndef NOT_USE_XLANGUAGE
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, /*_T("Row=%d  Col=%d  数据类型对象不存在")*/
            g_sLangTxt_DataTypeUnExist.GetString(), nRow, nCol);
#else
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Row=%d  Col=%d  数据类型对象不存在"), nRow, nCol);
#endif
        return;
    }

    //20240708 huangliang
    if (pGrid->IsAttachSettingItem(pCell))
    {
        return ;
    }

    CDataType *pDataType = (CDataType*)pVCellData->pExBaseList;
    ASSERT (pDataType != NULL);
    CString strTmp = pCell->text();

    CDataTypeValue *pValue = (CDataTypeValue*)pDataType->FindByName(strTmp);
    ASSERT(pValue)
    if(pValue != NULL)
    {
        CString strTempID = GetStringAfterLastDollar(pValue->m_strID);
        if (*(pVCellData->pString) != /*pValue->m_strID*/strTempID)
        {
            *(pVCellData->pString) = /*pValue->m_strID*/strTempID;
            emit ((QDeviceModelGrid_Eng* )pGrid)->sig_EndEditCellSuccess();
            ((QExBaseListGridBase*)pGrid)->SetModifiedFlag(pVCellData->pObj);
//            CString DestFile = _P_GetLibraryPath();
//            DestFile += "test01.xml";
//            CDvmDevice *pDevice = (CDvmDevice*)pVCellData->pObj->GetRoot();
//            pDevice->SaveXmlFile(DestFile, CDataMngrXmlRWKeys::g_pXmlKeys);
        }
    }
}

void QDeviceModelGrid_Eng::EndEditCell_Enumeration(int nRow, int nCol, QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
    //当前的nVt一定是String类型并且nReserved == QT_GRID_COMBOBOX_StringType_DataTypeID
    PEXBASECELLDATA pVCellData = (_ExBaseCellData*)pCell->lParam;
    ASSERT(pVCellData->nVt == VCD_STRING)
    ASSERT (pVCellData != NULL);
    ASSERT (pVCellData->pString != NULL);
    ASSERT (pVCellData->pObj != NULL);
    ASSERT(pCell->nReserved == QT_GRID_COMBOBOX_StringType_DataTypeID)

    if (pVCellData->pExBaseList == NULL)
    {
#ifndef NOT_USE_XLANGUAGE
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, /*_T("Row=%d  Col=%d  数据类型对象不存在")*/
            g_sLangTxt_DataTypeUnExist.GetString(), nRow, nCol);
#else
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Row=%d  Col=%d  数据类型对象不存在"), nRow, nCol);
#endif
        return;
    }

    //20240708 huangliang
    if (pGrid->IsAttachSettingItem(pCell))
    {
        return ;
    }

    CExBaseList *pList = pVCellData->pExBaseList;
    ASSERT (pList != NULL);
    CString strCurrText = pCell->text();
    CString strOldText = *pVCellData->pString;
    CExBaseObject *pObj = pList->FindByName(strCurrText);
    ASSERT(pObj)
    if(pObj != NULL)
    {
        CString strTempID = GetStringAfterLastDollar(pObj->m_strID);
        if (strOldText != strTempID)
        {
            *(pVCellData->pString) = strTempID;
            emit ((QDeviceModelGrid_Eng* )pGrid)->sig_EndEditCellSuccess();
            ((QExBaseListGridBase*)pGrid)->SetModifiedFlag(pVCellData->pObj);

            CString strNamePath = pVCellData->pObj->GetNamePathEx(DVMCLASSID_CDVMDEVICE,FALSE,_T("/"));
            CString strIDPath = GetObjIDPathEx(DVMCLASSID_CDVMDEVICE,pVCellData->pObj,FALSE);
            if(XRIO_PARAMETER_COL_REFVALUE == nCol)
            {
                //"参数修改:(提示信息)-,-Path =【名称路径-%s(ID路径-%s)】参考值【%s】更新为【%s】。"
                CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("%s:(%s)-,-Path =【%s-%s(%s-%s)】%s【%s】%s【%s】"),g_sLangTxt_ParaMdf.GetString(),g_sLangTxt_PromptMessage.GetString(),g_sLangTxt_Xrio_LogInfo_NamePath.GetString(),
                strNamePath.GetString(),g_sLangTxt_Xrio_LogInfo_IDPath.GetString(),strIDPath.GetString(),g_sLangTxt_Xrio_RefValue.GetString(),strOldText.GetString(),g_sLangTxt_Xrio_LogInfo_UpdateTo.GetString(),strTempID.GetString());
            }
            else if(XRIO_PARAMETER_COL_VALUE == nCol)
            {
                //"参数修改:(提示信息)-,-Path =【名称路径-%s(ID路径-%s)】值【%s】更新为【%s】。"
                CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("%s:(%s)-,-Path =【%s-%s(%s-%s)】%s【%s】%s【%s】"),g_sLangTxt_ParaMdf.GetString(),g_sLangTxt_PromptMessage.GetString(),g_sLangTxt_Xrio_LogInfo_NamePath.GetString(),
                strNamePath.GetString(),g_sLangTxt_Xrio_LogInfo_IDPath.GetString(),strIDPath.GetString(),g_sLangTxt_Values.GetString(),strOldText.GetString(),g_sLangTxt_Xrio_LogInfo_UpdateTo.GetString(),strTempID.GetString());
            }
        }
    }
}

void QDeviceModelGrid_Eng::EndEditCell_DoubleString(int nRow, int nCol, QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
    PEXBASECELLDATA pVCellData = (_ExBaseCellData*)pCell->lParam;

    if (pVCellData == NULL)
    {
        return;
    }

    ASSERT (pVCellData != NULL);
    ASSERT (pVCellData->pString != NULL);

    //20240708 huangliang
    if (pGrid->IsAttachSettingItem(pCell))
    {
        return ;
    }

    CString strCurrText,strOldText;
    strOldText = *pVCellData->pString;

    BOOL bGetRestrResultFlag = FALSE; //限制结果标记

    if(XRIO_PARAMETER_COL_REFVALUE == nCol)
    {
        bGetRestrResultFlag = SetRefValInputRestr_DataType_Real(pVCellData,pCell,pGrid);
    }
    else if(XRIO_PARAMETER_COL_VALUE == nCol || XRIO_RIO_CB_COL_VALUE == nCol)
    {
        bGetRestrResultFlag = SetValInputRestr_DataType_Real(pVCellData,pCell,pGrid);
    }
    else if(XRIO_PARAMETER_COL_MIN == nCol)
    {
        bGetRestrResultFlag = SetMinValInputRestr_DataType_Real(pVCellData,pCell,pGrid);
    }
    else if(XRIO_PARAMETER_COL_MAX == nCol)
    {
        bGetRestrResultFlag = SetMaxValInputRestr_DataType_Real(pVCellData,pCell,pGrid);
    }

    strCurrText = pCell->text();

    if(bGetRestrResultFlag)
    {
        ((QExBaseListGridBase*)pGrid)->SetModifiedFlag(pVCellData->pObj);
        emit ((QDeviceModelGrid_Eng* )pGrid)->sig_EndEditCellSuccess();

        CString strNamePath = pVCellData->pObj->GetNamePathEx(DVMCLASSID_CDVMDEVICE,FALSE,_T("/"));
        CString strIDPath = GetObjIDPathEx(DVMCLASSID_CDVMDEVICE,pVCellData->pObj,FALSE);
        if(XRIO_PARAMETER_COL_REFVALUE == nCol)
        {
            //"参数修改:(提示信息)-,-Path =【名称路径-%s(ID路径-%s)】参考值【%s】更新为【%s】。"
            CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("%s:(%s)-,-Path =【%s-%s(%s-%s)】%s【%s】%s【%s】"),g_sLangTxt_ParaMdf.GetString(),g_sLangTxt_PromptMessage.GetString(),g_sLangTxt_Xrio_LogInfo_NamePath.GetString(),
            strNamePath.GetString(),g_sLangTxt_Xrio_LogInfo_IDPath.GetString(),strIDPath.GetString(),g_sLangTxt_Xrio_RefValue.GetString(),strOldText.GetString(),g_sLangTxt_Xrio_LogInfo_UpdateTo.GetString(),strCurrText.GetString());
        }
        else if(XRIO_PARAMETER_COL_VALUE == nCol || XRIO_RIO_CB_COL_VALUE == nCol)
        {
            //"参数修改:(提示信息)-,-Path =【名称路径-%s(ID路径-%s)】值【%s】更新为【%s】。"
            CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("%s:(%s)-,-Path =【%s-%s(%s-%s)】%s【%s】%s【%s】"),g_sLangTxt_ParaMdf.GetString(),g_sLangTxt_PromptMessage.GetString(),g_sLangTxt_Xrio_LogInfo_NamePath.GetString(),
            strNamePath.GetString(),g_sLangTxt_Xrio_LogInfo_IDPath.GetString(),strIDPath.GetString(),g_sLangTxt_Values.GetString(),strOldText.GetString(),g_sLangTxt_Xrio_LogInfo_UpdateTo.GetString(),strCurrText.GetString());
        }
        else if(XRIO_PARAMETER_COL_MIN == nCol)
        {
            //"参数修改:(提示信息)-,-Path =【名称路径-%s(ID路径-%s)】最小值【%s】更新为【%s】。"
            CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("%s:(%s)-,-Path =【%s-%s(%s-%s)】%s【%s】%s【%s】"),g_sLangTxt_ParaMdf.GetString(),g_sLangTxt_PromptMessage.GetString(),g_sLangTxt_Xrio_LogInfo_NamePath.GetString(),
            strNamePath.GetString(),g_sLangTxt_Xrio_LogInfo_IDPath.GetString(),strIDPath.GetString(),g_sLangTxt_MinValue.GetString(),strOldText.GetString(),g_sLangTxt_Xrio_LogInfo_UpdateTo.GetString(),strCurrText.GetString());
        }
        else if(XRIO_PARAMETER_COL_MAX == nCol)
        {
            //"参数修改:(提示信息)-,-Path =【名称路径-%s(ID路径-%s)】最大值【%s】更新为【%s】。"
            CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("%s:(%s)-,-Path =【%s-%s(%s-%s)】%s【%s】%s【%s】"),g_sLangTxt_ParaMdf.GetString(),g_sLangTxt_PromptMessage.GetString(),g_sLangTxt_Xrio_LogInfo_NamePath.GetString(),
            strNamePath.GetString(),g_sLangTxt_Xrio_LogInfo_IDPath.GetString(),strIDPath.GetString(),g_sLangTxt_MaxValue.GetString(),strOldText.GetString(),g_sLangTxt_Xrio_LogInfo_UpdateTo.GetString(),strCurrText.GetString());
        }
    }
}

void QDeviceModelGrid_Eng::EndEditCell_IntString(int nRow, int nCol, QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
    PEXBASECELLDATA pVCellData = (_ExBaseCellData*)pCell->lParam;

    if (pVCellData == NULL)
    {
        return;
    }

    ASSERT (pVCellData != NULL);
    ASSERT (pVCellData->pString != NULL);

    //20240708 huangliang
    if (pGrid->IsAttachSettingItem(pCell))
    {
        return ;
    }

    CString strCurrText,strOldText;
    strOldText = *pVCellData->pString;

    BOOL bGetRestrResultFlag = FALSE; //限制结果标记

    if(XRIO_PARAMETER_COL_REFVALUE == nCol)
    {
        bGetRestrResultFlag = SetRefValInputRestr_DataType_Integer(pVCellData,pCell,pGrid);
    }
    else if(XRIO_PARAMETER_COL_VALUE == nCol)
    {
        bGetRestrResultFlag = SetValInputRestr_DataType_Integer(pVCellData,pCell,pGrid);
    }
    else if(XRIO_PARAMETER_COL_MIN == nCol)
    {
        bGetRestrResultFlag = SetMinValInputRestr_DataType_Integer(pVCellData,pCell,pGrid);
    }
    else if(XRIO_PARAMETER_COL_MAX == nCol)
    {
        bGetRestrResultFlag = SetMaxValInputRestr_DataType_Integer(pVCellData,pCell,pGrid);
    }

    strCurrText = pCell->text();

    if(bGetRestrResultFlag)
    {
        ((QExBaseListGridBase*)pGrid)->SetModifiedFlag(pVCellData->pObj);
        emit ((QDeviceModelGrid_Eng* )pGrid)->sig_EndEditCellSuccess();

        CString strNamePath = pVCellData->pObj->GetNamePathEx(DVMCLASSID_CDVMDEVICE,FALSE,_T("/"));
        CString strIDPath = GetObjIDPathEx(DVMCLASSID_CDVMDEVICE,pVCellData->pObj,FALSE);
        if(XRIO_PARAMETER_COL_REFVALUE == nCol)
        {
            //"参数修改:(提示信息)-,-Path =【名称路径-%s(ID路径-%s)】参考值【%s】更新为【%s】。"
            CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("%s:(%s)-,-Path =【%s-%s(%s-%s)】%s【%s】%s【%s】"),g_sLangTxt_ParaMdf.GetString(),g_sLangTxt_PromptMessage.GetString(),g_sLangTxt_Xrio_LogInfo_NamePath.GetString(),
            strNamePath.GetString(),g_sLangTxt_Xrio_LogInfo_IDPath.GetString(),strIDPath.GetString(),g_sLangTxt_Xrio_RefValue.GetString(),strOldText.GetString(),g_sLangTxt_Xrio_LogInfo_UpdateTo.GetString(),strCurrText.GetString());
        }
        else if(XRIO_PARAMETER_COL_VALUE == nCol)
        {
            //"参数修改:(提示信息)-,-Path =【名称路径-%s(ID路径-%s)】值【%s】更新为【%s】。"
            CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("%s:(%s)-,-Path =【%s-%s(%s-%s)】%s【%s】%s【%s】"),g_sLangTxt_ParaMdf.GetString(),g_sLangTxt_PromptMessage.GetString(),g_sLangTxt_Xrio_LogInfo_NamePath.GetString(),
            strNamePath.GetString(),g_sLangTxt_Xrio_LogInfo_IDPath.GetString(),strIDPath.GetString(),g_sLangTxt_Values.GetString(),strOldText.GetString(),g_sLangTxt_Xrio_LogInfo_UpdateTo.GetString(),strCurrText.GetString());
        }
        else if(XRIO_PARAMETER_COL_MIN == nCol)
        {
            //"参数修改:(提示信息)-,-Path =【名称路径-%s(ID路径-%s)】最小值【%s】更新为【%s】。"
            CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("%s:(%s)-,-Path =【%s-%s(%s-%s)】%s【%s】%s【%s】"),g_sLangTxt_ParaMdf.GetString(),g_sLangTxt_PromptMessage.GetString(),g_sLangTxt_Xrio_LogInfo_NamePath.GetString(),
            strNamePath.GetString(),g_sLangTxt_Xrio_LogInfo_IDPath.GetString(),strIDPath.GetString(),g_sLangTxt_MinValue.GetString(),strOldText.GetString(),g_sLangTxt_Xrio_LogInfo_UpdateTo.GetString(),strCurrText.GetString());
        }
        else if(XRIO_PARAMETER_COL_MAX == nCol)
        {
            //"参数修改:(提示信息)-,-Path =【名称路径-%s(ID路径-%s)】最大值【%s】更新为【%s】。"
            CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("%s:(%s)-,-Path =【%s-%s(%s-%s)】%s【%s】%s【%s】"),g_sLangTxt_ParaMdf.GetString(),g_sLangTxt_PromptMessage.GetString(),g_sLangTxt_Xrio_LogInfo_NamePath.GetString(),
            strNamePath.GetString(),g_sLangTxt_Xrio_LogInfo_IDPath.GetString(),strIDPath.GetString(),g_sLangTxt_MaxValue.GetString(),strOldText.GetString(),g_sLangTxt_Xrio_LogInfo_UpdateTo.GetString(),strCurrText.GetString());
        }
    }
}

void QDeviceModelGrid_Eng::EndEditCell_Check(int nRow, int nCol, QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
    PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
    ASSERT(pVCellData != NULL && pCell != NULL && pGrid != NULL);
    ASSERT(pVCellData->pString != NULL);
    ASSERT(pVCellData->pObj != NULL);

    //20240708 huangliang
    if (pGrid->IsAttachSettingItem(pCell))
    {
        return ;
    }

    CString strCurrText,strOldText;
    strOldText = *pVCellData->pString;

    QDeviceModelGrid_Eng_CheckBox *pCheckBox = qobject_cast<QDeviceModelGrid_Eng_CheckBox*>((QDeviceModelGrid_Eng*)pGrid->cellWidget(nRow, nCol));
    ASSERT(pCheckBox);

    if(pCheckBox->IsChecked())
    {
        strCurrText = XRIO_CUSTOM_PARAMETER_DATATYPE_BOOLEAN_TRUE;//XRIO_CUSTOM_PARAMETER_DATATYPE_BOOLEAN_TRUE_NUMERIC
    }
    else
    {
        strCurrText = XRIO_CUSTOM_PARAMETER_DATATYPE_BOOLEAN_FALSE;//XRIO_CUSTOM_PARAMETER_DATATYPE_BOOLEAN_FALSE_NUMERIC
    }

    if(0 != strCurrText.CompareNoCase(strOldText) &&
    ((XRIO_CUSTOM_PARAMETER_DATATYPE_BOOLEAN_TRUE == strCurrText && XRIO_CUSTOM_PARAMETER_DATATYPE_BOOLEAN_TRUE_NUMERIC != strOldText) ||
     ((XRIO_CUSTOM_PARAMETER_DATATYPE_BOOLEAN_FALSE == strCurrText && XRIO_CUSTOM_PARAMETER_DATATYPE_BOOLEAN_FALSE_NUMERIC != strOldText))))
    {
        *pVCellData->pString = strCurrText;
        ((QExBaseListGridBase*)pGrid)->SetModifiedFlag(pVCellData->pObj);
        emit ((QDeviceModelGrid_Eng* )pGrid)->sig_EndEditCellSuccess();

        CString strNamePath = pVCellData->pObj->GetNamePathEx(DVMCLASSID_CDVMDEVICE,FALSE,_T("/"));
        CString strIDPath = GetObjIDPathEx(DVMCLASSID_CDVMDEVICE,pVCellData->pObj,FALSE);
        if(XRIO_PARAMETER_COL_REFVALUE == nCol)
        {
            //"参数修改:(提示信息)-,-Path =【名称路径-%s(ID路径-%s)】参考值【%s】更新为【%s】。"
            CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("%s:(%s)-,-Path =【%s-%s(%s-%s)】%s【%s】%s【%s】"),g_sLangTxt_ParaMdf.GetString(),g_sLangTxt_PromptMessage.GetString(),g_sLangTxt_Xrio_LogInfo_NamePath.GetString(),
            strNamePath.GetString(),g_sLangTxt_Xrio_LogInfo_IDPath.GetString(),strIDPath.GetString(),g_sLangTxt_Xrio_RefValue.GetString(),strOldText.GetString(),g_sLangTxt_Xrio_LogInfo_UpdateTo.GetString(),strCurrText.GetString());
        }
        else if(XRIO_PARAMETER_COL_VALUE == nCol)
        {
            //"参数修改:(提示信息)-,-Path =【名称路径-%s(ID路径-%s)】值【%s】更新为【%s】。"
            CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("%s:(%s)-,-Path =【%s-%s(%s-%s)】%s【%s】%s【%s】"),g_sLangTxt_ParaMdf.GetString(),g_sLangTxt_PromptMessage.GetString(),g_sLangTxt_Xrio_LogInfo_NamePath.GetString(),
            strNamePath.GetString(),g_sLangTxt_Xrio_LogInfo_IDPath.GetString(),strIDPath.GetString(),g_sLangTxt_Values.GetString(),strOldText.GetString(),g_sLangTxt_Xrio_LogInfo_UpdateTo.GetString(),strCurrText.GetString());
        }
    }
}

void QDeviceModelGrid_Eng::InitGridTitle()
{
    if (m_nTitleType == XRIO_DEVICE_MODEL_GRID_TITLE_TYPE_NORMAL)
    {
        CString astrGridTitle[XRIO_PARAMETER_TABLE_COLS-1] = {/*_T("状态")*//*g_sLangTxt_Syn_State,*//*_T("名称")*/g_sLangTxt_Name,_T("ID"),/*_T("不相关")*/g_sLangTxt_Xrio_Foreignid,
                                                            /*_T("描述")*/g_sLangTxt_State_Description,/*_T("数据类型")*/g_sLangTxt_DataType,/*_T("参考值")*/g_sLangTxt_Xrio_RefValue,/*_T("值")*/g_sLangTxt_Values,
                                                            /*_T("单位")*/g_sLangTxt_Unit,/*_T("最小值")*/g_sLangTxt_MinValue,/*_T("最大值")*/g_sLangTxt_MaxValue,/*_T("公式")*/g_sLangTxt_Xrio_ValueFormula};
        int iGridWidth[XRIO_PARAMETER_TABLE_COLS-1]={/*40, */150, 120, 120, 150, 120, 120, 120, 80, 120, 120, 150};
        QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, XRIO_PARAMETER_TABLE_COLS-1);
    }
    else if (m_nTitleType == XRIO_DEVICE_MODEL_GRID_TITLE_TYPE_CBData)
    {
        CString astrGridTitle[XRIO_RIO_CB_TABLE_COLS-1] = {/*_T("状态")*//*g_sLangTxt_Syn_State,*//*_T("名称")*/g_sLangTxt_Name,_T("ID"),/*_T("描述")*/g_sLangTxt_State_Description,/*_T("值")*/g_sLangTxt_Values,
                                                         /*_T("单位")*/g_sLangTxt_Unit,/*_T("最小值")*/g_sLangTxt_MinValue,/*_T("最大值")*/g_sLangTxt_MaxValue,/*_T("公式")*/g_sLangTxt_Xrio_ValueFormula};
        int iGridWidth[XRIO_RIO_CB_TABLE_COLS-1]={/*40, */150, 120, 150 ,120, 80, 120, 120, 150};
        QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, XRIO_RIO_CB_TABLE_COLS-1);
    }
}

void QDeviceModelGrid_Eng::ShowCBDatas(CExBaseList *pDatas, BOOL bResetScrollBars)
{
    // 	m_idCurrentCell.col = -1;
    // 	m_idCurrentCell.row = -1;
    DisConnectAll_SigSlot();
    //	FreeListVCellData();
    // 	CTLinkList <_ExBaseCellData> listVCellData;
    // 	BackListCellData(listVCellData);
    m_pCurrData = NULL;

    if (pDatas == NULL)
    {
        SetRowCount(0);
        return;
    }

    m_pDatas = pDatas;
    CExBaseObject *pObj = NULL;
    POS pos = pDatas->GetHeadPosition();
    int nRowIndex = 0;//zhouhj Qt中不包括标题行
    long nCalRows = GetDatasCount();//zhouhj Qt中不包括标题行
    SetRowCount(nCalRows, bResetScrollBars);

    while (pos != NULL)
    {
        pObj = pDatas->GetNext(pos);
        ShowCBData(pObj, nRowIndex, FALSE);//
    }

    SetRowCount(nRowIndex, bResetScrollBars);
    AfterShowDatas(1, bResetScrollBars);

}

void QDeviceModelGrid_Eng::ShowCBData(CExBaseObject *pData, int &nRow, BOOL bInsertRow)
{
    CDvmData *pDvmData = (CDvmData*)pData;
    ShowCBDvmDataInTable(pDvmData,nRow);

    //    if (pDvmData->m_nChange == 1)
    //    {
    //        SetItemFgColour(nRow, 2, 255, 0, 0);
    //    }
    //    else
    //    {
    //        SetItemFgColour(nRow, 2, 0, 0, 0);
    //    }
    nRow++;
}

void QDeviceModelGrid_Eng::ShowData(CExBaseObject *pData, int &nRow, BOOL bInsertRow)
{
    if(pData->GetClassID() == DVMCLASSID_CDVMDATA)
    {
        CDvmData *pDvmData = (CDvmData*)pData;
        ShowDvmDataInTable(pDvmData,nRow);
    }
    else if (pData->GetClassID() == DVMCLASSID_CDVMVALUE)
    {
        CDvmValue *pDvmValue = (CDvmValue*)pData;
        ShowDvmValueInTable(pDvmValue,nRow);
    }

    //    if (pDvmData->m_nChange == 1)
    //    {
    //        SetItemFgColour(nRow, 2, 255, 0, 0);
    //    }
    //    else
    //    {
    //        SetItemFgColour(nRow, 2, 0, 0, 0);
    //    }
    nRow++;
}

void QDeviceModelGrid_Eng::EndEditCell_CmdDataValue(int nRow, int nCol, QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
    PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
    ASSERT(pVCellData != NULL && pCell != NULL && pGrid != NULL);
    ASSERT(pVCellData->pObj != NULL);

    if (pVCellData->pString == NULL)
    {
        return;
    }

    if (QString(*pVCellData->pString) != (pCell->text()))
    {
        QString SrcStr = *pVCellData->pString;
        if(pVCellData->pObj->GetClassID() == DVMCLASSID_CDVMDATA)
        {
            if(IsAllDigits((*pVCellData->pString)))
            {
                double MAX;
                double MIN;
                if(!((CDvmData *)pVCellData->pObj)->m_strMin.isEmpty() && !((CDvmData *)pVCellData->pObj)->m_strMax.isEmpty())
                {
                    MAX = ((CDvmData *)pVCellData->pObj)->m_strMax.toDouble();
                    MIN = ((CDvmData *)pVCellData->pObj)->m_strMin.toDouble();
                    if(!SetInputRestrWithMinAndMax(pCell->text(),MAX,MIN,pCell,SrcStr,pVCellData,pGrid))
                    {
                        return;
                    }
                }
                else if(!((CDvmData *)pVCellData->pObj)->m_strMin.isEmpty() && ((CDvmData *)pVCellData->pObj)->m_strMax.isEmpty())
                {
                    MIN = ((CDvmData *)pVCellData->pObj)->m_strMin.toDouble();
                    if(!SetInputRestrWithMin(pCell->text(),MIN,pCell,SrcStr,pVCellData,pGrid))
                    {
                        return;
                    }
                }
                else if(((CDvmData *)pVCellData->pObj)->m_strMin.isEmpty() && !((CDvmData *)pVCellData->pObj)->m_strMax.isEmpty())
                {
                    MAX = ((CDvmData *)pVCellData->pObj)->m_strMax.toDouble();
                    if(!SetInputRestrWithMax(pCell->text(),MAX,pCell,SrcStr,pVCellData,pGrid))
                    {
                        return;
                    }
                }
                else
                {
                    if(!SetInputRestrWithNone(pCell->text(),pCell,SrcStr,pVCellData,pGrid))
                    {
                        return;
                    }
                }
            }
            else
            {
                *pVCellData->pString = pCell->text();
            }
//            CDvmData *pData = (CDvmData*)pVCellData->pObj;
//            pData->m_nChange = 1;
//            pGrid->SetItemFgColour(nRow, XRIO_PARAMETER_COL_NAME, 255, 0, 0);
            //pVCellData->pObj就是设备模型的值，上面的限制函数已经修改，无需在调用下面的信号再次修改。
            //emit ((QDeviceModelGrid_Eng* )pGrid)->sig_XrioDeviceModel_UpdateData((CDvmData *)pVCellData->pObj);
            emit ((QDeviceModelGrid_Eng* )pGrid)->sig_EndEditCellSuccess();
        }
        else if(pVCellData->pObj->GetClassID() == DVMCLASSID_CDVMVALUE)
        {
            if(IsAllDigits((*pVCellData->pString)))
            {
                CString strTempIDPath;
                strTempIDPath = CString("%1$%2").arg(pVCellData->pObj->m_strID).arg(XRIO_DEVICE_MODEL_ID_MaxValue);
                CExBaseObject *MaxValueObj = ((CDvmValue *)pVCellData->pObj)->FindByID(strTempIDPath);
                strTempIDPath = CString("%1$%2").arg(pVCellData->pObj->m_strID).arg(XRIO_DEVICE_MODEL_ID_MinValue);
                CExBaseObject *MinValueObj = ((CDvmValue *)pVCellData->pObj)->FindByID(strTempIDPath);
                double MIN;
                double MAX;
                if(MaxValueObj != NULL && MinValueObj != NULL)
                {
                    if(!((CDvmValue*)MinValueObj)->m_strValue.isEmpty() && !((CDvmValue*)MaxValueObj)->m_strValue.isEmpty())
                    {
                        MIN = ((CDvmValue*)MinValueObj)->m_strValue.toDouble();
                        MAX = ((CDvmValue*)MaxValueObj)->m_strValue.toDouble();
                        if(!SetInputRestrWithMinAndMax(pCell->text(),MAX,MIN,pCell,SrcStr,pVCellData,pGrid))
                        {
                            return;
                        }
                    }
                    else if(!((CDvmValue*)MinValueObj)->m_strValue.isEmpty() && ((CDvmValue*)MaxValueObj)->m_strValue.isEmpty())
                    {
                        MIN = ((CDvmValue*)MinValueObj)->m_strValue.toDouble();
                        if(!SetInputRestrWithMin(pCell->text(),MIN,pCell,SrcStr,pVCellData,pGrid))
                        {
                            return;
                        }
                    }
                    else if(((CDvmValue*)MinValueObj)->m_strValue.isEmpty() && !((CDvmValue*)MaxValueObj)->m_strValue.isEmpty())
                    {
                        MAX = ((CDvmValue*)MaxValueObj)->m_strValue.toDouble();
                        if(!SetInputRestrWithMax(pCell->text(),MAX,pCell,SrcStr,pVCellData,pGrid))
                        {
                            return;
                        }
                    }
                    else
                    {
                        if(!SetInputRestrWithNone(pCell->text(),pCell,SrcStr,pVCellData,pGrid))
                        {
                            return;
                        }
                    }
                }
            }
            else
            {
                *pVCellData->pString = pCell->text();
            }
//            CDvmValue *pValue = (CDvmValue*)pVCellData->pObj;
//            pValue->m_nChange = 1;
//            pGrid->SetItemFgColour(nRow, XRIO_PARAMETER_COL_NAME, 255, 0, 0);
            //pVCellData->pObj就是设备模型的值，上面的限制函数已经修改，无需在调用下面的信号再次修改。
            //emit ((QDeviceModelGrid_Eng* )pGrid)->sig_XrioDeviceModel_UpdateValue((CDvmValue *)pVCellData->pObj);
            emit ((QDeviceModelGrid_Eng* )pGrid)->sig_EndEditCellSuccess();
        }
    }
    //    else
    //    {
    //        //这个分支如果修改的值和之前一样只有点击被修改的单元格以外的地方才会让确定按钮使能，但如果是使用回车确定，则确定按钮不会使能，暂时无法解决。
    //        emit ((QDeviceModelGrid_Eng*)pGrid)->sig_EndEditCellSuccess();
    //    }
    //emit ((QDeviceModelGrid_Eng*)pGrid)->sig_EndEditCellSuccess();
}

BOOL QDeviceModelGrid_Eng::AddListRef(CExBaseObject *pSelObj, CExBaseList *pList)
{
    if(!pSelObj)
    {
        return FALSE;
    }
    //    CExBaseObject* pObj = NULL;
    CExBaseObject* pSubObj = NULL;

    POS pos = ((CExBaseList*)pSelObj)->GetHeadPosition();
    POS SubPos = NULL;
    while(pos)
    {
        pSubObj = ((CExBaseList*)pSelObj)->GetNext(pos);
        if(pSubObj != NULL)
        {
            SubPos = ((CExBaseList*)pSubObj)->GetHeadPosition();
        }
        while(SubPos)
        {
            CExBaseList* pGrandchildrenList = (CExBaseList*)((CExBaseList*)pSubObj)->GetNext(SubPos);
            if(pGrandchildrenList->GetCount() <= 0)
            {
                if(((CDvmValue*)pGrandchildrenList)->m_strValue == XRIO_DEVICE_MODEL_ID_ForeignId)
                {
                    break;
                }
                if(pGrandchildrenList->GetClassID() == DVMCLASSID_CDVMDATA)//针对普通的设备数据模型存在Data节点没有Value节点的情况，如果有也不添加。
                {
                    break;
                }
                pList->AddTail(pSubObj);
                break;
            }
        }
    }
    return TRUE;
}

void QDeviceModelGrid_Eng::ClearCurrentContents()
{
    //在清空当前表格前，先将ShowDvmValue_DataType_Enumeration中new的对象进行释放，再释放QDeviceModelGrid_Eng_CheckBox对象。
    FreeCellListAndWidget();
    this->clearContents();
    this->SetRowCount(0);
}

void QDeviceModelGrid_Eng::FreeCellListAndWidget()
{
    int nMaxRow = GetRowCount();
    PEXBASECELLDATA pVCellRefValData = NULL,pVCellValData = NULL;
    QWidget *pWidget = NULL;

    for(int nRow = 0;nRow < nMaxRow; ++nRow)
    {
        pVCellRefValData = (PEXBASECELLDATA)GetItemData(nRow,XRIO_PARAMETER_COL_REFVALUE);
        if(pVCellRefValData != NULL)
        {
            if(pVCellRefValData->pExBaseList != NULL)
            {
//                CLogPrint::LogString(XLOGLEVEL_TRACE,_T("pVCellData的链表不为空"));
                pVCellRefValData->pExBaseList->DeleteHead();//只删除参考值下拉框中的第一个默认值_T("")节点。
                pVCellRefValData->pExBaseList->RemoveAll();//清空链表
                delete pVCellRefValData->pExBaseList;//删除链表指向的内存
                pVCellRefValData->pExBaseList = NULL;
            }
        }

        pWidget = cellWidget(nRow,XRIO_PARAMETER_COL_REFVALUE);
        if(pWidget != NULL)
        {
//            CLogPrint::LogString(XLOGLEVEL_TRACE,_T("pWidget不为空"));
            delete pWidget;
            pWidget = NULL;
        }
        removeCellWidget(nRow,XRIO_PARAMETER_COL_REFVALUE);//将当前的单元格Widget置为空。

        pVCellValData = (PEXBASECELLDATA)GetItemData(nRow,XRIO_PARAMETER_COL_VALUE);
        if(pVCellValData != NULL)
        {
            if(pVCellValData->pExBaseList != NULL)
            {
//                CLogPrint::LogString(XLOGLEVEL_TRACE,_T("pVCellData的链表不为空"));
                pVCellValData->pExBaseList->RemoveAll();//清空链表
                delete pVCellRefValData->pExBaseList;//删除链表指向的内存
                pVCellRefValData->pExBaseList = NULL;
            }
        }

        pWidget = cellWidget(nRow,XRIO_PARAMETER_COL_VALUE);
        if(pWidget != NULL)
        {
//            CLogPrint::LogString(XLOGLEVEL_TRACE,_T("pWidget不为空"));
            delete pWidget;
            pWidget = NULL;
        }
        removeCellWidget(nRow,XRIO_PARAMETER_COL_VALUE);//将当前的单元格Widget置为空。
    }
}

CDvmValue *QDeviceModelGrid_Eng::GetDataValue(CDvmData *pData)
{
    if (pData->GetCount() == 0)
    {
        return (CDvmValue*)pData->GetHead();
    }

    POS pos = pData->GetHeadPosition();
    CDvmValue *p = NULL;
    CString strRight;

    while (pos != NULL)
    {
        p = (CDvmValue *)pData->GetNext(pos);
        strRight = p->m_strID.right(2);

        if (strRight == "$t" || strRight == "$q")
        {
            continue;
        }

        return p;
    }

    return (CDvmValue*)pData->GetHead();
}

void QDeviceModelGrid_Eng::UpdateChangeState()
{
    if (m_pDatas == NULL)
    {
        return;
    }

    long nRow = 0;
    POS pos = m_pDatas->GetHeadPosition();
    CDvmData *pData = NULL;

    while (pos != NULL)
    {
        pData = (CDvmData *)m_pDatas->GetNext(pos);

        if (pData->m_nChange == 1)
        {
            SetItemFgColour(nRow, 2, 255, 0, 0);
        }
        else
        {
            SetItemFgColour(nRow, 2, 0, 0, 0);
        }
    }
}

void QDeviceModelGrid_Eng::DisConnectAll_SigSlot()
{
    QExBaseListGridBase::DisConnectAll_SigSlot();
}

void QDeviceModelGrid_Eng::ConnectAll_SigSlot()
{
    QExBaseListGridBase::ConnectAll_SigSlot();
}

void QDeviceModelGrid_Eng::slot_CellChanged(int nrow, int ncol)
{
    QGV_ITEM* pitem = (QGV_ITEM*)item(nrow,ncol);
    long nRows = GetRowCount();

    if(pitem == NULL)
    {
        return;
    }

    //20240708 huangliang
    if (IsAttachSettingItem(pitem))
    {
        return ;
    }

    //此处同一列的不同行存在ComBobox和CheckBox，但同一列至多存在同一个代理控件，当前表格使用的是ComBobox的代理控件，因此CheckBox代理需要在此处重新调用回调。
    if ((pitem->m_pEditFunc != NULL)&&((pitem->nDataType == QT_GVET_EDITBOX && itemDelegateForColumn(ncol) == NULL) || pitem->nDataType == QT_GVET_CHECKBOX))
    {
        pitem->m_pEditFunc(nrow,ncol,pitem,this);
    }

    //	OnChanDataChanged(pitem);
}

void QDeviceModelGrid_Eng::slot_cellDoubleClicked(int row, int column)
{
    if (row == -1 || column == -1)
    {
        return;
    }

    if (m_pDataViewOptrInterface != NULL)
    {
        m_pDataViewOptrInterface->OnEditCellLBDblClk(this, row, column, 0);
    }
}

void QDeviceModelGrid_Eng::slot_CheckBox_LeftClicked(int &nRow, int &nCol)
{
    this->setCurrentCell(nRow, nCol);
}

void QDeviceModelGrid_Eng::InitConnect()
{

}

BOOL QDeviceModelGrid_Eng::SetNameInputRestr(QGV_ITEM *pCell,const CString &strCurrText,const CString &strOldText,QExBaseListGridBase *pGrid)
{
    if(strCurrText.isEmpty())
    {
        CXMessageBox::information((QDeviceModelGrid_Eng*)pGrid,g_sLangTxt_Xrio_XrioError,g_sLangTxt_Xrio_InvalidName);
        pCell->UpdateText(strOldText);
        return FALSE;
    }
    return TRUE;
}

BOOL QDeviceModelGrid_Eng::SetRefValInputRestr_DataType_Real(PEXBASECELLDATA pVCellData,QGV_ITEM *pCell,QExBaseListGridBase *pGrid)
{
    if(pCell->text().isEmpty())
    {
        if(!pVCellData->pString->isEmpty())
        {
            *pVCellData->pString = pCell->text();//更新旧值
            return TRUE;
        }
        return FALSE;
    }
    else
    {
        return SetValInputRestr_DataType_Real(pVCellData,pCell,pGrid);
    }
}

BOOL QDeviceModelGrid_Eng::SetValInputRestr_DataType_Real(PEXBASECELLDATA pVCellData, QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
    CString strCurrText,strTmp,strOldText,strFormat;
    bool bOk = FALSE;
    strCurrText = pCell->text();
    strOldText = *pVCellData->pString;

    double dValue = strCurrText.toDouble(&bOk);
    double dOldValue = CString_To_double(strOldText);
#ifdef _PSX_QT_LINUX_
    if(!bOk || (bOk &&std:: isnan(dValue)))//转换失败,说明有非法字符,使用之前的内容
    {
        CXMessageBox::information((QDeviceModelGrid_Eng*)pGrid,g_sLangTxt_Xrio_XrioError,g_sLangTxt_Xrio_EnterNumbers);
        pCell->UpdateText(strOldText);
        return FALSE;
    }
#else
    if(!bOk || (bOk && _isnan(dValue)))//转换失败,说明有非法字符,使用之前的内容
    {
        CXMessageBox::information((QDeviceModelGrid_Eng*)pGrid,g_sLangTxt_Xrio_XrioError,g_sLangTxt_Xrio_EnterNumbers);
        pCell->UpdateText(strOldText);
        return FALSE;
    }
#endif
    else
    {
        double dMinValue,dMaxValue;
        CString strMinValue,strMaxValue;
        long nPrecision = (pCell->dwValue >> 16) & 0xFFFF;

        if(DVMCLASSID_CDVMDATA == pVCellData->pObj->GetClassID())
        {
            CDvmData *pDvmData = (CDvmData*)pVCellData->pObj;
            GetDvmDataMinAndMax_DataType_Real(pDvmData,dMinValue,dMaxValue,strMinValue,strMaxValue);
        }
        else if(DVMCLASSID_CDVMVALUE == pVCellData->pObj->GetClassID())
        {
            CDvmValue *pDvmValue = (CDvmValue*)pVCellData->pObj;
            GetDvmValueMinAndMax_DataType_Real(pDvmValue,dMinValue,dMaxValue,strMinValue,strMaxValue);
        }

        strFormat.Format(_T("%%.%ldlf"), nPrecision);
        strTmp.Format(strFormat.GetString(), dValue);
        dValue = CString_To_double(strTmp);

        //暂时不考虑double溢出问题。
        //初始化后此处一定不会为Nan
        if(DOUBLE_LESS == DoubleFuzzyCompare(dValue,dMinValue))
        {
            strFormat.Format(_T("%%.%ldlf"), nPrecision);
            strTmp.Format(strFormat.GetString(), dMinValue);
#ifdef _PSX_QT_LINUX_
             strTmp = !std::isfinite(dMinValue)?XRIO_DEVICE_MODEL_POSITIVE_INF:strTmp;
#else
            strTmp = !_finite(dMinValue)?XRIO_DEVICE_MODEL_POSITIVE_INF:strTmp;
#endif
            CXMessageBox::information((QDeviceModelGrid_Eng*)pGrid,g_sLangTxt_Xrio_XrioError,g_sLangTxt_Xrio_ValueGreaterThanOREqual + strTmp);
            pCell->UpdateText(strOldText);
            return FALSE;
        }

        //初始化后此处一定不会为Nan
        if(DOUBLE_GREATER == DoubleFuzzyCompare(dValue,dMaxValue))
        {
            strFormat.Format(_T("%%.%ldlf"), nPrecision);
            strTmp.Format(strFormat.GetString(), dMaxValue);
#ifdef _PSX_QT_LINUX_
             strTmp = !std::isfinite(dMinValue)?XRIO_DEVICE_MODEL_NEGATIVE_INF:strTmp;
#else
            strTmp = !_finite(dMaxValue)?XRIO_DEVICE_MODEL_NEGATIVE_INF:strTmp;
 #endif
            CXMessageBox::information((QDeviceModelGrid_Eng*)pGrid,g_sLangTxt_Xrio_XrioError,g_sLangTxt_Xrio_ValueLessThanOREqual + strTmp);
            pCell->UpdateText(strOldText);
            return FALSE;
        }

        //qFuzzyCompare
        //初始化后此处一定不会为Nan
        if(DOUBLE_EQUAL != DoubleFuzzyCompare(dValue,dOldValue))
        {
            disconnect((QDeviceModelGrid_Eng*)pGrid,SIGNAL(cellChanged(int,int)),(QDeviceModelGrid_Eng*)pGrid,SLOT(slot_CellChanged(int,int)));
            pCell->UpdateText(strTmp);
            *pVCellData->pString = pCell->text();
            connect((QDeviceModelGrid_Eng*)pGrid,SIGNAL(cellChanged(int,int)),(QDeviceModelGrid_Eng*)pGrid,SLOT(slot_CellChanged(int,int)));
            return TRUE;
        }
        return FALSE;
    }
}

BOOL QDeviceModelGrid_Eng::SetMinValInputRestr_DataType_Real(PEXBASECELLDATA pVCellData, QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
    CString strCurrText,strTmp,strOldText,strFormat;
    bool bOk = FALSE;
    strCurrText = pCell->text();
    strOldText = *pVCellData->pString;

    double dValue = strCurrText.toDouble(&bOk);//当前新值
    double dOldValue = CString_To_double(strOldText);//旧值
#ifdef _PSX_QT_LINUX_
    if(!bOk || (bOk &&std:: isnan(dValue)))//转换失败,说明有非法字符,使用之前的内容
    {
        CXMessageBox::information((QDeviceModelGrid_Eng*)pGrid,g_sLangTxt_Xrio_XrioError,g_sLangTxt_Xrio_InvalidDoublePrecisionValue);
        pCell->UpdateText(strOldText);
        return FALSE;
    }
#else
    if(!bOk || (bOk && _isnan(dValue)))//转换失败,说明有非法字符,使用之前的内容
    {
        CXMessageBox::information((QDeviceModelGrid_Eng*)pGrid,g_sLangTxt_Xrio_XrioError,g_sLangTxt_Xrio_InvalidDoublePrecisionValue);
        pCell->UpdateText(strOldText);
        return FALSE;
    }
#endif
    else
    {
        double dAttrValue;//属性值
        CString strAttrValue;
        long nPrecision = (pCell->dwValue >> 16) & 0xFFFF;

        if(DVMCLASSID_CDVMDATA == pVCellData->pObj->GetClassID())
        {
            CDvmData *pDvmData = (CDvmData*)pVCellData->pObj;
            strAttrValue = pDvmData->m_strValue;
            dAttrValue = CString_To_double(strAttrValue);
        }
        else if(DVMCLASSID_CDVMVALUE == pVCellData->pObj->GetClassID())
        {
            CDvmValue *pDvmValue = (CDvmValue*)pVCellData->pObj;
            strAttrValue = pDvmValue->m_strValue;
            dAttrValue = CString_To_double(strAttrValue);
        }

        strFormat.Format(_T("%%.%ldlf"), nPrecision);
        strTmp.Format(strFormat.GetString(), dValue);
        dValue = CString_To_double(strTmp);

        //初始化后此处一定不会为Nan
        if(DOUBLE_GREATER == DoubleFuzzyCompare(dValue,dAttrValue))
        {
            strFormat.Format(_T("%%.%ldlf"), nPrecision);
            strTmp.Format(strFormat.GetString(), dAttrValue);
#ifdef _PSX_QT_LINUX_
             strTmp = !std::isfinite(dAttrValue)?XRIO_DEVICE_MODEL_NEGATIVE_INF:strTmp;
#else
            strTmp = !_finite(dAttrValue)?XRIO_DEVICE_MODEL_NEGATIVE_INF:strTmp;
#endif
            CXMessageBox::information((QDeviceModelGrid_Eng*)pGrid,g_sLangTxt_Xrio_XrioError,g_sLangTxt_Xrio_ValueLessThanOREqual + strTmp);
            pCell->UpdateText(strOldText);
            return FALSE;
        }

        //qFuzzyCompare
        //初始化后此处一定不会为Nan
        if(DOUBLE_EQUAL != DoubleFuzzyCompare(dValue,dOldValue))
        {
            disconnect((QDeviceModelGrid_Eng*)pGrid,SIGNAL(cellChanged(int,int)),(QDeviceModelGrid_Eng*)pGrid,SLOT(slot_CellChanged(int,int)));
            pCell->UpdateText(strTmp);
            *pVCellData->pString = pCell->text();
            connect((QDeviceModelGrid_Eng*)pGrid,SIGNAL(cellChanged(int,int)),(QDeviceModelGrid_Eng*)pGrid,SLOT(slot_CellChanged(int,int)));
            return TRUE;
        }
        return FALSE;
    }
}

BOOL QDeviceModelGrid_Eng::SetMaxValInputRestr_DataType_Real(PEXBASECELLDATA pVCellData, QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
    CString strCurrText,strTmp,strOldText,strFormat;
    bool bOk = FALSE;
    strCurrText = pCell->text();
    strOldText = *pVCellData->pString;

    double dValue = strCurrText.toDouble(&bOk);//当前新值
    double dOldValue = CString_To_double(strOldText);//旧值
#ifdef _PSX_QT_LINUX_
    if(!bOk || (bOk &&std:: isnan(dValue)))//转换失败,说明有非法字符,使用之前的内容
    {
        CXMessageBox::information((QDeviceModelGrid_Eng*)pGrid,g_sLangTxt_Xrio_XrioError,g_sLangTxt_Xrio_InvalidDoublePrecisionValue);
        pCell->UpdateText(strOldText);
        return FALSE;
    }
#else
    if(!bOk || (bOk && _isnan(dValue)))//转换失败,说明有非法字符,使用之前的内容
    {
        CXMessageBox::information((QDeviceModelGrid_Eng*)pGrid,g_sLangTxt_Xrio_XrioError,g_sLangTxt_Xrio_InvalidDoublePrecisionValue);
        pCell->UpdateText(strOldText);
        return FALSE;
    }
#endif
    else
    {
        double dAttrValue;//属性值
        CString strAttrValue;
        long nPrecision = (pCell->dwValue >> 16) & 0xFFFF;

        if(DVMCLASSID_CDVMDATA == pVCellData->pObj->GetClassID())
        {
            CDvmData *pDvmData = (CDvmData*)pVCellData->pObj;
            strAttrValue = pDvmData->m_strValue;
            dAttrValue = CString_To_double(strAttrValue);
        }
        else if(DVMCLASSID_CDVMVALUE == pVCellData->pObj->GetClassID())
        {
            CDvmValue *pDvmValue = (CDvmValue*)pVCellData->pObj;
            strAttrValue = pDvmValue->m_strValue;
            dAttrValue = CString_To_double(strAttrValue);
        }

        strFormat.Format(_T("%%.%ldlf"), nPrecision);
        strTmp.Format(strFormat.GetString(), dValue);
        dValue = CString_To_double(strTmp);

        //初始化后此处一定不会为Nan
        if(DOUBLE_LESS == DoubleFuzzyCompare(dValue,dAttrValue))
        {
            strFormat.Format(_T("%%.%ldlf"), nPrecision);
            strTmp.Format(strFormat.GetString(), dAttrValue);
#ifdef _PSX_QT_LINUX_
             strTmp = !std::isfinite(dAttrValue)?XRIO_DEVICE_MODEL_POSITIVE_INF:strTmp;
#else
            strTmp = !_finite(dAttrValue)?XRIO_DEVICE_MODEL_POSITIVE_INF:strTmp;
#endif
            CXMessageBox::information((QDeviceModelGrid_Eng*)pGrid,g_sLangTxt_Xrio_XrioError,g_sLangTxt_Xrio_ValueGreaterThanOREqual + strTmp);
            pCell->UpdateText(strOldText);
            return FALSE;
        }

        //qFuzzyCompare
        //初始化后此处一定不会为Nan
        if(DOUBLE_EQUAL != DoubleFuzzyCompare(dValue,dOldValue))
        {
            disconnect((QDeviceModelGrid_Eng*)pGrid,SIGNAL(cellChanged(int,int)),(QDeviceModelGrid_Eng*)pGrid,SLOT(slot_CellChanged(int,int)));
            pCell->UpdateText(strTmp);
            *pVCellData->pString = pCell->text();
            connect((QDeviceModelGrid_Eng*)pGrid,SIGNAL(cellChanged(int,int)),(QDeviceModelGrid_Eng*)pGrid,SLOT(slot_CellChanged(int,int)));
            return TRUE;
        }
        return FALSE;
    }
}

BOOL QDeviceModelGrid_Eng::SetRefValInputRestr_DataType_Integer(PEXBASECELLDATA pVCellData, QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
    if(pCell->text().isEmpty())
    {
        if(!pVCellData->pString->isEmpty())
        {
            *pVCellData->pString = pCell->text();//更新旧值
            return TRUE;
        }
        return FALSE;
    }
    else
    {
        return SetValInputRestr_DataType_Integer(pVCellData,pCell,pGrid);
    }
}

BOOL QDeviceModelGrid_Eng::SetValInputRestr_DataType_Integer(PEXBASECELLDATA pVCellData, QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
    CString strCurrText,strTmp,strOldText;
    bool bOk = FALSE;
    strCurrText = pCell->text();
    strOldText = *pVCellData->pString;

    int nValue = strCurrText.toInt(&bOk);
    int nOldValue = strOldText.toInt();

    if(!bOk)//转换失败,说明有非法字符,使用之前的内容
    {
        CXMessageBox::information((QDeviceModelGrid_Eng*)pGrid,g_sLangTxt_Xrio_XrioError,g_sLangTxt_Xrio_InvalidIntValue);
        pCell->UpdateText(strOldText);
        return FALSE;
    }
    else
    {
        int nMinValue,nMaxValue;
        CString strMinValue,strMaxValue;

        if(DVMCLASSID_CDVMDATA == pVCellData->pObj->GetClassID())
        {
            CDvmData *pDvmData = (CDvmData*)pVCellData->pObj;
            GetDvmDataMinAndMax_DataType_Integer(pDvmData,nMinValue,nMaxValue,strMinValue,strMaxValue);
        }
        else if(DVMCLASSID_CDVMVALUE == pVCellData->pObj->GetClassID())
        {
            CDvmValue *pDvmValue = (CDvmValue*)pVCellData->pObj;
            GetDvmValueMinAndMax_DataType_Integer(pDvmValue,nMinValue,nMaxValue,strMinValue,strMaxValue);
        }

        if(nValue < nMinValue)
        {
            CXMessageBox::information((QDeviceModelGrid_Eng*)pGrid,g_sLangTxt_Xrio_XrioError,g_sLangTxt_Xrio_ValueGreaterThanOREqual + strMinValue);
            pCell->UpdateText(strOldText);
            return FALSE;
        }

        if(nValue > nMaxValue)
        {
            CXMessageBox::information((QDeviceModelGrid_Eng*)pGrid,g_sLangTxt_Xrio_XrioError,g_sLangTxt_Xrio_ValueLessThanOREqual + strMaxValue);
            pCell->UpdateText(strOldText);
            return FALSE;
        }

        if(nValue != nOldValue)
        {
            strTmp.Format(_T("%d"), nValue);
            pCell->UpdateText(strTmp);
            *pVCellData->pString = pCell->text();
            return TRUE;
        }
        return FALSE;
    }
}

BOOL QDeviceModelGrid_Eng::SetMinValInputRestr_DataType_Integer(PEXBASECELLDATA pVCellData, QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
    CString strCurrText,strTmp,strOldText;
    bool bOk = FALSE;
    strCurrText = pCell->text();
    strOldText = *pVCellData->pString;

    int nValue = strCurrText.toInt(&bOk);
    int nOldValue = strOldText.toInt();

    if(!bOk)//转换失败,说明有非法字符,使用之前的内容
    {
        CXMessageBox::information((QDeviceModelGrid_Eng*)pGrid,g_sLangTxt_Xrio_XrioError,g_sLangTxt_Xrio_InvalidIntValue);
        pCell->UpdateText(strOldText);
        return FALSE;
    }
    else
    {
        int nAttrValue;
        CString strAttrValue;

        if(DVMCLASSID_CDVMDATA == pVCellData->pObj->GetClassID())
        {
            CDvmData *pDvmData = (CDvmData*)pVCellData->pObj;
            strAttrValue = pDvmData->m_strValue;
            nAttrValue = pDvmData->m_strValue.toInt();
        }
        else if(DVMCLASSID_CDVMVALUE == pVCellData->pObj->GetClassID())
        {
            CDvmValue *pDvmValue = (CDvmValue*)pVCellData->pObj;
            strAttrValue = pDvmValue->m_strValue;
            nAttrValue = pDvmValue->m_strValue.toInt();
        }

        if(nValue > nAttrValue)
        {
            CXMessageBox::information((QDeviceModelGrid_Eng*)pGrid,g_sLangTxt_Xrio_XrioError,g_sLangTxt_Xrio_ValueLessThanOREqual + strAttrValue);
            pCell->UpdateText(strOldText);
            return FALSE;
        }

        if(nValue != nOldValue)
        {
            strTmp.Format(_T("%d"), nValue);
            pCell->UpdateText(strTmp);
            *pVCellData->pString = pCell->text();
            return TRUE;
        }
        return FALSE;
    }
}

BOOL QDeviceModelGrid_Eng::SetMaxValInputRestr_DataType_Integer(PEXBASECELLDATA pVCellData, QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
    CString strCurrText,strTmp,strOldText;
    bool bOk = FALSE;
    strCurrText = pCell->text();
    strOldText = *pVCellData->pString;

    int nValue = strCurrText.toInt(&bOk);
    int nOldValue = strOldText.toInt();

    if(!bOk)//转换失败,说明有非法字符,使用之前的内容
    {
        CXMessageBox::information((QDeviceModelGrid_Eng*)pGrid,g_sLangTxt_Xrio_XrioError,g_sLangTxt_Xrio_InvalidIntValue);
        pCell->UpdateText(strOldText);
        return FALSE;
    }
    else
    {
        int nAttrValue;
        CString strAttrValue;

        if(DVMCLASSID_CDVMDATA == pVCellData->pObj->GetClassID())
        {
            CDvmData *pDvmData = (CDvmData*)pVCellData->pObj;
            strAttrValue = pDvmData->m_strValue;
            nAttrValue = pDvmData->m_strValue.toInt();
        }
        else if(DVMCLASSID_CDVMVALUE == pVCellData->pObj->GetClassID())
        {
            CDvmValue *pDvmValue = (CDvmValue*)pVCellData->pObj;
            strAttrValue = pDvmValue->m_strValue;
            nAttrValue = pDvmValue->m_strValue.toInt();
        }

        if(nValue < nAttrValue)
        {
            CXMessageBox::information((QDeviceModelGrid_Eng*)pGrid,g_sLangTxt_Xrio_XrioError,g_sLangTxt_Xrio_ValueGreaterThanOREqual + strAttrValue);
            pCell->UpdateText(strOldText);
            return FALSE;
        }

        if(nValue != nOldValue)
        {
            strTmp.Format(_T("%d"), nValue);
            pCell->UpdateText(strTmp);
            *pVCellData->pString = pCell->text();
            return TRUE;
        }
        return FALSE;
    }
}

BOOL QDeviceModelGrid_Eng::IsAllDigits(const QString &str)
{
    // 去除字符串两端的空格
    QString trimmedStr = str.trimmed();

    // 如果字符串为空，则不是数字
    if(trimmedStr.isEmpty())
    {
         return FALSE;
    }

    // 检查可选的正负号
    BOOL hasSign = (trimmedStr.startsWith('-') || trimmedStr.startsWith('+')) && trimmedStr.length() > 1;
    QString numberStr = hasSign ? trimmedStr.mid(1) : trimmedStr;

    // 检查小数点（如果有的话）
    int dotIndex = numberStr.indexOf('.');
    BOOL hasDot = dotIndex != -1;

    // 遍历字符串，检查每个字符
    for(int i = 0; i < numberStr.length(); ++i)
    {
        QChar ch = numberStr.at(i);

        // 如果当前位置是小数点，则跳过，但确保它不是第一个或最后一个字符
        if(i == dotIndex)
        {
            if(i == 0 || i == numberStr.length() - 1)
            {
                return FALSE; // 小数点不能是第一个或最后一个字符
            }
            continue; // 跳过小数点的进一步检查
        }

        // 检查字符是否是数字
        if(!ch.isDigit())
        {
            return FALSE; // 发现非数字字符，失败
        }
    }

    // 如果没有小数点，或者小数点后还有字符，则通过检查
    // 但如果小数点是字符串中的唯一字符（如"."），则失败
    if(hasDot && dotIndex == numberStr.length() - 1)
    {
        return FALSE; // 小数点后没有数字
    }

    // 字符串通过所有检查
    return TRUE;
}

BOOL QDeviceModelGrid_Eng::SetInputRestrWithMin(const QString &str, double MIN, QGV_ITEM *pCell, QString SrcStr, PEXBASECELLDATA pVCellData,QExBaseListGridBase *pGrid)
{
    if(IsAllDigits(str))
    {
        if(str.toDouble() < MIN )
        {
            CXMessageBox::information((QDeviceModelGrid_Eng*)pGrid, g_sLangTxt_Xrio_XrioError, QString(QString(g_sLangTxt_Xrio_ValueGreaterThanOREqual)+QString::number(MIN)));
            pCell->UpdateText(SrcStr);
            return FALSE;
        }
        else
        {
            *pVCellData->pString = str;
            return TRUE;
        }
    }
    else
    {
        CXMessageBox::information((QDeviceModelGrid_Eng*)pGrid, g_sLangTxt_Xrio_XrioError, g_sLangTxt_Xrio_EnterNumbers);
        pCell->UpdateText(SrcStr);
        return FALSE;
    }
}

BOOL QDeviceModelGrid_Eng::SetInputRestrWithMax(const QString &str, double MAX, QGV_ITEM *pCell, QString SrcStr, PEXBASECELLDATA pVCellData,QExBaseListGridBase *pGrid)
{
    if(IsAllDigits(str))
    {
        if(str.toDouble() > MAX)
        {
            CXMessageBox::information((QDeviceModelGrid_Eng*)pGrid,g_sLangTxt_Xrio_XrioError, QString(QString(g_sLangTxt_Xrio_ValueLessThanOREqual)+QString::number(MAX)));
            pCell->UpdateText(SrcStr);
            return FALSE;
        }
        else
        {
            *pVCellData->pString = str;
            return TRUE;
        }
    }
    else
    {
        CXMessageBox::information((QDeviceModelGrid_Eng*)pGrid, g_sLangTxt_Xrio_XrioError, g_sLangTxt_Xrio_EnterNumbers);
        pCell->UpdateText(SrcStr);
        return FALSE;
    }
}

BOOL QDeviceModelGrid_Eng::SetInputRestrWithNone(const QString &str, QGV_ITEM *pCell, QString SrcStr, PEXBASECELLDATA pVCellData,QExBaseListGridBase *pGrid)
{
    if(IsAllDigits(str))
    {
        *pVCellData->pString = str;
        return TRUE;
    }
    else
    {
        CXMessageBox::information((QDeviceModelGrid_Eng*)pGrid, g_sLangTxt_Xrio_XrioError, g_sLangTxt_Xrio_EnterNumbers);
        pCell->UpdateText(SrcStr);
        return FALSE;
    }
}

BOOL QDeviceModelGrid_Eng::SetInputRestrWithMinAndMax(const QString &str,double MAX,double MIN,QGV_ITEM *pCell,QString SrcStr,PEXBASECELLDATA pVCellData,QExBaseListGridBase *pGrid)
{
    if(IsAllDigits(str))
    {
        if(str.toDouble() < MIN )
        {
            CXMessageBox::information((QDeviceModelGrid_Eng*)pGrid, g_sLangTxt_Xrio_XrioError, QString(QString(g_sLangTxt_Xrio_ValueGreaterThanOREqual)+QString::number(MIN)));
            pCell->UpdateText(SrcStr);
            return FALSE;
        }
        else if(str.toDouble() > MAX)
        {
            CXMessageBox::information((QDeviceModelGrid_Eng*)pGrid, g_sLangTxt_Xrio_XrioError, QString(QString(g_sLangTxt_Xrio_ValueLessThanOREqual)+QString::number(MAX)));
            pCell->UpdateText(SrcStr);
            return FALSE;
        }
        else
        {
            *pVCellData->pString = str;
            return TRUE;
        }
    }
    else
    {
        CXMessageBox::information((QDeviceModelGrid_Eng*)pGrid,g_sLangTxt_Xrio_XrioError,g_sLangTxt_Xrio_EnterNumbers);
        pCell->UpdateText(SrcStr);
        return FALSE;
    }
}
