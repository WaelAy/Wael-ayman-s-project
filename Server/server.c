#include "server.h"

ST_accountsDB_t accountsDB[255] = { {2000.0,RUNNING, "8989374615436851"},{1000.0,BLOCKED,"5807007076043875"},
									{3500.0,RUNNING,"8640215930259895"},{150000.0,BLOCKED,"8546201597530482"},
									{250000.0,RUNNING,"5670231578964227"},{1500.2,BLOCKED,"7346452297364252"} };
ST_transaction_t transactionsDB[255] = { 0 };
ST_accountsDB_t* accRef;


void recieveTransactionDataTest(void);
void isValidAccountTest(void);
void isBlockedAccountTest(void);
void isAmountAvailableTest(void);
void saveTransactionTest(void);

EN_transState_t recieveTransactionData(ST_transaction_t* transData) {
	static unsigned int Transaction_Number = 0;
	EN_transState_t State = FRAUD_CARD;
	
		// loops searches for the user account
		if (!isValidAccount(&transData->cardHolderData,accountsDB)) {
			State = DECLINED_INSUFFECIENT_FUND;
			if (transData->terminalData.transAmount <= accRef->balance)
				State = DECLINED_STOLEN_CARD;
			if (accRef->state == RUNNING && State == DECLINED_STOLEN_CARD) {
				State = APPROVED;
				accRef->balance -= transData->terminalData.transAmount;
			}	
		
	}
	if (Transaction_Number > 254)
		State = INTERNAL_SERVER_ERROR;
	transData->transState = State;
	return State;
};
EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountRefrence) {
	ST_accountsDB_t *currAcc;
	for (int i = 0; i < sizeof accountsDB / sizeof accountsDB[0]; i++) {
		currAcc = (accountRefrence + i);
		if (!strcmp(cardData->primaryAccountNumber, currAcc->primaryAccountNumber)) {
			accRef = currAcc;
			return SERVER_OK;
		}
	}
	return ACCOUNT_NOT_FOUND;
};
EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence) {
	if (accountRefrence->state == BLOCKED)
		return BLOCKED_ACCOUNT;
	else
		return SERVER_OK;
};
EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_accountsDB_t* accountRefrence) {
	if (termData->transAmount <= accountRefrence->balance)
		return SERVER_OK;
	else
		return LOW_BALANCE;
};
EN_serverError_t saveTransaction(ST_transaction_t* transData) {
	static  int transaction_number = 0;
	uint32_t sequence_number = 196548723642800000;
	transactionsDB[transaction_number].cardHolderData = transData->cardHolderData;
	transactionsDB[transaction_number].terminalData = transData->terminalData;
	transactionsDB[transaction_number].transactionSequenceNumber = sequence_number++;
	transactionsDB[transaction_number].transState = transData->transState;
	transaction_number++;
	listSavedTransactions();
	return SERVER_OK;

};
void listSavedTransactions(void) {
	for (size_t i = 0; i < 255; i++)
	{
		if (transactionsDB[i].transactionSequenceNumber == 0)
			break;
		printf("#########################\n");
		printf("Transaction Sequence Number:%llu\n", transactionsDB[i].transactionSequenceNumber);
		printf("Transaction Date :%s\n", transactionsDB[i].terminalData.transactionDate);
		printf("Transaction Amount:%f\n", transactionsDB[i].terminalData.transAmount);
		printf("Terminal Max Amount:%f\n", transactionsDB[i].terminalData.maxTransAmount);
		printf("Cardholder Name :%s\n", transactionsDB[i].cardHolderData.cardHolderName);
		printf("PAN:%s\n", transactionsDB[i].cardHolderData.primaryAccountNumber);
		printf("Card Expiration Date :%s\n", transactionsDB[i].cardHolderData.cardExpirationDate);
		printf("New balance:%f\n", accRef->balance);
		printf("transaction state:");
		switch (transactionsDB[i].transState)
		{
		case 0:
			printf("APPROVED\n");
			break;
		case 1:
			printf("DECLINED_INSUFFECIENT_FUND\n");
			break;
		case 2:
			printf("DECLINED_STOLEN_CARD\n");
			break;
		case 3:
			printf("FRAUD_CARD\n");
			break;
		default:
			printf("Internal Server Error\n");
			break;
		}
		printf("#########################\n");

	}

};

void recieveTransactionDataTest(void) {
	char input[input_size] = "";
	static uint8_t iteration = 1;
	char chMax[10];
	printf("Tester Name: WAEL AYMAN ELSEBAYE AHMED\n");
	printf("Function Name : recieveTransactionData \n");
	while (1)
	{
		short acc = iteration % 5;
		printf("Test Case:%d\n", iteration);
		iteration++;
		printf("Expected output:");
		fgets(input, 50, stdin);
		ST_transaction_t data = {0};
		for (int i = 0; i < strlen(accountsDB[0].primaryAccountNumber) + 1; i++)
		{

			data.cardHolderData.primaryAccountNumber[i] = accountsDB[acc].primaryAccountNumber[i];
		}
		printf("input data:");
		fgets(chMax, 10, stdin);
		float Max = atoi(chMax);
		data.terminalData.transAmount = Max;
		uint8_t result = recieveTransactionData(&data);
		if (result == 0) {
			printf("Test result: APPROVED\n");
			break;
		}
		else if (result == 1)
			printf("Test result: DECLINED_INSUFFECIENT_FUND\n");
		else if (result == 2)
			printf("Test result: DECLINED_STOLEN_CARD\n");
		else if (result == 3)
			printf("Test result: FRAUD_CARD\n");
		else
			printf("Test result: INTERNAL_SERVER_ERROR\n");
		for (size_t i = 0; i < 50; i++)
			printf("-");
		printf("\n");
	}
};
void isValidAccountTest(void) {
	char input[input_size] = "";
	static uint8_t iteration = 1;
	int acc = 0;
	printf("Tester Name: WAEL AYMAN ELSEBAYE AHMED\n");
	printf("Function Name : isValidAccount \n");
	while (1)
	{
		ST_cardData_t card = { 0 };
		printf("Test Case:%d\n", iteration);
		printf("Expected output:");
		fgets(input, 50, stdin);
		getCardPAN(&card);
		uint8_t result = isValidAccount(&card,accountsDB);
		if (result == 0) {
			printf("Test result: SERVER_OK\n");
			break;
		}
		else
			printf("Test result: ACCOUNT_NOT_FOUND\n");
		for (size_t i = 0; i < 50; i++)
			printf("-");
		printf("\n");
		iteration++;
	}
}
void isBlockedAccountTest(void) {
	unsigned short iteration = 1;
	printf("Tester Name: WAEL AYMAN ELSEBAYE AHMED\n");
	printf("Function Name : isBlockedAccount \n");
	while (1){

		ST_cardData_t card = {0};
		int acc = 0;

		printf("Test case: %d\n", iteration);
		printf("Input account number:");
		scanf("%d", &acc);

		ST_accountsDB_t account = accountsDB[acc];
		int result = isBlockedAccount(&account);

		printf("Expected output:");
		if (result == 0) {
			printf("Test result: SERVER_OK\n");
			break;
		}
		else
			printf("Test result: BLOCKED_ACCOUNT\n");
		iteration++;	
	}
}
void isAmountAvailableTest(void){
	int iteration = 0;
	char input[input_size];
	char chMax[10];
	int AMOUNT;
	printf("Tester Name: WAEL AYMAN ELSEBAYE AHMED\n");
	printf("Function Name : isAmountAvailable \n");
	while (1) {
		iteration++;
		printf("Test case: %d\n", iteration);
		printf("Expected output:");
		fgets(input, 50, stdin);
		printf("input data:");
		fgets(chMax, 10, stdin);
		AMOUNT = atoi(chMax);
		ST_accountsDB_t account = accountsDB[0];
		ST_terminalData_t data = {0};
		data.transAmount = AMOUNT;
		int result = isAmountAvailable(&data, &account);
		if (result == 0) {
			printf("Test result: SERVER_OK\n");
			break;
		}
		else
			printf("Test result: LOW_BALANCE\n");

	}
}
void saveTransactionTest(void) {
	int iteration = 0;
	printf("Tester Name: WAEL AYMAN ELSEBAYE AHMED\n");
	printf("Function Name : saveTransaction \n");
	while (1) {
		iteration++;
		printf("Test case: %d\n", iteration);
		ST_transaction_t trans = {0};
		ST_terminalData_t ter = {0};
		ST_cardData_t CARD= {0};
		getCardExpiryDate(&CARD);
		getCardHolderName(&CARD);
		getCardPAN(&CARD);
		getTransactionDate(&ter);
		getTransactionAmount(&ter);
		setMaxAmount(&ter, 10000.0);
		trans.cardHolderData = CARD;
		trans.terminalData = ter;

		int result = saveTransaction(&trans);
		if (result == 0)
			printf("Test result: SERVER_OK\n");
	}
}
