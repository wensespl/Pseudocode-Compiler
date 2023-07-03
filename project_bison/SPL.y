%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
char lexema[60];
void yyerror(char *msg);
int yylex();

typedef struct {
  char nombre[60];
  double valor;
  int token;
  int tokenaux;
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

void generaCodigo(int,int,int,int);
int localizaSimb(char *, int);
void imprimeTablaSim();

int nVarTemp = 0;
int GenVarTemp();
void InterpretaCodigo();

int errorLine = 0;
%}

%token VAR INTCONST DOUBLECONST
%token OUTPUT
%token IF THEN ELSE ENDIF
%token WHILE DO ENDWHILE
%token FOR TO ENDFOR
%token IMPRIMIR
%token ASIGNAR SUMAR RESTAR MULTIPLICAR DIVIDIR PARENTESIS
%token SALTAR1 SALTAR2 SALTAR_FOR BUCLE_WHILE BUCLE_FOR
%token MAYOR MENOR IGUAL DESIGUAL MAYOR_IGUAL MENOR_IGUAL

%start stmt_list

%%
stmt_list: simple_stmt
         | stmt_list simple_stmt;

simple_stmt: assig_stmt
           | if_stmt
           | while_stmt
           | for_stmt
           | output_stmt;

if_stmt: IF cond {generaCodigo(SALTAR1,$2,'?','-');$$=cx;} THEN stmt_list {generaCodigo(SALTAR2,$2,'?','-');$$=cx;}{TCodigo[$3].a2=cx+1;} otro {TCodigo[$6].a2=cx+1;} ENDIF;
otro: ELSE stmt_list
    |  ;

while_stmt: WHILE cond {generaCodigo(SALTAR1,$2,'?','-');$$=cx;} DO stmt_list {generaCodigo(BUCLE_WHILE,$3,'-','-');}{TCodigo[$3].a2=cx+1;} ENDWHILE;

for_stmt: FOR VAR {$$=localizaSimb(lexema,VAR);} TO expr {generaCodigo(SALTAR_FOR,$3,$5,'?');$$=cx;} stmt_list {generaCodigo(BUCLE_FOR,$3,$6,'-');}{TCodigo[$6].a3=cx+1;} ENDFOR;

assig_stmt: VAR {$$=localizaSimb(lexema,VAR);} '=' expr {generaCodigo(ASIGNAR,$2,$4,'-');};

output_stmt: OUTPUT expr {generaCodigo(IMPRIMIR,$2,'-','-');};

cond: expr '=' '=' expr {
                          int i = GenVarTemp(); 
                          generaCodigo(IGUAL,i,$1,$4); 
                          $$=i;
                        }
    | expr '<' '>' expr {
                          int i = GenVarTemp(); 
                          generaCodigo(DESIGUAL,i,$1,$4); 
                          $$=i;
                        }
    | cond2;
cond2: expr '<' expr {
                        int i = GenVarTemp(); 
                        generaCodigo(MENOR,i,$1,$3); 
                        $$=i;
                      }
     | expr '<' '=' expr {
                            int i = GenVarTemp(); 
                            generaCodigo(MENOR_IGUAL,i,$1,$4); 
                            $$=i;
                          }
     | expr '>' expr {
                        int i = GenVarTemp(); 
                        generaCodigo(MAYOR,i,$1,$3); 
                        $$=i;
                      }
     | expr '>' '=' expr {
                            int i = GenVarTemp(); 
                            generaCodigo(MAYOR_IGUAL,i,$1,$4); 
                            $$=i;
                          };

expr: expr '+' term {
                      int i = GenVarTemp(); 
                      generaCodigo(SUMAR,i,$1,$3); 
                      $$=i;
                    }
    | expr '-' term {
                      int i = GenVarTemp(); 
                      generaCodigo(RESTAR,i,$1,$3); 
                      $$=i;
                    }
    | term;
term: term '*' term2 {
                        int i = GenVarTemp(); 
                        generaCodigo(MULTIPLICAR,i,$1,$3); 
                        $$=i;
                      }
    | term '/' term2 {
                        int i = GenVarTemp(); 
                        generaCodigo(DIVIDIR,i,$1,$3); 
                        $$=i;
                      }
    | term2;
term2: '(' expr ')' {
                      int i = GenVarTemp(); 
                      generaCodigo(PARENTESIS,i,$2,$2); 
                      $$=i;
                    }
     | INTCONST {$$=localizaSimb(lexema,INTCONST);}
     | DOUBLECONST {$$=localizaSimb(lexema,DOUBLECONST);}
     | VAR {$$=localizaSimb(lexema,VAR);};
%%

void InterpretaCodigo(){
  int i,a1,a2,a3,op,j,temp;
  for(i=0; i<=cx; i++){
    op = TCodigo[i].op;
    a1 = TCodigo[i].a1;
    a2 = TCodigo[i].a2;
    a3 = TCodigo[i].a3;

    if(op==MAYOR){
      TablaSim[a1].tokenaux=MAYOR;
      if(TablaSim[a2].valor>TablaSim[a3].valor) TablaSim[a1].valor=1;
      else TablaSim[a1].valor=0;
    }
    if(op==MENOR){
      TablaSim[a1].tokenaux=MENOR;
      if(TablaSim[a2].valor<TablaSim[a3].valor) TablaSim[a1].valor=1;
      else TablaSim[a1].valor=0;
    }
    if(op==MAYOR_IGUAL){
      TablaSim[a1].tokenaux=MAYOR_IGUAL;
      if(TablaSim[a2].valor>=TablaSim[a3].valor) TablaSim[a1].valor=1;
      else TablaSim[a1].valor=0;
    }
    if(op==MENOR_IGUAL){
      TablaSim[a1].tokenaux=MENOR_IGUAL;
      if(TablaSim[a2].valor<=TablaSim[a3].valor) TablaSim[a1].valor=1;
      else TablaSim[a1].valor=0;
    }
    if(op==IGUAL){
      TablaSim[a1].tokenaux=IGUAL;
      if(TablaSim[a2].valor==TablaSim[a3].valor) TablaSim[a1].valor=1;
      else TablaSim[a1].valor=0;
    }
    if(op==DESIGUAL){
      TablaSim[a1].tokenaux=DESIGUAL;
      if(TablaSim[a2].valor!=TablaSim[a3].valor) TablaSim[a1].valor=1;
      else TablaSim[a1].valor=0;
    }

    if(op==SUMAR) TablaSim[a1].valor = TablaSim[a2].valor + TablaSim[a3].valor;
    if(op==RESTAR) TablaSim[a1].valor = TablaSim[a2].valor - TablaSim[a3].valor;
    if(op==MULTIPLICAR) TablaSim[a1].valor = TablaSim[a2].valor * TablaSim[a3].valor;
    if(op==DIVIDIR) TablaSim[a1].valor = TablaSim[a2].valor / TablaSim[a3].valor;
    if(op==PARENTESIS) TablaSim[a1].valor = TablaSim[a2].valor;
    if(op==ASIGNAR) TablaSim[a1].valor = TablaSim[a2].valor;
    if(op==IMPRIMIR) printf("%lf\n",TablaSim[a1].valor);

    if(op==SALTAR1){
      if(TablaSim[a1].valor==0) i=a2-1;
    }
    if(op==SALTAR2){
      if(TablaSim[a1].valor==1) i=a2-1;
    }
    if(op==SALTAR_FOR){
      if(TablaSim[a1].valor >= TablaSim[a2].valor) i=a3-1;
    }
    if(op==BUCLE_FOR){
      TablaSim[a1].valor += 1;
      i=a2-1;
    }
    if(op==BUCLE_WHILE) i=a1-2;
  }
}

int GenVarTemp(){
  char t[60];
  sprintf(t,"_T%d",nVarTemp++);
  return localizaSimb(t,VAR);
}

void generaCodigo(int op, int a1, int a2, int a3){
  cx++;
  TCodigo[cx].op = op;
  TCodigo[cx].a1 = a1;
  TCodigo[cx].a2 = a2;
  TCodigo[cx].a3 = a3;
}

int localizaSimb(char *nom, int tok){
  int i;
  for(i=0; i<nSim; i++){
    if(!strcasecmp(TablaSim[i].nombre,nom))
      return i;
  }
  strcpy(TablaSim[nSim].nombre,nom);
  TablaSim[nSim].token = tok;
  if(tok==VAR) TablaSim[nSim].valor = 0.0;
  if(tok==INTCONST) sscanf(nom,"%lf",&TablaSim[nSim].valor);
  if(tok==DOUBLECONST) sscanf(nom,"%lf",&TablaSim[nSim].valor);
  nSim++;
  return nSim - 1;
}

void imprimeTablaSim(){
  int i;
  for(i=0; i<nSim; i++){
    if(TablaSim[i].tokenaux==MAYOR ||
    TablaSim[i].tokenaux==MENOR ||
    TablaSim[i].tokenaux==IGUAL ||
    TablaSim[i].tokenaux==DESIGUAL ||
    TablaSim[i].tokenaux==MAYOR_IGUAL ||
    TablaSim[i].tokenaux==MENOR_IGUAL){
      if(TablaSim[i].valor==1.0){
        printf("%4d nombre=%6s tok=%5d valor=  V\n",i,TablaSim[i].nombre,TablaSim[i].token);
        continue;
      }
      else{
        printf("%4d nombre=%6s tok=%5d valor=  F\n",i,TablaSim[i].nombre,TablaSim[i].token);
        continue;
      }
    }
    printf("%4d nombre=%6s tok=%5d valor=%4.3lf\n",i,TablaSim[i].nombre,TablaSim[i].token,TablaSim[i].valor);
  }
}

void imprimeTablaCod(){
  int i;
  for(i=0; i<=cx; i++){
    printf("%4d op=%5d  a1=%4d a2=%4d a3=%4d\n",i,TCodigo[i].op,TCodigo[i].a1,TCodigo[i].a2,TCodigo[i].a3);
  }
}

void yyerror(char *msg){
  printf("Syntax Error: %s on line %i \n", msg, errorLine);
}

int EsPalabraReservada(char lexema[]){
  //strcmp considera mayusculas y minusculas
  //strcasecmp ignora mayusculas de minusculas
  if(strcmp(lexema,"SALIDA") == 0) return OUTPUT;
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
  
  return VAR;
}

int yylex(){
  char c; int i;
  while(1){
    c = getchar();

    if(c == ' ') continue;
    if(c == '\t') continue;
    if(c == '\n'){
      errorLine += 1;
      continue;
    }

    if(isalpha(c) || c == '_'){
      i = 0;
      do{
        lexema[i++] = c;
        c = getchar();
      }while(isalnum(c) || c == '_');
      ungetc(c, stdin);
      lexema[i] = '\0';
      return EsPalabraReservada(lexema);
    }

    if(isdigit(c)){
      i = 0;
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
          return DOUBLECONST;
        }
        ungetc(c, stdin);
        lexema[i] = '\0';
        return DOUBLECONST;
      }
      ungetc(c, stdin);
      lexema[i] = '\0';
      return INTCONST;
    }

    return c;
  }
}

int main(){
  /*if(!yyparse()) printf("La cadena es VALIDA\n");
  else printf("La cadena es INVALIDA\n");*/
  yyparse();
  printf("Tabla de Simbolos:\n"); imprimeTablaSim();
  printf("Tabla de Codigos\n"); imprimeTablaCod();
  printf("--------------------------------\n");
  InterpretaCodigo();
  printf("--------------------------------\n");
  printf("Tabla de Simbolos despues de interpretar\n"); imprimeTablaSim();
  return 0;
}