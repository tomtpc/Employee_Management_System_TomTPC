#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

struct employee{
    char name[30];
    int age;
    int code;
    float salary;
    struct employee *next;
};

typedef struct employee *node; //now the employee struct can be call by the name "node" for short

node CreateNode(char name[30],int age,int code,float salary){
    node temp; // declare a node
    temp = (node)malloc(sizeof(struct employee)); //give temp a ranged amount of memory
    temp->next = NULL; //don't have next node;

    //dump data into the node:
    //printf("\nInput Name: ");  fflush(stdin); gets(temp->name);
    //printf("\nInput Age: ");  fflush(stdin); scanf("%d",&temp->age);
    //printf("\nInput Code: ");  fflush(stdin); scanf("%d",&temp->code);
    //printf("\nInput Salary: ");  fflush(stdin); scanf("%f",&temp->salary);
    strcpy(temp->name,name);
    temp->age = age;
    temp->code = code;
    temp->salary = salary;
    return temp; // return new node with data dumped
}

//add to the fist position of the list
node AddHead(node head, char name[30],int age,int code,float salary){
    node temp = CreateNode( name,age, code,salary); //create a node with dumped data
    if(head == NULL){
        head = temp;
    }else{
        temp->next = head; //point the next position of the current head to the next of the temp node
        head = temp; // set the new head to the temp node
    }
    return head;
}

//add to the last position of the linked list
node AddTail(node head, char name[30],int age,int code,float salary){
    node temp, p; //declare 2 temporary node: temp, p
    temp = CreateNode(name,age, code,salary);//create a node with dumped data
    if(head == NULL){
        head = temp; //if the linked list is empty then temp now the head of it
    }else{
        p = head; // create p points to head;
        while(p->next != NULL){
            p = p->next; //go through the linked list till p reaches the end which have ->next = NULL;
        }
        p->next = temp; //make the last ->next = temp node;
    }
    return head;
}

node AddAt(node head, char name[30],int age,int code,float salary, int position){
    if(position == 0 || head == NULL){
        head = AddHead(head,name,age, code,salary);
    }else{

        int k = 1;
        node p = head;
        while(p != NULL && k != position){
            p = p->next;
            ++k;
        }

        if(k != position){


            head = AddTail(head,name,age, code,salary);
        }else{
            node temp = CreateNode(name,age, code,salary);
            temp->next = p->next;
            p->next = temp;
        }
    }
    return head;
}

//Delete node:

//Delete head
node DelHead(node head){
    if(head == NULL){
        printf("\nNothing to delete !");
    }else{
        head = head->next;
    }
    return head;
}

//Delete tail
node DelTail(node head){
    if (head == NULL || head->next == NULL){
         return DelHead(head);
    }
    node p = head;
    while(p->next->next != NULL){
        p = p->next;
    }
    p->next = p->next->next; // make ->next == NULL
    // or we can write like this: p->next = NULL
    return head;
}

//Delete at any position
node DelAt(node head, int position){
    if(position == 0 || head == NULL || head->next == NULL){
        head = DelHead(head);
    }else{
        // Start finding the right position to del, using int k to count position.
        int k = 1;
        node p = head;
        while(p->next->next != NULL && k != position){
            p = p->next;
            ++k;
        }

        if(k != position){
            // if it reached the end of the list, default is to del the last.
            // if you dont want that so, create a alert.
            // printf("The del position is way beyond this current list!\n");
        }else{
            p->next = p->next->next;
        }
    }
    return head;
}

//get data at any position
void GetAt(node head, int position){
    int k = 0;
    node p = head;
    while(p->next != NULL && k != position){
        ++k;
        p = p ->next;
    }
    print();
    printf("%-10s%-10d%-10d%-10.2f\n",p->name,p->age,p->code,p->salary);
}

//Search by name:
int Search(node head, char name[30]){
    int position = 0;
    int flag = 0;
    for(node p = head; p != NULL; p = p->next){
        if(strcmp(p->name, name) == 0){
            flag = 1;
            return position;
        }
        ++position;
    }
    if(flag == 0){
        printf("Object is not found.\n");
    }
    return -1;
}

//Del by name:
node DelByVal(node head, char name[30]){
    int position = Search(head, name);
    DelAt(head, position);
    return head;
}

//Show all Data:
void showAll(node head){
    print();
    for(node p = head; p != NULL; p = p->next){
        printf("%-10s%-10d%-10d%-10.2f\n",p->name,p->age,p->code,p->salary);
    }
}

//Create a empty head:
node InitHead(){
    node head;
    head = NULL;
    return head;
}

//default printf:
void print(){
    printf("\n%-10s%-10s%-10s%-10s\n","Name","Age","Code","Salary\n");
}

//Input data for the node
node Input(){
    node head = InitHead();
    int n, age, code;
    float salary;
    char name[30];
    do{
        printf("Input amount of employee(s): "); fflush(stdin); scanf("%d",&n);
    }while(n <= 0);
    for(int i = 1 ; i <= n; i ++){
        printf("Input data for the %d th employee:\n",i);
        printf("Input Name: "); fflush(stdin); gets(name);
        printf("Input Age: "); fflush(stdin);  scanf("%d",&age);
        printf("Input Code: "); fflush(stdin);  scanf("%d",&code);
        printf("Input Salary: "); fflush(stdin);  scanf("%f",&salary);
        head = AddHead(head,name,age,code,salary);
    }
    return head;
}

//menu
void menu(){
    printf("\n ==== EMPLOYEE MANAGEMENT SYSTEM =======");
    printf("\n 1.Add an employee.");
    printf("\n 2.Search employee data by name.");
    printf("\n 3.Delete employee data by name.");
    printf("\n 4.Update employee data.");
    printf("\n 5.Show all employees data.");
    printf("\n 6.Write all employees data to file.");
    printf("\n 7.Read all employees data from file.");
    printf("\n 0.Exit");
    printf("\nEnter number:");
}

//Add employee:
node addEmployee(node head){
    int age, code;
    float salary;
    char name[30];
    printf("Input data for the employee:\n");
    printf("Input Name: "); fflush(stdin); gets(name);
    printf("Input Age: "); fflush(stdin);  scanf("%d",&age);
    printf("Input Code: "); fflush(stdin);  scanf("%d",&code);
    printf("Input Salary: "); fflush(stdin);  scanf("%f",&salary);
    head = AddHead(head,name,age,code,salary);
    return head;
}

//Search Employee by name:
void searchEmp(node head){
    char name[30];
    printf("\nInput name to search: "); fflush(stdin);gets(name);
    int index = Search(head,name);
    GetAt(head,index);
}

//Del employee by name:
node deleteEmpl(node head){
    char name[30];
    printf("\nInput name to search: "); fflush(stdin);gets(name);
    head = DelByVal(head,name);
    return head;
}

//Update employee:
node updateEmp(node head){
    char name[30];
    printf("\nInput name to search: "); fflush(stdin);gets(name);
    int index = Search(head,name);
    GetAt(head,index);
    head = DelByVal(head, name);
    printf("Input data for the employee:\n");
    float salary;
    int age, code;
    printf("Input data for the employee:\n");
    printf("Input Age: "); fflush(stdin);  scanf("%d",&age);
    printf("Input Code: "); fflush(stdin);  scanf("%d",&code);
    printf("Input Salary: "); fflush(stdin);  scanf("%f",&salary);
    head = AddHead(head,name,age,code,salary);
    index = Search(head,name);
    GetAt(head,index);
    return head;
}

//Write to file:
void write_2_file(node head){
    FILE *fptr;
    fptr = fopen("Employee.txt","w");
    for(node p = head; p != NULL; p = p->next){
        fprintf(fptr,"%s %d %d %f\n",p->name,p->age,p->code,p->salary);
    }
    fclose(fptr);
}

//Read from file:
void read_from_file(){
    FILE *fptr;
    char line[128];
    node head, current;
    head = current = NULL;
    fptr = fopen("Employee.txt","r");
    char *sep = " ";
    while(fgets(line, sizeof(line),fptr)){
        node temp = malloc(sizeof(node));
        temp->next = NULL;
        char *item;
        item = strtok(line, sep);
        if(!item) break;
         strcpy(temp->name,strdup(item));
        item = strtok(NULL, sep);
        if(!item) break;
        temp->age = atof(strdup(item));
        item = strtok(NULL, sep);
        if(!item) break;
        temp->code = atof(strdup(item));
        item = strtok(NULL, sep);
        if(!item) break;
        temp->salary = atof(strdup(item));
        item = strtok(NULL, sep);
        if(head == NULL){
            current = head = temp;
        }else{
            current = current->next = temp;
        }
    }
    fclose(fptr);
    showAll(head);
}

int main()
{
    node head = Input();
    int choice;
    do{
        menu();
        fflush(stdin); scanf("%d",&choice);
        system("cls");
        switch(choice){
            case 1:
                head = addEmployee(head);
                break;
            case 2:
                searchEmp(head);
                break;
            case 3:
                head = deleteEmpl(head);
                break;
            case 4:
                head = updateEmp(head);
                break;
            case 5:
                showAll(head);
                break;
            case 6:
                write_2_file(head);
                break;
            case 7:
                read_from_file();
                break;
        }
    }while(choice != 0);
    return 0;
}
