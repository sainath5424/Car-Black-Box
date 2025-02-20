#include <xc.h>
#include "main.h"
#include "timer0.h"
extern unsigned int wait=0;
 int wait1;
void __interrupt() isr(void)
{
	static unsigned int count=0;
	if (TMR0IF)
	{
		TMR0 = TMR0 + 8;

		if (count++ == 20000)
		{
            //RB0 = !RB0;
			count = 0;
            wait++;
            wait1--;
			
		}
		TMR0IF = 0;
	}
}