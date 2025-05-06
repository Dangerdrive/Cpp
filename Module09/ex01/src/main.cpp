#include "RPN.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " \"RPN expression\"" << std::endl;
        return 1;
    }

    RPN calculator;
    try {
        int result = calculator.evaluate(argv[1]);
        std::cout << result << std::endl;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}

Merge insertion. A pleasant generalization of the method above has been
discovered by Lester Ford, Jr. and Selmer Johnson. Since it involves some aspects
of merging and some aspects of insertion, we shall call it merge insertion. For
example, consider the problem of sorting 21 elements. We start by comparing
the ten pairs K 1 : K 2, K3: K4, ... , K19: K2o; then we sort the ten larger elements
of the pairs, using merge insertion. As a result we obtain the configuration
bi b2 b3 b4 b5 b5 b7 bs bg b10 bn
analogous to (5)· The next step is to insert b3 among {b1, a1, a2}, then b2 among
the other elements less than a2; we arrive at the configuration
C3 C4 C5
>• 7 7 7 7 7 7 7. >• >• >• (8)
b4 b5 b5 b7 bs bg bio bn
Let us call the upper-line elements the main chain. We can insert b5 into its
proper place in the main chain, using three comparisons (first comparing it to
c4, then c2 or c6 , etc.); then b4 can be moved into the main chain in three more
steps, leading to
di d2 d3 d4 d5 d5 d7 ds dg dio a5 a7 as ag aio
• >• >• >• >• >• >• >• >• >• 7 7 7 7 7 •
(g)
b5 b7 bs bg bio bn
The next step is crucial; is it clear what to do? We insert bu (not b7 ) into the
main chain, using only four comparisons. Then b10 , b9 , b8 , b7 , b6 (in this order)
can also be inserted into their proper places in the main chain, using at most
four comparisons each.
A careful count of the comparisons involved here shows that the 21 elements
have been sorted in at most 10+ S(lO) + 2 + 2 + 3 + 3 +4+ 4+4 +4+ 4+4 = 66 