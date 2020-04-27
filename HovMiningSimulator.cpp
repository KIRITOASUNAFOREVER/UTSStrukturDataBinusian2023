#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct data{
	int caveIndex;
	int goldProduction;
	data *left,*right;
}*root=NULL;

data* push(data* node,int caveIndex,int goldProduction)
{
	if(node==NULL)
	{
		data* current=(data*)malloc(sizeof(struct data));
		current->caveIndex=caveIndex;
		current->goldProduction=goldProduction;
		current->left=current->right=NULL;
		
		printf("New cave index detected.\n");
        printf("Total gold production for Cave %d is %d",current->caveIndex,current->goldProduction);
        printf("\n\n\n");
        printf("Press any key to continue...");getchar();
		return current;
	}
	else if(node->caveIndex==caveIndex)
	{
	    data* current=(data*)malloc(sizeof(struct data));
	    current->goldProduction=goldProduction;
		printf("Cave index already exists.\n");
		node->goldProduction = node->goldProduction + current->goldProduction;
        printf("New total gold production for Cave %d is %d",node->caveIndex,node->goldProduction);
        printf("\n\n\n");
        printf("Press any key to continue...");getchar();
		return node;
	}
	else if(caveIndex < node->caveIndex)
	{
		node->left=push(node->left,caveIndex,goldProduction);
	}
	else if(caveIndex > node->caveIndex)
	{
		node->right = push(node->right,caveIndex,goldProduction);
	}
	return node;
}

int hanyaAngka(char CaveIndex[])
{
    bool penanda = true;
    int panjang = strlen(CaveIndex);
    for(int i=0;i<panjang;i++)
    {
        if((CaveIndex[i]>='a' && CaveIndex[i]<='z') || CaveIndex[0]=='-')
        {
            penanda = false;
        }
        if((CaveIndex[i]>='A' && CaveIndex[i]<='Z') || CaveIndex[0]=='-')
        {
            penanda = false;
        }
    }
    if(penanda==false)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int hanyaAngka1(char GoldProduction[])
{
    bool penanda = true;
    int panjang = strlen(GoldProduction);
    for(int i=0;i<panjang;i++)
    {
        if((GoldProduction[i]>='a' && GoldProduction[i]<='z') || GoldProduction[0]=='-')
        {
            penanda = false;
        }
        if((GoldProduction[i]>='A' && GoldProduction[i]<='Z') || GoldProduction[0]=='-')
        {
            penanda = false;
        }
    }
    if(penanda==false)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int inputCaveIndex()
{
    char caveIndex[1001];
    int finalCaveIndex;
    int temp;
    do{
        printf("Input cave index [1-999]     : ");
        scanf("%s",&caveIndex);fflush(stdin);
        int check = hanyaAngka(caveIndex);
        while(check==0)
        {
            printf("\n");
            printf("Input cave index [1-999]     : ");
            scanf("%s",&caveIndex);fflush(stdin);
            check = hanyaAngka(caveIndex);
        }
        finalCaveIndex = atoi(caveIndex);
        temp = finalCaveIndex;
        if(temp > 999 || temp==0)
        {
            printf("\n");
        }
    }while(temp > 999 || temp==0);
                
        return temp;
}

int inputGoldProduction()
{
    char goldProduction[101];
    int finalGoldProduction;
    int temp;
    int check;
    do{
        printf("Input gold production [1-100]: ");
        scanf("%s",&goldProduction);fflush(stdin);
        check = hanyaAngka1(goldProduction);
        while(check==0)
        {
            printf("Input gold production [1-100]: ");
            scanf("%s",&goldProduction);fflush(stdin);
            check = hanyaAngka(goldProduction);
        }
        finalGoldProduction = atoi(goldProduction);
        temp = finalGoldProduction;
    }while(temp > 100 || temp==0);
    return temp;
}

void inOrder(data *node,int depth) 
{
	if(node==NULL)
	{
		return;
	}
	else if(node!=NULL)
	{
	   inOrder(node->left,depth+1); 
	   printf(">> Cave %d   (depth %d   ), total gold production: %d\n",node->caveIndex,depth+1,node->goldProduction); 
	   inOrder(node->right,depth+1); 
    }
}

void *freeAllMemory(data * node){
       if (node != NULL) {
        freeAllMemory(node->right);
        freeAllMemory(node->left);
        free(node);
     }
}

void menu()
{
    printf("\n\n");
    printf("Hov Mining Simulator\n");
    printf("====================\n");
    printf("[1] Insert Mining Data\n");
    printf("[2] Display All Cave Data\n");
    printf("[3] Display Mining Reports\n");
    printf("[4] Exit\n");
    printf(">> ");
}
void printArr(int arr[], int n) 
{ 
    printf("\n\n");
    for (int i = 0; i < n; i++) 
        printf(">> Total gold production for depth %d   is %d\n",i+1,arr[i]); 
} 
int max(int num1, int num2)
{
    return (num1 > num2 ) ? num1 : num2;
}

int getHeight(data* node) 
{ 
    if (node->left == NULL && node->right == NULL) 
        return 0; 
  
    int left = 0; 
    if (node->left != NULL) 
        left = getHeight(node->left); 
  
    int right = 0; 
    if (node->right != NULL) 
        right = getHeight(node->right); 
  
    return (max(left, right) + 1); 
} 

void calculateLevelSum(data* node, int level, int sum[]) 
{ 
    if (node == NULL) 
        return; 
  
    sum[level] += node->goldProduction; 
   
    calculateLevelSum(node->left, level + 1, sum); 
    calculateLevelSum(node->right, level + 1, sum); 
} 

int main()
{
    int pilihan;
    int caveIndex;
    int goldProduction;  
    do{
        system("cls");
        menu();    
        scanf("%d",&pilihan); fflush(stdin);
        switch(pilihan)
		{
			case 1:
			    system("cls");
			    printf("\n\n");
				caveIndex = inputCaveIndex();
				goldProduction = inputGoldProduction();
				printf("\n\n");
				root = push(root,caveIndex,goldProduction);
				printf("\n\n");
				break;
			case 2:
			    system("cls");
				if(root==NULL)
				{
				    printf("\n\n");
				    printf("Cave data is empty, nothing to display.\n");
                }
                else
                {
                    printf("\n\n");
                    inOrder(root,0);
                }
                printf("\n\nPress any key to continue...");
				getchar();
				break;
			case 3:
				system("cls");
				if(root==NULL)
				{
				    printf("\n\n");
				    printf("Cave data is empty, nothing to report.\n");
                }
                else
                {
                    int levels = getHeight(root) + 1; 
                    int sum[levels] = { 0 }; 
                    calculateLevelSum(root, 0, sum); 
                    printArr(sum, levels); 
                }        
                printf("\n\nPress any key to continue...");
				getchar();
				break;
			case 4:
			    system("cls");
			    printf("\n\n");
				freeAllMemory(root);
				printf("All data has been removed from memory.\n");
				printf("Thank you for playing, see you again...\n\n");
				break;
		}
    }while(pilihan < 1 || pilihan > 4 || pilihan !=4);
	return 0;
}
