#include <stdio.h>
#include <stdlib.h>
struct timer
{
	int waitTime;
	struct timer* next;
	struct timer* prev;
};
typedef struct timer timer;

void printList(timer* baseTimer)
{
	timer *next = baseTimer->next;
	printf("%d",baseTimer->waitTime);
	while(next != baseTimer)
	{
		printf("->%d",next->waitTime);
		next = next->next;
	}
	printf("\n");
}

/* add timerto the list based on the delay
 */
void addTimer(timer* baseTimer, int delay)
{
	timer* newTimer = (timer*)malloc(sizeof(timer));
	timer* next = baseTimer->next;
	while(delay > next->waitTime)
	{
		delay = delay - next->waitTime;
		next = next->next;
	}
	next->waitTime -= delay;			//decrement next timer's delay
	newTimer->prev = next->prev;		// ->old->new->next  new timer previous is next timer previous
	next->prev->next = newTimer;		// old->next = new
	next->prev = newTimer;				// next timer previous is newTimer
	newTimer->next = next;				// newTimer next is next timer
	newTimer->waitTime = delay;			// waitTime of newTimer
}

/* check for expired timers
 * if waitTime = 0 remove the timer from the list.
 */
void removeTimer(timer* baseTimer)
{
	timer* next = baseTimer->next;
	while(next != baseTimer)		//check if the timer is not the base timer	
	{
		if(next->waitTime == 0)		//check if timer expired
		{
			next->prev->next = next->next;	//remove the timer from the list	
			next->next->prev = next->prev;
		}
		else
		{
			break;					//if first timer is not expired no need to check next timers
		}
		next = next->next;
	}
}
/* decrement the timer with the value.
 * add value to the base timer
 * handle if waitTime < 0 : assign waitTime = 0
 */
void decTimer(timer* baseTimer,int value)
{
	timer* next = baseTimer->next;
	while(value > next->waitTime && next != baseTimer) //if decrement value is greater than the first timer waitTime 
	{													//only then decrement excess value from other timers
		baseTimer->waitTime += next->waitTime;		//add the decremented value to base timer
		value -= next->waitTime;					//reduce the decremented value
		next->waitTime = 0;							//current timer is expired 
		next = next->next;  
	}
	if(next != baseTimer)							//add the decremented value to the baseTimer
	{
		baseTimer->waitTime += value;
		next->waitTime -= value;
	}
	removeTimer(baseTimer);						//remove the expired timers
}

int main(int argc, char **argv)
{
	timer* baseTimer = (timer*)malloc(sizeof(timer));		//create base timer
	baseTimer->waitTime = 10000;							//initialize base Timer value
	baseTimer->next = baseTimer;
	baseTimer->prev = baseTimer;
	
	printList(baseTimer);									//base<-base->base
	addTimer(baseTimer,2000);								
	printList(baseTimer);									//base->timer1
	addTimer(baseTimer,500);
	printList(baseTimer);									//base->timer1->timer2
	decTimer(baseTimer,500);	//decrement 500			
	printList(baseTimer);									//base->timer1
	addTimer(baseTimer,2000);
	printList(baseTimer);									//base->timer1->timer3
	addTimer(baseTimer,3000);
	printList(baseTimer);									//base->timer1->timer3->timer4
	decTimer(baseTimer,1000); //decrement 1000
	printList(baseTimer);									//base->timer1->timer3->timer4
	addTimer(baseTimer,3000);
	printList(baseTimer);									//base->timer1->timer3->timer4->timer5
	return 0;
}
