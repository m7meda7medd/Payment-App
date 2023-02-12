#define CRT_NO_WARNINGS
#include "Card.h"
#include<stdio.h>
#include<string.h>

EN_cardError_t getCardHolderName(ST_cardData_t *cardData)
{
	fflush(stdin);
	printf("CardHolder's Name is:");
	gets(cardData->cardHolderName);
	fflush(stdin);
	if ((strlen(cardData->cardHolderName) <= 24) && (strlen(cardData->cardHolderName)) >= 20)
	{
		printf("OK\n");
		return OK;
	}
	else if (((cardData->cardHolderName) == NULL) || (strlen(cardData->cardHolderName) < 20) || (strlen(cardData->cardHolderName) > 24))
	{
		printf("WRONG NAME\n");
		return WRONG_NAME;
	}
	else
	{
		printf("OK\n");
		return OK;

	}
}
EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData)
{
	fflush(stdin);
	printf("Exp Date as MM/YY is:");
	fflush(stdin);
	gets(cardData->cardExpirationDate);
	fflush(stdin);
	if ((cardData->cardExpirationDate[2] != '/') || (cardData->cardExpirationDate[0] > '1') || (cardData->cardExpirationDate[3] > '3') || (cardData->cardExpirationDate == NULL) || (strlen(cardData->cardExpirationDate) != 5))
	{
		printf("WRONG EXP DATE\n");
		return WRONG_EXP_DATE;
	}
	else
	{
		printf("OK\n");
		return OK;
	}

}
EN_cardError_t getCardPAN(ST_cardData_t *cardData)
{
	fflush(stdin);
	printf("PAN is:");
	gets(cardData->primaryAccountNumber);
	fflush(stdin);
	if ((strlen(cardData->primaryAccountNumber) < 16) || (strlen(cardData->primaryAccountNumber) > 19))
	{
		printf("WRONG PAN\n");
		return WRONG_PAN;
	}
	else
	{
		printf("OK\n");
		return OK;

	}
}
