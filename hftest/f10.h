#ifndef F10_H
#define F10_H
/**
 * class F10 definicioja
 * Stork Gabor, NO047V reszere
 * Datum: 2018-02-22 09:25:39
 * NE modositsa ezt az allmomanyt!
 */

class F10 {
   char *line;	// tarolt sztring
   int  len;	// hossz, de nem fontos hasznalni
public:  
   // szokasos tagfuggvenyek
   // nincsenek kommentezve, mert tudni kell, hogy mi mit jelent
   F10();
   F10(const F10&);
   F10& operator=(const F10&);
   ~F10();

   // specialis tagfuggvenyek:
   // visszaadja a hftest elso azonositosoranak cimet
   const char *ident() const;
   // megallapitjja, hogy a parameterkent kapot sztringben megtalalhato-e valamelyik
   // karaktersorozat az alabbiakbol:
   //    alakra 
   //    definialnunk 
   //    sebesseget 
   bool match(const char *line); 

   // visszaadja annak a szringnek a cimet melyben utoljara a match egyezest talalt 
   const char *getLine() const;
};
#endif
   
