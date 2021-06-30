/**********************************************************/
/* ͨѶ���� */
/**********************************************************/
//unsigned int == UDINT 4���ֽ�
//int == DINT 4���ֽ� ��longһ����4���ֽ� 
//float == REAL 4���ֽ� double��longlong��8���ֽ�
//unsigned char = USINT 8λ 1���ֽ�
//char == STRING
//char[40] == STRING[40] 8λ 1���ֽ���1���ַ�ռλ
//bool == BOOL 1λ
//short == INT 2���ֽ�
//short == UINT 2���ֽ�
#define UDINT unsigned int
#define DINT int
#define REAL float
#define USINT unsigned char
#define STRING char
#define INT short
#define UINT short
#define LREAL double

#define SET_BIT(_X,_pos)		{_X|=(1l<<(_pos));}
#define GET_BIT(_X,_pos)		((bool)((((long)(_X)&(1l<<(_pos)))!=0))
#define RESET_BIT(_X,_pos)		{(_X=~((~_X)|(1l<<(_pos))));}
#define ABS(x)					((x)>0?(x):(-1*(x)))

#ifndef _COMM_H_

#define	_COMM_H_

#pragma pack(4)
#define			MAX_PULSE_SERVO		2
typedef struct
{
	UINT		second;
	UINT		minute;
	UINT		hour;
	UINT		day;
	UINT		month;
	UINT		year;
	UINT		weekday;	/*0:Sunday--6:Saturday*/
}DateTimeStructTyp;

typedef struct
{
	UDINT		GroupNo;
	UDINT		GroupIndex;
	REAL		GroupAvg;			//��ƽ������,g
	REAL		GroupMax;
	REAL		GroupMin;
	REAL		GroupMaxRatio;
	REAL		GroupMinRatio;
	REAL        GroupWeightDelta;
	UDINT		Tag;				//�����
}Displaytyp;

typedef struct
{
	REAL		Weight[20];
	REAL		Avg;
}DisplayWeightTyp;

typedef struct
{
	bool		FeedTrigger;			//����������
	bool		SwingTrigger;			//�ڱ�λ�ü��
}Input_typ;


//output
typedef	struct
{
	bool		Reject;					//�ŷϵ����
	bool		ChannelSwith;			//����ͨ���л�
	bool		Vaccum;					//��շ�����
	bool		CapGet;					//ȡ�ϵ����
	bool		CapGetValve;			//ȡ�ϵ�ŷ�
	bool		CapBackValve;			//���ϵ�ŷ�
	bool		AlarmOut;				//����������
	bool		StopSignal;				//ͣ���ź�
	bool		AlarmSignal;			//�������
	bool        YellowAlarmout;			//�ƵƱ���
	bool		Baffle;					//����
	bool		LeftFeed;				//��ȡ��
	bool		RightFeed;				//��ȡ��
	bool		LeftAbsorb;				//���ȡ
	bool		RightAbsorb;			//�ҳ�ȡ
	INT			Analogoutput;			//ģ�������
}Output_typ;


/**********************************************************/
/* ͨѶ���� */
/**********************************************************/
#define		TELEGRAM_TYPE_HEARTBEAT		0
#define		TELEGRAM_TYPE_COMMAND		1
#define		TELEGRAM_TYPE_PARAMETER		2
#define		TELEGRAM_TYPE_RESULT		3
#define		TELEGRAM_TYPE_RUNPARA		4
#define		TELEGRAM_TYPE_REPLY			100

typedef struct
{
	REAL		s_trg_stop[MAX_PULSE_SERVO];				//ֹͣλ��	
	REAL		FeedTimeOut;				//���ϳ�ʱʱ��,��λs	
	REAL		CapPickInterval;				//�Զ�ȡ������,��λs	
	REAL		CapBackInterval;				//��Ʒ��������,��λs	
	REAL		CapAbsorbInterval;				//��ȡʱ��	
	REAL		TireDelay;				//ȥƤ�ӳ�����ʱ��,��λs	
	REAL		ReadDelay;				//�����ӳ�����ʱ��,��λs	
	REAL		TireWaitTime;				//ȥƤ�ȴ�ʱ��,��λs	
	UINT		StopSignalDelay;				//�������γ��ػ�������ͣ���ź�	
	REAL		CapPickInterval2;				//��ȡʱ��2	
	DINT		PillPickCount;				//ȡ�ϼ���	
	DINT		PillPickCount2;				//ȡ�ϼ���2	
	UINT		StartCapNum;				//��������ȡ��	
	UINT		StartPillNum;				//����Ƭ��ȡ��	
	UINT		enable;				//1��ȡ2д��	
	UINT		temp;				//no use	


	DINT		Reserve[16];							//Ԥ���ռ�
}Comm_Machine_Para_typ;

typedef struct
{
	UINT		SysOveride;		//ϵͳ�ٶ�
	UINT		StableState;		//0:�ǳ��ȶ�,1:�ȶ�,2:���ȶ�,3:�ǳ����ȶ�
	UDINT		PassCount;		//ͨ������
	UDINT		ProdCount;		//���ؼ���
	UDINT		TOCount;		//���ؼ���
	UDINT		TUCount;		//�������
	UDINT		RejectCount;		//�޷ϼ���
	UINT		WorkMode;		//0:Ƭ����1������
	UINT		GroupSet;		//ÿ����Խ�������
	UINT		GroupCounter;		//����������
	UINT		TireMode;		//0:ÿ��ȥƤ��,1:ÿ�γ���ȥƤ��
	REAL		TestInterval;		//���Լ��ʱ��,��λs
	REAL		TOverload;		//��������,g
	REAL		TUnderload;		//��������,g
	REAL		TDemand;		//��������,g
	DINT		DeltaSwing;		//λ��ƫ��,δʹ��
	UINT		GroupWeightCounter;		//���������
	UINT		GroupRejectCounter;		 //���߷�����,ָ�޷ϴ���,���޷϶���
	STRING		BatchName[40];		//�����ַ���
	UDINT		GroupNo;		//���
	UDINT		GroupIndex;		//����������
	LREAL		GroupSum;		//������
	REAL		GroupAvg;		//��ƽ������,g
	REAL		GroupMax;		//�����ֵ
	REAL		GroupMin;		//����Сֵ
	REAL		GroupMaxRatio;		//�����ƫ��
	REAL		GroupMinRatio;		//����Сƫ��
	REAL		InterOverLoad;		//�ڿ��ߣ�����
	REAL		InterUnderLoad;		//�ڿ��ߣ�����
	bool		UsbOk;		//U��׼����
	bool		UsbPrintOk;		//Print׼����
	REAL		UserAnalogoutput;		//�û�ģ��������
	REAL		Adjustvalue;		//�Զ�����ϵ��
	UDINT		DeltaInput;		//װ������ƫ��ֵ
	REAL		TestInterval2;		//���Լ��ʱ��2,��λs
	UINT		GroupSet2;		//ÿ����Խ�������2
	UINT		CurrentGroup;		//��ǰ������Ӧ�ĸ�������0����1��1����2
	REAL		EmptyCapAvgWeight;		//�ս��ҿǾ���
	UINT		enGroupMode;		//0:��ͨģʽ��1:���ģʽ
	UINT		GroupAmount;		//�������


	DINT				Reserve[16];			//Ԥ���ռ�
}Comm_Run_Para_typ;

typedef struct
{
	DINT				Finished;				//�������
	DINT				GroupIndex;				//�������
	REAL				Weight;					//��������

	//plc���
	DateTimeStructTyp	PLCTimeNow;				//PLC��ǰʱ��
	DINT				UsbPrintOk;				//��ӡ����������,0:δ���ӣ�1��������
	DINT				UsbOk;					//U����������,0:δ���ӣ�1��������

	//Scale Data
	REAL				ScaleResult;			//��ƽ��ǰ��������λg
	DINT				ScaleStableState;		//��ƽ��ǰ�ȶ�״̬,0:�ǳ��ȶ�,1:�ȶ�,2:���ȶ�,3:�ǳ����ȶ�

	//Group Data
	Displaytyp			CapDataDisp;			//������

	//AxisStatus
	DINT				AxisFeedStep;			//���ϵ��״̬������
	DINT				AxisFeedErrorNo;		//���ϵ���������
	DINT				AxisFeedRelMovDistance;	//���ϵ������˶����룬��λunit

	DINT				AxisSwingStep;			//��ת���״̬������
	DINT				AxisSwingErrorNo;		//��ת����������
	DINT				AxisSwingRelMovDistance;//��ת�������˶����룬��λunit

	//MainCtrl etc
	DINT				MachineStep;			//ϵͳ����״̬������
	REAL				TimeInterval;			//����ʵ�ʼ��ʱ��

	DINT				AlarmStatus;			//0:�ޱ�����1��һ�㱨����2�����ر���
	USINT				Alarm[16];				//����λ0-99��ÿһλ��Ӧһ������,Alarm[0].0 ---- Alarm[13].3

	DINT				usertime;				//�û������ӡʱ����(����)
	REAL				Rsd;					//��Ա�׼ƫ��ֵ


	DINT				Reserve[31];			//Ԥ���ռ�
}Comm_Status_typ;

typedef struct
{//���ദ����
	UDINT		OK;								//0:�ϸ�1�����ϸ�
	DINT		Reserve[16];					//Ԥ���ռ�
}Comm_Result_typ;

typedef struct
{
	DateTimeStructTyp		DateTimeSet;		//�趨����ʱ��Ŀ��
	USINT		cmdChangeDT;					//�޸�����ʱ��,1:ִ�У��Զ���λ

	USINT		cmdScaleRead;					//�Ӷ�������,1:ִ�У��Զ���λ
	USINT		cmdScaleTire;					//������,1:ִ�У��Զ���λ
	USINT		cmdScaleSetStable;				//�趨���ȶ�״̬,1:ִ�У��Զ���λ
//	USINT		paraScaleSetStable;				//�ȶ�״̬�趨Ŀ�꣬0:�ǳ��ȶ�,1:�ȶ�,2:���ȶ�,3:�ǳ����ȶ�

	USINT		cmdScaleCalibExt;				//���ⲿУ��,1:ִ�У��Զ���λ
	USINT		cmdAxisFeedJogPos;				//������ת�㶯��1:ִ�У�0:ֹͣ
	USINT		cmdAxisFeedJogNeg;				//���Ϸ�ת�㶯��1:ִ�У�0:ֹͣ
	USINT		cmdAxisFeedRelMov;				//��������˶�������1:ִ�У��Զ���λ
	USINT		cmdAxisFeedPosMov;				//�������������˶�������1:ִ�У��Զ���λ
	USINT		cmdAxisFeedStopMov;				//����ֹͣ�˶���1:ִ�У��Զ���λ

	USINT		cmdAxisSwingJogPos;				//��ת��ת�㶯��1:ִ�У�0:ֹͣ
	USINT		cmdAxisSwingJogNeg;				//��ת��ת�㶯��1:ִ�У�0:ֹͣ
	USINT		cmdAxisSwingRelMov;				//��ת����˶�������1:ִ�У��Զ���λ
	USINT		cmdAxisSwingPosMov;				//��ת���������˶�������1:ִ�У��Զ���λ
	USINT		cmdAxisSwingStopMov;			//��תֹͣ�˶���1:ִ�У��Զ���λ

	USINT		cmdFeedSingle;					//�������ϣ�1:ִ�У��Զ���λ
	USINT		cmdFeedSingleStop;				//��������ֹͣ��1:ִ�У��Զ���λ

	USINT		cmdSwing;						//��ת����λ,1:ִ�У��Զ���λ
	USINT		cmdStart;						//�������أ�1:ִ�У��Զ���λ
	USINT		cmdEStop;						//��ͣ��1:ִ�У��Զ���λ
	USINT		cmdStop;						//ֹͣ,1:ִ�У��Զ���λ
	USINT		cmdInit;						//��ʼ����1:ִ�У��Զ���λ
	USINT		cmdAlarmReset;					//������λ,1:ִ�У��Զ���λ
	USINT		cmdCounterZero;					//����������,1:ִ�У��Զ���λ
	USINT		cmdPrintStart;					//������ӡ,1:ִ�У��Զ���λ
	USINT		cmdPrintStartE;					//����Ӣ�Ĵ�ӡ��1:ִ�У��Զ���λ
	USINT		cmdCapClean;					//��ս��ң�1:ִ�У��Զ���λ
	USINT		cmdAlogtest;					//ģ�����������,1:ִ�У��Զ���λ

	USINT		LeftRightFeedSign;				//���ҽ��ϱ�־0�����1�ҽ���
	USINT		cmdSingleSelect;				//����ѡ��
	USINT		cmdLeftGetCap;					//��ȡ�Ҷ���
	USINT		cmdRightGetCap;					//��ȡ�Ҷ���
	USINT		cmdReject;						//�߷�
	USINT		cmdFeedAmount;					//�������
	Output_typ					Outputs;			//�����

	DINT				AxisFeedRelMovDistance;	//���ϵ������˶����룬��λunit

	DINT				AxisSwingRelMovDistance;//��ת�������˶����룬��λunit



	USINT		Reserve[32];					//Ԥ���ռ�
}Comm_Machine_Cmd_typ;



typedef struct DataFromPC_typ
{
	UDINT						Telegram_typ;		//�������ͣ�0:��������,1:�����,2:��������,3:�������,4,���в���,100:Ӧ��
	Comm_Machine_Para_typ		Machine_Para;		//ϵͳ����
	Comm_Run_Para_typ			ActData;			//���в���
	Comm_Machine_Cmd_typ		Machine_Cmd;		//����
	Comm_Result_typ				PhotoResult;		//���մ�����
	DINT						Reserve[16];		//Ԥ���ռ�
	DataFromPC_typ()
	{
		memset(this, 0, sizeof(DataFromPC_typ));
	}
}DataFromPC_typ;

//_GLOBAL			DataFromPC_typ			DataFromPC;

typedef struct DataToPC_typ
{
	UDINT						Telegram_typ;		//�������ͣ�0:��������,1:�����,2:��������,3:�������,100:Ӧ��
	//ActData�����޸ģ�ԭRun_Para
	Comm_Run_Para_typ			ActData;			//��������
	Comm_Status_typ				Status;				//ϵͳ״̬
	Comm_Machine_Para_typ		Machine_Para;		//ϵͳ����
	Input_typ					Inputs;				//����� 
	Output_typ					Outputs;			//����� 

	DINT						Reserve[16];		//Ԥ���ռ�

}DataToPC_typ;

#pragma pack()
//_GLOBAL			DataToPC_typ			DataToPC;


#endif

