#ifndef SCANNER_HPP
#define SCANNER_HPP

#include <iostream>
#include <fstream>
#include <string>
#include "typage.hpp"
#include "tabSymbole.hpp"

typedef struct {
	int code;
	int action;
	AtomType type;
	std::string chaine;
} Instance;

typedef struct {
	std::fstream * fs;
	Instance * instance;
} Scanner;

///////////////////////////////////////////////////
enum Symbole_GPL {ENT, IDENT, SYMBOLE_S, SYMBOLE_C};

typedef struct {
	int code;
	int action;
	AtomType type;
	std::string chaine;
} Instance_GPL;//?????

typedef struct {
	std::fstream * fs;
	Instance_GPL * instance;
} Scanner_GPL;
///////////////////////////////////////////////////

//scan permet d'avancer dans phrase (S -> 'a' + 'b') et avec analyse
// -> a chaque fin d'analyse (ATOM) on check si se qu'on a trouve == 
//ce sur quoi le scan est. si ok on avance scan et on continue 
// ex ici conc -> star -> conc -> conc -> N ->idnter : scan = S donc ok, on continue;
// conc droit = ->, scan est sur fleche: ok...

void initScan(Scanner * s, std::string file);
void closeScan(Scanner * s);
//int recherche(string s);
void lireMot(Scanner * s, type_tableSymbole & tabSymb);
// void lireBlanc(Scanner * s);
void afficheInstance(Instance * inst);

void lireMotGLP(Scanner * s, type_tableSymbole & tabSymb);


#endif //SCANNER_HPP