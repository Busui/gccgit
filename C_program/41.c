//Binary tree

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct Node Node;

struct Node{
    long item;
    int count;
    Node *pLeft;
    Node *pRight;
};

Node *create_node(long);
Node *add_node(long, Node*);
void list_nodes(Node*);
void free_nodes(Node*);


int main(void)
{
    Node *pRoot = NULL;
    char answer = '\0';
    long value = 0;

    do{
        printf("Enter the node's value: ");
        scanf(" %ld", &value);
        if(!pRoot)
            pRoot = create_node(value);
        else
            //pRoot = add_node(value, pRoot);
            //I make a big mistake at here....
            add_node(value, pRoot);//abandonning the returned value.
        
        printf("Do you want to enter anther (y or n)? ");
        scanf(" %c", &answer);
    }while(tolower(answer) == 'y');

    printf("The values in ascending squuence are: \n");
    list_nodes(pRoot);
    free_nodes(pRoot);

    return 0;
}

Node *create_node(long value)
{
    Node *pNode = (Node*)malloc(sizeof(Node));
    pNode -> item = value;
    pNode -> count = 1;
    pNode -> pLeft = pNode -> pRight = NULL;
    return pNode;
}

Node *add_node(long value, Node *pNode)
{
    if(!pNode)
        return create_node(value);

    if(value == pNode -> item){
        ++pNode -> count;
        return pNode;
    }

    if(value < pNode -> item){
        if(!pNode -> pLeft){
            pNode -> pLeft = create_node(value);
            return pNode -> pLeft;
        }
        else
            return add_node(value, pNode -> pLeft);
    }
    else{
        if(!pNode -> pRight){
            pNode -> pRight = create_node(value);
            return pNode -> pRight;
        }
        else
            return add_node(value, pNode -> pRight);
    }
}

void list_nodes(Node *pNode)
{
    if(pNode -> pLeft)
        list_nodes(pNode -> pLeft);

    printf("%10d x %10ld\n", pNode -> count, pNode -> item);

    if(pNode -> pRight)
        list_nodes(pNode -> pRight);
}

void free_nodes(Node *pNode)
{
    if(!pNode)
        return;

    if(pNode -> pLeft)
        free_nodes(pNode -> pLeft);

    if(pNode -> pRight)
        free_nodes(pNode -> pRight);
        
    //free_nodes(pNode);//oh my god!!!!!
    free(pNode);
}
