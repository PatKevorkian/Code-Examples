#include <math.h>
#include <stdio.h>
#define BITS_PER_LONG   32l
#define BITS_PER_LONG_1 31l

long get_bit(long i, long *sieve)
{
    long b = i % BITS_PER_LONG;
    long c = i / BITS_PER_LONG;
    return (sieve[c] >> (BITS_PER_LONG_1 - b)) & 1;
}

void set_bit(long i, long v, long *sieve)
{
    long b = i % BITS_PER_LONG;
    long c = i / BITS_PER_LONG;
    long mask = 1 << (BITS_PER_LONG_1 - b);
    if (v == 1)
        sieve[c] |= mask;
    else
        sieve[c] &= ~mask;
}

void Sieve(long n, long *sieve)
{
    long c, i, inc;
    set_bit(0l, 0l, sieve);
    set_bit(1l, 0l, sieve);
    set_bit(2l, 1l, sieve);
    for (i = 3; i <= n; i++)
        set_bit(i, i & 1, sieve);
    c = 3;
    do
    {
        i = c * c;
        inc = c + c;
        while (i <= n)
        {
            set_bit(i, 0l, sieve);
            i += inc;
            
        }
        c += 2;
        while (!get_bit(c, sieve)) c++;
    } while (c * c <= n);
}

long factor(long n, long *sieve)
/* factor using trial division */
{
    int found = 0;
    long p = 0, s = sqrt(n);
    while (!found && p <= s)
    {
        while (!get_bit(p, sieve)) p++;
        found = n % p == 0;
        if (!found) p++;
    }
    return p;
    
}

long Extended_Euclidean(long b, long n)
{
    long b0 = b, n0 = n, t = 1, t0 = 0, temp, q, r;
    q = n0 / b0;
    r = n0 - q * b0;
    while (r > 0)
    {
        temp = t0 - q * t;
        if (temp >= 0) temp = temp % n;
        else temp = n - (- temp % n);
        t0 = t;
        t = temp;
        n0 = b0;
        b0 = r;
        q = n0 / b0;
        r = n0 - q * b0;
    }
    if (b0 != 1) return 0;
    else return t % n;
}

long exp_mod(long x, long b, long n)
/* returns x ^ b mod n */
{
    long a = 1l, s = x;
    while (b != 0)
    {
        if (b & 1l) a = (a * s) % n;
        b >>= 1;
        if (b != 0) s = (s * s) % n;
    }
    return a;
    
}

int main(void)
{
    char abc[27] = "abcdefghijklmnopqrstuvwxyz";
    long b = 4913l; //which is the same as e
    long n = 31313l;
    long c[139] =
    {
        6340l,    8309l,    14010l,   8936l,    27358l,   25023l,  16481l,   25809l,
        23614l,   7135l,    24996l,   30590l,   27570l,   26486l,  30388l,   9395l,
        27584l,   14999l,   4517l,    12146l,   29421l,   26439l,  1606l,    17881l,
        25774l,   7647l,    23901l,   7372l,    25774l,   18436l,  12056l,   13547l,
        7908l,    8635l,    2149l,    1908l,    22076l,   7372l,   8686l,    1304l,
        4082l,    11803l,   5314l,    107l,     7359l,    22470l,  7372l,    22827l,
        15698l,   30317l,   4685l,    14696l,   30388l,   8671l,   29956l,   15705l,
        1417l,    26905l,   25809l,   28347l,   26277l,   7897l,   20240l,   21519l,
        12437l,   1108l,    27106l,   18743l,   24144l,   10685l,  25234l,   30155l,
        23005l,   8267l,    9917l,    7994l,    9694l,    2149l,   10042l,   27705l,
        15930l,   29748l,   8635l,    23645l,   11738l,   24591l,  20240l,   27212l,
        27486l,   9741l,    2149l,    29329l,   2149l,    5501l,   14015l,   30155l,
        18154l,   22319l,   27705l,   20321l,   23254l,   13624l,  3249l,    5443l,
        2149l,    16975l,   16087l,   14600l,   27705l,   19386l,  7325l,    26277l,
        19554l,   23614l,   7553l,    4734l,    8091l,    23973l,  14015l,   107l,
        3183l,    17347l,   25234l,   4595l,    21498l,   6360l,   19837l,   8463l,
        6000l,    31280l,   29413l,   2066l,    369l,     23204l,  8425l,    7792l,
        25973l,   4477l,    30989l
   };
    
    long  i, sieve[10000], m, p, q;
    long a, phi, t;
    Sieve(n, sieve);
    
    
        p = factor(n, sieve);
        q = n / p;
    
        printf("p = %5ld    q = %5ld  n = %5ld\n", p, q, n);
    
        phi = (p - 1) * (q - 1);
        a = Extended_Euclidean(b, phi);
    
        printf("a = %5ld  b,e = %5ld\n\n", a, b);
        printf("%5ld * %5ld mod %5ld = %1ld\n", a, b, phi, (a * b) % phi);
        printf("\n-------Plaintext------- \n\n");
    
        for (i = 0; i < 139; i++)
        {
            m = exp_mod(c[i], a, n);
            
            if (c[i] != exp_mod(m, b, n))
                printf("*error* in RSA\n");
            
            t = m / 676l;
            m = m % 676l;
            
            printf("%c", abc[t]);
            
            t = m / 26l;
            m = m % 26l;
            
            printf("%c", abc[t]);
            printf("%c", abc[m]);
            
            if ((i + 1) % 8 == 0)
                printf("\n");
        }
        printf("\n\n-----------------------\n\n");
    
    return 0; }
