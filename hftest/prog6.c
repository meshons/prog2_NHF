#include <stdio.h>
#include <string.h>
#include <stdbool.h>
 
char myid[]   = "Stork Gábor,1MI,IMSC3,L3p <storkgaborka98@gmail.com> NO047V\n";
char mytask[] = "Feladat = 6 UTF-8\n";

int okt(int dec){
    int oktal = dec%8;
    dec = dec/8;
    oktal += dec%8 * 10;
    dec = dec/8;
    oktal += dec%8 * 100;
    return oktal;
}

int main(){
    setbuf(stdout, NULL);        // Kikapcsolja a bufferelest
    printf(myid); 
    printf(mytask);
    int sorok=0,illeszkedo = 0;
    char sor[10000];
    sor[10000]=0;
    for(;fgets(sor,10000,stdin);){
        sorok++;
        int x = 0;
        int hossz = strlen(sor);
        if(sor[x++]=='#' && x<=hossz)continue;
        if(sor[x]=='-' && x<=hossz)x++;
        while(sor[x]=='0'&&sor[x+1]=='x'&& x+1<=hossz)x+=2;
        while(sor[x]>='0'&&sor[x]<='9'&& x<=hossz)x++;
        if(sor[x++]!='W'&& x<=hossz)continue;
        if(sor[x++]!='6'&& x<=hossz)continue;
        if(!sor[x++]&& x<=hossz)continue;
        bool AZ=true;
        while(sor[x]&& x<=hossz &&AZ){
            if(sor[x]>='A'&&sor[x]<='Z')
                AZ = false;
            x++;
        }
        AZ=true;
        while(sor[x]&& x<=hossz &&AZ){
            if(sor[x]<'A'||sor[x]>'Z')
                AZ=false;
            x++;
        }
        while((sor[x]!='q' || sor[x+1]!='q' || sor[x+2]!='r' || sor[x+3] != 'i' || sor[x+4]!='q') && x+4<=hossz)x++;
        if((sor[x]!='q' || sor[x+1]!='q' || sor[x+2]!='r' || sor[x+3] != 'i' || sor[x+4]!='q') && x+4<=hossz)continue;
        x+=5;
        if(sor[x]!='A' && sor[x]!='b')continue;
        if(x>hossz)continue;
        illeszkedo++;
    }
    printf("%d/%d\n",okt(sorok),okt(illeszkedo));
    return 0;
}