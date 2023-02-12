#define CRT_NO_WARNINGS
#include "Server.h"
#include <string.h>
#include<stdio.h>
int d;
int index;
ST_accountsDB_t validaccounts[255] = { {5000,"14567899235677893"},{125000,"01559949017123456"},{3000000,"123456789123456789"},{2000000,"25421234355"} };
ST_transaction_t transactions[255] = { (uint8_t)NULL };

EN_serverError_t saveTransaction(ST_transaction_t *transData)
{

	for (int i = 0; i < (sizeof(transactions) / sizeof(transactions[0])); i++)
	{
		if ((transactions[i].transactionSequenceNumber != 0) && (i == (sizeof(transactions) / sizeof(transactions[0])) - 1))
		{
			return SAVING_FAILED;

		}
		else if (transactions[i].transactionSequenceNumber == 0)
		{
			transactions[i] = *transData;
			transactions[i].transactionSequenceNumber = i + 1;

			return Server_OK;
		}
	}
	return SAVING_FAILED;
}

EN_serverError_t isAmountAvailable(ST_terminalData_t *termData)
{

	if (termData->transAmount > validaccounts[index].balance)
	{
		return LOW_BALANCE;
	}
	else
	{
		return Server_OK;
	}
}
EN_serverError_t isValidAccount(ST_cardData_t *cardData)
{
	int i;
	for (i = 0; i < (sizeof(validaccounts) / sizeof(validaccounts[0])); i++)
	{
		if (strcmp(cardData->primaryAccountNumber, validaccounts[i].primaryAccountNumber) == 0)
		{
			index = i;
			return Server_OK;
		}
		else if ((i == 254) && (strcmp(&cardData->primaryAccountNumber, &validaccounts[i].primaryAccountNumber) != 0))
		{
			return ACCOUNT_NOT_FOUND;
		}
		else
			continue;
	}
	return ACCOUNT_NOT_FOUND;
}

EN_transStat_t recieveTransactionData(ST_transaction_t *transData)
{
	if (isValidAccount(&transData->cardHolderData) != 0)
	{
		if (saveTransaction(transData) != 0)
		{
			printf("INTERNAL SERVER ERROR\n");
			return INTERNAL_SERVER_ERROR;

		}
		else
		{
			printf("DECLINED STOLEN CARD\n");
			transData->transState = DECLINED_STOLEN_CARD;
			return DECLINED_STOLEN_CARD;
		}

	}
	else
	{
		if (isAmountAvailable(&transData->terminalData) != 0)
		{
			if (saveTransaction(transData) != 0)
			{
				printf("INTERNAL SERVER ERROR\n");
				return INTERNAL_SERVER_ERROR;

			}
			else
			{
				printf("DECLINED INSUFFECIENT FUND\n");
				transData->transState = DECLINED_INSUFFECIENT_FUND;
				return DECLINED_INSUFFECIENT_FUND;
			}
		}
	}

	if (saveTransaction(transData) != 0)
	{
		printf("INTERNAL SERVER ERROR\n");
		return INTERNAL_SERVER_ERROR;

	}
	else
	{
		printf("APPROVED\n");
		transData->transState = APPROVED;
		return APPROVED;
	}

}

