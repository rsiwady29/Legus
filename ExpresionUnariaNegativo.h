#ifndef EXPRESIONUNARIANEGATIVO_H
#define EXPRESIONUNARIANEGATIVO_H

#include "Expresion.h"
#include "ExpresionUnaria.h"

class ExpresionUnariaNegativo : public ExpresionUnaria
{
public:
    ExpresionUnariaNegativo(Expresion *expresion);
};

#endif // EXPRESIONUNARIANEGATIVO_H