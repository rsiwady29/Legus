#include "Instruccion/InstruccionAsignacion.h"
#include "ExpresionArreglo.h"

InstruccionAsignacion::InstruccionAsignacion(Expresion *variable, Expresion *expresion, Instruccion *siguiente,
                                             int idDeExpresion, int numeroDeLinea)
    :Instruccion(siguiente, ASIGNACION, idDeExpresion, numeroDeLinea)
{
    this->variable = variable;
    this->expresion = expresion;
    this->listaIndices = 0;
}

InstruccionAsignacion::InstruccionAsignacion(VariableArreglo *variable, Lista *listaIndices,
                                             Instruccion *siguiente, int idDeExpresion,
                                             int numeroDeLinea)
    :Instruccion(siguiente,ASIGNACION, idDeExpresion,numeroDeLinea)
{
    this->variable = variable;
    this->listaIndices = listaIndices;
    this->expresion = new ExpresionArreglo(numeroDeLinea);
}

void InstruccionAsignacion::validarSemantica()
{
//    this->variable->validarSemantica();
    if( variable->tipo == VARIABLENORMAL )
    {
        Variable *var = (Variable*)variable;

        /*Que no sea una variable de Utilizar ni nombre de funcion*/
        if( Programa::obtenerInstancia()->existeEnTablaDePuertosYSensores(var->obtenerIdentificador()))
        {
            throw(ExcepcionLegus("Variable 'ReemplazarPorVariable' esta siendo utilizada en Puerto 'PUERTO' como 'SENSOR'",numeroDeLinea));
        }

        if( Programa::obtenerInstancia()->existeEnTablaDeFunciones(var->obtenerIdentificador(), var->obtenerIdDeExpresion()) )
        {
            throw(ExcepcionLegus("Variable 'ReemplazarPorVariable' esta siendo utilizada en funcion 'FUNCION'",numeroDeLinea));
        }

        if( expresion != 0)
        {
            var->tipoInferido = this->expresion->validarSemantica();
            // Actualizar Tabla De Variables A Declarar
            Programa::obtenerInstancia()->actualizarVariableADeclarar(var->obtenerIdentificador(), var->obtenerIdDeExpresion(), var->tipoInferido);
        }
    }
    else if( variable->tipo == ARREGLO)
    {
        VariableArreglo* var = (VariableArreglo*)variable;
        if( Programa::obtenerInstancia()->existeEnTablaDePuertosYSensores(var->obtenerIdentificador()))
        {
            throw(ExcepcionLegus("Variable 'ReemplazarPorVariable' esta siendo utilizada en Puerto 'PUERTO' como 'SENSOR'",numeroDeLinea));
        }

        if( Programa::obtenerInstancia()->existeEnTablaDeFunciones(var->obtenerIdentificador(), var->obtenerIdDeExpresion()) )
        {
            throw(ExcepcionLegus("Variable 'ReemplazarPorVariable' esta siendo utilizada en funcion 'FUNCION'",numeroDeLinea));
        }

        if( expresion != 0)
        {
            var->tipoInferido = this->expresion->validarSemantica();
            Programa::obtenerInstancia()->actualizarVariableADeclarar(var->obtenerIdentificador(), var->obtenerIdDeExpresion(), var->tipoInferido);
        }
    }

    if( obtenerSiguiente() != 0)
    {
        obtenerSiguiente()->validarSemantica();
    }
}

Expresion* InstruccionAsignacion::obtenerExpresion()
{
    return this->expresion;
}

Expresion* InstruccionAsignacion::obtenerVariable()
{
    return this->variable;
}

string InstruccionAsignacion::generarCodigoJava()
{
    /*
    Caso, buscar nombre de variable
        1. si ya existe verificar que la expresion reduzca al mismo tipo en que esta declarado
        2. si no existe declarar la variable.
    */
    stringstream codigoAsignacion;

    if( variable->tipo == VARIABLENORMAL )
    {
        string codigoVariable = this->variable->generarCodigoJava();
        Variable *var = (Variable*)variable;
        this->expresion->validarSemantica();
        VariableDeclarada* variableDeclarada = Programa::obtenerInstancia()->existeVariable(var->obtenerIdentificador(), var->obtenerIdDeExpresion());
        if( variableDeclarada == 0 )
        {
            //Programa::obtenerInstancia()->tablaDeVariablesADeclarar->push_back(new VariableADeclarar(var->obtenerIdentificador(),var->validarSemantica(), var->obtenerIdDeExpresion()));
            Programa::obtenerInstancia()->agregarVariableADeclarar(var->obtenerIdentificador(), var->validarSemantica(), var->obtenerIdDeExpresion());
            /*No hay variable*/
            //codigoAsignacion << codigoVariable;
            codigoAsignacion << "$";
            codigoAsignacion << var->obtenerIdDeExpresion();
            /*Falta el nombre de la variables*/
            codigoAsignacion << var->obtenerIdentificador()->c_str();
                /*InstruccionPara*/ variableConIdDeExpresion = codigoAsignacion.str();
            codigoAsignacion << " = ";
            codigoAsignacion << this->expresion->generarCodigoJava();
            codigoAsignacion << "; \n";
        }
        else if( variableDeclarada != 0 && variableDeclarada->obtenerTipo()->tipo == this->expresion->tipoInferido->tipo)
        {
            /*
                Ya existe y es del mismo tipo
                    Verificar si es arreglo!
            */
            /*Selectivo que sea igual que el de var*/
            Programa::obtenerInstancia()->establecerIdDeExpresionAVariable(var->obtenerIdDeExpresion(), variableDeclarada->obtenerIdDeExpresion());
            codigoAsignacion << "$";
            codigoAsignacion << variableDeclarada->obtenerIdDeExpresion();
            /*Falta el nombre de la variables*/
            codigoAsignacion << variableDeclarada->obtenerVariable()->obtenerIdentificador()->c_str();
            if( this->expresion->tipoInferido->tipo == Arreglo )
            {
            }
            else
            {
                /*InstruccionPara*/ variableConIdDeExpresion = codigoAsignacion.str();
                codigoAsignacion << " = ";
            }

            codigoAsignacion << this->expresion->generarCodigoJava();
            codigoAsignacion << "; \n";
        }
        else
        {
            //Programa::obtenerInstancia()->tablaDeVariablesADeclarar->push_back(new VariableADeclarar(var->obtenerIdentificador(),var->validarSemantica(), var->obtenerIdDeExpresion()));
            Programa::obtenerInstancia()->agregarVariableADeclarar(var->obtenerIdentificador(), var->validarSemantica(), var->obtenerIdDeExpresion());
            /*Ya existe y el tipo no es igual*/
            //codigoAsignacion << codigoVariable;
            codigoAsignacion << "$";
            codigoAsignacion << var->obtenerIdDeExpresion();
            /*Falta el nombre de la variables*/
            codigoAsignacion << var->obtenerIdentificador()->c_str();
                /*InstruccionPara*/ variableConIdDeExpresion = codigoAsignacion.str();
            codigoAsignacion << " = ";
            codigoAsignacion << this->expresion->generarCodigoJava();
            codigoAsignacion << "; \n";
        }
    }
    else if(variable->tipo == ARREGLO)
    {
        /*Verificar si ya existe el arreglo*/
        VariableArreglo *var = (VariableArreglo*)variable;
        codigoAsignacion << "ArrayList<Object> ";
        codigoAsignacion << "$";
        codigoAsignacion << var->obtenerIdDeExpresion();
        codigoAsignacion << var->obtenerIdentificador()->c_str();
        codigoAsignacion << " = new ArrayList<Object>();\n";
    }

    /*if( obtenerSiguiente() != 0)
    {
        codigoAsignacion << obtenerSiguiente()->generarCodigoJava();
    }*/

    return codigoAsignacion.str();
}

string InstruccionAsignacion::obtenerVariableConIdDeExpresion()
{
    return this->variableConIdDeExpresion;
}
