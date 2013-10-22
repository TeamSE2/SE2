/*
 * Werkstueck.h
 *
 *  Created on: 21.10.2013
 *      Author: Ruben Christian Buhl
 */

#ifndef WERKSTUECK_H
#define WERKSTUECK_H

enum WerkstueckTyp
{
	BOHRUNG_OBEN,
	BOHRUNG_OBEN_METALL,
	BOHRUNG_UNTEN,
	BOHRUNG_UNTEN_METALL,
	ZU_FLACH
};

struct Werkstueck
{
	long id;
	WerkstueckTyp typ;
	float hoehen[2];
};

#endif /* WERKSTUECK_H */
