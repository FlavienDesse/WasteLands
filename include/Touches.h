#ifndef TOUCHES_H
#define TOUCHES_H
#include <cstdlib>
#include <string>
class Touches {
public:
	Touches(short int attack,short int runBR, short int runBL, short int runTL, short int runTR, short int avancerrTR,short int avancerrTL,short int avancerrBL,short int avancerrBR,short int avancerR, short int avancerT, short int avancerL, short int avancerB, short int jump, short int runR, short int runT, short int runL, short int runB,short int shift, short int changeaAura , short int interaction);
	short int GetValueTouche(std::string touchesVoulues);
private:
	short int avancerR;
	short int avancerT;
	short int avancerL;
	short int avancerB;
	short int avancerTR;
	short int avancerTL;
	short int avancerBR;
	short int avancerBL;
	short int jump;
	short int runR;
	short int runT;
	short int runL;
	short int runTL;
	short int runTR;
	short int runBL;
	short int runBR;
	short int runB;
	short int shift;
	short int attack;
	short int changeaAura;
	short int interaction;
};

#endif
