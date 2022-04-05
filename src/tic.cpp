#include "tic.h"
#include <unistd.h>

long int Tic::hz(){ return sysconf(_SC_CLK_TCK);
}
unsigned long int Tic::diff(unsigned long int tic){
        unsigned long int prev_tic = tic_;
        tic_ = tic;
    
        return (tic-prev_tic);
    }

    
unsigned long int Tic::tic() const{
    return tic_; 
    }
float Tic::seconds() const{
    return 1.*tic_/hz();
    }

