//
//  main.c
//  2.63
//
//  Created by Nikki Woo on 10/1/18.
//  Copyright © 2018 Nikki Woo. All rights reserved.
//

// should be logical shift
unsigned long srl (unsigned long x, int k) {
    /* Perform shift arithmetically */
    unsigned long xsra = (long) x >> k;
    int wo = 8*sizeof(unsigned long);
    // test if k = 0, test evaluates to 1 if k is zero and 0 otherwise
    int test = (k == 0);
    // make it so that, if k = 0, then w = w - 1;
    int w = wo - test;
    // mask will evaluate to 000.. if k is zero
    unsigned long mask = ((1 << (w - k)) - 1);
    return (unsigned long) (mask & xsra);
    
    
    
}


// should be arithmetic shift
long sra (long x, int k) {
    /* Perform shift logically */
    long xsrl = (unsigned long) x >> k;
    int wo = 8*sizeof(long);
    long firstbit = ((1<<(wo-1))&x);
    // sigbit returns 1 the first bit is 1
    long sigbit = (firstbit == 0);
    sigbit--;
    // test if k = 0, if it is then w = w - 1
    int test = (k == 0);
    int w = wo - test;
    return (sigbit << (w - k) | xsrl);
}



