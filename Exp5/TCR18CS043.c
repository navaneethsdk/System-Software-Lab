#include<stdio.h>
#include <stdlib.h>

void FCFS(FILE *fp, int queue[],int n){
    int j,seek=0,diff;
    for(j=0;j<=n-1;j++)
    {
                diff=abs(queue[j+1]-queue[j]);
                seek+=diff;
                // printf("Disk head moves from %d to %d with seek %d\n",queue[j],queue[j+1],diff);
    }
    printf("Total seek time is %d\n",seek);
    fprintf(fp,"Total seek time is %d\n",seek);
}

void scan_algorithm(FILE *fp,int left[], int right[], int count, int limit, int disk_head, int max)
{
      int arr[20],seek=0,diff;
      arr[0] = disk_head;
    //   left scan
    //   int x = count - 1, y = count + 2, c = 0, d = 1, j;
    //   while(x > -1)
    //   { 
    //         arr[d++] = left[x--];
    //   }
    //   arr[d] = 0;
    //   while(y < limit + 2)
    //   {
    //         arr[y++] = right[c++];
    //   }

    //  right scan 
    int x = count - 1, y = count + 2, c = 0, d = 1, j;
      while(y < limit + 2)
      {
            arr[d++] = right[c++];
            y++;
      }
      arr[d] = max;
      d++;
      while(x > -1)
      { 
            arr[d++] = left[x--];
      }
    
      
    //   printf("\nScanning Order:\n");
    //   for(j = 0; j < limit + 2; j++)
    //   {
    //         printf("%d ", arr[j]);
    //   }
      for(j=0;j<=limit;j++)
        {
            diff=abs(arr[j+1]-arr[j]);
            seek+=diff;
            // printf("Disk head moves from %d to %d with seek %d\n",arr[j],arr[j+1],diff);
        }
    printf("Total seek time is %d\n",seek);
    fprintf(fp,"Total seek time is %d\n",seek);
      
}

void cscan_algorithm(FILE *fp,int left[], int right[], int count, int limit, int disk_head,int max)
{
      int arr[20],seek=0,diff;
      arr[0] = disk_head;
    //   left scan
    //   int x = count - 1, y = count + 2, c = 0, d = 1, j;
    //   while(x > -1)
    //   { 
    //         arr[d++] = left[x--];
    //   }
    //   arr[d] = 0;
    //   while(y < limit + 2)
    //   {
    //         arr[y++] = right[c++];
    //   }

    //  right scan 
    int x = 0, y = count + 2, c = 0, d = 1, j;
      while(y < limit + 2)
      {
            arr[d++] = right[c++];
            y++;
      }
      arr[d] = max;
      d++;
      arr[d] = 0;
      d++;
      while(x < count)
      { 
            arr[d++] = left[x++];
      }
    
      
    //   printf("\nScanning Order:\n");
    //   for(j = 0; j < limit + 3; j++)
    //   {
    //         printf("%d ", arr[j]);
    //   }
      for(j=0;j<=limit+1;j++)
        {
            diff=abs(arr[j+1]-arr[j]);
            seek+=diff;
            // printf("Disk head moves from %d to %d with seek %d\n",arr[j],arr[j+1],diff);
        }
    printf("Total seek time is %d\n",seek);
    fprintf(fp,"Total seek time is %d\n",seek);
      
}
 
void sorting(int elements[], int limit)
{
      int location, count, j, temp, small;
      for(count = 0; count < limit - 1; count++)
      {
            small = elements[count];
            location = count;
            for(j = count + 1; j < limit; j++)
            {
                  if(small > elements[j])
                  {
                        small = elements[j];
                        location = j;
                  }
            }
            temp = elements[location];
            elements[location] = elements[count];
            elements[count] = temp;
      }
}

void division(FILE *fp,int elements[], int limit, int disk_head, int scan,int max)
{
      int count = 0, p, q, m, x;
      int left[20], right[20];
      for(count = 0; count < limit; count++)
      {
            if(elements[count] > disk_head)
            {
                  break;
            }      
      }

      q = 0;
      p = 0;
      m = limit;
      while(q < count)
      {
            left[q] = elements[q];
            q++;
      }
      x = count;
      while(x < m)
      {
            right[p++] = elements[x++];
      }
      int i;
      if (scan == 1)
      {
          scan_algorithm(fp,left, right, count, limit, disk_head,max);
      }else{
          cscan_algorithm(fp,left, right, count, limit, disk_head,max);
      }
      
      
}
 

int main()
{
    FILE *fp,*fpo;
    fp = fopen ("input.txt", "w+");
    fpo = fopen ("output.txt", "w+");
    // int queue[] = {0,98,183,41,122,14,124,65,67},n,head,i,j,k,seek=0,max,diff,choice,elements[20];
    int queue[20],n,head,i,j,k,seek=0,max,diff,choice,elements[20];
    int ch;
    printf("Enter the max range of disk:");
    fprintf(fp,"Enter the max range of disk:");
    scanf("%d",&max);
    fprintf(fp,"%d",max);
    printf("Enter the size of queue request:");
    fprintf(fp,"\nEnter the size of queue request:");
    scanf("%d",&n);
    fprintf(fp,"%d",n);
    printf("Enter the queue of disk positions to be read: ");
    fprintf(fp,"\nEnter the queue of disk positions to be read: ");
    for(i=1;i<=n;i++){
        scanf("%d",&queue[i]);
        fprintf(fp,"%d ",queue[i]);
    }
    
    printf("Enter the initial head position:");
    fprintf(fp,"\nEnter the initial head position:");
    scanf("%d",&head);
    fprintf(fp,"%d",head);
    queue[0]=head;
    do
    {
        printf("------DISC SCHEDULING ALGORITHMS------\n");
        fprintf(fp,"\n\n------DISC SCHEDULING ALGORITHMS------\n");
        printf("1.FCFS\n");
        fprintf(fp,"1.FCFS\n");
        printf("2.SCAN\n");
        fprintf(fp,"2.SCAN\n");
        printf("3.C-SCAN\n");
        fprintf(fp,"3.C-SCAN\n");
        printf("Enter choice:");
        fprintf(fp,"Enter choice:");
        scanf("%d",&choice);
        fprintf(fp,"%d",choice);
        switch (choice)
        {
        case 1:
            FCFS(fpo,queue,n);
            break;
        case 2:
            for(i = 1; i <= n; i++)
            {
                elements[i-1] = queue[i];
            }
            sorting(elements, n);
            division(fpo,elements, n,head,1,max);
            break;
        case 3:
            for(i = 1; i <= n; i++)
            {
                elements[i-1] = queue[i];
            }
            sorting(elements, n);
            division(fpo,elements, n,head,0,max);
            break;
        default:
            break;
        }
        printf("\nDo you want to continue? :");
        scanf("%d",&ch);
    } while (ch ==1);
    
    

    
    return 0;
}