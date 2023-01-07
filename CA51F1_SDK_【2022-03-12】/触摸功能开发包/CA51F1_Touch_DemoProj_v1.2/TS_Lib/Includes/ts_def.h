//TKCON����
#define TKST(N)		(N<<7)	 //N=0-1
#define TKIE(N)		(N<<6)	 //N=0-1
#define TMEN(N)		(N<<5)	 //N=0-1	//RTC����TKST
#define FAEN(N)		(N<<4)	 //N=0-1	//ʡ���Զ�����	  0��TKST=0������TKIF, 1: TKST=0������Ƚ�������Ų���TKIF 
#define TCAPSEL(N)	(N<<3)	 //N=0-1	//���òο�ͨ���Ƿ�ѡ��
#define VRS(N)		(N<<0)	 //N=0-7	//�Ƚ����ο���ѹѡ��

//TKCFG����
#define TKDIV(N)	(N<<5)	 //N=0-7	//ʱ�ӷ�Ƶ		��Ƶϵ�� ��TKDIV+1����0������Ƶ
#define TKTMS(N)	(N<<0)	 //N=0-31	//�ŵ�ʱ������   �ŵ�ʱ�䣺 (TKTMS)*32*Ttk  , TKTMS�������0�����Ϊ0���ŵ� 

//TKxCHS����			//x=0-5
#define MPOL(N)     (N<<7) 	 //N=0-1	   //0- TKxMS <  ATKxM; 1-  TKxMS >=  ATKxM
#define NPOL(N)     (N<<6) 	 //N=0-1	   //0- TKxMS <  ATKxN; 1-  TKxMS >=  ATKxN
#define TKPS(N)    	(N<<0) 	 //N=0-14   0����ѡ    1-13��ӦTK0-TK12; 14��ӦTKCAP

//TKIF����					 //TKST=0��һ����λ
#define TKIF5		(1<<5)
#define TKIF4		(1<<4)
#define TKIF3		(1<<3)
#define TKIF2		(1<<2)
#define TKIF1		(1<<1)
#define TKIF0		(1<<0)

//TKPWC����
#define TKPC(N)		(N<<6)	 //N=0-3
#define VDS(N)		(N<<4)	 //N=0-3
#define VIRS(N)		(N<<2)	 //N=0-3
#define TKPWS(N)	(N<<1)	 //N=0-1
#define TKCVS(N)	(N<<0)	 //N=0-1

//TKCKS����
#define TKSIL(N)	(N<<0)	 //N=0-1


//TLCKS����
#define TLCKS(N)	(N<<0)	 //N=0-7

//TLCKS����
#define TLCOMS(N)	(N<<0)	 //N=0-7


typedef union 
{	
	unsigned long int 	dwVal;
	unsigned int 		wVal[2];
	unsigned char 		bVal[4];
}
DWORD_UNION;

typedef union 
{	
	unsigned int 	wVal;
	unsigned char 	bVal[2];
}
WORD_UNION;

typedef enum
{
	TS_INIT,
	TS_DEAL
} TSState_T;

enum 
{
	AREA_FINGER_TOUCH,
	AREA_PNOISE_PLUS,
	AREA_PNOISE,
	AREA_NNOISE,
	AREA_OVER_LOW		
};
enum 
{
	WHEEL_SLIDER_NO_TOUCH,
	WHEEL_SLIDER_TOUCH,	
};

#define WHEEL 	0
#define SLIDER  1
enum
{
	TS_CH0,
	TS_CH1,
	TS_CH2,
	TS_CH3,
	TS_CH4,
};

#define KEY_BREAK			0x1000     	//�̰�̧��
#define KEY_LONG			0x2000     	//����
#define KEY_LONG_BREAK		0x3000		//����̧��
#define KEY_LONG_START		0x4000		//������ʼ   

#define K1					0x0001
#define K2					0x0002
#define K3					0x0003
#define K4					0x0004
#define K5					0x0005

enum 
{
	TK_STATE_RELEASE,
	TK_STATE_SINGLE_KEY_PRESS,	
	TK_STATE_DOUBLE_KEY_PRESS,
};

#define TS_LONG_START_TIME	250
#define TS_LONG_TIME				70



