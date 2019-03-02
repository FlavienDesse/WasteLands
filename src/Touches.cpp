#include "Touches.h"

Touches::Touches(short int attack, short int runBR, short int runBL, short int runTL, short int runTR, short int avancerTR, short int avancerTL, short int avancerBL, short int avancerBR, short int avancerR, short int avancerT, short int avancerL, short int avancerB, short int jump, short int runR, short int runT, short int runL, short int runB, short int shift)
	:attack(attack), runBR(runBR), runBL(runBL), runTL(runTL), runTR(runTR), avancerTR(avancerTR), avancerTL(avancerTL), avancerBL(avancerBL), avancerBR(avancerBR), avancerR(avancerR), avancerT(avancerT), avancerL(avancerL), avancerB(avancerB), jump(jump), runR(runR), runT(runT), runL(runL), runB(runB), shift(shift) {}

short int Touches::GetValueTouche(std::string touchesVoulues) {
	if (touchesVoulues == "WalkR") {
		return this->avancerR;
	}
	if (touchesVoulues == "WalkT") {
		return this->avancerT;
	}
	if (touchesVoulues == "WalkL") {
		return this->avancerL;
	}
	if (touchesVoulues == "WalkB") {
		return this->avancerB;
	}
	if (touchesVoulues == "Jump") {
		return this->jump;
	}
	if (touchesVoulues == "RunR") {
		return this->runR;
	}
	if (touchesVoulues == "RunT") {
		return this->runT;
	}
	if (touchesVoulues == "RunL") {
		return this->runL;
	}
	if (touchesVoulues == "RunB") {
		return this->runB;
	}
	if (touchesVoulues == "Shift") {
		return this->shift;
	}
	if (touchesVoulues == "WalkTR") {
		return this->avancerTR;
	}
	if (touchesVoulues == "WalkTL") {
		return this->avancerTL;
	}
	if (touchesVoulues == "WalkBL") {
		return this->avancerBL;
	}
	if (touchesVoulues == "WalkBR") {
		return this->avancerBR;
	}
	if (touchesVoulues == "RunTR") {
		return this->runTR;
	}
	if (touchesVoulues == "RunTL") {
		return this->runTL;
	}
	if (touchesVoulues == "RunBL") {
		return this->runBL;
	}
	if (touchesVoulues == "RunBR") {
		return this->runBR;
	}
	if (touchesVoulues == "Attack") {
		return this->attack;
	}
	return 0;
}