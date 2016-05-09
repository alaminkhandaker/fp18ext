//
//  parameters.c
//  Fp18_Arith
//
//  Created by Khandaker Md. Al-Amin on 4/29/16.
//  Copyright © 2016 Khandaker Md. Al-Amin. All rights reserved.
//

#include "parameters.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h>

int parameters(int bit){

    mpz_t X,X2;
    mpz_init(X);
    mpz_init(X2);
    
//    mpz_t u,utmp0,utmp1;
//    
//    mpz_init(u);
//    mpz_init(utmp0);
//    mpz_init(utmp1);
//    //    264+247+243+237+226+225+219−213−27
//    mpz_set_ui(u,2);
//    mpz_pow_ui(utmp0,u,64);
//    mpz_pow_ui(utmp1,u,47);
//    mpz_add(utmp0,utmp0,utmp1);
//    mpz_pow_ui(utmp1,u,43);
//    mpz_add(utmp0,utmp0,utmp1);
//    mpz_pow_ui(utmp1,u,37);
//    mpz_add(utmp0,utmp0,utmp1);
//    mpz_pow_ui(utmp1,u,26);
//    mpz_add(utmp0,utmp0,utmp1);
//    mpz_pow_ui(utmp1,u,25);
//    mpz_add(utmp0,utmp0,utmp1);
//    mpz_pow_ui(utmp1,u,19);
//    mpz_add(utmp0,utmp0,utmp1);
//    mpz_pow_ui(utmp1,u,13);
//    mpz_sub(utmp0,utmp0,utmp1);
//    mpz_pow_ui(utmp1,u,13);
//    mpz_sub(utmp0,utmp0,utmp1);
//    mpz_pow_ui(utmp1,u,7);
//    mpz_sub(u,utmp0,utmp1);
//    gmp_printf("U %Zd = bit %d\n",u,(int)mpz_sizeinbase(u,2));
//    mpz_set(X,u);
    
    //==============
    int X_int = bit;
//    X_int=X_int/8; //bit count?
    printf("X_int %d\n",X_int);
    mpz_setbit(X,X_int);
    gmp_printf("X Set bit %Zd = %d\n",X,(int)mpz_sizeinbase(X,2));
    mpz_div_ui(X2,X,4);
    gmp_printf("X2div %Zd = bit %d\n",X2,(int)mpz_sizeinbase(X2,2));
    mpz_add(X,X2,X);
//    mpz_add(X,X2,X);
    mpz_div_ui(X,X,2);
    gmp_printf("X = %Zd,HW %ld Bit size %d bit\n",X,mpz_popcount(X),(int)mpz_sizeinbase(X,2));
    
    
//    while ((int)mpz_sizeinbase(X,2) <= 64)
//    {
//        if ((int)mpz_sizeinbase(X,2) == 64)
//        {
//            printf("Got it\n");
//        }
//        mpz_add(X,X2,X);
//    }
//    if ((int)mpz_sizeinbase(X,2) == 64)
//    {
//        printf("Got it\n");
//        return 0;
//    }
//    else
//    {
//        return 0;
//    }
    
    mpz_t p_tmp,r_tmp;
    mpz_t xpow2,xpow3,xpow4,xpow5,xpow6,xpow7,xpow8;
    mpz_t tmp1,tmp2;
    
    mpz_init(p_tmp);
    mpz_init(r_tmp);
    
    mpz_init(xpow2);
    mpz_init(xpow3);
    mpz_init(xpow4);
    mpz_init(xpow5);
    mpz_init(xpow6);
    mpz_init(xpow7);
    mpz_init(xpow8);
    
    mpz_init(tmp1);
    mpz_init(tmp2);
    
    mpz_tdiv_r_ui(tmp1,X,42); //tmp1 = x/42 | x = 14(mod 42)
    while(mpz_cmp_ui(tmp1,14)!=0){
        mpz_add_ui(X,X,1);
        mpz_tdiv_r_ui(tmp1,X,42);
    }
    
    mpz_t tmp,mod;
    mpz_init(tmp);
    mpz_init(mod);
    unsigned long int j,k,l;
    mpz_set_ui(mod,3);
    
    long long int count192p = 0;
    long long int count192p_cond = 0;
    
    FILE *fp;
    fp=fopen("Primes.csv","a");
    
    if(fp == NULL){
        printf("Couldn't open file\n");
    }
    gmp_fprintf(fp,"X,HW,Prime,Bits\n");
    
    for(;;){
        mpz_mul(xpow2,X,X);
        mpz_mul(xpow3,xpow2,X);
        mpz_mul(xpow4,xpow2,xpow2);
        mpz_mul(xpow5,xpow4,X);
        mpz_mul(xpow6,xpow3,xpow3);
        mpz_mul(xpow7,xpow6,X);
        mpz_mul(xpow8,xpow4,xpow4);
        
        mpz_mul_ui(tmp1,xpow3,37);//37x^3
        mpz_add_ui(tmp2,xpow6,343);//x^6 + 343
        mpz_add(r_tmp,tmp1,tmp2);// x^6 + 37x^3 + 343
        
        
        mpz_mul_ui(tmp1,xpow7,5);// 5x^7
        mpz_add(p_tmp,tmp1,xpow8);// x^8+5x^7
        mpz_mul_ui(tmp1,xpow6,7);// 7x^6
        mpz_add(p_tmp,tmp1,p_tmp);// x^8 + 5x^7 + 7x^6
        mpz_mul_ui(tmp1,xpow5,37);// 37x^5
        mpz_add(p_tmp,tmp1,p_tmp);// x^8 + 5x^7 + 7x^6 + 37x^5
        mpz_mul_ui(tmp1,xpow4,188); // 188x^4
        mpz_add(p_tmp,tmp1,p_tmp);// x^8 + 5x^7 + 7x^6 + 37x^5 +  188x^4
        mpz_mul_ui(tmp1,xpow3,259); // 259x^3
        mpz_add(p_tmp,tmp1,p_tmp); // x^8 + 5x^7 + 7x^6 + 37x^5 +  188x^4 + 259x^3
        mpz_mul_ui(tmp1,xpow2,343); // 343x^2
        mpz_add(p_tmp,tmp1,p_tmp); // x^8 + 5x^7 + 7x^6 + 37x^5 +  188x^4 + 259x^3 + 343x^2
        mpz_mul_ui(tmp1,X,1763); //1763x
        mpz_add(p_tmp,tmp1,p_tmp); // x^8 + 5x^7 + 7x^6 + 37x^5 +  188x^4 + 259x^3 +1763x
        mpz_add_ui(p_tmp,p_tmp,2401);// x^8 + 5x^7 + 7x^6 + 37x^5 +  188x^4 + 259x^3 +1763x + 2401
        
        mpz_tdiv_r_ui(tmp1,p_tmp,21);
        
        
        if(mpz_cmp_ui(tmp1,0)==0){
            mpz_div_ui(p_tmp,p_tmp,21);
            // gmp_printf("%Zd\n",p_tmp);
            
            mpz_pow_ui(tmp,p_tmp,18);
            mpz_sub_ui(tmp,tmp,1);
            mpz_tdiv_r(tmp2,tmp,r_tmp);
            
            if(mpz_cmp_ui(tmp2,0)==0){
                // printf("afh\n");
                mpz_sub_ui(tmp,p_tmp,1); //tmp = p-1
                mpz_mod(tmp,tmp,mod); // tmp = p-1/3
                k=mpz_get_ui(tmp);
                
                j=mpz_probab_prime_p(p_tmp,25);
                mpz_add_ui(tmp,p_tmp,1);
                mpz_tdiv_r_ui(tmp,tmp,4);
                l=mpz_get_ui(tmp);
                // i=mpz_probab_prime_p(r_tmp,25);
                
                if(k == 0 && j >= 1 && l==0)
                {
                     count192p++;
//                    if ((int)mpz_sizeinbase(p_tmp,2) <341)
//                    {
//                        printf("Got it %lld\n",count192p);
//                        continue;
//                    }
                    
                   
                    
                    mpz_t p_1,p_m1,p_mod4,c1_tmp,c2_tmp,q_p_m1_d3,c1_mod;
                    int c1 = 2, c2 = -1;
                    
                    mpz_init(p_1);
                    mpz_init(p_m1);
                    mpz_init(p_mod4);
                    mpz_init(c1_tmp);
                    mpz_init(c2_tmp);
                    mpz_init(q_p_m1_d3);
                    mpz_init(c1_mod);
                    
                    mpz_set_ui(c1_tmp,c1);
                    mpz_set_ui(c2_tmp,c2);
                    
                    mpz_sub_ui(p_m1,p_tmp,1);
                    
                    mpz_cdiv_r_ui(p_1,p_m1,3);
                    gmp_printf("\n\nP = %Zd\nr = P-1/3 %Zd\n",p_tmp,p_1);
                    
                    mpz_cdiv_q_ui(q_p_m1_d3,p_m1,3);
                    gmp_printf("q = P-1/3 %Zd\n",q_p_m1_d3);
                    
                    mpz_powm(c1_tmp,c1_tmp,q_p_m1_d3,p_tmp);
                    gmp_printf("2^(P-1)/3 %Zd\n",c1_tmp);
                    
                    
                    int leg = mpz_legendre(c2_tmp,p_tmp);
                    printf("(-1)^(P-1)/2 = %d\n",leg);
                    
                    mpz_mod_ui(p_mod4,p_tmp,4);
                    gmp_printf("P mod 4 = %Zd\n",p_mod4);
                    
                    
                    //                    if ((mpz_cmp_ui(p_1,0) == 0) && (mpz_cmp_ui(p_mod4,3) == 0) && (mpz_cmp_ui(c1_tmp,0) != 0 &&  mpz_cmp_ui(c1_tmp,1) != 0) && (leg == -1 || mpz_cmp_ui(p_tmp1,leg) == 0))
                    if ((mpz_cmp_ui(c1_tmp,0) != 0 &&  mpz_cmp_ui(c1_tmp,1) != 0) && (leg == -1 || mpz_cmp_ui(p_m1,leg) == 0))
                    {
                        count192p_cond++;
                        gmp_printf("%Zd\n",X);
                        gmp_printf("p:%Zd\n",p_tmp);
                        printf("p = %dbit\n\n\n",(int)mpz_sizeinbase(p_tmp,2));
                        
                        if(fp == NULL){
                            printf("Couldn't open file\n");
                        }
                        gmp_fprintf(fp,"%Zd,%ld,%Zd,%d\n",X,mpz_popcount(X),p_tmp,(int)mpz_sizeinbase(p_tmp,2));
                        if ((int)mpz_sizeinbase(p_tmp,2) == 512)
                        {
                            fclose(fp);
                            break;
                            
                        }
                    }
                }
            }
        }
        mpz_add_ui(X,X,42);
    }
    printf("Total %lld primes generated, where %lld satisfies our condition\n",count192p,count192p_cond);
    printf(" %d of total generated",(int)(count192p_cond * 100)/(int)count192p);
    
    return 0;
}
