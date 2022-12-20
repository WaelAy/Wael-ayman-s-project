#ifndef server_h
#define server_h


#include "terminal.h"
typedef unsigned long long uint32_t;
typedef enum EN_transState_t
{
    APPROVED, DECLINED_INSUFFECIENT_FUND,
    DECLINED_STOLEN_CARD, FRAUD_CARD, INTERNAL_SERVER_ERROR
}EN_transState_t;

typedef struct ST_transaction_t
{
    ST_cardData_t cardHolderData;
    ST_terminalData_t terminalData;
    EN_transState_t transState;
    uint32_t transactionSequenceNumber;
}ST_transaction_t;

typedef enum EN_serverError_t
{
    SERVER_OK, SAVING_FAILED, TRANSACTION_NOT_FOUND,
    ACCOUNT_NOT_FOUND, LOW_BALANCE, BLOCKED_ACCOUNT
}EN_serverError_t;

typedef enum EN_accountState_t
{
    RUNNING,
    BLOCKED
}EN_accountState_t;

typedef struct ST_accountsDB_t
{
    float balance;
    EN_accountState_t state;
    uint8_t primaryAccountNumber[20];
}ST_accountsDB_t;

EN_transState_t recieveTransactionData(ST_transaction_t* transData);
EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountRefrence);
EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence);
EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_accountsDB_t* accountRefrence);
EN_serverError_t saveTransaction(ST_transaction_t* transData);
void listSavedTransactions(void);

static ST_accountsDB_t accountsDB[255] = { {2000.0,RUNNING, "8989374615436851"},{1000.0,BLOCKED,"5807007076043875"},
                                    {3500.0,RUNNING,"8640215930259895"},{150000.0,BLOCKED,"8546201597530482"},
                                    {250000.0,RUNNING,"5670231578964227"},{1500.2,BLOCKED,"7346452297364252"} };
static ST_transaction_t transactionsDB[255] = {0};
ST_accountsDB_t *accRef;

#endif
