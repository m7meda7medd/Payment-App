#define _CRT_SECURE_NO_WARNINGS
#include "Terminal.h"
#include<string.h>
#include<stdio.h>


EN_terminalError_t getTransactionDate(ST_terminalData_t *termData)
{
	printf("Transaction Date as DD/MM/YYYY is :");
	fflush(stdin);
	gets(termData->transactionDate);// get the date
	fflush(stdin);
	if ((termData->transactionDate[2] != '/') || (termData->transactionDate[5] != '/') || (termData->transactionDate[0] > '3') || (termData->transactionDate[3] > '1') || (strlen(termData->transactionDate) < 10) || (termData->transactionDate[0] > '3') || (termData->transactionDate[3] > '1') || (strlen(termData->transactionDate) < 10) || ((termData->transactionDate) == NULL)) //check it
	{
		printf("WRONG DATE\n");
		return WRONG_DATE;
	}
	else
	{
		printf("OK\n");
		return Terminal_OK;

	}
}

EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData)
{
	if ((termData->transactionDate[8]) > (cardData->cardExpirationDate[3]))
	{
		printf("Expired Card\n");
		return EXPIRED_CARD;
	}
	else if ((termData->transactionDate[8]) == (cardData->cardExpirationDate[3]))
	{
		if ((termData->transactionDate[9]) > (cardData->cardExpirationDate[4]))
		{
			printf("Expired Card\n");
			return EXPIRED_CARD;
		}
		else if ((termData->transactionDate[9]) == (cardData->cardExpirationDate[4]))
		{
			if ((termData->transactionDate[3]) > (cardData->cardExpirationDate[0]))
			{
				printf("Expired Card\n");
				return EXPIRED_CARD;
			}
			else if ((termData->transactionDate[3]) == (cardData->cardExpirationDate[0]))
			{
				if ((termData->transactionDate[4]) > (cardData->cardExpirationDate[1]))
				{
					printf("Expired Card\n");
					return EXPIRED_CARD;
				}
				else
				{
					return Terminal_OK;

				}
			}
			else
			{
				return Terminal_OK;
			}
		}
		else
		{
			return Terminal_OK;
		}
	}
	else
	{
		return Terminal_OK;

	}
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData)
{
	printf("Your Transaction amount is :");
	scanf("%f", &(termData->transAmount));
	if ((termData->transAmount) <= 0)
	{
		printf("INVALID AMOUNT\n");
		return INVALID_AMOUNT;
	}
	else
	{
		printf("OK\n");
		return Terminal_OK;
	}
}

EN_terminalError_t setMaxAmount(ST_terminalData_t *termData)
{
	printf("MAX Transaction amount is :");
	scanf("%f", &(termData->maxTransAmount));
	if ((termData->maxTransAmount) <= 0)
	{
		printf("INVALID MAX AMOUNT\n");
		return INVALID_MAX_AMOUNT;
	}
	else
	{
		printf("OK\n");
		return Terminal_OK;
	}
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData)
{
	if ((termData->transAmount) > (termData->maxTransAmount))
	{
		printf("Exceeded Max Amount\n");
		return EXCEED_MAX_AMOUNT;
	}
	else
	{
		return Terminal_OK;
	}
}
