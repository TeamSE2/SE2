/**
 * @file    Weiche.cpp
 * @date    20.10.2013
 * @author  Ruben Christian Buhl
 * @brief   Weiche Implementierung
 */

#include "Weiche.h"

Weiche::Weiche()
{
}

Weiche::~Weiche()
{
}

/**
 * Oeffnet oder schliesst die Weiche.
 *
 * @param   ein  Wahr, wenn die Weiche geoeffnet werden soll. Falsch, wenn die Weiche geschlossen werden soll.
 *
 * Bit zur Oeffnung der Weiche auf dem entsprechenden Port wird gesetzt oder geloescht.
 */

void Weiche::auf(bool ein)
{
	HAL::getInstance().set(PORT_A, WEICHE_AUF, ein);
}

//bool Weiche::offen()
//{
//	return HAL::getInstance().isSet(PORT_B, WEICHE_OFFEN);
//}
//
//bool Weiche::lichtschranke()
//{
//	return HAL::getInstance().isSet(PORT_B, LICHTSCHRANKE_WEICHE);
//}
