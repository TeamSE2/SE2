/**
 * Diese Datei enthaelt den Header der Struktur Werkstueck und definiert die Enumeration WerkstueckTyp, welche in der Struktur Werkstueck enthalten ist.
 *
 * @file    Werkstueck.h
 * @date    21.10.2013
 * @author  Ruben Christian Buhl
 * @brief   Werkstueck Header
 */

#ifndef WERKSTUECK_H
#define WERKSTUECK_H

/**
 * Beschreibt den Typ von einem Werkstueck.
 *
 * Enthaelt fuer jeden moeglichen Typ einen Wert.
 * Ein Werkstueck kann eine Bohrung an der Ober- oder Unterseite haben, ueber einen Metalleinsatz verfuegen und zu flach sein.
 */

enum WerkstueckTyp
{
	BOHRUNG_OBEN,
	BOHRUNG_OBEN_METALL,
	BOHRUNG_UNTEN,
	BOHRUNG_UNTEN_METALL,
	ZU_FLACH
};

/**
 * Datenstruktur zu einem Werkstueck.
 *
 * Hier werden alle Daten zu einem Werkstueck abgelegt.
 * Jedes Werkstueck erhaelt eine ID, ist von einem bestimmten Typ und hat zwei Hoehenmesswerte.
 */

#define MAX_ID 65500

typedef struct Werkstueck
{
	long id;
	WerkstueckTyp typ;
	float hoehen[2];
} WerkstueckDaten;

#endif /* WERKSTUECK_H */
