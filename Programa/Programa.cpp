#include "Programa/Programa.h"

Programa* Programa::instancia = 0;

Programa::Programa()
{
    this->tablaDeFunciones = new vector<DeclaracionDeFuncion*>();
    this->tablaDeVariables = new vector<VariableDeclarada*>();
    this->tablaDePuertosYSensores = new vector<DeclaracionUtilizar*>();
    this->tablaDeVariablesADeclarar = new vector<VariableADeclarar*>();

    this->tablaDeUsoDeFunciones = new map<string, Funcion*>();
    this->codigoDefunciones = 0;
    compilarParaNxt = true;

    /*Instancia de los tipos*/
    this->tipoBooleano = new TipoBooleano();
    this->tipoCadena = new TipoCadena();
    this->tipoCaracter = new TipoCaracter();
    this->tipoEntero = new TipoEntero();
    this->tipoFlotante = new TipoFlotante();
    this->tipoArreglo = new TipoArreglo();
    this->tipoMotor = new TipoMotor();
    this->tipoSensorDeBrujula = new TipoSensorDeBrujula();
    this->tipoSensorDeColor = new TipoSensorDeColor();
    this->tipoSensorDeInclinacion = new TipoSensorDeInclinacion();
    this->tipoSensorDeLuz = new TipoSensorDeLuz();
    this->tipoSensorDeSonido = new TipoSensorDeSonido();
    this->tipoSensorDeTacto = new TipoSensorDeTacto();
    this->tipoSensorGiroscopico = new TipoSensorGiroscopico();
    this->tipoSensorUltrasonico = new TipoSensorUltrasonico();
}

Programa* Programa::obtenerInstancia()
{
    if(!instancia)
    {
        instancia = new Programa();
        instancia->cargarFuncionesIncorporadas();
        instancia->cargarCodigoFunciones();
    }
    return instancia;
}

TipoBooleano* Programa::obtenerTipoBooleano()
{
    return this->tipoBooleano;
}

TipoCadena* Programa::obtenerTipoCadena()
{
    return this->tipoCadena;
}

TipoCaracter* Programa::obtenerTipoCaracter()
{
    return this->tipoCaracter;
}

TipoEntero* Programa::obtenerTipoEntero()
{
    return this->tipoEntero;
}

TipoFlotante* Programa::obtenerTipoFlotante()
{
    return this->tipoFlotante;
}

TipoArreglo*  Programa::obtenerTipoArreglo()
{
    return this->tipoArreglo;
}

TipoMotor* Programa::obtenerTipoMotor()
{
    return this->tipoMotor;
}

TipoSensorDeBrujula* Programa::obtenerTipoSensorDeBrujula()
{
    return this->tipoSensorDeBrujula;
}

TipoSensorDeColor* Programa::obtenerTipoSensorDeColor()
{
    return this->tipoSensorDeColor;
}

TipoSensorDeInclinacion* Programa::obtenerTipoSensorDeInclinacion()
{
    return this->tipoSensorDeInclinacion;
}

TipoSensorDeLuz* Programa::obtenerTipoSensorDeLuz()
{
    return this->tipoSensorDeLuz;
}

TipoSensorDeSonido* Programa::obtenerTipoSensorDeSonido()
{
    return this->tipoSensorDeSonido;
}

TipoSensorDeTacto* Programa::obtenerTipoSensorDeTacto()
{
    return this->tipoSensorDeTacto;
}

TipoSensorGiroscopico* Programa::obtenerTipoSensorGiroscopico()
{
    return this->tipoSensorGiroscopico;
}

TipoSensorUltrasonico* Programa::obtenerTipoSensorUltrasonico()
{
    return this->tipoSensorUltrasonico;
}

VariableDeclarada* Programa::existeVariable(string *identificador, int idDeExpresion)
{
    vector<VariableDeclarada*> *variables = Programa::obtenerInstancia()->tablaDeVariables;
    VariableDeclarada* ultimaVariable = 0;

    for(unsigned int i = 0 ; i< variables->size(); i++)
    {
        VariableDeclarada* variable = variables->at(i);
        /*mismo identificador y que posea un idDeExpresion menor al mio*/
        if( variable->obtenerVariable()->obtenerIdentificador()->compare( *identificador ) == 0 &&
            variable->obtenerIdDeExpresion() < idDeExpresion)
        {
            ultimaVariable = variable;
        }
    }

    return ultimaVariable;
}

DeclaracionDeFuncion* Programa::existeEnTablaDeFunciones(string *identificador, int idDeExpresion)
{
    for(unsigned int i = 0; i< tablaDeFunciones->size(); i++)
    {
        DeclaracionDeFuncion *declaracion = tablaDeFunciones->at(i);
        if( identificador->compare(*declaracion->obtenerVariable()->obtenerIdentificador())==0)
        {
            return declaracion;
        }
    }
    return 0;
}

DeclaracionUtilizar* Programa::existeEnTablaDePuertosYSensores(string *identificador)
{
    for(unsigned int i = 0; i< tablaDePuertosYSensores->size(); i++)
    {
        DeclaracionUtilizar *declaracion = tablaDePuertosYSensores->at(i);
        if(identificador->compare(*declaracion->obtenerVariable()->obtenerIdentificador())==0)
        {
            return declaracion;
        }
    }
    return 0;
}

bool Programa::existePuerto(string *puerto)
{
    for(unsigned int i = 0; i< tablaDePuertosYSensores->size(); i++)
    {
        DeclaracionUtilizar *declaracion = tablaDePuertosYSensores->at(i);
        if(strcmpi(puerto->c_str(), declaracion->obtenerPuerto()->obtenerIdentificador()->c_str())==0)
        {
            return true;
        }
    }
    return false;
}

/*El primero es el id de expresion de la variable que quiero cambiar
    el segundo es el valor que le pondre
*/
void  Programa::establecerIdDeExpresionAVariable(int idExpresion, int idExpresionACambiar)
{
    for(unsigned int i = 0 ; i< this->tablaDeVariables->size(); i++)
    {
        VariableDeclarada* variable = this->tablaDeVariables->at(i);
        /*mismo identificador y que posea un idDeExpresion menor al mio*/
        if( variable->obtenerIdDeExpresion() == idExpresion)
        {
            variable->establecerIdDeExpresion(idExpresionACambiar);
        }
    }
}

void Programa::limpiarInstancia()
{
    this->instancia = 0;
    delete instrucciones;
    delete tablaDeFunciones;
    delete tablaDePuertosYSensores;
    delete tablaDeVariables;
    delete tablaDeVariablesADeclarar;
    delete tipoBooleano;
    delete tipoCadena;
    delete tipoCaracter;
    delete tipoEntero;
    delete tipoFlotante;
    delete tipoArreglo;
    delete tipoMotor;
    delete tipoSensorDeBrujula;
    delete tipoSensorDeColor;
    delete tipoSensorDeInclinacion;
    delete tipoSensorDeLuz;
    delete tipoSensorDeSonido;
    delete tipoSensorDeTacto;
    delete tipoSensorGiroscopico;
    delete tipoSensorUltrasonico;
    delete funcionesIncorporadas;
    delete tablaDeUsoDeFunciones;
    delete codigoDefunciones;
}

string Programa::obtenerCodigoVariablesADeclarar()
{
    stringstream resultado;
    for(unsigned int i = 0; i<this->tablaDeVariablesADeclarar->size(); i++)
    {
        VariableADeclarar *variable = this->tablaDeVariablesADeclarar->at(i);
        Tipo *tipoVariable = variable->tipo;

        if( tipoVariable->tipo == Entero )
        {
            resultado << "int ";
            resultado << "$";
            resultado << variable->id;
            resultado << *variable->variable;
            resultado << "=0;";
        }

        if( tipoVariable->tipo == Flotante )
        {
            resultado << "float ";
            resultado << "$";
            resultado << variable->id;
            resultado << *variable->variable;
            resultado << "=0.0f;";
        }

        if( tipoVariable->tipo == Caracter)
        {
            resultado << "char ";
            resultado << "$";
            resultado << variable->id;
            resultado << *variable->variable;
            resultado << "=' ';";
        }

        if( tipoVariable->tipo == Cadena)
        {
            resultado << "String ";
            resultado << "$";
            resultado << variable->id;
            resultado << *variable->variable;
            resultado << "=\"\";";
        }

        if( tipoVariable->tipo == Booleano )
        {
            resultado << "boolean ";
            resultado << "$";
            resultado << variable->id;
            resultado << *variable->variable;
            resultado << "=false;";
        }

        resultado << "\n";
    }
    return resultado.str();
}

/*Cargas las funciones incorporadas en Legus*/
void Programa::cargarFuncionesIncorporadas()
{
    FuncionesIncorporadas fi;
    this->funcionesIncorporadas = fi.obtenerFuncionesIncorporadas();
}

void Programa::cargarCodigoFunciones()
{
    FuncionesIncorporadas fi;
    this->codigoDefunciones = fi.obtenerCodigoFunciones();
}

string Programa::obtenerCodigoFuente(string nombreArchivo,
                                     string inclusiones,
                                     string funcsIncorporadas,
                                     string declaracionFunciones,
                                     string bloqueCodigo)
{
    stringstream codigoFuente;
    codigoFuente << inclusiones;
    codigoFuente << "public class ";
    codigoFuente << nombreArchivo;
    codigoFuente << "{\n";

        codigoFuente << funcsIncorporadas;
        codigoFuente << "\n";
        codigoFuente << declaracionFunciones;

        codigoFuente << "public static void main(String args[])";
        codigoFuente << "{\n";
            codigoFuente << obtenerCodigoVariablesADeclarar();
            codigoFuente << bloqueCodigo;
            codigoFuente << "\n";
        codigoFuente << "}\n";
    codigoFuente << "}\n";

    return codigoFuente.str();
}

Funcion* Programa::existeFuncionIncorporada(string nombreFuncion, Lista *parametros)
{
    /*a minusculas*/
    transform(nombreFuncion.begin(), nombreFuncion.end(), nombreFuncion.begin(), ::tolower);

    // transformarlo a una entrada en la tabla
    string nombre = convertirAEntradaEnTabla(nombreFuncion, parametros);

    Funcion* encontrado = 0;
    if( funcionesIncorporadas->find(nombre) != funcionesIncorporadas->end())
    {
        /*Existe!*/
        Funcion* funcion = (*funcionesIncorporadas)[nombre];
        return funcion;
    }
    return encontrado;
}

Tipo* Programa::obtenerTipoEnBaseATipoParametro(TipoParametro tipoParam)
{
    if(tipoParam == TEntero)
    {
        return tipoEntero;
    }
    else if( tipoParam == TFlotante)
    {
        return tipoFlotante;
    }
    else if( tipoParam == TCadena)
    {
        return tipoCadena;
    }
    else if(tipoParam == TCaracter)
    {
        return tipoCaracter;
    }
    else if(tipoParam == TBooleano)
    {
        return tipoBooleano;
    }
    else if( tipoParam == TMotor)
    {
        return tipoMotor;
    }
    else if( tipoParam == TSensorDeBrujula)
    {
        return tipoSensorDeBrujula;
    }
    else if( tipoParam == TSensorDeColor)
    {
        return tipoSensorDeColor;
    }
    else if( tipoParam == TSensorDeInclinacion)
    {
        return tipoSensorDeInclinacion;
    }
    else if( tipoParam == TSensorDeLuz)
    {
        return tipoSensorDeLuz;
    }
    else if( tipoParam == TSensorDeSonido)
    {
        return tipoSensorDeSonido;
    }
    else if( tipoParam == TSensorDeTacto)
    {
        return tipoSensorDeTacto;
    }
    else if( tipoParam == TSensorGiroscopico)
    {
        return tipoSensorGiroscopico;
    }
    else if( tipoParam == TSensorUltrasonico)
    {
        return tipoSensorUltrasonico;
    }
    return 0;
}

string Programa::obtenerTipoEnBaseATipo(Tipo *tipo)
{
    if(tipo==tipoEntero)                    return "entero";
    else if(tipo==tipoMotor)                return "motor";
    else if(tipo==tipoFlotante)             return "flotante";
    else if(tipo==tipoCadena)               return "cadena";
    else if(tipo==tipoCaracter)             return "caracter";
    else if(tipo==tipoBooleano)             return "booleano";
    else if(tipo==tipoSensorDeBrujula)      return "brujula";
    else if(tipo==tipoSensorDeColor)        return "color";
    else if(tipo==tipoSensorDeInclinacion)  return "inclinacion";
    else if(tipo==tipoSensorDeLuz)          return "luz";
    else if(tipo==tipoSensorDeSonido)       return "sonido";
    else if(tipo==tipoSensorDeTacto)        return "tacto";
    else if(tipo==tipoSensorGiroscopico)    return "giroscopico";
    else if(tipo==tipoSensorUltrasonico)    return "ultrasonico";
    return "";
}

bool Programa::obtenerTipoDeCompilacion()
{
    return this->compilarParaNxt;
}

void Programa::agregarUsoDeFuncionATabla(string id, Lista *params, Funcion *funcion)
{
    string nombre = convertirAEntradaEnTabla(id, params);
    if( tablaDeUsoDeFunciones->find(nombre) == tablaDeUsoDeFunciones->end())
    {
        // No existe...
        (*tablaDeUsoDeFunciones)[nombre] = funcion;
    }
}

string Programa::convertirAEntradaEnTabla(string nombreFuncion, Lista *parametros)
{
    stringstream nfunc;
    nfunc << nombreFuncion;
    nfunc << "|";

    for(int k = parametros->lista->size()-1; k>=0; k--)
    {
        Expresion *expr = parametros->lista->at(k);
        nfunc << obtenerTipoEnBaseATipo(expr->validarSemantica());

        if(k!=0)
        {
            nfunc << ",";
        }
    }
    return nfunc.str();
}

string Programa::obtenerCodigoFunciones()
{
    stringstream codigoFuncs;
    map<string, Funcion*>::iterator it;
    for(it = tablaDeUsoDeFunciones->begin();
        it != tablaDeUsoDeFunciones->end();
        it++)
    {
        string codigo = (*it).first;

        if( this->codigoDefunciones != 0)
        {
            if(this->codigoDefunciones->find(codigo) != codigoDefunciones->end())
            {
                codigoFuncs << (*this->codigoDefunciones)[codigo];
                codigoFuncs << "\n";
            }
        }
    }
    return codigoFuncs.str();
}

void Programa::validarSemantica()
{
    Instruccion *actual = this->instrucciones;
    while(actual!=0)
    {
        actual->validarSemantica();
        actual = actual->obtenerSiguiente();
    }
}

void Programa::generarArchivo(string nombreArchivo)
{
    // Revisar si el codigo esta correcto
    validarSemantica();

    // generar el archivo
    string codigoPrograma = obtenerCodigoFuente(nombreArchivo,
                                                obtenerInclusiones(),
                                                obtenerCodigoFunciones(),
                                                "",
                                                obtenerCodigoInstrucciones());

    ofstream archivo;
    string nombre = nombreArchivo + ".java";
    archivo.open(nombre.c_str());
        archivo << codigoPrograma.c_str();
    archivo.close();
}

string Programa::obtenerCodigoInstrucciones()
{
    string codigo="";
    Instruccion *actual = this->instrucciones;
    while(actual!=0)
    {
        codigo += actual->generarCodigoJava();
        actual = actual->obtenerSiguiente();
    }

    return codigo;
}

string Programa::obtenerInclusiones()
{
    return "import lejos.nxt.*;\n"
           "import lejos.util.*;\n"
           "import java.util.ArrayList;\n";
}
