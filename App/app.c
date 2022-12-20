#include "server.h"
void appStart(void) {
	while (1)
	{
		ST_cardData_t myCard;
		ST_terminalData_t term;
		ST_transaction_t trans= {0};
		short result = 0;
		do {
			 result = getCardHolderName(&myCard);
			 if (result != 0) {
				 system("cls");
				 printf("Error incorrect name!\n");
			 }

		} while (result != 0);

		do {
			result = getCardExpiryDate(&myCard);
			if (result != 0) {
				system("cls");
				printf("Error incorrect Expiry date!\n");
			}
		} while (result != 0);

		do {
			result = getCardPAN(&myCard);
			if (result != 0) {
				system("cls");
				printf("Error incorrect PAN!\n");
			}
		} while (result != 0);

		do {
			result = getTransactionDate(&term);
		} while (result != 0);
		

		if (isCardExpired(&myCard, &term) != 0) {
			//system("cls");
			printf("Card Expired\n");
			continue;
		}

		getTransactionAmount(&term);
		setMaxAmount(&term, 1500);

		if (term.transAmount>term.maxTransAmount)
		{
			printf("Transaction Amount exceeds limit.\n");
			continue;
		}

		if (isValidAccount(&myCard, accountsDB) != 0) {
			//system("cls");
			printf("Account Not found\n");
			continue;
		}

		if (isBelowMaxAmount(&term) != 0) {
			system("cls");
			printf("Insufficiant funds\n");
			continue;
		}
		if (isAmountAvailable(&term, accRef) != 0) {
			printf("Insufficiant funds\n");
			continue;
		}
		trans.cardHolderData = myCard;
		trans.terminalData = term;
		recieveTransactionData(&trans);
		saveTransaction(&trans);

	}
}

int main() {
	appStart();
	return 0;
}
//Transaction approved user story
//Exceed the maximum amount user story
//Insufficient fund user story
//Expired card user story
//Stolen card user story
