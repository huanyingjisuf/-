//CKCON¼Ä´æÆ÷¶¨Òå

#define IHCKE		(1<<7)
#define ILCKE		(1<<6)
#define PFGKE		(1<<5)
#define SCKS(n)			(n<<0)


#define CKSEL_IRCH	0	
#define CKSEL_IRCL	1


void Sys_Clk_Set_IRCH(void);
void Sys_Clk_Set_IRCL(void);

