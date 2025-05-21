#include "jegy.h"
#include "dintomb.hpp"

Jegy::Jegy() :vonat(Vonat(1, 1)), hely(1), idoI("Default"), idoE("Default"), allomasI("Default"), allomasE("Default"), ar(1) { }
Jegy::Jegy(Vonat v, int h, String ido1, String ido2, String all1, String all2, int a) :vonat(v), hely(h), idoI(ido1), idoE(ido2), allomasI(all1), allomasE(all2), ar(a) {}


void Jegy::setVonat(Vonat v) { this->vonat = v; }
void Jegy::setIdoI(String ido) { idoI = ido; }
void Jegy::setIdoE(String ido) { idoE = ido; }
void Jegy::setAllomasI(const String nev) { allomasI = nev; }
void Jegy::setAllomasE(const String nev) { allomasE = nev; }
void Jegy::setHely(int h)
{
	if (h < 0)
	{
		hely = 1;
	}
	else if (h > 50)
	{
		hely = 50;
	}
	else
		hely = h;
}
void Jegy::setAr(int a) { ar = a; }

Vonat Jegy::getVonat()const { return  vonat; }
String Jegy::getIdoI()const { return idoI; }
String Jegy::getIdoE()const { return idoE; }
String Jegy::getAllomasI() const { return allomasI; }
String Jegy::getAllomasE() const { return allomasE; }
int Jegy::getHely()const { return hely; }
int Jegy::getAr() const { return ar; }

Jegy& Jegy::operator=(Jegy& j)
{
	this->setVonat(j.getVonat());
	this->setAllomasI(j.getAllomasI());
	this->setAllomasE(j.getAllomasE());
	this->setIdoI(j.getIdoI());
	this->setIdoE(j.getIdoE());
	this->setHely(j.getHely());
	this->setAr(j.getAr());

	return *this;
}
int operator+(int sum, Jegy& j)
{
	return ( sum + j.getAr() );
}
