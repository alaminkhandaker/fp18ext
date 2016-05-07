//
//  testprime.c
//  Fp18_Arith
//
//  Created by Khandaker Md. Al-Amin on 4/29/16.
//  Copyright © 2016 Khandaker Md. Al-Amin. All rights reserved.
//

#include "testprime.h"
#include <assert.h>

int test()
{
    char inputStr[1025];
    mpz_t n;
    int flag;
    
    printf ("Enter your number: ");
    scanf("%1024s" , inputStr);
    mpz_init(n);
    mpz_set_ui(n,0);
    
    /* 2. Parse the input string as a base 10 number */
    flag = mpz_set_str(n,inputStr, 10);
    assert (flag == 0); /* If flag is not 0 then the operation failed */
    
    /* Print n */
    printf ("n = ");
    mpz_out_str(stdout,10,n);
    printf ("\n");
    
    return 0;
}