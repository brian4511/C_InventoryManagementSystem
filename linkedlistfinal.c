

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node
{
    int partNum;
    int quantity;
    float price;
    struct Node *next;
};
void getInput(int *,int *,float *);
void getHelp();

void createLink(struct Node** head_ref,int part_data, int qty_data, float price_data)
{
        struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));

        struct Node *last = *head_ref;

        new_node->partNum = part_data;
        new_node->quantity = qty_data;
        new_node->price = price_data;

        new_node->next = NULL;

        while (last->next != NULL)
            last = last->next;

        last->next = new_node;

}
void insertLink(struct Node** head_ref,int key_data,int qty_data,float price_data)
{
    system("cls");

    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));

            new_node->partNum=key_data;
            new_node->quantity=qty_data;
            new_node->price=price_data;

            new_node->next = *head_ref;
            *head_ref = new_node;
}
void insertmiddleLink(struct Node** head_ref,struct Node* prev_node,int key_data, int qty_data, float price_data)
{
    system("cls");

    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    struct Node *last = *head_ref;

            new_node->partNum=key_data;
            new_node->quantity=qty_data;
            new_node->price=price_data;

            while (last->next != NULL)
            {
                if (key_data < prev_node->partNum)
                {
                    new_node->next = last->next;
                    last->next = new_node;
                    break;
                }
                prev_node = prev_node->next;
                last = last->next;
            }
            if (last->next==NULL && key_data>last->partNum)
            {
                new_node->next = NULL;
                last->next = new_node;
            }

}
void destroyLink(struct Node** head_ref,struct Node* next_node,int key_data)
{
    system("cls");

    struct Node *last = *head_ref;

    while (last->next != NULL)
    {
        if (key_data == next_node->partNum)
        {
            last->next = next_node->next;
            free(next_node);
            break;
        }
        else if (key_data == last->partNum)
        {
            *head_ref = last->next;
            free(last);
        }
        next_node = next_node->next;
        last = last->next;
    }
    getchar();
}
void destroyFinalLink(struct Node** head_ref,int key_data)
{
	struct Node* current = *head_ref;
	struct Node* next;

	next = current->next;
	free(current);
	current = next;

	*head_ref = NULL;

	getchar();
}
void selectLink(struct Node** head_ref,int key_data)
{
    system("cls");

    struct Node *last = *head_ref;
    while (last->next != NULL)
    {
        if (key_data == last->partNum)
        {
            printf("The part number is: %d\nThe quantity is: %d\nThe price is: $%.2f\n",last->partNum,last->quantity,last->price);
            break;
        }
        last = last->next;
    }
    if ((last->next == NULL) && (key_data == last->partNum))
    {
        printf("The part number is: %d\nThe quantity is: %d\nThe price is: $%.2f",last->partNum,last->quantity,last->price);
    }
    getchar();
}
void modifyLink(struct Node** head_ref,int key_data,int new_qty,float new_price)
{
    system("cls");

    struct Node *last = *head_ref;

    while (last->next != NULL)
    {
        if (key_data == last->partNum)
        {
            last->quantity = new_qty;
            last->price = new_price;
            break;
        }
        last = last->next;
    }
    if ((last->next == NULL) && (key_data == last->partNum))
    {
            last->quantity = new_qty;
            last->price = new_price;
    }
    getchar();
}
void saveList(struct Node** head_ref)
{
    system("cls");

    struct Node *last = *head_ref;

    FILE *link;

    link = fopen("linkList.txt","w");

    if (link == NULL)
    {
        printf("Error with file!");
        exit(0);
    }

    while (last != NULL)
    {
        fprintf(link,"%d %d %.2f\n",last->partNum,last->quantity,last->price);
        last = last->next;
    }

    fclose(link);
}
void printList(struct Node *first)
{
    system("cls");

    while (first != NULL)
    {
        printf("%d,%d,$%.2f\n",first->partNum,first->quantity,first->price);
        first = first->next;
    }
}
int main()
{
    char option[11],file_name[15];
    int partNum,qty,x;
    float price;
    struct Node* first = NULL;

    printf("**create**\n**print**\n**delete**\n**insert**\n**select**\n**modify**\n**save**\n**add**\n**exit**\n**help**  ");
    gets(option);
    while (strcmp(option,"exit")!=0)
    {
        if (strcmp(option,"create")==0)
        {
            first = (struct Node*)malloc(sizeof(struct Node));
            printf("Enter the part number ");
            scanf("%d",&first->partNum);

            printf("Enter the quantity ");
            scanf("%d",&first->quantity);

            printf("Enter the price ");
            scanf("%f",&first->price);
            getchar();
            first->next = NULL;

            printf("Would you like to add another part (yes or no): ");
            gets(option);
            do {
                if (strcmp(option,"yes")==0)
                {
                    getInput(&partNum,&qty,&price);
                    createLink(&first,partNum,qty,price);
                    printf("Would you like to add another part (yes or no): ");
                    gets(option);
                }
            } while (strcmp(option,"yes")==0);
        }
        else if (strcmp(option,"print")==0)
        {
            system("cls");
            printList(first);
        }
        else if (strcmp(option,"insert")==0)
        {
            getInput(&partNum,&qty,&price);
            if (partNum < first->partNum)
            {
                insertLink(&first,partNum,qty,price);
            }
            else if (partNum > first->partNum)
            {
                insertmiddleLink(&first,first->next,partNum,qty,price);
            }
        }
        else if (strcmp(option,"delete")==0)
        {
            printf("What is the part number of the part you would like to delete? ");
            scanf("%d",&partNum);
            if (first->next != NULL)
            {
            	destroyLink(&first,first->next,partNum);
        	}
        	else if (first->next == NULL)
			{
				destroyFinalLink(&first,partNum);
			}
        }
        else if (strcmp(option,"select")==0)
        {
            printf("What is the part number of the part you would like to see? ");
            scanf("%d",&partNum);
            selectLink(&first,partNum);
        }
        else if (strcmp(option,"modify")==0)
        {
            printf("What is the part number of the part you would like to modify? ");
            scanf("%d",&partNum);
            printf("\nEnter the new quantity: ");
            scanf("%d",&qty);
            printf("\nEnter the price: ");
            scanf("%f",&price);

            modifyLink(&first,partNum,qty,price);
        }
        else if (strcmp(option,"save")==0)
        {
            saveList(&first);
        }
        else if (strcmp(option,"add")==0)
        {
            first = (struct Node*)malloc(sizeof(struct Node));
            printf("Enter the filename including extension: ");
            gets(file_name);
                FILE *link;
                link = fopen(file_name,"r");
                if (link == NULL)
                {
                    printf("Error with writing to the file!");
                    exit(0);
                }
                x = fscanf(link,"%d%d%f",&first->partNum,&first->quantity,&first->price);
                first->next = NULL;
                while(x!=-1)
                {
                x = fscanf(link,"%d%d%f",&partNum,&qty,&price);
                if (x == -1)
                    break;
                createLink(&first,partNum,qty,price);
                }
                fclose(link);
        }
        else if (strcmp(option,"help")==0)
        {
            getHelp();
        }

        printf("\n**create**\n**print**\n**delete**\n**insert**\n**select**\n**modify**\n**save**\n**add**\n**exit**\n**help**  ");
        gets(option);
    }
    return 0;
}
void getHelp()
{
    system("cls");
    printf("create - Create a set of parts with part number, quantity, and price\n");
    printf("print - Print the entire list\n");
    printf("select - Print the information for one selected part number\n");
    printf("modify - Modify an existing part in the linked list\n");
    printf("delete - Delete an existing part from the list\n");
    printf("insert - Insert a new structure into the sorted linked list\n");
    printf("save - Save a set of parts to a text file named linkList.txt\n");
    printf("add - Add to an parts to the list from a text file.\n");
    printf("exit - Exit from the parts application.\n\n\n\n");
}
void getInput(int *partNum,int *qty,float *price)
{
    printf("Enter the part number ");
    scanf("%d",partNum);

    printf("Enter the quantity ");
    scanf("%d",qty);

    printf("Enter the price ");
    scanf("%f",price);
    getchar();
}
