/* Revision 1.1.  loadComplex() changed, to return Complex structure */
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <limits.h>

typedef struct {
   double real; 
   double imag; 
} Complex;

#define Exit 0
#define Load 1
#define Display 2
#define Move 3
#define Conjugate 4
#define Add 5
#define Subtract 6
#define Multiply 7
#define Divide 8

#define STACK_SIZE 4
#define EMPTY  (-1)
#define STACK_EMPTY INT_MIN

#define PROMPT_USER_TO(menuItem) printf("%d. %s complex numbers\n", menuItem, #menuItem);

int  displayMenu();
void executeMenuItem(int menuItem);
Complex loadComplex();
int chooseComplexNumberTo(char*);

Complex add(Complex*);
Complex subtract(Complex*);
Complex multiply(Complex*);
Complex divide(Complex*);
Complex complexConjugate(Complex*);
Complex moveComplex(Complex*);
char display();

Complex push(Complex);

Complex stack[STACK_SIZE];
int top = EMPTY;
Complex *head = stack;

int main(void){   
   int choice = Exit;
   printf("Welcome to the complex number calculatollr\n\n");
   do{
      choice = displayMenu();
	   executeMenuItem(choice);
   } while (choice != Exit);

   printf("Program exited\n");
   exit(EXIT_SUCCESS);
}

Complex push(Complex value){
   if (top == STACK_SIZE - 1){
      // stack[top].real = 0;
      // stack[top].imag = 0;
      top = EMPTY;
      for (int i = 0; i < STACK_SIZE; i++){
         stack[i].real = stack[i+1].real;
         stack[i].imag = stack[i+1].imag;
         top++;
      }
      stack[top].real = value.real;
      stack[top].imag = value.imag;
   }

   top++;
   stack[top].real = value.real;
   stack[top].imag = value.imag;
   return stack[top];
}

// display menu options, prompt the user to enter a choice, and return the value selected
// DO NOT CHANGE THIS FUNCTION
int displayMenu(){  
    int input = Exit;
    printf("Select one of the following:\n\n");
    PROMPT_USER_TO(Load)
    PROMPT_USER_TO(Display)
    PROMPT_USER_TO(Move)
    PROMPT_USER_TO(Conjugate)
    PROMPT_USER_TO(Add)
    PROMPT_USER_TO(Subtract)
    PROMPT_USER_TO(Multiply)
    PROMPT_USER_TO(Divide)
    printf("%d. Exit Program\n", Exit);
    scanf("%d", &input);
    return input;
}

// DO NOT CHANGE THIS FUNCTION
void executeMenuItem(int menuItem){
   Complex c = {0,0};  
   static Complex c0 = {0,0}, c1 = {0,0}, cResult = {0,0};

   switch (menuItem) {

         case Exit: break; 

         case Load:
            // push(loadComplex());
            top++;
            if (top > 4){
               for (int i = 0; i < STACK_SIZE; i++){
                  stack[i].real = stack[i+1].real;
                  stack[i].imag = stack[i+1].imag;
               }
               top = 4;
               *(head+(top%STACK_SIZE)) = loadComplex();
            }
            *(head+(top%STACK_SIZE)) = loadComplex();
            // head++;
            // push(*head);
            // head = stack+((head-stack)%STACK_SIZE);
            break;

         case Display:
            // c = chooseComplexNumberTo("display")?c1:c0;
            display();
            break;  

         case Move:
            // c = chooseComplexNumberTo("Move")?(c1 = moveComplex(&cResult)):(c0 = moveComplex(&cResult));
            moveComplex(stack);
            break; 

         case Conjugate:
            // c = chooseComplexNumberTo("Conjugate")?(c1 = complexConjugate(&c1)):(c0 = complexConjugate(&c0));
            complexConjugate(stack);
            break;

         case Add:
            // cResult = add(&c1, &c0);
            add(stack);
            break;      

         case Subtract:
            // cResult = subtract(&c1, &c0);
            subtract(stack);
            break;

         case Multiply:
            // cResult = multiply(&c1, &c0);
            multiply(stack);
            break;

         case Divide:
            // cResult = divide(&c1, &c0); 
            divide(stack);
            break;        

         default:
            printf("Bad menu value entered; ");
      }
      printf("\n");
}

// DO NOT CHANGE THIS FUNCTION
Complex loadComplex(){
   Complex cTemp; char sign; char i;
    printf("\tEnter complex number as 'a + Bi' (e.g. 3.4 - 27.1i) : ");
    scanf("%lf %c %lf%c", &cTemp.real, &sign, &cTemp.imag, &i);
    if (sign=='-') cTemp.imag = -cTemp.imag;
    fflush(stdin);
    return cTemp;
}

// TODO: add all additional funtions here, as specified above in the executeMenuItem() method.

char display(){
   
   // int index = top;
   for (int i = 0; i < STACK_SIZE; i++){
      if ((*(stack+(i%STACK_SIZE))).imag < 0){
         printf("Index = %i\t%lf - %lfi\n", i, (*(stack+(i%STACK_SIZE))).real, (-1 * (*(stack+(i%STACK_SIZE))).imag));
      }else{
         printf("Index = %i\t%lf + %lfi\n", i, (*(stack+(i%STACK_SIZE))).real, (*(stack+(i%STACK_SIZE))).imag);
      }
      // index++;
   }
}

Complex complexConjugate(Complex *c){
   Complex result;
   (*(c+(top%STACK_SIZE))).real = (*(c+(top%STACK_SIZE))).real;
   (*(c+(top%STACK_SIZE))).imag = -1 * (*(c+(top%STACK_SIZE))).imag;
   return result;
}

Complex add(Complex *c) {
   // (*(head+(%STACK_SIZE))).real = (*head).real + (*(head+(-1%STACK_SIZE))).real;
   // (*(head+(-1%STACK_SIZE))).imag = (*head).imag + (*(head+(-1%STACK_SIZE))).imag;
   // (*(c+(top%STACK_SIZE))).imag = 0;
   // (*(c+(top%STACK_SIZE))).real = 0;
   // head--;

   (*(c+((top-1)%STACK_SIZE))).real = (*(c+(top%STACK_SIZE))).real + (*(c+((top-1)%STACK_SIZE))).real;
   (*(c+((top-1)%STACK_SIZE))).imag = (*(c+(top%STACK_SIZE))).imag + (*(c+((top-1)%STACK_SIZE))).imag;
   (*(c+(top%STACK_SIZE))).imag = 0;
   (*(c+(top%STACK_SIZE))).real = 0;
   top--;
   return *(c+((top-1)%STACK_SIZE));
}

Complex subtract(Complex *c) {
   (*(c+((top-1)%STACK_SIZE))).real = (*(c+(top%STACK_SIZE))).real - (*(c+((top-1)%STACK_SIZE))).real;
   (*(c+((top-1)%STACK_SIZE))).imag = (*(c+(top%STACK_SIZE))).imag - (*(c+((top-1)%STACK_SIZE))).imag;
   (*(c+(top%STACK_SIZE))).imag = 0;
   (*(c+(top%STACK_SIZE))).real = 0;
   top--;
   return *(c+((top-1)%STACK_SIZE));
}

Complex divide(Complex *c) {
   double denominator = ((*(c+(top%STACK_SIZE))).real * (*(c+(top%STACK_SIZE))).real) + ((*(c+(top%STACK_SIZE))).imag * (*(c+(top%STACK_SIZE))).imag);
   assert(denominator != 0 && "Denominator should not be zero");
   (*(c+((top-1)%STACK_SIZE))).real = (((*(c+(top%STACK_SIZE))).real * (*(c+((top-1)%STACK_SIZE))).real) + ((*(c+(top%STACK_SIZE))).imag * (*(c+((top-1)%STACK_SIZE))).imag))/denominator;
   // result.real = ((c0.real*c1.real) + (c1.imag*c0.imag))/denominator;
   (*(c+((top-1)%STACK_SIZE))).imag = (((*(c+((top-1)%STACK_SIZE))).real * (*(c+(top%STACK_SIZE))).imag) - ((*(c+(top%STACK_SIZE))).real * (*(c+((top-1)%STACK_SIZE))).imag))/denominator;
   // result.imag = ((c0.real*c1.imag) - (c1.real*c0.imag))/denominator;
   (*(c+(top%STACK_SIZE))).imag = 0;
   (*(c+(top%STACK_SIZE))).real = 0;
   top--;
   return *(c+((top-1)%STACK_SIZE));
}

Complex multiply(Complex *c) {
   (*(c+((top-1)%STACK_SIZE))).real = ((*(c+(top%STACK_SIZE))).real*(*(c+((top-1)%STACK_SIZE))).real) - ((*(c+(top%STACK_SIZE))).imag*(*(c+((top-1)%STACK_SIZE))).imag);
   // result.real = (c1.real*c0.real) - (c1.imag*c0.imag);
   // result.imag = (c1.real*c0.imag) + (c0.real*c1.imag);
   (*(c+((top-1)%STACK_SIZE))).imag = ((*(c+(top%STACK_SIZE))).real*(*(c+((top-1)%STACK_SIZE))).imag) + ((*(c+((top-1)%STACK_SIZE))).real*(*(c+(top%STACK_SIZE))).imag);
   (*(c+(top%STACK_SIZE))).imag = 0;
   (*(c+(top%STACK_SIZE))).real = 0;
   top--;
   return *(c+((top-1)%STACK_SIZE));
}

Complex moveComplex(Complex *c){
   // top++;
   Complex result;
   result.real = (*(c+((top)%STACK_SIZE))).real;
   result.imag = (*(c+((top)%STACK_SIZE))).imag;
   push(result);
   return result;
}