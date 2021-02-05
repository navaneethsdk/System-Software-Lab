#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 7
#define BIN_LEN 7
#define MAX_BIN_SIZE 28

struct node
{
    int data;
    char key[4];
    struct node *next;
};

struct node *chain[MAX];
/**To Calculate the exponent of a number
 */
int power(int base, int exponent){
    int result=1;
    for(exponent; exponent>0; exponent--){
        result = result * base;
    }
    return result;
}

/** To convert the string into a binaary number
 * and consequently obtain the equivalent number for 
 * hashing
 */
int strToBin(char* str){
    int k,i,value=0,index=0;
    int bin[MAX_BIN_SIZE];
    for (i = 0; i < MAX_BIN_SIZE; i++){ bin[i]=0;}
    for ( k = 0; k < strlen(str); k++)
    {
        int num = (int)*(str+k);
        i=0;
        while(num!=0){
            bin[(BIN_LEN*(k+1))-1-i]=num%2;
            num/=2;
            i++;
        }
        for (i = 0; i < MAX_BIN_SIZE; i++)
        {
            printf("%d ",bin[i]);
        }
        printf("\n");
        
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
    return (binkey/2) % MAX;
}

void init()
{
    int i;
    for(i = 0; i < MAX; i++)
        chain[i] = NULL;
}

void insert(char* key,int data)
{
    //create a newnode with value
    struct node *newNode = malloc(sizeof(struct node));
    newNode->data = data;
    strcpy(newNode->key,key);
    newNode->next = NULL;

    //calculate hash key
    int hashIndex = hashCode(key);

    //check if chain[hashIndex] is empty
    if(chain[hashIndex] == NULL)
        chain[hashIndex] = newNode;
    //collision
    else
    {
        //add the node at the end of chain[hashIndex].
        struct node *temp = chain[hashIndex];
        while(temp->next)
        {
            temp = temp->next;
        }

        temp->next = newNode;
    }
}

struct node *search(char* key) {
   //get the hash 
    int hashIndex = hashCode(key);  
	int i;
    struct node *temp = NULL;
	for(i = 0; i < MAX; i++){
        if(i==hashIndex){
            temp = chain[i];
            while(temp != NULL){
                if(strcmp(temp->key,key)==0)
                    return temp;
                temp = temp->next;
            }
        }
    }

    return NULL;        
}

void print()
{
    int i;

    for(i = 0; i < MAX; i++)
    {
        struct node *temp = chain[i];
        printf("chain[%d]-->",i);
        while(temp)
        {
            printf("%d -->",temp->data);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

int main()
{
    struct node* item = NULL;
    char key[4];
    int ch,choice,addr;
    do
    {
        printf("-----SYMTABLE HASH------");
        printf("\n1.Insert");
        printf("\n2.Search");
        printf("\n3.Display");
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
                printf("[info] Element %d found at index %d (%d mod %d)\n", item->data,hashCode(key),strToBin(key),MAX);
            } else {
                printf("[info] Element not found\n");
            }
            break;
        case 3:
            printf("\n------DISPLAY------\n");
            print();
            break;
        default:
            break;
        }
        printf("\nDo you wish to continue(0/1)?");
        scanf("%d",&ch);
    } while (ch==1);

}