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

#include "../../../Module/xml/PugiXML/pugixml.hpp"
#include "../../../Module/BaseClass/ThreadProgressInterface.h"

#include <QWidget>

using namespace pugi;

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
}SCL_IED_INFO_QT;

class QSclFileRead//:public QWidget
{
 //   Q_OBJECT

public:
	QSclFileRead();
//    explicit CXML(QWidget *parent=0);
	virtual ~QSclFileRead();

    BOOL ReadSclFile(const CString &strSclFilePath, CSclStation *pSclStation);   //装载SCD文件
    BOOL SavePscdFile(const CString &strPscdFilePath);   //保存解析结果
	void SetProgressInterface(CThreadProgressInterface *pProgressInterface){m_pProgressInterface = pProgressInterface;}

protected:
	DWORD GetHexValue(const QString &strHexText);
	BOOL ParseSCL(const CString &strSclFilePath);
	void ReadSclStation();//将SCL读取的内容存入m_pSclStation对象链表中
	CSclChBase* FindVirtualTerminalCh(CSclCtrlBase **ppSclCtrlOut,const CString strIedName,const CString strChRef ,BOOL bSmvCtrl);
	CSclStation   *m_pSclStation;
    QList<SCL_IED_INFO_QT> m_oSclIedList;    //解析的全部IED结果结果
    int m_nSclAnalyzeErrorNum;

private:
    enum DataFC{DOType,SDOType,DAType,BDAType};
	CThreadProgressInterface *m_pProgressInterface;

    //Qhash
    QHash<QString,int>  m_oIedNameHash;

    typedef QHash<QString,xml_node> DataTypeHash;
    DataTypeHash m_oDOType_Hash;
    DataTypeHash m_oDAType_Hash;

    typedef QHash<QString,DataTypeHash> LNodeTypeHash;
    LNodeTypeHash m_oLNodeType_Hash;

private:
	void CreateDataTypeTemplatesHash(xml_node oRootNodePugi);
	void CreateLNHash(const xml_node LD_node,DataTypeHash *pLN_hash);
   QString GetDataFC(const DataFC dataFC,const QString id,const QString name,const QString fc);
};

#endif // CSCLFILE_READ_H
