#include<stdio.h>
#include<stdlib.h>

struct node {
int Process;
int ArrivalTime;
int BurstTime;
int TurnAroundTime;
int WaitingTime;
int CompletionTime;
struct node *next;
};
struct node *start = NULL;

//Implemented in later version as I realized i was manuplating BurstTime of orignal List which created problem in claculating Waiting Time
int arrayIndex = 0;
int individaulBurstTimeHolder[100];

int n;
int currentTime = 0;
int startTime = 0;
int totalBurstTime;


int numberOfProcessesWithBurstTimeZero = 0;

void createNode(){
    struct node *temp = start;
    struct node *p = (struct node *)malloc(sizeof(struct node));
    printf("\nEnter Process Number : ");
    scanf("%d",&p->Process);

    printf("\nEnter Burst Time : ");
    scanf("%d",&p->BurstTime);
	
	//Save the Orignal BurstTime in an array
	individaulBurstTimeHolder[arrayIndex] = p->BurstTime;
	arrayIndex++;

	p->CompletionTime = 0;
    p->ArrivalTime = 0;
    p->TurnAroundTime = 0;
    p->WaitingTime = 0;
    p->next=NULL;

    if(start == NULL){
        start = p;
    }

    else{
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = p;
    }
}


void main()
{

    int i,timeQuantum;
    struct node *mainTemp = start;

    printf("\n ENTER THE NUMBER OF PROCESS : ");
    scanf("%d",&n);
    for(i=1;i<=n;i++){
        createNode();
    }

    printf("\nENTER THE TIME QUANTUM : ");
    scanf("%d",&timeQuantum);

    printf("\nTOTAL PROCESSES IN THE SYSTEM : ");
    mainTemp = start;
    while(mainTemp != NULL){
        printf(" %d ",mainTemp->Process);
        totalBurstTime = totalBurstTime + mainTemp->BurstTime;
        mainTemp = mainTemp->next;
    }



	
    mainTemp = start;
    struct node *quantumPointer = start;

    printf("\nNOTE: Output Format is:- TIME <PROCESS NO> TIME <PROCESS NO> ... \n");

    printf(" %d ",startTime);
    while(1)
    {
        quantumPointer = start;
        while(quantumPointer != NULL)
        {
            //Print the processes one by one in the order they were taken.
            if(quantumPointer->BurstTime != 0)
            {
                printf(" < %d > ",quantumPointer->Process);
            }


            //Reduce the burst time by time quantum
            if(quantumPointer->BurstTime != 0)
            {
                //If BURST TIME is < Time Quantum then current time is Full Burst Time of that Process (It has been fully executed)
                if(quantumPointer->BurstTime < timeQuantum)
                {
                    currentTime = currentTime + quantumPointer->BurstTime;
                    printf(" %d ",currentTime);
                }

				//If BURST TIME is > TIME QUANTUM then obviously the process executed only for time=timeQuantum and then preempted
                if(quantumPointer->BurstTime > timeQuantum)
                {
                    currentTime = currentTime + timeQuantum;
                    printf(" %d ",currentTime);
                }

				//Handle equal to case
                if(quantumPointer->BurstTime == timeQuantum)
                {
                    currentTime = currentTime + timeQuantum;
                    printf(" %d ",currentTime);
                }

                quantumPointer->BurstTime = quantumPointer->BurstTime - timeQuantum;
            }

            //If burst time goes to negative, make it zero
			/*If process has BURST TIME zero that means the process wont we executing again. Hence set its execution time = currentTime 
			and next time dont allow that process to enter this if-statement again. as it will set the CompletionTime again and again */
            if(quantumPointer->BurstTime <= 0 && quantumPointer->CompletionTime == 0)
            {
                quantumPointer->BurstTime = 0;
                numberOfProcessesWithBurstTimeZero++;
				quantumPointer->CompletionTime = currentTime;
            }
            quantumPointer = quantumPointer->next;
        }



        if(numberOfProcessesWithBurstTimeZero == n || currentTime == totalBurstTime)
        {
            break;
        }

    }
	
	printf("\n");
    printf("\nDETAILS OF EACH PROCESS : ");
    int totalTurnAroundTime = 0;
    int totalWaitingTime = 0;
    struct node *m = start;
	int index = 0;
    while(m != NULL)
    {
		//Calculate TURN AROUND TIME and WAITING TIME for each process before printing
		m->TurnAroundTime = m->CompletionTime - m->ArrivalTime;
		m->WaitingTime = m->TurnAroundTime - individaulBurstTimeHolder[index];

        printf("\n Process No = %d : Arrival Time = %d : Burst Time = %d : Turn Around Time = %d : Waiting Time = %d : Completion Time = %d ",m->Process,m->ArrivalTime,m->BurstTime,m->TurnAroundTime,m->WaitingTime,m->CompletionTime);

		totalTurnAroundTime = totalTurnAroundTime + m->TurnAroundTime;
        totalWaitingTime = totalWaitingTime + m->WaitingTime;
		
        m = m->next;
		index++;
    }

    printf("\n average waiting time = %f ",(float)totalWaitingTime/n);
    printf("\n average turn around time = %f ",(float)totalTurnAroundTime/n);
}
