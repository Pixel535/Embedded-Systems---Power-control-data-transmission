#include <REGX52.H>
#define PWM_Freq_Num   4	 

sbit PWM_Pin = P2^0;		  

unsigned char PWM = 0;	  
unsigned int temp = 0;  

void InitTimer0(void);
void InitPWM(void);  


void InitTimer0(void)
{
	TMOD &= 0xF0;    
	TMOD |= 0x01;    
	
	TH0 = 0x00;      
	TL0 = 0x00;      
	
	ET0 = 1;        
	EA  = 1;         
	
	TR0 = 1;         
}

void InitPWM(void)
{
	PWM = 0;         
	InitTimer0();    
}


void Timer0_ISR (void) interrupt 1   
{
	TR0 = 0;    

	if(PWM_Pin)	
	{
		PWM_Pin = 0;
		temp = (255-PWM)*PWM_Freq_Num;
		TH0  = 0xFF - (temp>>8)&0xFF;
		TL0  = 0xFF - temp&0xFF;	
	}
	else	    
	{
		PWM_Pin = 1;
		temp = PWM*PWM_Freq_Num;
		TH0  = 0xFF - (temp>>8)&0xFF;
		TL0  = 0xFF - temp&0xFF;
	}

	TF0 = 0;     
	TR0 = 1;    
}

int main(void)
{
   InitPWM();              
 
   PWM = 33;              

   while(1) {;}
}