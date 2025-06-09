#pragma once

/*
<ats-cmd name="ConfigEngine" id="" testor="" >
    <paras name="" id="">
        <data id=" log-data-bind " value=" "/>【显示数据绑定错误】
        <data id=" log-pkg-data-infor " value=" "/>【显示报文数据信息】
        <data id=" log-pkg " value=" "/>【显示发送、接受报文】
        <data id=" log-protocol-debug-infor " value=" "/>【显示调试信息】
        <data id=" log-server-debug-infor " value=" "/>【显示调试信息】
        <data id=" no-change-when-same " value=" "/>【数据相同不执行修改】
    </paras>
</ats -cmd>
*/

/*
 * /Source/Protocol/Module/Engine/PpGlobalDefine.cpp
long g_bLogBindQueryErrorInfor = FALSE;
long g_bLogPackageInfor = FALSE;
long g_bLogEngineDebugInfor = FALSE;
*/

//监视服务端调试输出信息
extern long g_nSttLogServerDebugInfor;

//监视服务端所有的命令报文
extern long g_nSttLogServerSpyAllCmd;

//2020-12-08  lijunqing
extern long g_nCloseTestWhenDisconnect;
