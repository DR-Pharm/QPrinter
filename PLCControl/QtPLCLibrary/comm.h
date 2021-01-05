/**********************************************************/
/* ͨѶ���� */
/**********************************************************/
//unsigned int == UDINT 4���ֽ�
//int == DINT 4���ֽ� ��longһ����4���ֽ� 
//float == REAL 4���ֽ� double��longlong��8���ֽ�
//unsigned char = USINT 8λ 1���ֽ�
//char[40] == STRING[40] 8λ 1���ֽ���1���ַ�ռλ
//bool == BOOL 1λ
//short == INT 2���ֽ�

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
	float				GroupAvg;			//��ƽ������,g
	float				GroupMax;
	float				GroupMin;
	float				GroupMaxRatio;
	float				GroupMinRatio;
	float				GroupWeightDelta;
	unsigned int		Tag;				//�����
}Displaytyp;

typedef struct
{
	float		Weight[20];
	float		Avg;
}DisplayWeightTyp;
//input
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
	short		Analogoutput;			//ģ������� ///// ����������û��
	bool		Photo;					//����
	bool		Flash;					//����	
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
	unsigned int		enable;

	float		s_trg_stop[MAX_PULSE_SERVO];				//ֹͣλ��
	float		FeedTimeOut;								//���ϳ�ʱʱ��,��λs
	float		CapPickInterval;							//�Զ�ȡ������,��λs
	float		CapBackInterval;							//��Ʒ��������,��λs

	float		TireDelay;									//ȥƤ�ӳ�����ʱ��,��λs
	float		ReadDelay;									//�����ӳ�����ʱ��,��λs
	float		TireWaitTime;								//ȥƤ�ȴ�ʱ��,��λs
	int			StopSignalDelay;							//�������γ��ػ�������ͣ���ź�

	int			Reserve[16];								//Ԥ���ռ�
}Comm_Machine_Para_typ;

typedef struct
{
	int				SysOveride;				//ϵͳ�ٶȣ�0-10000��Ӧ0-100%
	int				PassCount;				//ͨ������
	int				RejectCount;			//�޷ϼ���
	int				ProdCount;				//���ؼ���
	unsigned int	TOCount;				//���ؼ���
	unsigned int	TUCount;				//�������
	float			TOverload;				//��������,��λg
	float			TUnderload;				//��������,��λg
	float			InterOverLoad;			//�ڿ��ߣ�����,��λg
	float			InterUnderLoad;			//�ڿ��ߣ�����,��λg
	float			TDemand;				//��������,��λg			
	int				TireMode;				//0:ÿ��ȥƤ��,1:ÿ�γ���ȥƤ��
	int				GroupSet;				//ÿ����Խ�������
	float			TestInterval;			//���Լ��ʱ��,��λs
	char			BatchName[40];			//�����ַ���
	unsigned int	GroupNo;				//��ǰ���
	int				Language;				//��ǰ���ԣ�0�����ģ�1��Ӣ��
	float			UserAnalogoutput;		//�û�ģ��������
	float			Adjustvalue;			//�Զ�����ϵ��
	unsigned int	DeltaInput;				//װ������ƫ��ֵ
	int				usertime;				//�û������ӡʱ����(����)
	float			Rsd;					//��Ա�׼ƫ��ֵ
	int				cmdAutoPrint;			//�Զ���ӡ��1:�Զ���0���ֶ�

	int				Reserve[16];			//Ԥ���ռ�
}Comm_Run_Para_typ;

typedef struct
{
	unsigned int		AlarmStatus;			//����״̬,0:�ޱ�����1:Warning, 2,Fatal Error
	unsigned char		Alarm[16];				//����λ0-99��ÿһλ��Ӧһ������,Alarm[0].0 ---- Alarm[13].3
	
	unsigned int		ServoErrorNum[2];		//�ŷ���������
	unsigned int		SysPhase;				//ϵͳ��λ
	unsigned int		HomeOK;					//Ѱ�γɹ�

	unsigned int		CommStep;				//ͨѶ״̬
	unsigned int		NoDataCounter;			//�����ݼ���
	unsigned int		SendCounter;			//���ͱ��ļ���
	unsigned int		RecvCounter;			//���ձ��ļ���
	unsigned int		RecvTelLength;			//���ձ��ĳ���

	unsigned int		CommStep2;				//ͨѶ״̬2
	unsigned int		NoDataCounter2;			//�����ݼ���2
	unsigned int		SendCounter2;			//���ͱ��ļ���2
	unsigned int		RecvCounter2;			//���ձ��ļ���2
	unsigned int		RecvTelLength2;			//���ձ��ĳ���2

	unsigned int		RejectTelCount;			//���յ��޷ϱ��ĵļ�����
	unsigned int		RejectTelRecivedPhase;	//���յ��޷ϱ��ĵ���λ
	unsigned int		ServoState[2];			//�ŷ�״̬
	unsigned int		RejectCounter[6]; //ͨ���޷ϼ��� useless for me
	int Reserve[32]; //Ԥ���ռ�
}Comm_Status_typ;

typedef struct
{
	unsigned char		cmdHome;							//Ѱ��,1:Ѱ������
	unsigned char		cmdStart;							//����,1:��������
	unsigned char		cmdStop;							//ֹͣ,ͣ��0��λ,1:ֹͣ
	unsigned char		cmdEStop;							//����ֹͣ(����ֹͣ), 1:ֹͣ
	unsigned char		cmdJog;								//�㶯����, 1,����,0,ֹͣ
	unsigned char		cmdErrorAck;						//������λ, 1:��λ
	unsigned char		cmdResetCounter;					//��λ��������, 1:��λ
	unsigned char		cmdParaSave;						//������������, 1:����
	unsigned char		cmdParaLoad;						//������ȡ����, 1:��ȡ
	unsigned char		cmdTestKick[6];		//�ֶ��޷�, 1:Push, 2:Back
	unsigned char		cmdTestFlash[6];			//�ֶ�����, 1:����,�Զ���λ
	unsigned char		cmdTestValveUp;						//�ֶ���������, 1:Push, 2:Back
	unsigned char		cmdTestValveClip;					//�ֶ��н�����, 1:Push, 2:Back
	unsigned char		cmdTestValveDrop;					//�ֶ���������, 1:Push, 2:Back
	unsigned char		cmdTestInverter;					//�ֶ������϶�����, 1:Start, 2:Stop
	unsigned char		cmdTestLampRead;					//�ֶ�������, 1:��� , 2: ��λ
	unsigned char		cmdTestLampYellow;					//�ֶ��Ƶ����, 1:��� , 2: ��λ
	unsigned char		cmdTestLampGreen;					//�ֶ��̵����, 1:��� , 2: ��λ
	unsigned char		cmdTestBuzzer;						//�ֶ����������, 1:��� , 2: ��λ
	unsigned char		cmdTestPhoto;						//�ֶ�����, 1:��� , 2: ��λ
	unsigned char		cmdTestFlashPhoto;					//�ֶ����������, 1:����
	unsigned char		cmdTestCapPhoto;					//�ֶ���������
	unsigned char		cmdRotateCtl;						//�ֶ�ת����ͣ
	unsigned char		cmdSetAlarm;								//�ֶ����������ţ��������㴥������Χ1-99

	unsigned char Reserve[32]; //Ԥ���ռ�
}Comm_Machine_Cmd_typ;

typedef struct
{//���ദ����
	unsigned char		Alarm[4];				//4bytes=32bits,ÿһλ��Ӧһ��ͨ��,0:ͨ��,1:�޷�
	unsigned int		id;						//���id

	int Reserve[16]; //Ԥ���ռ�
}Comm_Result_typ;

typedef struct DataFromPC_typ
{
	unsigned int						Dummy;				//ռ��
	unsigned int						Telegram_typ;		//�������ͣ�0:��������,1:�����,2:��������,3:�������,4,���в���,100:Ӧ��
	Comm_Machine_Para_typ		Machine_Para;		//ϵͳ���� 2
	Comm_Run_Para_typ			Run_Para;			//���в��� 4
	Comm_Machine_Cmd_typ		Machine_Cmd;		//���� 1
	Comm_Result_typ				PhotoResult;		//���մ����� 3
	DataFromPC_typ()
	{
		memset(this, 0, sizeof(DataFromPC_typ));
	}
}DataFromPC_typ;

//_GLOBAL			DataFromPC_typ			DataFromPC;

typedef struct DataToPC_typ
{
	unsigned int						Telegram_typ;		//�������ͣ�0:��������,1:�����,2:��������,3:�������,100:Ӧ��
	Comm_Run_Para_typ			ActData;			//��������
	Comm_Status_typ				Status;				//ϵͳ״̬	
	Comm_Machine_Para_typ		Machine_Para;		//ϵͳ����
	Input_typ					Inputs;				//����� 
	Output_typ					Outputs;			//����� 	
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

