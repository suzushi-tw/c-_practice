#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

int getlistlength(Node *head)
{
    int length = 0;

    return length;
}

int solvelinklist(Node *list1, Node *list2)
{
    Node *resultlist = NULL;
    int carry = 0;
    int length1 = getlistlength(list1);
    int length2 = getlistlength(list2);

    while (list1 != NULL || list2 != NULL || carry)
    {
        int digit1 = (list1 != NULL) ? list1->data : 0;
        int digit2 = (list2 != NULL) ? list2->data : 0;

        int sum = digit1 + digit2 + carry;

        // insert(&resultlist, sum % 10);
        if (length1 > length2)
        {
            list1->data = sum % 10;

            if (carry > 0)
            {
                // insert new node
            }
        }
        else
        {
            list2->data = sum % 10;
            if (carry > 0)
            {
                //insert new node
            }
        }

        carry = sum / 10;
        if (list1)
        {
            list1 = list1->next;
        }
        if (list2)
        {
            list2 = list2->next;
        }
    }

    return resultlist;
}
// inser at beginning

int main()
{
    Node *list1;
    insert(&list1, 4);
    insert(&list1, 3);
    insert(&list1, 2);
    insert(&list1, 1);

    Node *list2;
    insert(&list1, 4);
    insert(&list1, 5);

    int result = solvelinklist(list1, list2);
}