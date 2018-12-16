//
//  main.c
//  3.61
//
//  Created by Nikki Woo on 10/15/18.
//  Copyright © 2018 Nikki Woo. All rights reserved.
//

#include <stdio.h>


long cread_alt (long *xp) {
    
    long one = -1;
    long *res = &one;
    long res2 = (long)xp - 8;
    if (xp) { res = (long*)res2; }
    return *res;
}


