#include<stdio.h>

void FCFS(int at[],int bt[],int wt[],int tat[],int n){
    int i,moving_sum=0;

    for(i=0;i<n;i++){
        moving_sum+=bt[i];
        wt[i] = moving_sum - bt[i] - at[i];
        tat[i] = moving_sum - at[i];
    }

}

void SJF(int at[],int bt[],int wt[],int tat[],int n){
    int i,moving_sum=0;
    int completed=0,time=0;
    int smallest = 0;
    int temp2[n+1];
    temp2[n] = 99999;
    for(i = 0; i < n; i++) {
      temp2[i] = bt[i];
    }
    while(completed!=n){
        smallest = n;
        for ( i = 0; i < n; i++)
        {
            if(at[i]<=time && bt[i]< temp2[smallest] && bt[i]>0){
                smallest = i;
            }   
        }
        moving_sum+=temp2[smallest];
        wt[smallest] = moving_sum - temp2[smallest] - at[smallest];
        tat[smallest] = moving_sum - at[smallest];
        time+=temp2[smallest];
        bt[smallest] = 0;
        completed +=1;
        
    }
}

void RoundRobin(int at[],int bt[],int wt[],int tat[],int n,int quantum){
    int completed=0,time=0,i,inuse;
    int temp[n],diff=0;
    for(i = 0; i < n; i++) {
      temp[i] = bt[i];
    }
    while (1) 
    { 
        completed = 1; 
        for (i = 0 ; i < n; i++) 
        { 
            if (temp[i] > 0) 
            { 
                completed = 0;
  
                if (temp[i] > quantum && at[i]<=time) 
                { 
                    time += quantum;  
                    temp[i] -= quantum; 
                } 

                else
                { 
                    time = time + temp[i]; 
                    wt[i] = time - bt[i] -at[i]; 
                    tat[i] = time - at[i];
                    temp[i] = 0; 
                } 
            } 
        } 
        if (completed == 1) 
          break; 
    } 
}

void Priority(int at[],int bt[],int pri[],int wt[],int tat[],int n){
    int i,moving_sum=0;
    int completed=0,time=0;
    int smallest = 0;
    int temp[n+1];
    for(i = 0; i < n; i++) {
      temp[i] = pri[i];
    }
    temp[n] = 99999;
    int temp2[n];
    for(i = 0; i < n; i++) {
      temp2[i] = bt[i];
    }
    
    // printf("%d",completed);
    while(completed!=n){
        smallest = n;
        for ( i = 0; i < n; i++)
        {
            if(at[i]<=time && pri[i]< temp[smallest] && bt[i]>0){
                smallest = i;
            }   
        }
        moving_sum+=temp2[smallest];
        wt[smallest] = moving_sum - temp2[smallest] - at[smallest];
        tat[smallest] = moving_sum - at[smallest];
        time+=temp2[smallest];
        bt[smallest] = 0;
        completed +=1;
        
    }
}

void read_ints (const char* file_name,int at[], int bt[], int pri[],int* n)
{
    FILE* file = fopen (file_name, "r");
    int i = 0,j = 0,k = 0;
    int count = 0 ;
    if ( file == NULL ) 
    { 
        printf( "input.txt file failed to open." ) ; 
    } 
    else{
        fscanf (file, "%d %d %d", &i, &j, &k);    
        while (!feof (file))
        {   
            at[count] = i;
            bt[count] = j;
            pri[count] = k;
            // printf ("%d %d %d\n", i,j,k);
            fscanf (file, "%d %d %d", &i, &j, &k); 
            count++;
        }
        at[count] = i;
        bt[count] = j;
        pri[count] = k;
    }
    fclose (file);  
    *n = ++count;      
}

void write_ints(const char* file_name,int wt[], int tat[],int n){
    FILE * fp;
    int i;
    fp = fopen (file_name, "w+");
    for ( i = 0; i < n; i++)
    {
        fprintf(fp, "%d\t%d\n", tat[i], wt[i]);
    }
    fclose(fp);
}

int main(){
    int choice,i;
    int at[50],bt[50],pri[50],wt[50],tat[50],n;
    read_ints("input.txt",at,bt,pri,&n);
    int quantum;
    printf("1.FCFS\n");
    printf("2.SJF(non preemptive)\n");
    printf("3.Round Robin(premptive)\n");
    printf("4.Priority\n");
    printf("Enter your choice:");
    scanf("%d",&choice);
    printf("Enter the quantum for Round robin CPU scheduling: ");
    scanf("%d",&quantum);
    

    switch (choice)
    {
    case 1:
        FCFS(at,bt,wt,tat,n);
        printf("------FCFS------\n");
        printf("\nTurnaround time  \tWaiting time  ");
        for ( i = 0; i < n; i++)
        {
            printf("\n%d\t\t\t%d",tat[i],wt[i]);
        }
        printf("\n");
        write_ints("output.txt",wt,tat,n);
        printf("Output has been written to output.txt\n");
        break;
    case 2:
        SJF(at,bt,wt,tat,n);
        printf("------SJF(non preemptive)------\n");
        printf("\nTurnaround time  \tWaiting time  ");
        for ( i = 0; i < n; i++)
        {
            printf("\n%d\t\t\t%d",tat[i],wt[i]);
        }
        printf("\n");
        write_ints("output.txt",wt,tat,n);
        printf("Output has been written to output.txt\n");

        break;
    case 3:
        RoundRobin(at,bt,wt,tat,n,quantum);
        printf("------Round Robin(premptive)------\n");
        printf("\nTurnaround time  \tWaiting time  ");
        for ( i = 0; i < n; i++)
        {
            printf("\n%d\t\t\t%d",tat[i],wt[i]);
        }
        printf("\n");
        write_ints("output.txt",wt,tat,n);
        printf("Output has been written to output.txt\n");


        break;
    
    case 4:
        
        Priority(at,bt,pri,wt,tat,n);
        printf("-------Priority-------\n");
        printf("\nTurnaround time  \tWaiting time  ");
        for ( i = 0; i < n; i++)
        {
            printf("\n%d\t\t\t%d",tat[i],wt[i]);
        }
        printf("\n");
        write_ints("output.txt",wt,tat,n);
        printf("Output has been written to output.txt\n");


        break;
    default:
        break;
    }
    return 0;
}