/**********************************************************/
/* 通讯数据 */
/**********************************************************/

#define SET_BIT(_X,_pos)		{_X|=(1l<<(_pos));}
#define GET_BIT(_X,_pos)		((bool)((((long)(_X)&(1l<<(_pos)))!=0))
#define RESET_BIT(_X,_pos)		{(_X=~((~_X)|(1l<<(_pos))));}
#define ABS(x)					((x)>0?(x):(-1*(x)))
#ifndef _COMM_H_
#define	_COMM_H_

#define		NUM_OF_CHANNEL				30
#define		NUM_OF_FLASH				3

//input
typedef struct
{
	bool		FeedTrigger;			//胶囊下落检测
	bool		SwingTrigger;			//摆臂位置检测
}Input_typ;


//output
typedef	struct
{	
	bool		Inveter;					//变频器启停
	bool		ClipValve;					//夹紧阀
	bool		UpValve;					//升降阀
	bool		DropValve;					//落囊阀
	
	bool		LampRed;					//红灯
	bool		LampYellow;					//黄灯
	bool		LampGreen;					//绿灯
	bool		Buzzer;						//蜂鸣器
	bool		Photo;						//拍照
	
	bool		Flash[NUM_OF_FLASH];		//光源
	bool		Reject[NUM_OF_CHANNEL];		//剔废
	
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
	int		FeedAxisHomeOffset;		//送进轴寻参偏移,单位0.01度
	
	int		ClipPhase1;				//夹紧气缸动作相位,单位0.01度
	int		ClipPhase2;				//夹紧气缸释放相位,单位0.01度
	int		UpPhase1;				//抬升气缸动作相位,单位0.01度
	int		UpPhase2;				//抬升气缸释放相位,单位0.01度
	int		DropPhase1;				//落料气缸动作相位,单位0.01度
	int		DropPhase2;				//落料气缸释放相位,单位0.01度
	
	float		tClip1;					//夹紧气缸动作延迟,单位ms
	float		tClip2;					//夹紧气缸释放延迟,单位ms
	float		tUp1;					//抬升气缸动作延迟,单位ms
	float		tUp2;					//抬升气缸释放延迟,单位ms
	float		tDrop1;					//落料气缸动作延迟,单位ms
	float		tDrop2;					//抬升气缸释放延迟,单位ms
	
	int		FeedLength;				//送进长度，单位0.01mm
	
	float		FlashTime;				//闪光时间,单位ms
	float		PhotoTime;				//拍照时间,单位ms
	float		RejectTime;				//剔废阀动作时间,单位ms
	
	float		PhotoDelay;				//闪光后多久开始拍照,单位ms
	int		PhotoPhase;				//闪光加拍照相位,单位0.01度	
	int		RejectPhase;			//剔废相位,单位0.01度
	
	int		PhotoTimes;				//每周期照相次数,1-10
	
	float		RotateSpeed;			//最高速度对应旋转速度, RPM
	int		DisableForceReject;		//关闭强制剔废,1:关闭

	int		CapCheckAlarmTime;		//胶囊检测报警时间，单位ms

	int		RejectFallingTime;		//剔废胶囊下落时间，单位ms


	float	PhotoInterval;			//拍照间隔角度，针对转囊，单位:度,范围1-360度。

	int Reserve[16]; //预留空间
}Comm_Machine_Para_typ;

typedef struct
{
	int		RunSpeed;				//运行速度
	int		SysPhase;				//当前系统相位
	int		enPhoto;				//拍照使能 0:停止拍照, 1:开始拍照
	int		enReject;				//剔废使能, 0:停止剔废, 1:开始剔废
	int		enFeed;					//料斗使能
	int		enRotate;				//转囊使能
	unsigned int		CheckCount;				//检测计数
	unsigned int		RejectCount;			//剔废计数
	unsigned int		ForceRejectCount;		//强制剔废计数	
	int Reserve[16]; //预留空间
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
	unsigned int		RejectCounter[NUM_OF_CHANNEL]; //通道剔废计数 useless for me
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
	unsigned char		cmdTestKick[NUM_OF_CHANNEL];		//手动剔废, 1:Push, 2:Back
	unsigned char		cmdTestFlash[NUM_OF_FLASH];			//手动闪光, 1:闪光,自动复位
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
		if (Status.HomeOK != data.Status.HomeOK)return false;
		if (Telegram_typ!= data.Telegram_typ)return false; 
		if (Status.AlarmStatus != data.Status.AlarmStatus)return false;
		if (ActData.CheckCount != data.ActData.CheckCount)return false;
		if (ActData.RunSpeed != data.ActData.RunSpeed)return false;
		return true;
	}
}DataToPC_typ;

//_GLOBAL			DataToPC_typ			DataToPC;


#endif

