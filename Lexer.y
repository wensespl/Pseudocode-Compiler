%{
  #include<stdio.h>
  #include<string.h>
  #include<ctype.h>
  char lexema[255];
  void yyerror(char *);
%}

// Especificamos los tokens
%token VAR INT_CONST DOUBLE_CONST STRING_CONST PLUS MINUS TIMES DIVIDE EQUALS PERCENT COMMA NEWLINE LPAREN RPAREN LBRACKET RBRACKET LESS_THAN LESS_EQUAL GREATER_THAN GREATER_EQUAL EQUALITY NOT_EQUALITY INT DOUBLE INPUT OUTPUT SUBROUTINE ENDSUBROUTINE RETURN IF THEN ELSE ENDIF WHILE DO ENDWHILE FOR TO ENDFOR

// Especificamos la gramatica
%%
statement : stmt_list;
stmt_list : simple_stmt
          | stmt_list NEWLINE simple_stmt;
if_stmt : IF expression THEN NEWLINE stmt_list NEWLINE ENDIF
        | IF expression THEN NEWLINE stmt_list NEWLINE ELSE NEWLINE stmt_list NEWLINE ENDIF
        | IF expression THEN NEWLINE stmt_list NEWLINE ELSE if_stmt;
while_stmt : WHILE expression DO NEWLINE stmt_list NEWLINE ENDWHILE;
for_stmt : FOR assignment_stmt TO expression NEWLINE stmt_list NEWLINE ENDFOR;
simple_stmt : expression
            | expr_list
            | arg_list
            | assignment_stmt
            | array_decl_stmt
            | if_stmt
            | while_stmt
            | for_stmt
            | output_stmt
            | input_stmt
            | function_stmt
            | return_stmt;
array_decl_stmt : DOUBLE array_index
                | INT array_index;
assignment_stmt : VAR EQUALS expression;
assignment_stmt : array_index EQUALS expression;
input_stmt : INPUT VAR
           | INPUT array_index;
output_stmt : OUTPUT expression;
return_stmt : RETURN expression;
function_header : INT SUBROUTINE VAR LPAREN arg_list RPAREN
                | DOUBLE SUBROUTINE VAR LPAREN arg_list RPAREN
                | INT SUBROUTINE VAR LPAREN RPAREN
                | DOUBLE SUBROUTINE VAR LPAREN RPAREN;
function_stmt : function_header NEWLINE stmt_list NEWLINE ENDSUBROUTINE;
arg_list : INT VAR
         | DOUBLE VAR
         | arg_list COMMA INT VAR
         | arg_list COMMA DOUBLE VAR;
expr_list : expression COMMA expression
          | expr_list COMMA expression;
expression : expression PLUS expression
           | expression MINUS expression
           | expression TIMES expression
           | expression DIVIDE expression
           | expression PERCENT expression;
expression : expression LESS_THAN expression
           | expression GREATER_THAN expression
           | expression LESS_EQUAL expression
           | expression GREATER_EQUAL expression
           | expression EQUALITY expression
           | expression NOT_EQUALITY expression;
expression : LPAREN expression RPAREN;
expression : VAR LPAREN expression RPAREN
           | VAR LPAREN expr_list RPAREN
           | VAR LPAREN RPAREN;
expression : array_index;
array_index : VAR LBRACKET expression RBRACKET;
expression : literal;
literal : INT_CONST;
literal : DOUBLE_CONST;
literal : STRING_CONST;
expression : VAR;
%%

void yyerror(char *msg) {
  printf("error: %s", msg);
}

// Especificamos las reglas de los tokens
int yylex() {
  char c;
  while(1) {
    c = getchar();

    if(c == '\t') continue;
    if(isspace(c)) continue;

    if(c == '+') return PLUS;
    if(c == '-') return MINUS;
    if(c == '*') return TIMES;
    if(c == '/') return DIVIDE;
    if(c == '=') return EQUALS;
    if(c == '%') return PERCENT;

    if(c == '<') return LESS_THAN;
    if(c == '>') return GREATER_THAN;

    char LESSEQUAL[] = "<=";
    if(c == LESSEQUAL[0]) {
      int i = 0, j = 0;
      do {
        lexema[i++] = c;
        c = getchar();
        j++;
      } while (c == LESSEQUAL[j] && j < 2);
      if(j == 2) {
        ungetc(c, stdin);
        lexema[i] == 0;
        return LESS_EQUAL;
      }
    }

    char GREATEREQUAL[] = ">=";
    if(c == GREATEREQUAL[0]) {
      int i = 0, j = 0;
      do {
        lexema[i++] = c;
        c = getchar();
        j++;
      } while (c == GREATEREQUAL[j] && j < 2);
      if(j == 2) {
        ungetc(c, stdin);
        lexema[i] == 0;
        return GREATER_EQUAL;
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
        lexema[i] == 0;
        return EQUALITY;
      }
    }

    char NOTEQUALITY[] = "<>";
    if(c == NOTEQUALITY[0]) {
      int i = 0, j = 0;
      do {
        lexema[i++] = c;
        c = getchar();
        j++;
      } while (c == NOTEQUALITY[j] && j < 2);
      if(j == 2) {
        ungetc(c, stdin);
        lexema[i] == 0;
        return NOT_EQUALITY;
      }
    }

    if(c == '(') return LPAREN;
    if(c == ')') return RPAREN;
    if(c == '[') return LBRACKET;
    if(c == ']') return RBRACKET;

    if(c == ',') return COMMA;

    char ENTERO[] = "ENTERO";
    if(c == ENTERO[0]) {
      int i = 0, j = 0;
      do {
        lexema[i++] = c;
        c = getchar();
        j++;
      } while (c == ENTERO[j] && j < 6);
      if(j == 6) {
        ungetc(c, stdin);
        lexema[i] == 0;
        return INT;
      }
    }

    char DECIMAL[] = "DECIMAL";
    if(c == DECIMAL[0]) {
      int i = 0, j = 0;
      do {
        lexema[i++] = c;
        c = getchar();
        j++;
      } while (c == DECIMAL[j] && j < 7);
      if(j == 7) {
        ungetc(c, stdin);
        lexema[i] == 0;
        return DOUBLE;
      }
    }

    char ENTRADA[] = "ENTRADA";
    if(c == ENTRADA[0]) {
      int i = 0, j = 0;
      do {
        lexema[i++] = c;
        c = getchar();
        j++;
      } while (c == ENTRADA[j] && j < 7);
      if(j == 7) {
        ungetc(c, stdin);
        lexema[i] == 0;
        return INPUT;
      }
    }

    char SALIDA[] = "SALIDA";
    if(c == SALIDA[0]) {
      int i = 0, j = 0;
      do {
        lexema[i++] = c;
        c = getchar();
        j++;
      } while (c == SALIDA[j] && j < 6);
      if(j == 6) {
        ungetc(c, stdin);
        lexema[i] == 0;
        return OUTPUT;
      }
    }

    char SUBRUTINA[] = "SUBRUTINA";
    if(c == SUBRUTINA[0]) {
      int i = 0, j = 0;
      do {
        lexema[i++] = c;
        c = getchar();
        j++;
      } while (c == SUBRUTINA[j] && j < 9);
      if(j == 9) {
        ungetc(c, stdin);
        lexema[i] == 0;
        return SUBROUTINE;
      }
    }

    char FINSUBRUTINA[] = "FINSUBRUTINA";
    if(c == FINSUBRUTINA[0]) {
      int i = 0, j = 0;
      do {
        lexema[i++] = c;
        c = getchar();
        j++;
      } while (c == FINSUBRUTINA[j] && j < 12);
      if(j == 12) {
        ungetc(c, stdin);
        lexema[i] == 0;
        return ENDSUBROUTINE;
      }
    }

    char DEVOLVER[] = "DEVOLVER";
    if(c == DEVOLVER[0]) {
      int i = 0, j = 0;
      do {
        lexema[i++] = c;
        c = getchar();
        j++;
      } while (c == DEVOLVER[j] && j < 8);
      if(j == 8) {
        ungetc(c, stdin);
        lexema[i] == 0;
        return RETURN;
      }
    }

    char SI[] = "SI";
    if(c == SI[0]) {
      int i = 0, j = 0;
      do {
        lexema[i++] = c;
        c = getchar();
        j++;
      } while (c == SI[j] && j < 2);
      if(j == 2) {
        ungetc(c, stdin);
        lexema[i] == 0;
        return IF;
      }
    }

    char ENTONCES[] = "ENTONCES";
    if(c == ENTONCES[0]) {
      int i = 0, j = 0;
      do {
        lexema[i++] = c;
        c = getchar();
        j++;
      } while (c == ENTONCES[j] && j < 8);
      if(j == 8) {
        ungetc(c, stdin);
        lexema[i] == 0;
        return THEN;
      }
    }

    char SINO[] = "SINO";
    if(c == SINO[0]) {
      int i = 0, j = 0;
      do {
        lexema[i++] = c;
        c = getchar();
        j++;
      } while (c == SINO[j] && j < 4);
      if(j == 4) {
        ungetc(c, stdin);
        lexema[i] == 0;
        return ELSE;
      }
    }

    char FINSI[] = "FINSI";
    if(c == FINSI[0]) {
      int i = 0, j = 0;
      do {
        lexema[i++] = c;
        c = getchar();
        j++;
      } while (c == FINSI[j] && j < 5);
      if(j == 5) {
        ungetc(c, stdin);
        lexema[i] == 0;
        return ENDIF;
      }
    }

    char MIENTRAS[] = "MIENTRAS";
    if(c == MIENTRAS[0]) {
      int i = 0, j = 0;
      do {
        lexema[i++] = c;
        c = getchar();
        j++;
      } while (c == MIENTRAS[j] && j < 8);
      if(j == 8) {
        ungetc(c, stdin);
        lexema[i] == 0;
        return WHILE;
      }
    }

    char HACER[] = "HACER";
    if(c == HACER[0]) {
      int i = 0, j = 0;
      do {
        lexema[i++] = c;
        c = getchar();
        j++;
      } while (c == HACER[j] && j < 5);
      if(j == 5) {
        ungetc(c, stdin);
        lexema[i] == 0;
        return DO;
      }
    }

    char FINMIENTRAS[] = "FINMIENTRAS";
    if(c == FINMIENTRAS[0]) {
      int i = 0, j = 0;
      do {
        lexema[i++] = c;
        c = getchar();
        j++;
      } while (c == FINMIENTRAS[j] && j < 11);
      if(j == 11) {
        ungetc(c, stdin);
        lexema[i] == 0;
        return ENDWHILE;
      }
    }

    char PARA[] = "PARA";
    if(c == PARA[0]) {
      int i = 0, j = 0;
      do {
        lexema[i++] = c;
        c = getchar();
        j++;
      } while (c == PARA[j] && j < 4);
      if(j == 4) {
        ungetc(c, stdin);
        lexema[i] == 0;
        return FOR;
      }
    }

    char HASTA[] = "HASTA";
    if(c == HASTA[0]) {
      int i = 0, j = 0;
      do {
        lexema[i++] = c;
        c = getchar();
        j++;
      } while (c == HASTA[j] && j < 5);
      if(j == 5) {
        ungetc(c, stdin);
        lexema[i] == 0;
        return TO;
      }
    }

    char FINPARA[] = "FINPARA";
    if(c == FINPARA[0]) {
      int i = 0, j = 0;
      do {
        lexema[i++] = c;
        c = getchar();
        j++;
      } while (c == FINPARA[j] && j < 7);
      if(j == 7) {
        ungetc(c, stdin);
        lexema[i] == 0;
        return ENDFOR;
      }
    }

    if(isalpha(c) || c == '_'){
      int i=0;
      do {
        lexema[i++] = c;
        c = getchar();
      } while(isalnum(c) || c == '_');
      ungetc(c, stdin);
      lexema[i] == 0;
      return VAR;
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
          lexema[i] == 0;
          return DOUBLE_CONST;
        }
      }
      ungetc(c, stdin);
      lexema[i] == 0;
      return INT_CONST;
    }

    if(c == '"') {
      int i=0;
      do {
        lexema[i++] = c;
        c = getchar();
      } while(c != '"');
      ungetc(c, stdin);
      lexema[i] == 0;
      return STRING_CONST;
    }

    if(c == '\n'){
      int i=0;
      do {
        lexema[i++] = c;
        c = getchar();
      } while(c == '\n');
      ungetc(c, stdin);
      lexema[i] == 0;
      return NEWLINE;
    }

    return c;
  }
}

int main() {
  if(!yyparse()) printf("cadena valida\n");
  else printf("\ncadena invalida\n");
  return 0;
}