#include <stdio.h>
void findMinCoins(int amount)
{
    int coins[] = {25, 10, 5, 1}; 
    int numCoins[] = {0, 0, 0, 0}; 
    int i;
    for (i = 0; i < 4; i++)
	{
        if (amount >= coins[i])
		{
            numCoins[i] = amount / coins[i];
            amount = amount % coins[i];
        }
    }

    for (i = 0; i < 4; i++)
	{
        if (numCoins[i] > 0)
		{
            printf("%d ¸ö %d ·ÖÓ²±Ò\n", numCoins[i], coins[i]);
        }
    }
}
int main()
{
    int amount;
    scanf("%d",&amount);
    while(amount!=0)
    {
    	findMinCoins(amount);
    	scanf("%d",&amount);
	}
    return 0;
}

