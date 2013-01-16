/*******************************************************************************
 * DANIEL'S ALGORITHM IMPLEMENTAIONS
 *
 *  /\  |  _   _  ._ o _|_ |_  ._ _   _ 
 * /--\ | (_| (_) |  |  |_ | | | | | _> 
 *         _|                      
 *
 * PRIME TEST FUNCTION
 *
 * http://en.wikipedia.org/wiki/Primality_test
 *
 ******************************************************************************/
#ifndef __PRIME_H__
#define __PRIME_H__
/**
 * check whether a given number is a prime number.
 */
inline int is_prime(unsigned int n)
{
	unsigned int p;
	if (!(n & 1) || n < 2 ) return n == 2;
 
	/* comparing p*p <= n can overflow */
	for (p = 3; p <= n/p; p += 2)
		if (!(n % p)) return 0;
	return 1;
}

#endif //
