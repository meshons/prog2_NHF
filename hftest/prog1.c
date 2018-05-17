#include <stdio.h>
 
char myid[]   = "Stork Gábor,1MI,IMSC3,L3p <storkgaborka98@gmail.com.hu> NO047V\n";
char mytask[] = "Feladat = 1 UTF-8\n";
 
int main() 
{
    setbuf(stdout, NULL);        // Kikapcsolja a bufferelest
    printf(myid); 
    printf(mytask);
    return 0; 
}