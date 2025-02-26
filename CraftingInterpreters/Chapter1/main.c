#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <assert.h>

#define perror(str) do { printf(str); exit(1); } while(0);

#define COLOR_BOLD  "\e[1m"
#define COLOR_OFF   "\e[m"

#define COLOR_GREEN "\x1B[32m"
#define COLOR_WHITE "\x1B[37m"

///////// Command Parsing ////////////

enum CMD
{
  ADD,
  REMOVE,
  PRINT,
  PRINTREV
};

typedef struct Command Command;

struct Command
{
  enum CMD name;
  char *nameVal;
  char *val;
};

Command *parseCommand(int ind, char *arr[])
{
  // Parse command type
  char *name = arr[ind];
  enum CMD cmd;
  if (strcmp(name, "ADD") == 0)
  {
    cmd = ADD;
  }
  else if (strcmp(name, "REMOVE") == 0)
  {
    cmd = REMOVE;
  }
  else if (strcmp(name, "PRINT") == 0)
  {
    cmd = PRINT; 
  }
  else if (strcmp(name, "PRINTREV") == 0) 
  {
    cmd = PRINTREV;
  }
  else
  {
    return NULL;
  }

  Command *ret = malloc(sizeof(Command));
  ret->name = cmd;
  ret->nameVal = malloc(strlen(arr[ind]) * sizeof(char));
  strcpy(ret->nameVal, arr[ind]);
  if (cmd == PRINT || cmd == PRINTREV) {
    return ret; 
  }

  ret->val = malloc(strlen(arr[ind+1]) * sizeof(char));
  strcpy(ret->val, arr[ind+1]);
  return ret;
}

///////// LINKED LIST ////////////
// Define a doubly linked list of heap allocated strings

typedef struct Node Node;

struct Node 
{
  char *val;
  Node *next;
  Node *prev;
};

Node *addNode(Node *head, char *val)
{
  printf("Adding node: %s\n", val);
  if (val == NULL) 
  {
    perror("Adding NULL to Linked List!\n")
  }

  if (head == NULL)
  {
    head = malloc(sizeof(Node));
    head->val = val;
    head->next = NULL;
    head->prev = NULL;
    return head;
  }

  Node *curr = head;
  while (curr->next != NULL)
  {
    curr = curr->next;
  }
  curr->next = malloc(sizeof(Node));

  Node *prev = curr;
  curr = curr->next;

  curr->next=NULL;
  curr->prev=prev;
  curr->val = val;
  return curr;
}

void print(Node *head)
{
  printf(COLOR_BOLD);
  printf("Printing Linked List:");
  Node *curr = head;
  printf(COLOR_GREEN);
  while(curr != NULL)
  {
    printf(" %s", curr->val);
    curr = curr->next;
  }
  printf(COLOR_WHITE);
  printf("\n");
  printf(COLOR_OFF);
}

void printRev(Node *head)
{
  Node *curr = head;
  while(curr->next != NULL)
  {
    curr = curr->next;
  }

  printf(COLOR_BOLD);
  printf("Printing Linked List in Rev:");
  printf(COLOR_GREEN);
  while(curr != NULL)
  {
    printf(" %s", curr->val);
    curr = curr->prev;
  }
  printf(COLOR_WHITE);
  printf("\n");
  printf(COLOR_OFF);
}

Node *removeNode(Node *head, int i)
{
  Node *curr = head;
  int j = 0;
  while (j < i && curr != NULL)
  {
    curr = curr->next;
    j++;
  }
  
  if (j != i)
  {
    perror("Attempted to remove element not in Linked List\n")
  }
  
  curr->prev->next = curr->next;
  curr->next->prev = curr->prev;
  return curr;
}

void freeLinkedList(Node *head)
{
  Node *next = head;
  while (next != NULL)
  {
    Node *temp = next;
    next = next->next;
    free(temp->val);
    free(temp);
  }
}

int main(int argc, char *argv[])
{
  Command **cmds = malloc(argc * sizeof(Command));
  int cmdInd = 0;

  printf("Parsing commands. argc: %d\n", argc);
  for (int i = 1; i < argc; i++)
  {
    if (i + 1 == argc) 
    {
      if ((strcmp(argv[i], "PRINT") != 0) && (strcmp(argv[i], "PRINTREV") != 0)){
        printf("Command at index %d - %s, does not have a matching argument", i, argv[i]);
      }
    }
    Command *cmd = parseCommand(i, argv);
    if (cmd == NULL)
    {
      printf("ERROR: Command %s is not valid", argv[i]);
    }
    switch(cmd->name)
    {
      case PRINT:
      case PRINTREV:
        break;
      default:
        i++;
    }
    printf("Command Parsed: %s. New i: %d\n", cmd->nameVal, i);

    cmds[cmdInd++] = cmd;
  }
  printf("Done parsing commands\n");

  Node *head = NULL;
  char **str;
  int i;
  for (int i = 0; i < cmdInd; i++)
  {
    switch(cmds[i]->name)
    {
      case PRINT:
        print(head);
        break;
      case PRINTREV:
        printRev(head);
        break;
      case ADD:
        assert(cmds[i]->val != NULL);
        Node *createdNode = addNode(head, cmds[i]->val);
        if (createdNode != NULL && head == NULL)
        {
          head = createdNode;
        }
        break;
      case REMOVE:
        i = strtol(cmds[i]->val, str, 10);
        if (strcmp(*str, "\0")) {
          printf("ERROR: %c is invalid character", (*str)[0]);
          perror("Invalid character in command\n");
        }
        removeNode(head, i); 
        break;
      default:
        printf("Error: Unknown Command: %s", cmds[i]->nameVal);
    }
  }

  freeLinkedList(head);
  return 0;
}