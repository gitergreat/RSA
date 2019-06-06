#ifndef _INITIAL_H
#define _INITIAL_H

#include "file.h"

void create_e(mpz_t e0,mpz_t fraii)
{
    mpz_t rop;
    mpz_init(rop);
    mpz_t one;
    mpz_init_set_ui(one,1);
    gmp_randstate_t randd;
	gmp_randinit_default(randd); 
	gmp_randseed_ui(randd, time(NULL));
    mpz_urandomb(e0, randd , 20);

    while(1){
        mpz_gcd(rop,e0,fraii);
        if(!mpz_cmp(rop,one)){
            mpz_clear(rop);
            mpz_clear(one);
            break;
        }
        else{
            mpz_add_ui(e0,e0,1);
        }
    }

}

void initial()
{
    mpz_t keyp,keyq;
    mpz_init(keyp);
    mpz_init(keyq);

	gmp_randstate_t rand;
	gmp_randinit_default(rand); 
	gmp_randseed_ui(rand, time(NULL));

    mpz_urandomb(keyp, rand, 256);
	mpz_urandomb(keyq, rand, 256);
    mpz_t temp;
    mpz_init_set_str(temp,"10000000000",10);
    mpz_add(keyp,keyp,temp);
    mpz_add(keyq,keyp,temp);

    mpz_nextprime(keyp,keyp);
    mpz_nextprime(keyq,keyq);

    mpz_t n;
    mpz_init(n);
    mpz_mul(n,keyp,keyq);

    mpz_t frai;
    mpz_init(frai);
    mpz_sub_ui(keyp,keyp,1);
    mpz_sub_ui(keyq,keyq,1);
    mpz_mul(frai,keyp,keyq);
    mpz_add_ui(keyp,keyp,1);
    mpz_add_ui(keyq,keyq,1);

    mpz_t e;
    mpz_init(e);
    create_e(e,frai);

    mpz_t d;
    mpz_init(d);
    mpz_invert(d,e,frai);

    if (!writeFile("p.txt", "w", keyp)){
        return;
    }
    if (!writeFile("q.txt", "w", keyq)){
        return;
    }
    if (!writeFile(n_location, "w", n)){
        return;
    }
    if (!writeFile(d_location, "w", d)){
        return;
    }
    if (!writeFile(e_location, "w", e)){
        return;
    }

    mpz_clear(keyp);
    mpz_clear(keyq);
    mpz_clear(n);
    mpz_clear(d);
    mpz_clear(e);
}

#endif