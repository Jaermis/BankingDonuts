#include <stdio.h>
#include <unistd.h>
#include<stdlib.h>

#define MAX_CARDS 100 // Maximum number of cards in the program

int cardInfoArray[MAX_CARDS][3];// 2D array for card number, pin, and reset pin
double balanceArray[MAX_CARDS]; // Array for account balances
int cardCount = 0;// Variable to keep track of the number of cards created

//function declarations
void Splash(); 
void showMenu(); 
void createCard(); 
void makeTransaction(); 


int main() {
    Splash();
    showMenu();
    return 0;
}

//logo of the program
void Splash() {
    printf(" /$$$$$$$                      /$$       /$$                           /$$$$$$$                                  /$$    \n");
    printf("| $$__  $$                    | $$      |__/                          | $$__  $$                                | $$    \n");
    printf("| $$  \\ $$  /$$$$$$  /$$$$$$$ | $$   /$$ /$$ /$$$$$$$   /$$$$$$       | $$  \\ $$  /$$$$$$  /$$$$$$$  /$$   /$$ /$$$$$$  \n");
    printf("| $$$$$$$  |____  $$| $$__  $$| $$  /$$/| $$| $$__  $$ /$$__  $$      | $$  | $$ /$$__  $$| $$__  $$| $$  | $$|_  $$_/  \n");
    printf("| $$__  $$  /$$$$$$$| $$  \\ $$| $$$$$$/ | $$| $$  \\ $$| $$  \\ $$      | $$  | $$| $$  \\ $$| $$  \\ $$| $$  | $$  | $$    \n");
    printf("| $$  \\ $$ /$$__  $$| $$  | $$| $$_  $$ | $$| $$  | $$| $$  | $$      | $$  | $$| $$  | $$| $$  | $$| $$  | $$  | $$ /$$\n");
    printf("| $$$$$$$/|  $$$$$$$| $$  | $$| $$ \\  $$| $$| $$  | $$|  $$$$$$$      | $$$$$$$/|  $$$$$$/| $$  | $$|  $$$$$$/  |  $$$$/\n");
    printf("|_______/  \\_______/|__/  |__/|__/  \\__/|__/|__/  |__/ \\____  $$      |_______/  \\______/ |__/  |__/ \\______/    \\___/  \n");
    printf("                                                       /$$  \\ $$                                                        \n");
    printf("                                                      |  $$$$$$/                                                        \n");
    printf("                                                       \\______/                                                         \n");

    sleep(2); // Pause for 2 seconds
}

//main menu of the program
void showMenu() {
   int choice;

    while (1) {
        system("cls");
		printf("Welcome to Banking Donuts! What can we do for you?\n\n");
        printf("Choose an option:\n");
        printf("[1] Create a card\n");
        printf("[2] Make a transaction\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                system("cls");
                createCard();
                break;
            case 2:
                system("cls");
                makeTransaction();
                break;
            default:
                while (getchar() != '\n');
                break;
        }

        if (choice == 1 || choice == 2) {
            break;
        }
    }
}

//card creation function
void createCard() {
    int pin, resetPin;

    printf("Creating a Card for you...\n\n");

	//this loop will continue to ask user for a 4-digit PIN until they give the correct input format.
    while (1) {
        printf("Enter a 4-digit PIN: ");
        if (scanf("%d", &pin) != 1 || pin < 1000 || pin > 9999) {
            printf("\nInvalid PIN. Please enter a 4-digit PIN.\n");
            while (getchar() != '\n'); //prevents the console from crashing if the input has non-integer values, will be seen in other parts of the code
        }
		else {
            break;
        }
    }
	//same to this loop
    while (1) {
        printf("Enter a 6-digit Reset PIN: ");
        if (scanf("%d", &resetPin) != 1 || resetPin < 100000 || resetPin > 999999) {
            printf("\nInvalid Reset PIN. Please enter a 6-digit Reset PIN.\n");
            while (getchar() != '\n');
        }
		else {
            break;
        }
    }

    // Generate the 10-digit card number with format
    long long cardNumber = 1000000000LL + cardCount;

    // Store the card number, pin, and reset pin in the 2D array
    cardInfoArray[cardCount][0] = cardNumber;
    cardInfoArray[cardCount][1] = pin;
    cardInfoArray[cardCount][2] = resetPin;

    // Store the initial balance in the balance array
    double initialBalance = 500.0;
    balanceArray[cardCount] = initialBalance;

    // Increment the card count
    cardCount++;
	
	//print the card details
    printf("\n\nCard created successfully!\n\n");
    printf("Card Number: %010lld\n", cardNumber);
    printf("PIN: %04d\n", pin);
    printf("Reset PIN: %06d\n", resetPin);
    printf("Initial Balance: %.2f\n\n", initialBalance);
    
    //redirecting to main menu with a loading animation for 5 seconds, will be seen in other parts of the code
    printf("Redirecting to main menu ");
    int loadcount;
    for (loadcount = 0; loadcount <= 5; loadcount++) {
        printf(".");
        sleep(1);
    }

    system("cls");
    showMenu(); //goes back to main menu
}

//function to withdraw, deposit, and reset PIN
void makeTransaction() {
	//declarations for needed data
    long long inputCardNumber;
    int i, inputPIN, inputResetPin, newPin, loadcount, transactionChoice, anotherTransactionInput;
    int index = -1;
    double withdrawalAmount, depositAmount;

    printf("Making a transaction...\n\n");
    printf("Enter your Card Number: ");
    scanf("%lld", &inputCardNumber);
    printf("Enter your PIN: ");
    scanf("%d", &inputPIN);

    // Check if the card number and PIN match
    for (i = 0; i < cardCount; i++) {
        if (cardInfoArray[i][0] == inputCardNumber && cardInfoArray[i][1] == inputPIN) {
            index = i;
            break;
        }
    }
	//if details do not match
    if (index == -1) {
        printf("\nInvalid Card Number or PIN. Redirecting to main menu ");
        for (loadcount = 0; loadcount <= 2; loadcount++) {
            printf(".");
            sleep(1);
        }
        system("cls");
        showMenu();
        return;
    }
    //if details match
    system("cls");
    while (1) {
        printf("Account successfully verified!\n\n");
        printf("Current Balance: %.2f\n\n", balanceArray[index]);
        printf("[1] Withdraw Credits\n");
        printf("[2] Deposit Credits\n");
        printf("[3] Reset PIN\n");
        printf("[4] Back to Main Menu\n\n");
        printf("Enter your choice: ");

        scanf("%d", &transactionChoice);

        switch (transactionChoice) {
            case 1: //withdrawal process
                do {
        			printf("Enter the amount to withdraw: ");
        			if (scanf("%lf", &withdrawalAmount) != 1 || withdrawalAmount < 0) {
        				//format checkers (negative inputs and non-integer inputs)
            			printf("\nInvalid input. Please enter a valid positive amount.\n");
            			while (getchar() != '\n');
        			}
					else {
            			break;
        			}
    			} while (1);
				//if withdrawal amount is less than the current balance and the withdrawal limit (5000)
   				if (withdrawalAmount <= balanceArray[index]) {
        			if (withdrawalAmount <= 5000) {
            			balanceArray[index] -= withdrawalAmount; //withdrawal amount is deducted to the current balance and reassigns the difference back to the balance
            			//printing receipt
						printf("\nTransaction completed. Amount withdrawn: %.2f\n", withdrawalAmount);
            			printf("Current Balance: %.2f\n", balanceArray[index]);
        			} else {
            			printf("\nTransaction failed. Maximum withdrawal limit exceeded. You can only withdraw up to 5000 per transaction.\n");
        			}
    			} else {
        			printf("\nTransaction failed. Insufficient balance.\n");
    			}
    			break;
            case 2: //deposit process
    			do {
        			printf("Enter the amount to deposit: ");
        			if (scanf("%lf", &depositAmount) != 1 || depositAmount < 0) {
        				//same format checker with withdrawal process
            			printf("\nInvalid input. Please enter a valid positive amount.\n");
            			while (getchar() != '\n');
        			}
					else {
            			break;
        			}
    			} while (1);
				//add the amount entered to the current balance and reassign the sum to the current balance
    			balanceArray[index] += depositAmount;
    			//print receipt
    			printf("\nTransaction completed. Amount deposited: %.2f\n", depositAmount);
    			printf("Current Balance: %.2f\n", balanceArray[index]);
    			break;
            case 3: //reset PIN
    			printf("Enter your 6-digit Reset PIN: ");
    			scanf("%d", &inputResetPin);

				//Reset PIN Checker
    			if (inputResetPin == cardInfoArray[index][2]) {
    				//if the PIN matched, ask for a new 4 digit PIN, will loop until the correct format is inputted
        			while (1) {
            			printf("Enter your new 4-digit PIN: ");
            			if (scanf("%d", &newPin) != 1 || newPin < 1000 || newPin > 9999) {
                			printf("\nInvalid PIN. Please enter a 4-digit PIN.\n");
                			while (getchar() != '\n');
            			}
						else {
                			cardInfoArray[index][1] = newPin;
                
               				printf("\nPIN updated successfully.\n\n");
                			break;
            			}
        			}
    			}
				else {
        			printf("\nIncorrect Reset PIN.\n\n");
    			}
    			break;
			case 4: //back to main menu
				printf("Redirecting to main menu ");
        			for (loadcount = 0; loadcount <= 2; loadcount++) {
            			printf(".");
            			sleep(1);
        			}
        			system("cls");
        			showMenu();
        			return;
				break; 
            default:
                continue; 
        }
        
        //for cases 1-3, in every after a transaction, it asks the user if it wants to make another transaction or not
        while (1) {
        	printf("\nDo you want to make another transaction? (1 for Yes, 0 for No): ");
        	if (scanf("%d", &anotherTransactionInput) == 1) {
          	  if (anotherTransactionInput == 0) {
            	    // If No, redirect to the main menu
            	    system("cls");
            	   	showMenu();
                	return;
            	}
				else if (anotherTransactionInput == 1) {
            	// If Yes, break the loop for another transaction
            	break;
            	}
        	}
				else {
            	// Invalid input, clear input buffer
            	while (getchar() != '\n');
        		}
    	}
    system("cls");
    }
}
