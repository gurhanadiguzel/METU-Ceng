#include "Queue.h"
#include <iostream>

/*
Write a program that finds prime numbers using the Sieve of Erastosthenes, an algorithm devised by a Greek mathematician
of the same name who lived in the third century BC. The algorithm finds all prime numbers up to some maximum value n,
as described by the following pseudocode:

Create a queue of numbers to process.
Fill the queue with the integers 2 through n inclusive
Create an empty result queue to store primes.
Repeat the following steps:
Obtain the next prime p by removing the first value from the queue of numbers.
     Put p into the result queue of primes.
Loop through the queue of numbers, eliminating all numbers that are divisible by p.
while (p is less than the square root of n).

All remaining values in the numbers queue are prime, so transfer them to the result primes queue.

EXAMPLE:
Following are the prime numbers smaller than or equal to 30
2 3 5 7 11 13 17 19 23 29
*/

Queue <int> SieveOfEratosthenes(int n) {
    /* TODO */

    Queue<int> numbers;
    for (int i = 2; i <= n; i++) {
        // Fill the queue with the integers 2 through n inclusive.
        numbers.enqueue(i);
    }

    Queue<int> primes; // Create an empty result queue to store primes.
    int p = 2;
    do {
        Queue<int> temp;
        p = numbers.peek(); // Obtain the next prime p by removing the first value from the queue of numbers.
        numbers.dequeue();

        primes.enqueue(p); // Put p into the result queue of primes.

        while (!numbers.isEmpty()) {
            // Loop through the queue of numbers, eliminating all numbers that are divisible by p.
            int i = numbers.peek();
            if (i % p != 0) {
                temp.enqueue(i);
            }
            numbers.dequeue();
        }
        numbers = temp;
    } while(p*p <= n);

    // All remaining values in the numbers queue are prime, so transfer them to the result primes queue.
    while (!numbers.isEmpty()) {
        p = numbers.peek();
        primes.enqueue(p);
        numbers.dequeue();
    }

    return primes;
}
