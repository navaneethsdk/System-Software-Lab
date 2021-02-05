
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 20
#define BIN_LEN 7
#define MAX_BIN_SIZE 28

struct DataItem {
   int data;   
   char key[4];
};

struct DataItem* hashArray[SIZE]; 
struct DataItem* dummyItem;
struct DataItem* item;

int power(int base, int exponent){
    int result=1;
    for(exponent; exponent>0; exponent--){
        result = result * base;
    }
    return result;
}

int strToBin(char* a){
    int k,i,value=0,index=0;
    int bin[MAX_BIN_SIZE];
    for (i = 0; i < MAX_BIN_SIZE; i++){ bin[i]=0;}
    for ( k = 0; k < strlen(a); k++)
    {
        int num = (int)*(a+k);
        i=0;
        while(num!=0){
            bin[(BIN_LEN*(k+1))-1-i]=num%2;
            num/=2;
            i++;
        }
        
    } 

    for ( i = BIN_LEN*k-1; i >= 0; i--)
    {
        if (bin[i]==1)
        {
            value = value + power(2,index);
        }
        index++;
    }  
    return value;
}

int hashCode(char* key) {
    int binkey = 0;
    binkey = strToBin(key);
    return binkey % SIZE;
}

struct DataItem *search(char* key) {
   //get the hash 
   int hashIndex = hashCode(key);  
	
   //move in array until an empty 
   while(hashArray[hashIndex] != NULL) {
	
      if(strcmp(hashArray[hashIndex]->key,key)==0)
         return hashArray[hashIndex]; 
			
      //go to next cell
      ++hashIndex;
		
      //wrap around the table
      hashIndex %= SIZE;
   }        
	
   return NULL;        
}

void insert(char* key,int data) {

   struct DataItem *item = (struct DataItem*) malloc(sizeof(struct DataItem));
   item->data = data;  
   strcpy(item->key,key);

   //get the hash 
   int hashIndex = hashCode(key);

   //move in array until an empty or deleted cell
   while(hashArray[hashIndex] != NULL) {
      //go to next cell
      ++hashIndex;
		
      //wrap around the table
      hashIndex %= SIZE;
   }
	
   hashArray[hashIndex] = item;
}


int main(){
    char key[4];
    int ch,choice,addr;
    do
    {
        printf("-----SYMTABLE HASH------");
        printf("\n1.Insert");
        printf("\n2.Search");
        printf("\nEnter the operation to be performed : ");
        scanf("%d",&choice);
        switch (choice)
        {
        case 1:
            printf("\n------INSERT------\n");
            printf("\nEnter the key(label) : ");
            scanf("%s",key);
            printf("Enter the address : ");
            scanf("%d",&addr);
            insert(key,addr);
            break;
        case 2:
            printf("\n------SEARCH------\n");
            printf("Enter the key(label) : ");
            scanf("%s",key);
            item = search(key);
            if(item != NULL) {
                printf("[info] Element %d found at index %d (%d mod %d)\n", item->data,hashCode(key),strToBin(key),SIZE);
            } else {
                printf("[info] Element not found\n");
            }
            break;
        default:
            break;
        }
        printf("\nDo you wish to continue(0/1)?");
        scanf("%d",&ch);
    } while (ch==1);

}