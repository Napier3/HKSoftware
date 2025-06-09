#ifndef CSCLFILE_READ_H
#define CSCLFILE_READ_H

#include <QList>
#include <QString>
#include <QStringList>
#include <QObject>
#include <QMessageBox>
#include <QProgressDialog>
#include <QList>
#include <QHash>

#include "../SCL/SclIecCfgDatas.h"
#include "../../../Module/BaseClass/ThreadProgressInterface.h"
#include <QWidget>

#define SCL_FILE_PARSE_USE_XPUGI//zhouhj 2024.2.2 SCL解析采用xpugl方式,即采用char*方式

#ifdef SCL_FILE_PARSE_USE_XPUGI
#include "../../../Module/xml/XPugiXML/xpugixml.hpp"
#else
#include "../../../Module/xml/PugiXML/pugixml.hpp"
#endif

//using namespace xpugi;

//订阅信息
typedef struct  SCL_SUB_REC_INFO_QT
{
    //内部虚端子信息
    QString ref;
    QString desc;

    //外部虚端子信息
    QString sub_IED_name;
    QString sub_ldInst;
    QString sub_ref;

    int index_IED;
    int index_GSE_SMV;
    int index_Rec;

}SCL_SUB_REC_INFO_QT;

//发布信息
typedef struct SCL_CONNECT_PUB_INFO_QT
{
    int index_IED;
    int index_Rec;
}SCL_CONNECT_PUB_INFO_QT;

typedef struct  SCL_PUB_REC_INFO_QT
{
    QString ref;
    QString desc;
    QString bType;
    //一条信息发布给多个IED
    QList<SCL_CONNECT_PUB_INFO_QT> recPubList;
	virtual ~SCL_PUB_REC_INFO_QT()
	{
		recPubList.clear();
	}
}SCL_PUB_REC_INFO_QT;

//GOOSE发送数据块
typedef struct SCL_GSE_INFO_QT
{
    QString apName;    //访问点名称
    QString apDesc;

    QString cbName;    //控制块名称
    QString ldInst;    //逻辑设备
    QString desc;      //控制块注释
    //Address
    QString MAC_Adress;
    QString VLAN_ID;
    QString VLAN_PRIORITY;
    QString APPID;

    int MinTime;
    int MaxTime;

    QString datSet;    //数据集名称
    QString confRev;    //版本号
    QString goID;    //goID

    int recNum;    //数据集通道个数
    QString DataSetDesc;    //数据集注释

    //一个控制块，多条记录
    QList<SCL_PUB_REC_INFO_QT> pubList;

	virtual ~SCL_GSE_INFO_QT()
	{
		pubList.clear();
	}
}SCL_GSE_INFO_QT;

//SMV发送数据块
typedef struct SCL_SMV_INFO_QT
{
    QString apName;
    QString apDesc;

    QString cbName;
    QString ldInst;
    QString desc;
    //Address
    QString MAC_Adress;
    QString VLAN_ID;
    QString APPID;
    QString VLAN_PRIORITY;

    //SampledValueControl
    QString datSet;
    QString confRev;
    QString SmvID;
//  QString multicast;    //暂时不用
    int smpRate;
    int nofASDU;

    //SmvOpts
    bool refreshTime;    //刷新时间
    bool sampleSynchronized;    //同步采样
    bool sampleRate;    //采样速率
    bool security;    //完全
    bool dataRef;    //数据引用

    int recNum;
    QString DataSetDesc;

    //一个控制块，多条记录
    QList<SCL_PUB_REC_INFO_QT> pubList;

	virtual ~SCL_SMV_INFO_QT()
	{
		pubList.clear();
	}
}SCL_SMV_INFO_QT;

//IED的信息
typedef struct SCL_IED_INFO_QT
{
    QString name;
    QString type;
    QString manufacturer;
    QString configVersion;
    QString desc;

    QList<SCL_GSE_INFO_QT> GSEList;
    QList<SCL_SMV_INFO_QT> SMVList;

    QList<SCL_SUB_REC_INFO_QT> GOSubList;
    QList<SCL_SUB_REC_INFO_QT> SVSubList;
	virtual ~SCL_IED_INFO_QT()
	{
		GSEList.clear();
		SMVList.clear();
		GOSubList.clear();
		SVSubList.clear();
	}
}SCL_IED_INFO_QT;

class QSclFileRead//:public QWidget
{
 //   Q_OBJECT

public:
	QSclFileRead();
//    explicit CXML(QWidget *parent=0);
	virtual ~QSclFileRead();

    BOOL ReadSclFile(const CString &strSclFilePath, CSclStation *pSclStation);   //装载SCD文件
	BOOL IsTscdSclFile(const CString &strSclFilePath); //20240117 gongyiping 是否存在TSCD文件
    BOOL SavePscdFile(const CString &strPscdFilePath);   //保存解析结果
	void SetProgressInterface(CThreadProgressInterface *pProgressInterface){m_pProgressInterface = pProgressInterface;}
	static UINT ReadSCLThread (LPVOID pParam );//cgl：只为检测SCD读写文件用
	BOOL ParseSCL(const CString &strSclFilePath);
	void ReadSclStation();//将SCL读取的内容存入m_pSclStation对象链表中
//	void OpenSclStation();//20240117 gongyiping 进度条显示读取TSCD的ied内容
	BOOL IsInReadState()	{	return m_bIsInReadState;	}
	void FreeThreadAndDatas();
	void InitThreadProgress();

	CSclStation   *m_pSclStation;

protected:
	SCL_IED_INFO_QT* GetSclIedInforQT(const QString &strIedName);
	void FreeReadThread();
	void FreeAllList();
	DWORD GetHexValue(const QString &strHexText);
	CSclChBase* FindVirtualTerminalCh(CSclCtrlBase **ppSclCtrlOut,const CString strIedName,const CString strChRef ,BOOL bSmvCtrl);
    QList<SCL_IED_INFO_QT*> m_oSclIedList;    //解析的全部IED结果结果
    int m_nSclAnalyzeErrorNum;

private:
    enum DataFC{DOType,SDOType,DAType,BDAType};
	CThreadProgressInterface *m_pProgressInterface;

    //Qhash
    QHash<QString,int>  m_oIedNameHash;

	BOOL m_bIsInReadState;
	CWinThread *m_pReadThread;

#ifdef SCL_FILE_PARSE_USE_XPUGI
	typedef QHash<QString,xpugi::xml_node> DataTypeHash;
#else
	typedef QHash<QString,pugi::xml_node> DataTypeHash;
#endif
    DataTypeHash m_oDOType_Hash;
    DataTypeHash m_oDAType_Hash;

    typedef QHash<QString,DataTypeHash> LNodeTypeHash;
    LNodeTypeHash m_oLNodeType_Hash;

private:
#ifdef SCL_FILE_PARSE_USE_XPUGI
	void CreateDataTypeTemplatesHash(xpugi::xml_node oRootNodePugi);
	void CreateLNHash(const xpugi::xml_node LD_node,DataTypeHash *pLN_hash);
#else
	void CreateDataTypeTemplatesHash(pugi::xml_node oRootNodePugi);
	void CreateLNHash(const pugi::xml_node LD_node,DataTypeHash *pLN_hash);
#endif
   QString GetDataFC(const DataFC dataFC,const QString id,const QString name,const QString fc);
   CString GetIEDDescByIEDName(const CString &strIEDName);
};

#endif // CSCLFILE_READ_H
