/*
Thomas Trivino
Infix to Postfix helper
03/19/2024
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 10000

// Nodes for the stack; prev for previous elements, c for characters
typedef struct stackNode {
  char c;
  struct stackNode *prev;
} stackNode;

// Prototypes
void push(stackNode **top, char op);
stackNode *pop(stackNode **top);
char peek(stackNode *top);
stackNode *initialize();
void printStack(stackNode *top);
int precedence(char c);

// Driver Code
int main() {
  // Initializes infix and postfix and stack to hold operators
  char infix[SIZE];
  char postfix[SIZE];
  stackNode *top = initialize();

  // Loads the expression into infix
  printf("Please enter Infix: ");
  scanf("%[^\n]s", infix);

  // Stores the length of infix
  int len = strlen(infix);

  // Keeps track of our pos in postfix and infix
  int j = 0;
  int i;

  for (i = 0; i < len; i++) {

    // We encountered an operator
    if (infix[i] == '+' || infix[i] == '-' || infix[i] == '*' ||
        infix[i] == '/' || infix[i] == '^' || infix[i] == '(' ||
        infix[i] == ')') {

      // Stores the operator
      char currentOp = infix[i];
      
      // If open parenthesis immediately push
      if (currentOp == '(')
        push(&top, '(');

      // If closed parenthesis pop until open parenthesis found
      else if (currentOp == ')') {
        // Pops and frees the ')'
        free(pop(&top));

        // Until '(' is found, appends the operators and frees their memory
        while (peek(top) != '(') {
          postfix[j++] = peek(top);
          free(pop(&top));
        }
      }

      // If the operator is of higher precedence, push it
      else if (precedence(currentOp) > precedence(peek(top)))
        push(&top, currentOp);

      // If the operator is lower precedence, pop and append the stack until
      // currentOp is higher precedence
      else if (precedence(currentOp) <= precedence(peek(top))) {
        while (precedence(currentOp) <= precedence(peek(top))) {
          postfix[j++] = peek(top);
          free(pop(&top));
        }

        // Finally, push currentOp to the stack
        push(&top, currentOp);
      }
    }

    // If we encounter an operand add to postfix
    else {
      postfix[j++] = infix[i];
    }

    // Prints the steps
    printf("\nSTEP %d:\n\t", i + 1);
    printf("STACK:\n\t\t");
    printStack(top);
    printf("\tPOSTFIX:\n\t\t%s\n", postfix);
  }

  // Adds remaining operators in the stack to postfix
  while (top != NULL) {
    postfix[j++] = peek(top);
    free(pop(&top));

    // Prints the steps
    printf("\nSTEP %d:\n\t", (i + 1));
    printf("STACK:\n\t\t");
    printStack(top);
    printf("\tPOSTFIX:\n\t\t%s\n", postfix);
  }

  return 0;
}

// Pushes the elements to the top of the stack
void push(stackNode **top, char op) {
  // Allocates memory for temp
  stackNode *temp = (stackNode *)malloc(sizeof(stackNode));

  // If temp allocated correctly, sets loads the data into temp and updates the
  // top
  if (temp != NULL) {
    temp->c = op;
    temp->prev = *top;
    *top = temp;
  }
}

// Returns the top and removes it from the stack
stackNode *pop(stackNode **top) {
  // Initializes temp to store the to be popped node
  stackNode *temp;
  temp = NULL;

  // If stack not empty, store top in temp and update top
  if (*top != NULL) {
    temp = *top;
    *top = (*top)->prev;
  }

  // Returns NULL if empty, returns the popped element if not
  return temp;
}

// Returns char c in the top of the stack
char peek(stackNode *top) { 
  if (top != NULL)
    return top->c; 
}

// Initializes the stack and returns a stackNode
stackNode *initialize() {
  // Initializes the stack and sets it to NULL (empty)
  stackNode *top = (stackNode *)malloc(sizeof(stackNode));
  top = NULL;

  // Returns the stack
  return top;
}

// Prints the entire stack
void printStack(stackNode *top) {
  // Initializes the traversal node
  stackNode *t;
  t = top;

  // Traverses the entire stack printing the data
  while (t != NULL) {
    printf("(%c) <- ", t->c);
    t = t->prev;
  }

  // Prints NULL to indicate the bottom of the stack
  printf("NULL\n");
}

// Returns the precedence level of the operator
int precedence(char c) {
  // Returns the level of precedence according to PEMDAS
  if (c == '^')
    return 3;
  if (c == '/' || c == '*')
    return 2;
  if (c == '-' || c == '+')
    return 1;

  // Returns -1 if no precedence
  return -1;
}
