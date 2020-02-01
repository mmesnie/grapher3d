#include <stdio.h>
#include <strings.h>

#define MAX_TOKEN_LENGTH 100
#define MAX_TOKENS 100
#define REAL 0
#define VARIABLE 1
#define FUNCTION 2
#define OPERATOR 3
#define OPEN_PAREN 4
#define CLOSE_PAREN 5
#define NO_PRIORITY -13
 
typedef struct {
  char token[MAX_TOKEN_LENGTH];
  int type;
  int priority;
} TOKEN_TYPE;

/*
void main() {
  char infix[100];
  char postfix[100];
  int result;
  int i;
 
  scanf("%s", infix);
  result = infix2postfix(infix, postfix);
  if (result <= 0) { 
    fprintf(stderr, "parsing error: %s\n", infix);
    fprintf(stderr, "               ");
    for (i=0;i<-result;i++) {
      fprintf(stderr, " ");
    }
    fprintf(stderr, "^\n");
  } else {
    printf("postfix = %s\n", postfix);
  }
}
*/

TOKEN_TYPE tokens[MAX_TOKENS];
TOKEN_TYPE scalar_stack[MAX_TOKENS]; 
TOKEN_TYPE operator_stack[MAX_TOKENS]; 
int num_tokens;
int num_scalars;
int num_operators;

int infix2postfix(char *infix, char* postfix) {
  int i;

  num_tokens = 0;
  num_scalars = 0;
  num_operators = 0;
 
  /* Step 1:  parse infix string into tokens */

  num_tokens = get_tokens(infix, tokens);
  if (num_tokens < 0) {
    return(num_tokens);
  }

  /* Step 2: parse each token */

  for(i=0;i<num_tokens;i++) {

    switch (tokens[i].type) {
      case REAL:
        scalar_stack[num_scalars] = tokens[i]; num_scalars++;
        break;
      case VARIABLE:
        scalar_stack[num_scalars] = tokens[i]; num_scalars++;
        break;
      case OPERATOR:
        pop_until(tokens[i].priority);
        operator_stack[num_operators] = tokens[i]; num_operators++;
        break;
      case FUNCTION:
        pop_until(tokens[i].priority);
        operator_stack[num_operators] = tokens[i]; num_operators++;
        break;
      case OPEN_PAREN:
        operator_stack[num_operators] = tokens[i]; num_operators++;
        break;
      case CLOSE_PAREN:
        pop_until(tokens[i].priority);
        break;
    }
  } 
  pop_until(NO_PRIORITY);

  /* Step 3: output scalar stack */

  if (num_operators!=0) {
    printf("operator stack has %i elements!!!!\n", num_operators); 
  } 
  if (num_scalars>1) {
    printf("scalar stack has %i elements!!!!\n", num_scalars); 
  } 

  #ifdef DEBUG_INFIX
  printf("final scalar stack:\n");
  print_tokens(scalar_stack, num_scalars);
  printf("operator stack:\n");
  print_tokens(operator_stack, num_operators);
  #endif

  strcpy(postfix, scalar_stack[num_scalars-1].token);
  return 1;
}

int pop_until(int priority) {
  char *arg1;
  char *arg2;
  char *op;
  char result[MAX_TOKEN_LENGTH];
  int i = num_operators;
  int done=0;

  while (!done) {
    if (num_operators == 0) {
      done = 1;
      break;
    }
    if (operator_stack[num_operators-1].priority < priority) {
      done = 1;
      break;
    }
    switch (operator_stack[num_operators-1].type) {
      case OPEN_PAREN:
        num_operators--;
        done = 1;
        break;
      case OPERATOR:
        arg1 = scalar_stack[num_scalars-1].token; num_scalars--;
        if (num_scalars==0) {
          fprintf(stderr, "parsing error: unexpected end of input\n"); 
          return(-1); 
        }
        arg2 = scalar_stack[num_scalars-1].token; num_scalars--;
        strcpy(result, arg2); 
        strcat(result, arg1); 
        break;
      case FUNCTION:
        arg1 = scalar_stack[num_scalars-1].token; num_scalars--;
        strcpy(result, arg1); 
        break;
    }
    if (!done) {
      op = operator_stack[num_operators-1].token; num_operators--;
      strcat(result, op); 
      strcpy(scalar_stack[num_scalars].token, result);
      num_scalars++;
    }
  }
  return 0;
} 

int print_tokens(TOKEN_TYPE *array, int count) {
  int i;

  for (i=0;i<count;i++) {
    printf("%s\n", array[i].token);
  }
  return 0;
}

int get_tokens(char *infix, TOKEN_TYPE *tokens) {
  int index;
  int length;
  int count;
  char function[MAX_TOKEN_LENGTH];
  char real[MAX_TOKEN_LENGTH];
  char c;
  int i;
  int decimal_point_flag;
  int leading_zero_flag;
  int parenthesis = 0;
  int last_type = -1;
  int current_type;

  length = strlen(infix);
  index = 0;
  count = 0;

  for(index=0; index<length; index++) {
    c = infix[index];
    if ((isdigit(c))||(c=='.')) {
      if (c=='.') {
        real[0] = '0';
        i=1;
        decimal_point_flag = 1;
        real[i] = c; i++; index++;
      } else {
        i=0;
        decimal_point_flag = 0;
        real[i] = c; i++; index++;
      }
      while (index < length) {
        c = infix[index];
        if (isdigit(c)||(c=='.')) {
          if (c=='.') {
            if (decimal_point_flag) { 
              real[i] = '\0'; 
              fprintf(stderr, "parsing error: badly formed number\n");
              return(-(index-1)); 
            } else {
              decimal_point_flag = 1;
            }
          } 
          real[i] = c; i++; index++;
        } else {  
          break;
        }
      }
      if (!decimal_point_flag) { 
        real[i] = '.'; i++;
        real[i] = '0'; i++; 
      }
      real[i] = '\0';
      strcat(real, "#");
      strcpy(tokens[count].token, real); 
      tokens[count].type = REAL; 
      tokens[count].priority = NO_PRIORITY ; 
      index--;
    } else {
      switch (c) {
        case ' ':
          count--;
          break;
        case 'x':
          strcpy(tokens[count].token, "x"); 
          tokens[count].type = VARIABLE; 
          tokens[count].priority = NO_PRIORITY ; 
          break;
        case 'y':
          strcpy(tokens[count].token, "y"); 
          tokens[count].type = VARIABLE; 
          tokens[count].priority = NO_PRIORITY ; 
          break;
        case '+':
          if ((last_type == OPEN_PAREN)||(last_type==-1)||(last_type==OPERATOR)) {
            tokens[count].type = FUNCTION; 
          } else {
            strcpy(tokens[count].token, "+"); 
            tokens[count].type = OPERATOR; 
            tokens[count].priority = 1; 
          }
          break;
        case '-':
          if ((last_type == OPEN_PAREN)||(last_type==-1)||(last_type==OPERATOR)) {
            strcpy(tokens[count].token, "n"); 
            tokens[count].type = FUNCTION; 
            tokens[count].priority = 4; 
          } else {
            strcpy(tokens[count].token, "-"); 
            tokens[count].type = OPERATOR; 
            tokens[count].priority = 1; 
          }
          break;
        case '*':
          strcpy(tokens[count].token, "*"); 
          tokens[count].type = OPERATOR; 
          tokens[count].priority = 2; 
          break;
        case '/':
          strcpy(tokens[count].token, "/"); 
          tokens[count].type = OPERATOR; 
          tokens[count].priority = 2; 
          break;
        case '^':
          strcpy(tokens[count].token, "^"); 
          tokens[count].type = OPERATOR; 
          tokens[count].priority = 3; 
          break;
        case '(':
          parenthesis++;
          strcpy(tokens[count].token, "("); 
          tokens[count].type = OPEN_PAREN; 
          tokens[count].priority = 0; 
          break;
        case ')':
          parenthesis--;
          if (parenthesis < 0) { 
            fprintf(stderr, "parsing error: unbalanced parenthesis\n");
            return(-index);
          }
          if (last_type == OPEN_PAREN) {
            fprintf(stderr, "parsing error: missing expression\n");
            return(-index);
          }
          strcpy(tokens[count].token, ")"); 
          tokens[count].type = CLOSE_PAREN; 
          tokens[count].priority = NO_PRIORITY; 
          break; 
        default :
          function[0] = c; i = 1; index++;
          while (1) {
            c = infix[index];
            if (isalpha(c)&&(index<length)) {
              function[i] = c; i++; index++;
            } else {
              index--;
              break;
            } 
          }
          function[i] = '\0'; 
          if (strcmp(function, "sin")==0) {
            strcpy(tokens[count].token, "s"); 
          } else if (strcmp(function, "abs")==0) {
            strcpy(tokens[count].token, "a"); 
          } else if (strcmp(function, "ln")==0) {
            strcpy(tokens[count].token, "l"); 
          } else if (strcmp(function, "sqrt")==0) {
            strcpy(tokens[count].token, "q"); 
          } else if (strcmp(function, "cos")==0) {
            strcpy(tokens[count].token, "c"); 
          } else if (strcmp(function, "exp")==0) {
            strcpy(tokens[count].token, "e"); 
          } else if (strcmp(function, "tan")==0) {
            strcpy(tokens[count].token, "t"); 
          } else {
            fprintf(stderr, "parsing error: undefined function: %s\n", function);
            return(-index);
          } 
          tokens[count].type = FUNCTION; 
          tokens[count].priority = 4; 
          break;
      }
    }
    current_type = tokens[count].type;
    #ifdef DEBUG_INFIX
    printf("current = %i\n", current_type);
    printf("last = %i\n", last_type);
    #endif
    if ((((current_type!=CLOSE_PAREN)&&(current_type!=OPERATOR))&&((last_type==VARIABLE)||(last_type==REAL)))||
         (((current_type!=OPERATOR)&&(current_type!=CLOSE_PAREN))&&(last_type==CLOSE_PAREN))) {
      if (current_type==FUNCTION) {
        index -= strlen(function)-1; 
      }
      printf("parsing error: missing operator\n");
      return(-index);
    }
    last_type = current_type;
    count++;
  } 
  if (parenthesis != 0) { 
    fprintf(stderr, "parsing error: unbalanced parentheses\n");
    return(-length);
  }
  if ((last_type == OPERATOR)||(last_type == FUNCTION)) {
    fprintf(stderr, "parsing error: unexpected end of input\n");
    return(-length);
  }
  return count;
}
