////////////////////Project 2 DS, Name: Abdalkarim Eiss --- Id: 1200015
#include <stdio.h>
#include <malloc.h>
#include <intrin.h>
#include <math.h>

struct stack;
typedef struct stack *ptr;
struct stack {
    char operation;
    ptr next;
};
typedef ptr stack;
typedef ptr pos;
//////////////////////
//////Single Linked list to store the equation
struct node;
typedef struct node *pr;
struct node {
    char exp;
    pr next;
};
typedef pr LinkedList;
typedef pr ps;

///insert function
void insert(LinkedList L, char x) {
    LinkedList newNode = (LinkedList) malloc(sizeof(struct node));
    ps t;
    if (L != NULL && newNode != NULL) {
        for (t = L; t->next != NULL; t = t->next); //////////////check and move cursor
        newNode->next = t->next;
        t->next = newNode;
        newNode->exp = x;
    }
}

///Check empty
int isEmpty(LinkedList L) {
    return (L->next == NULL);   /////Only Header
}

////Display
void printList(LinkedList L) {
    if (L != NULL) {
        ps t = L->next;
        while (t != NULL) {
            printf("%c", t->exp);
            t = t->next;
        }
        printf("\n");
    }
}


///Get Size
int getsize(LinkedList L) {
    if (L != NULL) {
        int count = 0;
        ps t = L->next;
        while (t != NULL) {
            count++;
            t = t->next;
        }
        return count;
    }
}

/////////////////////////////////////////////////////////////////////////
/////////////////////
/////To add
void push(stack s, char x) {
    stack newNode = (stack) malloc(sizeof(struct stack));  ///To put the value into
    if (s != NULL && newNode != NULL) {
        newNode->next = s->next;
        newNode->operation = x;
        s->next = newNode;
        /// printf("\nAdd Done To the stack!!\n");
    }
}

////To check if empty or not
int isStackEmpty(stack s) {
    return (s->next == NULL);
}

/////////////////To make the pop operation for parenthesis without action
void POP(stack s) {
    if (!isStackEmpty(s)) {
        pos top = s->next; ///Cursor, I don't need to make malloc and etc
        s->next = top->next;
//        printf("\n%c deleted", top->operation);
        free(top);
    }
//        printf("No action, the stack it's empty!!");
}

/////To delete the top element from the stack
int pop(stack s) {
    if (!isStackEmpty(s)) {
        pos top = s->next; ///Cursor, I don't need to make malloc and etc
        s->next = top->next;
//        printf("\n%c deleted", top->operation);
        free(top);
        return top->operation;
    }
//        printf("No action, the stack it's empty!!");
}

int isValid(LinkedList L) {
    /////To store if all exp on equation is valid or not
    LinkedList validity = (LinkedList) malloc(sizeof(struct node));
    validity->next = NULL;
    ps currentN = L->next;
    ///////////////Variables to check the validity
    int fBrackets1; ///// For (
    int fBrackets2; /////For )
    int sBrackets1; ////For [
    int sBrackets2; ////For ]
    int tBrackets1; ///// For {
    int tBrackets2; ///// For }
    char currentExp;

    int count = 0;
    if (L != NULL) {
        while (currentN != NULL) {
            currentExp = currentN->exp; ///to get the exp
            ///printf("%c\t",currentExp);
            //////To check if there is ( <- and -> )
            if (currentExp == '(') {
                fBrackets1 = 1;
                currentN = currentN->next;
                count++;
            } else if (currentExp == ')') {
                fBrackets2 = 1;
                currentN = currentN->next;
            } else if (currentExp == '[') {
                sBrackets1 = 1;
                currentN = currentN->next;
                count++;
            } else if (currentExp == ']') {
                sBrackets2 = 1;
                currentN = currentN->next;
            } else if (currentExp == '{') {
                tBrackets1 = 1;
                currentN = currentN->next;
                count++;
            } else if (currentExp == '}') {
                tBrackets2 = 1;
                currentN = currentN->next;
            } else {
                currentN = currentN->next;
            }
            //////////////////Check the validity
            if (fBrackets1 && fBrackets2 == 1) {
                ///printf("\n\nYes\t");
                ////////Update
                fBrackets1 = 0;
                fBrackets2 = 0;
                insert(validity, 'y');
            } else if (sBrackets1 && sBrackets2 == 1) {
                ///printf("\n\nYes for 2\t");
                ////////Update
                sBrackets1 = 0;
                sBrackets2 = 0;
                insert(validity, 'y');
            } else if (tBrackets1 && tBrackets2 == 1) {
                ///printf("\n\nYes for 3\t");
                ////////Update
                tBrackets1 = 0;
                tBrackets2 = 0;
                insert(validity, 'y');
            } else {
                continue;
            }

        }

        /// printList(validity);
        /////To check if all valid
        int validitySize = getsize(validity);  ///The size of Validity Linked list OK
        if (validity != NULL) {
            /// printf("\n%d",validitySize);
            if (count == validitySize) {
                return 1;
            } else {
                return 0;
            }
        }
    } else {
        return 0;
    }

}

////////////Function to get the top of stack
int topOfStack(stack s) {
    if (!isStackEmpty(s)) {
        return s->next->operation;
    }
    return 0;
}

///////////////priority function to set the priority of each op
int priority(char operator) {
    if (operator == '^') {
        return 3;
    } else if (operator == '*' || operator == '/' || operator == '%') {
        return 2;
    } else if (operator == '+' || operator == '-') {
        return 1;
    } else {
        return 0;  // lowest precedence for invalid or unrecognized operators
    }
}

////////////To check if the char is operation
int isOperation(char op) {
    return (op == '*' || op == '/' || op == '+' || op == '-');
}

////////Infix to postfix function
void infixTopostfix(stack S, LinkedList infix, LinkedList postfix) {  ////////OK
    ps cursor = infix->next;   //Cursor on postfix linked list
    if (infix != NULL && isValid(infix)) {
        while (cursor != NULL) {
            /////printf("%c",cursor->exp);
            ////Insert
            if (cursor->exp >= '0' && cursor->exp <= '9') { ////OK
                insert(postfix, cursor->exp);
            } else if (cursor->exp == '(') { ////////OK
                push(S, cursor->exp);
            } else if (cursor->exp == ')') {    ///////OK
                char x;
                while ((x = pop(S)) != '(') {
                    insert(postfix, x);
                }

            } else if (cursor->exp == '[' || cursor->exp == ']') {
                insert(postfix, cursor->exp);
            } else { //////OK
                if (priority(topOfStack(S)) >= priority(cursor->exp)) {
                    insert(postfix, pop(S));
                    push(S, cursor->exp);
                    //printf("\n\n%c", pop(S));
                }
                    /// if(priority(topOfStack(S))<priority(cursor->exp)){
                else {
                    push(S, cursor->exp);
                }

                ////}
            }
            cursor = cursor->next;
        }
        while (!isStackEmpty(S)) {
            insert(postfix, pop(S));
        }
        printList(postfix);
    }
}

//// This function converts a postfix expression to prefix form.
void postfixToprefix(stack s, LinkedList postfix, LinkedList prefix) {
    ps cursor = postfix->next;
    ///////int mark=0; /////To set a mark if the next exp is operation
    //char store[100]; ////To store the equation on each step
    if (postfix != NULL) {
        while (cursor != NULL) {
            if (cursor->exp >= '0' && cursor->exp <= '9') {
                push(s, cursor->exp);
                if (isOperation(cursor->next->exp)) {
                    /// mark=1;
                }
            } else if (isOperation(cursor->exp)) {
                int count = 0; ////Counter to count the number of times that the stack became poped
                int special = 0;
                char firstOp; ///To put the first Operand
                char secondOp;////// To put the second operand that (on the top)
                insert(prefix, cursor->exp);
                while (count != 2) {
                    if (count == 0) {
                        secondOp = pop(s);
                        if (isStackEmpty(s)) {
                            special = 1;
                            break;
                        }
                    } else {
                        firstOp = pop(s);
                    }
                    ////insert(prefix,pop(s));
                    count++;
                }
                ///Insert the operands
                if (special == 1) {
                    insert(prefix, secondOp);
                } else {
                    insert(prefix, firstOp);
                    insert(prefix, secondOp);
                }
            }
            cursor = cursor->next;
        }
        printList(prefix);
    }
}

////SaveToFile
void Save(LinkedList L, FILE *file) {
    if (L != NULL) {
        ps t = L->next;
        while (t != NULL) {
            fprintf(file, "%c", t->exp);
            t = t->next;
        }
        printf("\n");
    }
}

////////////Function to find the result of equation
void evaluate(stack s, LinkedList postfix) {
    ps cursor = postfix->next;  ///Cursor
    char operation;
    int result;
    if (postfix != NULL) {
        while (cursor != NULL) {
            if (cursor->exp >= '0' && cursor->exp <= '9') { ///////If number
                push(s, cursor->exp);
            } else if (isOperation(cursor->exp)) {
                operation = cursor->exp;  /// To store operation
                /////To check plus
                if (operation == '+') {
                    result = (pop(s) - '0') + (pop(s) - '0');   /////To evaluate the operands
                    //printf("\n res = %d",result);
                    if (cursor->next == NULL) {
                        printf("%d", result);
                    } else {
                        push(s, result + '0');   ////Push the result into the stack
                    }
                    ////printf("\n\n%c",topOfStack(s));

                }
                    ////To check multiply
                else if (operation == '*') {
                    result = (pop(s) - '0') * (pop(s) - '0');   /////To evaluate the operands
                    if (cursor->next == NULL) {
                        printf("%d", result);
                    } else {
                        push(s, result + '0');   ////Push the result into the stack
                    }
                    ////printf("\n\n%c",topOfStack(s));

                }
                    ////To check divide
                else if (operation == '/') {
                    int Fnum = pop(s) - '0';
                    int Lnum = pop(s) - '0';
                    result = Lnum / Fnum;   /////To evaluate the operands
                    //printf("\n res = %d",result);
                    if (cursor->next == NULL) {
                        printf("%d", result);
                    } else {
                        push(s, result + '0');   ////Push the result into the stack
                    }
                    ////printf("\n\n%c",topOfStack(s));

                }
                    ////To check minus
                else if (operation == '-') {
                    int Fnum = pop(s) - '0';
                    int Lnum = pop(s) - '0';
                    result = Lnum - Fnum;   /////To evaluate the operands
                    //printf("\n res = %d",result);
                    if (cursor->next == NULL) {
                        printf("%d", result);
                    } else {
                        push(s, result + '0');   ////Push the result into the stack
                    }
                    ////printf("\n\n%c",topOfStack(s));

                }
                    ////To check exponential
                else if (operation == '^') {
                    int Fnum = pop(s) - '0';
                    int Lnum = pop(s) - '0';
                    result = pow(Lnum, Fnum);   /////To evaluate the operands
                    //printf("\n res = %d",result);
                    if (cursor->next == NULL) {
                        printf("%d", result);
                    } else {
                        push(s, result + '0');   ////Push the result into the stack
                    }
                    ////printf("\n\n%c",topOfStack(s));

                }
            }
            cursor = cursor->next;
        }
        if (!isStackEmpty(s)) {
            printf("%c", pop(s));
        }
    }
}

////////Main function
int main() {
    stack s;
    s = (stack) malloc(sizeof(struct stack));
    s->next = NULL;
    stack s2;
    s2 = (stack) malloc(sizeof(struct stack));
    s2->next = NULL;
    ///I need this Linked list to convert from infix to postfix and insert on it then convert to prefix
    LinkedList postfix1 = (LinkedList) malloc(sizeof(struct node));
    postfix1->next = NULL;
    LinkedList postfix2 = (LinkedList) malloc(sizeof(struct node));
    postfix2->next = NULL;
    LinkedList postfix3 = (LinkedList) malloc(sizeof(struct node));
    postfix3->next = NULL;
    LinkedList postfix4 = (LinkedList) malloc(sizeof(struct node));
    postfix4->next = NULL;
    /////For prefix
    LinkedList prefix1 = (LinkedList) malloc(sizeof(struct node));
    prefix1->next = NULL;
    LinkedList prefix2 = (LinkedList) malloc(sizeof(struct node));
    prefix2->next = NULL;
    LinkedList prefix3 = (LinkedList) malloc(sizeof(struct node));
    prefix3->next = NULL;
    LinkedList prefix4 = (LinkedList) malloc(sizeof(struct node));
    prefix4->next = NULL;
    //////////////fOR MENU
    char e = '.';
    int choice;
///////Definitions for read
    FILE *InFile;
    FILE *OutFile;
    // char line[100];
    char charExp; ////To read the exp from the file
    char InFileName[50];//////////array of char to put the name of Input file
    char OutfileName[50] = "output.txt";    ////Output file
    // int counter = 1; ////Counter for lines
    char Isread = 'n'; /////To mark the file if read or not
    int isConvert = 0;
    printf("\t\t\t--- Calculator Application ---\n");

    ////Define Linked list to store the equations
    LinkedList L1 = (LinkedList) malloc(sizeof(struct node));
    L1->next = NULL;
    LinkedList L2 = (LinkedList) malloc(sizeof(struct node));
    L2->next = NULL;
    LinkedList L3 = (LinkedList) malloc(sizeof(struct node));
    L3->next = NULL;
    LinkedList L4 = (LinkedList) malloc(sizeof(struct node));
    L4->next = NULL;
/////////While loop to give the menu to the user on each time
    while (e != 'q') {
        ////////////////Instructions for menu
        printf("\nPlease choose from the menu: \n");
        printf("\n\t1.Read all equations from the file.\n\t2.Check the validity of equations.\n\t"
               "3.Convert valid equations from infix to prefix and print the prefix expressions.\n\t"
               "4.Evaluate the prefix expressions and print all results.\n\t5.Print all invalid equations.\n\t"
               "6.Print all equations to the output.txt file.\n\t7.Exit\n\tEnter: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: ////For read the file
                if (Isread == 'n') {
                    printf("\nPlease enter the input file name: ");
                    scanf("%s", InFileName);
                    ////Open the input file
                    InFile = fopen(InFileName, "r");
                    if (InFile == NULL) {
                        printf("\nThis file isn't exist!!");
                        continue;
                    } else {
                        /// Counter for the number of lines
                        int countNewLine = 0;
                        //////To display the equations to the user
                        while ((charExp = fgetc(InFile)) != EOF) {
                            ////To check if new line
                            if (charExp == '\n') {
                                countNewLine++;
                            }
                            ///Insert equations
                            if (countNewLine == 0) {
                                insert(L1, charExp);
                            } else if (countNewLine == 1) {
                                insert(L2, charExp);
                            } else if (countNewLine == 2) {
                                insert(L3, charExp);
                            } else if (countNewLine == 3) {
                                insert(L4, charExp);
                            }
                        }
                        ///Close the file
                        fclose(InFile);
                        ////Display equations
                        printf("\nAll equations in an infix form: \n\n");
                        printList(L1);
                        printList(L2);
                        printList(L3);
                        printList(L4);
                        Isread = 'y';
                    }
                } else {
                    printf("\nThis file is already read!!");
                }


                break;

            case 2: //////////To check the validity of equation
                ////To force the user to read the input file firstly
                if (Isread == 'n') {
                    printf("\nSorry, we cannot make the operation, read and load the equations then make this operation after that save it!!");
                } else {
                    if (isValid(L1)) {   ///////To check the validity
                        printf("\nEq1->is valid");
                    } else {
                        printf("\nEq1-> invalid");
                    }
                    if (isValid(L2)) {
                        printf("\nEq2->is valid");
                    } else {
                        printf("\nEq2-> invalid");
                    }
                    if (isValid(L3)) {
                        printf("\nEq3->is valid");
                    } else {
                        printf("\nEq3-> invalid");
                    }
                    if (isValid(L4)) {
                        printf("\nEq4->is valid");
                    } else {
                        printf("\nEq4-> invalid");
                    }
                }
                break;
            case 3: /////////To convert from infix to prefix
                if (Isread == 'n') {
                    printf("\nSorry, we cannot make the operation, read and load the equations then make this operation after that save it!!");
                } else {
                    if (isValid(L1)) {   ///////To check the validity and then print all invalid equations
                        printf("\nPostfix of Eq1: ");
                        infixTopostfix(s, L1, postfix1);
                        printf("\nPrefix of Eq1: ");
                        postfixToprefix(s2, postfix1, prefix1);
                    }
                    if (isValid(L2)) {
                        printf("\nPostfix of Eq2: ");
                        infixTopostfix(s, L2, postfix2);
                        printf("\nPrefix of Eq2: ");
                        postfixToprefix(s2, postfix2, prefix2);

                    }
                    if (isValid(L3)) {
                        printf("\nPostfix of Eq3: ");
                        infixTopostfix(s, L3, postfix3);
                        printf("\nPrefix of Eq3: ");
                        postfixToprefix(s2, postfix3, prefix3);
                    }
                    if (isValid(L4)) {
                        printList(L4);
                        printf("\nPostfix of Eq4: ");
                        infixTopostfix(s, L4, postfix4);
                        printf("\nPrefix of Eq4: ");
                        postfixToprefix(s2, postfix4, prefix4);
                    }
                    isConvert = 1; ////UPDATE
                }
                break;
            case 4: ////TESTTTTT  ---> Evaluate the prefix  ////Put a reference for read and  conversion to prefix as special char
                if (Isread == 'n') {
                    printf("\nSorry, we cannot make the operation, read and load the equations then make this operation after that save it!!");
                } else {
                    if (isConvert == 1) {
                        if (isValid(L1)) {
                            printf("\nResult1= ");
                            evaluate(s, postfix1);
                        }
                        if (isValid(L2)) {
                            printf("\nResult2= ");
                            evaluate(s, postfix2);
                        }
                        if (isValid(L3)) {
                            printf("\nResult3= ");
                            evaluate(s, postfix3);
                        }
                        if (isValid(L4)) {
                            printf("\nResult4= ");
                            evaluate(s, postfix4);
                        }
                    }
                }

                break;
            case 5: ////To print invalid equations
                if (Isread == 'n') {
                    printf("\nSorry, we cannot make the operation, read and load the equations then make this operation after that save it!!");
                } else {
                    printf("\nInvalid Equations: \n");
                    if (!isValid(L1)) {   ///////To check the validity and then print all invalid equations
                        printf("\nEq1:");
                        printList(L1);
                    }
                    if (!isValid(L2)) {
                        printf("\nEq2:");
                        printList(L2);

                    }
                    if (!isValid(L3)) {
                        printf("\nEq3:");
                        printList(L3);
                    }
                    if (!isValid(L4)) {
                        printf("\nEq4:");
                        printList(L4);
                    }
                }
                break;
            case 6: ////To save all equations to output.txt file
                OutFile = fopen(OutfileName, "w");
                if (Isread == 'n') { ///If there is no data
                    printf("\nSorry, we cannot make the operation, read and load the equations then make this operation after that save it!!");
                } else {
                    if (OutFile == NULL) {
                        printf("\n\n\nNo file");
                        continue;
                    } else {
                        if (L1 != NULL) {
                            ////To save equation 1
                            fprintf(OutFile, "Eq1: ");
                            Save(L1, OutFile);
                            if (isValid(L1)) {
                                fprintf(OutFile, " -> Valid");
                                fprintf(OutFile, ", postfix: ");
                                Save(postfix1, OutFile);
                                fprintf(OutFile, ", prefix: ");
                                Save(prefix1, OutFile);
                            } else {
                                fprintf(OutFile, " -> InValid");
                            }
                        }
                        /////For eq2
                        fprintf(OutFile, "\nEq2: ");
                        Save(L2, OutFile);
                        if (isValid(L2)) {
                            fprintf(OutFile, " -> Valid");
                            fprintf(OutFile, ", postfix: ");
                            Save(postfix2, OutFile);
                            fprintf(OutFile, ", prefix: ");
                            Save(prefix2, OutFile);
                        } else {
                            fprintf(OutFile, " -> InValid");
                        }
                        //////For eq3
                        fprintf(OutFile, "\nEq3: ");
                        Save(L3, OutFile);
                        if (isValid(L3)) {
                            fprintf(OutFile, " -> Valid");
                            fprintf(OutFile, ", postfix: ");
                            Save(postfix3, OutFile);
                            fprintf(OutFile, ", prefix: ");
                            Save(prefix3, OutFile);
                        } else {
                            fprintf(OutFile, " -> InValid");
                        }
                        ////For eq4
                        fprintf(OutFile, "\nEq4: ");
                        Save(L4, OutFile);
                        if (isValid(L4)) {
                            fprintf(OutFile, " -> Valid");
                            fprintf(OutFile, ", postfix: ");
                            Save(postfix4, OutFile);
                            fprintf(OutFile, ", prefix: ");
                            Save(prefix4, OutFile);
                        } else {
                            fprintf(OutFile, " -> InValid");
                        }
                        printf("\n\nSave Done!!");
                        //fclose(OutFile); ///To close the file
                    }
                }
                break;
            case 7: ////To exit from the program
                printf("\nWe are happy to serve you, thanks ^_^\n");
                exit(1);
                break;
            default:
                printf("\nSorry, this choice is not exist!!!");
                break;

        }
    }

    return 0;
}
