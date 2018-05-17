#include <stdio.h>
    char myid[]   = "Stork Gábor,1MI,IMSC3,L3p <storkgaborka98@gmail.com.hu> NO047V\n";
    char mytask[] = "Feladat = 4 ISO 8859-2\n";
int main(){
    setbuf(stdout, NULL);        // Kikapcsolja a bufferelest
    printf(myid); 
    printf(mytask);

    printf("a-0x1W6vAdqqriqA\nb-0x1W6vAdqqriqA\nc-0x1W6vAdqqriqA\nd-0x1W6vAdqqriqA\n");
    int i = 0;
    for(i=0;i<213;i++)
        printf("valami %d\n",i);
    return 0;
}