#ifndef QDeviceModelDlg_Eng_H
#define QDeviceModelDlg_Eng_H
#include <QFrame>
#include <QDebug>
#include <QDialog>
#include <QSplitter>
#include <QTextEdit>
#include <QFileDialog>
#include <QVBoxLayout>
#include <QPushButton>
#include "QDeviceModelGrid_Eng.h"
#include "QDeviceModelTreeCtrl_Eng.h"
#include "QDeviceModelAttrWidget_Eng.h"
#include "../../../UI/SttTestCntrCmdDefine.h"
#include "../../../../../AutoTest/Module/XrioRead/XrioToCharacterTool.h"
#include "../../../../../AutoTest/Module/XrioRead/XrioToDeviceModelTool.h"
#include "../../../../../AutoTest/Module/XrioRead/SettingFilesToXrioTool.h"
#include "../../../../../AutoTest/Module/XrioRead/XrioTextFileToAtsCharTool.h"
#include "../../../../../AutoTest/Module/GbItemsGen/GbSmartGenWzd/GbSmartGenWzd.h"
#include "../../../UI/Module/CharLibWidget/InternationalModeUI/CharEditMainDialog.h"

//当前界面模式
#define _FIXED_VALUE_CORRELATION_TYPE_           0 //定值关联模式
#define _FIXED_VALUE_MODIFICATION_TYPE_          1 //定值修改模式

//XRIO文件
#define IMPORT_XRIO_FILE_TYPE                   _T("XRIO(*.xrio)|*.xrio||")
#define IMPORT_XRIO_FILE_TITLE                  _T("XRIO");
//XRIO文件和RIO文件
#define IMPORT_XRIO_RIO_FILE_TYPE               _T("XRIO/RIO(*.xrio;*.rio)|*.xrio;*.rio||")
#define IMPORT_XRIO_RIO_FILE_TITLE              _T("XRIO/RIO");
//SET、CSV、TXT文件
#define UPDATE_XRIO_SET_CSV_TXT_FILE_TYPE       _T("XRIO/SET/CSV/TXT(*.xrio;*.set;*.csv;*.txt)|*.xrio;*.set;*.csv;*.txt||")
#define UPDATE_XRIO_SET_CSV_TXT_FILE_TITLE      _T("XRIO/SET/CSV/TXT")

class QDeviceModelTreeCtrl_Eng;

extern CGbSmartGenWzd *g_theGbSmartGenWzd;
namespace Ui {
class QDeviceModelDlg_Eng;
}

class QDeviceModelDlg_Eng : public QDialog,public CExBaseListTreeOptrInterface,public CExBaseListGridOptrInterface
{
    Q_OBJECT

public:
	explicit QDeviceModelDlg_Eng( QWidget *parent = 0);
    virtual ~QDeviceModelDlg_Eng();

	void InitXrioDeviceModel(CXDeviceModel *pXrioDeviceModel);
    void SetXrioDeviceModelUIIDAndParas(const CString &strTestMacroUI_ID, CDataGroup *pTestMacroUI_Paras);
	CExBaseObject* GetCurrSelData();
	CExBaseObject* GetCurrSelData_Global();
	CString GetCurrSelDataPath();
    BOOL m_bHasModifyDevModel;//标记当前设备数据模型值被修改
	BOOL m_bHasChangedXrio;//标记重新导入Xrio当前设备数据模型被删除重新创建
    BOOL m_bHasUpdateXrio;//标记更新Xrio当前的设备数据模型 暂时用不上
    long m_nDlgModeType;//标记当前的模式选择,定值关联还是定值修改
    CCharacterFolder *m_pCharacterFolder;//要更新给外层曲线编辑界面的对象
    CString m_sEpExpressionFormat;	//20240815 huangliang 记录原表达式，传入为名称的表达式，传出为对象地址的表达式
    CString m_sEpExpressionName;

	void InsertFunc(const CString &strText, BOOL bFunc=TRUE);	//20240819 huangliang
	void CharToGroupDatas(CDataGroup *pDatas);//将特性曲线界面参数数据赋值给模板视图数据
protected:
    virtual BOOL OnItemBDblClk(CExBaseListTreeCtrl  *pTreeCtrl, CExBaseObject *pSelObj);
    virtual void OnItemSelChanged(CExBaseListTreeCtrl *pTreeCtrl, CExBaseObject *pSelObj);
    virtual void OnDataSelChanged(QTableWidget *pGridCtrl, int nRow, int nCol);
    virtual BOOL OnEditCellLBDblClk(QTableWidget *pGridCtrl, int nRow, int nCol, UINT nChar);
    virtual void OnDataEditChanged(QTableWidget *pGridCtrl, int nRow, int nCol);
    virtual void EnableBtns();
	BOOL IsEditableCharact(const CString &strCharactDataType);//判断是否为可编辑的曲线,需要当前功能ID与对应的曲线匹配
    enum Operation{Import,Update};
    BOOL XrioOperationSwitch(BOOL &XrioFileOperateType/*该参数标记Xrio文件重新导入还是更新*/,const Operation &OperationType);//用来切换是导入操作还是更新操作

    CString OpenFileDlg(const CString& OpenFileType ,const CString& OpenFileTitle,BOOL bIsOpen = TRUE);
    BOOL OpenFile(const CString& OpenFileType,const CString& OpenFileTitle);
	CXDeviceModel *m_pXrioDeviceModel;
	QDeviceModelGrid_Eng* m_pDeviceModelGrid_Eng;
private:
    CString m_strUI_ID;//界面功能UI_ID
    CDataGroup m_oUI_Paras;//界面功能UI_Paras
    void HideTextEditDisplay();
    void InitUI();//界面文字多语言处理
    void InitConnect();
	CExBaseList m_oDvmGridListRef;//zhouhj 2024.7.26 之前使用new的方式存在内存泄漏，且采用AddNewChild方式，破坏了类的继承关系
    CXrioToDeviceModelTool m_oXrioToDeviceModelTool;
	CXrioToCharacterTool m_oXrioToCharacterTool;
    CSettingFilesToXrioTool m_oSettingFilesToXrioTool;
    CXrioTextFileToAtsCharTool m_oXrioTextFileToAtsCharTool;
    QFrame *m_pGridFrame;
    QFrame *m_pTreeCtrlFrame;
    CString m_strFilePath;
    QDeviceModelTreeCtrl_Eng*m_pDeviceModelTreeCtrl_Eng;
    Ui::QDeviceModelDlg_Eng *ui;
signals:
    void sig_InsertTextEdit();
private slots:
    void slot_XrioDeviceModel_UpdateDeviceAttrs(CDvmDataset* pDataset);
    void slot_InsertTextEdit();
    void slot_AfterEndEditGridCellSuccess();
    void slot_TextEditChanged();
//    void slot_onItemClicked(QTableWidgetItem*);
private slots:
	void on_m_btnEdit_clicked();
    void on_m_btnImport_clicked();
    void on_m_btnOk_clicked();
    void on_m_btnCancel_clicked();
    void on_m_btnUpdate_clicked();
    void on_m_btnSin_clicked();
    void on_m_btnCoS_clicked();
    void on_m_btnTan_clicked();
    void on_m_btnAsin_clicked();
    void on_m_btnAcos_clicked();
    void on_m_btnAtan_clicked();
    void on_m_btnSind_clicked();
    void on_m_btnCosd_clicked();
    void on_m_btnTgd_clicked();
    void on_m_btnAsind_clicked();
    void on_m_btnAcosd_clicked();
    void on_m_btnAtgd_clicked();
    void on_m_btnSqrt_clicked();
    void on_m_btnAbs_clicked();
    void on_m_btnExp_clicked();
    void on_m_btnAddition_clicked();
    void on_m_btnSubtraction_clicked();
    void on_m_btnMultiplication_clicked();
    void on_m_btnDivision_clicked();
    void on_m_btnLeftParenthesis_clicked();
    void on_m_btnRightParenthesis_clicked();
};

#endif // QDeviceModelDlg_Eng_H
