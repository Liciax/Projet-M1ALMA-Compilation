#include "analyseur.hpp"

using namespace std;

bool analyse(Scanner * s, std::map<int, Node*>& G0, Node* p, type_tableSymbole & tabSymb, type_pile & pile) {
	bool analyseur = false;

	switch(p->classe) {
		case CONC: {
			Conc* pconc = (Conc*)p;
			//cout<< " conc "  <<  endl;
			if(analyse(s, G0, pconc->left, tabSymb, pile)) {
				//cout<< " conc gauche ok donc go droite" << endl;
				analyseur = analyse(s, G0, pconc->right, tabSymb, pile);
				//cout<< " conc droite a été fait " << endl;

			} else {
				analyseur = false;
			}

			//cout<< ", analyseur conc: " << analyseur <<  endl;
		}
			break;
		case UNION: {
			//cout<< " union" << endl;
			Union* punion = (Union*)p;
			if(analyse(s, G0, punion->left, tabSymb, pile)) {
				//cout<< " union gauche ok pas de droite" << endl;
				analyseur = true;
			} else {
				//cout<< " union gauche pas ok go droite" << endl;
				analyseur = analyse(s, G0, punion->right, tabSymb, pile);
			}

			//cout<< ", analyseur union : " << analyseur <<  endl;
		}
			break;
		case STAR: {
			//cout<< " star" << endl;
			Star* pstar = (Star*)p;
			analyseur = true;
			while (analyse(s, G0, pstar->stare, tabSymb, pile)) {
				//cout<< "1 star effectué" << endl;
			}
		}
			break;
		case UN: {
			//cout<< " un" << endl;
			Un* pun = (Un*)p;
			analyseur = true;
			analyse(s, G0, pun->une, tabSymb, pile);
			//cout<< ", analyseur un : " << analyseur <<  endl;
		}
			break;
		case ATOM: {
			Atom* pa = (Atom*)p;
			//cout<< " ATom" << endl;

			switch(pa->type) {
				case TERMINAL: {
					cout<< "-------------------" << endl;
					if(pa->code == s->instance->code) {

						//cout<< "je suis term, symb = " << s->instance->chaine << ", code mère:" << pa->code  << ", code gpl :" << s->instance->code << endl;
						analyseur = true;
						if(pa->action !=0) {
							g0_action(pa, s->instance->action, G0, tabSymb, pile, s->instance->chaine);
						}
						lireMot(s, tabSymb);
					} else {
						//cout<< "je suis term, symb = " << s->instance->chaine << ", code mère:" << pa->code  << ", code gpl :" << s->instance->code << " differents" << endl;
						
						analyseur = false;
					}

					//cout<< ", analyseur atom term: " << analyseur <<  endl;
				}
					break;
				case NONTERMINAL: {
					cout<< " ----------------" << endl;
					//on choppe la case de G0 contenant l'action a effectuer
					//cout<< "je suis passé par non term" << endl;
					if(analyse(s, G0, G0[pa->code], tabSymb, pile)) {
						if(pa->action !=0) {
							g0_action(pa, s->instance->action, G0, tabSymb, pile, s->instance->chaine);
						}
						analyseur = true;
					} else {
						analyseur = false;
					}

					//cout<< ", analyseur atom non term: " << analyseur <<  endl;
				}
					break;
			}
		}
			break;
	}
	return analyseur;
}


bool analyse_GLP(Scanner * s, std::map<int, Node*>& G0, Node* p, type_tableSymbole & tabSymb, type_pile & pile) {
	bool analyseur_GLP = false;

	switch(p->classe) {
		case CONC: {
			Conc* pconc = (Conc*)p;
			//cout<< " conc "  <<  endl;
			if(analyse_GLP(s, G0, pconc->right, tabSymb, pile)) {
				//cout<< " conc gauche ok donc go droite" << endl;
				analyseur_GLP = analyse_GLP(s, G0, pconc->left, tabSymb, pile);
				//cout<< " conc droite a été fait " << endl;

			} else {
				analyseur_GLP = false;
			}

			//cout<< ", analyseur_GLP = conc: " << analyseur_GLP = <<  endl;
		}
			break;
		case UNION: {
			//cout<< " union" << endl;
			Union* punion = (Union*)p;
			if(analyse_GLP(s, G0, punion->right, tabSymb, pile)) {
				//cout<< " union gauche ok pas de droite" << endl;
				analyseur_GLP = true;
			} else {
				//cout<< " union gauche pas ok go droite" << endl;
				analyseur_GLP = analyse_GLP(s, G0, punion->left, tabSymb, pile);
			}

			//cout<< ", analyseur_GLP = union : " << analyseur_GLP = <<  endl;
		}
			break;
		case STAR: {
			//cout<< " star" << endl;
			Star* pstar = (Star*)p;
			analyseur_GLP = true;
			while (analyse_GLP(s, G0, pstar->stare, tabSymb, pile)) {
				//cout<< "1 star effectué" << endl;
			}
		}
			break;
		case UN: {
			//cout<< " un" << endl;
			Un* pun = (Un*)p;
			analyseur_GLP = true;
			analyse_GLP(s, G0, pun->une, tabSymb, pile);
			//cout<< ", analyseur_GLP = un : " << analyseur_GLP = <<  endl;
		}
			break;
		case ATOM: {
			Atom* pa = (Atom*)p;
			//cout<< " ATom" << endl;

			switch(pa->type) {
				case TERMINAL: {
					cout<< "-------------------" << endl;
					if(pa->code == s->instance->code) {

						//cout<< "je suis term, symb = " << s->instance->chaine << ", code mère:" << pa->code  << ", code gpl :" << s->instance->code << endl;
						analyseur_GLP = true;
						if(pa->action !=0) {
							//gpl_action(pa, s->instance->action, G0, tabSymb, pile, s->instance->chaine);
						}

						lireMotGLP(s, tabSymb);

					} else {
						//cout<< "je suis term, symb = " << s->instance->chaine << ", code mère:" << pa->code  << ", code gpl :" << s->instance->code << " differents" << endl;
						
						analyseur_GLP = false;
					}

					//cout<< ", analyseur_GLP = atom term: " << analyseur_GLP = <<  endl;
				}
					break;
				case NONTERMINAL: {
					cout<< " ----------------" << endl;
					//on choppe la case de G0 contenant l'action a effectuer
					//cout<< "je suis passé par non term" << endl;
					if(analyse_GLP(s, G0, G0[pa->code], tabSymb, pile)) {
						if(pa->action !=0) {
							//gpl_action(pa, s->instance->action, G0, tabSymb, pile, s->instance->chaine);
						}
						analyseur_GLP = true;
					} else {
						analyseur_GLP = false;
					}

					//cout<< ", analyseur_GLP = atom non term: " << analyseur_GLP = <<  endl;
				}
					break;
			}
		}
			break;
	}
	return analyseur_GLP;
}