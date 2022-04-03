#ifndef TIC_H
#define TIC_H


class Tic{
    public:
        Tic(unsigned long int tic) : tic_(tic){}
        unsigned long int diff(unsigned long int tic);
        unsigned long int tic() const;
        float seconds() const;
        static long int hz();
    private:
        unsigned long int tic_{0};
};

#endif