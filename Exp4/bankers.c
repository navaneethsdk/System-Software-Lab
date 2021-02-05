#include <stdio.h>
#include <stdlib.h>

void findSafeSeq(FILE*fp,int Max[10][10],int need[10][10],int alloc[10][10],int avail[],int completed[],int safeSequence[],int p,int r){
    int i, j, process=0, count, temp;
    count = 0;
    do
    {
        // printf("\n Max matrix:\tAllocation matrix:\n");
        // for(i = 0; i < p; i++)
        // {
        //     for( j = 0; j < r; j++)
        //         printf("%d  ", Max[i][j]);
        //     printf("\t\t");
        //     for( j = 0; j < r; j++)
        //         printf("%d  ", alloc[i][j]);
        //     printf("\n");
        // }
        if (process == p-1)
        {
            temp = 0;
        }else{
            temp = process;
        }
        
        process = -1;

        for(i = temp; i < p; i++)
        {
            if(completed[i] == 0)//if not completed
            {
                process = i ;
                for(j = 0; j < r; j++)
                {
                    if(avail[j] < need[i][j])
                    {
                        process = -1;
                        break;
                    }
                }
            }
            if(process != -1)
                break;
        }

        if(process != -1)
        {
            safeSequence[count] = process;
            count++;
            for(j = 0; j < r; j++)
            {
                avail[j] += alloc[process][j];
                alloc[process][j] = 0;
                Max[process][j] = 0;
                completed[process] = 1;
            }
        }
    }while(count != p && process != -1);

    if(count == p)
    {
        printf("\nThe system is in a safe state!!\n");
        fprintf(fp,"\nThe system is in a safe state!!\n");
        printf("Safe Sequence : < ");
        fprintf(fp,"Safe Sequence : < ");
        for( i = 0; i < p; i++)
                {printf("P%d  ", safeSequence[i]);
                fprintf(fp,"P%d  ", safeSequence[i]);}
        printf(">\n");
        fprintf(fp,">\n");
    }
    else
        {printf("\nThe system is in an unsafe state\n");
        fprintf(fp,"\nThe system is in an unsafe state\n");}
}


int main()
{
    int Max[10][10], need[10][10], alloc[10][10], avail[10], completed[10], safeSequence[10];
    int tMax[10][10], tneed[10][10], talloc[10][10], tavail[10], tcompleted[10], tsafeSequence[10];
    int p, r, i, j, rflag=0;
    FILE *fp,*fpo;
    fp = fopen ("input.txt", "w+");
    fpo = fopen ("output.txt", "w+");

    // int need[10][10], completed[10], safeSequence[10];
    // int Max[][10] = {{7,5,3},{3,2,2},{9,0,2},{2,2,2},{4,3,3}};
    // int alloc[][10] = {{0,1,0},{2,0,0},{3,0,2},{2,1,1},{0,0,2}};
    // int avail[] = {3,3,2};
    int reqP,req[10] ;
    
    printf("Enter the no of processes : ");
    fprintf(fp,"Enter the no of processes : ");
    scanf("%d", &p);
    fprintf(fp,"%d",p);

    for(i = 0; i< p; i++)
        completed[i] = 0;

    printf("\nEnter the no of resources : ");
    fprintf(fp,"\nEnter the no of resources : ");
    scanf("%d", &r);
    fprintf(fp,"%d",p);


    printf("\nEnter the Max Matrix for each process : ");
    fprintf(fp,"\nEnter the Max Matrix for each process : ");
    for(i = 0; i < p; i++)
    {
        printf("\nFor process %d : ", i + 1);
        fprintf(fp,"\nFor process %d : ", i + 1);
        for(j = 0; j < r; j++)
            {scanf("%d", &Max[i][j]);
            fprintf(fp,"%d",Max[i][j]);}
    }

    printf("\n\nEnter the allocation for each process : ");
    fprintf(fp,"\n\nEnter the allocation for each process : ");
    for(i = 0; i < p; i++)
    {
        printf("\nFor process %d : ",i + 1);
        fprintf(fp,"\nFor process %d : ",i + 1);
        for(j = 0; j < r; j++)
            {scanf("%d", &alloc[i][j]);	
            fprintf(fp,"%d",alloc[i][j]);}

    }

    printf("\nEnter the Available Resources : ");
    fprintf(fp,"\nEnter the Available Resources : ");
    for(i = 0; i < r; i++)
        {scanf("%d", &avail[i]);	
        fprintf(fp,"%d",avail[i]);}

    for(i = 0; i < p; i++)
        for(j = 0; j < r; j++){
            if (i==reqP)
            {
                need[i][j] = Max[i][j] - alloc[i][j] - req[j];
            }else{
                need[i][j] = Max[i][j] - alloc[i][j];
            }
            
        }
    int choice,ch;
    do
    {
        printf("\n------Banker's Algorithm------");
        fprintf(fp,"\n------Banker's Algorithm------");
        printf("\n1.Check for snapshot\n");
        fprintf(fp,"\n1.Check for snapshot\n");
        printf("2.Check for a request\n");
        fprintf(fp,"2.Check for a request\n");
        printf("Enter the choice\n");
        fprintf(fp,"Enter the choice\n");
        scanf("%d",&choice);
        fprintf(fp,"%d\n",choice);
        switch (choice)
        {
        case 1:

            for ( i = 0; i < p; i++)
            {
                for ( j = 0; j < r; j++)
                {
                    tneed[i][j] = need[i][j];
                    tMax[i][j] = Max[i][j];
                    talloc[i][j] = alloc[i][j];
                    tavail[j] = avail[j];
                }
                
            }
            for ( i = 0; i < p; i++)
            {
                tcompleted[i] = completed[i];
                tsafeSequence[i] = safeSequence[i];
            }
            
            for(i = 0; i < p; i++)
                for(j = 0; j < r; j++){
                    tneed[i][j] = Max[i][j] - alloc[i][j];
                }

            printf("\nNeed Matrix\n");
            for(i = 0; i < p; i++){
                for(j = 0; j < r; j++){
                    printf("%d\t",tneed[i][j]);
                    fprintf(fpo,"%d\t",tneed[i][j]);
                    } 
                printf("\n");     
                fprintf(fpo,"\n");     
            } 
            findSafeSeq( fpo,tMax, tneed, talloc, tavail, tcompleted, tsafeSequence, p, r);
                
            break;
        case 2:
            

            for ( i = 0; i < p; i++)
            {
                for ( j = 0; j < r; j++)
                {
                    tneed[i][j] = need[i][j];
                    tMax[i][j] = Max[i][j];
                    talloc[i][j] = alloc[i][j];
                    tavail[j] = avail[j];
                }
                
            }
            for ( i = 0; i < p; i++)
            {
                tcompleted[i] = completed[i];
                tsafeSequence[i] = safeSequence[i];
            }
            

            printf("Enter the process for request: ");
            fprintf(fp,"Enter the process for request: ");
            scanf("%d",&reqP);
            fprintf(fp,"%d",reqP);
            printf("Enter the request: ");
            fprintf(fp,"Enter the request: ");
            for ( i = 0; i < r; i++)
            {
                scanf("%d",&req[i]);
                fprintf(fp,"%d",req[i]);
            }

            for ( i = 0; i < r ; i++)
            {
                if (req[i]>tneed[reqP][i])
                {
                    rflag = 1;
                }
                if (req[i]>tavail[i])
                {
                    rflag = 1;
                }
            }
            
            if (rflag == 0){
                
            for(i = 0; i < p; i++)
                for(j = 0; j < r; j++){
                    if (i==reqP)
                    {
                        tneed[i][j] = Max[i][j] - alloc[i][j] - req[j];
                    }else{
                        tneed[i][j] = Max[i][j] - alloc[i][j];
                    }
                    
                }
            for(i = 0; i < p; i++)
                for(j = 0; j < r; j++){
                    if (i==reqP)
                    {
                        talloc[i][j] +=  req[j];
                    }
                    
                }
            for ( i = 0; i < r; i++)
            {
                tavail[i]-=req[i];
            }

            printf("\nNeed Matrix\n");
            fprintf(fpo,"\nNeed Matrix\n");
            for(i = 0; i < p; i++){
                for(j = 0; j < r; j++){
                    printf("%d\t",tneed[i][j]);
                    fprintf(fpo,"%d\t",tneed[i][j]);
                    } 
                printf("\n");     
                fprintf(fpo,"\n");     
            } 
            findSafeSeq(fpo, tMax, tneed, talloc, tavail, tcompleted, tsafeSequence, p, r);
            }else{
                printf("\nOpps request cannot be processed\n");
            }
            rflag =0;
            break;
        default:
            break;
        }

        printf("Do you want to continue? :");
        scanf("%d",&ch);
    } while (ch == 1);
    
    fclose(fp);
    fclose(fpo);
    
            
}
