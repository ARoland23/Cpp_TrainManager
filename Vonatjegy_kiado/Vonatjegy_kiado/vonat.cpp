#include "vonat.h"
#include "dintomb.hpp"
#define Max_Kocsiszam 50

Vonat::Vonat() : jarat(1), kocsiSzam(1) {}
Vonat::Vonat(int jt, int ksz) :jarat(jt), kocsiSzam(ksz) {}

void Vonat::setJarat(int jt)
{
	if (jt < 0)
		jarat = 0;
	else
		jarat = jt; 
}
void Vonat::setKocsiSzam(int ksz) 
{
	if (ksz < 0)
		ksz = 0;
	else
		kocsiSzam = ksz; 
}
int Vonat::getJarat()const { return jarat; }
int Vonat::getKocsi()const { return kocsiSzam; }


Vonat& Vonat::operator=(Vonat& v)
{
	this->setJarat(v.jarat);
	this->setKocsiSzam(v.kocsiSzam);
	return *this;
}