//
//  main.c
//  2.73
//
//  Created by Nikki Woo on 10/4/18.
//  Copyright © 2018 Nikki Woo. All rights reserved.
//

//
#include <limits.h>
//#include <stdio.h>

int saturating_add(int x, int y) {
    // find the size of x
    int w = (sizeof(int) << 3);
    //find sum and first bit of sum
    int sum = x + y;
    int sumfront = sum >> (w - 1);
    // first, determine if there is overflow by checking the first bit of x and y
    // we assign the first bit of x to be xfront
    int xfront = x >> (w - 1);
    // we assign the first bit of y to by yfront
    int yfront = y >> (w - 1);
    // we know that if yfront == xfront there is a possibility of overflow but not if yfront != xfront
    // if yfront == xfront, there is overflow if xfront != sumfront where sumfront is first bit of the sum
    // let us assign an integer named overflow '1' if there is overflow and '0' if none
    int overflow = (xfront == yfront) && (xfront != sumfront);
    // makes it so that, if overflow is 1, overflow is now 000... and if overflow was 0, overflow is now 111...
    // so, if there was overflow, overflow is 000... and if there was no overflow, overflow is now 111...
    overflow--;
    // now, we have checked to see if there is overflow, from here we produce an answer such that
    // if overflow is 111... , we return x + y and zero otherwise
    int nooverflowsum = overflow & (x+y);
    // now, we check for if there is positive overflow in which case we return Tmax, or 0111....
    // so, if overflow is 000... and yfront or xfront == 0, then we return Tmax
    int posoverflow = (~overflow) & ~((xfront == 0) - 1) & INT_MAX;
    // finally, we check for if there is negative overflow in which case we return Tmin, or 100...
    // so, if overflow is 000... and yfront or xfront != 0, then we return Tmin
    int negoverflow = (~overflow) & ((xfront == 0) - 1) & INT_MIN;
    return (nooverflowsum + posoverflow + negoverflow);
}


