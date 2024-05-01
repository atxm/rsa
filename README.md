# RSA Decryption Tool
## A program for CS 111, UC Riverside's upper-division Discrete Structures course
A small-scale RSA decryption program developed in C++ for the CS 111 course at the University of California, Riverside.

The program takes the public key $(\textcolor{lime}{e}, \textcolor{orange}{n})$ as well as the number of encrypted characters-mapped-to-numbers $\textcolor{violet}{m}$ as user input.

Two arrays of size $\textcolor{violet}{m}$ are declared prior to the deposit of the encrypted characters (having been created by the sender taking some number $\textcolor{teal}{M}$ with a character value and encrypting it to a value $\textcolor{red}{C} = \textcolor{teal}{M}^{\textcolor{lime}{e}} \text{ rem } \textcolor{orange}{n}$).

A function `findpq()` is called to return a pair of prime numbers $(\textcolor{magenta}{p}, \textcolor{pink}{q}) \in \mathbb{P}$ from the semiprime $\textcolor{orange}{n}$ by checking all values $\textcolor{magenta}{p} < \sqrt{\textcolor{orange}{n}}$ before discovering $\textcolor{magenta}{p} \ni \textcolor{magenta}{p} \mid \textcolor{orange}{n}$. A $\textcolor{pink}{q}$ is then found by ensuring that $\textcolor{pink}{q} = \frac{\textcolor{orange}{n}}{\textcolor{magenta}{p}}$ and the function returns the pair of numbers if $\textcolor{magenta}{p}, \textcolor{pink}{q} \in \mathbb{P}$ (`isPrime()`).

If no valid public key is found (i.e., $\textcolor{orange}{n} \in \mathbb{P}$ or $\textcolor{magenta}{p} \geq \textcolor{pink}{q}$), the `panic()` function is called. This outputs an error message, and returns an error code of `-1`, and kills the program.

The totient $\textcolor{turquoise}{\phi(}\textcolor{orange}{n}\textcolor{turquoise}{)} = (\textcolor{magenta}{p} - 1)(\textcolor{pink}{q} - 1)$, a value relatively prime to the public key's $\textcolor{lime}{e}$, is calculated and used in a call to `gcd()`, an implementation of the extended Euclidean algorithm that returns a pointer to dynamically allocated memory. Our $\textcolor{yellow}{d} = \textcolor{lime}{e}^{-1} \pmod{\textcolor{turquoise}{\phi(}\textcolor{orange}{n}\textcolor{turquoise}{)}}$, the most important value in decrypting our encrypted $\textcolor{red}{C}$ is assigned this value. If $\gcd(\textcolor{lime}{e},\textcolor{turquoise}{\phi(}\textcolor{orange}{n}\textcolor{turquoise}{)}) \neq 1$, the `panic()` function is called.

$\textcolor{teal}{M} = \textcolor{red}{C}^{\textcolor{yellow}{d}} \text{ rem } \textcolor{orange}{n}$ is then calculated by way of the `deCrypt()` function and `charize()` maps  the numbers back to their original Latin character values.