#include"card.h"

EN_cardError_t getCardHolderName(ST_cardData_t* cardData) {
	char temp[50] = "";
	EN_cardError_t CardState = WRONG_NAME;
	// displaying message to user
	printf("Please type the card holder name:");
	gets(temp);
	size_t temp_size = strlen(temp);
	// if the user's input doesn't meet the size requirements 
	if (temp_size < 20 || temp_size>24) {
		CardState = WRONG_NAME;
		return CardState;
	}
	for (int i = 0; i < temp_size-1; i++)
	{
		// if the user entered a number or a symbol
		if ((int)temp[i] != 32 && (int)temp[i] < 65 || (int)temp[i]>122 || 
			(int)temp[i] > 90 && (int)temp[i] < 97) {
			CardState = WRONG_NAME;
			printf("%d", i);
			return CardState;

		}

	}
	//if all goes well	
	CardState = CARD_OK;
	strcpy(cardData->cardHolderName, temp);
	return CardState;
	
};
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData) {
	char expTemp[input_size];
	EN_cardError_t CardState = WRONG_EXP_DATE;
	printf("Please Enter the date of expiration: ");
	fgets(expTemp, input_size, stdin);
	size_t temp_size = strlen(expTemp);
	// checks for the card format
	if (temp_size == 6 && expTemp[2] == '/')
	{
		if ((int)expTemp[0] > 49)
			return CardState;

		if ((int)expTemp[1] > 50 && (int)expTemp[0] != 48) 
			return CardState;

		// if the user enters any letters or illegal symbols or an invalid month
		for (int i = 0; i < temp_size-1; i++)
			if ((int)expTemp[i] < 47 || (int)expTemp[i]>57 )
				return CardState;

		//if the user enters the correct format
		for (int i = 0; i < temp_size; i++)
			cardData->cardExpirationDate[i] = expTemp[i];
		
		CardState = CARD_OK;
		if (temp_size > 0 && cardData->cardExpirationDate[temp_size - 1] != '\0')
			cardData->cardExpirationDate[temp_size - 1] = '\0';
	}

		return CardState;
	
};
EN_cardError_t getCardPAN(ST_cardData_t* cardData) {
	uint8_t accNumber[30] = "";
	EN_cardError_t cardState = WRONG_PAN;
	printf("Enter your Card's pan Number:");
	fgets(accNumber, 30, stdin);
	size_t temp_size = strlen(accNumber);

	if (temp_size >= 16 && temp_size <= 20) {
		if (temp_size > 0 && accNumber[temp_size - 1] != '\0')
			accNumber[temp_size - 1] = '\0';
		memcpy(cardData->primaryAccountNumber, accNumber, temp_size + 1);
		cardState = CARD_OK;
		return cardState;
	}
	return cardState;

}


void getCardPANTest(void) {
	ST_cardData_t card;
	printf("Tester Name: Wael ayman Elsebaye ahmed\n");
	printf("function name: getCardPAN\n");
	printf("When not enough characters are given\n");
	printf("testcase 1:- \n");
	printf("expected result: 3\n test result: %d\n ", getCardPAN(&card));
	printf("When the number of letters in card name exceed 19 \n");
	printf("testcase 2:- \n");
	printf("expected result: 3\n test result: %d\n ", getCardPAN(&card));
	printf("When number satisfies the conditions\n");
	printf("testcase 3:- \n");
	printf("expected result: 0\n test result: %d\n ", getCardPAN(&card));
};
void getCardExpiryDateTest(void) {
	ST_cardData_t card;
	printf("Tester Name: Wael ayman Elsebaye ahmed\n");
	printf("function name: getCardExpiryDate\n");
	printf("When not enough characters are given\n");
	printf("testcase 1:- \n");
	printf("expected result:2\n test result: %d\n ", getCardExpiryDate(&card));
	printf("When the number of letters in card name exceed 5 \n");
	printf("testcase 2:- \n");
	printf("expected result: 2\n test result: %d\n ", getCardExpiryDate(&card));
	printf("when the user enters letters in his expiry date\n");
	printf("testcase 3:- \n");
	printf("expected result: 2\n test result: %d\n ", getCardExpiryDate(&card));
	printf("when user enters a month greater than 12\n");
	printf("testcase 4:- \n");
	printf("expected result: 2\n test result :%d\n ", getCardExpiryDate(&card));
	printf("When number satisfies the conditions\n");
	printf("testcase 5:- \n");
	printf("expected result: 0\n test result: %d\n ", getCardExpiryDate(&card));
}
void getCardHolderNameTest(void) {
	printf("Tester Name: Wael ayman Elsebaye ahmed\n");
	ST_cardData_t card;
	printf("function name: getCardHolderName\n");
	printf("When not enough characters are given\n");
	printf("testcase 1:- \n");
	printf("expected result:1\n test result: %d\n ", getCardHolderName(&card));
	printf("When the number of letters in card name exceed 24 \n");
	printf("testcase 2:- \n");
	printf("expected result: 1\n test result: %d\n ", getCardHolderName(&card));
	printf("When number satisfies the conditions\n");
	printf("testcase 3:- \n");
	printf("expected result: 0\n test result: %d\n ", getCardHolderName(&card));
}
