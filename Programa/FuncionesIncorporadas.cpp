#include "Programa/FuncionesIncorporadas.h"

FuncionesIncorporadas::FuncionesIncorporadas()
{
}

map<string, Funcion*>* FuncionesIncorporadas::obtenerFuncionesIncorporadas()
{
    /*�Como manejar el tipo de retorno? ... Like a Boss!*/
    bool compilarNxt = Programa::obtenerInstancia()->obtenerTipoDeCompilacion();

    map<string, Funcion*> *funcionesIncorporadas = new map<string, Funcion*>();

    /*Escriba!*/
    (*funcionesIncorporadas)["escriba|entero"] = new Funcion( 0, obtenerVectorParametros(1, TEntero));
    (*funcionesIncorporadas)["escriba|flotante"] = new Funcion( 0, obtenerVectorParametros(1, TFlotante));
    (*funcionesIncorporadas)["escriba|caracter"] = new Funcion( 0, obtenerVectorParametros(1, TCaracter));
    (*funcionesIncorporadas)["escriba|cadena"] = new Funcion( 0, obtenerVectorParametros(1, TCadena));
    (*funcionesIncorporadas)["escriba|booleano"] = new Funcion( 0, obtenerVectorParametros(1, TBooleano));

    if( compilarNxt )
    {
        (*funcionesIncorporadas)["escriba|entero,entero,entero"] = new Funcion( 0, obtenerVectorParametros(3, TEntero, TEntero, TEntero));
        (*funcionesIncorporadas)["escriba|flotante,entero,entero"] = new Funcion( 0, obtenerVectorParametros(3, TFlotante, TEntero, TEntero));
        (*funcionesIncorporadas)["escriba|caracter,entero,entero"] = new Funcion( 0, obtenerVectorParametros(3, TCaracter, TEntero, TEntero));
        (*funcionesIncorporadas)["escriba|cadena,entero,entero"] = new Funcion( 0, obtenerVectorParametros(3, TCadena, TEntero, TEntero));
        (*funcionesIncorporadas)["escriba|booleano,entero,entero"] = new Funcion( 0, obtenerVectorParametros(3, TBooleano, TEntero, TEntero));

        /*Con Retorno*/
        /*Leer*/

        /*********************************************************************************/

        /*Lego NXT*/
        /*Funciones incorporadas para LCD*/
        (*funcionesIncorporadas)["limpiar_pantalla"] = new Funcion(0 , obtenerVectorParametros(0) );

        /*Funciones Incorporadas para MOTORES*/
        /*Adelante*/
        (*funcionesIncorporadas)["adelante|motor"] = new Funcion(0 , obtenerVectorParametros(1, TMotor));

        /*Atras*/
        (*funcionesIncorporadas)["atras|motor"] = new Funcion(0 , obtenerVectorParametros(1, TMotor));

        /*Detener*/
        (*funcionesIncorporadas)["detener|motor"] = new Funcion(0 , obtenerVectorParametros(1, TMotor));
        (*funcionesIncorporadas)["detener|motor,booleano"] = new Funcion(0 , obtenerVectorParametros(2, TMotor, TBooleano));

        /*RotarMotor*/
        (*funcionesIncorporadas)["rotar_motor|motor,entero"] = new Funcion(0 , obtenerVectorParametros(2, TMotor, TEntero));

        /*RotarMotorConRetorno*/
        (*funcionesIncorporadas)["rotar_motor|motor,entero,booleano"] = new Funcion(0 , obtenerVectorParametros(3, TMotor, TEntero, TBooleano));

        /*RotarMotorHacia*/
        (*funcionesIncorporadas)["rotar_motor_hacia|motor,entero"] = new Funcion(0 , obtenerVectorParametros(2, TMotor, TEntero));

        /*RotarMotorHaciaConRetorno*/
        (*funcionesIncorporadas)["rotar_motor_hacia|motor,entero,booleano"] = new Funcion(0 , obtenerVectorParametros(3, TMotor, TEntero,TBooleano));

        /*Establecer Velocidad*/
        (*funcionesIncorporadas)["establecer_velocidad|motor,entero"] = new Funcion(0 , obtenerVectorParametros(2, TMotor, TEntero));

        /*Obtener Angulo*/
        (*funcionesIncorporadas)["obtener_angulo|motor"] = new Funcion( obtenerTipo(TEntero) , obtenerVectorParametros(1, TMotor));

        /*Obtener Velocidad*/
        (*funcionesIncorporadas)["obtener_velocidad|motor"] = new Funcion( obtenerTipo(TEntero) , obtenerVectorParametros(1, TMotor));

        /*EstaEnMovimiento*/
        (*funcionesIncorporadas)["esta_en_movimiento|motor"] = new Funcion( obtenerTipo(TBooleano), obtenerVectorParametros(1, TMotor));

        /*Bloquear*/
        (*funcionesIncorporadas)["bloquear|motor,entero"] = new Funcion(0 , obtenerVectorParametros(2, TMotor, TEntero));

        /*EsperarCompletacion???*/

        /*Funciones Incorporadas para SENSORES*/
        /*Sensor Ultrasonico*/
        (*funcionesIncorporadas)["obtener_distancia|ultrasonico"] = new Funcion( obtenerTipo(TEntero), obtenerVectorParametros(1, TSensorUltrasonico));

        /*Sensor de Tacto*/
        (*funcionesIncorporadas)["esta_presionado|tacto"] = new Funcion( obtenerTipo(TBooleano), obtenerVectorParametros(1, TSensorDeTacto));

        /*Sensor de Luz*/
        (*funcionesIncorporadas)["obtener_luz|luz"] = new Funcion( obtenerTipo(TEntero), obtenerVectorParametros(1, TSensorDeLuz)) ;
        (*funcionesIncorporadas)["establecer_inundacion|luz,booleano"] = new Funcion( obtenerTipo(TEntero), obtenerVectorParametros(2, TSensorDeLuz, TBooleano) );

        /*Sensor de Color*/
        /*Sensor de Inclinacion*/
        /*Sensor de Sonido ? */
        /*Sensor Giroscopico ?*/
        /*Sensor de Brujula ? */

        /*Funciones INCORPORADAS PARA BOTONES DE NXT*/
        /*Izq, Der, enter, escape*/

        // Eventos Test...
        (*funcionesIncorporadas)["cuando_se_presione|boton_derecho,funcion"] = new Funcion(0, obtenerVectorParametros(2, TBotonDerecho, _TFuncion));
        (*funcionesIncorporadas)["cuando_se_presione|boton_izquierdo,funcion"] = new Funcion(0, obtenerVectorParametros(2, TBotonDerecho, _TFuncion));
        (*funcionesIncorporadas)["cuando_se_presione|boton_central,funcion"] = new Funcion(0, obtenerVectorParametros(2, TBotonDerecho, _TFuncion));
        (*funcionesIncorporadas)["cuando_se_presione|boton_escape,funcion"] = new Funcion(0, obtenerVectorParametros(2, TBotonDerecho, _TFuncion));

        // esta presionado
        (*funcionesIncorporadas)["esta_presionado|boton_derecho"] = new Funcion(obtenerTipo(TBooleano), obtenerVectorParametros(1, TBotonDerecho));
        (*funcionesIncorporadas)["esta_presionado|boton_izquierdo"] = new Funcion(obtenerTipo(TBooleano), obtenerVectorParametros(1, TBotonIzquierdo));
        (*funcionesIncorporadas)["esta_presionado|boton_central"] = new Funcion(obtenerTipo(TBooleano), obtenerVectorParametros(1, TBotonCentral));
        (*funcionesIncorporadas)["esta_presionado|boton_escape"] = new Funcion(obtenerTipo(TBooleano), obtenerVectorParametros(1, TBotonEscape));

        // EsperarPresion
        (*funcionesIncorporadas)["esperar_presion|boton_derecho"] = new Funcion(0, obtenerVectorParametros(1, TBotonDerecho));
        (*funcionesIncorporadas)["esperar_presion|boton_izquierdo"] = new Funcion(0, obtenerVectorParametros(1, TBotonIzquierdo));
        (*funcionesIncorporadas)["esperar_presion|boton_central"] = new Funcion(0, obtenerVectorParametros(1, TBotonCentral));
        (*funcionesIncorporadas)["esperar_presion|boton_escape"] = new Funcion(0, obtenerVectorParametros(1, TBotonEscape));

        // EsperarPresionYLiberacion
        (*funcionesIncorporadas)["esperar_presion_liberacion|boton_derecho"] = new Funcion(0, obtenerVectorParametros(1, TBotonDerecho));
        (*funcionesIncorporadas)["esperar_presion_liberacion|boton_izquierdo"] = new Funcion(0, obtenerVectorParametros(1, TBotonIzquierdo));
        (*funcionesIncorporadas)["esperar_presion_liberacion|boton_central"] = new Funcion(0, obtenerVectorParametros(1, TBotonCentral));
        (*funcionesIncorporadas)["esperar_presion_liberacion|boton_escape"] = new Funcion(0, obtenerVectorParametros(1, TBotonEscape));

        // Delay
        (*funcionesIncorporadas)["esperar|entero"] = new Funcion( 0, obtenerVectorParametros(1, TEntero) );
        (*funcionesIncorporadas)["salir"] = new Funcion(0, obtenerVectorParametros(0));

        // sonido!
        (*funcionesIncorporadas)["tono|entero,entero"] = new Funcion(0, obtenerVectorParametros(2, TEntero, TEntero));
        (*funcionesIncorporadas)["tono|entero,entero,entero"] = new Funcion(0, obtenerVectorParametros(3, TEntero, TEntero, TEntero));
    }

    /*Extras!*/
    //Random
    (*funcionesIncorporadas)["numero_aleatorio|entero"] = new Funcion( obtenerTipo(TEntero), obtenerVectorParametros(1, TEntero) );
    (*funcionesIncorporadas)["numero_aleatorio|entero,entero"] = new Funcion( obtenerTipo(TEntero), obtenerVectorParametros(2, TEntero, TEntero) );

    // Delay
    //(*funcionesIncorporadas)["esperar|entero"] = new Funcion( 0, obtenerVectorParametros(1, TEntero) );
    (*funcionesIncorporadas)["obtener_cantidad|arreglo"] = new Funcion( obtenerTipo(TEntero),obtenerVectorParametros(1, TArreglo) );

    return funcionesIncorporadas;
}

vector<TipoParametro>* FuncionesIncorporadas::obtenerVectorParametros(int cantidadArgumentos, ...)
{
    vector<TipoParametro>* vect = new vector<TipoParametro>();

    if( cantidadArgumentos == 0)
    {
        return vect;
    }

    va_list argumentos;
    va_start(argumentos, cantidadArgumentos);

    for(int i=0; i<cantidadArgumentos; i++)
    {
        /*Esta onda esta bien QtCreator es el loco*/
        int tParametro= va_arg(argumentos, int );
        vect->push_back((TipoParametro)tParametro);
    }
    va_end(argumentos);
    return vect;
}

Tipo* FuncionesIncorporadas::obtenerTipo(TipoParametro tipoParam)
{
    if(tipoParam == TEntero)
    {
        return Programa::obtenerInstancia()->obtenerTipoEntero();
    }
    else if( tipoParam == TFlotante)
    {
        return Programa::obtenerInstancia()->obtenerTipoFlotante();
    }
    else if( tipoParam == TCadena)
    {
        return Programa::obtenerInstancia()->obtenerTipoCadena();
    }
    else if(tipoParam == TCaracter)
    {
        return Programa::obtenerInstancia()->obtenerTipoCaracter();
    }
    else if(tipoParam == TBooleano)
    {
        return Programa::obtenerInstancia()->obtenerTipoBooleano();
    }
    else if( tipoParam == TArreglo)
    {
        return Programa::obtenerInstancia()->obtenerTipoArreglo();
    }
    else if( tipoParam == _TFuncion)
    {
        return Programa::obtenerInstancia()->obtenerTipoFuncion();
    }
    return 0;
}

map<string, string>* FuncionesIncorporadas::obtenerCodigoFunciones()
{
    // Estas funciones estan hard-coded para mejorar el rendimiento
    bool compilarNxt = Programa::obtenerInstancia()->obtenerTipoDeCompilacion();
    map<string, string>* codigo = new map<string, string>();

    /*UniPrograma(para pc y nxt) -> Como Unisex*/
    /*Escriba*/
    (*codigo)["escriba|entero"] = compilarNxt?
              "public static void escriba(int i){LCD.drawInt(i,0,0);LCD.refresh();}" :
              "public static void escriba(int i){System.out.println(i+\"\");}";
    (*codigo)["escriba|flotante"] = compilarNxt?
              "public static void escriba(float f){LCD.drawString(f+\"\",0,0);LCD.refresh();}":
              "public static void escriba(float f){System.out.println(f+\"\");}";
    (*codigo)["escriba|caracter"] = compilarNxt?
              "public static void escriba(char c){LCD.drawString(c+\"\",0,0);LCD.refresh();}":
              "public static void escriba(char c){System.out.println(c+\"\");}";
    (*codigo)["escriba|cadena"] = compilarNxt?
              "public static void escriba(String s){LCD.drawString(s,0,0);LCD.refresh();}":
              "public static void escriba(String s){System.out.println(s+\"\");}";
    (*codigo)["escriba|booleano"] = compilarNxt?
              "public static void escriba(boolean b){LCD.drawString(b+\"\",0,0);LCD.refresh();}":
              "public static void escriba(boolean b){System.out.println(b+\"\");}";

    (*codigo)["escriba|entero,entero,entero"] = compilarNxt?
              "public static void escriba(int i,int x,int y){LCD.drawInt(i,x,y);LCD.refresh();}":
              "";
    (*codigo)["escriba|flotante,entero,entero"] = compilarNxt?
              "public static void escriba(float f,int x,int y){LCD.drawString(f+\"\",x,y);LCD.refresh();}":
              "";
    (*codigo)["escriba|caracter,entero,entero"] = compilarNxt?
              "public static void escriba(char c,int x, int y){LCD.drawString(c+\"\",x,y);LCD.refresh();}":
              "";
    (*codigo)["escriba|cadena,entero,entero"] = compilarNxt?
              "public static void escriba(String s,int x,int y){LCD.drawString(s,x,y);LCD.refresh();}":
              "";
    (*codigo)["escriba|booleano,entero,entero"] = compilarNxt?
              "public static void escriba(boolean b,int x,int y){LCD.drawString(b+\"\",x,y);LCD.refresh();}":
              "";

    if( compilarNxt )
    {
        /*NXT*/
        /*LCD*/
        (*codigo)["limpiar_pantalla"] = "public static void limpiar_pantalla(){LCD.clear();}";

        //Motores
        (*codigo)["adelante|motor"] =                    "public static void adelante(NXTRegulatedMotor m){m.forward();}";
        (*codigo)["atras|motor"] =                       "public static void atras(NXTRegulatedMotor m){m.backward();}";
        (*codigo)["detener|motor"] =                     "public static void detener(NXTRegulatedMotor m){m.stop();}";
        (*codigo)["detener|motor,booleano"] =            "public static void detener(NXTRegulatedMotor m,boolean b){m.stop(b);}";
        (*codigo)["rotar_motor|motor,entero"] =          "public static void rotar_motor(NXTRegulatedMotor m,int r){m.rotate(r);}";
        (*codigo)["rotar_motor|motor,entero,booleano"] = "public static void rotar_motor(NXTRegulatedMotor m,int r,boolean b){m.rotate(r,b);}";
        (*codigo)["rotar_motor_hacia|motor,entero"] =       "public static void rotar_motor_hacia(NXTRegulatedMotor m,int r){m.rotateTo(r);}";
        (*codigo)["rotar_motor_hacia|motor,entero,booleano"] = "public static void rotar_motor_hacia(NXTRegulatedMotor m,int r,boolean b){m.rotateTo(r,b);}";
        (*codigo)["establecer_velocidad|motor,entero"] =    "public static void establecer_velocidad(NXTRegulatedMotor m,int v){m.setSpeed(v);}";
        (*codigo)["obtener_angulo|motor"] =                 "public static int obtener_angulo(NXTRegulatedMotor m){return m.getLimitAngle();}";
        (*codigo)["obtener_velocidad|motor"] =              "public static int obtener_velocidad(NXTRegulatedMotor m){return m.getSpeed();}";
        (*codigo)["esta_en_movimiento|motor"] =             "public static boolean esta_en_movimiento(NXTRegulatedMotor m){return m.isMoving();}";
        (*codigo)["bloquear|motor,entero"] =                "public static void bloquear(NXTRegulatedMotor m,int p){m.lock(p);}";

        //Sensores
        // UltraSonico
        (*codigo)["obtener_distancia|ultrasonico"] = "public static int obtener_distancia(UltrasonicSensor s){return s.getDistance();}";

        //Tacto
        (*codigo)["esta_presionado|tacto"] = "";

        //Luz
        (*codigo)["obtener_luz|luz"] = "public static int obtener_luz(LightSensor s){return s.readValue();}";
        (*codigo)["establecer_inundacion|luz,booleano"] = "public static void establecer_inundacion(LightSensor s, boolean b){s.setFloodlight(b);}";

        //Botones LCD

        // esta_presionado
        (*codigo)["esta_presionado|boton_derecho"] = "public static boolean esta_presionado(Button b){return b.isPressed();}";
        (*codigo)["esta_presionado|boton_izquierdo"] = "public static boolean esta_presionado(Button b){return b.isPressed();}";
        (*codigo)["esta_presionado|boton_central"] = "public static boolean esta_presionado(Button b){return b.isPressed();}";
        (*codigo)["esta_presionado|boton_escape"] = "public static boolean esta_presionado(Button b){return b.isPressed();}";

        // EsperarPresion
        (*codigo)["esperar_presion|boton_derecho"] = "public static void esperar_presion(Button b){b.waitForPress();}";
        (*codigo)["esperar_presion|boton_izquierdo"] = "public static void esperar_presion(Button b){b.waitForPress();}";
        (*codigo)["esperar_presion|boton_central"] = "public static void esperar_presion(Button b){b.waitForPress();}";
        (*codigo)["esperar_presion|boton_escape"] = "public static void esperar_presion(Button b){b.waitForPress();}";

        // EsperarPresionYLiberacion
        (*codigo)["esperar_presion_liberacion|boton_derecho"] = "public static void esperar_presion_liberacion(Button b){b.waitForPressAndRelease();}";
        (*codigo)["esperar_presion_liberacion|boton_izquierdo"] = "public static void esperar_presion_liberacion(Button b){b.waitForPressAndRelease();}";
        (*codigo)["esperar_presion_liberacion|boton_central"] = "public static void esperar_presion_liberacion(Button b){b.waitForPressAndRelease();}";
        (*codigo)["esperar_presion_liberacion|boton_escape"] = "public static void esperar_presion_liberacion(Button b){b.waitForPressAndRelease();}";

        (*codigo)["esperar|entero"] = "public static void esperar(int t){Delay.msDelay(t);}";

        // Eventos, falta ver como van a funcionar
        (*codigo)["cuando_se_presione|boton_derecho"] = "Button.RIGHT.addButtonListener(new ButtonListener(){public void buttonPressed(Button b) {$$_REEMPLAZAR_POR_CODIGO_$$}});";
        (*codigo)["cuando_se_presione|boton_izquierdo"] = "Button.LEFT.addButtonListener(new ButtonListener(){public void buttonPressed(Button b) {$$_REEMPLAZAR_POR_CODIGO_$$}});";
        (*codigo)["cuando_se_presione|boton_central"] = "Button.ENTER.addButtonListener(new ButtonListener(){public void buttonPressed(Button b) {$$_REEMPLAZAR_POR_CODIGO_$$}});";
        (*codigo)["cuando_se_presione|boton_escape"] = "Button.ESCAPE.addButtonListener(new ButtonListener(){public void buttonPressed(Button b) {$$_REEMPLAZAR_POR_CODIGO_$$}});";

        (*codigo)["tono|entero,entero"] = "public static void tono(int a,int b){Sound.playTone(a,b);}";
        (*codigo)["tono|entero,entero,entero"] = "public static void tono(int a,int b,int t){Sound.playTone(a,b);Delay.msDelay(t);}";
        (*codigo)["salir"] = "public static void salir(){System.exit(0);}";
    }
    else
    {
        // PC Based
    }
    //Utilidades
    (*codigo)["numero_aleatorio|entero"] = "public static int numero_aleatorio(int m){return new Random().nextInt(m);}";
    (*codigo)["numero_aleatorio|entero,entero"] = "public static int numero_aleatorio(int m,int x){if(m==x){return m;}int l=m<x?m:x;int b=m>x?m:x;return (new Random().nextInt(b-l))+l;}";
    //(*codigo)["esperar|entero"] = "public static void retrasar_programa(int t){Delay.msDelay(t);}";

    (*codigo)["obtener_cantidad|arreglo"] = "public static int obtener_cantidad(ArrayList<Object> a){return a.size();}";
    return codigo;
}

/*
CODIGO MOTORES
*/
