#define R 7
#define S 5
#define T 8

long A[R][S][T];

long
ele (long i, long j, long k)
{
  return A[R - i][1 - j][k - 1];
}

/*
 1
 We know that a long has a length of 8 bytes so we factor that into the equation/
 First, we consider Equation 3.1 in the book.
 The book states that for array D declared as T D[R][C], array element D[i][j] is
 at the memory address
 
                          &D[i][j] = x + L(C * i + j)
 
 where x is the base address and L is the size of the data type T.
 
 Similarly, we can extend this to the three dimensional case for our given problem.
 Given long A[R][S][T], we know that the array is RxSxT with L = 8 since a long is 8
 bytes. Let's say that we want to find the address of A[i][j][k].
 Thinking logically, we can extend the two-dimensional equation. Let us take a
 look at the equation and fill in what we know (neglecting the base address for now).
 
                            8(C * i + j)
 
 We see that the C*i term takes into account the fact that, for every increase in i,
 there are C 8-byte "stacks" while, within that substack, each j only has an 8-byte
 "stack".
 
 Thus, we take this reasoning and use similar reasoning for the three-dimensional case
 
                        8(T * ((S * i) + j) + k)
 
 Therefore, we have
 
            &A[i][j][k] = a + 8(T * ((S * i) + j) + k)
 
 where a is the base address.

 
 2
 In order to derive the constants from the extended equation and from ele.s, let
 us first look at the .s code
 we know i = %rdi, j = %rsi, and k = %rdx
 ele:
 movl    $7, %eax               //this adds 7 to the bottom half of rax
                                // %rax = 7
 subq    %rdi, %rax             // this subtracts rdi from rax
                                // %rax = 7 - %rdi
 leaq    (%rax,%rax,4), %rax    // this replaces rax with 5 times itself
                                // %rax = 35 - 5*%rdi
 subq    %rsi, %rax             // this subtracts %rsi from %rax
                                // %rax = 35 - 5*%rdi - %rsi
 leaq    7(%rdx,%rax,8), %rax   // %rax = %rdx + 8*(35 - 5*%rdi - %rsi) + 7
 movq    A(,%rax,8), %rax       // %rax = *(A + 8*(%rdx + 8*(35 - 5*%rdi - %rsi) + 7))
 ret
 
 We compare the return address given by the .s code (substituting in the parameters)
 
                A + 8(k + 8*(35 - 5*i - j) + 7)
 
 with the return address given by the formula (substituing in what the function is
 actually returning, i.e. i' = R - i, j' = 1 - j, and k' = k - 1)
 
                a + 8(T * ((S * (R - i)) + 1 - j) + k - 1)
 
 Simplifying and setting the first equal to the second,
 
 k + 280 - 40i - 8j + 7 = STR - STi + T - Tj + k - 1
 
 We see
 
 -Tj = -8j
 T = 8
 
 -40i = -STi = -8Si
 5i = Si
 S = 5
 
 280 + 7 = STR + t - 1
 287 = 40R + 8 - 1
 280 = 40R
 R = 7
 
 So, we find that S = 8, T = 5, and R = 7.
 
 
 
*/
