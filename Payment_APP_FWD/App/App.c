#define CRT_NO_WARNINGS
#include "App.h"
#include<stdio.h>
ST_transaction_t User;
int z;
void appStart(void)
{ while (1)
	{	
		while (1)
		{
			fflush(stdin);
			if ( getCardHolderName(&User.cardHolderData ) == 0)
				break;
		}
		while (1)
		{
			fflush(stdin);
			if (getCardExpiryDate(&User.cardHolderData) == 0)
				break;
		}
		while (1)
		{
			fflush(stdin);
			if (getCardPAN(&User.cardHolderData) == 0)
				break;
		}

		while (1)
		{
			if ((getTransactionDate(&User.terminalData)) == 0)
				break;
		}
		if (isCardExpired(&User.cardHolderData, &User.terminalData) != 0)
		{
			continue;
		}
		while (1)
		{
			if ((getTransactionAmount(&User.terminalData)) == 0)
				break;
		}


		while (1)
		{
			if (setMaxAmount(&User.terminalData) == 0)
				break;
		}



		if (isBelowMaxAmount(&User.terminalData) != 0)
		{
			continue;
		}

		if (recieveTransactionData(&User) == INTERNAL_SERVER_ERROR)
		{
			printf("SAVING FAILED\n");
			fflush(stdin);
		}
		else
		{
			
			printf("SAVED\n");
			fflush(stdin);

		}


		fflush(stdin);
	}

}