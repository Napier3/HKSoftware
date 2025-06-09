#ifndef QDeviceModelGrid_Eng_H
#define QDeviceModelGrid_Eng_H
#include <QLineEdit>
#include "../../../../../Module/OSInterface/QT/XMessageBox.h"
#include "../../../XLangResource_Native.h"
#include "../../../../../Module/BaseClass/QT/QExBaseListComboBox.h"
#include "../../../../../AutoTest/Module/XrioRead/XDeviceModel/XDeviceModel.h"
#include "../../../UI/Module/QExBaseListGridBase/QExBaseListGridBase.h"
#include "../../../UI/Module/QExBaseListGridBase/QExBaseListComBoxDelegBase.h"

//XRIO_PARAMETER
#define XRIO_PARAMETER_TABLE_COLS         12

//#define XRIO_PARAMETER_COL_STATE          0 //暂时先去除状态列
#define XRIO_PARAMETER_COL_NAME           /*1*/0
#define XRIO_PARAMETER_COL_ID             /*2*/1
#define XRIO_PARAMETER_COL_FOREIGNID      /*3*/2
#define XRIO_PARAMETER_COL_DESCRIPTION    /*4*/3
#define XRIO_PARAMETER_COL_DATATYPE       /*5*/4
#define XRIO_PARAMETER_COL_REFVALUE       /*6*/5
#define XRIO_PARAMETER_COL_VALUE          /*7*/6
#define XRIO_PARAMETER_COL_UNIT           /*8*/7
#define XRIO_PARAMETER_COL_MIN            /*9*/8
#define XRIO_PARAMETER_COL_MAX            /*10*/9
#define XRIO_PARAMETER_COL_VALUEFORMULA   /*11*/10

// XRIO_RIO_CB
#define XRIO_RIO_CB_TABLE_COLS            9

//#define XRIO_RIO_CB_COL_STATE             0//暂时先去除状态列
#define XRIO_RIO_CB_COL_NAME              /*1*/0
#define XRIO_RIO_CB_COL_ID                /*2*/1
#define XRIO_RIO_CB_COL_DESCRIPTION       /*3*/2
#define XRIO_RIO_CB_COL_VALUE             /*4*/3
#define XRIO_RIO_CB_COL_UNIT              /*5*/4
#define XRIO_RIO_CB_COL_MIN               /*6*/5
#define XRIO_RIO_CB_COL_MAX               /*7*/6
#define XRIO_RIO_CB_COL_VALUEFORMULA      /*8*/7

#define XRIO_DEVICE_MODEL_GRID_TITLE_TYPE_NULL            0
#define XRIO_DEVICE_MODEL_GRID_TITLE_TYPE_NORMAL          1
#define XRIO_DEVICE_MODEL_GRID_TITLE_TYPE_CBData          2

//#define QDEVICEMODELGRID_ENG_CHECKkBOX_SINGLE_CLICK_TIMEOUT     200 // QDeviceModelGrid_Eng_CheckBox勾选控件类的单击超时常量200毫秒

// QDeviceModelGrid_Eng_CheckBox勾选框控件
class QDeviceModelGrid_Eng_CheckBox : public QWidget
{
    Q_OBJECT
public:
    QDeviceModelGrid_Eng_CheckBox(QWidget *parent = NULL);
    virtual ~QDeviceModelGrid_Eng_CheckBox();
    void SetChecked(BOOL bIsChecked);
    BOOL IsChecked() const;
    void SetEditable(BOOL bEditable);
    void SetRowIndexAndColIndex(const int &nRow, const int &nCol);
protected:
    virtual void paintEvent(QPaintEvent *);
    virtual void mousePressEvent(QMouseEvent *mouseEvent);
    virtual void mouseDoubleClickEvent(QMouseEvent *mouseEvent); // 添加双击事件处理,此处仍然需要双击事件,不然无法触发QDeviceModelGrid_Eng表格的双击信号。
//    virtual void timerEvent(QTimerEvent *event); // 添加定时器事件处理
signals:
    void CheckBoxStateChanged(BOOL bStateValue);
    void CheckBox_LeftClicked(int &nRow, int &nCol);
private:
    void InitStyleSheet();
private:
    BOOL m_bIsChecked;
    int m_nRowIndex;
    int m_nColIndex;
    QPixmap m_oSelectedPixmap;       // 选中图标
    QPixmap m_oUnselectedPixmap;     // 未选中图标
//    QBasicTimer m_timer;             // 定时器
//    BOOL m_bSingleClick;             // 标识是否单击
};

class QDeviceModelGrid_Eng_ComBoxDelegBase : public QExBaseListComBoxDelegBase
{

public:
    QDeviceModelGrid_Eng_ComBoxDelegBase(QObject *parent=NULL);
    virtual ~QDeviceModelGrid_Eng_ComBoxDelegBase();
    virtual QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index ) const;
    virtual void setEditorData(QWidget * editor, const QModelIndex &index) const;
    virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
};

class QDeviceModelGrid_Eng:public QExBaseListGridBase
{
    Q_OBJECT
public:
    QDeviceModelGrid_Eng(QWidget* pparent = 0);
    virtual ~QDeviceModelGrid_Eng();

public:
    virtual void InitGrid();
    virtual void InitGridTitle();
    virtual void ShowCBDatas(CExBaseList *pDatas, BOOL bResetScrollBars=TRUE);
    virtual void ShowCBData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
    virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
    static void EndEditCell_CmdDataValue(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);
    BOOL AddListRef(CExBaseObject* pSelObj,CExBaseList *pList);
    void ClearCurrentContents();
    void FreeCellListAndWidget();

    //---------------------暂时用不到----------------//
    CDvmValue* GetDataValue(CDvmData *pData);
    void UpdateChangeState();
    //----------------------------------------------//

    void UpdateTitle(long nTitleType);
protected:
    long m_nTitleType;
    BOOL GetCurrObjIsEnabled(CExBaseObject *pObj, const CString &strID);
    static void GetDvmDataMinAndMax_DataType_Real(CDvmData *pDvmData, double &dMinValue, double &dMaxValue, CString &strMinValue, CString &strMaxValue);
    static void GetDvmValueMinAndMax_DataType_Real(CDvmValue *pDvmValue, double &dMinValue, double &dMaxValue, CString &strMinValue, CString &strMaxValue);
    static void GetDvmDataMinAndMax_DataType_Integer(CDvmData *pDvmData, int &nMinValue, int &nMaxValue, CString &strMinValue, CString &strMaxValue);
    static void GetDvmValueMinAndMax_DataType_Integer(CDvmValue *pDvmValue, int &nMinValue, int &nMaxValue, CString &strMinValue, CString &strMaxValue);

    //------------------------------------------暂时用不到-------------------------------------------------//
    //自身的属性如果变化已经在编辑处理函数中修改更新过了，无需再次调用下面函数进行修改。
    //修改自身属性值
    static BOOL ModifyOwnAttrVal(CString &strOwnValue,const CString& strNewValue);
    //修改额外添加属性值
    static BOOL ModifyAddAttrVal(CExBaseList *pList, const CString& strID, const CString& strNewValue);
    //修改DvmData属性值
    static BOOL ModifyDvmData_AttrVal(CDvmData *pDvmData, int nCol ,const CString& strNewValue);
    //修改DvmValue属性值
    static BOOL ModifyDvmValue_AttrVal(CDvmValue *pDvmValue, int nCol, const CString& strNewValue);
    //----------------------------------------------------------------------------------------------------//

    //展示额外添加的属性：不相关，描述，参考值，单位，最大值，最小值，公式
    BOOL ShowDvmValue_AddAttrValue_String(CExBaseObject* pObj, int &nRow, int nCol, const CString &strID, BOOL bCanEdit = TRUE);
    BOOL ShowDvmValue_AddAttrValue_DoubleString(CExBaseObject* pObj, int &nRow, int nCol, const CString &strID, long nPrecision, BOOL bCanEdit = TRUE);
    BOOL ShowDvmValue_AddAttrValue_IntString(CExBaseObject* pObj, int &nRow, int nCol, const CString &strID, BOOL bCanEdit = TRUE);

    //CDvmData类型
    BOOL ShowDvmData(CDvmData *pDvmData, int &nRow);
    BOOL ShowDvmData_DataType_String(CDvmData *pDvmData, int &nRow);//字符串类型
    BOOL ShowDvmData_DataType_Real(CDvmData *pDvmData, int &nRow);//double类型，默认保存小数点后两位
    BOOL ShowDvmData_DataType_Enumeration(CDvmData *pDvmData, int &nRow);//枚举类型
    BOOL ShowDvmData_DataType_Integer(CDvmData *pDvmData, int &nRow);//int类型
    BOOL ShowDvmData_DataType_Boolean(CDvmData *pDvmData, int &nRow);//布尔类型
    BOOL ShowDvmData_DataType_Default(CDvmData *pDvmData, int &nRow);//当前如果存在不属于上述五种外的数据类型，统一转化成字符串类型处理。

    //CDvmValue类型
    BOOL ShowDvmValue(CDvmValue *pDvmValue, int &nRow);
    BOOL ShowDvmValue_DataType_String(CDvmValue *pDvmValue, int &nRow);//字符串类型
    BOOL ShowDvmValue_DataType_Real(CDvmValue *pDvmValue, int &nRow);//double类型，默认保存小数点后两位
    BOOL ShowDvmValue_DataType_Enumeration(CDvmValue *pDvmValue, int &nRow);//枚举类型
    BOOL ShowDvmValue_DataType_Integer(CDvmValue *pDvmValue, int &nRow);//int类型
    BOOL ShowDvmValue_DataType_Boolean(CDvmValue *pDvmValue, int &nRow);//布尔类型
    BOOL ShowDvmValue_DataType_Default(CDvmValue *pDvmValue, int &nRow);//当前如果存在不属于上述五种外的数据类型，统一转化成字符串类型处理。

    //Show方法
    virtual void Show_DataType_Val(CExBaseObject *pData, const int& nRow, const int& nCol, CDataType *pDataType, CString *pstrValue, GRID_CELL_EDIT_FUNC pFunc=NULL);
    virtual void Show_Enumeration(CExBaseObject *pData, const int& nRow, const int& nCol, CExBaseList *pList, CString *pstrValue, GRID_CELL_EDIT_FUNC pFunc=NULL);
    virtual void Show_Double(CExBaseObject *pData, const int& nRow, const int& nCol, long nPrecision, CString *pstrValue, BOOL bCanEdit = TRUE, GRID_CELL_EDIT_FUNC pFunc=NULL, BOOL bUnitConversion=TRUE);
    virtual void Show_Int(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pstrValue, BOOL bCanEdit = TRUE,GRID_CELL_EDIT_FUNC pFunc=NULL);
    virtual void Show_Check(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pstrCheck, GRID_CELL_EDIT_FUNC pFunc=NULL, BOOL bCanEdit=TRUE);

    //原来版本的函数
    BOOL ShowDvmDataInTable(CDvmData* pDvmData, int &nRow);
    BOOL ShowCBDvmDataInTable(CDvmData* pDvmData, int &nRow);
    BOOL ShowDvmValueInTable(CDvmValue* pDvmValue, int &nRow);
    BOOL ShowObjectAttrs(CExBaseObject* pObj, int &nRow, int nCol, const CString &strID);
    BOOL ShowMultipleValues(CExBaseList *pList, int &nRow, int nRefValueCol, int nValueCol);

    //------------------------------------------------------暂时用不到-------------------------------------------------------//
    //下面两个函数被上面的ShowMultipleValues替代。
    BOOL ShowDvmDataMultipleValues(CDvmData* pDvmData,int &nRow,int nRefValueCol,int nValueCol,const CString &strID);
    BOOL ShowDvmValueMultipleValues(CDvmValue* pDvmValue,int &nRow,int nRefValueCol,int nValueCol,const CString &strID);
    //----------------------------------------------------------------------------------------------------------------------//

public:
    //编辑处理函数
    static void EndEditCell_String(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);//字符串类型编辑处理函数
    static void EndEditCell_DataType_Val(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);//枚举类型编辑处理函数
    static void EndEditCell_Enumeration(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);//枚举类型编辑处理函数
    static void EndEditCell_DoubleString(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);//double类型编辑处理函数
    static void EndEditCell_IntString(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);//int类型编辑处理函数
    static void EndEditCell_Check(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);//布尔类型编辑处理函数

    virtual void DisConnectAll_SigSlot();
    virtual void ConnectAll_SigSlot();
signals:
    void sig_ScrollFinished();
    void sig_EndEditCellSuccess();
public slots:
    void slot_CellChanged(int nrow,int ncol);
    virtual void slot_cellDoubleClicked(int row, int column);
    void slot_CheckBox_LeftClicked(int &nRow, int &nCol);
private:
    void InitConnect();
    //名称输入限制
    static BOOL SetNameInputRestr(QGV_ITEM *pCell, const CString &strCurrText, const CString &strOldText, QExBaseListGridBase *pGrid);//名称属性输入限制
    //double类型输入限制
    static BOOL SetRefValInputRestr_DataType_Real(PEXBASECELLDATA pVCellData, QGV_ITEM *pCell, QExBaseListGridBase *pGrid);//double类型参考值属性输入限制
    static BOOL SetValInputRestr_DataType_Real(PEXBASECELLDATA pVCellData, QGV_ITEM *pCell, QExBaseListGridBase *pGrid);//double类型值属性输入限制
    static BOOL SetMinValInputRestr_DataType_Real(PEXBASECELLDATA pVCellData, QGV_ITEM *pCell, QExBaseListGridBase *pGrid);//double类型最小值属性输入限制
    static BOOL SetMaxValInputRestr_DataType_Real(PEXBASECELLDATA pVCellData, QGV_ITEM *pCell, QExBaseListGridBase *pGrid);//double类型最大值属性输入限制
    //int类型输入限制
    static BOOL SetRefValInputRestr_DataType_Integer(PEXBASECELLDATA pVCellData, QGV_ITEM *pCell, QExBaseListGridBase *pGrid);//int类型参考值属性输入限制
    static BOOL SetValInputRestr_DataType_Integer(PEXBASECELLDATA pVCellData, QGV_ITEM *pCell, QExBaseListGridBase *pGrid);//int类型值属性输入限制
    static BOOL SetMinValInputRestr_DataType_Integer(PEXBASECELLDATA pVCellData, QGV_ITEM *pCell, QExBaseListGridBase *pGrid);//int类型最小值属性输入限制
    static BOOL SetMaxValInputRestr_DataType_Integer(PEXBASECELLDATA pVCellData, QGV_ITEM *pCell, QExBaseListGridBase *pGrid);//int类型最大值属性输入限制
    //原来版本输入限制
    static BOOL IsAllDigits(const QString &str);
    static BOOL SetInputRestrWithMinAndMax(const QString &str, double MAX, double MIN, QGV_ITEM *pCell, QString SrcStr, PEXBASECELLDATA pVCellData, QExBaseListGridBase *pGrid);
    static BOOL SetInputRestrWithMin(const QString &str, double MIN, QGV_ITEM *pCell, QString SrcStr, PEXBASECELLDATA pVCellData, QExBaseListGridBase *pGrid);
    static BOOL SetInputRestrWithMax(const QString &str, double MAX, QGV_ITEM *pCell, QString SrcStr, PEXBASECELLDATA pVCellData, QExBaseListGridBase *pGrid);
    static BOOL SetInputRestrWithNone(const QString &str, QGV_ITEM *pCell, QString SrcStr, PEXBASECELLDATA pVCellData, QExBaseListGridBase *pGrid);

private:
    QExBaseListCheckBoxDelegate *m_pCheckBoxDelegateBase;//2024-9-13 wuxinyi checkbox居中代理
    QDeviceModelGrid_Eng_ComBoxDelegBase  *m_pRefValueComBoxDeleBase;
    QDeviceModelGrid_Eng_ComBoxDelegBase  *m_pValueComBoxDeleBase;
};

#endif // QDeviceModelGrid_Eng_H
