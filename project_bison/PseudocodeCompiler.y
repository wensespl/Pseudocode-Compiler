%{
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include <ctype.h>
  #define YYSTYPE double /* double type for YACC stack */
  char lexema[255];
  void yyerror(char *msg);

  typedef struct {
    char nombre[60];
    double valor;
    int token;
	} tipoTS;
  tipoTS TablaSim[100];
  int nSim = 0;

  typedef struct {
    int op;
    int a1;
    int a2;
    int a3;
  } tipoCodigo;
  int cx = -1;
  tipoCodigo TCodigo[100];
  void generaCodigo(int, int, int, int);

  int localizaSimb(char *, int);
  void imprimeTablaSim();

  void imprimeTablaCod();
  int nVarTemp = 0;
  int GenVarTemp();

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
%token ASIGNAR SUMAR RESTAR MULTIPLICAR DIVIDIR PORCENTAJE PARENTESIS

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
       | IF exp THEN stmt_list ELSE stmt_list ENDIF
       | IF exp THEN stmt_list ELSE if_stmt;

while_stmt: WHILE exp DO stmt_list ENDWHILE;

for_stmt: FOR assig_stmt TO INTCONST { $$ = localizaSimb(lexema, INTCONST); } stmt_list ENDFOR;

array_decl_stmt: DOUBLE array_index
               | INT array_index;

var_decl_stmt: DOUBLE var_list
             | INT var_list;
var_list: VAR { $$ = localizaSimb(lexema, VAR); }
        | var_list COMMA VAR { $$ = localizaSimb(lexema, VAR); };

assig_stmt: VAR { $$ = localizaSimb(lexema, VAR); } EQUALS exp { generaCodigo(ASIGNAR, $2, $4, '-'); }
          | array_index EQUALS exp;

input_stmt: INPUT VAR { $$ = localizaSimb(lexema, VAR); }
          | INPUT array_index;
output_stmt: OUTPUT exp;
return_stmt: RETURN exp;

function_header: INT SUBROUTINE VAR LPAREN arg_list RPAREN
               | DOUBLE SUBROUTINE VAR LPAREN arg_list RPAREN
               | INT SUBROUTINE VAR LPAREN RPAREN
               | DOUBLE SUBROUTINE VAR LPAREN RPAREN;
function_stmt: function_header stmt_list ENDSUBROUTINE;
exp_fun_call: VAR LPAREN exp RPAREN
            | VAR LPAREN expr_list RPAREN
            | VAR LPAREN RPAREN;
arg_list: INT VAR
        | DOUBLE VAR
        | arg_list COMMA INT VAR
        | arg_list COMMA DOUBLE VAR;

expr_list: exp COMMA exp
         | expr_list COMMA exp;

array_index: VAR LBRACKET INTCONST RBRACKET;

exp: exp EQUALITY term
   | exp NOTEQUALITY term
   | term;
term: term LESSTHAN exp_arit
    | term GREATERTHAN exp_arit
    | term LESSEQUAL exp_arit
    | term GREATEREQUAL exp_arit
    | exp_arit;
exp_arit: exp_arit PLUS term_arit1 {
                                      int i = GenVarTemp(); 
                                      generaCodigo(SUMAR, i, $1, $3); 
                                      $$ = i;
                                   }
        | exp_arit MINUS term_arit1 {
                                      int i = GenVarTemp(); 
                                      generaCodigo(RESTAR, i, $1, $3); 
                                      $$ = i;
                                    }
        | term_arit1;
term_arit1: term_arit1 TIMES term_arit2 {
                                          int i = GenVarTemp(); 
                                          generaCodigo(MULTIPLICAR, i, $1, $3); 
                                          $$ = i;
                                        }
          | term_arit1 DIVIDE term_arit2 {
                                            int i = GenVarTemp(); 
                                            generaCodigo(DIVIDIR, i, $1, $3); 
                                            $$ = i;
                                         }
          | term_arit1 PERCENT term_arit2 {
                                            int i = GenVarTemp(); 
                                            generaCodigo(PORCENTAJE, i, $1, $3); 
                                            $$ = i;
                                         }
          | term_arit2;
term_arit2: MINUS term_arit2 %prec UMINUS { $$ = -$2; }
          | term_arit3;
term_arit3: LPAREN exp RPAREN {
                                int i = GenVarTemp(); 
                                generaCodigo(PARENTESIS, i, $2, '-'); 
                                $$ = i;
                              }
          | INTCONST { $$ = localizaSimb(lexema, INTCONST); }
          | DOUBLECONST { $$ = localizaSimb(lexema, DOUBLECONST); }
          | STRINGCONST
          | VAR { $$ = localizaSimb(lexema, VAR); }
          | array_index
          | exp_fun_call;
%%

int GenVarTemp(){
	char t[60];
	sprintf(t, "_T%d", nVarTemp++);
	return localizaSimb(t, VAR);
}

void generaCodigo(int op, int a1, int a2, int a3){
	cx++;	
	TCodigo[cx].op = op;
	TCodigo[cx].a1 = a1;
	TCodigo[cx].a2 = a2;
	TCodigo[cx].a3 = a3;
}

int localizaSimb(char *nom, int tok) {
	int i;
	for(i = 0; i < nSim; i++) {
		if(!strcasecmp(TablaSim[i].nombre, nom)) 
			return i;
	}
	strcpy(TablaSim[nSim].nombre, nom);
	TablaSim[nSim].token = tok;
	if(tok == VAR) TablaSim[nSim].valor = 0.0;
	if(tok == INTCONST) sscanf(nom, "%lf", &TablaSim[nSim].valor);
  if(tok == DOUBLECONST) sscanf(nom, "%lf", &TablaSim[nSim].valor);
	nSim++;
	return nSim - 1;
}

void imprimeTablaSim(){
	int i;
	for(i = 0; i < nSim; i++) {
		printf("%4d  nombre=%6s tok=%5d valor=%4.3lf\n", i, TablaSim[i].nombre, TablaSim[i].token, TablaSim[i].valor);
	}
}

void imprimeTablaCod(){
	int i;
	for(i = 0; i <= cx; i++){
		printf("op=%5d  a1=%4d a2=%4d a3=%4d\n", TCodigo[i].op, TCodigo[i].a1, TCodigo[i].a2, TCodigo[i].a3);
	}
}

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

int yylex() {
  char c;
  while(1) {
    c = getchar();

    if(c == ' ') continue;
		if(c == '\t') continue;
		if(c == '\n') continue;
    // if(isspace(c)) continue;

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
        lexema[i] = '\0';
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
        lexema[i] = '\0';
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
        lexema[i] = '\0';
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
        lexema[i] = '\0';
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
      lexema[i] = '\0';
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
          lexema[i] = '\0';
          yylval = atof(lexema);
          return DOUBLECONST;
        }
        ungetc(c, stdin);
        lexema[i] = '\0';
        yylval = atof(lexema);
        return DOUBLECONST;
      }
      ungetc(c, stdin);
      lexema[i] = '\0';
      yylval = atoi(lexema);
      return INTCONST;
    }

    return c;
  }
}

int main() {
  // return yyparse();
  if(!yyparse()) printf("cadena valida\n");
  else printf("cadena invalida\n");
  printf("tabla de simbolos\n");
	imprimeTablaSim();
  printf("tabla de codigos\n");
	imprimeTablaCod();
  return 0;
}