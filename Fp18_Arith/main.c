//
//  main.c
//  Fp18_Arith
//
//  Created by Khandaker Md. Al-Amin on 4/15/16.
//  Copyright © 2016 Khandaker Md. Al-Amin. All rights reserved.
//

#include"embedding_degree18.h"
#include "parameters.h"
#include <assert.h>

#define C1 2
#define C2 -1
#define C1_sq 4

int main(void)
{
    mpz_init(X);
    mpz_set_str(X,"18446893747415302274",10);//192bit
   

    
    mpz_init(prime);
//mpz_set_str(prime,"7",10);
    mpz_set_str(prime,"638508488753389092195439720208817843316062995515124574544010783086949264599518591426924070465759719017041310253064889352571109595156203400346010025740431",10);
    mpz_init(r_order);
    mpz_init(r_order_EFp);
    mpz_init(t_trace);
    mpz_init(b);
    mpz_init(c1_tmp);
    mpz_init(c1_tmp_bar);
    
//    get_C1_C1bar();
    
//    struct Fp6 P,RES,RES1,Q;
//    Fp6_init(&P);
//    Fp6_init(&Q);
//    Fp6_init(&RES);
//    Fp6_init(&RES1);
//    Fp6_take_input(&P);
//    Fp6_take_input(&Q);
//    
//    Fp6_mul(&RES, &P, &Q);
////    Fp3_neg(&RES, &P);
//    printf("new\n");
//    Fp6_printf(&RES);
//    Fp6_mul_prev(&RES1, &P,&Q);
//    printf("prev\n");
//    Fp6_printf(&RES1);
    
    
    EFp_set_EC_parameter();
    // mpz_set_str(p,"11",10);
    gmp_printf("p=%Zd\n",prime);
    gmp_printf("r=%Zd\n",r_order);
    gmp_printf("t=%Zd\n",t_trace);
    gmp_printf("#E(Fp)=%Zd\n",r_order_EFp);
    
    printf("p = %d bit\n",(int)mpz_sizeinbase(prime,2));
    printf("r = %d bit\n",(int)mpz_sizeinbase(r_order,2));
    printf("t = %d bit\n",(int)mpz_sizeinbase(t_trace,2));
    
    gmp_printf("y^2=x^3+%Zd\n",b);
    

//     struct EFp18 P,Q;
//    
//     EFp18_init(&P);
//     EFp18_init(&Q);
//    
//     EFp18_random_set_for_Ate(&P);
//     EFp18_frobenius_map(&Q,&P);
//     EFp18_printf(&Q);
//     EFp18_SCM(&P,&P,prime);
//     EFp18_printf(&P);
//     printf("%d\n",EFp18_cmp(&P,&Q));
    
    mpz_clear(prime);
    mpz_clear(r_order);
    mpz_clear(b);
    mpz_clear(c1_tmp);
    mpz_clear(c1_tmp_bar);
    return 0;
}


void Fp_take_input(struct Fp *RES)
{
    struct Fp tmp;
    Fp_init(&tmp);
    
    char inputStr[1025];
    int flag;
    printf ("Enter Fp element:\n");
    scanf("%1024s",inputStr);
    mpz_set_ui(tmp.x_0,0);
    
    flag = mpz_set_str(tmp.x_0,inputStr,10);
    assert(flag == 0);
    
    Fp_set(RES,&tmp);
//    Fp_printf(RES);
    Fp_clear(&tmp);
}

void Fp3_take_input(struct Fp3 *RES)
{
    struct Fp3 tmp;
    Fp3_init(&tmp);
//    printf ("Will take 3 Fp element:\n");
    Fp_take_input(&tmp.a0);
    Fp_take_input(&tmp.a1);
    Fp_take_input(&tmp.a2);
    
    Fp3_set(RES,&tmp);
    Fp3_clear(&tmp);
}

void Fp6_take_input(struct Fp6 *RES)
{
    struct Fp6 tmp;
    Fp6_init(&tmp);
    
    Fp3_take_input(&tmp.a0);
    Fp3_take_input(&tmp.a1);
    
    Fp6_set(RES,&tmp);
    Fp6_clear(&tmp);
}

void Fp18_take_input(struct Fp18 *RES)
{
    struct Fp18 tmp;
    Fp18_init(&tmp);
    //    printf ("Will take 3 Fp element:\n");
    Fp6_take_input(&tmp.m0);
    Fp6_take_input(&tmp.m1);
    Fp6_take_input(&tmp.m2);
    
    Fp18_set(RES,&tmp);
    Fp18_clear(&tmp);
}


//-----------------------------------------------------------------------------------------

void Fp_init(struct Fp *A){
    mpz_init(A->x_0);
}
void Fp_set(struct Fp *RES,struct Fp *A){
    mpz_set(RES->x_0,A->x_0);
}
void Fp_set_mpz(struct Fp *RES,mpz_t a){
    mpz_set(RES->x_0,a);
}
void Fp_set_ui(struct Fp *A,signed long int B){
    mpz_set_ui(A->x_0,B);
}
void Fp_random(struct Fp *A){
    mpz_random(A->x_0,10);
    mpz_mod(A->x_0,A->x_0,prime);
}
void Fp_clear(struct Fp *A){
    mpz_clear(A->x_0);
}
void Fp_printf(struct Fp *A){
    gmp_printf("%Zd\n",A->x_0);
}
void Fp_add(struct Fp *RES,struct Fp *a,struct Fp *b){
    struct Fp tmp;
    Fp_init(&tmp);
    
    mpz_add(tmp.x_0,a->x_0,b->x_0);
    mpz_mod(tmp.x_0,tmp.x_0,prime);
    
    Fp_set(RES,&tmp);
    Fp_clear(&tmp);
}
void Fp_add_ui(struct Fp *RES,struct Fp *a,unsigned long int b){
    struct Fp tmp;
    Fp_init(&tmp);
    
    mpz_add_ui(tmp.x_0,a->x_0,b);
    mpz_mod(tmp.x_0,tmp.x_0,prime);
    
    Fp_set(RES,&tmp);
    Fp_clear(&tmp);
}
void Fp_sub(struct Fp *RES,struct Fp *a,struct Fp *b){
    struct Fp tmp;
    Fp_init(&tmp);
    
    mpz_sub(tmp.x_0,a->x_0,b->x_0);
    mpz_mod(tmp.x_0,tmp.x_0,prime);
    
    Fp_set(RES,&tmp);
    Fp_clear(&tmp);
}
void Fp_sub_ui(struct Fp *RES,struct Fp *a,unsigned long int b){
    struct Fp tmp;
    Fp_init(&tmp);
    
    mpz_sub_ui(tmp.x_0,a->x_0,b);
    mpz_mod(tmp.x_0,tmp.x_0,prime);
    
    Fp_set(RES,&tmp);
    
    Fp_clear(&tmp);
}
void Fp_mul(struct Fp *RES,struct Fp *a,struct Fp *b){
    struct Fp tmp;
    Fp_init(&tmp);
    
    mpz_mul(tmp.x_0,a->x_0,b->x_0);
    mpz_mod(tmp.x_0,tmp.x_0,prime);
    
    Fp_set(RES,&tmp);
    Fp_clear(&tmp);
}
void Fp_mul_ui(struct Fp *RES,struct Fp *a,unsigned long int b){
    struct Fp tmp;
    Fp_init(&tmp);
    
    mpz_mul_ui(tmp.x_0,a->x_0,b);
    mpz_mod(tmp.x_0,tmp.x_0,prime);
    
    Fp_set(RES,&tmp);
    
    Fp_clear(&tmp);
}

void Fp_mul_c1(struct Fp *RES,struct Fp *a){
    struct Fp tmp;
    Fp_init(&tmp);
    
    mpz_mul_2exp(tmp.x_0,a->x_0,1);//C1=2, so 1 bit shift
    mpz_mod(tmp.x_0,tmp.x_0,prime);
    Fp_set(RES,&tmp);
    Fp_clear(&tmp);
}
void Fp_inv(struct Fp *RES,struct Fp *a){
    struct Fp tmp;
    Fp_init(&tmp);
    
    mpz_invert(tmp.x_0,a->x_0,prime);
    
    Fp_set(RES,&tmp);
    Fp_clear(&tmp);
}


void Fp_div(struct Fp *RES,struct Fp *a,struct Fp *b){
    struct Fp tmp;
    Fp_init(&tmp);
    
    mpz_invert(tmp.x_0,b->x_0,prime);
    mpz_mul(tmp.x_0,a->x_0,tmp.x_0);
    mpz_mod(tmp.x_0,tmp.x_0,prime);
    
    Fp_set(RES,&tmp);
    Fp_clear(&tmp);
}
//void Fp_pow(struct Fp *RES,struct Fp *A,mpz_t B){//RES = A^B
//    unsigned long long i,length;
//    length= (unsigned long long)mpz_sizeinbase(B,2);
//    char B_binary[length];
//    mpz_get_str(B_binary,2,B);
//    printf("Length: %lld\n",length);
////    printf("p: %s\n",&B_binary[0]);
//
//    struct Fp tmp;
//    Fp_init(&tmp);
//    Fp_set(&tmp,A);
//
//    for(i=1;B_binary[i]!='\0';i++){
//        Fp_mul(&tmp,&tmp,&tmp);
//        if(B_binary[i]=='1'){
//            Fp_mul(&tmp,&tmp,A);
//        }
//    }
//    Fp_set(RES,&tmp);
//    Fp_clear(&tmp);
//}

void Fp_pow(struct Fp *RES,struct Fp *A,mpz_t B){//RES = A^B
    unsigned long long i,length;
    length= (unsigned long long)mpz_sizeinbase(B,2);
    char B_binary[length];
    mpz_get_str(B_binary,2,B);
//    printf("Length: %lld\n",length);
    //    printf("p: %s\n",&B_binary[0]);
    
    struct Fp tmp,dumy;
    Fp_init(&tmp);
    Fp_init(&dumy);
    Fp_set(&tmp,A);
    Fp_set(&dumy,A);
    
    for(i=1;B_binary[i]!='\0';i++){
        Fp_mul(&tmp,&tmp,&tmp);
        Fp_mul(&dumy,&tmp,A);
        if(B_binary[i]=='1'){
            Fp_mul(&tmp,&tmp,A);
            Fp_mul(&dumy,&dumy,&dumy);
        }
    }
    Fp_set(RES,&tmp);
    Fp_clear(&tmp);
    Fp_clear(&dumy);
}


void Fp_sqrt(struct Fp *RES,struct Fp *A){
    struct Fp n_tmp,y_tmp,x_tmp,b_tmp,t_tmp,tmp_Fp;
    Fp_init(&n_tmp);
    Fp_init(&y_tmp);
    Fp_init(&x_tmp);
    Fp_init(&b_tmp);
    Fp_init(&t_tmp);
    Fp_init(&tmp_Fp);
    
    Fp_set(&n_tmp,A);
    
    mpz_t tmp_mpz,q_tmp,e_tmp,r_tmp,set_1,set_2;
    mpz_init(tmp_mpz);
    mpz_init(q_tmp);
    mpz_init(e_tmp);
    mpz_init(r_tmp);
    mpz_init(set_1);
    mpz_init(set_2);
    
    mpz_set_ui(set_1,1);
    mpz_set_ui(set_2,2);
    
    while(mpz_legendre(n_tmp.x_0,prime)!=-1){
        Fp_add_ui(&n_tmp,&n_tmp,1);
    }
    
    mpz_set(q_tmp,prime);
    mpz_sub_ui(q_tmp,q_tmp,1);
    mpz_set_ui(e_tmp,0);
    
    while(mpz_odd_p(q_tmp)==0){
        mpz_add_ui(e_tmp,e_tmp,1);
        mpz_div_ui(q_tmp,q_tmp,2);
    }
    
    Fp_pow(&y_tmp,&n_tmp,q_tmp);
    
    mpz_set(r_tmp,e_tmp);
    
    mpz_sub_ui(tmp_mpz,q_tmp,1);
    mpz_div_ui(tmp_mpz,tmp_mpz,2);
    Fp_pow(&x_tmp,A,tmp_mpz);
    Fp_pow(&tmp_Fp,&x_tmp,set_2);
    Fp_mul(&b_tmp,&tmp_Fp,A);
    Fp_mul(&x_tmp,&x_tmp,A);
    
    int m;
    
    while(Fp_cmp_mpz(&b_tmp,set_1)==1){
        m=-1;
        while(Fp_cmp_mpz(&tmp_Fp,set_1)==1){
            m++;
            mpz_pow_ui(tmp_mpz,set_2,m);
            Fp_pow(&tmp_Fp,&b_tmp,tmp_mpz);
        }
        // gmp_printf("%Zd,%Zd\n",x.a0.a0,x.a1.a0);
        mpz_sub_ui(tmp_mpz,r_tmp,m);
        mpz_sub_ui(tmp_mpz,tmp_mpz,1);
        mpz_powm(tmp_mpz,set_2,tmp_mpz,prime);
        Fp_pow(&t_tmp,&y_tmp,tmp_mpz);
        Fp_pow(&y_tmp,&t_tmp,set_2);
        mpz_set_ui(r_tmp,m);
        Fp_mul(&x_tmp,&x_tmp,&t_tmp);
        Fp_mul(&b_tmp,&b_tmp,&y_tmp);
    }
    
    Fp_set(RES,&x_tmp);
    
    Fp_clear(&n_tmp);
    Fp_clear(&y_tmp);
    Fp_clear(&x_tmp);
    Fp_clear(&b_tmp);
    Fp_clear(&t_tmp);
    Fp_clear(&tmp_Fp);
    mpz_clear(tmp_mpz);
    mpz_clear(q_tmp);
    mpz_clear(e_tmp);
    mpz_clear(r_tmp);
    mpz_clear(set_1);
}
void Fp_neg(struct Fp *RES,struct Fp *A){
    struct Fp tmp;
    Fp_init(&tmp);
    
    mpz_sub(tmp.x_0,prime,A->x_0);
    mpz_mod(tmp.x_0,tmp.x_0,prime);
    
    Fp_set(RES,&tmp);
    Fp_clear(&tmp);
}
int Fp_cmp(struct Fp *A,struct Fp *B){
    if(mpz_cmp(A->x_0,B->x_0)==0){
        return 0;
    }
    return 1;
}
int Fp_cmp_mpz(struct Fp *A,mpz_t B){
    if(mpz_cmp(A->x_0,B)==0){
        return 0;
    }
    return 1;
}

//-----------------------------------------------------------------------------------------

void Fp3_init(struct Fp3 *A){
    Fp_init(&A->a0);
    Fp_init(&A->a1);
    Fp_init(&A->a2);
}
void Fp3_set(struct Fp3 *RES,struct Fp3 *A){
    Fp_set(&RES->a0,&A->a0);
    Fp_set(&RES->a1,&A->a1);
    Fp_set(&RES->a2,&A->a2);
}
void Fp3_set_ui(struct Fp3 *A,signed long int B){
    Fp_set_ui(&A->a0,B);
    Fp_set_ui(&A->a1,B);
    Fp_set_ui(&A->a2,B);
}
void Fp3_random(struct Fp3 *A){
    Fp_random(&A->a0);
    Fp_random(&A->a1);
    Fp_random(&A->a2);
}
void Fp3_clear(struct Fp3 *A){
    Fp_clear(&A->a0);
    Fp_clear(&A->a1);
    Fp_clear(&A->a2);
}
void Fp3_printf(struct Fp3 *A){
    gmp_printf("%Zd,%Zd,%Zd\n",A->a0.x_0,A->a1.x_0,A->a2.x_0);
}
void Fp3_add(struct Fp3 *RES,struct Fp3 *A,struct Fp3 *B){
    struct Fp3 tmp;
    Fp3_init(&tmp);
    
    Fp_add(&tmp.a0,&A->a0,&B->a0);
    Fp_add(&tmp.a1,&A->a1,&B->a1);
    Fp_add(&tmp.a2,&A->a2,&B->a2);
    
    Fp3_set(RES,&tmp);
    Fp3_clear(&tmp);
}
void Fp3_add_ui(struct Fp3 *RES,struct Fp3 *A,unsigned long int B){
    struct Fp3 tmp;
    Fp3_init(&tmp);
    
    Fp_add_ui(&tmp.a0,&A->a0,B);
    Fp_add_ui(&tmp.a1,&A->a1,B);
    Fp_add_ui(&tmp.a2,&A->a2,B);
    
    Fp3_set(RES,&tmp);
    Fp3_clear(&tmp);
}
void Fp3_sub(struct Fp3 *RES,struct Fp3 *A,struct Fp3 *B){
    struct Fp3 tmp;
    Fp3_init(&tmp);
    
    Fp_sub(&tmp.a0,&A->a0,&B->a0);
    Fp_sub(&tmp.a1,&A->a1,&B->a1);
    Fp_sub(&tmp.a2,&A->a2,&B->a2);
    
    Fp3_set(RES,&tmp);
    Fp3_clear(&tmp);
}

void Fp3_mul_prev(struct Fp3 *RES,struct Fp3 *A,struct Fp3 *B){
    //(a0,a1,a2)*(b0,b1,b2)=(x0y0+xi((a1+a2)(b1+b2)-a1b1-x2y2),xix2y2+(a0+a1)(b0+b1)-x0y0-a1b1,a1b1+(a0+a2)(b0+b2)-x0y0-x2y2)
    struct Fp A0,A1,A2,tmp_a01,tmp_a12,tmp_a20,tmp_b01,tmp_b12,tmp_b20,A3,A4,A5,tmp;
    struct Fp3 t_RES;
    Fp_init(&A0);
    Fp_init(&A1);
    Fp_init(&A2);
    Fp_init(&tmp_a01);
    Fp_init(&tmp_a12);
    Fp_init(&tmp_a20);
    Fp_init(&tmp_b01);
    Fp_init(&tmp_b12);
    Fp_init(&tmp_b20);
    Fp_init(&A3);
    Fp_init(&A4);
    Fp_init(&A5);
    Fp_init(&tmp);
    Fp3_init(&t_RES);
    
    Fp_mul(&A0,&A->a0,&B->a0);//A0=a0*b0
    Fp_mul(&A1,&A->a1,&B->a1);//A1=a1*b1
    Fp_mul(&A2,&A->a2,&B->a2);//A2=a2*b2
    
    Fp_add(&tmp_a01,&A->a0,&A->a1);//a0+a1
    Fp_add(&tmp_a12,&A->a1,&A->a2);//a1+a2
    Fp_add(&tmp_a20,&A->a0,&A->a2);//a2+a0
    Fp_add(&tmp_b01,&B->a0,&B->a1);//b0+b1
    Fp_add(&tmp_b12,&B->a1,&B->a2);//b1+b2
    Fp_add(&tmp_b20,&B->a0,&B->a2);//b2+b0
    
    Fp_mul(&A3,&tmp_a01,&tmp_b01);//A3=(a0+a1)(b0+b1)
    Fp_mul(&A4,&tmp_a12,&tmp_b12);//A4=(a1+a2)(b1+b2)
    Fp_mul(&A5,&tmp_a20,&tmp_b20);//A5=(a2+a0)(b2+b0)
    
    //(a0,a1,a2)*(b0,b1,b2)=(a0b0 + ai((a1+a2)(b1+b2)-a1b1-a2b2), aia2b2+(a0+a1)(b0+b1)-a0b0-a1b1, a1b1+(a0+a2)(b0+b2)-a0b0-a2b2)
    
    //t1 = A3 −A1 −A0
    //t2 = A4−A2−A0+A1
    //t3 = A5 −A1 −A2
    //ab = (t0 + c1t3) + (t1 + c1t4)ω + t2ω2.
    Fp_sub(&A4,&A4,&A1);//A4-A1
    Fp_sub(&A4,&A4,&A2);//A4-A2-A1        /(a1+a2)(b1+b2)-a1b1-a2b2
    Fp_mul_ui(&tmp,&A4,C1);
    Fp_add(&t_RES.a0,&A0,&tmp);
    
    Fp_sub(&A3,&A3,&A0);//A3-A0
    Fp_sub(&A3,&A3,&A1);//t1 = A3-A1-A0
    Fp_mul_ui(&tmp,&A2,C1);//A2*C1
    Fp_add(&t_RES.a1,&tmp,&A3);
    
    Fp_sub(&A5,&A5,&A0);//A5-A0
    Fp_sub(&A5,&A5,&A2);//A5-A2-A0
    Fp_add(&t_RES.a2,&A1,&A5);//A5-A2-A0 + A1;;t2 = A4−A2−A0+A1
    
    Fp3_set(RES,&t_RES);
    
    Fp_clear(&A0);
    Fp_clear(&A1);
    Fp_clear(&A2);
    Fp_clear(&tmp_a01);
    Fp_clear(&tmp_a12);
    Fp_clear(&tmp_a20);
    Fp_clear(&tmp_b01);
    Fp_clear(&tmp_b12);
    Fp_clear(&tmp_b20);
    Fp_clear(&A3);
    Fp_clear(&A4);
    Fp_clear(&A5);
    Fp_clear(&tmp);
}
void Fp3_mul(struct Fp3 *RES,struct Fp3 *A,struct Fp3 *B){
    //(a0,a1,a2)*(b0,b1,b2)=(x0y0+xi((a1+a2)(b1+b2)-a1b1-x2y2),xix2y2+(a0+a1)(b0+b1)-x0y0-a1b1,a1b1+(a0+a2)(b0+b2)-x0y0-x2y2)
    struct Fp A0,A1,A2,tmp_a01,tmp_a12,tmp_a20,tmp_b01,tmp_b12,tmp_b20,A3,A4,A5,t0,t1,t2,t3,t4,tmp;
    
    struct Fp3 t_RES;
    Fp_init(&A0);
    Fp_init(&A1);
    Fp_init(&A2);
    Fp_init(&tmp_a01);
    Fp_init(&tmp_a12);
    Fp_init(&tmp_a20);
    Fp_init(&tmp_b01);
    Fp_init(&tmp_b12);
    Fp_init(&tmp_b20);
    Fp_init(&A3);
    Fp_init(&A4);
    Fp_init(&A5);
    Fp_init(&t0);
    Fp_init(&t1);
    Fp_init(&t2);
    Fp_init(&t3);
    Fp_init(&t4);
    Fp_init(&tmp);
    Fp3_init(&t_RES);
    
    Fp_mul(&A0,&A->a0,&B->a0);//A0=a0*b0
    Fp_mul(&A1,&A->a1,&B->a1);//A1=a1*b1
    Fp_mul(&A2,&A->a2,&B->a2);//A2=a2*b2
    
    Fp_add(&tmp_a01,&A->a0,&A->a1);//a0+a1
    Fp_add(&tmp_a12,&A->a1,&A->a2);//a1+a2
    Fp_add(&tmp_a20,&A->a0,&A->a2);//a2+a0
    Fp_add(&tmp_b01,&B->a0,&B->a1);//b0+b1
    Fp_add(&tmp_b12,&B->a1,&B->a2);//b1+b2
    Fp_add(&tmp_b20,&B->a0,&B->a2);//b2+b0
    
    Fp_mul(&A3,&tmp_a01,&tmp_b01);//A3=(a0+a1)(b0+b1)
    Fp_mul(&A4,&tmp_a20,&tmp_b20);//A4=(a0+a2)(b0+b2)
    Fp_mul(&A5,&tmp_a12,&tmp_b12);//A5=(a1+a2)(b1+b2)
    
    Fp_set(&t0,&A0);//t0=A0
    Fp_set(&t4, &A2);//t4= A2
    Fp_sub(&A3,&A3,&A0);//A3-A0
    Fp_sub(&t1,&A3,&A1);//t1 = A3-A1-A0
    Fp_sub(&A4,&A4,&A0);//A4-A0
    Fp_sub(&A4,&A4,&A2);//A4-A2-A0
    Fp_add(&t2,&A1,&A4);//t2 = A4−A2−A0+A1
    Fp_sub(&A5,&A5,&A1);//A5-A1
    Fp_sub(&t3,&A5,&A2);//t3 = A5 −A1 −A2
    
    //ab = (t0 + c1t3) + (t1 + c1t4)ω + t2ω2.
    Fp_mul_c1(&tmp, &t3);
//    Fp_mul_ui(&tmp,&t3,C1);
    Fp_add(&t_RES.a0, &tmp, &t0);
    Fp_mul_c1(&tmp, &t4);
//    Fp_mul_ui(&tmp,&t4,C1);
    Fp_add(&t_RES.a1, &tmp, &t1);
    Fp_set(&t_RES.a2, &t2);
    
    Fp3_set(RES,&t_RES);
    
    Fp_clear(&A0);
    Fp_clear(&A1);
    Fp_clear(&A2);
    Fp_clear(&tmp_a01);
    Fp_clear(&tmp_a12);
    Fp_clear(&tmp_a20);
    Fp_clear(&tmp_b01);
    Fp_clear(&tmp_b12);
    Fp_clear(&tmp_b20);
    Fp_clear(&A3);
    Fp_clear(&A4);
    Fp_clear(&A5);
    Fp_clear(&t0);
    Fp_clear(&t1);
    Fp_clear(&t2);
    Fp_clear(&t3);
    Fp_clear(&t4);
    Fp_clear(&tmp);
}

void Fp3_mul_omega(struct Fp3 *RES,struct Fp3 *A){
    struct Fp3 tmp;
    Fp3_init(&tmp);
    
    Fp_mul_c1(&tmp.a0,&A->a2);//omega^3=C1
//    Fp_mul_ui(&tmp.a0,&A->a2,C1);//omega^3=C1
    Fp_set(&tmp.a1,&A->a0);
    Fp_set(&tmp.a2,&A->a1);
    
    Fp3_set(RES,&tmp);
    Fp3_clear(&tmp);
}

void Fp3_mul_ui(struct Fp3 *RES,struct Fp3 *A,unsigned long int B){
    struct Fp3 tmp;
    Fp3_init(&tmp);
    
    Fp_mul_ui(&tmp.a0,&A->a0,B);
    Fp_mul_ui(&tmp.a1,&A->a1,B);
    Fp_mul_ui(&tmp.a2,&A->a2,B);
    
    Fp3_set(RES,&tmp);
    Fp3_clear(&tmp);
}
void Fp3_mul_Fp(struct Fp3 *RES,struct Fp3 *A,struct Fp *B){
    struct Fp3 tmp;
    Fp3_init(&tmp);
    
    Fp_mul(&tmp.a0,&A->a0,B);
    Fp_mul(&tmp.a1,&A->a1,B);
    Fp_mul(&tmp.a2,&A->a2,B);
    
    Fp3_set(RES,&tmp);
    Fp3_clear(&tmp);
}

void get_C1_C1bar(){
    mpz_t prime_s1,q_p_m1_d3;
    mpz_init(prime_s1);
    mpz_init(q_p_m1_d3);
    
    mpz_set_ui(c1_tmp,C1);
    
    mpz_sub_ui(prime_s1,prime,1);
    mpz_cdiv_q_ui(q_p_m1_d3,prime_s1,3);
    mpz_powm(c1_tmp,c1_tmp,q_p_m1_d3,prime);
    mpz_powm_ui(c1_tmp_bar,c1_tmp,2,prime);
    
    mpz_clear(prime_s1);
    mpz_clear(q_p_m1_d3);
}

//a^−1 = n(a)^−1(a^q*a^q^2 ),
void Fp3_frobenious_conjugate(struct Fp3 *RES,struct Fp3 *A){
    struct Fp3 t_RES;
    Fp3_init(&t_RES);
    
    struct Fp tmp_c1;
    Fp_init(&tmp_c1);
    
    mpz_set(tmp_c1.x_0,c1_tmp);
    Fp_set(&t_RES.a0,&A->a0);
    Fp_mul(&t_RES.a1,&A->a1,&tmp_c1);
    Fp_set_mpz(&tmp_c1, c1_tmp_bar);
    Fp_mul(&t_RES.a2,&A->a2,&tmp_c1);
    
    Fp3_set(RES,&t_RES);
    Fp3_clear(&t_RES);
    Fp_clear(&tmp_c1);
}


void Fp3_invert(struct Fp3 *RES, struct Fp3 *A){
    struct Fp3 t_RES,Aq,Aqsq,t_Aq,AqAqsq,t_norm;
    Fp3_init(&t_RES);
    Fp3_init(&Aq);
    Fp3_init(&Aqsq);
    Fp3_init(&t_Aq);
    Fp3_init(&AqAqsq);
    Fp3_init(&t_norm);
    
    Fp3_frobenious_conjugate(&Aq, A);
    Fp3_set(&t_Aq, &Aq);
    Fp3_frobenious_conjugate(&Aqsq,&t_Aq);
    Fp3_mul(&AqAqsq, &Aq, &Aqsq);
    Fp3_mul(&t_norm, &AqAqsq, A);

    struct Fp norm,T0;
    Fp_init(&norm);
    Fp_init(&T0);
    
    if (mpz_cmp_ui(t_norm.a1.x_0,0) != 0 || mpz_cmp_ui(t_norm.a2.x_0,0) != 0)
    {
        printf("Fp3 inverse calculation goes wrong\n");
        exit(0);
    }
    
    mpz_set(T0.x_0,t_norm.a0.x_0);
    Fp_inv(&norm, &T0);
    Fp_mul(&t_RES.a0, &AqAqsq.a0, &norm);
    Fp_mul(&t_RES.a1, &AqAqsq.a1, &norm);
    Fp_mul(&t_RES.a2, &AqAqsq.a2, &norm);
    
    Fp3_set(RES,&t_RES);
    
    Fp3_clear(&t_RES);
    Fp3_clear(&Aq);
    Fp3_clear(&Aqsq);
    Fp3_clear(&AqAqsq);
    Fp3_clear(&t_norm);
    Fp_clear(&T0);
    Fp_clear(&norm);
}
void Fp3_div(struct Fp3 *RES,struct Fp3 *A,struct Fp3 *B){
    struct Fp3 tmp,t_RES;
    Fp3_init(&tmp);
    Fp3_init(&t_RES);
    
    Fp3_invert(&tmp,B);
    Fp3_mul(&t_RES,A,&tmp);
    
    Fp3_set(RES,&t_RES);
    
    Fp3_clear(&tmp);
    Fp3_clear(&t_RES);
}
void Fp3_pow(struct Fp3 *RES,struct Fp3 *A,mpz_t B){
    int i;
    int r;//bit数
    r= (int)mpz_sizeinbase(B,2);
    //printf("r= %d\n",r);
    
    struct Fp3 RESwer_tmp;
    Fp3_init(&RESwer_tmp);
    Fp3_set(&RESwer_tmp,A);
    
    struct Fp3 in_tmp;
    Fp3_init(&in_tmp);
    Fp3_set(&in_tmp,A);
    
    for(i=r-2;i>=0;i--){
        if(mpz_tstbit(B,i)==1){
            Fp3_mul(&RESwer_tmp,&RESwer_tmp,&RESwer_tmp);//a*2
            Fp3_mul(&RESwer_tmp,&RESwer_tmp,&in_tmp);//*a
        }else{
            Fp3_mul(&RESwer_tmp,&RESwer_tmp,&RESwer_tmp);//a*2
        }
    }
    
    Fp3_set(RES,&RESwer_tmp);
    
    Fp3_clear(&RESwer_tmp);
    Fp3_clear(&in_tmp);
}
void Fp3_sqrt(struct Fp3 *RES,struct Fp3 *A){
    struct Fp3 n,y,x,b,t,tmp_Fp3;
    Fp3_init(&n);
    Fp3_init(&y);
    Fp3_init(&x);
    Fp3_init(&b);
    Fp3_init(&t);
    Fp3_init(&tmp_Fp3);
    Fp3_set(&n,A);
    
    mpz_t tmp_mpz,q,e,r,set_1,set_2;
    mpz_init(tmp_mpz);
    mpz_init(q);
    mpz_init(e);
    mpz_init(r);
    mpz_init(set_1);
    mpz_init(set_2);
    mpz_set_ui(set_1,1);
    mpz_set_ui(set_2,2);
    
    while(Fp3_legendre(&n)!=-1){
        Fp3_random(&n);
    }
    
    mpz_pow_ui(q,prime,3);
    mpz_sub_ui(q,q,1);
    mpz_set_ui(e,0);
    while(mpz_odd_p(q)==0){
        mpz_add_ui(e,e,1);
        mpz_div_ui(q,q,2);
    }
    Fp3_pow(&y,&n,q);
    mpz_set(r,e);
    mpz_sub_ui(tmp_mpz,q,1);
    mpz_div_ui(tmp_mpz,tmp_mpz,2);
    Fp3_pow(&x,A,tmp_mpz);
    Fp3_pow(&tmp_Fp3,&x,set_2);
    Fp3_mul(&b,&tmp_Fp3,A);
    Fp3_mul(&x,&x,A);
    int m;
    while(Fp3_cmp_mpz(&b,set_1)==1){
        m=-1;
        Fp3_set(&tmp_Fp3,&b);
        while(Fp3_cmp_mpz(&tmp_Fp3,set_1)==1){
            m++;
            mpz_pow_ui(tmp_mpz,set_2,m);
            Fp3_pow(&tmp_Fp3,&b,tmp_mpz);
        }
        mpz_sub_ui(tmp_mpz,r,m);
        mpz_sub_ui(tmp_mpz,tmp_mpz,1);
        mpz_powm(tmp_mpz,set_2,tmp_mpz,prime);
        Fp3_pow(&t,&y,tmp_mpz);
        Fp3_pow(&y,&t,set_2);
        mpz_set_ui(r,m);
        Fp3_mul(&x,&x,&t);
        Fp3_mul(&b,&b,&y);
    }
    
    Fp3_set(RES,&x);
    
    Fp3_clear(&n);
    Fp3_clear(&y);
    Fp3_clear(&x);
    Fp3_clear(&b);
    Fp3_clear(&t);
    Fp3_clear(&tmp_Fp3);
    mpz_clear(tmp_mpz);
    mpz_clear(q);
    mpz_clear(e);
    mpz_clear(r);
    mpz_clear(set_1);
}
int Fp3_cmp(struct Fp3 *A,struct Fp3 *B){
    if(Fp_cmp(&A->a0,&B->a0)==0 && Fp_cmp(&A->a1,&B->a1)==0 && Fp_cmp(&A->a2,&B->a2)==0){
        return 0;
    }
    return 1;
}
int Fp3_cmp_mpz(struct Fp3 *A,mpz_t B){
    struct Fp3 tmp;
    Fp3_init(&tmp);
    if(Fp_cmp_mpz(&A->a0,B)==0 && Fp_cmp(&A->a1,&tmp.a1)==0 && Fp_cmp(&A->a2,&tmp.a2)==0){
        Fp3_clear(&tmp);
        return 0;
    }
    Fp3_clear(&tmp);
    return 1;
}
int Fp3_legendre(struct Fp3 *a){
    mpz_t i,cmp;
    mpz_init(i);
    mpz_init(cmp);
    mpz_set_ui(cmp,1);
    struct Fp3 tmp;
    Fp3_init(&tmp);
    mpz_pow_ui(i,prime,3);
    mpz_sub_ui(i,i,1);
    mpz_tdiv_q_ui(i,i,2);
    Fp3_pow(&tmp,a,i);
    
    if((Fp3_cmp_mpz(&tmp,cmp))==0){
        Fp3_clear(&tmp);
        mpz_clear(i);
        return 1;
    }else{
        Fp3_clear(&tmp);
        mpz_clear(i);
        return -1;
    }
}
void Fp3_neg(struct Fp3 *RES,struct Fp3 *a){
    struct Fp3 tmp;
    Fp3_init(&tmp);
    Fp_neg(&tmp.a0,&a->a0);
    Fp_neg(&tmp.a1,&a->a1);
    Fp_neg(&tmp.a2,&a->a2);
    Fp3_set(RES,&tmp);
    Fp3_clear(&tmp);
}

//-----------------------------------------------------------------------------------------

void Fp6_init(struct Fp6 *A){
    Fp3_init(&A->a0);
    Fp3_init(&A->a1);
}
void Fp6_set(struct Fp6 *RES,struct Fp6 *A){
    Fp3_set(&RES->a0,&A->a0);
    Fp3_set(&RES->a1,&A->a1);
}
void Fp6_set_ui(struct Fp6 *A,signed long int B){
    Fp3_set_ui(&A->a0,B);
    Fp3_set_ui(&A->a1,B);
}
void Fp6_random(struct Fp6 *A){
    Fp3_random(&A->a0);
    Fp3_random(&A->a1);
}
void Fp6_clear(struct Fp6 *A){
    Fp3_clear(&A->a0);
    Fp3_clear(&A->a1);
}
void Fp6_printf(struct Fp6 *A){
    gmp_printf("%Zd,%Zd,%Zd,%Zd,%Zd,%Zd\n",A->a0.a0.x_0,A->a0.a1.x_0,A->a0.a2.x_0,A->a1.a0.x_0,A->a1.a1.x_0,A->a1.a2.x_0);
}
void Fp6_add(struct Fp6 *RES,struct Fp6 *A,struct Fp6 *B){
    struct Fp6 tmp;
    Fp6_init(&tmp);
    
    Fp3_add(&tmp.a0,&A->a0,&B->a0);
    Fp3_add(&tmp.a1,&A->a1,&B->a1);
    
    Fp6_set(RES,&tmp);
    Fp6_clear(&tmp);
}
void Fp6_add_ui(struct Fp6 *RES,struct Fp6 *A,unsigned long int B){
    struct Fp6 tmp;
    Fp6_init(&tmp);
    
    Fp3_add_ui(&tmp.a0,&A->a0,B);
    Fp3_add_ui(&tmp.a1,&A->a1,B);
    
    Fp6_set(RES,&tmp);
    Fp6_clear(&tmp);
}
void Fp6_sub(struct Fp6 *RES,struct Fp6 *A,struct Fp6 *B){
    struct Fp6 tmp;
    Fp6_init(&tmp);
    
    Fp3_sub(&tmp.a0,&A->a0,&B->a0);
    Fp3_sub(&tmp.a1,&A->a1,&B->a1);
    
    Fp6_set(RES,&tmp);
    Fp6_clear(&tmp);
}
void Fp6_mul_prev(struct Fp6 *RES,struct Fp6 *A,struct Fp6 *B){
    //x^2-c2=0;c2=-1
    //= (a0b0 + c2a1b1) + (a0 + a1)(b0 + b1)τ−(a0b0)τ − (a1b1)τ.
    struct Fp3 tmp1,tmp2,tmp3,tmp4,tmp5,tmp6;
    Fp3_init(&tmp1);
    Fp3_init(&tmp2);
    Fp3_init(&tmp3);
    Fp3_init(&tmp4);
    Fp3_init(&tmp5);
    Fp3_init(&tmp6);
    
    struct Fp6 t_RES;
    Fp6_init(&t_RES);
    
    Fp3_mul(&tmp1,&A->a0,&B->a0);//a0*b0
    Fp3_mul(&tmp2,&A->a1,&B->a1);//a1*b1
    Fp3_mul_omega(&tmp3,&tmp2);//c2*a1*b1
    //    Fp3_mul_omega(&tmp3,&tmp2);
    Fp3_add(&t_RES.a0,&tmp1,&tmp3);//a*c+b*d*v
    Fp3_add(&tmp4,&A->a0,&A->a1);//a+b
    Fp3_add(&tmp5,&B->a0,&B->a1);//c+d
    Fp3_mul(&tmp6,&tmp4,&tmp5);//(a+b)(c+d)
    Fp3_sub(&t_RES.a1,&tmp6,&tmp1);
    Fp3_sub(&t_RES.a1,&t_RES.a1,&tmp2);
    
    Fp6_set(RES,&t_RES);
    
    Fp3_clear(&tmp1);
    Fp3_clear(&tmp2);
    Fp3_clear(&tmp3);
    Fp3_clear(&tmp4);
    Fp3_clear(&tmp5);
    Fp3_clear(&tmp6);
    Fp6_clear(&t_RES);
}
void Fp6_mul(struct Fp6 *RES,struct Fp6 *A,struct Fp6 *B){
    //x^2-c2=0;c2=-1
    //mn= (a0b0 + c2a1b1) + (a0 + a1)(b0 + b1)τ−(a0b0)τ − (a1b1)τ.
    struct Fp3 tmp1,tmp2,tmp3,tmp4,tmp5;
    Fp3_init(&tmp1);
    Fp3_init(&tmp2);
    Fp3_init(&tmp3);
    Fp3_init(&tmp4);
    Fp3_init(&tmp5);
    
    struct Fp6 t_RES;
    Fp6_init(&t_RES);
    
    Fp3_mul(&tmp1,&A->a0,&B->a0);//a0*b0
    Fp3_mul(&tmp2,&A->a1,&B->a1);//a1*b1
    Fp3_sub(&t_RES.a0, &tmp1, &tmp2);//c2*a1*b1; a0b0-a1b1
    Fp3_add(&tmp3,&A->a0,&A->a1);//a0+a1
    Fp3_add(&tmp4,&B->a0,&B->a1);//b0+b1
    Fp3_mul(&tmp5,&tmp3,&tmp4);//(a0+a1)(b0+b1)
    Fp3_sub(&t_RES.a1,&tmp5,&tmp1);//(a0+a1)(b0+b1)-a0b0
    Fp3_sub(&t_RES.a1,&t_RES.a1,&tmp2);//(a0+a1)(b0+b1)-a0b0-a1b1
    
    Fp6_set(RES,&t_RES);
    
    Fp3_clear(&tmp1);
    Fp3_clear(&tmp2);
    Fp3_clear(&tmp3);
    Fp3_clear(&tmp4);
    Fp3_clear(&tmp5);
    Fp6_clear(&t_RES);
}
void Fp6_mul_v_prev(struct Fp6 *RES,struct Fp6 *A){
    struct Fp6 tmp;
    Fp6_init(&tmp);
    
    Fp3_mul_omega(&tmp.a0,&A->a1);
    Fp3_set(&tmp.a1,&A->a0);
    
    Fp6_set(RES,&tmp);
    Fp6_clear(&tmp);
}
void Fp6_mul_tau(struct Fp6 *RES,struct Fp6 *A){
    struct Fp6 tmp;
    Fp6_init(&tmp);
    
    Fp3_neg(&tmp.a0,&A->a1);
    Fp3_set(&tmp.a1,&A->a0);
    
    Fp6_set(RES,&tmp);
    Fp6_clear(&tmp);
}
void Fp6_mul_ui(struct Fp6 *RES,struct Fp6 *A,unsigned long int B){
    struct Fp6 tmp;
    Fp6_init(&tmp);
    
    Fp3_mul_ui(&tmp.a0,&A->a0,B);
    Fp3_mul_ui(&tmp.a1,&A->a1,B);
    
    Fp6_set(RES,&tmp);
    Fp6_clear(&tmp);
}
void Fp6_mul_Fp(struct Fp6 *RES,struct Fp6 *A,struct Fp *B){
    struct Fp6 tmp;
    Fp6_init(&tmp);
    
    Fp3_mul_Fp(&tmp.a0,&A->a0,B);
    Fp3_mul_Fp(&tmp.a1,&A->a1,B);
    
    Fp6_set(RES,&tmp);
    
    Fp6_clear(&tmp);
}
void Fp6_invert(struct Fp6 *RES, struct Fp6 *A){
    struct Fp6 tmp;
    Fp6_init(&tmp);
    
    // tmp=A^(q^6)=(a0,-a1)
    Fp3_set(&tmp.a0,&A->a0);
    Fp3_neg(&tmp.a1,&A->a1);
    
    struct Fp3 c,a,b;
    Fp3_init(&c);
    Fp3_init(&a);
    Fp3_init(&b);
    
    Fp3_mul(&a,&A->a0,&A->a0); // a=a0^2
    Fp3_mul(&b,&A->a1,&A->a1); // b=a1^2
    Fp3_mul_omega(&b,&b); // b=a1^2*v
    Fp3_sub(&c,&a,&b); // c=a0^2-a1^2*v mod q
    
    Fp3_invert(&c,&c);
    
    // RES=A^{-1}=(c)^{-1}*A^(p^6) A which c is Fp6-element and tmp is a vector A Fp6
    Fp3_mul(&tmp.a0,&tmp.a0,&c);
    Fp3_mul(&tmp.a1,&tmp.a1,&c);
    
    Fp6_set(RES,&tmp);
    
    Fp3_clear(&c);
    Fp3_clear(&a);
    Fp3_clear(&b);
    Fp6_clear(&tmp);
}
void Fp6_div(struct Fp6 *RES,struct Fp6 *A,struct Fp6 *B){
    struct Fp6 tmp,t_RES;
    Fp6_init(&tmp);
    Fp6_init(&t_RES);
    
    Fp6_invert(&tmp,B);
    Fp6_mul(&t_RES,A,&tmp);
    
    Fp6_set(RES,&t_RES);
    
    Fp6_clear(&tmp);
    Fp6_clear(&t_RES);
}
void Fp6_pow(struct Fp6 *RES,struct Fp6 *A,mpz_t B){
    int i,length;
    length= (int)mpz_sizeinbase(B,2);
    char B_binary[length];
    mpz_get_str(B_binary,2,B);
    struct Fp6 tmp;
    Fp6_init(&tmp);
    Fp6_set(&tmp,A);
    for(i=1;B_binary[i]!='\0';i++){
        Fp6_mul(&tmp,&tmp,&tmp);
        if(B_binary[i]=='1'){
            Fp6_mul(&tmp,&tmp,A);
        }
    }
    Fp6_set(RES,&tmp);
    Fp6_clear(&tmp);
}
void Fp6_sqrt(struct Fp6 *RES,struct Fp6 *A){
    struct Fp6 n,y,x,b,t,tmp_Fp6;
    Fp6_init(&n);
    Fp6_init(&y);
    Fp6_init(&x);
    Fp6_init(&b);
    Fp6_init(&t);
    Fp6_init(&tmp_Fp6);
    Fp6_set(&n,A);
    
    mpz_t tmp_mpz,q,e,r,set_1,set_2;
    mpz_init(tmp_mpz);
    mpz_init(q);
    mpz_init(e);
    mpz_init(r);
    mpz_init(set_1);
    mpz_init(set_2);
    mpz_set_ui(set_1,1);
    mpz_set_ui(set_2,2);
    
    while(Fp6_legendre(&n)!=-1){
        Fp6_random(&n);
    }
    mpz_pow_ui(q,prime,6);
    mpz_sub_ui(q,q,1);
    mpz_set_ui(e,0);
    while(mpz_odd_p(q)==0){
        mpz_add_ui(e,e,1);
        mpz_div_ui(q,q,2);
    }
    Fp6_pow(&y,&n,q);
    
    mpz_set(r,e);
    
    mpz_sub_ui(tmp_mpz,q,1);
    mpz_div_ui(tmp_mpz,tmp_mpz,2);
    
    Fp6_pow(&x,A,tmp_mpz);
    Fp6_pow(&tmp_Fp6,&x,set_2);
    Fp6_mul(&b,&tmp_Fp6,A);
    Fp6_mul(&x,&x,A);
    
    int m;
    
    while(Fp6_cmp_mpz(&b,set_1)==1){
        m=-1;
        Fp6_set(&tmp_Fp6,&b);
        while(Fp6_cmp_mpz(&tmp_Fp6,set_1)==1){
            m++;
            mpz_pow_ui(tmp_mpz,set_2,m);
            Fp6_pow(&tmp_Fp6,&b,tmp_mpz);
        }
        mpz_sub_ui(tmp_mpz,r,m);
        mpz_sub_ui(tmp_mpz,tmp_mpz,1);
        mpz_powm(tmp_mpz,set_2,tmp_mpz,prime);
        // gmp_printf("%Zd,%Zd,%d\n",tmp_mpz,r,m);
        Fp6_pow(&t,&y,tmp_mpz);
        Fp6_pow(&y,&t,set_2);
        // gmp_printf("%Zd,%Zd,\n",y.a0.a0.a0,y.a0.a1.a0);
        mpz_set_ui(r,m);
        Fp6_mul(&x,&x,&t);
        Fp6_mul(&b,&b,&y);
    }
    
    Fp6_set(RES,&x);
    
    Fp6_clear(&n);
    Fp6_clear(&y);
    Fp6_clear(&x);
    Fp6_clear(&b);
    Fp6_clear(&t);
    Fp6_clear(&tmp_Fp6);
    mpz_clear(tmp_mpz);
    mpz_clear(q);
    mpz_clear(e);
    mpz_clear(r);
    mpz_clear(set_1);
}
int Fp6_legendre(struct Fp6 *a){
    mpz_t i,cmp;
    struct Fp6 tmp;
    Fp6_init(&tmp);
    mpz_init(i);
    mpz_init(cmp);
    mpz_set_ui(cmp,1);
    mpz_pow_ui(i,prime,6);
    mpz_sub_ui(i,i,1);
    mpz_tdiv_q_ui(i,i,2);
    Fp6_pow(&tmp,a,i);
    
    if((Fp6_cmp_mpz(&tmp,cmp))==0){
        Fp6_clear(&tmp);
        mpz_clear(i);
        mpz_clear(cmp);
        return 1;
    }else{
        Fp6_clear(&tmp);
        mpz_clear(i);
        mpz_clear(cmp);
        return -1;
    }
}
int Fp6_cmp(struct Fp6 *A,struct Fp6 *B){
    if(Fp3_cmp(&A->a0,&B->a0)==0 && Fp3_cmp(&A->a1,&B->a1)==0){
        return 0;
    }
    return 1;
}
int Fp6_cmp_mpz(struct Fp6 *A,mpz_t B){
    struct Fp6 tmp;
    Fp6_init(&tmp);
    if(Fp3_cmp_mpz(&A->a0,B)==0 && Fp3_cmp(&A->a1,&tmp.a1)==0){
        Fp6_clear(&tmp);
        return 0;
    }
    Fp6_clear(&tmp);
    return 1;
}
void Fp6_neg(struct Fp6 *RES,struct Fp6 *a){
    struct Fp6 tmp;
    Fp6_init(&tmp);
    Fp3_neg(&tmp.a0,&a->a0);
    Fp3_neg(&tmp.a1,&a->a1);
    Fp6_set(RES,&tmp);
    Fp6_clear(&tmp);
}

//-----------------------------------------------------------------------------------------

void Fp18_init(struct Fp18 *A){
    Fp6_init(&A->m0);
    Fp6_init(&A->m1);
    Fp6_init(&A->m2);
}
void Fp18_set(struct Fp18 *RES,struct Fp18 *A){
    Fp6_set(&RES->m0,&A->m0);
    Fp6_set(&RES->m1,&A->m1);
    Fp6_set(&RES->m2,&A->m2);
}
void Fp18_set_ui(struct Fp18 *A,signed long int B){
    Fp6_set_ui(&A->m0,B);
    Fp6_set_ui(&A->m1,B);
    Fp6_set_ui(&A->m2,B);
}
void Fp18_random(struct Fp18 *A){
    Fp6_random(&A->m0);
    Fp6_random(&A->m1);
    Fp6_random(&A->m2);
}
void Fp18_clear(struct Fp18 *A){
    Fp6_clear(&A->m0);
    Fp6_clear(&A->m1);
    Fp6_clear(&A->m2);
}
void Fp18_printf(struct Fp18 *A){
    gmp_printf("%Zd,%Zd,%Zd,%Zd,%Zd,%Zd\n",A->m0.a0.a0.x_0,A->m0.a0.a1.x_0,A->m0.a0.a2.x_0,A->m0.a1.a0.x_0,A->m0.a1.a1.x_0,A->m0.a1.a2.x_0);
    gmp_printf("%Zd,%Zd,%Zd,%Zd,%Zd,%Zd\n",A->m1.a0.a0.x_0,A->m1.a0.a1.x_0,A->m1.a0.a2.x_0,A->m1.a1.a0.x_0,A->m1.a1.a1.x_0,A->m1.a1.a2.x_0);
    gmp_printf("%Zd,%Zd,%Zd,%Zd,%Zd,%Zd\n\n",A->m2.a0.a0.x_0,A->m2.a0.a1.x_0,A->m2.a0.a2.x_0,A->m2.a1.a0.x_0,A->m2.a1.a1.x_0,A->m2.a1.a2.x_0);
}
void Fp18_add(struct Fp18 *RES,struct Fp18 *A,struct Fp18 *B){
    struct Fp18 tmp;
    Fp18_init(&tmp);
    
    Fp6_add(&tmp.m0,&A->m0,&B->m0);
    Fp6_add(&tmp.m1,&A->m1,&B->m1);
    Fp6_add(&tmp.m2,&A->m2,&B->m2);
    
    Fp18_set(RES,&tmp);
    
    Fp18_clear(&tmp);
}
void Fp18_add_ui(struct Fp18 *RES,struct Fp18 *A,unsigned long int B){
    struct Fp18 tmp;
    Fp18_init(&tmp);
    
    Fp6_add_ui(&tmp.m0,&A->m0,B);
    Fp6_add_ui(&tmp.m1,&A->m1,B);
    Fp6_add_ui(&tmp.m2,&A->m2,B);
    
    Fp18_set(RES,&tmp);
    
    Fp18_clear(&tmp);
}
void Fp18_sub(struct Fp18 *RES,struct Fp18 *A,struct Fp18 *B){
    struct Fp18 tmp;
    Fp18_init(&tmp);
    
    Fp6_sub(&tmp.m0,&A->m0,&B->m0);
    Fp6_sub(&tmp.m1,&A->m1,&B->m1);
    Fp6_sub(&tmp.m2,&A->m2,&B->m2);
    
    Fp18_set(RES,&tmp);
    
    Fp18_clear(&tmp);
}
void Fp18_mul(struct Fp18 *RES,struct Fp18 *A,struct Fp18 *B){
    //(a0,a1,a2)*(b0,b1,b2)=(x0y0+xi((a1+a2)(b1+b2)-a1b1-x2y2),xix2y2+(a0+a1)(b0+b1)-x0y0-a1b1,a1b1+(a0+a2)(b0+b2)-x0y0-x2y2)
    struct Fp6 tmp00,tmp11,tmp22,tmpx01,tmpx12,tmpx20,tmpy01,tmpy12,tmpy20,t0,t1,t2,tmp;
    struct Fp18 t_RES;
    Fp6_init(&tmp00);
    Fp6_init(&tmp11);
    Fp6_init(&tmp22);
    Fp6_init(&tmpx01);
    Fp6_init(&tmpx12);
    Fp6_init(&tmpx20);
    Fp6_init(&tmpy01);
    Fp6_init(&tmpy12);
    Fp6_init(&tmpy20);
    Fp6_init(&t0);
    Fp6_init(&t1);
    Fp6_init(&t2);
    Fp6_init(&tmp);
    Fp18_init(&t_RES);
    
    Fp6_mul(&tmp00,&A->m0,&B->m0);//a0*b0
    Fp6_mul(&tmp11,&A->m1,&B->m1);//a1*b1
    Fp6_mul(&tmp22,&A->m2,&B->m2);//a2*b2
    
    Fp6_add(&tmpx01,&A->m0,&A->m1);//a0+a1
    Fp6_add(&tmpx12,&A->m1,&A->m2);//a1+a2
    Fp6_add(&tmpx20,&A->m0,&A->m2);//a2+a0
    Fp6_add(&tmpy01,&B->m0,&B->m1);//b0+b1
    Fp6_add(&tmpy12,&B->m1,&B->m2);//b1+b2
    Fp6_add(&tmpy20,&B->m0,&B->m2);//b2+b0
    
    Fp6_mul(&t0,&tmpx01,&tmpy01);//(a0+a1)(b0+b1)
    Fp6_mul(&t1,&tmpx12,&tmpy12);//(a1+a2)(b1+b2)
    Fp6_mul(&t2,&tmpx20,&tmpy20);//(a2+a0)(b2+b0)
    
    Fp6_sub(&t1,&t1,&tmp11);
    Fp6_sub(&t1,&t1,&tmp22);//(a1+a2)(b1+b2)-a1b1-x2y2
    Fp6_mul_tau(&tmp,&t1);//TODO
    Fp6_add(&t_RES.m0,&tmp00,&tmp);
    
    Fp6_sub(&t0,&t0,&tmp00);
    Fp6_sub(&t0,&t0,&tmp11);
    Fp6_mul_tau(&tmp,&tmp22);
    Fp6_add(&t_RES.m1,&tmp,&t0);
    
    Fp6_sub(&t2,&t2,&tmp00);
    Fp6_sub(&t2,&t2,&tmp22);
    Fp6_add(&t_RES.m2,&tmp11,&t2);
    
    Fp18_set(RES,&t_RES);
    
    Fp6_clear(&tmp00);
    Fp6_clear(&tmp11);
    Fp6_clear(&tmp22);
    Fp6_clear(&tmpx01);
    Fp6_clear(&tmpx12);
    Fp6_clear(&tmpx20);
    Fp6_clear(&tmpy01);
    Fp6_clear(&tmpy12);
    Fp6_clear(&tmpy20);
    Fp6_clear(&t0);
    Fp6_clear(&t1);
    Fp6_clear(&t2);
    Fp6_clear(&tmp);
}
void Fp18_mul_ui(struct Fp18 *RES,struct Fp18 *A,unsigned long int B){
    struct Fp18 tmp;
    Fp18_init(&tmp);
    
    Fp6_mul_ui(&tmp.m0,&A->m0,B);
    Fp6_mul_ui(&tmp.m1,&A->m1,B);
    Fp6_mul_ui(&tmp.m2,&A->m2,B);
    
    Fp18_set(RES,&tmp);
    Fp18_clear(&tmp);
}
void Fp18_mul_Fp(struct Fp18 *RES,struct Fp18 *A,struct Fp *B){
    struct Fp18 tmp;
    Fp18_init(&tmp);
    
    Fp6_mul_Fp(&tmp.m0,&A->m0,B);
    Fp6_mul_Fp(&tmp.m1,&A->m1,B);
    Fp6_mul_Fp(&tmp.m2,&A->m2,B);
    
    Fp18_set(RES,&tmp);
    
    Fp18_clear(&tmp);
}
void Fp18_invert(struct Fp18 *RES, struct Fp18 *A){
    struct Fp18 t_RES;
    Fp18_init(&t_RES);
    
    struct Fp6 T0,T1,t0,t1,t2,t3;
    Fp6_init(&T0);
    Fp6_init(&T1);
    Fp6_init(&t0);
    Fp6_init(&t1);
    Fp6_init(&t2);
    Fp6_init(&t3);
    
    // An optimized version of Grewal's Algo. 3   (a,b,c)
    Fp6_mul(&T0,&A->m0,&A->m0);
    Fp6_mul_tau(&t0,&A->m1);//TODO
    
    Fp6_mul(&T1,&t0,&A->m2);
    Fp6_sub(&t1,&T0,&T1); // t1=(a^2-bci) mod q
    
    Fp6_mul(&T0,&A->m2,&A->m2);
    Fp6_mul_tau(&T0,&T0);
    Fp6_mul(&T1,&A->m0,&A->m1);
    Fp6_sub(&t2,&T0,&T1); // t2=(c^2i-ab) mod q
    
    Fp6_mul(&T0,&A->m1,&A->m1);
    Fp6_mul(&T1,&A->m0,&A->m2);
    Fp6_sub(&t3,&T0,&T1); // t3=(b^2-ac) mod q
    
    Fp6_mul(&T0,&t0,&t3);
    Fp6_mul(&T1,&A->m0,&t1);
    Fp6_add(&T0,&T0,&T1); // T0={bi(b^2-ac)+a(a^2-bci)} mod q
    
    Fp6_mul_tau(&t0,&A->m2);
    Fp6_mul(&T1,&t0,&t2);
    Fp6_add(&t0,&T0,&T1); // t0={ci(c^2i-ab)+{bi(b^2-ac)+a(a^2-bci)}} mod q .0
    
    Fp6_invert(&t0,&t0);
    
    Fp6_mul(&t_RES.m0,&t1,&t0);
    Fp6_mul(&t_RES.m1,&t2,&t0);
    Fp6_mul(&t_RES.m2,&t3,&t0);
    
    Fp18_set(RES,&t_RES);
    
    Fp18_clear(&t_RES);
    Fp6_clear(&T0);
    Fp6_clear(&T1);
    Fp6_clear(&t0);
    Fp6_clear(&t1);
    Fp6_clear(&t2);
    Fp6_clear(&t3);
}
void Fp18_div(struct Fp18 *RES,struct Fp18 *A,struct Fp18 *B){
    struct Fp18 tmp,t_RES;
    Fp18_init(&tmp);
    Fp18_init(&t_RES);
    
    Fp18_invert(&tmp,B);
    Fp18_mul(&t_RES,A,&tmp);
    
    Fp18_set(RES,&t_RES);
    
    Fp18_clear(&tmp);
    Fp18_clear(&t_RES);
}
void Fp18_pow(struct Fp18 *RES,struct Fp18 *A,mpz_t B){
    int i;
    int r;//bit数
    r= (int)mpz_sizeinbase(B,2);
    //printf("r= %d\n",r);
    
    struct Fp18 RESwer_tmp;
    Fp18_init(&RESwer_tmp);
    Fp18_set(&RESwer_tmp,A);
    
    struct Fp18 in_tmp;
    Fp18_init(&in_tmp);
    Fp18_set(&in_tmp,A);
    
    for(i=r-2;i>=0;i--){
        if(mpz_tstbit(B,i)==1){
            Fp18_mul(&RESwer_tmp,&RESwer_tmp,&RESwer_tmp);//a*2
            Fp18_mul(&RESwer_tmp,&RESwer_tmp,&in_tmp);//*a
        }else{
            Fp18_mul(&RESwer_tmp,&RESwer_tmp,&RESwer_tmp);//a*2
        }
    }
    
    Fp18_set(RES,&RESwer_tmp);
    
    Fp18_clear(&RESwer_tmp);
    Fp18_clear(&in_tmp);
}
void Fp18_sqrt(struct Fp18 *RES,struct Fp18 *A){
    struct Fp18 n,y,x,b,t,tmp_Fp18;
    Fp18_init(&n);
    Fp18_init(&y);
    Fp18_init(&x);
    Fp18_init(&b);
    Fp18_init(&t);
    Fp18_init(&tmp_Fp18);
    Fp18_set(&n,A);
    
    mpz_t tmp_mpz,q,e,r,set_1,set_2;
    mpz_init(tmp_mpz);
    mpz_init(q);
    mpz_init(e);
    mpz_init(r);
    mpz_init(set_1);
    mpz_init(set_2);
    mpz_set_ui(set_1,1);
    mpz_set_ui(set_2,2);
    
    while(Fp18_legendre(&n)!=-1){
        Fp18_random(&n);
        // printf("%d\n",Fp18_legendre(&n));
    }
    
    mpz_pow_ui(q,prime,18);
    mpz_sub_ui(q,q,1);
    mpz_set_ui(e,0);
    while(mpz_odd_p(q)==0){
        mpz_add_ui(e,e,1);
        mpz_div_ui(q,q,2);
    }
    Fp18_pow(&y,&n,q);
    mpz_set(r,e);
    mpz_sub_ui(tmp_mpz,q,1);
    mpz_div_ui(tmp_mpz,tmp_mpz,2);
    Fp18_pow(&x,A,tmp_mpz);
    Fp18_pow(&tmp_Fp18,&x,set_2);
    Fp18_mul(&b,&tmp_Fp18,A);
    Fp18_mul(&x,&x,A);
    int m;
    while(Fp18_cmp_mpz(&b,set_1)==1){
        m=-1;
        Fp18_set(&tmp_Fp18,&b);
        while(Fp18_cmp_mpz(&tmp_Fp18,set_1)==1){
            m++;
            mpz_pow_ui(tmp_mpz,set_2,m);
            Fp18_pow(&tmp_Fp18,&b,tmp_mpz);
        }
        mpz_sub_ui(tmp_mpz,r,m);
        mpz_sub_ui(tmp_mpz,tmp_mpz,1);
        mpz_powm(tmp_mpz,set_2,tmp_mpz,prime);
        Fp18_pow(&t,&y,tmp_mpz);
        Fp18_pow(&y,&t,set_2);
        mpz_set_ui(r,m);
        Fp18_mul(&x,&x,&t);
        Fp18_mul(&b,&b,&y);
    }
    
    Fp18_set(RES,&x);
    
    Fp18_clear(&n);
    Fp18_clear(&y);
    Fp18_clear(&x);
    Fp18_clear(&b);
    Fp18_clear(&t);
    Fp18_clear(&tmp_Fp18);
    mpz_clear(tmp_mpz);
    mpz_clear(q);
    mpz_clear(e);
    mpz_clear(r);
    mpz_clear(set_1);
}
int Fp18_cmp(struct Fp18 *A,struct Fp18 *B){
    if(Fp6_cmp(&A->m0,&B->m0)==0 && Fp6_cmp(&A->m1,&B->m1)==0 && Fp6_cmp(&A->m2,&B->m2)==0){
        return 0;
    }
    return 1;
}
int Fp18_cmp_mpz(struct Fp18 *A,mpz_t B){
    struct Fp18 tmp;
    Fp18_init(&tmp);
    if(Fp6_cmp_mpz(&A->m0,B)==0 && Fp6_cmp(&A->m1,&tmp.m1)==0 && Fp6_cmp(&A->m2,&tmp.m2)==0){
        Fp18_clear(&tmp);
        return 0;
    }
    Fp18_clear(&tmp);
    return 1;
}
int Fp18_legendre(struct Fp18 *a){
    mpz_t i,cmp;
    struct Fp18 tmp;
    mpz_init(i);
    mpz_init(cmp);
    Fp18_init(&tmp);
    mpz_set_ui(cmp,1);
    mpz_pow_ui(i,prime,18);
    mpz_sub_ui(i,i,1);
    mpz_tdiv_q_ui(i,i,2);
    Fp18_pow(&tmp,a,i);
    
    if((Fp18_cmp_mpz(&tmp,cmp))==0){
        Fp18_clear(&tmp);
        mpz_clear(i);
        mpz_clear(cmp);
        return 1;
    }else{
        Fp18_clear(&tmp);
        mpz_clear(i);
        mpz_clear(cmp);
        return -1;
    }
}
void Fp18_neg(struct Fp18 *RES,struct Fp18 *a){
    struct Fp18 tmp;
    Fp18_init(&tmp);
    Fp6_neg(&tmp.m0,&a->m0);
    Fp6_neg(&tmp.m1,&a->m1);
    Fp6_neg(&tmp.m2,&a->m2);
    Fp18_set(RES,&tmp);
    Fp18_clear(&tmp);
}

//-----------------------------------------------------------------------------------------

void EFp_init(struct EFp *A){
    Fp_init(&A->x);
    Fp_init(&A->y);
    A->isInfinity=FALSE;
}
void EFp_set(struct EFp *A,struct EFp *B){
    Fp_set(&A->x,&B->x);
    Fp_set(&A->y,&B->y);
    A->isInfinity=B->isInfinity;
}
void EFp_set_infity(struct EFp *A){
    Fp_set_ui(&A->x,0);
    Fp_set_ui(&A->y,0);
    A->isInfinity=TRUE;
}
void EFp_clear(struct EFp *A){
    Fp_clear(&A->x);
    Fp_clear(&A->y);
}
void EFp_printf(struct EFp *A){
    gmp_printf("(%Zd,%Zd)\n",A->x.x_0,A->y.x_0);
}
void EFp_SCM(struct EFp *RES, struct EFp *P,mpz_t j){
    int i,length;
    length= (int)mpz_sizeinbase(j,2);
    // int eca=0,ecd=0;
    char r_binary[length];
    mpz_get_str(r_binary,2,j);
    struct EFp Q,R;
    EFp_init(&Q);
    EFp_set(&Q,P);
    EFp_init(&R);
    for(i=1;r_binary[i]!='\0';i++){
        EFp_ECD(&Q,&Q);
        // ecd++;
        if(r_binary[i]=='1'){
            EFp_ECA(&Q,&Q,P);
            // eca++;
        }
    }
    EFp_set(RES,&Q);
    // printf("%d,%d\n",eca,ecd);
    EFp_clear(&Q);
    EFp_clear(&R);
    return;
}
void EFp_ECD(struct EFp *RES, struct EFp *P){
    if(P->isInfinity==TRUE){
        EFp_set(RES,P);
        return;
    }
    if(mpz_sgn(P->y.x_0)==0){//P.y==0
        EFp_set_infity(RES);
        return;
    }
    
    struct Fp x,y,lambda,tmp;
    struct EFp t_RES;
    Fp_init(&x);
    Fp_init(&lambda);
    Fp_init(&tmp);
    Fp_init(&y);
    EFp_init(&t_RES);
    
    Fp_mul(&x,&P->x,&P->x);
    Fp_add(&tmp,&x,&x);
    Fp_add(&x,&tmp,&x);//3x^2
    Fp_add(&y,&P->y,&P->y);//2y
    
    Fp_div(&lambda,&x,&y);
    Fp_mul(&tmp,&lambda,&lambda);
    Fp_add(&x,&P->x,&P->x);
    Fp_sub(&x,&tmp,&x);
    Fp_sub(&tmp,&P->x,&x);
    
    Fp_set(&t_RES.x,&x);
    
    Fp_mul(&tmp,&tmp,&lambda);
    Fp_sub(&t_RES.y,&tmp,&P->y);
    
    EFp_set(RES,&t_RES);
    
    Fp_clear(&x);
    Fp_clear(&lambda);
    Fp_clear(&y);
    Fp_clear(&tmp);
    EFp_clear(&t_RES);
}
void EFp_ECA(struct EFp *RES, struct EFp *P1, struct EFp *P2){
    if(P2->isInfinity==TRUE){//if P2==inf
        EFp_set(RES,P1);
        return;
    }
    else if(P1->isInfinity==TRUE){//if P1==inf
        EFp_set(RES,P2);
        return;
    }
    else if(Fp_cmp(&P1->x,&P2->x)==0&&Fp_cmp(&P1->y,&P2->y)==1){ //P1.x==P2.x&&P1.y!=P2.y
        EFp_set_infity(RES);
        return;
    }
    else if(EFp_cmp(P1,P2)==0){ // P=Q
        EFp_ECD(RES,P1);
        return;
    }
    
    struct Fp x,y,lambda,tmp;
    struct EFp t_RES;
    
    Fp_init(&x);
    Fp_init(&y);
    Fp_init(&lambda);
    Fp_init(&tmp);
    EFp_init(&t_RES);
    
    Fp_sub(&x,&P2->x,&P1->x);
    Fp_sub(&y,&P2->y,&P1->y);
    Fp_div(&lambda,&y,&x);
    Fp_mul(&tmp,&lambda,&lambda);
    Fp_add(&x,&P1->x,&P2->x);
    Fp_sub(&x,&tmp,&x);
    Fp_sub(&tmp,&P1->x,&x);
    Fp_set(&t_RES.x,&x);
    Fp_mul(&tmp,&tmp,&lambda);
    Fp_sub(&t_RES.y,&tmp,&P1->y);
    
    EFp_set(RES,&t_RES);
    
    Fp_clear(&x);
    Fp_clear(&y);
    Fp_clear(&lambda);
    Fp_clear(&tmp);
    EFp_clear(&t_RES);
}
int EFp_cmp(struct EFp *A,struct EFp *B){
    if(Fp_cmp(&A->x,&B->x)==0 && Fp_cmp(&A->y,&B->y)==0){
        return 0;
    }
    return 1;
}
void EFp_random_set(struct EFp *RES){
    struct Fp a,x;
    Fp_init(&a);
    Fp_init(&x);
    
    struct EFp P,Q;
    EFp_init(&P);
    EFp_init(&Q);
    
    mpz_t r_div_2;
    mpz_init(r_div_2);
    mpz_div_ui(r_div_2,r_order,2);
    // gmp_printf("%Zd\n",r_div_2);
    do{
        do{
            Fp_random(&x);
            Fp_mul(&a,&x,&x);
            Fp_mul(&a,&a,&x);
            mpz_add(a.x_0,a.x_0,b);
        }while(mpz_legendre(a.x_0,prime)!=1);
        Q.isInfinity=0;
        Fp_sqrt(&P.y,&a);
        Fp_set(&P.x,&x);
        
        EFp_SCM(&Q,&P,r_div_2);
        // EFp_SCM(&P,&P,p2);
        // printf("%d\n",Q.infity);
    }while(Q.isInfinity==TRUE);
    EFp_set(RES,&P);
    
    
    Fp_clear(&a);
    Fp_clear(&x);
    EFp_clear(&P);
    // // int legendle;
    // struct EFp P;
    // EFp_init(&P);
    
    // struct Fp x,a;
    // Fp_init(&a);
    
    // Fp_init(&x);
    // mpz_t set_3;
    // mpz_init(set_3);
    // mpz_set_ui(set_3,3);
    
    // do{
    // 	Fp_random(&x);
    // 	Fp_pow(&a,&x,set_3);
    // 	mpz_add(a.a0,a.a0,b);
    // }while(mpz_legendre(a.a0,p)!=1);
    
    // Fp_sqrt(&P.y,&a);
    // Fp_set(&P.x,&x);
    // EFp_set(RES,&P);
    
    // EFp_clear(&P);
    // Fp_clear(&a);
    // Fp_clear(&x);
    // mpz_clear(set_3);
}

//-----------------------------------------------------------------------------------------

void EFp3_init(struct EFp3 *A){
    Fp3_init(&A->x);
    Fp3_init(&A->y);
    A->isInfinity=FALSE;
}
void EFp3_set(struct EFp3 *A,struct EFp3 *B){
    Fp3_set(&A->x,&B->x);
    Fp3_set(&A->y,&B->y);
    A->isInfinity=B->isInfinity;
}
void EFp3_set_infity(struct EFp3 *A){
    Fp3_set_ui(&A->x,0);
    Fp3_set_ui(&A->y,0);
    A->isInfinity=TRUE;
}
void EFp3_clear(struct EFp3 *A){
    Fp3_clear(&A->x);
    Fp3_clear(&A->y);
}
void EFp3_printf(struct EFp3 *A){
    gmp_printf("(%Zd,%Zd,%Zd,%Zd,%Zd,%Zd)\n",A->x.a0.x_0,A->x.a1.x_0,A->x.a2.x_0,A->y.a0.x_0,A->y.a1.x_0,A->y.a2.x_0);
}
void EFp3_ECD(struct EFp3 *RES, struct EFp3 *P){
    if(P->isInfinity==TRUE){
        EFp3_set(RES,P);
        return;
    }
    mpz_t cmp;
    mpz_init(cmp);
    mpz_set_ui(cmp,0);
    if(Fp3_cmp_mpz(&P->y,cmp)==0){//P.y==0
        EFp3_set_infity(RES);
        return;
    }
    
    struct Fp3 x,y,lambda,tmp;
    struct EFp3 t_RES;
    Fp3_init(&x);
    Fp3_init(&lambda);
    Fp3_init(&tmp);
    Fp3_init(&y);
    EFp3_init(&t_RES);
    
    Fp3_mul(&x,&P->x,&P->x);
    Fp3_add(&tmp,&x,&x);
    Fp3_add(&x,&tmp,&x);
    Fp3_add(&y,&P->y,&P->y);
    Fp3_div(&lambda,&x,&y);
    Fp3_mul(&tmp,&lambda,&lambda);
    Fp3_add(&x,&P->x,&P->x);
    Fp3_sub(&x,&tmp,&x);
    Fp3_sub(&tmp,&P->x,&x);
    Fp3_set(&t_RES.x,&x);
    Fp3_mul(&tmp,&tmp,&lambda);
    Fp3_sub(&t_RES.y,&tmp,&P->y);
    
    EFp3_set(RES,&t_RES);
    
    Fp3_clear(&x);
    Fp3_clear(&lambda);
    Fp3_clear(&y);
    Fp3_clear(&tmp);
    EFp3_clear(&t_RES);
}
void EFp3_ECA(struct EFp3 *RES, struct EFp3 *P1, struct EFp3 *P2){
    if(P2->isInfinity==TRUE){//if P2==inf
        EFp3_set(RES,P1);
        return;
    }
    else if(P1->isInfinity==TRUE){//if P1==inf
        EFp3_set(RES,P2);
        return;
    }
    else if(Fp3_cmp(&P1->x,&P2->x)==0&&Fp3_cmp(&P1->y,&P2->y)==1){ //P1.x==P2.x&&P1.y!=P2.y
        EFp3_set_infity(RES);
        return;
    }
    else if(EFp3_cmp(P1,P2)==0){ // P=Q
        EFp3_ECD(RES,P1);
        return;
    }
    
    struct Fp3 x,y,lambda,tmp;
    struct EFp3 t_RES;
    
    Fp3_init(&x);
    Fp3_init(&y);
    Fp3_init(&lambda);
    Fp3_init(&tmp);
    EFp3_init(&t_RES);
    
    Fp3_sub(&x,&P2->x,&P1->x);
    Fp3_sub(&y,&P2->y,&P1->y);
    Fp3_div(&lambda,&y,&x);
    Fp3_mul(&tmp,&lambda,&lambda);
    Fp3_add(&x,&P1->x,&P2->x);
    Fp3_sub(&x,&tmp,&x);
    Fp3_sub(&tmp,&P1->x,&x);
    Fp3_set(&t_RES.x,&x);
    Fp3_mul(&tmp,&tmp,&lambda);
    Fp3_sub(&t_RES.y,&tmp,&P1->y);
    
    EFp3_set(RES,&t_RES);
    
    Fp3_clear(&x);
    Fp3_clear(&y);
    Fp3_clear(&lambda);
    Fp3_clear(&tmp);
    EFp3_clear(&t_RES);
}
void EFp3_SCM(struct EFp3 *RES, struct EFp3 *P, mpz_t j){
    int i,length;
    length= (int)mpz_sizeinbase(j,2);
    char r_binary[length];
    // printf("%d\n",length);
    mpz_get_str(r_binary,2,j);
    struct EFp3 Q,R;
    EFp3_init(&Q);
    EFp3_set(&Q,P);
    EFp3_init(&R);
    for(i=1;r_binary[i]!='\0';i++){
        EFp3_ECD(&Q,&Q);
        if(r_binary[i]=='1'){
            EFp3_ECA(&Q,&Q,P);
        }
    }
    EFp3_set(RES,&Q);
    
    EFp3_clear(&Q);
    EFp3_clear(&R);
    return;
}
int EFp3_cmp(struct EFp3 *A,struct EFp3 *B){
    if(Fp3_cmp(&A->x,&B->x)==0 && Fp3_cmp(&A->y,&B->y)==0){
        return 0;
    }
    return 1;
}
void EFp3_set_EFp(struct EFp3 *A,struct EFp *B){
    Fp3_set_ui(&A->x,0);
    Fp3_set_ui(&A->y,0);
    
    Fp_set(&A->x.a0,&B->x);
    Fp_set(&A->y.a0,&B->y);
    A->isInfinity=B->isInfinity;
}
void EFp3_random_set(struct EFp3 *RES){
    struct Fp3 a,x;
    Fp3_init(&a);
    Fp3_init(&x);
    
    struct EFp3 P,Q;
    EFp3_init(&P);
    EFp3_init(&Q);
    
    mpz_t p3,t3,r3,tmp;
    mpz_init(p3);
    mpz_init(t3);
    mpz_init(r3);
    mpz_init(tmp);
    
    mpz_mul(p3,prime,prime);
    mpz_mul(p3,p3,prime);//p3=p^3
    
    mpz_mul(t3,t_trace,t_trace);
    mpz_mul(t3,t3,t_trace);//t3=t^3
    
    mpz_mul(tmp,t_trace,prime);
    mpz_mul_ui(tmp,tmp,3);//tmp=3tp
    
    mpz_sub(r3,p3,t3);//r3=p3-t3
    mpz_add(r3,r3,tmp);//r3=p3-t3+3tp
    mpz_add_ui(r3,r3,1);//r3=p3-t3+3tp+1
    
    mpz_tdiv_q(r3,r3,r_order);
    mpz_tdiv_q(r3,r3,r_order);
    do{
        Fp3_random(&x);
        Fp3_mul(&a,&x,&x);
        Fp3_mul(&a,&a,&x);
        mpz_add(a.a0.x_0,a.a0.x_0,b);
    }while(Fp3_legendre(&a)!=1);
    P.isInfinity=FALSE;
    Fp3_sqrt(&P.y,&a);
    Fp3_set(&P.x,&x);
    
    EFp3_SCM(&P,&P,r3);
    EFp3_set(RES,&P);
    
    
    Fp3_clear(&a);
    Fp3_clear(&x);
    EFp3_clear(&P);
    mpz_clear(p3);
}
void EFp3_neg(struct EFp3 *RES, struct EFp3 *A){
    struct EFp3 tmp;
    EFp3_init(&tmp);
    Fp3_neg(&tmp.y,&A->y);
    Fp3_set(&tmp.x,&A->x);
    
    EFp3_set(RES,&tmp);
    EFp3_clear(&tmp);
}

//-----------------------------------------------------------------------------------------

void EFp6_init(struct EFp6 *A){
    Fp6_init(&A->x);
    Fp6_init(&A->y);
    A->isInfinity=FALSE;
}
void EFp6_set(struct EFp6 *A,struct EFp6 *B){
    Fp6_set(&A->x,&B->x);
    Fp6_set(&A->y,&B->y);
    A->isInfinity=B->isInfinity;
}
void EFp6_set_infity(struct EFp6 *A){
    Fp6_set_ui(&A->x,0);
    Fp6_set_ui(&A->y,0);
    A->isInfinity=TRUE;
}
void EFp6_clear(struct EFp6 *A){
    Fp6_clear(&A->x);
    Fp6_clear(&A->y);
}
void EFp6_printf(struct EFp6 *A){
    gmp_printf("%Zd,%Zd,%Zd,%Zd,%Zd,%Zd\n",A->x.a0.a0.x_0,A->x.a0.a1.x_0,A->x.a0.a2.x_0,A->x.a1.a0.x_0,A->x.a1.a1.x_0,A->x.a1.a2.x_0);
    gmp_printf("%Zd,%Zd,%Zd,%Zd,%Zd,%Zd\n",A->y.a0.a0.x_0,A->y.a0.a1.x_0,A->y.a0.a2.x_0,A->y.a1.a0.x_0,A->y.a1.a1.x_0,A->y.a1.a2.x_0);
}
void EFp6_ECD(struct EFp6 *RES, struct EFp6 *P){
    if(P->isInfinity==TRUE){
        EFp6_set(RES,P);
        return;
    }
    mpz_t cmp;
    mpz_init(cmp);
    mpz_set_ui(cmp,0);
    if(Fp6_cmp_mpz(&P->y,cmp)==0){//P.y==0
        EFp6_set_infity(RES);
        return;
    }
    
    struct Fp6 x,y,lambda,tmp;
    struct EFp6 t_RES;
    Fp6_init(&x);
    Fp6_init(&lambda);
    Fp6_init(&tmp);
    Fp6_init(&y);
    EFp6_init(&t_RES);
    
    Fp6_mul(&x,&P->x,&P->x);
    Fp6_add(&tmp,&x,&x);
    Fp6_add(&x,&tmp,&x);
    Fp6_add(&y,&P->y,&P->y);
    Fp6_div(&lambda,&x,&y);
    Fp6_mul(&tmp,&lambda,&lambda);
    Fp6_add(&x,&P->x,&P->x);
    Fp6_sub(&x,&tmp,&x);
    Fp6_sub(&tmp,&P->x,&x);
    Fp6_set(&t_RES.x,&x);
    Fp6_mul(&tmp,&tmp,&lambda);
    Fp6_sub(&t_RES.y,&tmp,&P->y);
    
    EFp6_set(RES,&t_RES);
    
    Fp6_clear(&x);
    Fp6_clear(&lambda);
    Fp6_clear(&y);
    Fp6_clear(&tmp);
    EFp6_clear(&t_RES);
}
void EFp6_ECA(struct EFp6 *RES, struct EFp6 *P1, struct EFp6 *P2){
    if(P2->isInfinity==TRUE){//if P2==inf
        EFp6_set(RES,P1);
        return;
    }
    else if(P1->isInfinity==TRUE){//if P1==inf
        EFp6_set(RES,P2);
        return;
    }
    else if(Fp6_cmp(&P1->x,&P2->x)==0&&Fp6_cmp(&P1->y,&P2->y)==1){ //P1.x==P2.x&&P1.y!=P2.y
        EFp6_set_infity(RES);
        return;
    }
    else if(EFp6_cmp(P1,P2)==0){ // P=Q
        EFp6_ECD(RES,P1);
        return;
    }
    
    struct Fp6 x,y,lambda,tmp;
    struct EFp6 t_RES;
    
    Fp6_init(&x);
    Fp6_init(&y);
    Fp6_init(&lambda);
    Fp6_init(&tmp);
    EFp6_init(&t_RES);
    
    Fp6_sub(&x,&P2->x,&P1->x);
    Fp6_sub(&y,&P2->y,&P1->y);
    Fp6_div(&lambda,&y,&x);
    Fp6_mul(&tmp,&lambda,&lambda);
    Fp6_add(&x,&P1->x,&P2->x);
    Fp6_sub(&x,&tmp,&x);
    Fp6_sub(&tmp,&P1->x,&x);
    Fp6_set(&t_RES.x,&x);
    Fp6_mul(&tmp,&tmp,&lambda);
    Fp6_sub(&t_RES.y,&tmp,&P1->y);
    
    EFp6_set(RES,&t_RES);
    
    Fp6_clear(&x);
    Fp6_clear(&y);
    Fp6_clear(&lambda);
    Fp6_clear(&tmp);
    EFp6_clear(&t_RES);
}
void EFp6_SCM(struct EFp6 *RES,struct EFp6 *P,mpz_t j){
    int i,length;
    length= (int)mpz_sizeinbase(j,2);
    char j_binary[length];
    mpz_get_str(j_binary,2,j);
    struct EFp6 Q,R;
    EFp6_init(&Q);
    EFp6_set(&Q,P);
    EFp6_init(&R);
    for(i=1;j_binary[i]!='\0';i++){
        EFp6_ECD(&Q,&Q);
        if(j_binary[i]=='1'){
            EFp6_ECA(&Q,&Q,P);
        }
    }
    EFp6_set(RES,&Q);
    
    EFp6_clear(&Q);
    EFp6_clear(&R);
    return;
}
int EFp6_cmp(struct EFp6 *A,struct EFp6 *B){
    if(Fp6_cmp(&A->x,&B->x)==0 && Fp6_cmp(&A->y,&B->y)==0){
        return 0;
    }
    return 1;
}
void EFp6_random_set(struct EFp6 *RES){
    struct EFp6 P;
    EFp6_init(&P);
    
    struct Fp6 x,a;
    Fp6_init(&a);
    Fp6_init(&x);
    
    //t12=a^12+b^12={(t^3-3pt)^2-2p^3}^2-2p^6
    mpz_t tmp1,tmp2,p_pow;
    mpz_t r6,t6;
    mpz_init(tmp1);
    mpz_init(tmp2);
    mpz_init(p_pow);
    mpz_init(r6);
    mpz_init(t6);
    
    mpz_pow_ui(tmp1,t_trace,3);
    mpz_mul(p_pow,prime,t_trace);
    mpz_mul_ui(p_pow,p_pow,3);
    mpz_sub(tmp1,tmp1,p_pow);
    mpz_mul(tmp1,tmp1,tmp1);
    
    mpz_pow_ui(p_pow,prime,3);
    mpz_mul_ui(tmp2,p_pow,2);
    mpz_sub(t6,tmp1,tmp2);
    // mpz_pow_ui(tmp1,tmp1,2);
    
    mpz_pow_ui(p_pow,p_pow,2);
    // mpz_mul_ui(tmp2,p_pow,2);
    // mpz_sub(t6,tmp1,tmp2);
    
    // mpz_pow_ui(p_pow,p_pow,2);
    mpz_add_ui(tmp1,p_pow,1);
    mpz_sub(r6,tmp1,t6);
    
    do{
        Fp6_random(&x);
        Fp6_mul(&a,&x,&x);
        Fp6_mul(&a,&a,&x);
        mpz_add(a.a0.a0.x_0,a.a0.a0.x_0,b);
    }while(Fp6_legendre(&a)!=1);
    Fp6_sqrt(&P.y,&a);
    Fp6_set(&P.x,&x);
    
    mpz_t r6_div_r2;
    mpz_init(r6_div_r2);
    mpz_div(r6_div_r2,r6,r_order);
    mpz_div(r6_div_r2,r6_div_r2,r_order);
    
    EFp6_SCM(RES,&P,r6_div_r2);
    
    EFp6_clear(&P);
    Fp6_clear(&a);
    Fp6_clear(&x);
    mpz_clear(tmp1);
    mpz_clear(tmp2);
    mpz_clear(p_pow);
    mpz_clear(r6);
    mpz_clear(t6);
    mpz_clear(r6_div_r2);
}

//-----------------------------------------------------------------------------------------

void EFp18_init(struct EFp18 *A){
    Fp18_init(&A->x);
    Fp18_init(&A->y);
    A->isInfinity=FALSE;
}
void EFp18_set(struct EFp18 *A,struct EFp18 *B){
    Fp18_set(&A->x,&B->x);
    Fp18_set(&A->y,&B->y);
    A->isInfinity=B->isInfinity;
}
void EFp18_set_infity(struct EFp18 *A){
    Fp18_set_ui(&A->x,0);
    Fp18_set_ui(&A->y,0);
    A->isInfinity=TRUE;
}
void EFp18_clear(struct EFp18 *A){
    Fp18_clear(&A->x);
    Fp18_clear(&A->y);
}
void EFp18_printf(struct EFp18 *A){
    gmp_printf("(%Zd,%Zd,%Zd,%Zd,%Zd,%Zd\n",A->x.m0.a0.a0.x_0,A->x.m0.a0.a1.x_0,A->x.m0.a0.a2.x_0,A->x.m0.a1.a0.x_0,A->x.m0.a1.a1.x_0,A->x.m0.a1.a2.x_0);
    gmp_printf("%Zd,%Zd,%Zd,%Zd,%Zd,%Zd\n",A->x.m1.a0.a0.x_0,A->x.m1.a0.a1.x_0,A->x.m1.a0.a2.x_0,A->x.m1.a1.a0.x_0,A->x.m1.a1.a1.x_0,A->x.m1.a1.a2.x_0);
    gmp_printf("%Zd,%Zd,%Zd,%Zd,%Zd,%Zd)\n",A->x.m2.a0.a0.x_0,A->x.m2.a0.a1.x_0,A->x.m2.a0.a2.x_0,A->x.m2.a1.a0.x_0,A->x.m2.a1.a1.x_0,A->x.m2.a1.a2.x_0);
    
    gmp_printf("(%Zd,%Zd,%Zd,%Zd,%Zd,%Zd\n",A->y.m0.a0.a0.x_0,A->y.m0.a0.a1.x_0,A->y.m0.a0.a2.x_0,A->y.m0.a1.a0.x_0,A->y.m0.a1.a1.x_0,A->y.m0.a1.a2.x_0);
    gmp_printf("%Zd,%Zd,%Zd,%Zd,%Zd,%Zd\n",A->y.m1.a0.a0.x_0,A->y.m1.a0.a1.x_0,A->y.m1.a0.a2.x_0,A->y.m1.a1.a0.x_0,A->y.m1.a1.a1.x_0,A->y.m1.a1.a2.x_0);
    gmp_printf("%Zd,%Zd,%Zd,%Zd,%Zd,%Zd)\n\n",A->y.m2.a0.a0.x_0,A->y.m2.a0.a1.x_0,A->y.m2.a0.a2.x_0,A->y.m2.a1.a0.x_0,A->y.m2.a1.a1.x_0,A->y.m2.a1.a2.x_0);
}
void EFp18_ECD(struct EFp18 *RES, struct EFp18 *P){
    if(P->isInfinity==TRUE){
        EFp18_set(RES,P);
        return;
    }
    mpz_t cmp;
    mpz_init(cmp);
    mpz_set_ui(cmp,0);
    if(Fp18_cmp_mpz(&P->y,cmp)==0){//P.y==0
        EFp18_set_infity(RES);
        return;
    }
    
    struct Fp18 x,y,lambda,tmp;
    struct EFp18 t_RES;
    Fp18_init(&x);
    Fp18_init(&lambda);
    Fp18_init(&tmp);
    Fp18_init(&y);
    EFp18_init(&t_RES);
    
    Fp18_mul(&x,&P->x,&P->x);
    Fp18_add(&tmp,&x,&x);
    Fp18_add(&x,&tmp,&x);
    Fp18_add(&y,&P->y,&P->y);
    Fp18_div(&lambda,&x,&y);
    Fp18_mul(&tmp,&lambda,&lambda);
    Fp18_add(&x,&P->x,&P->x);
    Fp18_sub(&x,&tmp,&x);
    Fp18_sub(&tmp,&P->x,&x);
    Fp18_set(&t_RES.x,&x);
    Fp18_mul(&tmp,&tmp,&lambda);
    Fp18_sub(&t_RES.y,&tmp,&P->y);
    
    EFp18_set(RES,&t_RES);
    
    Fp18_clear(&x);
    Fp18_clear(&lambda);
    Fp18_clear(&y);
    Fp18_clear(&tmp);
    EFp18_clear(&t_RES);
}
void EFp18_ECA(struct EFp18 *RES, struct EFp18 *P1, struct EFp18 *P2){
    if(P2->isInfinity==TRUE){//if P2==inf
        EFp18_set(RES,P1);
        return;
    }
    else if(P1->isInfinity==TRUE){//if P1==inf
        EFp18_set(RES,P2);
        return;
    }
    else if(Fp18_cmp(&P1->x,&P2->x)==0&&Fp18_cmp(&P1->y,&P2->y)==1){ //P1.x==P2.x&&P1.y!=P2.y
        EFp18_set_infity(RES);
        return;
    }
    else if(EFp18_cmp(P1,P2)==0){ // P=Q
        EFp18_ECD(RES,P1);
        return;
    }
    
    struct Fp18 x,y,lambda,tmp;
    struct EFp18 t_RES;
    
    Fp18_init(&x);
    Fp18_init(&y);
    Fp18_init(&lambda);
    Fp18_init(&tmp);
    EFp18_init(&t_RES);
    
    Fp18_sub(&x,&P2->x,&P1->x);
    Fp18_sub(&y,&P2->y,&P1->y);
    Fp18_div(&lambda,&y,&x);
    Fp18_mul(&tmp,&lambda,&lambda);
    Fp18_add(&x,&P1->x,&P2->x);
    Fp18_sub(&x,&tmp,&x);
    Fp18_sub(&tmp,&P1->x,&x);
    Fp18_set(&t_RES.x,&x);
    Fp18_mul(&tmp,&tmp,&lambda);
    Fp18_sub(&t_RES.y,&tmp,&P1->y);
    
    EFp18_set(RES,&t_RES);
    
    Fp18_clear(&x);
    Fp18_clear(&y);
    Fp18_clear(&lambda);
    Fp18_clear(&tmp);
    EFp18_clear(&t_RES);
}
void EFp18_SCM(struct EFp18 *RES,struct EFp18 *P,mpz_t j){
    int i,length;
    length= (int)mpz_sizeinbase(j,2);
    char j_binary[length];
    mpz_get_str(j_binary,2,j);
    struct EFp18 Q,R;
    EFp18_init(&Q);
    EFp18_set(&Q,P);
    EFp18_init(&R);
    for(i=1;j_binary[i]!='\0';i++){
        EFp18_ECD(&Q,&Q);
        if(j_binary[i]=='1'){
            EFp18_ECA(&Q,&Q,P);
        }
    }
    EFp18_set(RES,&Q);
    
    EFp18_clear(&Q);
    EFp18_clear(&R);
    return;
}
int EFp18_cmp(struct EFp18 *A,struct EFp18 *B){
    if(Fp18_cmp(&A->x,&B->x)==0 && Fp18_cmp(&A->y,&B->y)==0){
        return 0;
    }
    return 1;
}
void EFp18_random_set(struct EFp18 *RES){
    struct EFp18 P;
    EFp18_init(&P);
    
    struct Fp18 x,a;
    Fp18_init(&a);
    Fp18_init(&x);
    
    //t18=a^18+b^18={(t^3-3pt)^3-3p^3(t^3-3pt)}^2-2p^9
    mpz_t tmp1,tmp2,tmp3,t_RES,t18,r18;
    mpz_init(tmp1);
    mpz_init(tmp2);
    mpz_init(tmp3);
    mpz_init(t_RES);
    mpz_init(t18);
    mpz_init(r18);
    
    mpz_mul(tmp1,prime,t_trace);
    mpz_mul_ui(tmp1,tmp1,3);
    
    mpz_mul(tmp2,t_trace,t_trace);
    mpz_mul(tmp2,tmp2,t_trace);
    
    mpz_sub(tmp1,tmp2,tmp1);//tmp1=t^3-3pt
    
    mpz_mul(t_RES,tmp1,tmp1);
    mpz_mul(t_RES,t_RES,tmp1);//t_RES=(t^3-3pt)^3
    
    mpz_mul(tmp2,prime,prime);
    mpz_mul(tmp2,tmp2,prime);//tmp2=p^3
    
    mpz_mul(tmp3,tmp1,tmp2);
    mpz_mul_ui(tmp3,tmp3,3);//tmp3=3p^3(t^3-3pt)
    
    mpz_sub(t_RES,t_RES,tmp3);//t_RES=(t^3-3pt)^3-3p^3(t^3-3pt)
    mpz_mul(t_RES,t_RES,t_RES);//t_RES=t_RES^2
    
    mpz_pow_ui(tmp2,tmp2,3);//tmp2=p^9
    mpz_add(tmp3,tmp2,tmp2);//tmp3=2*tmp2
    
    mpz_sub(t18,t_RES,tmp3);//t18=t_RES-tmp3
    
    mpz_mul(tmp3,tmp2,tmp2);//tmp3=p^18
    
    mpz_add_ui(tmp3,tmp3,1);
    mpz_sub(r18,tmp3,t18);
    mpz_div(r18,r18,r_order);
    mpz_div(r18,r18,r_order);
    
    do{
        Fp18_random(&x);
        Fp18_mul(&a,&x,&x);
        Fp18_mul(&a,&a,&x);
        mpz_add(a.m0.a0.a0.x_0,a.m0.a0.a0.x_0,b);
    }while(Fp18_legendre(&a)!=1);
    Fp18_sqrt(&P.y,&a);
    Fp18_set(&P.x,&x);
    
    EFp18_SCM(RES,&P,r18);
    
    EFp18_clear(&P);
    Fp18_clear(&a);
    Fp18_clear(&x);
    
    mpz_clear(tmp1);
    mpz_clear(tmp2);
    mpz_clear(t18);
}
void EFp18_set_EFp(struct EFp18 *A,struct EFp *B){
    Fp18_set_ui(&A->x,0);
    Fp18_set_ui(&A->y,0);
    
    Fp_set(&A->x.m0.a0.a0,&B->x);
    Fp_set(&A->y.m0.a0.a0,&B->y);
    A->isInfinity=B->isInfinity;
}
void EFp18_frobenius_map(struct EFp18 *RES,struct EFp18 *A){
    struct EFp18 tmp;
    EFp18_init(&tmp);
    
    Fp18_pow(&tmp.x,&A->x,prime);
    Fp18_pow(&tmp.y,&A->y,prime);
    
    EFp18_set(RES,&tmp);
    
    EFp18_clear(&tmp);
}
void EFp18_random_set_for_Ate(struct EFp18 *RES){
    struct EFp18 P,P_frobenius,tmp_EFp18;
    EFp18_init(&P);
    EFp18_init(&P_frobenius);
    EFp18_init(&tmp_EFp18);
    
    EFp18_random_set(&P);
    
    EFp18_frobenius_map(&P_frobenius,&P);
    Fp18_neg(&tmp_EFp18.y,&P.y);
    Fp18_set(&tmp_EFp18.x,&P.x);
    
    EFp18_ECA(&tmp_EFp18,&tmp_EFp18,&P_frobenius);
    
    EFp18_set(RES,&tmp_EFp18);
    
    EFp18_clear(&P);
    EFp18_clear(&P_frobenius);
    EFp18_clear(&tmp_EFp18);
}

//-----------------------------------------------------------------------------------------

void EFp_set_EC_parameter(void){
    //set p,r
    mpz_t p_tmp,r_tmp,t_tmp;
    mpz_t xpow2,xpow3,xpow4,xpow5,xpow6,xpow7,xpow8;
    mpz_t tmp1,tmp2;
    
    mpz_init(p_tmp);
    mpz_init(r_tmp);
    mpz_init(t_tmp);
    
    mpz_init(xpow2);
    mpz_init(xpow3);
    mpz_init(xpow4);
    mpz_init(xpow5);
    mpz_init(xpow6);
    mpz_init(xpow7);
    mpz_init(xpow8);
    
    mpz_init(tmp1);
    mpz_init(tmp2);
    
    mpz_mul(xpow2,X,X);
    mpz_mul(xpow3,xpow2,X);
    mpz_mul(xpow4,xpow2,xpow2);
    mpz_mul(xpow5,xpow4,X);
    mpz_mul(xpow6,xpow3,xpow3);
    mpz_mul(xpow7,xpow6,X);
    mpz_mul(xpow8,xpow4,xpow4);
    
    //t=1/7(x^4+16x+7)
    mpz_mul_ui(tmp1,X,16);
    mpz_add_ui(tmp2,xpow4,7);
    mpz_add(t_tmp,tmp1,tmp2);
    
    mpz_div_ui(t_trace,t_tmp,7);
    
    //r=x^6+37x^3+343
    mpz_mul_ui(tmp1,xpow3,37);
    mpz_add_ui(tmp2,xpow6,343);
    mpz_add(r_tmp,tmp1,tmp2);
    
    mpz_set(r_order,r_tmp);
    
    //p=1/21(x^8+5x^7+7x^6+37x^5+188x^4+259x^3+343x^2+1763x+2401)
    mpz_mul_ui(tmp1,xpow7,5);
    mpz_add(p_tmp,tmp1,xpow8);
    mpz_mul_ui(tmp1,xpow6,7);
    mpz_add(p_tmp,tmp1,p_tmp);
    mpz_mul_ui(tmp1,xpow5,37);
    mpz_add(p_tmp,tmp1,p_tmp);
    mpz_mul_ui(tmp1,xpow4,188);
    mpz_add(p_tmp,tmp1,p_tmp);
    mpz_mul_ui(tmp1,xpow3,259);
    mpz_add(p_tmp,tmp1,p_tmp);
    mpz_mul_ui(tmp1,xpow2,343);
    mpz_add(p_tmp,tmp1,p_tmp);
    mpz_mul_ui(tmp1,X,1763);
    mpz_add(p_tmp,tmp1,p_tmp);
    mpz_add_ui(p_tmp,p_tmp,2401);
    
    mpz_div_ui(prime,p_tmp,21);
    
    mpz_add_ui(r_order_EFp,prime,1);
    mpz_sub(r_order_EFp,r_order_EFp,t_trace);
    
    if(mpz_probab_prime_p(prime,25)==0){
        gmp_printf("p:%Zd\n",prime);
        printf("not  prime number!\n");
        exit(0);
    }
    get_C1_C1bar();
    
    struct EFp P,RES;
    int legendle;
    struct Fp a,x;
    mpz_t tmp_b;
    Fp_init(&a);
    EFp_init(&P);
    EFp_init(&RES);
    Fp_init(&x);
    mpz_init(tmp_b);
    mpz_set_ui(tmp_b,0);
    
    for(;;){
        mpz_add_ui(tmp_b,tmp_b,1);
        Fp_set_ui(&x,1);
        legendle=0;
        while(legendle!=1){
            mpz_powm_ui(a.x_0,x.x_0,3,prime);
            mpz_add(a.x_0,a.x_0,tmp_b);
            if((legendle=mpz_legendre(a.x_0,prime))==1){
                Fp_sqrt(&P.y,&a);
                Fp_set(&P.x,&x);
                EFp_SCM(&RES,&P,r_order_EFp);
                if(RES.isInfinity==TRUE){
                    mpz_set(b,tmp_b);
                    mpz_clear(tmp_b);
                    Fp_clear(&a);
                    Fp_clear(&x);
                    EFp_clear(&P);
                    EFp_clear(&RES);
                    return;
                }
            }
            Fp_add_ui(&x,&x,1);
        }
    }
    return;
}

//-----------------------------------------------------------------------------------------

int getParameters(int bit){
    
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
    X_int=X_int/8; //bit count?
    printf("X_int %d\n",X_int);
    mpz_setbit(X,X_int);
    gmp_printf("X Set bit %Zd = %d\n",X,(int)mpz_sizeinbase(X,2));
    mpz_div_ui(X2,X,4);
    gmp_printf("X2div %Zd = bit %d\n",X2,(int)mpz_sizeinbase(X2,2));
    mpz_add(X,X2,X);
    //    mpz_add(X,X2,X);
    mpz_div_ui(X,X,2);
    gmp_printf("X = %Zd,HW %ld Bit size %d bit\n",X,mpz_popcount(X),(int)mpz_sizeinbase(X,2));
    
    
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
                    if ((int)mpz_sizeinbase(p_tmp,2) <341)
                    {
                        printf("Got it %lld\n",count192p);
                        continue;
                    }
                    
                    
                    
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
