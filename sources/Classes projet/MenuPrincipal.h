#pragma once
#include "Menu.h"
#include "Sprite2D.h"
#include "GestionnairePhases.h"
#include "PhaseMenuNouvellePartie.h"
#include "PhaseMenuOptions.h"
#include "Bouton.h"


class MenuPrincipal : public Menu {

private:

	Bouton* demarrer;
	Bouton* options;
	gfx::Sprite2D* logo;

public:

	MenuPrincipal(void) {

		this->spriteFond = new gfx::Sprite2D(Vecteur2f(0, 0), gfx::GestionnaireRessources::obtInstance().obtTexture("fondMenu.png"));
		logo = new gfx::Sprite2D(Vecteur2f(450, 650), gfx::GestionnaireRessources::obtInstance().obtTexture("logo.png"));

		demarrer = new Bouton(std::bind(&MenuPrincipal::enClicDemarrer, this, std::placeholders::_1),
			std::bind(&MenuPrincipal::survol, this, std::placeholders::_1),
			std::bind(&MenuPrincipal::defaut, this, std::placeholders::_1),
			Vecteur2f(50, 330),
			new std::string("New Game"), 50);

		options = new Bouton(std::bind(&MenuPrincipal::enClicOptions, this, std::placeholders::_1),
			std::bind(&MenuPrincipal::survol, this, std::placeholders::_1),
			std::bind(&MenuPrincipal::defaut, this, std::placeholders::_1),
			Vecteur2f(50, 180),
			new std::string("Options"), 50);

		retour = new Bouton(std::bind(&MenuPrincipal::enClicQuitter, this, std::placeholders::_1),
			std::bind(&MenuPrincipal::survol, this, std::placeholders::_1),
			std::bind(&MenuPrincipal::defaut, this, std::placeholders::_1),
			Vecteur2f(50, 30),
			new std::string("Quit"), 50);
		defPause(true);
	}

	~MenuPrincipal(void) {
		gfx::Gestionnaire2D::obtInstance().retObjets({ logo, spriteFond });
		delete logo, spriteFond;
	}

	void survol(Bouton* envoi){
		envoi->defCouleur({ 215, 110, 75, 255 });
	}

	void defaut(Bouton* envoi){
		envoi->defCouleur({ 0, 0, 0, 255 });
	}

	void enClicDemarrer(Bouton* envoi){
		clic(MENUNOUVELLEPARTIE);
	}

	void enClicOptions(Bouton* envoi){
		clic(MENUOPTIONS);
	}

	void enClicQuitter(Bouton* envoi){
		GestionnairePhases::obtInstance().enleverPhaseActive();
	}

	void remplir(void) {

		gfx::Gestionnaire2D::obtInstance().ajouterObjets({ spriteFond, logo });
		demarrer->remplir();
		options->remplir();
		retour->remplir();

	}

	void defPause(bool pause) {

		if (pause) {
			this->pause = pause;
			demarrer->defEtat(PAUSE);
			options->defEtat(PAUSE);
			retour->defEtat(PAUSE);
		}

		else {
			this->pause = pause;
			demarrer->defEtat(DEFAUT);
			options->defEtat(DEFAUT);
			retour->defEtat(DEFAUT);
		}

	}

	void actualiserEchelle(Vecteur2f vecteurEchelle) {
		this->spriteFond->defEchelle(vecteurEchelle);
		this->retour->defEchelle(vecteurEchelle);
		demarrer->defEchelle(vecteurEchelle);
		options->defEchelle(vecteurEchelle);
		logo->defEchelle(vecteurEchelle);
	}

};