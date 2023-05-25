%{
  #include<stdio.h>
  #include<string.h>
  #include<ctype.h>
  char lexema[255];
  void yyerror(char *);
  int yylex();
  int IsReservedWord(char[], int);
%}

%token VAR INTCONST DOUBLECONST STRINGCONST
%token PLUS MINUS TIMES DIVIDE EQUALS PERCENT UMINUS
%token COMMA LPAREN RPAREN LBRACKET RBRACKET
%token LESSTHAN LESSEQUAL GREATERTHAN GREATEREQUAL EQUALITY NOTEQUALITY
%token INT DOUBLE
%token INPUT OUTPUT
%token SUBROUTINE ENDSUBROUTINE RETURN
%token IF THEN ELSE ENDIF
%token WHILE DO ENDWHILE
%token FOR TO ENDFOR

%start stmt_list

%%
stmt_list: simple_stmt
         | stmt_list simple_stmt;

simple_stmt: assig_stmt
           | array_decl_stmt
           | var_decl_stmt
           | if_stmt
           | while_stmt
           | for_stmt
           | output_stmt
           | input_stmt
           | function_stmt
           | return_stmt;

if_stmt: IF exp THEN stmt_list ENDIF
       | IF exp THEN stmt_list ELSE stmt_list ENDIF;

while_stmt: WHILE exp DO stmt_list ENDWHILE;

for_stmt: FOR assig_stmt TO INTCONST stmt_list ENDFOR;

array_decl_stmt: DOUBLE array_index
               | INT array_index;

var_decl_stmt: DOUBLE var_list
             | INT var_list;
var_list: VAR
        | var_list COMMA VAR;

assig_stmt: VAR EQUALS exp
          | array_index EQUALS exp;

input_stmt: INPUT VAR
          | INPUT array_index;
output_stmt : OUTPUT exp;
return_stmt : RETURN exp;

function_header : INT SUBROUTINE VAR LPAREN arg_list RPAREN
                | DOUBLE SUBROUTINE VAR LPAREN arg_list RPAREN
                | INT SUBROUTINE VAR LPAREN RPAREN
                | DOUBLE SUBROUTINE VAR LPAREN RPAREN;
function_stmt : function_header stmt_list ENDSUBROUTINE;
exp_fun_call: VAR LPAREN exp RPAREN
            | VAR LPAREN expr_list RPAREN
            | VAR LPAREN RPAREN;
arg_list : INT VAR
         | DOUBLE VAR
         | arg_list COMMA INT VAR
         | arg_list COMMA DOUBLE VAR;

expr_list : exp COMMA exp
          | expr_list COMMA exp;

exp: exp EQUALITY term
   | exp NOTEQUALITY term
   | term;
term: term LESSTHAN exp_arit
    | term GREATERTHAN exp_arit
    | term LESSEQUAL exp_arit
    | term GREATEREQUAL exp_arit
    | exp_arit;
exp_arit: exp_arit PLUS term_arit1
        | exp_arit MINUS term_arit1
        | term_arit1;
term_arit1: term_arit1 TIMES term_arit2
          | term_arit1 DIVIDE term_arit2
          | term_arit1 PERCENT term_arit2
          | term_arit2;
term_arit2: MINUS term_arit2 %prec UMINUS
          | term_arit3;
term_arit3: LPAREN exp RPAREN
          | INTCONST
          | DOUBLECONST
          | STRINGCONST
          | VAR
          | array_index
          | exp_fun_call;

array_index: VAR LBRACKET INTCONST RBRACKET;

// exp_literal: INTCONST;
//            | DOUBLECONST;
//            | STRINGCONST;
%%

void yyerror(char *msg) {
  printf("error: %s", msg);
}

int IsReservedWord(char lexema[], int default_token) {
  //strcmp considera mayusculas y minusculas
  //strcasecmp ignora mayusculas de minusculas
  if(strcmp(lexema,"ENTERO") == 0) return INT;
  if(strcmp(lexema,"DECIMAL") == 0) return DOUBLE;
  if(strcmp(lexema,"ENTRADA") == 0) return INPUT;
  if(strcmp(lexema,"SALIDA") == 0) return OUTPUT;
  if(strcmp(lexema,"SUBRUTINA") == 0) return SUBROUTINE;
  if(strcmp(lexema,"FINSUBRUTINA") == 0) return ENDSUBROUTINE;
  if(strcmp(lexema,"DEVOLVER") == 0) return RETURN;
  if(strcmp(lexema,"SI") == 0) return IF;
  if(strcmp(lexema,"ENTONCES") == 0) return THEN;
  if(strcmp(lexema,"SINO") == 0) return ELSE;
  if(strcmp(lexema,"FINSI") == 0) return ENDIF;
  if(strcmp(lexema,"MIENTRAS") == 0) return WHILE;
  if(strcmp(lexema,"HACER") == 0) return DO;
  if(strcmp(lexema,"FINMIENTRAS") == 0) return ENDWHILE;
  if(strcmp(lexema,"PARA") == 0) return FOR;
  if(strcmp(lexema,"HASTA") == 0) return TO;
  if(strcmp(lexema,"FINPARA") == 0) return ENDFOR;
  return default_token;
}

// Especificamos las reglas de los tokens
int yylex() {
  char c;
  while(1) {
    c = getchar();

    if(c == '\t') continue;
    if(c == ' ') continue;
    if(isspace(c)) continue;

    if(c == '+') return PLUS;
    if(c == '-') return MINUS;
    if(c == '*') return TIMES;
    if(c == '/') return DIVIDE;
    if(c == '=') return EQUALS;
    if(c == '%') return PERCENT;

    if(c == '<') return LESSTHAN;
    if(c == '>') return GREATERTHAN;

    char LESS_EQUAL[] = "<=";
    if(c == LESS_EQUAL[0]) {
      int i = 0, j = 0;
      do {
        lexema[i++] = c;
        c = getchar();
        j++;
      } while (c == LESS_EQUAL[j] && j < 2);
      if(j == 2) {
        ungetc(c, stdin);
        lexema[i] = 0;
        return LESSEQUAL;
      }
    }

    char GREATER_EQUAL[] = ">=";
    if(c == GREATER_EQUAL[0]) {
      int i = 0, j = 0;
      do {
        lexema[i++] = c;
        c = getchar();
        j++;
      } while (c == GREATER_EQUAL[j] && j < 2);
      if(j == 2) {
        ungetc(c, stdin);
        lexema[i] = 0;
        return GREATEREQUAL;
      }
    }

    char EQUALITYT[] = "==";
    if(c == EQUALITYT[0]) {
      int i = 0, j = 0;
      do {
        lexema[i++] = c;
        c = getchar();
        j++;
      } while (c == EQUALITYT[j] && j < 2);
      if(j == 2) {
        ungetc(c, stdin);
        lexema[i] = 0;
        return EQUALITY;
      }
    }

    char NOTEQUALITYT[] = "<>";
    if(c == NOTEQUALITYT[0]) {
      int i = 0, j = 0;
      do {
        lexema[i++] = c;
        c = getchar();
        j++;
      } while (c == NOTEQUALITYT[j] && j < 2);
      if(j == 2) {
        ungetc(c, stdin);
        lexema[i] = 0;
        return NOTEQUALITY;
      }
    }

    if(c == '(') return LPAREN;
    if(c == ')') return RPAREN;
    if(c == '[') return LBRACKET;
    if(c == ']') return RBRACKET;

    if(c == ',') return COMMA;

    if(c == 34) {
      int i = 0;
      do {
        lexema[i++] = c;
        c = getchar();
      } while(c != 34);
      if(c == 34) {
        lexema[i++] = c;
        c = getchar();
      }
      ungetc(c, stdin);
      lexema[i] = 0;
      return STRINGCONST;
    }

    if(isalpha(c) || c == '_'){
      int i = 0;
      do {
        lexema[i++] = c;
        c = getchar();
      } while(isalnum(c) || c == '_');
      ungetc(c, stdin);
      lexema[i] = '\0';
      return IsReservedWord(lexema, VAR);
    }

    if(isdigit(c)) {
      int i = 0;
      do {
        lexema[i++] = c;
        c = getchar();
      } while(isdigit(c));
      if(c == '.') {
        lexema[i++] = c;
        c = getchar();
        if(isdigit(c)) {
          do {
            lexema[i++] = c;
            c = getchar();
          } while(isdigit(c));
          ungetc(c, stdin);
          lexema[i] = 0;
          return DOUBLECONST;
        }
        ungetc(c, stdin);
        lexema[i] = 0;
        return DOUBLECONST;
      }
      ungetc(c, stdin);
      lexema[i] = 0;
      return INTCONST;
    }

    return c;
  }
}

int main() {
  if(!yyparse()) printf("cadena valida\n");
  else printf("\ncadena invalida\n");
  return 0;
}