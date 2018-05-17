#ifndef F8_hpp
#define F8_hpp true

#include <iostream>
#include <iomanip>
#include <stdexcept>

template<int meret>
class F8{
    public:
    int s;
    int r;
    double *d;
    bool *b;
    F8(){   
        s = meret;
        d = new double[meret];
        b = new bool[meret];
        for(int i=0;i<meret;i++)b[i]=false;
        r = 0;
    }
    ~F8(){
        delete[] d;
        delete[] b;
    }
    const char* c_str(){
        return "Stork Gabor,1MI,IMSC3,L3p <storkgaborka98@gmail.com> NO047V\n";
    }
    void rendez(){
        for(int i=0;i<r;i++)
            for(int j=0;j+1<r-i;j++)
                if(d[j]>d[j+1]){
                    double tmp = d[j];
                    d[j] = d[j+1];
                    d[j+1] = tmp;
                }
        
    }
    double& operator[](int x){
        if(x>=s || x<0)throw std::out_of_range("out_of_range");
        if(!b[x]){
            b[x]=true;
            r++;
        }
        return d[x];
    }
    template <int U> 
    friend std::ostream& operator<<(std::ostream& os, F8<U>& f);  

};

template <int meret>
std::ostream& operator<<(std::ostream& os, F8<meret>& f)  
{  
    os << std::setprecision(4) << std::fixed << f.d[22] << std::endl << f.d[2] << std::endl << f.d[65] << std::endl << f.d[64] << std::endl << f.d[398];
    return os;
}  
  
#endif
