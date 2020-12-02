#include<stdio.h>
#include<stdlib.h>

struct node {
int Process;
int ArrivalTime;
int BurstTime;
int TurnAroundTime;
int WaitingTime;
struct node *next;
};
struct node *start = NULL;

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
            if(quantumPointer->BurstTime != 0)
            {
                printf(" < %d > ",quantumPointer->Process);
            }

            if(quantumPointer->BurstTime != 0)
            {
                if(quantumPointer->BurstTime < timeQuantum)
                {
                    currentTime = currentTime + quantumPointer->BurstTime;
                    printf(" %d ",currentTime);
                }

                if(quantumPointer->BurstTime > timeQuantum)
                {
                    currentTime = currentTime + timeQuantum;
                    printf(" %d ",currentTime);
                }

                if(quantumPointer->BurstTime == timeQuantum)
                {
                    currentTime = currentTime + timeQuantum;
                    printf(" %d ",currentTime);
                }

                quantumPointer->BurstTime = quantumPointer->BurstTime - timeQuantum;
            }

            if(quantumPointer->BurstTime <= 0)
            {
                quantumPointer->BurstTime = 0;
                numberOfProcessesWithBurstTimeZero++;
            }

            quantumPointer = quantumPointer->next;
        }



        if(numberOfProcessesWithBurstTimeZero == n || currentTime == totalBurstTime)
        {
            break;
        }

    }
}
