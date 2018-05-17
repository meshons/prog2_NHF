#include <iostream>
#include <iomanip>

/*double hatvany(double szam,int k){
    double x=szam;
    while(k-->1)
        x*=szam;
    return x;
}*/

 double fv(long double szam){
     double eredmeny;
    if(szam>14)
        eredmeny = szam / 99.65;
    else{
        eredmeny = 0.389 * szam*szam*szam*szam;
        eredmeny -= 0.777 * szam*szam*szam;
        eredmeny += 49.75*szam*szam;
        eredmeny += 14*szam;
        eredmeny -= 14.0;
    }
    return eredmeny;
    //return (szam>33)?szam/104.40:0.407*hatvany(szam,4)-0.814*hatvany(szam,3)+52.12*hatvany(szam,2)+szam-33;
}
char myid[]   = "Stork Gábor,1MI,IMSC3,L3p <storkgaborka98@gmail.com.hu> NO047V\n";
char mytask[] = "Feladat = 2 UTF-8\n";

int main(){
    //std::cout.
    std::cout << myid << mytask;
    std::cout << std::setprecision(4) << std::fixed;
     double szam = 0;
    while(std::cin >> szam){
        std::cout << fv(szam) <<std::endl;
    }
    return 0;
}