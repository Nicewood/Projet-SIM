#pragma once
#include <SDL2\SDL.h>
#include <math.h>

#include "GestionnaireEvenements.h"
#include "Camera.h"

namespace gfx{
	class CameraGodMode : public Camera{
	private:
		float vitesse;
		float sensibilite;

		float hAngle;
		float vAngle;

		void calculerVecteurs(){
			if (vAngle > 89)
				vAngle = 89;
			if (vAngle < -89)
				vAngle = -89;

			devant.x = cos(vAngle * M_PI / 180) * cos(hAngle * M_PI / 180);
			devant.y = cos(vAngle * M_PI / 180) * sin(hAngle * M_PI / 180);
			devant.z = sin(vAngle * M_PI / 180);

			devant.normaliser();

			haut = Vecteur3f(0, 0, 1);

			cote = devant.produitVectoriel(haut);
			cote.normaliser();

			haut = cote.produitVectoriel(devant);
			haut.normaliser();

			coustruireMatrice();
		}
	public:

		CameraGodMode(Vecteur3f& position) : Camera(position, Vecteur3f(), Vecteur3f(0, 0, 1)){
			this->vitesse = 0.01;
			this->sensibilite = 0.2;
			
			this->hAngle = 0;
			this->vAngle = 0;

			calculerVecteurs();

			GestionnaireEvenements::obtInstance().ajouterUnRappel(SDL_MOUSEMOTION, std::bind(&CameraGodMode::surMouvementSouris, this, std::placeholders::_1));

			SDL_SetRelativeMouseMode(SDL_TRUE);
			SDL_ShowCursor(SDL_DISABLE);
		}

		~CameraGodMode(){
			SDL_SetRelativeMouseMode(SDL_FALSE);
			SDL_ShowCursor(SDL_ENABLE);
		}

		void surMouvementSouris(SDL_Event &event){
			hAngle -= event.motion.xrel * sensibilite;
			vAngle -= event.motion.yrel * sensibilite;
			calculerVecteurs();
		}

		void deplacement(float frametime){
			if (Clavier::toucheAppuyee(SDLK_w))
				position += devant * vitesse * frametime;
			if (Clavier::toucheAppuyee(SDLK_s))
				position -= devant * vitesse * frametime;
			if (Clavier::toucheAppuyee(SDLK_a))
				position -= cote * vitesse * frametime;
			if (Clavier::toucheAppuyee(SDLK_d))
				position += cote * vitesse * frametime;
			if (Clavier::toucheAppuyee(SDLK_SPACE))
				position.z += vitesse;
			if (Clavier::toucheAppuyee(SDLK_LSHIFT))
				position.z -= vitesse;
		}

		
		
	};
}