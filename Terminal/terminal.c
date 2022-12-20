#include "terminal.h"
#include <stdlib.h>
void getTransactionDateTest(void);
void isCardExpiredTest(void);
void getTransactionAmountTest(void);
void isBelowMaxAmountTest(void);
void setMaxAmountTest(void);

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData) {
    char currentDate[input_size];
    printf("please type current date in the following format DD/MM/YYYY: ");
    fgets(currentDate, input_size, stdin);
    size_t temp_size = strlen(currentDate);
    //checks for the MM\DD\YYYY format
    if (temp_size != 11)
        return WRONG_DATE;

    if (currentDate[2] != '/' || currentDate[5] != '/')
        return WRONG_DATE;

    for (int i = 0; i < temp_size-1; i++)
    {
        if ((uint8_t)currentDate[i] > 58 && (uint8_t)currentDate[i] < 47) 
            return WRONG_DATE;
        
    }
    //checks whether the day is higher than 31
    if (currentDate[0] > 51)
        return WRONG_DATE;
    //checks whether the user entered a day in the correct format; 
    if (currentDate[0] == 51 && currentDate[1] > 49)
        return WRONG_DATE;
    //checks whether the user entered a month in the correct format;
    if (currentDate[3] == 49 && currentDate[4] > 50)
        return WRONG_DATE;
    strcpy(termData->transactionDate, currentDate);
    if (temp_size > 0 && termData->transactionDate[temp_size - 1] == '\n') termData->transactionDate[temp_size - 1] = '\0';
    return TERMINAL_OK;
};
EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData) {
    char cardYear[3] = "", cardMonth[3]="", currYear[3]="", currMonth[3]="";

  for (int i = 0; i < 2; i++) {
        cardYear[i] = cardData->cardExpirationDate[i + 3];
        cardMonth[i] = cardData->cardExpirationDate[i];
        currMonth[i] = termData->transactionDate[3 + i];
        currYear[i] = termData->transactionDate[8 + i];
    }
    //Checks if the card  expiration date exeeds the current date
    if(atoi(cardYear)>atoi(currYear))
        return TERMINAL_OK;

    if (atoi(cardYear) < atoi(currYear))
        return EXPIRED_CARD;

    if (atoi(cardYear) == atoi(cardYear))
        if (atoi(cardMonth) <= atoi(currMonth))
            return EXPIRED_CARD;
        else
            return TERMINAL_OK;

    return EXPIRED_CARD;
    
};
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData) {
    uint8_t amount[input_size] ="";
    printf("Please Enter Transaction amount:");
    fgets(&amount, 7, stdin);
    if (atoi(amount) > 0) {
        termData->transAmount = atoi(amount);
        return CARD_OK;
    }
    else
        return INVALID_AMOUNT;
};
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData) {
    if (termData->transAmount <= termData->maxTransAmount)
        return TERMINAL_OK;
    else
        return EXCEED_MAX_AMOUNT;

};
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData, float maxAmount) {
    if (maxAmount > 0) {
        termData->maxTransAmount = maxAmount;
        return TERMINAL_OK;
    }
    else
        return INVALID_MAX_AMOUNT;
};

void getTransactionDateTest(void) {
    uint8_t input[input_size] = "";
    short iteration = 1;
    printf("Tester Name: WAEL AYMAN ELSEBAYE AHMED\n");
    printf("Function Name : getTransactionDate \n");
    while (1)
    {
        printf("Test Case:%d\n", iteration);
        iteration++;
        printf("Expected output:");
        fgets(input, 50, stdin);
        ST_terminalData_t data;
        short result = getTransactionDate(&data);
        if (result == 0) {
            printf("Test result: Terminal OK\n");
            break;
        }
        else
            printf("Test result: WRONG DATE\n");

        for (size_t i = 0; i < 50; i++)
            printf("-");
        printf("\n");
    }

}
void isCardExpiredTest(void) {
    uint8_t input[input_size]= "";
    short iteration = 1;
    printf("Tester Name: WAEL AYMAN ELSEBAYE AHMED\n");
    printf("Function Name : isCardExpired \n");
    while (1)
    {
        printf("Test Case:%d\n", iteration);
        printf("Expected output:");
        fgets(input,50,stdin);
        iteration++;
        ST_cardData_t cardDate = {0};
        ST_terminalData_t trmoData = {0};
        getTransactionDate(&trmoData);
        getCardExpiryDate(&cardDate);
        short result = isCardExpired(&cardDate, &trmoData);
        if (result == 0) {
            printf("Test result: Terminal OK\n");
            break;
        }
        else 
            printf("Test result: EXPIRED_CARD \n");

        for (size_t i = 0; i < 50; i++)
            printf("-");
        printf("\n");
    }

};
void getTransactionAmountTest(void) {
    uint8_t input[input_size] = "";
    short iteration = 1;
    printf("Tester Name: WAEL AYMAN ELSEBAYE AHMED\n");
    printf("Function Name : getTransactionAmount \n");
    while (1)
    {
        printf("Test Case:%d\n", iteration);
        iteration++;
        printf("Expected output:");
        fgets(input, 50, stdin);
        ST_terminalData_t data;
        uint8_t result = getTransactionAmount(&data);
        if (result == 0) {
            printf("Test result: Terminal OK\n");
            break;
        }
        else
            printf("Test result: Invalid Amount\n");

        for (size_t i = 0; i < 50; i++)
            printf("-");
        printf("\n");
    }

};
void isBelowMaxAmountTest(void) {
    uint8_t input[input_size] = "";
    short iteration = 1;
    printf("Tester Name: WAEL AYMAN ELSEBAYE AHMED\n");
    printf("Function Name : isBelowMaxAmoun \n");
    while (1)
    {
        printf("Test Case:%d\n", iteration);
        iteration++;
        printf("Expected output:");
        fgets(input, 50, stdin);
        ST_terminalData_t data;
        getTransactionAmount(&data);
        setMaxAmount(&data, 1000);
        uint8_t result = isBelowMaxAmount(&data);
        if (result == 0) {
            printf("Test result: Terminal OK\n");
            break;
        }
        else
            printf("Test result: EXCEED_MAX_AMOUNT\n");

        for (size_t i = 0; i < 50; i++)
            printf("-");
        printf("\n");
    }
}
void setMaxAmountTest(void) {
    uint8_t input[input_size] = "";
    short iteration = 1;
    char chMax[10];
    printf("Tester Name: WAEL AYMAN ELSEBAYE AHMED\n");
    printf("Function Name : setMaxAmount \n");
    while (1)
    {
        ST_terminalData_t data;
        printf("Test Case:%d\n", iteration);
        iteration++;
        printf("Expected output:");
        fgets(input, input_size, stdin);
        printf("Enter the Max Amount:");
        fgets(chMax, 10, stdin);
        float Max = atof(chMax);
        uint8_t result = setMaxAmount(&data,Max);
        if (result == 0) {
            printf("Test result: Terminal OK\n");
            break;
        }
        else
            printf("Test result: INVALID_MAX_AMOUNT\n");

        for (size_t i = 0; i < 50; i++)
            printf("-");
        printf("\n");
    }
}
