/**********************************************************/
/* 通讯数据 */
/**********************************************************/
#define MODBUSTCP
//unsigned int == UDINT 4个字节
//int == DINT 4个字节 和long一样是4个字节 
//float == REAL 4个字节 double和longlong是8个字节
//unsigned char = USINT 8位 1个字节
//char == STRING
//char[40] == STRING[40] 8位 1个字节是1个字符占位
//bool == BOOL 1位
//short == INT 2个字节
//short == UINT 2个字节
/*#define UDINT unsigned int
#define DINT int
#define REAL float
#define USINT unsigned char
#define STRING char
#define INT short
#define UINT unsigned short
#define LREAL double*/
//#define BOOL bool

#define SET_BIT(_X,_pos)		{_X|=(1l<<(_pos));}
#define GET_BIT(_X,_pos)		((bool)((((long)(_X)&(1l<<(_pos)))!=0))
#define RESET_BIT(_X,_pos)		{(_X=~((~_X)|(1l<<(_pos))));}
#define ABS(x)					((x)>0?(x):(-1*(x)))

#ifndef _COMM_H_

#define	_COMM_H_

enum MODBUSTCPREGISTERS
{
	DTPLC_second = 1,    // UINT
	DTPLC_minute,    // UINT
	DTPLC_hour,    // UINT
	DTPLC_day,    // UINT
	DTPLC_month,    // UINT
	DTPLC_year,    // UINT
	DTPLC_weekday,    // UINT
	GroupDone, //本组结束 UINT
	ActData_GroupSum,    //总重 LREAL
	ActData_GroupSum_Reserve1,    //总重 LREAL
	ActData_GroupSum_Reserve2,    //总重 LREAL
	ActData_GroupSum_Reserve3,    //总重 LREAL
	FeedCounter,   //已经落料数量，针对cmdFeedFive命令 UINT
	ActData_ThickRejectCount,   //厚度剔废计数器 UDINT
	ActData_ThickRejectCount_Reserve,
	ActData_RejectBoxCnt,   //剔废盒内数量 UDINT
	ActData_RejectBoxCnt_Reserve,
	ActData_FeedAmount,   //n片数量 UINT
	
	ActData_GroupNo,   // UDINT
	ActData_GroupNo_Reserve,
	ActData_GroupIndex,   // UDINT
	ActData_GroupIndex_Reserve,
	Machine_step,  //步骤 UINT
	ActData_PassCount,   //通过计数 UDINT
	ActData_PassCount_Reserve,
	ActData_ProdCount,   //称重计数 UDINT
	ActData_ProdCount_Reserve,
	ActData_TOCount,   //过重计数 UDINT
	ActData_TOCount_Reserve,
	ActData_TUCount,   //过轻计数 UDINT
	ActData_TUCount_Reserve,
	ActData_RejectCount,   //剔废计数 UDINT
	ActData_RejectCount_Reserve,
	ActData_GroupAvg,   //组平均重量g REAL
	ActData_GroupAvg_Reserve,
	ActData_GroupMax,   // REAL
	ActData_GroupMax_Reserve,
	ActData_GroupMin,   // REAL
	ActData_GroupMin_Reserve,
	ActData_GroupMaxRatio,   // REAL
	ActData_GroupMaxRatio_Reserve,
	ActData_GroupMinRatio,   // REAL
	ActData_GroupMinRatio_Reserve,
	ActData_HardnessChkCnt,   //硬度检测计数 UINT
	HMU_ResultForce,   //测量结果硬度单位N REAL
	HMU_ResultForce_Reserve,
	HMU_ResultDiam,   //测量结果直径 REAL
	HMU_ResultDiam_Reserve,
	HMU_ActForce,   //当前硬度单位N REAL
	HMU_ActForce_Reserve,
	TMU_ThicknessResult,   //厚度结果 REAL
	TMU_ThicknessResult_Reserve,
	AlarmStatus,   //报警状态 UINT

	ActData_SysOveride,   //系统速度 UINT
	ActData_GroupSet,   //每组测试胶囊数量 UINT
	ActData_GroupCounter,   //组落料数量 UINT
	ActData_TestInterval,   //测试间隔时间单位s UINT
	ActData_TOverload,   //超重重量g REAL
	ActData_TOverload_Reserve,
	ActData_TUnderload,   //超轻重量g REAL
	ActData_TUnderload_Reserve,
	ActData_TDemand,   //期望重量g REAL
	ActData_TDemand_Reserve,
	ActData_InterOverLoad,   //内控线，上限 REAL
	ActData_InterOverLoad_Reserve,
	ActData_InterUnderLoad,   //内控线，下限 REAL
	ActData_InterUnderLoad_Reserve,

	ActData_UserAnalogoutput,   //用户模拟量输入 REAL
	ActData_UserAnalogoutput_Reserve,
	ActData_Adjustvalue,   //自动调整系数 REAL
	ActData_Adjustvalue_Reserve,
	ActData_DeltaInput,   //装量调整偏差值 UDINT
	ActData_DeltaInput_Reserve,

	ActData_HMU_Zero,   //硬度测试传感器零点 DINT
	ActData_HMU_Zero_Reserve,
	ActData_HMU_K,   //硬度测试K REAL
	ActData_HMU_K_Reserve,
	ActData_TMU_Zero,   //厚度测试传感器零点 DINT
	ActData_TMU_Zero_Reserve,
	ActData_TMU_K,   //厚度测试K REAL
	ActData_TMU_K_Reserve,

	ActData_SetPillDiam,   //设定片径 DINT
	ActData_SetPillDiam_Reserve,
	ActData_PillDiamOffset,   //片径计算偏差 DINT
	ActData_PillDiamOffset_Reserve,

	ActData_HardnessChkNum,   //硬度检测设定数量 UINT
	ActData_RecipeNo,   //配方号 UINT
	ActData_reserve,   // UINT
	ActData_ThickUpperLimit,   //厚度上限 REAL
	ActData_ThickUpperLimit_Reserve,
	ActData_ThickUnderLimit,   //厚度下限 REAL
	ActData_ThickUnderLimit_Reserve,

	HMU_paraCalibForce,   //校正推力 REAL
	HMU_paraCalibForce_Reserve,
	TMU_calibThickness,   //校正厚度单位mm REAL
	TMU_calibThickness_Reserve,

	System_enable,    //读取与保存 UINT
	System_StopSignalDelay,    //连续几次超重或超轻后输出停机信号 UINT
	System_paraTurnUpSpd,    //翻板上速度 UINT
	System_paraTurnDnSpd,    //翻板下速度 UINT
	System_s_trg_stop0,    //落料零点偏移 REAL
	System_s_trg_stop0_Reserve,
	System_s_trg_stop1,    //转盘零点偏移 REAL
	System_s_trg_stop1_Reserve,
	System_s_trg_stop2,    //翻板零点偏移 REAL
	System_s_trg_stop2_Reserve,
	System_s_trg_stop3,    //推杆零点偏移 REAL
	System_s_trg_stop3_Reserve,

	System_FeedTimeOut,    //下料超时时间,单位s REAL
	System_FeedTimeOut_Reserve,
	System_CapPickInterval,    //自动取料周期,单位s REAL
	System_CapPickInterval_Reserve,
	System_CapBackInterval,    //成品返还周期,单位s REAL
	System_CapBackInterval_Reserve,
	System_TireDelay,    //去皮延迟启动时间,单位s REAL
	System_TireDelay_Reserve,
	System_ReadDelay,    //读数延迟启动时间,单位s REAL
	System_ReadDelay_Reserve,
	System_TireWaitTime,    //去皮等待时间,单位s REAL
	System_TireWaitTime_Reserve,
	System_paraTurnUpPosition,    //翻板上位置 DINT
	System_paraTurnUpPosition_Reserve,
	System_paraTurnDnPosition,    //翻板下位置 DINT
	System_paraTurnDnPosition_Reserve,
	System_paraPushDestPosition,    //压片送进最大位置 DINT
	System_paraPushDestPosition_Reserve,
	System_ForceThresholdSlow,    //压力阈值1,检测到此压力后,减速 REAL
	System_ForceThresholdSlow_Reserve,
	System_CapThickValve_t1,    //测厚气缸动作延迟 REAL
	System_CapThickValve_t1_Reserve,
	System_CapThickValve_t2,    //测厚气缸复位延迟 REAL
	System_CapThickValve_t2_Reserve,
	System_CapTurnValve_t1,    //整形升降气缸动作延迟 REAL
	System_CapTurnValve_t1_Reserve,
	System_CapTurnValve_t2,    //整形升降气缸复位延迟 REAL
	System_CapTurnValve_t2_Reserve,
	
	System_HMU_Zero,    //硬度测试传感器零点 DINT
	System_HMU_Zero_Reserve,
	System_HMU_K,    //硬度测试K REAL
	System_HMU_K_Reserve,
	System_TMU_Zero,    //厚度测试传感器零点 DINT
	System_TMU_Zero_Reserve,
	System_TMU_K,    //厚度测试K REAL
	System_TMU_K_Reserve,
	System_SetPillDiam,    //设定片径 REAL
	System_SetPillDiam_Reserve,
	System_PillDiamOffset,    //片径计算偏差 REAL
	System_PillDiamOffset_Reserve,

	System_HMU_PressStopPercent,    //硬度测量，停止压片比例，百分比10-100 REAL
	System_HMU_PressStopPercent_Reserve,
	System_PrintIntervel,    //用户定义打印时间间隔(分钟) REAL
	System_PrintIntervel_Reserve,
	System_RejectBoxFullNum,    //剔废盒满数量 DINT
	System_RejectBoxFullNum_Reserve,
	Scale_Result,  //读数 REAL
	Scale_Result_Reserve,
	axis0_s_rel,  //落料步进数
	axis0_s_rel_Reserve,
	axis1_s_rel,  //转盘步进数
	axis1_s_rel_Reserve,
	Recipe_enable,//配方读取1,2保存 UDINT
	Recipe_enable_Reserve
};

enum MODBUSTCPCOILS
{
	Alarm1 = 1, Alarm2, Alarm3, Alarm4, Alarm5, Alarm6, Alarm7, Alarm8, Alarm9, Alarm10,
	Alarm11, Alarm12, Alarm13, Alarm14, Alarm15, Alarm16, Alarm17, Alarm18, Alarm19, Alarm20,
	Alarm21, Alarm22, Alarm23, Alarm24, Alarm25, Alarm26, Alarm27, Alarm28, Alarm29, Alarm30,
	Alarm31, Alarm32, Alarm33, Alarm34, Alarm35, Alarm36, Alarm37, Alarm38, Alarm39, Alarm40,
	Alarm41, Alarm42, Alarm43, Alarm44, Alarm45, Alarm46, Alarm47, Alarm48, Alarm49, Alarm50,

	Input_FeedTrigger,    //胶囊下落检测 BOOL
	Input_PressTrigger,    //硬度检测位置零位 BOOL
	Input_stCapThickValve,     //厚度气缸BOOL
	Input_stCapTurnValve,     //硬度气缸BOOL
	Input_SwingTrigger,    //摆臂位置检测 BOOL
	Input_TouchCalib,    //启动触摸屏校正 BOOL
	Input_TurnTrigger,    //翻板位置零位 BOOL

	DTChanged,  //HMI设定更改时间
	ActData_enHMU,   //硬度检测使能 BOOL
	ActData_enTMU,   //厚度检测使能 BOOL
	HMU_cmdStart,   //启动硬度测试 BOOL
	HMU_cmdStop,   //停止 BOOL
	HMU_cmdHome,   //硬度测试系统寻参 BOOL
	HMU_cmdZero,   //设定零点 BOOL
	HMU_cmdCalibStd,   //校正标准 BOOL
	HMU_cmdTurn,   //翻片 BOOL
	HMU_cmdReject,   //剔废用 BOOL
	Machine_cmdStart,   //启动 BOOL
	Machine_cmdEStop,   //停止 BOOL
	TMU_cmdStart,   //启动厚度测试 BOOL
	TMU_cmdStop,   //停止 BOOL
	TMU_cmdZero,   //设定零点 BOOL
	TMU_cmdCalib,   //校正标准 BOOL
	AlarmReset,    //BOOL
	cmdFeedSingle,   //落料 BOOL
	cmdFeedFive,   //连续落料5 BOOL
	cmdFeedSingleStop,   //落料停止 BOOL
	cmdSwing,   //转盘旋转一工位 BOOL
	SetCounterZero,   //计数清零 BOOL
	cmdCapClean,   //胶囊返还 BOOL
	cmdGetCap,   //取囊，返囊动作 BOOL
	cmdSetIP,   //设定ip命令 BOOL
	FeedDone,    //BOOL
	CmdAlogtest,   //模拟量测试 BOOL
	cmdFeedAmount,   //下N粒命令 BOOL


	Output_CapGet,       //取料电磁铁    BOOL
	Output_AlarmOut,       //报警蜂鸣器    BOOL
	Output_StopSignal,       //停机信号    BOOL
	Output_AlarmSignal,       //报警输出    BOOL
	Output_YellowAlarmout,       //黄灯报警    BOOL
	Output_Baffle,       //挡板    BOOL
	Output_CapTurnValve,       //整形升降气缸    BOOL
	Output_CapThickValve,       //测厚升降气缸    BOOL

	axis_fun_axis0_com_rel_pos_start,     //落料步进
	axis_fun_axis0_com_jog_pos,     //落料正向点动
	axis_fun_axis0_com_jog_neg,     //落料反向点动
	axis_fun_axis0_com_pos_move,     //落料正向连续
	axis_fun_axis1_com_rel_pos_start,     //转盘步进
	axis_fun_axis1_com_jog_pos,     //转盘正向点动
	axis_fun_axis1_com_jog_neg,     //转盘反向点动
	axis_fun_axis1_com_pos_move,     //转盘正向连续
	axis_fun_axis1_com_stop_move,     //转盘停止
	axis_fun_axis2_com_jog_neg,     //翻转反转
	axis_fun_axis2_com_jog_pos,     //翻转正转
	axis_fun_axis3_com_jog_neg,     //压片反转
	axis_fun_axis3_com_jog_pos,     //压片正转
	Scale_cmdTire,				//秤清零
	Scale_cmdCalibExt,     //秤外部校正
};
#define			MAX_PULSE_SERVO		2
#pragma pack(4)
typedef struct
{
	unsigned short		second;
	unsigned short		minute;
	unsigned short		hour;
	unsigned short		day;
	unsigned short		month;
	unsigned short		year;
	unsigned short		weekday;	
}DateTimeStructTyp;

typedef struct
{
	unsigned int		GroupNo;
	unsigned int		GroupIndex;
	float		GroupAvg;			//组平均重量,g
	float		GroupMax;
	float		GroupMin;
	float		GroupMaxRatio;
	float		GroupMinRatio;
	float        GroupWeightDelta;
	unsigned int		Tag;				//表格标记
}Displaytyp;

typedef struct
{
	float		Weight[20];
	float		Avg;
}DisplayWeightTyp;

typedef struct
{
	bool		FeedTrigger;			//胶囊下落检测
	bool		SwingTrigger;			//摆臂位置检测
	bool		FeedTrigger1;			//胶囊下落检测1
}Input_typ;


//output
typedef	struct
{
	bool         CapGet;				//取料电磁铁    		86,1
	bool         AlarmOut;				//报警蜂鸣器    		87,1
	bool         StopSignal;			//停机信号    	    88,1
	bool         AlarmSignal;			//报警输出    		89,1
	bool         YellowAlarmout;		//黄灯报警    	    90,1
	bool         Baffle;				//挡板     			91,1
	bool         CapTurnValve;			//整形升降气缸    	92,
	bool         CapThickValve;			//测厚升降气缸    	93,
}Output_typ;


#define		TELEGRAM_TYPE_HEARTBEAT		0
#define		TELEGRAM_TYPE_COMMAND		1
#define		TELEGRAM_TYPE_PARAMETER		2
#define		TELEGRAM_TYPE_RESULT		3
#define		TELEGRAM_TYPE_RUNPARA		4
#define		TELEGRAM_TYPE_REPLY			100

typedef struct
{
	unsigned short		enable;//1读取2写入	
	float		s_trg_stop[MAX_PULSE_SERVO];				//停止位置	
	float		Feed_shakeoffset;			//片剂摆动距离
	float		FeedTimeOut;				//下料超时时间,单位s	
	float		CapPickInterval;				//自动取料周期,单位s	
	float		CapBackInterval;				//成品返还周期,单位s	


	float		TireDelay;				//去皮延迟启动时间,单位s	
	float		ReadDelay;				//读数延迟启动时间,单位s	
	float		TireWaitTime;				//去皮等待时间,单位s	
	unsigned short		StopSignalDelay;				//连续几次超重或超轻后输出停机信号	

	int		Reserve[16];							//预留空间
}Comm_Machine_Para_typ;

typedef struct
{
	unsigned short		SysOveride;		//系统速度
	unsigned short		StableState;		//0:非常稳定,1:稳定,2:不稳定,3:非常不稳定
	unsigned short		FeedOveride;   //下料速度

	unsigned int		PassCount;		//通过计数
	unsigned int		ProdCount;		//称重计数
	unsigned int		TOCount;		//过重计数
	unsigned int		TUCount;		//过轻计数
	unsigned int		RejectCount;		//剔废计数

	unsigned short		WorkMode;		//0:Normal，1：Debug
	unsigned short		GroupSet;		//每组测试胶囊数量
	unsigned short		GroupCounter;		//组落料数量
	unsigned short		TireMode;		//0:每组去皮重,1:每次称重去皮重

	float		TestInterval;		//测试间隔时间,单位s
	float		TOverload;		//超重重量,g
	float		TUnderload;		//超轻重量,g
	float		TDemand;		//期望重量,g

	int		DeltaSwing;		//位置偏差,未使用
	unsigned short		GroupWeightCounter;		//组称重数量
	unsigned short		GroupRejectCounter;		 //组踢废数量,指剔废处理,非剔废动作
	char		BatchName[40];		//批号字符串

	unsigned int		GroupNo;		//组号
	unsigned int		GroupIndex;		//组数量计数

	double		GroupSum;		//组总重
	float		GroupAvg;		//组平均重量,g
	float		GroupMax;		//组最大值
	float		GroupMin;		//组最小值
	float		GroupMaxRatio;		//组最大偏差
	float		GroupMinRatio;		//组最小偏差
	float		InterOverLoad;		//内控线，上限
	float		InterUnderLoad;		//内控线，下限

	bool		UsbOk;		//U盘准备好
	bool		UsbPrintOk;		//Print准备好
	bool		Feedmode;	//0 胶囊 1 片剂

	float		UserAnalogoutput;		//用户模拟量输入
	float		Adjustvalue;		//自动调整系数
	unsigned int		DeltaInput;		//装量调整偏差值
	unsigned short		MultiCount;     //下多粒

	int				Reserve[16];			//预留空间
}Comm_Run_Para_typ;

typedef struct
{
	int				Finished;				//本组结束
	int				GroupIndex;				//本组序号
	float				Weight;					//本次重量

	//plc相关
	DateTimeStructTyp	PLCTimeNow;				//PLC当前时间
	int				UsbPrintOk;				//打印机连接正常,0:未连接，1：已连接
	int				UsbOk;					//U盘连接正常,0:未连接，1：已连接

	//Scale Data
	float				ScaleResult;			//天平当前读数，单位g
	int				ScaleStableState;		//天平当前稳定状态,0:非常稳定,1:稳定,2:不稳定,3:非常不稳定

	//Group Data
	Displaytyp			CapDataDisp;			//组数据

	//AxisStatus
	int				AxisFeedStep;			//下料电机状态机步骤
	int				AxisFeedErrorNo;		//下料电机错误代码
	int				AxisFeedRelMovDistance;	//下料电机相对运动距离，单位unit
	
	int				AxisSwingStep;			//旋转电机状态机步骤
	int				AxisSwingErrorNo;		//旋转电机错误代码
	int				AxisSwingRelMovDistance;//旋转电机相对运动距离，单位unit

	//MainCtrl etc
	int				MachineStep;			//系统运行状态机步骤
	float				TimeInterval;			//测量实际间隔时间

	int				AlarmStatus;			//0:无报警，1：一般报警，2：严重报警
	unsigned char				Alarm[16];				//报警位0-99，每一位对应一个报警,Alarm[0].0 ---- Alarm[13].3

	int				usertime;				//用户定义打印时间间隔(分钟)
	float				Rsd;					//相对标准偏差值


	int				Reserve[31];			//预留空间
}Comm_Status_typ;

typedef struct
{//照相处理结果
	unsigned int		OK;								//0:合格，1：不合格
	int		Reserve[16];					//预留空间
}Comm_Result_typ;

typedef struct
{
	DateTimeStructTyp		DateTimeSet;		//设定日期时间目标
	unsigned char		cmdChangeDT;					//修改日期时间,1:执行，自动复位

	unsigned char		cmdScaleRead;					//秤读数命令,1:执行，自动复位
	unsigned char		cmdScaleTire;					//秤清零,1:执行，自动复位
	unsigned char		cmdScaleSetStable;				//设定秤稳定状态,1:执行，自动复位
//	USINT		paraScaleSetStable;				//稳定状态设定目标，0:非常稳定,1:稳定,2:不稳定,3:非常不稳定

	unsigned char		cmdScaleCalibExt;				//秤外部校正,1:执行，自动复位
	unsigned char		cmdAxisFeedJogPos;				//下料正转点动，1:执行，0:停止
	unsigned char		cmdAxisFeedJogNeg;				//下料反转点动，1:执行，0:停止
	unsigned char		cmdAxisFeedRelMov;				//下料相对运动启动，1:执行，自动复位
	unsigned char		cmdAxisFeedPosMov;				//下料正向连续运动启动，1:执行，自动复位
	unsigned char		cmdAxisFeedStopMov;				//下料停止运动，1:执行，自动复位

	unsigned char		cmdAxisSwingJogPos;				//旋转正转点动，1:执行，0:停止
	unsigned char		cmdAxisSwingJogNeg;				//旋转反转点动，1:执行，0:停止
	unsigned char		cmdAxisSwingRelMov;				//旋转相对运动启动，1:执行，自动复位
	unsigned char		cmdAxisSwingPosMov;				//旋转正向连续运动启动，1:执行，自动复位
	unsigned char		cmdAxisSwingStopMov;			//旋转停止运动，1:执行，自动复位

	unsigned char		cmdFeedSingle;					//单粒下料，1:执行，自动复位
	//unsigned char		cmdFeedSingleStop;				//单粒下料停止，1:执行，自动复位

	unsigned char		cmdSwing;						//旋转单工位,1:执行，自动复位
	unsigned char		cmdStart;						//启动称重，1:执行，自动复位
	unsigned char		cmdEStop;						//急停，1:执行，自动复位
	unsigned char		cmdStop;						//停止,1:执行，自动复位
	unsigned char		cmdInit;						//初始化，1:执行，自动复位
	unsigned char		cmdAlarmReset;					//报警复位,1:执行，自动复位
	unsigned char		cmdCounterZero;					//计数器清零,1:执行，自动复位
	unsigned char		cmdPrintStart;					//启动打印,1:执行，自动复位
	unsigned char		cmdPrintStartE;					//启动英文打印，1:执行，自动复位
	unsigned char		cmdCapClean;					//清空胶囊，1:执行，自动复位
	unsigned char		cmdAlogtest;					//模拟量输出测试,1:执行，自动复位

	unsigned char		LeftRightFeedSign;				//左右进料标志0左进料1右进料
	unsigned char		cmdSingleSelect;				//单称选择
	unsigned char		cmdLeftGetCap;					//左取囊动作
	unsigned char		cmdRightGetCap;					//右取囊动作
	unsigned char		cmdReject;						//踢废
	unsigned char		cmdFeedAmount;					//组称落料

	bool		cmdFeedShake;					//下料摇摆
	bool		cmdFeedshakestop;				//下料摇摆停止
	bool		cmdFeedshakelevel;				//下料摇摆水平
	bool		cmdFeedhome;					//下料寻参
	bool		cmdFeedFive;					//胶囊落料5粒
	bool		cmdFeedShakefive;				//片剂落料5粒

	int				AxisFeedRelMovDistance;	//下料电机相对运动距离，单位unit

	int				AxisSwingRelMovDistance;//旋转电机相对运动距离，单位unit


	Output_typ					Outputs;			//输出点

	unsigned char		Reserve[32];					//预留空间
}Comm_Machine_Cmd_typ;



typedef struct DataFromPC_typ
{
	unsigned int						Telegram_typ;		//报文类型，0:心跳报文,1:命令报文,2:参数报文,3:结果报文,4,运行参数,100:应答
	Comm_Machine_Para_typ		Machine_Para;		//系统参数
	Comm_Run_Para_typ			ActData;			//运行参数
	Comm_Machine_Cmd_typ		Machine_Cmd;		//命令
	Comm_Result_typ				PhotoResult;		//拍照处理结果
	int						Reserve[16];		//预留空间
	DataFromPC_typ()
	{
		memset(this, 0, sizeof(DataFromPC_typ));
	}
}DataFromPC_typ;

//_GLOBAL			DataFromPC_typ			DataFromPC;

typedef struct DataToPC_typ
{
	unsigned int						Telegram_typ;		//报文类型，0:心跳报文,1:命令报文,2:参数报文,3:结果报文,100:应答
	//ActData名称修改，原Run_Para
	Comm_Run_Para_typ			ActData;			//运行数据
	Comm_Status_typ				Status;				//系统状态
	Comm_Machine_Para_typ		Machine_Para;		//系统参数
	Input_typ					Inputs;				//输入点 
	Output_typ					Outputs;			//输出点 

	int						Reserve[16];		//预留空间

}DataToPC_typ;

#pragma pack()
//_GLOBAL			DataToPC_typ			DataToPC;


#endif

