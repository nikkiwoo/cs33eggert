Nikki Woo 204927670
Eggert
CS33 Disc 1D
18 Oct 2018

In cread_alt, we must find a way to evaluate the then and else statement in a way that does not dereference xp in case it is a nullptr. Thus, we utilize the fact that the nullptr as a long itself is zero and thus subtract 8 from the address of xp. We work with the address of xp and not the actual contents of it until we test it and can be sure that it is not the nullptr.
