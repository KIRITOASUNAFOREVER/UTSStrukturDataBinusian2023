#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct data {
	int date, month, year;
	char name[100];
	struct data *next, *prev;
}*head=NULL, *tail=NULL, *temp=NULL;

void popHead();
void popAll();
void printAll();
void addData();
void priorityPush(int, int, int, char*);
int getMonthNumber(char*);
char* getMonthName(int);
long getDateNumber(int, int, int);
struct data *createNode(int, int, int, char*);

long getDateNumber(int date, int month, int year) {
	return (long)(year*10000)+(month*100)+date;
}

int getMonthNumber(char *month) {
	if(!strcmp(month, "january"))return 1;
	if(!strcmp(month, "february"))return 2;
	if(!strcmp(month, "march"))return 3;
	if(!strcmp(month, "april"))return 4;
	if(!strcmp(month, "may"))return 5;
	if(!strcmp(month, "june"))return 6;
	if(!strcmp(month, "july"))return 7;
	if(!strcmp(month, "august"))return 8;
	if(!strcmp(month, "september"))return 9;
	if(!strcmp(month, "october"))return 10;
	if(!strcmp(month, "november"))return 11;
	if(!strcmp(month, "december"))return 12;
}

char* getMonthName(int month) {
	switch(month) {
		case 1: return "january";
		case 2: return "february";
		case 3: return "march";
		case 4: return "april";
		case 5: return "may";
		case 6: return "june";
		case 7: return "july";
		case 8: return "august";
		case 9: return "september";
		case 10: return "october";
		case 11: return "november";
		case 12: return "december";
	}
}

void popAll() {
	while(head)
		popHead();
}

void printAll() {
	temp = head;
	while(temp != NULL) {
		printf("%d %s %d - %s\n", temp->date, getMonthName(temp->month), temp->year, temp->name);
		temp = temp->next;
	}
}

void addData() {
	int date, year;
	char month[100], name[100];
	scanf("%d %s %d - %[^\n]", &date, &month, &year, &name); getchar();
	priorityPush(date, getMonthNumber(month), year, name);
}

struct data *createNode(int date, int month, int year, char *name) {
	// [1] INSERT YOUR CODE HERE
	temp = (struct data*)malloc(sizeof(struct data));
    temp->date = date;
    temp->month = month;
    temp->year = year;
    strcpy(temp->name, name);
    temp->next = NULL;
    temp->prev = NULL;
    return temp;
}

void priorityPush(int date, int month, int year, char *name) {
	// [2] INSERT YOUR CODE HERE
	struct data* newNode = createNode(date, month, year, name);
    long current = getDateNumber(date, month, year);
    
    if (head == NULL) {
        head = tail = newNode;
    }
    else {
        long nodePriority = getDateNumber(head->date, head->month, head->year);
        if (current < nodePriority) {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
            return;
        }
        temp = head;
        while (temp->next != NULL) {
            long nodePriority = getDateNumber(temp->next->date, temp->next->month, temp->next->year);
            if (current < nodePriority) {
                newNode->prev = temp;
                temp->next->prev = newNode;
                newNode->next = temp->next;
                temp->next = newNode;
                return;
            }
            else {
                temp = temp->next;
            }
        }
        tail->next = newNode;
        newNode->prev = tail;
        tail = tail->next;
    }
}

void popHead() {
	// [3] INSERT YOUR CODE HERE
	temp = head;
    if (head != NULL) {
        head = head->next;
        free(temp);
    }
}

int main() {
	int totalPatients, totalCure;
	scanf("%d %d", &totalPatients, &totalCure); getchar();
	for(int i=0; i<totalPatients; i++)
		addData();
	
	for(int i=0; i<totalCure; i++)
		popHead();
	
	if(totalPatients < totalCure || totalPatients == totalCure)
		printf("All patients get the cure, %d cure left\n", totalCure-totalPatients);
	else if(totalPatients > totalCure)
		printf("Need %d more cure\n", totalPatients-totalCure);
		
	printAll();
	popAll();
}
