-- 本脚本解析GSP通用服务协议
-- 协议文档:  《GB/T 33602-2017 电力系统通用服务协议》
-- 服务器端默认监听端口为: 2404

local gsp = Proto("gsp","通用服务协议")

-- 服务码：《GB/T 33602-2017 电力系统通用服务协议》附录F.4.5
local vs_sc = {
    [1] ="关联",
    [2] ="中止",
    [3] ="释放",
    [4] ="创建服务",
    [5] ="删除服务",
    [6] ="注册服务",
    [7] ="取消服务",
    [8] ="服务状态(心跳) 报告",
    [9] ="获取服务列表",
    [10] ="获取服务信息",
    [11] ="服务定位",
    [12] ="特定服务域内的服务提供者查询",
    [13] ="特定服务部署位置查询",
    [14] ="获取服务状态",
    [15] ="获取域名",
    [16] ="设置域名",
    [17] ="域注册",
    [18] ="服务域状态(心跳) 报告",
    [19] ="域注册管理",
    [20] ="域名查询",
    [21] ="代理定位",
    [22] ="创建服务相关类",
    [23] ="获取服务相关类",
    [24] ="删除服务相关类",
    [25] ="获取服务相关类列表",
    [48] ="读数据值",
    [49] ="设置数据值",
    [50] ="读数据目录",
    [51] ="读数据定义",
    [52] ="读取数据集",
    [53] ="设置数据集",
    [54] ="生成数据集",
    [55] ="删除数据集",
    [56] ="校验数据集",
    [57] ="读取数据集目录",
    [58] ="读取数据集的数据值",
    [59] ="发送数据集的数据值",
    [60] ="获取数据集列表",
    [61] ="注册事件",
    [62] ="订阅事件",
    [63] ="事件推送",
    [64] ="取消事件注册",
    [65] ="查询事件",
    [66] ="获取事件列表",
    [67] ="取消事件订阅",
    [68] ="选择",
    [69] ="带值选择",
    [70] ="取消",
    [71] ="执行",
    [72] ="命令终止",
    [73] ="时间激活操作",
    [74] ="操作控制",
    [75] ="操作控制",
    [76] ="查询操作票列表",
    [77] ="序列控制",
    [78] ="序列单步",
    [79] ="获取时间",
    [80] ="读服务器目录",
    [81] ="读逻辑设备目录",
    [82] ="读逻辑节点目录",
    [83] ="读所有数据值",
    [84] ="选择活动定值组",
    [85] ="选择编辑定值组",
    [86] ="写编辑定值组值",
    [87] ="确认编辑定值组值",
    [88] ="读编辑定值组值",
    [89] ="读定值组控制块值",
    [90] ="报告",
    [91] ="读缓存报告控制块值",
    [92] ="设置缓存报告控制块值",
    [93] ="读非缓存报告控制块值",
    [94] ="设置非缓存报告控制块值",
    [95] ="读日志控制块值",
    [96] ="设置日志控制块值",
    [97] ="按时间查询日志",
    [98] ="查询某条目以后的日志",
    [99] ="读日志状态值",
    [100] ="发送GOOSE报文",
    [101] ="读GOOSE元素数目",
    [102] ="读GOOSE控制块值",
    [103] ="设置GOOSE控制块值",
    [104] ="发送MSV报文",
    [105] ="读MSV控制块值",
    [106] ="设置MSV控制块值",
    [107] ="发送USV报文",
    [108] ="读USV控制块值",
    [109] ="设置USV控制块值",
    [128] ="读文件",
    [129] ="设置文件",
    [130] ="删除文件",
    [131] ="读文件属性值",
    [132] ="获取文件列表",
    [133] ="获取文件目录",
    [134] ="用SQL读取数据库内容",
    [135] ="用SQL修改数据库内容",
    [136] ="获取数据库列表",
    [137] ="获取数据库表结构",
    [138] ="获取数据库域结构",
    [139] ="读取时间序列库",
    [140] ="写入时间序列库",
    [141] ="获取数据库存储清单",
    [142] ="获取数据库表清单",
    [143] ="获取数据库表结构",
    [144] ="获取数据库表记录",
    [145] ="订阅画面",
    [146] ="注销画面",
    [147] ="暂停画面",
    [148] ="刷新画面",
    [149] ="获取画面列表",
    [150] ="获取模型",
    [151] ="更新模型",
    [152] ="获取模型列表",
    [153] ="测试",
    [154] ="查询历史未来数据信息",
    [155] ="读取历史未来数据",
    [156] ="写入历史未来数据",
    [157] ="综合查询",
    [158] ="读取版本信息",
    [159] ="发送邮件",
    [160] ="接收邮件",
    [161] ="发送消息",
    [162] ="接收消息",
    [163] ="启动工作流程",
    [164] ="删除工作流程",
    [165] ="结束工作流程",
    [166] ="读取通信链路",
    [167] ="读取通信链路列表",
    [168] ="通信链路控制",
    [191] ="深瑞召数据集"
}

-- ClassID: 预定义类标识
local vs_ci = {
    [0] ="尚未定义",
    [1] ="支持所有",
    [3] ="数据触发原因",
    [4] ="关联标识",
    [5] ="遥测数据",
    [6] ="遥信数据",
    [7] ="变化遥信数据",
    [8] ="带时标的变化遥测数据",
    [9] ="变化遥信数据",
    [10] ="带时标的变化遥信数据",
    [11] ="类描述信息",
    [12] ="单点数据定义",
    [13] ="事件信息",
    [14] ="事件数据",
    [15] ="事件查询条件",
    [16] ="文件头定义",
    [17] ="数据库SQL 语句信息",
    [18] ="结果域信息",
    [20] ="查询返回值",
    [22] ="查询返回值",
    [23] ="数据库描述信息",
    [24] ="数据集配置信息",
    [25] ="GOOSE 控制块定义",
    [26] ="GOOSE 报文定义",
    [27] ="多路广播采样量测值控制块定义",
    [28] ="单路传输采样量测值控制块定义",
    [29] ="采样量测值报文定义",
    [30] ="时间戳",
    [31] ="包含在报告中的任选域",
    [32] ="缓存报告控制块类定义",
    [33] ="缓存报告格式定义",
    [34] ="非缓存报告控制块类定义",
    [35] ="非缓存报告格式定义",
    [36] ="条目数据",
    [37] ="原因码",
    [38] ="数据集摘要",
    [39] ="链路属性",
    [40] ="时间序列库测点数据",
    [41] ="时序库描述符",
    [42] ="测点参数",
    [43] ="综合查询结果",
    [44] ="数据对象标识",
    [45] ="控制数据"
}

-- 控制码：next
local vs_ccnext = {
    [0]  ="无下一帧",
    [1]  ="有下一帧"
}

-- 控制码：resp
local vs_ccresp = {
    [0]  ="返回结果无效",
    [1]  ="返回结果有效"
}

-- 控制码：error
local vs_ccerr = {
    [0]  ="响应成功",
    [1]  ="无效服务"
}

local vs_ccproto = {
    [0] ="通用服务协议",
    [1] ="DL/T 860.72协议",
    [2] ="DL/T 634.5104协议",
    [3] ="DL/T 476协议",
    [4] ="GB/T 18700.1(TASE.2)协议",
    [5] ="DL/T 719(IEC 870-5-102)协议",
    [6] ="DL/T 667(IEC 870-5-103)协议"
}

-- 编码类型CT
local vs_uict = {
    [0] ="M0-兼容ASN.1编码方式",
    [1] ="M1-带名字ASN.1编码方式",
    [2] ="M2-对象编码方式",
    [3] ="M3-类编码方式"
--  [4] ="M3-类对象编码方式"  -- GSP与行标1232矛盾
}

-- 数据单元标识DI
local vs_uiut = {
    [0] ="对象单元",
    [1] ="参数单元",
    [2] ="流数据单元",
    [3] ="类描述单元",
    [4] ="数据集扩展单元",
    [5] ="通用宽扩展单元"
}

local vs_uief5 = {
    [0] ="短类描述",
    [1] ="长类描述"
}

local vs_uief6 = {
    [0] ="头部4字节扩展",
    [1] ="头部8字节扩展"
}

local vs_uih = {
    [0] ="小端",
    [1] ="大端"
}

-- 数据集索引表标识DS
local vs_dsex_ds = {
    [0] ="保留",
    [1] ="接收遥测索引表",
    [2] ="接收遥信索引表",
    [3] ="接收遥控索引表",
    [4] ="接收遥调索引表",
    [5] ="发送遥测索引表",
    [6] ="发送遥信索引表",
    [7] ="发送遥控索引表",
    [8] ="发送遥调索引表",
}

-- 子服务: 数据集扩展时的子服务码
local vs_dsex_ss = {
    [0] ="变化数据传送",
    [1] ="全数据传送"
}

-- 品质-bit6
local vs_q_upd = {
    [0] ="未停止更新",
    [1] ="已停止更新"
}

-- 品质-bit5
local vs_q_vld = {
    [0] ="数据有效",
    [1] ="数据无效"
}

-- 品质-bit4
local vs_q_wrn = {
    [0] ="未引起告警",
    [1] ="引起告警"
}

-- 品质-bit3
local vs_q_acq = {
    [0] ="自动采集",
    [1] ="人工置入"
}

-- 品质-bit2
local vs_q_eval = {
    [0] ="非估计导出",
    [1] ="估计导出"
}

-- 本协议涉及到的所有字段
local f_apci = ProtoField.new("APCI","gsp.apci", ftypes.NONE)
local f_cc = ProtoField.new("控制码CC","gsp.cc", ftypes.NONE)
local f_ccnext = ProtoField.uint8("gsp.cc.next","next",base.DEC,vs_ccnext,0x80)
local f_ccresp = ProtoField.uint8("gsp.cc.resp","resp",base.DEC,vs_ccresp,0x40)
local f_ccerro = ProtoField.uint8("gsp.cc.error","error",base.DEC,vs_ccerr,0x20)
local f_ccproto = ProtoField.uint8("gsp.cc.pi","适用协议PI",base.DEC,vs_ccproto,0x0F)
local f_sc = ProtoField.uint8("gsp.sc","服务码SC",base.DEC,vs_sc)
local f_seq = ProtoField.uint32("gsp.seq","报文序号",base.DEC)
local f_len = ProtoField.uint16("gsp.len","ASDU长度",base.DEC)

local f_asdu = ProtoField.new("ASDU","gsp.asdu", ftypes.NONE)
local f_ui = ProtoField.new("单元标识UI","gsp.ui", ftypes.NONE)
local f_uict = ProtoField.uint8("gsp.ui.ct","编码类型CT",base.DEC,vs_uict,0x03)
local f_uiut = ProtoField.uint8("gsp.ui.ut","单元类型UT",base.DEC,vs_uiut,0x1C)
local f_uief5 = ProtoField.uint8("gsp.ui.ef5","扩展标志EF5",base.DEC,vs_uief5,0x20)
local f_uief6 = ProtoField.uint8("gsp.ui.ef6","扩展标志EF6",base.DEC,vs_uief6,0x40)
local f_uih = ProtoField.uint8("gsp.ui.h","字节序标志",base.DEC,vs_uih,0x80)

local f_ci = ProtoField.uint8("gsp.ci","类标识CI",base.DEC,vs_ci)

local f_dsex_ds = ProtoField.uint8("gsp.dsex.ds","索引表标识DS",base.DEC,vs_dsex_ds)
local f_dsex_ss = ProtoField.uint8("gsp.dsex.ss","子服务SS",base.DEC,vs_dsex_ss)
local f_dsex_seq = ProtoField.uint16("gsp.dsex.seq","相对序列号SEQ",base.DEC)

local f_parnum = ProtoField.uint8("gsp.parnum","参数数目",base.DEC)
local f_parnam = ProtoField.new("参数", "gsp.parname", ftypes.STRING)
local f_errmsg = ProtoField.new("错误", "gsp.errmsg", ftypes.STRING)

local f_tag = ProtoField.uint8("gsp.tag","TAG",base.DEC)
local f_tlen = ProtoField.uint8("gsp.tlen","LEN",base.DEC)

local f_clssiz = ProtoField.uint8("gsp.clssiz","类尺寸CS",base.DEC)
local f_clslen = ProtoField.uint8("gsp.clslen","类描述长度",base.DEC)

local f_objsiz = ProtoField.uint8("gsp.objsiz","对象尺寸OS",base.DEC)
local f_objcnt = ProtoField.uint8("gsp.objcnt","对象数目OC",base.DEC)
local f_obj = ProtoField.new("对象","gsp.obj", ftypes.NONE)
local f_obj_index = ProtoField.uint16("gsp.obj.index","序号",base.DEC)
local f_obj_t = ProtoField.new("时间","gsp.obj.t", ftypes.NONE)

local f_obj_ptval = ProtoField.new("遥信点","gsp.ptval", ftypes.NONE)
local f_obj_pv_val = ProtoField.uint16("gsp.ptval.sta","状态值",base.DEC,nil,0x03)

local f_obj_cavt = ProtoField.new("遥测点","gsp.cavt", ftypes.NONE)
local f_obj_cavt_val = ProtoField.float("gsp.cavt.val","遥测值",base.DEC)

local f_obj_q_upd = ProtoField.uint16("gsp.q.upd","品质-更新",base.DEC,vs_q_upd,0x40)
local f_obj_q_vld = ProtoField.uint16("gsp.q.vld","品质-有效性",base.DEC,vs_q_vld,0x20)
local f_obj_q_wrn = ProtoField.uint16("gsp.q.wrn","品质-告警",base.DEC,vs_q_wrn,0x10)
local f_obj_q_acq = ProtoField.uint16("gsp.q.acq","品质-采集",base.DEC,vs_q_acq,0x08)
local f_obj_q_eval = ProtoField.uint16("gsp.q.eval","品质-估计",base.DEC,vs_q_eval,0x04)

local f_vbool = ProtoField.uint8("gsp.vbool","BOOL",base.DEC)
local f_vint8 = ProtoField.int8("gsp.vint8","INT8",base.DEC)
local f_vint16 = ProtoField.int16("gsp.vint16","INT16",base.DEC)
local f_vint32 = ProtoField.int32("gsp.vint32","INT32",base.DEC)
local f_vint64 = ProtoField.int64("gsp.vint64","INT64",base.DEC)
local f_vint128 = ProtoField.none("gsp.vint128", "INT128") 
local f_vint8u = ProtoField.uint8("gsp.vint8u","INT8U",base.DEC)
local f_id_dst = ProtoField.uint8("gsp.datasetid","INT8U",base.DEC)
local f_id_cls = ProtoField.uint8("gsp.classid","INT8U",base.DEC)
local f_id_grp = ProtoField.uint8("gsp.groupid","INT8U",base.DEC)
local f_vint16u = ProtoField.uint16("gsp.vint16u","INT16U",base.DEC)
local f_vint32u = ProtoField.uint32("gsp.vint32u","INT32U",base.DEC)
local f_vint64u = ProtoField.uint64("gsp.vint64u","INT64U",base.DEC)
local f_vfloat32 = ProtoField.float("gsp.vfloat32","FLOAT32")
local f_vfloat64 = ProtoField.double("gsp.vfloat64","FLOAT64")
local f_voctets = ProtoField.string("gsp.voctets","OCTETS")
local f_vstring = ProtoField.string("gsp.vstring","STRING")
local f_venum = ProtoField.int32("gsp.venum","ENUM",base.DEC)
local f_vnone = ProtoField.none("gsp.vnone", "未知类型") 

-- 注册所有字段
gsp.fields = {
    f_apci, f_cc, f_ccnext, f_ccresp, f_ccerro, f_ccproto, f_sc, f_seq, f_len, 
    f_asdu, f_ui, f_uict, f_uiut, f_uief5, f_uief6, f_uih, f_ci, f_dsex_ds, f_dsex_ss, f_dsex_seq,
    f_parnum, f_parnam, f_tag, f_tlen, f_vbool, f_vint8, f_vint16,f_vint32, 
    f_vint64, f_vint128, f_vint8u, f_vint16u,f_vint32u, f_vint64u, f_vfloat32,
    f_vfloat64, f_voctets, f_vstring, f_venum, f_vnone,
    f_id_dst,f_id_cls,f_id_grp,
    f_clssiz, f_clslen, f_objsiz, f_objcnt,f_obj,f_obj_ptval,f_obj_pv_val,
    f_obj_cavt, f_obj_index, f_obj_cavt_val,f_obj_t,
    f_obj_q_upd,f_obj_q_vld, f_obj_q_wrn, f_obj_q_acq, f_obj_q_eval,
    f_errmsg 
}

local data_dis = Dissector.get("data")

-- 行标DL／T 1232-2013《电力系统动态消息编码规范》的表3
local function add_tlv_value(tag, len, tvb, tlvTree, name)
    if     (tag == 1) then -- BOOLEAN
        tlvTree:add_le(f_vbool, tvb)
    elseif (tag == 43) then -- INT8
        tlvTree:add_le(f_vint8, tvb)
    elseif (tag == 33) then -- INT16
        tlvTree:add_le(f_vint16, tvb)
    elseif (tag == 2) then -- INT32
        tlvTree:add_le(f_vint32, tvb)
    elseif (tag == 36) then -- INT64
        tlvTree:add_le(f_vint64, tvb)
    elseif (tag == 44) then -- INT128
        tlvTree:add_le(f_vint128, tvb)
    elseif (tag == 32) then -- INT8U
        if (name == "dataSetID") then
            tlvTree:add_le(f_id_dst, tvb)
        elseif (name == "classID") then
            tlvTree:add_le(f_id_cls, tvb)
        elseif (name == "groupID") then
            tlvTree:add_le(f_id_grp, tvb)
        else
            tlvTree:add_le(f_vint8u, tvb)
        end
    elseif (tag == 34) then -- INT16U
        tlvTree:add_le(f_vint16u, tvb)
    elseif (tag == 35) then -- INT32U
        tlvTree:add_le(f_vint32u, tvb)
    elseif (tag == 37) then -- INT64U
        tlvTree:add_le(f_vint64u, tvb)
    elseif (tag == 38) then -- FLOAT32
        tlvTree:add_le(f_vfloat32, tvb)
    elseif (tag == 39) then -- FLOAT64
        tlvTree:add_le(f_vfloat64, tvb)
    elseif (tag == 4) then
        tlvTree:add(f_voctets, tvb)
    elseif (tag == 26) then
        tlvTree:add(f_vstring, tvb)
    elseif (tag == 10) then
        tlvTree:add(f_venum, tvb)
    else
        tlvTree:add(f_vnone, tvb)
    end
    return true
end

local function diss_params(cnt, tvb, asduTree)
    local dlen = tvb:len()
    local i = 0

    local tvbPar = tvb(0,dlen)
    for i = 0,cnt,1 
    do
        local name = tvbPar:stringz(ENC_UTF_8)
        local namelen = string.len(name)
        if (namelen+1 > dlen) then
            asduTree:add(f_errmsg, tvbPar(0, dlen), "(长度异常)")
            return false
        end
        local treeItm = asduTree:add(f_parnam, tvbPar(0,namelen)) -- 参数名称
        dlen = dlen - namelen - 1
        if (dlen < 2) then
            asduTree:add(f_errmsg, tvbPar(namelen+1, dlen), "(长度异常)")
            return false
        end
        local tag = tvbPar(namelen+1, 1):le_uint()
        local tlen = tvbPar(namelen+2, 1):le_uint()
        local tiTag = treeItm:add(f_tag, tvbPar(namelen+1,1))
        local tiLen = treeItm:add(f_tlen, tvbPar(namelen+2,1))
        dlen = dlen - 2
        if (dlen < tlen) then
            treeItm:add(f_errmsg, tvbPar(namelen+3, dlen), "(长度异常)")
            return false
        end
        
        if not add_tlv_value(tag, tlen, tvbPar(namelen+3, tlen), treeItm, name) then

        end

        dlen = dlen - tlen
        if (dlen == 0) then
            return true
        end
        tvbPar = tvbPar(namelen+3+tlen, dlen)
    end
    return true
end

local function diss_classdisc(tvb, asduTree, clssiz, clslen)
    local dlen = tvb:len()
    local i = 0

    

end

local function diss_objdisc(tvb, asduTree, ci, osiz, oc, byteOrder)
    local dlen = tvb:len()
    local i = 0
    local ofs = 0
    for i = 1, oc, 1 
    do
        if (dlen < osiz) then
            asduTree:add(f_errmsg, tvb(ofs, dlen), "(长度异常)")
            return false
        end
        if ci==6 and osiz==2 then 
            local treeItem = asduTree:add(f_obj_ptval, tvb(ofs, osiz))
            treeItem:append_text(string.format("%d", i))
            treeItem:add_le(f_obj_q_upd, tvb(ofs, osiz))
            treeItem:add_le(f_obj_q_vld, tvb(ofs, osiz))
            treeItem:add_le(f_obj_q_wrn, tvb(ofs, osiz))
            treeItem:add_le(f_obj_q_acq, tvb(ofs, osiz))
            treeItem:add_le(f_obj_q_eval, tvb(ofs, osiz))
            treeItem:add_le(f_obj_pv_val, tvb(ofs, osiz))
        elseif ci==5 and osiz==8 then
            local treeItem = asduTree:add(f_obj_cavt, tvb(ofs, osiz))
            treeItem:append_text(string.format("%d", i))
            treeItem:add_le(f_obj_cavt_val, tvb(ofs, 4))
            treeItem:add_le(f_obj_q_upd, tvb(ofs+4, 2))
            treeItem:add_le(f_obj_q_vld, tvb(ofs+4, 2))
            treeItem:add_le(f_obj_q_wrn, tvb(ofs+4, 2))
            treeItem:add_le(f_obj_q_acq, tvb(ofs+4, 2))
            treeItem:add_le(f_obj_q_eval, tvb(ofs+4, 2))            
        elseif ci==8 and osiz==18 then
            local treeItem = asduTree:add(f_obj_cavt, tvb(ofs, osiz))
            treeItem:append_text(string.format("%d", i))
            treeItem:add_le(f_obj_index, tvb(ofs, 2))
            treeItem:add_le(f_obj_q_upd, tvb(ofs+2, 2))
            treeItem:add_le(f_obj_q_vld, tvb(ofs+2, 2))
            treeItem:add_le(f_obj_q_wrn, tvb(ofs+2, 2))
            treeItem:add_le(f_obj_q_acq, tvb(ofs+2, 2))
            treeItem:add_le(f_obj_q_eval, tvb(ofs+2, 2))
            treeItem:add_le(f_obj_cavt_val, tvb(ofs+4, 4))
            local treeTime = treeItem:add_le(f_obj_t, tvb(ofs+8, 10))
            treeTime:append_text(": ")
            treeTime:append_text(os.date("%Y-%m-%d %H:%M:%S", tvb(ofs+8, 8):le_uint64():tonumber()))
            treeTime:append_text(string.format(".%03d", tvb(ofs+16, 2):le_uint()))
        elseif ci==10 and osiz==14 then
            local treeItem = asduTree:add(f_obj_ptval, tvb(ofs, osiz))
            treeItem:append_text(string.format("%d", i))
            treeItem:add_le(f_obj_index, tvb(ofs, 2))
            treeItem:add_le(f_obj_q_upd, tvb(ofs+2, 2))
            treeItem:add_le(f_obj_q_vld, tvb(ofs+2, 2))
            treeItem:add_le(f_obj_q_wrn, tvb(ofs+2, 2))
            treeItem:add_le(f_obj_q_acq, tvb(ofs+2, 2))
            treeItem:add_le(f_obj_q_eval, tvb(ofs+2, 2))
            treeItem:add_le(f_obj_pv_val, tvb(ofs+2, 2)) 
            local treeTime = treeItem:add_le(f_obj_t, tvb(ofs+4, 10))
            treeTime:append_text(": ")
            treeTime:append_text(os.date("%Y-%m-%d %H:%M:%S", tvb(ofs+4, 8):le_uint64():tonumber()))
            treeTime:append_text(string.format(".%03d", tvb(ofs+12, 2):le_uint()))
        else
            asduTree:add(f_obj, tvb(ofs, osiz))
        end

        ofs = ofs + osiz
        dlen = dlen - osiz
    end

    return true
end

-- 解析PDU 
local function diss_gsp(tvb, pinfo, tree)
    local offset = pinfo.desegment_offset or 0
    if tvb:len()<4 then
        return false
    end

    while true do
        -- lenASDU为ASDU长度，len为APDU长度（APCI+ASDU）
        local lenASDU = tvb(offset+2, 2):le_uint()
        local lenALL = lenASDU + 4

        -- 粘包分包处理
        local nxtpdu = offset + lenALL
        if nxtpdu > tvb:len() then
            pinfo.desegment_len = nxtpdu - tvb:len()
            pinfo.desegment_offset = offset
            return true
        end

        local gspRoot = tree:add(gsp, tvb(offset, lenALL))

        local apciTree = gspRoot:add(f_apci, tvb(offset, 4)) -- APCI
        
        local ccTree = apciTree:add(f_cc, tvb(offset, 1)) -- 控制码CC
        ccTree:add_le(f_ccnext, tvb(offset, 1))  -- next
        ccTree:add_le(f_ccresp, tvb(offset, 1))  -- resp
        ccTree:add_le(f_ccerro, tvb(offset, 1))  -- error
        ccTree:add_le(f_ccproto, tvb(offset, 1)) -- 适用协议

        apciTree:add_le(f_sc, tvb(offset+1, 1))  -- 服务码 SC
        apciTree:add_le(f_len, tvb(offset+2, 2)) -- ASDU长度

        if lenASDU < 4 then
            gspRoot:append_text("(长度异常)")
            return false
        end

        local asduTVB = tvb(offset+4, lenASDU)
        local asduTree = gspRoot:add(f_asdu, asduTVB) -- APCI
        local uiTree = asduTree:add(f_ui, asduTVB(0, 1)) -- 控制码CC
        uiTree:add_le(f_uict, asduTVB(0, 1))  -- 编码类型CT
        uiTree:add_le(f_uiut, asduTVB(0, 1))  -- 单元标识UT
        uiTree:add_le(f_uief5, asduTVB(0, 1))  -- 扩展标志EF5
        uiTree:add_le(f_uief6, asduTVB(0, 1))  -- 扩展标志EF6
        uiTree:add_le(f_uih, asduTVB(0, 1))  -- 字节序
        
        asduTree:add_le(f_ci, asduTVB(1, 1))  -- 类标识CI
        local ci = asduTVB(1, 1):le_uint()   

        -- asduTVB(2,1)和asduTVB(3,1)根据DI确定

        local ui = asduTVB(0, 1):le_uint()
        local ut = bit.band(bit.rshift(ui, 2), 0x7)  -- 单元标识UT
        local ct = bit.band(ui, 0x3)                 -- 编码类型CT
        
        local ef5 = bit.band(bit.rshift(ui, 5), 0x1) -- 扩展标志EF5
        local ef6 = bit.band(bit.rshift(ui, 6), 0x1) -- 扩展标志EF6
        local byteOrder = bit.band(bit.rshift(ui, 7), 0x1) -- 字节序

        if lenASDU > 4 then
            if (ut==1) then -- 参数单元: M1编码-带名字的ASN.1编码方式
                -- asduTVB(2,1) 保留
                asduTree:add_le(f_parnum, asduTVB(3, 1))  -- 参数数目
                diss_params(asduTVB(3, 1):le_uint(), asduTVB(4, lenASDU-4), asduTree)
            elseif (ut==4) then -- 数据集扩展单元, M2编码：对象编码方式
                asduTree:add_le(f_objsiz, asduTVB(2, 1))  -- 对象尺寸OS
                local osiz = asduTVB(2, 1):le_uint()

                asduTree:add_le(f_objcnt, asduTVB(3, 1))  -- 对象数目OC
                local oc = asduTVB(3, 1):le_uint()
                
                asduTree:add_le(f_dsex_ds, asduTVB(4, 1))  -- 数据集索引变标识DS
                asduTree:add_le(f_dsex_ss, asduTVB(5, 1))  -- 数据集子服务SS
                asduTree:add_le(f_dsex_seq, asduTVB(6, 2))  -- 相对序列号SEQ
                diss_objdisc(asduTVB(8, lenASDU-8), asduTree, ci, osiz, oc, byteOrder)
            elseif (ut==4) then -- 类描述单元
                asduTree:add_le(f_clssiz, asduTVB(2, 1))  -- 类尺寸
                asduTree:add_le(f_clslen, asduTVB(3, 1))  -- 类描述长度
                diss_classdisc(asduTVB(4, lenASDU-4), asduTree, asduTVB(2, 1):le_uint(), asduTVB(3, 1):le_uint())
            end
        end

        -- 粘包分包处理
        offset = nxtpdu
        if nxtpdu == tvb:len() then
             return true
        end
    end
    return true
end

-- 解析主入口
function gsp.dissector(tvb, pinfo, tree)
    if diss_gsp(tvb,pinfo,tree) then
        --valid
    else
        --data这个dissector几乎是必不可少的；当发现不是我的协议时，就应该调用data
        data_dis:call(tvb,pinfo,tree)
    end
end

local tcp_table = DissectorTable.get("tcp.port")
tcp_table:add(8102, gsp)