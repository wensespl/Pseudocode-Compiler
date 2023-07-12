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

double histValRet[100];
int histValorN = -1;

typedef struct {
  char nombre[60];
  int token;
  int args[20];
  int nArgs;
  int iniFun;
  int finFun;
  int retVal;
} tipoTF;
tipoTF TablaFun[20];
int nFun = 0;
int nArgFun = 0;
int nRet;
int retVal;

int histRetVal[100];
int histRetN = -1;

typedef struct {
  int op;
  int a1;
  int a2;
  int a3;
  int args[20];
} tipoCodigo;
int cx = -1;
tipoCodigo TCodigo[100];

void generaCodigo(int,int,int,int);
int localizaSimb(char *, int);
int localizaFun(char *, int);
void imprimeTablaSim();
void imprimeTablaFun();

int nVarTemp = 0;
int GenVarTemp();
void InterpretaCodigo();

int errorLine = 0;
char scope[60] = "";
%}

%token VAR INTCONST DOUBLECONST
%token OUTPUT
%token IF THEN ELSE ENDIF
%token WHILE DO ENDWHILE
%token FOR TO ENDFOR
%token SUBROUTINE ENDSUBROUTINE RETURN
%token IMPRIMIR
%token ASIGNAR SUMAR RESTAR MULTIPLICAR DIVIDIR PARENTESIS
%token SALTAR FUNCALL RETORNO FINAL
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
           | function_stmt
           | return_stmt
           | output_stmt;

if_stmt: IF cond {generaCodigo(SALTAR1,$2,'?','-');$$=cx;} THEN stmt_list {generaCodigo(SALTAR2,$2,'?','-');$$=cx;}{TCodigo[$3].a2=cx+1;} otro {TCodigo[$6].a2=cx+1;} ENDIF;
otro: ELSE stmt_list
    |  ;

while_stmt: WHILE cond {generaCodigo(SALTAR1,$2,'?','-');$$=cx;} DO stmt_list {generaCodigo(BUCLE_WHILE,$3,'-','-');}{TCodigo[$3].a2=cx+1;} ENDWHILE;

for_stmt: FOR VAR {$$=localizaSimb(lexema,VAR);} '=' expr {generaCodigo(ASIGNAR,$3,$5,'-');} TO expr {generaCodigo(SALTAR_FOR,$3,$8,'?');$$=cx;} stmt_list {generaCodigo(BUCLE_FOR,$3,$9,'-');}{TCodigo[$9].a3=cx+1;} ENDFOR;

assig_stmt: VAR {$$=localizaSimb(lexema,VAR);} '=' expr {generaCodigo(ASIGNAR,$2,$4,'-');};

output_stmt: OUTPUT expr ';' {generaCodigo(IMPRIMIR,$2,'-','-');};

function_header: SUBROUTINE VAR {strcpy(scope,lexema);$$=localizaFun(lexema,VAR);} '(' arg_list ')' {
                                                                                                      TablaFun[$3].nArgs=nArgFun;
                                                                                                      nArgFun=0;
                                                                                                      int i = GenVarTemp();
                                                                                                      TablaFun[$3].retVal=i;
                                                                                                      $$=$3;
                                                                                                    };
arg_list: expr {TablaFun[nFun-1].args[nArgFun++]=$1;}
        | arg_list ',' expr {TablaFun[nFun-1].args[nArgFun++]=$3;};

function_stmt: function_header {generaCodigo(SALTAR,'?','-','-');$$=cx;} stmt_list {generaCodigo(FINAL,'?',$1,'-');$$=cx;} {TCodigo[$2].a1=cx+1;} ENDSUBROUTINE {
                                                                                                                                                                    TablaFun[$1].iniFun=$2;
                                                                                                                                                                    TablaFun[$1].finFun=$4;
                                                                                                                                                                    sprintf(scope,"%s","");
                                                                                                                                                                  };
return_stmt: RETURN expr ';' {
                                generaCodigo(RETORNO,$2,nFun-1,'-');
                              };

function_call: VAR {$$=localizaFun(lexema,VAR);} {generaCodigo(FUNCALL,$2,'-','-');} '(' expr_list ')' {nArgFun=0;$$=TablaFun[$2].retVal;};
expr_list: expr {TCodigo[cx].args[nArgFun++]=$1;}
        | expr_list ',' expr {TCodigo[cx].args[nArgFun++]=$3;};

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
     | VAR {$$=localizaSimb(lexema,VAR);}
     | function_call {$$=$1;};
%%

void InterpretaCodigo(){
  int i,a1,a2,a3,op,j,temp;
  for(i=0; i<=cx; i++){
    op = TCodigo[i].op;
    a1 = TCodigo[i].a1;
    a2 = TCodigo[i].a2;
    a3 = TCodigo[i].a3;

    // printf("Codigo %d\n", i);

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

    if(op==SALTAR)  i=a1-1;
    if(op==FUNCALL){
      for(int idx=0; idx < TablaFun[a1].nArgs; idx++){
        TablaSim[TablaFun[a1].args[idx]].valor = TablaSim[TCodigo[i].args[idx]].valor;
      }
      histRetN++;
      histRetVal[histRetN] = i;
      // histValorN++;
      // histValRet[histValorN] = TablaSim[TablaFun[a1].retVal].valor;
      // TCodigo[TablaFun[a1].finFun].a1 = i;
      i = TablaFun[a1].iniFun;
    }
    if(op==RETORNO){
      // histValorN++;
      // histValRet[histValorN] = TablaSim[a1].valor;
      TablaSim[TablaFun[a2].retVal].valor = TablaSim[a1].valor;
      i = TablaFun[a2].finFun - 1;
    }
    if(op==FINAL){
      // TablaSim[TablaFun[a2].retVal].valor = histValRet[histValorN];
      // histValorN--;
      i = histRetVal[histRetN];
      histRetN--;
      // i = a1;
    }
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
  char t[60];
  if(tok==VAR){
    sprintf(t,"%s%s",scope,nom);
  } else {
    strcpy(t,nom);
  }
  for(i=0; i<nSim; i++){
    if(!strcasecmp(TablaSim[i].nombre,t))
      return i;
  }
  if(tok==VAR){
    strcpy(TablaSim[nSim].nombre,t);
  } else {
    strcpy(TablaSim[nSim].nombre,nom);
  }
  TablaSim[nSim].token = tok;
  if(tok==VAR) TablaSim[nSim].valor = 0.0;
  if(tok==INTCONST) sscanf(nom,"%lf",&TablaSim[nSim].valor);
  if(tok==DOUBLECONST) sscanf(nom,"%lf",&TablaSim[nSim].valor);
  nSim++;
  return nSim - 1;
}

int localizaFun(char *nom, int tok){
  int i;
  for(i=0; i<nFun; i++){
    if(!strcasecmp(TablaFun[i].nombre,nom))
      return i;
  }
  strcpy(TablaFun[nFun].nombre,nom);
  TablaFun[nFun].token = tok;
  nFun++;
  return nFun - 1;
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
        printf("%4d nombre=%10s tok=%4d valor=  V\n",i,TablaSim[i].nombre,TablaSim[i].token);
        continue;
      }
      else{
        printf("%4d nombre=%10s tok=%4d valor=  F\n",i,TablaSim[i].nombre,TablaSim[i].token);
        continue;
      }
    }
    printf("%4d nombre=%10s tok=%4d valor=%4.3lf\n",i,TablaSim[i].nombre,TablaSim[i].token,TablaSim[i].valor);
  }
}

void imprimeTablaFun(){
  int i;
  for(i=0; i<nFun; i++){
    printf("%4d nombre=%10s tok=%4d args=",i,TablaFun[i].nombre,TablaFun[i].token);
    for(int idx=0; idx < TablaFun[i].nArgs; idx++){
      printf("%3d ",TablaFun[i].args[idx]);
    }
    printf("iniFun=%4d finFun=%4d retVal=%4d\n",TablaFun[i].iniFun,TablaFun[i].finFun,TablaFun[i].retVal);
  }
}

void imprimeTablaCod(){
  int i;
  for(i=0; i<=cx; i++){
    if(TCodigo[i].op==FUNCALL){
      printf("%4d op=%4d a1=%3d a2=%3d a3=%3d args=",i,TCodigo[i].op,TCodigo[i].a1,TCodigo[i].a2,TCodigo[i].a3);
      for(int idx=0; idx < TablaFun[TCodigo[i].a1].nArgs; idx++){
        printf("%3d ",TCodigo[i].args[idx]);
      }
      printf("\n");
    } else {
      printf("%4d op=%4d a1=%3d a2=%3d a3=%3d\n",i,TCodigo[i].op,TCodigo[i].a1,TCodigo[i].a2,TCodigo[i].a3);
    }
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
  if(strcmp(lexema,"SUBRUTINA") == 0) return SUBROUTINE;
  if(strcmp(lexema,"FINSUBRUTINA") == 0) return ENDSUBROUTINE;
  if(strcmp(lexema,"DEVOLVER") == 0) return RETURN;
  
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

    if(isalpha(c)){
      i = 0;
      do{
        lexema[i++] = c;
        c = getchar();
      }while(isalnum(c));
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
  printf("Tabla de Funciones:\n"); imprimeTablaFun();
  printf("Tabla de Codigos\n"); imprimeTablaCod();
  printf("--------------------------------\n");
  InterpretaCodigo();
  printf("--------------------------------\n");
  printf("Tabla de Simbolos despues de interpretar\n"); imprimeTablaSim();
  return 0;
}