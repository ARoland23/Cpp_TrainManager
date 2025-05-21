#ifndef JEGY_GUARD
#define JEGY_GUARD
#include "vonat.h"
#include "string5.h"
#include "memtrace.h"


template<typename T> class DinTomb;

/**
 * Jegy osztaly
 *	Tartalmazza a vonatot amire a jegy szol
 *	a helyet amire a jegy szol
 *	az indulasi illetve erkezesi idot
 *	az indulasi es erkezesi allomast
 *	illetve a jegy arat.
 */
class Jegy {
	Vonat vonat;	///< vonat amire szol a jegy
	int hely;		///< ules amire foglalt a jegy
	String idoI;	///< indulasi ido
	String idoE;	///< erkezesi ido
	String allomasI;///< allomas ahonnan indul a vonat
	String allomasE;///< allomas ahova erkezik a vonat
	int ar;			///< a jegy ara Forintban
public:
	///default ctor
	Jegy();
	/// Konstruktor parameterekbol
	/// Ez a deafault is!
	/// @param v - vonat
	/// @param h - ules szama a vonaton(int)
	/// @param ido1 - indulasi ido (string)
	/// @param ido2 - erkezesi ido (string)
	/// @param indulasi allomas (string)
	/// @param erkezesi allomas (string)
	/// @param ar - a jegy ara (int)
	Jegy(Vonat v, int h, String ido1, String ido2, String all1, String all2, int a);

	void setVonat(Vonat v);
	void setIdoI(String ido);
	void setIdoE(String ido);
	void setAllomasI(String nev);
	void setAllomasE(String nev);
	void setHely(int h);
	void setAr(int a);

	Vonat getVonat()const;
	String getIdoI()const;
	String getIdoE()const;
	String getAllomasI() const;
	String getAllomasE() const;
	int getHely() const;
	int getAr() const;

/// ertekado operator (=)
/// @param j - masik jegy referenciaja
/// @return *this
	Jegy& operator=(Jegy& j);


};

/// osszeado operator (+)
/// egy szamhoz adja a jegy arat
/// @param bal_oldal - szam amihez adunk
/// @param jobb_oldal - jegy aminek vesszuk az arat
/// @return (bal_oldal+jobb_oldal)
int operator+(int sum,Jegy& j);



#endif // !JEGY_GUARD