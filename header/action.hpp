#ifndef ACTION_HPP
#define ACTION_HPP

#include <iostream>
#include <vector>
#include <stack>
#include "generateur.hpp"
#include "tabSymbole.hpp"
#include "typage.hpp"

typedef std::stack<Node*> type_pile;
typedef std::vector<int> type_dico;

int recherche(type_dico & dico, int code);
void empiler(type_pile & pile, Node * p);
Node * depiler(type_pile & pile);
void g0_action(Atom *pa,AtomType type, int scanAction, std::map<int, Node*>& G0, type_tableSymbole & tabSymb, type_pile & pile, std::string symbole);
void gpl_action( std::map<std::string, int>& IATAB, std::stack<int>& pileOP, std::vector<int>& p_code, std::string chaine, int action);
#endif //ACTION_HPP