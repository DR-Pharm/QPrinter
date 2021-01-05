/**********************************************************/
/* 通讯数据 */
/**********************************************************/
//unsigned int == UDINT 4个字节
//int == DINT 4个字节 和long一样是4个字节 
//float == REAL 4个字节 double和longlong是8个字节
//unsigned char = USINT 8位 1个字节
//char[40] == STRING[40] 8位 1个字节是1个字符占位
//bool == BOOL 1位
//short == INT 2个字节

#define SET_BIT(_X,_pos)		{_X|=(1l<<(_pos));}
#define GET_BIT(_X,_pos)		((bool)((((long)(_X)&(1l<<(_pos)))!=0))
#define RESET_BIT(_X,_pos)		{(_X=~((~_X)|(1l<<(_pos))));}
#define ABS(x)					((x)>0?(x):(-1*(x)))
#ifndef _COMM_H_
#define	_COMM_H_

#define			MAX_PULSE_SERVO		2
typedef struct
{
	unsigned int		second;
	unsigned int		minute;
	unsigned int		hour;
	unsigned int		day;
	unsigned int		month;
	unsigned int		year;
	unsigned int		weekday;	/*0:Sunday--6:Saturday*/
}DateTimeStructTyp;

typedef struct
{
	unsigned int		GroupNo;
	unsigned int		GroupIndex;
	float				GroupAvg;			//组平均重量,g
	float				GroupMax;
	float				GroupMin;
	float				GroupMaxRatio;
	float				GroupMinRatio;
	float				GroupWeightDelta;
	unsigned int		Tag;				//表格标记
}Displaytyp;

typedef struct
{
	float		Weight[20];
	float		Avg;
}DisplayWeightTyp;
//input
typedef struct
{
	bool		FeedTrigger;			//胶囊下落检测
	bool		SwingTrigger;			//摆臂位置检测
}Input_typ;


//output
typedef	struct
{	
	bool		Reject;					//排废电磁铁
	bool		ChannelSwith;			//胶囊通道切换
	bool		Vaccum;					//真空发生器
	bool		CapGet;					//取料电磁铁
	bool		CapGetValve;			//取料电磁阀
	bool		CapBackValve;			//回料电磁阀
	bool		AlarmOut;				//报警蜂鸣器
	bool		StopSignal;				//停机信号
	bool		AlarmSignal;			//报警输出
	bool        YellowAlarmout;			//黄灯报警
	bool		Baffle;					//挡板
	short		Analogoutput;			//模拟量输出 ///// 下面这三个没用
	bool		Photo;					//拍照
	bool		Flash;					//闪光	
}Output_typ;


/**********************************************************/
/* 通讯数据 */
/**********************************************************/
#define		TELEGRAM_TYPE_HEARTBEAT		0
#define		TELEGRAM_TYPE_COMMAND		1
#define		TELEGRAM_TYPE_PARAMETER		2
#define		TELEGRAM_TYPE_RESULT		3
#define		TELEGRAM_TYPE_RUNPARA		4
#define		TELEGRAM_TYPE_REPLY			100

typedef struct
{
	unsigned int		enable;

	float		s_trg_stop[MAX_PULSE_SERVO];				//停止位置
	float		FeedTimeOut;								//下料超时时间,单位s
	float		CapPickInterval;							//自动取料周期,单位s
	float		CapBackInterval;							//成品返还周期,单位s

	float		TireDelay;									//去皮延迟启动时间,单位s
	float		ReadDelay;									//读数延迟启动时间,单位s
	float		TireWaitTime;								//去皮等待时间,单位s
	int			StopSignalDelay;							//连续几次超重或超轻后输出停机信号

	int			Reserve[16];								//预留空间
}Comm_Machine_Para_typ;

typedef struct
{
	int				SysOveride;				//系统速度，0-10000对应0-100%
	int				PassCount;				//通过计数
	int				RejectCount;			//剔废计数
	int				ProdCount;				//称重计数
	unsigned int	TOCount;				//过重计数
	unsigned int	TUCount;				//过轻计数
	float			TOverload;				//超重重量,单位g
	float			TUnderload;				//超轻重量,单位g
	float			InterOverLoad;			//内控线，上限,单位g
	float			InterUnderLoad;			//内控线，下限,单位g
	float			TDemand;				//期望重量,单位g			
	int				TireMode;				//0:每组去皮重,1:每次称重去皮重
	int				GroupSet;				//每组测试胶囊数量
	float			TestInterval;			//测试间隔时间,单位s
	char			BatchName[40];			//批号字符串
	unsigned int	GroupNo;				//当前组号
	int				Language;				//当前语言，0：中文，1：英文
	float			UserAnalogoutput;		//用户模拟量输入
	float			Adjustvalue;			//自动调整系数
	unsigned int	DeltaInput;				//装量调整偏差值
	int				usertime;				//用户定义打印时间间隔(分钟)
	float			Rsd;					//相对标准偏差值
	int				cmdAutoPrint;			//自动打印，1:自动，0：手动

	int				Reserve[16];			//预留空间
}Comm_Run_Para_typ;

typedef struct
{
	unsigned int		AlarmStatus;			//报警状态,0:无报警，1:Warning, 2,Fatal Error
	unsigned char		Alarm[16];				//报警位0-99，每一位对应一个报警,Alarm[0].0 ---- Alarm[13].3
	
	unsigned int		ServoErrorNum[2];		//伺服报警代码
	unsigned int		SysPhase;				//系统相位
	unsigned int		HomeOK;					//寻参成功

	unsigned int		CommStep;				//通讯状态
	unsigned int		NoDataCounter;			//无数据计数
	unsigned int		SendCounter;			//发送报文计数
	unsigned int		RecvCounter;			//接收报文计数
	unsigned int		RecvTelLength;			//接收报文长度

	unsigned int		CommStep2;				//通讯状态2
	unsigned int		NoDataCounter2;			//无数据计数2
	unsigned int		SendCounter2;			//发送报文计数2
	unsigned int		RecvCounter2;			//接收报文计数2
	unsigned int		RecvTelLength2;			//接收报文长度2

	unsigned int		RejectTelCount;			//接收到剔废报文的计数器
	unsigned int		RejectTelRecivedPhase;	//接收到剔废报文的相位
	unsigned int		ServoState[2];			//伺服状态
	unsigned int		RejectCounter[6]; //通道剔废计数 useless for me
	int Reserve[32]; //预留空间
}Comm_Status_typ;

typedef struct
{
	unsigned char		cmdHome;							//寻参,1:寻参启动
	unsigned char		cmdStart;							//启动,1:启动运行
	unsigned char		cmdStop;							//停止,停在0相位,1:停止
	unsigned char		cmdEStop;							//紧急停止(立即停止), 1:停止
	unsigned char		cmdJog;								//点动运行, 1,启动,0,停止
	unsigned char		cmdErrorAck;						//报警复位, 1:复位
	unsigned char		cmdResetCounter;					//复位计数变量, 1:复位
	unsigned char		cmdParaSave;						//参数保存命令, 1:保存
	unsigned char		cmdParaLoad;						//参数读取命令, 1:读取
	unsigned char		cmdTestKick[6];		//手动剔废, 1:Push, 2:Back
	unsigned char		cmdTestFlash[6];			//手动闪光, 1:闪光,自动复位
	unsigned char		cmdTestValveUp;						//手动升降气缸, 1:Push, 2:Back
	unsigned char		cmdTestValveClip;					//手动夹紧气缸, 1:Push, 2:Back
	unsigned char		cmdTestValveDrop;					//手动落囊气缸, 1:Push, 2:Back
	unsigned char		cmdTestInverter;					//手动胶囊料斗启动, 1:Start, 2:Stop
	unsigned char		cmdTestLampRead;					//手动红灯输出, 1:输出 , 2: 复位
	unsigned char		cmdTestLampYellow;					//手动黄灯输出, 1:输出 , 2: 复位
	unsigned char		cmdTestLampGreen;					//手动绿灯输出, 1:输出 , 2: 复位
	unsigned char		cmdTestBuzzer;						//手动蜂鸣器输出, 1:输出 , 2: 复位
	unsigned char		cmdTestPhoto;						//手动拍照, 1:输出 , 2: 复位
	unsigned char		cmdTestFlashPhoto;					//手动闪光加拍照, 1:启动
	unsigned char		cmdTestCapPhoto;					//手动胶囊拍照
	unsigned char		cmdRotateCtl;						//手动转囊启停
	unsigned char		cmdSetAlarm;								//手动触发报警号，不等于零触发。范围1-99

	unsigned char Reserve[32]; //预留空间
}Comm_Machine_Cmd_typ;

typedef struct
{//照相处理结果
	unsigned char		Alarm[4];				//4bytes=32bits,每一位对应一个通道,0:通过,1:剔废
	unsigned int		id;						//结果id

	int Reserve[16]; //预留空间
}Comm_Result_typ;

typedef struct DataFromPC_typ
{
	unsigned int						Dummy;				//占空
	unsigned int						Telegram_typ;		//报文类型，0:心跳报文,1:命令报文,2:参数报文,3:结果报文,4,运行参数,100:应答
	Comm_Machine_Para_typ		Machine_Para;		//系统参数 2
	Comm_Run_Para_typ			Run_Para;			//运行参数 4
	Comm_Machine_Cmd_typ		Machine_Cmd;		//命令 1
	Comm_Result_typ				PhotoResult;		//拍照处理结果 3
	DataFromPC_typ()
	{
		memset(this, 0, sizeof(DataFromPC_typ));
	}
}DataFromPC_typ;

//_GLOBAL			DataFromPC_typ			DataFromPC;

typedef struct DataToPC_typ
{
	unsigned int						Telegram_typ;		//报文类型，0:心跳报文,1:命令报文,2:参数报文,3:结果报文,100:应答
	Comm_Run_Para_typ			ActData;			//运行数据
	Comm_Status_typ				Status;				//系统状态	
	Comm_Machine_Para_typ		Machine_Para;		//系统参数
	Input_typ					Inputs;				//输入点 
	Output_typ					Outputs;			//输出点 	
	bool operator==(const DataToPC_typ &data)
	{
		//if (Status.HomeOK != data.Status.HomeOK)return false;
		//if (Telegram_typ!= data.Telegram_typ)return false; 
		//if (Status.AlarmStatus != data.Status.AlarmStatus)return false;
		//if (ActData.CheckCount != data.ActData.CheckCount)return false;
		//if (ActData.RunSpeed != data.ActData.RunSpeed)return false;
		return true;
	}
}DataToPC_typ;

//_GLOBAL			DataToPC_typ			DataToPC;


#endif

