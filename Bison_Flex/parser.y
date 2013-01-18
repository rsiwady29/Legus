%locations
%error-verbose
%code requires{
    #include <string>
    #include "Expresion/Expresion.h"
    #include "Instruccion/Instruccion.h"
    #include "Bison_Flex/Lista.h"
    #include "Instruccion/ListaDeCaso.h"
}
%{
    /* Imports Tree */
    #include "Bison_Flex/ParserImports.h"

    extern int yylex();
    extern char *yytext;
    extern int linea, yytoken, yylineno;
    extern FILE *yyin;

    int token_esperado = -1;
    int correlativo = 0;

    void yyerror(const char *s) {        
//        QMessageBox::about(0,"","Error Sintactico: " + QString(s) + "linea: " + QString::number(yylineno));
    }
%}

%union{
    std::string              *string;
    Expresion                *expresion;
    Instruccion              *instruccion;
    Expresion                *vectorExpresiones;
    Lista                    *lista;
    ListaDeCaso              *lista_de_caso;
}

/* TERMINALES */

/* EXPRESIONES REGULARES */
%token <string> T_IDENTIFICADOR

/* SIMBOLOS */
/*IDE Agregar cadena */
%token <string> T_SIMBOLO_IGUAL T_SUMA T_RESTA T_MULTIPLICACION T_DIVISION T_SIMBOLO_MODULO
%token <string> T_EXPONENCIACION T_MAYOR_IGUAL T_MENOR_IGUAL T_MENOR T_MAYOR T_IGUALDAD
%token <string> T_NEGACION T_SIMBOLO_OPERADOR_Y T_SIMBOLO_OPERADOR_O T_CORCHETE_IZQUIERDO
%token <string> T_CORCHETE_DERECHO T_PARENTESIS_IZQUIERDO T_PARENTESIS_DERECHO T_DOS_PUNTOS
%token <string> T_DESIGUALDAD T_LITERAL_CARACTER T_LITERAL_FLOTANTE T_LITERAL_CADENA T_COMA
%token <string> T_ENTER T_EOF


/* PALABRAS RESERVADAS */
%token <string> T_MODULO T_DIVISION_ENTERA T_IGUAL T_A T_DISTINTO T_DE T_OPERADOR_Y T_OPERADOR_O
%token <string> T_NO T_SI T_ENTONCES T_FIN T_SINO T_CASO T_MIENTRAS T_HAGA T_EJECUTE T_REPETIR
%token <string> T_INFINITAS T_VECES T_PARA T_DESDE T_REPITA T_CADA T_EN T_FUNCION T_HASTA
%token <string> T_RETORNA T_RETORNAR T_UTILIZAR T_COMO T_LITERAL_NUMERICA T_DEFINIR T_VERDADERO T_FALSO


/* NO TERMINALES */
%type <string>          declaracion_sensores_motores declaracion_funciones
%type <instruccion>     instrucciones instruccion instruccion_si instruccion_caso instruccion_mientras
                        instruccion_para instruccion_repetir instruccion_asignacion
                        instruccion_repita_desde instruccion_para_cada instruccion_llamada_a_funcion
                        instruccion_retornar sino_caso programa instruccion_auto_asignacion

%type <expresion>       id_variable id_funcion id_arreglo
%type <lista>           lista_indices lista_indices_declaracion
%type <lista>           lista_parametros acumulador_parametros
%type <lista_de_caso>   lista_casos
%type <expresion>       literales literal_booleana relacionales expresiones factores terminales


/* PUNTO DE ENTRADA */
%start programa

%%
    /* DEFINICIONES GRAMATICALES */

    programa :
        declaracion_sensores_motores declaracion_funciones instrucciones
        {
            $$ = $3;
            Programa::obtenerInstancia()->instrucciones = $3;
        }
        ;

    /******************** Declaraciones *******************/

    declaracion_funciones :
        T_FUNCION   {}
            T_IDENTIFICADOR
                T_PARENTESIS_IZQUIERDO
                    lista_parametros
                        T_PARENTESIS_DERECHO
                    instrucciones
                    T_FIN T_FUNCION declaracion_funciones
        {
            DeclaracionDeFuncion *declrFuncion = new DeclaracionDeFuncion(new Variable($3, yylineno, correlativo++), $5, $7);
            Programa::obtenerInstancia()->tablaDeFunciones->push_back(declrFuncion);
        }
        |/*Epsilon*/
        {
            $$=0;
        }
        ;

    declaracion_sensores_motores :
        T_UTILIZAR T_IDENTIFICADOR T_COMO T_IDENTIFICADOR T_EN T_IDENTIFICADOR declaracion_sensores_motores
        {
            DeclaracionUtilizar *declrUtilizar = new DeclaracionUtilizar(new VariablePuerto($2, yylineno, correlativo++), new VariableSensor($4, yylineno, correlativo++), new Variable($6, yylineno, correlativo++));
            Programa::obtenerInstancia()->tablaDePuertosYSensores->push_back(declrUtilizar);
        }
        |/*Epsilon*/
        {
            $$=0;
        }
        ;

    /******************** Instrucciones *******************/

    instrucciones :
        instruccion instrucciones
        {
            $1->establecerSiguiente($2);
            $$ = $1;
        }
        |/*Epsilon*/

        {
            $$ = 0;
        }
        ;

    instruccion :
        instruccion_si
        {
            $$ = $1;
        }
        |instruccion_caso
        {
            $$ = $1;
        }
        |instruccion_mientras
        {
            $$ = $1;
        }
        |instruccion_para
        {
            $$ = $1;
        }
        |instruccion_repetir
        {
            $$ = $1;
        }
        |instruccion_asignacion
        {
            $$ = $1;
        }
        |instruccion_auto_asignacion
        {
            $$ = $1;
        }
        |instruccion_repita_desde
        {
            $$ = $1;
        }
        |instruccion_para_cada
        {
            $$ = $1;
        }
        |instruccion_llamada_a_funcion
        {
            $$ = $1;
        }
        |instruccion_retornar
        {
            $$ = $1;
        }
        |T_REPITA instruccion/*Deberia ir instrucciones ( TO-DO )*/ T_MIENTRAS relacionales T_FIN T_REPITA
        {
        }/*Aqui solia ir instruccion_repita: fue eliminada porque generaba 2 shift/reduce */;

    instruccion_si :
        T_SI relacionales T_ENTONCES instrucciones T_FIN T_SI
        {
            /* Parametros: condicion, instruccionSiVerdadero, instruccionSiFalso,instruccionSiAnidado, Siguiente*/
            $$ = new InstruccionSi($2, $4, 0, 0, 0, correlativo++);
        }
        |T_SI relacionales T_ENTONCES instrucciones T_SINO instrucciones T_FIN T_SI
        {
            /* Parametros: condicion, instruccionSiVerdadero, instruccionSiFalso,instruccionSiAnidado, Siguiente*/
            $$ = new InstruccionSi($2, $4, $6, 0, 0, correlativo++);
        }
        ;

    instruccion_caso:
        T_CASO T_IDENTIFICADOR lista_casos sino_caso T_FIN T_CASO
        {
            $$ = new InstruccionCaso( new Variable($2, yylineno, correlativo++), $3, $4, 0, correlativo++);
        }
        |T_CASO lista_casos sino_caso T_FIN T_CASO
        {
            $$ = new InstruccionCaso(0, $2, $3, 0, correlativo++);
        };

    instruccion_mientras:
        T_MIENTRAS relacionales T_EJECUTE instrucciones T_FIN T_MIENTRAS
        {
            /* Parametros:   condicion, instrucciones, siguiente */
            $$ = new InstruccionMientras($2, $4, 0, correlativo++);
        };

    instruccion_para :
        T_PARA T_IDENTIFICADOR T_SIMBOLO_IGUAL relacionales T_HASTA relacionales T_EJECUTE instrucciones T_FIN T_PARA
        {
            /*identificador, inicio, final, instrucciones, siguiente*/
            $$ = new InstruccionPara(new InstruccionAsignacion(new Variable($2, yylineno, correlativo++),$4,0, correlativo++), $6, $8, 0, correlativo++);
        };

    instruccion_repetir :
        T_REPETIR relacionales T_VECES instrucciones T_FIN T_REPETIR
        {
            /*Cantidad, instrucciones, siguiente*/
            $$ = new InstruccionRepetir($2, $4, 0, correlativo++);
        };

    instruccion_asignacion :
        T_IDENTIFICADOR T_SIMBOLO_IGUAL relacionales
        {
            /*Variable, Expresion, siguiente*/
            Variable *var = new Variable($1, $3, yylineno, correlativo);
            Programa::obtenerInstancia()->tablaDeVariables->push_back(new VariableDeclarada(var,$3->validarSemantica(), correlativo));
            $$ = new InstruccionAsignacion(var, $3, 0, correlativo++);
        }
        |id_arreglo T_SIMBOLO_IGUAL relacionales
        {
            /*Variable, Expresion, siguiente*/
            $$ = new InstruccionAsignacion($1, $3, 0, correlativo++);
        }
        |T_IDENTIFICADOR T_SIMBOLO_IGUAL lista_indices_declaracion
        {
            VariableArreglo* variableArreglo = new VariableArreglo($1, 0, yylineno, correlativo);
            TipoArreglo *tipoArreglo = Programa::obtenerInstancia()->obtenerTipoArreglo();
            Programa::obtenerInstancia()->tablaDeVariables->push_back(new VariableDeclarada(variableArreglo, tipoArreglo, correlativo));
            $$ = new InstruccionAsignacion(variableArreglo, 0, 0, correlativo++);
        };

    instruccion_auto_asignacion:
        T_IDENTIFICADOR T_SUMA T_SIMBOLO_IGUAL relacionales
        {
            Variable *vari = new Variable($1, yylineno, correlativo++);
            ExpresionBinariaSuma *suma = new ExpresionBinariaSuma(vari, $4, yylineno);

            Variable *var = new Variable($1, suma, yylineno, correlativo);
            Programa::obtenerInstancia()->tablaDeVariables->push_back(new VariableDeclarada(var, suma->validarSemantica(), correlativo));
            $$ = new InstruccionAsignacion(var, suma, 0, correlativo++);
        }
        |T_IDENTIFICADOR T_DIVISION T_SIMBOLO_IGUAL relacionales
        {
            Variable *vari = new Variable($1, yylineno, correlativo++);
            ExpresionBinariaDivision *division = new ExpresionBinariaDivision(vari, $4, yylineno);

            Variable *var = new Variable($1, division, yylineno, correlativo);
            Programa::obtenerInstancia()->tablaDeVariables->push_back(new VariableDeclarada(var, division->validarSemantica(), correlativo));
            $$ = new InstruccionAsignacion(var, division, 0, correlativo++);
        }
        |T_IDENTIFICADOR T_SIMBOLO_MODULO T_SIMBOLO_IGUAL relacionales
        {
            Variable *vari = new Variable($1, yylineno, correlativo++);
            ExpresionBinariaModulo *modulo = new ExpresionBinariaModulo(vari, $4, yylineno);

            Variable *var = new Variable($1, modulo, yylineno, correlativo);
            Programa::obtenerInstancia()->tablaDeVariables->push_back(new VariableDeclarada(var, modulo->validarSemantica(), correlativo));
            $$ = new InstruccionAsignacion(var, modulo, 0, correlativo++);
        }
        |T_IDENTIFICADOR T_MULTIPLICACION T_SIMBOLO_IGUAL relacionales
        {
            Variable *vari = new Variable($1, yylineno, correlativo++);
            ExpresionBinariaMultiplicacion *multiplicacion= new ExpresionBinariaMultiplicacion(vari, $4, yylineno);

            Variable *var = new Variable($1, multiplicacion, yylineno, correlativo);
            Programa::obtenerInstancia()->tablaDeVariables->push_back(new VariableDeclarada(var, multiplicacion->validarSemantica(), correlativo));
            $$ = new InstruccionAsignacion(var, multiplicacion, 0, correlativo++);
        }
        |T_IDENTIFICADOR T_RESTA T_SIMBOLO_IGUAL relacionales
        {
            Variable *vari = new Variable($1, yylineno, correlativo++);
            ExpresionBinariaResta *resta= new ExpresionBinariaResta(vari, $4, yylineno);

            Variable *var = new Variable($1, resta, yylineno, correlativo);
            Programa::obtenerInstancia()->tablaDeVariables->push_back(new VariableDeclarada(var, resta->validarSemantica(), correlativo));
            $$ = new InstruccionAsignacion(var, resta, 0, correlativo++);
        }
        |T_IDENTIFICADOR T_EXPONENCIACION T_SIMBOLO_IGUAL relacionales
        {
            Variable *vari = new Variable($1, yylineno, correlativo++);
            ExpresionBinariaExponenciacion *exponenciacion= new ExpresionBinariaExponenciacion(vari, $4, yylineno);

            Variable *var = new Variable($1, exponenciacion, yylineno, correlativo);
            Programa::obtenerInstancia()->tablaDeVariables->push_back(new VariableDeclarada(var, exponenciacion->validarSemantica(), correlativo));
            $$ = new InstruccionAsignacion(var, exponenciacion, 0, correlativo++);
        }
        ;


    instruccion_repita_desde :
        T_REPITA T_DESDE relacionales T_HASTA relacionales T_EJECUTE instrucciones T_FIN T_REPITA
        {
            /* inicio , final , instrucciones , siguiente*/
            $$ = new InstruccionRepitaDesde($3, $5, $7, 0, correlativo++);
        };

    instruccion_para_cada :
        T_PARA T_CADA relacionales T_EN relacionales T_EJECUTE instrucciones T_FIN T_PARA T_CADA
        {
            /* variable, coleccion, instrucciones, siguientes */
            $$ = new InstruccionParaCada($3, $5, $7, 0, correlativo++);
        };

    instruccion_llamada_a_funcion :
        T_IDENTIFICADOR T_PARENTESIS_IZQUIERDO lista_parametros T_PARENTESIS_DERECHO
        {
            $$ = new InstruccionLlamadaAFuncion($1, $3, 0, correlativo++);
        };

    instruccion_retornar :
        T_RETORNAR relacionales
        {
            $$ = new InstruccionRetornar($2, 0, correlativo++);
        }
        ;
    /******************** Expresiones  ********************/

    relacionales :
        relacionales T_MENOR         expresiones
        {
            $$ = new ExpresionBinariaMenor($1, $3, yylineno);
        }
        |relacionales T_MAYOR         expresiones
        {
            $$ = new ExpresionBinariaMayor($1, $3, yylineno);
        }
        |relacionales T_MAYOR_IGUAL   expresiones
        {
            $$ = new ExpresionBinariaMayorIgual($1, $3, yylineno);
        }
        |relacionales T_MENOR_IGUAL   expresiones
        {
            $$ = new ExpresionBinariaMenorIgual($1, $3, yylineno);
        }
        |relacionales T_IGUALDAD      expresiones
        {
            $$ = new ExpresionBinariaIgualdad($1, $3, yylineno);
        }
        |relacionales T_DESIGUALDAD   expresiones
        {
            $$ = new ExpresionBinariaDistinto($1, $3, yylineno);
        }
        |expresiones
        {
            $$ = $1;
        };

    expresiones :
        expresiones T_SUMA                factores
        {
            $$ = new ExpresionBinariaSuma($1, $3, yylineno);
        }
        |expresiones T_RESTA               factores
        {
            $$ = new ExpresionBinariaResta($1, $3, yylineno);
        }
        |expresiones T_OPERADOR_O          factores
        {
            $$ = new ExpresionBinariaO($1, $3, yylineno);
        }
        |expresiones T_SIMBOLO_OPERADOR_O  factores
        {
            $$ = new ExpresionBinariaO($1, $3, yylineno);
        }
        |factores
        {
            $$ = $1;
        };

    factores :
        factores T_MULTIPLICACION         terminales
        {
            $$ = new ExpresionBinariaMultiplicacion($1, $3, yylineno);
        }
        |factores T_DIVISION               terminales
        {
            $$ = new ExpresionBinariaDivision($1, $3, yylineno);
        }
        |factores T_OPERADOR_Y             terminales
        {
            $$ = new ExpresionBinariaY($1, $3, yylineno);
        }
        |factores T_SIMBOLO_OPERADOR_Y     terminales
        {
            $$ = new ExpresionBinariaY($1, $3, yylineno);
        }
        |factores T_SIMBOLO_MODULO         terminales
        {
            $$ = new ExpresionBinariaModulo($1, $3, yylineno);
        }
        |terminales
        {
            $$ = $1;
        };

    terminales :
        T_PARENTESIS_IZQUIERDO relacionales  T_PARENTESIS_DERECHO
        {
            $$ = $2;
        }
        |literales
        {
            $$ = $1;
        }
        |id_variable
        {
            $$ = $1;
        }
        |T_IDENTIFICADOR
        {
            $$ = new Variable($1, yylineno, correlativo++);
        };

    id_variable :
        id_funcion
        {
            $$ = $1;
        }
        |id_arreglo
        {
            $$ = $1;
        };

    id_funcion:
        T_IDENTIFICADOR T_PARENTESIS_IZQUIERDO lista_parametros T_PARENTESIS_DERECHO
        {
            $$ = new VariableFuncion($1, $3, yylineno, correlativo++);
        };

    id_arreglo :
        T_IDENTIFICADOR lista_indices
        {
            $$ = new VariableArreglo($1, $2, yylineno, correlativo++);
        };

    /*Literales*/

    literal_booleana :
        T_VERDADERO
        {
            $$ = new ExpresionLiteralBooleana(true, yylineno);
        }
        |T_FALSO
        {
            $$ = new ExpresionLiteralBooleana(false, yylineno);
        };

    literales:
        literal_booleana
        {
            $$ = $1;
        }
       |T_LITERAL_NUMERICA
       {
            $$ = new ExpresionLiteralEntera( atoi( $1->c_str() ), yylineno);
       }
       |T_LITERAL_CARACTER
       {
            $$ = new ExpresionLiteralCaracter( $1->at(1), yylineno);
       }
       |T_LITERAL_FLOTANTE
       {
            $$ = new ExpresionLiteralFlotante( atof( $1->c_str() ), yylineno);
       }
       |T_LITERAL_CADENA
       {
            $$ = new ExpresionLiteralCadena($1, yylineno);
       };

    lista_indices:
        T_CORCHETE_IZQUIERDO relacionales T_CORCHETE_DERECHO lista_indices
        {
            $4->lista->push_back($2);
            $$ = $4;
        }
        |T_CORCHETE_IZQUIERDO relacionales T_CORCHETE_DERECHO
        {
            Lista *lista = new Lista();
            lista->lista->push_back($2);
            $$ = lista;
        };

    lista_indices_declaracion :
        T_CORCHETE_IZQUIERDO T_CORCHETE_DERECHO
        {
        }
        |T_CORCHETE_IZQUIERDO T_CORCHETE_DERECHO T_CORCHETE_IZQUIERDO T_CORCHETE_DERECHO
        {

        }
        ;

    lista_parametros :
        relacionales acumulador_parametros
        {
            $2->lista->push_back($1);
            $$ = $2;
        }
        |/*Epsilon*/
        {
            $$ = new Lista();
        };

    acumulador_parametros :
        T_COMA  relacionales    acumulador_parametros
        {
            $3->lista->push_back($2);
            $$ = $3;
        }
        |/*Epsilon*/
        {
            $$ = new Lista();
        };

    lista_casos :
         T_DOS_PUNTOS relacionales T_DOS_PUNTOS instrucciones lista_casos
         {
            $5->establecerSiguiente(new ListaDeCaso($2, $4, 0) );
            $$ = $5;
         }
        |T_DOS_PUNTOS relacionales T_DOS_PUNTOS instrucciones
        {
            /*Parametros, Expresion, Instruccion, Siguiente*/
            $$ = new ListaDeCaso($2, $4, 0);
        };

    sino_caso :
        T_SINO instrucciones
        {
            $$ = $2;
        }
        | /*Epsilon*/
        {
            $$ = 0;
        };
%%