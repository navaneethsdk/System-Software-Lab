#include<stdio.h>
#include <stdlib.h>

void Seq(int Start[],int Length[],char Content[][5] ,int nof,int nob){
    FILE * fp;
    fp = fopen ("output.txt", "w+");
    int i,j,flag =0,count=0;
    fprintf(fp,"------Sequential File Allocation------\n\n");
    char* ptr = (char*)malloc(nob * sizeof(ptr));
    // char ptr[nob];
    for ( i = 0; i < nob; i++)
    {
        *(ptr + i) = '*';
    }

    
    int* Status = (int*)malloc(nof * sizeof(int));
    for ( i = 0; i < nof; i++)
    {
        *(Status + i) = -1;
    }
    for (i=0; i<nof; i++){
        flag = 0 ;
        if (Start[i]+Length[i]>nob){
            continue;
        }

        for ( j = Start[i]; j < Start[i]+Length[i]; j++)
        {
            if(*(ptr+j)!='*'){
                flag = 1;
            }
        }

        if(flag == 1 ){
            continue;
        }
        

        count = 0;
        for ( j = Start[i]; j < Start[i]+Length[i]; j++)
        {
            *(ptr+j) = Content[i][count++];
            *(Status+i) = 1;
        } 
    }

    printf("\nBlock\tContent\tStatus\n");
    fprintf(fp, "Block\tContent\tStatus\n");
    for (i = 0; i < nob; i++)
    {   
        if(*(ptr+i)!='*'){
            printf("%d\t%c\tOccupied\n",i+1,*(ptr + i));
            fprintf(fp, "%d\t%c\tOccupied\n",i+1,*(ptr + i));    
        }
        else{
            printf("%d\tNA\tFree\n",i+1);
            fprintf(fp, "%d\tNA\tFree\n",i+1);
            
        }
        
    }
    
    
    printf("\nPid\tStatus\n");
    fprintf(fp, "\nPid\tStatus\n");
    for ( i = 0; i < nof; i++)
    {
        if(*(Status + i)!=-1){
            printf("%d\t",Start[i]);
            printf("Allocated\n");
            fprintf(fp,"%d\t",Start[i]);
            fprintf(fp,"Allocated\n");
        }
        else{
            printf("%d\t",Start[i]);
            printf("Not Allocated\n");
            fprintf(fp,"%d\t",Start[i]);
            fprintf(fp,"Not Allocated\n");
        }
    }
    fclose(fp);
}



void LinLis(int CNode[],int NNode[],int Length[],char Content[][5] ,int nof,int nob,int non){
    FILE * fp;
    fp = fopen ("output.txt", "w+");
    int i,j,k=0,nodes[non+1],count=0;
    char temp[nob];
    fprintf(fp,"------Linked list File Allocation------\n\n");

    int* Status = (int*)malloc(nob * sizeof(int));
    for ( i = 0; i < nob; i++)
    {
        *(Status + i) = 0;
    }
    char* Tot = (char*)malloc(nob * sizeof(char));
    for ( i = 0; i < nob; i++)
    {
        *(Tot + i) = '*';
    }
    int* FileStatus = (int*)malloc(nof * sizeof(int));
    //assuming the nodes are given in connected order
    for ( i = 0; i < non; i++)
    {
        nodes[i] = CNode[i];
    }
    nodes[non] = NNode[non-1];

    printf("SA\tEA\n");
    fprintf(fp,"SA\tEA\n");
    for ( i = 0; i < nof; i++)
    {   
        if(count >= non ){
            *(FileStatus + i) = 0;
            printf("%d\t\n",nodes[count]);
            fprintf(fp,"%d\t\n",nodes[count]);
            continue;
        }
        j=0;
        printf("%d\t",nodes[count]);
        fprintf(fp,"%d\t",nodes[count]);
        while (j < Length[i])
        {   
            temp[k++] = Content[i][j];
            *(Tot + nodes[count]) = Content[i][j++];
            *(Status + nodes[count]) = 1;
            count ++;
            
        }
        printf("%d\n",nodes[count-1]);
        fprintf(fp,"%d\n",nodes[count-1]);

        *(FileStatus + i) = 1;
    }


    printf("\n");
    fprintf(fp,"\n");

    k=0;
    for ( i = 0; i < nof; i++)
    {   
        if (*(FileStatus + i))
        {
            printf("P%d: ",i+1);
            fprintf(fp,"P%d: ",i+1);
            for (j = k; j< Length[i] + k; j++)
            {
                printf("%c ",temp[j]);
                fprintf(fp,"%c ",temp[j]);
            }
            k = j;
            printf("\n");
            fprintf(fp,"\n");
        }
        
        
        
    }
    
    
    printf("\n");
    fprintf(fp,"\n");
    
    // for (i = 0; i < nob; i++)
    // {   
    //     if(*(Tot + i)!='*'){
    //         printf("%c ",*(Tot + i));    
    //     }
    //     else{
    //         printf("NA ");
    //     }
        
    // }
    // printf("\n");
    printf("Process\tStatus\n");
    fprintf(fp,"Process\tStatus\n");
    for (i = 0; i < nof; i++)
    {   
        printf("P%d\t",i+1);
        fprintf(fp,"P%d\t",i+1);
        if(*(FileStatus + i)){
            printf("Allocated \n");    
            fprintf(fp,"Allocated \n");    
        }
        else{
            printf("NA \n");
            fprintf(fp,"NA \n");
        }

        
    }
    // for (i = 0; i < nob; i++)
    // {   
    //     if(*(Status + i)){
    //         printf("%d ",*(Status + i));    
    //     }
    //     else{
    //         printf("NA ");
    //     }
        
    // }

    fclose(fp);
}



void Indexed(int Index[],int Length[],char Content[][5] ,int nof,int nob){
    FILE * fp;
    fp = fopen ("output.txt", "w+");
    int i,j,k,l=0,flag =0,count=1;    
    int temp[nob];
    fprintf(fp,"------Indexed File Allocation------\n\n");

    int* Status = (int*)malloc(nob * sizeof(int));
    for ( i = 0; i < nob; i++)
    {
        *(Status + i) = -1;
    }
    char* Tot = (char*)malloc(nob * sizeof(char));
    for ( i = 0; i < nob; i++)
    {
        *(Tot + i) = '*';
    }
    int* FileStatus = (int*)malloc(nof * sizeof(int));
    


    for ( i = 0; i < nof; i++)
    {   
        if (Index[i] <= count)
        {
            *(FileStatus + i) = 0;
            continue;
        }
        
        flag =0 ;
        *(Status+Index[i]) = 1;
        j=0;
        while (j<Length[i])
        {
            // 
            
            if (*(Status + count) == -1)
            {
                *(Tot + count) = Content[i][j++];
                temp[l++]=count;
                *(Status+count) = 1;
                count++;
            }
            else{
                for ( k = count+1; k < nob; k++)
                {
                    if(*(Status+k)==-1){
                        count = k;
                        *(Status+count) = 1;
                        *(Tot + count) = Content[i][j++];
                        temp[l++]=count;
                        flag=0;
                        break;
                    }
                    else{
                        flag=1;
                    }
                }
                
            }
            
        }
        if (flag == 1)
        {
            *(FileStatus + i) = 0;
        }else
        {
            *(FileStatus + i) = 1;
        }
        
    }

    printf("\nProcess\tStatus\n");
    fprintf(fp,"\nProcess\tStatus\n");
    for (i = 0; i < nof; i++)
    {   
        printf("P%d\t",i+1);
        fprintf(fp,"P%d\t",i+1);
        if(*(FileStatus + i)){
            printf("Allocated \n");    
            fprintf(fp,"Allocated \n");    
        }
        else{
            printf("NA \n");
            fprintf(fp,"NA \n");
        }

        
    }

    printf("\nProcess\tBlocks allocated with index\n");
    fprintf(fp,"\nProcess\tBlocks allocated with index\n");
    k=0;
    for ( i = 0; i < nof; i++)
    {   
        if (*(FileStatus + i))
        {
            printf("P%d:\t",i+1);
            fprintf(fp,"P%d:\t",i+1);
            for (j = k; j< Length[i] + k; j++)
            {
                printf("%d",temp[j]);
                fprintf(fp,"%d",temp[j]);
            }
            k = j;
            printf(" for index %d\n",Index[i]);
            fprintf(fp," for index %d\n",Index[i]);
        }
        
        
        
    }
    
    printf("\nIndex\tCharacter\n");
    fprintf(fp,"\nIndex\tCharacter\n");

    for (i = 0; i < nob; i++)
    {   
        if(*(Tot + i)!='*'){
            printf("%d\t%c\n",i,*(Tot + i));    
            fprintf(fp,"%d\t%c\n",i,*(Tot + i));    
        }
        else{
            printf("%d\tNA\n",i);
            fprintf(fp,"%d\tNA\n",i);
        }
        
    }
    
    // printf("\n");
    // for (i = 0; i < nob; i++)
    // {   
    //     if(*(Status + i)!=-1){
    //         printf("%d ",*(Status + i));    
    //     }
    //     else{
    //         printf("NA ");
    //     }
        
    // }
    
}


void read_ints (char* file_name,char* file_name_nnode,int Start[], int Length[], int Index[],char Content[30][5],int NNode[],int CNode[], int* nof,int* non)
{
    FILE* file = fopen (file_name, "r");
    int p = 0,q = 0,k = 0;
    int m=0;
    char l[5];
    int count = 0 ;
    if ( file == NULL ) 
    { 
        printf( "input.txt file failed to open." ) ; 
    } 
    else{
        fscanf (file, "%d %d %d %s", &p, &q, &k, l);    
        while (!feof (file))
        {   
            Start[count] = p;
            Length[count] = q;
            Index[count] = k;
            m=0;
            while(*(l+m)!='\0'){
                Content[count][m] = *(l+m);
                m++;
            }
            Content[count][m] = '\0';
            // printf ("%d %d %d %s\n", i,q,k,l);
            fscanf (file, "%d %d %d %s", &p, &q, &k, l); 
            count++;
        }
        
    }
    fclose (file);  
    *nof = count;     
    // -------------------------------------------------------------------------------
    count = 0;
    FILE* file2 = fopen (file_name_nnode, "r");
    if ( file2 == NULL ) 
    { 
        printf( "input2.txt file failed to open." ) ; 
    } 
    else{
        fscanf (file2, "%d %d", &p, &q);    
        while (!feof (file2))
        {   
            CNode[count] = p;
            NNode[count] = q;
            fscanf (file2, "%d %d", &p, &q); 
            count++;
        }
        CNode[count] = p;
        NNode[count] = q;

    }
    fclose (file2);  
    *non = ++count;

}


void main(){
    // int Start[50],Length[50],choice;
    // char Contents[50][50];
    int choice,nof=4,nob=10,non=6;
    // int Start[] = {1,2,7,9};
    // int Length[] = {3,1,2,3};
    // int CNode[] = {1,5,2,7,3,4};
    // int NNode[] = {5,2,7,3,4,6};
    // int Index[] = {7,8,3,4};
    // char Content[][5] = {"abc","x","yz","pqr"};
    int Start[4] ;
    int Length[4];
    int CNode[6];
    int NNode[6];
    int Index[4];
    char Content[4][5];

    printf("1.Sequential\n");
    printf("2.Linked List \n");
    printf("3.Indexed \n");
    printf("Enter your choice:");
    scanf("%d",&choice);
    printf("Enter the number of blocks:");
    scanf("%d",&nob);
 
    
    read_ints("input1.txt","input2.txt",Start,Length,Index,Content,NNode,CNode,&nof,&non);
    int i,j;
    

    switch (choice)
    {
    case 1:
        Seq(Start, Length, Content, nof, nob);
        break;
    case 2:
        LinLis(CNode,NNode,Length,Content,nof,nob,non);
        break;
    case 3:
        Indexed(Index, Length, Content, nof, nob);
        break;
    
    default:
        break;
    }   

    

}