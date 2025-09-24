#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
const int EXIT = 0;
const int INVALID = -1;
const int CPU = 1;
const int PID = 5;
const int RACE = 2;
const int BANKER = 3;
const int PROCESS = 5;
const int RESOURCE = 3;
const int TRUE = 1;
const int FALSE = 0;
const int MEMORY = 4;
const int FIRST = 0;
const int BEST = 1;
const int WORST = 2;
const int NEXT = 3;
const int PAGE = 5;
const int FIFO = 0;
const int LRU = 1;
const int FRAMES = 4;
const int DISK = 6;
const int FCFS = 0;
const int SSTF = 1;
const int REQUEST = 8;


void memoryManagment();
void displayProcess();
void firstFit();
void worstFit();
void bestFit();
void nextFit();

void cpuScheduling(void);
void displaySchedule();
void raceCondition();
void bankerAlgorithm();
void systemState();
void *threadFuncOne();
void *threadFuncTwo();
int displayMenu();
void fcfs();
void sjf();

void pageReplacement();
void lru();
int findLRU();
void fifo();
void displayPages();

void diskScheduling();
void diskFcfs();
void diskSstf();

int wt[5];
int resource = 5;


int displayMenu(){
    int choice = INVALID;
    while(choice == INVALID){
      printf("Choose an option:\n");
      printf("6. Disk Scheduling\n");
      printf("5. Page Replacement\n");
      printf("4. Memory Management\n");
      printf("3. Banker's Algorithm\n");
      printf("2. Race Condition\n");
      printf("1. CPU Scheduling\n");
      printf("0. Exit\n");
      scanf("%d", &choice);
      if (choice == CPU){
        cpuScheduling();
      }
      if (choice == EXIT){
        exit(0);
      }
      if (choice == RACE){
        raceCondition();
      }
      if (choice == BANKER){
        bankerAlgorithm();
      }
      if (choice == 4){
        memoryManagment();
      }
      if (choice == PAGE){
        pageReplacement();
      }
      if (choice == DISK){
        diskScheduling();
      }
      else{
        choice = INVALID;
      }
    }
    return choice;
}

void diskScheduling(){
  int requests[] = {146, 89, 24,
70, 102, 13, 51, 134};
  int head = 50;
  int algorithm = 0;
  for (algorithm =0; algorithm < 2; algorithm++){
    if (algorithm == FCFS){
      diskFcfs(requests, head);
    }
    if (algorithm == SSTF){
      diskSstf(requests,head);
    }
  }
  
}

void diskFcfs(int requests[], int head){
  int seek = 0;
  int track = 0;
  int distance = 0;
  int start = head;
  printf("%d ", head);
  for (int i = 0; i < 8; i++){
    printf("---> %d ", requests[i]);
    track = requests[i];
    distance = abs(head - track);
    seek += distance;
    head = track;
    
  }
 
  printf("\nTotal Seek Time: %d\n\n", seek);
}

void diskSstf(int requests[], int head){
  int sequence[8];
  int distance[8];
  int seek = 0;
  int start = head;
  int minVal = 0;
  int minValIdx = 0;
  int seqIdx = 0;

  printf(" %d ", head);

  for (int i = 0; i < 8; i++){
    for (int j = 0; j < 8; j++){
      distance[j] = abs(head - requests[j]);
    }
    minVal = distance[0];
    minValIdx = 0;
    for (int k = 0; k < 8; k++){
      if (minVal > distance[k]){
        minVal = distance[k];
        minValIdx = k;
      }
    }
    sequence[seqIdx] = requests[minValIdx];
    seqIdx++;
    
    head = requests[minValIdx];
    requests[minValIdx] = 999;
    
    seek += abs(start - sequence[seqIdx - 1]);

    start = sequence[seqIdx - 1];

    printf("---> %d ", sequence[seqIdx - 1]);
    
  }

  printf("\nTotal Seek Time: %d\n\n", seek);
}





void pageReplacement(){
  int algorithm = 0;
  for (algorithm =0; algorithm < 2; algorithm++){
    if (algorithm == FIFO){
      fifo();
    }
    if (algorithm == LRU){
      lru();
    }
  }
  
}

void fifo(){
  printf("\n\n* * * * *     FIFO     * * * * *\n");
  int pageRequests[] = {2,3,8,4,5,6,5,7,1,8,3,1,4,2,6};
  int pageFaults = 0;
  int allocation[FRAMES];
  int present;
  int pages = sizeof(pageRequests)/sizeof(pageRequests[0]);
  memset(allocation, -1, sizeof(allocation));
  for (int i = 0; i < pages; i++){
    present = 0;
    for (int j = 0; j < FRAMES; j++){
      if (pageRequests[i] == allocation[j]){
        present++;
        pageFaults--;
      }
      
    }
    pageFaults++;
    if (pageFaults <= FRAMES && present == 0){
      allocation[i] = pageRequests[i];
      
    }
    else if (present == 0){
      allocation[(pageFaults - 1) % FRAMES] = pageRequests[i];
    }
    displayPages(pageRequests[i], allocation);
    
  }
  printf("\n\n Page Faults: %d\n", pageFaults);
}
void lru(){
  printf("\n\n* * * * *     LRU     * * * * *\n");
  int pageRequests[] = {2,3,8,4,5,6,5,7,1,8,3,1,4,2,6};
  int pageFaults = 0;
  int allocation[FRAMES];
  int pages = sizeof(pageRequests)/sizeof(pageRequests[0]);
  int counter = 0;
  int time[10];
  int flag1 = 0;
  int flag2 = 0;
  int position = 0;
  memset(allocation, -1, sizeof(allocation));
  for (int i = 0; i < pages; i++){
    flag1 = 0;
    flag2 = 0;
    for (int j = 0; j < FRAMES; j++){
      if (pageRequests[i] == allocation[j]){
        counter++;
        time[j] = counter;
        flag1 = 1;
        flag2 = 1;
        break;
      }
    }
      if (flag1 == 0){
        for (int k = 0; k < FRAMES; k++){
          if (allocation[k] == -1){
            counter++;
            pageFaults++;
            allocation[k] = pageRequests[i];
            time[k] = counter;
            flag2 = 1;
            break;
          }
        }
      }
      if (flag2 == 0){
        position = findLRU(time);
        counter++;
        pageFaults++;
        allocation[position] = pageRequests[i];
        time[position] = counter;
      
        
      }
      
    displayPages(pageRequests[i], allocation);
      }
  
    printf("\n\n Page Faults: %d\n", pageFaults);
    }

  
  
int findLRU(int time[]){
  int position = 0;
  int minimum = time[0];
  for (int i = 0; i < FRAMES; i++){
    if (time[i] < minimum){
      minimum = time[i];
      position = i;
    }
  }
  
  return position;
  
}

void displayPages(int page, int allocation[]){
  printf("\nPage: %d     ", page);
  for (int i = 0; i < FRAMES; i++){
    if (allocation[i] == -1){
      printf("-    ");
    }
    else{
      printf("%d    ", allocation[i]);
    }
    
    
  }
}

  

void memoryManagment(){


  for (int i = 1; i <=4 ; i++){
    int blockSize[] = {70,20,45,65,40,80};
    int processSize[] = {15,35,25,45,60,20};
    int blocks = sizeof(blockSize) / sizeof(blockSize[0]);
    int processes = sizeof(processSize) / sizeof(processSize[0]);
    switch(i){
      case 1:
      firstFit(blockSize, blocks, processSize, processes);
      break;

      case 2:
      bestFit(blockSize, blocks, processSize, processes);
      break;

      case 3:
      worstFit(blockSize, blocks, processSize, processes);
      break;

      case 4:
      nextFit(blockSize, blocks, processSize, processes);
      break;
      default:
      break;
    }
    
  }
  
}

void nextFit(int blockSize[], int blocks, int processSize[], int processes){
  int allocation[processes];
  int id = 0;
  memset(allocation, INVALID, sizeof(allocation));
  for (int i = 0; i < processes; i++){
    while (id < blocks){
      if (blockSize[id] >= processSize[i]){
        allocation[i] = id;
        blockSize[id] -= processSize[i];
        break;
      }
       id = (id + 1) % blocks;
    }
  }
 
  displayProcess(allocation, processes, processSize);
 
}
void firstFit(int blockSize[], int blocks, int processSize[], int processes){
  int allocation[processes];
  memset(allocation, INVALID, sizeof(allocation));
  for (int i = 0; i < processes; i++){
    for (int j = 0; j < blocks; j++){
      if (blockSize[j] >= processSize[i]){
        allocation[i] = j;
        blockSize[j] -= processSize[i];
        break;
      }
    }
  }
  displayProcess(allocation, processes, processSize);
}

void bestFit(int blockSize[], int blocks, int processSize[], int processes){
  int allocation[processes];
  memset(allocation, INVALID, sizeof(allocation));
  for (int i = 0; i < processes; i++){
    int bestIdx = INVALID;
    for (int j = 0; j < blocks; j++){
      if (blockSize[j] >= processSize[i]){
        if (bestIdx == INVALID){
          bestIdx = j;
        }
        else if(blockSize[bestIdx] >= blockSize[j]){
          bestIdx = j;
        }
      }
    }
    if (bestIdx != INVALID){
      allocation[i] = bestIdx;
      blockSize[bestIdx] -= processSize[i];
    }
  }
  displayProcess(allocation, processes, processSize);
  
}

void worstFit(int blockSize[], int blocks, int processSize[], int processes){
  int allocation[processes];
  memset(allocation, INVALID, sizeof(allocation));
  for (int i = 0; i < processes; i++){
    int wstIdx = INVALID;
    for (int j = 0; j < blocks; j++){
      if (blockSize[j] >= processSize[i]){
        if (wstIdx == INVALID){
          wstIdx = j;
        }
        else if(blockSize[wstIdx] < blockSize[j]){
          wstIdx = j;
        }
      }
    }
    if (wstIdx != INVALID){
      allocation[i] = wstIdx;
      blockSize[wstIdx] -= processSize[i];
    }
  }
  displayProcess(allocation, processes, processSize);
}

void displayProcess(int allocation[], int processes, int processSize[]) {
    printf("Process No.\tProcess Size\tBlock No.\n");
    for (int i = 0; i < processes; i++) {
        printf("%d\t\t%d\t\t", i+1, processSize[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1); 
        else
            printf("Not Allocated\n");
    }
}


void bankerAlgorithm(void){
  int allocation[5][3] = {
      {0, 0, 2},
      {3, 0, 2},
      {0, 1, 0},
      {2, 1, 1},
      {2, 0, 0}
  };
  int maxDemand[5][3] ={
  {4,3,3},
  {9,0,2},
  {7,5,3},
  {2,2,2},
  {3,2,2}  
  };
  int available[3] = {2,4,6};
  int need[5][3];
  int feasible[5];
  int safe[5];
  int safeIdx = 0;
  for (int p = 0; p < 5; p++){
    feasible[p] = 0;
  }
  
  for (int p = 0; p < 5; p++){
      for (int r = 0; r < 3; r++){
          need[p][r] = maxDemand[p][r] - allocation[p][r];
      }
  }
  
  for (int i = 0; i < 5; i++){
     for (int p = 0; p < 5; p++){
       
          if (feasible[p] == 0){ 
            int isUnsafe = 0; 
            for (int r = 0; r < 3; r++){
              
              if (need[p][r] > available[r]){
                isUnsafe = 1; 
                break;
                }
              }
              if (isUnsafe == 0){
                  safe[safeIdx++] = p; 
                  for (int r = 0; r < 3; r++) {
                      available[r] += allocation[p][r];
                  }
                  feasible[p] = 1;
              }
          }
      }
  }
  int allSafe = 1;
  for (int i = 0; i < PROCESS; i++) {
      if (feasible[i] == 0) {
          allSafe = 0;
          break;
      }
  }
  if (allSafe) {
      printf("Safe sequence:");
          for (int i = 0; i < 5; i++) {
              printf(" P%d", safe[i]);
              if (i < 5 - 1) {
                  printf(" ->");
              }
          }
          printf("\n");
      } 
  else {
          printf("Unsafe state detected.\n");
  }

  systemState(feasible, safe);
 

  
}
void systemState(int feasible[], int safe[]){
    int isSafe=1;
       for(int i=0;i<5;i++){
          if(feasible[i] ==0){
            isSafe=0;
            printf("This system is not safe\n");
            break;
          }
        }
        if(isSafe){
          for (int j = 0; j < 5; j++){
            printf("P%d", safe[j]);
          }
          printf("\n");
        }
}

void raceCondition(void){
  pthread_t thread1;
  pthread_t thread2;
  pthread_create(&thread1, NULL, threadFuncOne, NULL);
  pthread_create(&thread2, NULL, threadFuncTwo, NULL);
  pthread_join(thread1, NULL );
  pthread_join(thread2, NULL);
  printf("Final value of shared resource: %d\n", resource);
}
void *threadFuncOne(void *arg){
  int threadId = 1;
  int fOne = resource;
  printf("Thread 1 reads the resource as %d\n", fOne);
  fOne++;
  printf("Local Update by Thread 1: %d\n", fOne);
  sleep(1);
  resource = fOne;
  printf("Value of shared resource updated by Thread 1 is: %d\n", resource);
  
}
void *threadFuncTwo(void *arg){
  int threadId = 2;
  int fTwo = resource;
  printf("Thread 2 reads the resource as %d\n", fTwo);
  fTwo--;
  printf("Local Update by Thread 2: %d\n", fTwo);
  sleep(1);
  resource = fTwo;
  printf("Value of shared resource updated by Thread 2 is: %d\n", resource);

}

void cpuScheduling(void){

  int process[5] = {1,2,3,4,5};
  int arrvTime[5] ={0,2,4,6,7};
  int burstTime[5] = {8,5,10,2,3};

  fcfs(process, arrvTime, burstTime);
  sjf(process, arrvTime, burstTime);
  
  
  
  
}

void fcfs(int process[5], int arrvTime[5], int burstTime[5]){

  int tat[PID];
  wt[0] = 0;
  for (int i = 1; i < PID; i++){
    wt[i] = burstTime[i-1] + wt[i-1];
  }
  for (int i = 0; i < PID; i++){
    tat[i] = burstTime[i] + wt[i];
  }
  displaySchedule(process, arrvTime, burstTime, tat, wt);
  
  
  
  
}
void sjf(int process[5], int arrvTime[5], int burstTime[5]){
  int tat[PID];
  int idx = 0;
  int temp = 0;
  int wt[5];
  wt[0] = 0;
  for (int i = 0; i < PID; i++){
    idx = i;
    for (int j = i+1; j < PID; j++){
      if (burstTime[j] < burstTime[idx]){
        idx = j;
        
      }   
    }

    temp = burstTime[i];
    burstTime[i] = burstTime[idx];
    burstTime[idx] = temp;

    temp = process[i];
    process[i] = process[idx];
    process[idx] = temp;

    temp = arrvTime[i];
    arrvTime[i] = arrvTime[idx];
    arrvTime[idx] = temp;
    
  }
  for (int i = 1; i < PID; i++){
    wt[i] = burstTime[i-1] + wt[i-1];
    
  }
  for (int i = 0; i < PID; i++){
    tat[i] = burstTime[i] + wt[i];
  }

   displaySchedule(process, arrvTime, burstTime, tat, wt);
  
  
  
  
}
void displaySchedule(int process[5], int arrvTime[5], int burstTime[5], int tat[5], int wt[5]){
  int processID;
  int at;
  int bt;
  int wait;
  int ta;
  int totWt = 0;
  int totTat = 0;
  float avgWt;
  float avgTat;

  for (int i = 0; i < PID; i++){
    totWt = totWt + wt[i];
    totTat = totTat + tat[i];
    printf("Process ID: %d\n", process[i]);
    printf("Arrival Time: %d\n", arrvTime[i]);
    printf("Burst Time: %d\n", burstTime[i]);
    printf("Waiting time: %d\n", wt[i] );
    printf("Turn Around Time: %d\n\n", tat[i] );
    
  }
  avgWt = (totWt/PID);
  printf("Average Wait Time: %.2f\n", avgWt);
  avgTat = (totTat/PID);
  printf("Average Turn Around Time: %.2f\n\n\n\n", avgTat);


  
  
}


int main() {
  int choice = -1;
  while(choice != 0){
    choice = displayMenu();
    /*if (choice == 1){
      cpuScheduling();
    }
    if (choice == 2){
      raceCondition();
    }
    if (choice == 3){
      bankerAlgorithm();
    }
    if (choice == 4){
      memoryManagment();
    }*/
    if (choice == 0){
      exit(0);
    }
  }

  return 0;
}

