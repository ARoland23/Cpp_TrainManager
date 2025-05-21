#ifndef VONAT_GUARD
#define VONAT_GUARD
#include "memtrace.h"

template<typename T> class DinTomb;
/**
 * Vonat osztály.
 * Egy vonatot ad meg, ami egy jaratbol (szam) illetve a huzott kocsik (szam) szamabol all.
 * A jarat = vonat. Egy vonat egy jarathoz tartozik.
 */
class Vonat {
	int jarat; ///< jarat azonositoja
	int kocsiSzam; ///< a jarat (vonat) altal huzott kocsik szama
public:
///default ctor
	Vonat();

/// Konstruktor parameterekbol
/// Ez a deafault is!
/// @param jt - jarat szama
/// @param ksz - a vonat altal huzott kocsik szama
	Vonat(int jt, int ksz);

	void setJarat(int jt);
	void setKocsiSzam(int ksz);
	int getJarat()const;
	int getKocsi()const;

/// ertekado operator (=)
/// @param v - masik vonat referenciaja
/// @return *this
	Vonat& operator=(Vonat& v);

};


#endif // !VONAT_GUARD