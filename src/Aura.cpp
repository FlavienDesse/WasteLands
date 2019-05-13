#include "Aura.h"


void Aura::update() {
	
	if (this->animationClock.getSeconds() > SPEEDANIMATIONAURA / this->allTextureAura[this->actualAura].size()) {
		posAura++;
		if (posAura == this->allTextureAura[this->actualAura].size()) {
			posAura = 0;
		}
		
	
		this->animationClock.stop();
		this->animationClock.start();
	}
}
void Aura::ChangeAura() {
	if (this->actualAura == "Rouge") {
		posAura = 0;
		this->actualAura = "Vert";
	}
	else if (this->actualAura == "Vert") {
		posAura = 0;
		this->actualAura = "Bleu";
	}
	else if (this->actualAura == "Bleu") {
		posAura = 0;
		this->actualAura = "Jaune";
	}
	else if (this->actualAura == "Jaune") {
		posAura = 0;
		this->actualAura = "Noir";
	}
	else if (this->actualAura == "Noir") {
		posAura = 0;
		this->actualAura = "Rouge";
	}
}