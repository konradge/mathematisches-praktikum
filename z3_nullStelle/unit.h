/*******************************************************************
 *  Name       : unit.h                                             *
 *  Verwendung : Schnittstelle zu Praktikumsumgebung (MAPRA),       *
 *               Nullstellen einer Funktion (einschlusserhaltend):  *
 *               Regula Falsi, Illinois, Pegasus, Anderson-Bjoerk   *
 *  Autor      : diverse, IGPM RWTH Aachen                          *
 *  Datum      : Jul '89 bis                                        *
 *  Aenderung  : Apr '00                                            *
 *******************************************************************/

#ifndef _UNIT_H
#define _UNIT_H

// Externe Variablen aus der Praktikumsumgebung

extern const int num_examples;
extern double eps;

// Damit man die Verfahren nicht nur durch die Werte 0 bis 3 angeben kann
// sondern mit Namen (dies vermeidet schwer zu findende Fehler!), wird hier
// mittels "enum" ein entsprechender Aufzaehlungstyp konstruiert. Bei
// Zuweisung zu einem Integer wird automatisch eine Typumwandlung vorgenommen.

enum { RegFalsi, Illinois, Pegasus, AndBjrk };

// Die Funktion "f" stellt die Funktion zur Verfuegung, deren Nullstelle
// bestimmt werden soll.

double f(double x);

// Die folgenden drei Funktionen sorgen fuer die Beurteilung und
// eventuell die grafische Ausgabe der Ergebnisse.
// "getExample" ist zu Beginn eines jeden Beispiels aufzurufen,
// "checkStep" nach jeder Iteration (einschliesslich der nullten) und
// "checkSolution" am Schluss mit dem Endergebnis.
// Fuer eine genauere Beschreibung siehe Aufgabenblatt.

void getExample(int ex, double &x0, double &x1, bool draw = true, int pause = 300);

void checkStep(int meth, double xi, double fi, double xiPlus1, double fiPlus1);

void checkSolution(int meth, double x);

#endif
