#include "Node.h"
#include "Stack.h"
#include "BinaryNode.h"
#include <cstdlib>
#include <cstring>

using namespace std;
// John Elsta - this program takes in infix and converts it to postfix and prefix.
bool isOperator(char c);
int precedence(char c);  
Stack* shuntingYard(char* input);
BinaryNode* makeTree(Stack* stack);
void print (BinaryNode* node, int indent = 0);
void printPostfix (BinaryNode* node);
void printPrefix (BinaryNode* node);
void printInfix(BinaryNode* nodes);;


int main(){// this is the main function
  char input[50];
  cin.get(input, 50);
  Stack* stack = shuntingYard(input);
  BinaryNode* head = makeTree(stack);
 
  
  cout << "Tree:" << endl;
  print(head);
  cout << "\nPostfix:  " << endl;
  printPostfix(head);
  cout << endl << "\nPrefix:" << endl;
  printPrefix(head);
  cout << endl << "\nInfix:" << endl;
  printInfix(head);
  cout << endl;
}

void print(BinaryNode* node, int indent){//prints out the tree 
  
  if (node->getRight())
    print(node->getRight(),indent+1);
  for(int j = 0; j <= indent; j++){
    cout << "   ";
  }
  node->printData();
  cout << endl;
  if (node->getLeft()) 
    print(node->getLeft(),indent+1);
}

void printPostfix (BinaryNode* node){//prints out the postfix notation
  if (node->getType() == 1){
    printPostfix(node->getRight());
    printPostfix(node->getLeft());
  }
  node->printData();
}
void printPrefix (BinaryNode* node){ //prints out the prefix notation
  node->printData();
  if (node->getType() == 1){
    printPrefix(node->getRight());
    printPrefix(node->getLeft());
  }
}
void printInfix(BinaryNode* node){ //prints out the infix notation
  if (node->getType() == 1){
    printInfix(node->getRight());
    node->printData();
    printInfix(node->getLeft());
  }
  else{
    node->printData();
  }
  
}

BinaryNode* makeTree(Stack* stack){//this is what actually creates the tree by inputing things from the stack
  BinaryNode* binaryNode;
  if (stack->peek()->getType() == 1){
    binaryNode = new BinaryNode(stack->pop()->getCharData());
    binaryNode->setLeft(makeTree(stack));
    binaryNode->setRight(makeTree(stack));
  }
  else{
    binaryNode = new BinaryNode(stack->pop()->getIntData());
  
  }
  return binaryNode;
}


Stack* shuntingYard(char* input){//shunting yard algorithm
  int i = 0;
  Stack* operatorStack = new Stack(); 
  Stack* outputStack = new Stack();
  while (input[i]){ 
    if(isdigit(input[i])){
      outputStack->push(new Node(atoi(&input[i])));
      while(isdigit(input[i+1])){ 
	i++;
      }
    }
    else if (isOperator(input[i])){ 
      while(operatorStack->peek()){ 
	if (precedence(input[i]) >= precedence(operatorStack->peek()->getCharData())){
	    break;
	  }
	outputStack->push(operatorStack->pop());
	  }
      operatorStack->push(new Node(input[i]));
      }
    else if (input[i] == '('){ 
      operatorStack->push(new Node(input[i]));
    }
    else if (input[i] == ')'){ 
      while(operatorStack->peek()->getCharData() != '('){ 
	outputStack->push(operatorStack->pop());
      }
      delete operatorStack->pop();
    }
    i++;
  }
  while(operatorStack->peek()){ 
    outputStack->push(operatorStack->pop());
  }
  delete operatorStack;
  return outputStack;
}
//checks to see if the char is an operator or not
bool isOperator(char c){
  if (c == '-' ||
      c == '+' ||
      c == '^' ||
      c == '*' ||
      c == '/'){
    return true;
  }
  return false;
}
//check the order before it puts the op onto the stack
int precedence(char c){
  int precedence[256];
  precedence['-'] = 1;
  precedence['+'] = 1;
  precedence['*'] = 2;
  precedence['/'] = 2;
  precedence['^'] = 3;
  precedence['('] = -1;
  return precedence[c];
}
