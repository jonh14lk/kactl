# Teorema de Lucas

sejam m e n numeros inteiros nao negativos e p um numero primo
desenvolver n e m na base p
ou seja:
m = m[k]*p^(k) + m[k - 1]*p^(k - 1) + ... + m[0]*p^(0)
n = n[k]*p^(k) + n[k - 1]*p^(k - 1) + ... + n[0]*p^(0)

entao:
ncr(m, n) mod p = produtorio de (ncr(m[i], n[i]) mod p)

dai pra generalizar pro mod 2 eh deboas, pq se tiver um bit setado em n[i] que nao ta setado em m[i], entao miou, vai dar zero

# Manhattan and Chebyshev distances equivalences

It is well known that given points (x, y) and you need to calculate the Manhattan distances between them, instead of using: 
|x1-x2|+|y1-y2| 

you can first convert all points (x, y) into (x+y, x-y) (rotate 45 degrees) and the distances will become max(|x1-x2|, |y1-y2|) (also known as Chebyshev distance).

# Chicken McNugget Theorem

For any two coprime numbers (n > 0, m > 0), the greatest integer that cannot be written in the form:

an + bm, (a >= 0, b >= 0)

is (n \* m) - n - m

## Consequence of the theorem

That there are exactly ((n - 1) \* (m - 1)) / 2 positive integers which cannot be expressed in the form an + bm, (a >= 0, b >= 0)

## Generalization

If n and m are not coprime, so all numbers that are not multiples of gcd(n, m) cannot be expressed in the form an + bm, (a >= 0, b >= 0)

in addition, you can consider n = (n / gcd(n, m)) and m = (m / gcd(n, m)), to find how many multiples of gcd(n, m) cannot be expressed, or to find the greatest multiple of gcd(n, m) that cannot be expressed

## Considering a > 0, b > 0

Considering (n > 0, m > 0), n and m are coprime:

let y = ((n \* m) + min(n, m)) - 1

The number of positive integers which cannot be expressed increases by (y / n)

The number of positive integers which cannot be expressed increases by (y / m)

you must not count the multiples of (n \* m) more than once, just decrease number of positive integers which cannot be expressed by (y / (n \* m))

# Binomial Theorem

### Theorem

$$
(x + y)^n = \sum_{k = 0}^{n} {n \choose k} x^{n - k}y^{k}
$$

in addition, we have:

$$
(x - y)^n = \sum_{k = 0}^{n} (-1)^k {n \choose k} x^{n - k}y^{k}
$$

$$
(1 + x)^n = \sum_{k = 0}^{n} {n \choose k} x^{k}