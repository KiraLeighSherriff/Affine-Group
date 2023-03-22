/****************************************************
*             De Montfort University                /
*              Cryptography CTEC2915                /
*        Affine Cipher for both brute froce &       /
*              encryption & Decryption              /
****************************************************/

/****************************************************
*                   Created by                      /
*              p2531028 Aryan Gill                  /
*              p2519032 Jasmin Hayre                /
*              p2668258 Faheem Khan                 /
*              p2660920 Kira Sherriff               /
*           All team members contributed            /
****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Prototype function
void affineDecrypt(char *plaintext, int a, int b);
void affineEncrypt(char *plaintext, int a, int b);
void affineBruteFroce(char *plaintext, int a, int b);
int gcd(int a, int b);
int modInv(int a, int m);
char removeNonLetters(char *plaintext);

int main()
{

    char plaintext[1024]; 
    int a, b; // keys 
    int option, menu;

    option = menu = 0;

    /* 

    options = used for Case 1 to let the use choose to 
    encrypted or decrypted 
     
    menu = Lets the user choose between case 1 and case 2.

    Case 1 is for encrypted or decrypted with keys when the keys are known to the user
    also can be used to encryt a text. User can give thier own keys.

    Case 2 is for brute forece, used for when the keys are unknown. 
    Group cipher text =  RILTOEAQGEQDPOJOESPQW = key a = 19, b = 18 

    */

    do {

        printf("\nEnter 0 to exit the program\n");
        printf("Enter 1 for encrypted or decrypted with keys\n");
        printf("Enter 2 for Brute Froce of affiner cipher\n");
        printf("Enter: ");
        scanf("%d", &menu);

        // Clears the input buffer so fegts can run
        while(getchar() != '\n');

        switch(menu)
        {

            case 0:

                exit(0);

            break;
                
/*------------------------------------Encrytion/Decryption-----------------------------------------------------*/
            case 1:

            // Getting user input
            printf("Enter the text to be encrypted or decrypted: ");
            fgets(plaintext, sizeof(plaintext), stdin);

            // Text to upper case
            for (int i = 0; i < strlen(plaintext); i++) 
            {
                plaintext[i] = toupper(plaintext[i]);
            }

            removeNonLetters(plaintext);

            // Getting key a 
            printf("Enter key a: ");
            scanf("%d", &a);

            // If the key is not relatively prime to 26 loop until it is
            // GCD number are 1,3,5,7,9,11,15,17,19,21,23,25,
            while (gcd(a, 26) != 1)
            {
                printf("Invalid key for a! Key of a needs to relatively prime to 26: ");
                scanf("%d", &a);
            }

            printf("Enter key b: ");
            scanf("%d", &b);

            option = 0;

            // Letting the user choose if they want to decrypt or encrypt
            // If 1 entered Encrypt 
            // If 2 entered Decrypt
            while((option != 1) && (option != 2))
            {
                // Choosing function
                printf("Enter 1 to encrypt or 2 to decrypt: ");
                scanf("%d", &option);

                if (option == 1)
                    affineEncrypt(plaintext, a, b);
                else if (option == 2)
                    affineDecrypt(plaintext, a, b);
                else
                    printf("Invalid input\n");
            }

            printf("\nKeys: a = %d, b = %d \tResult: %s\n", a, b, plaintext);


            break;
                
/*------------------------------------Brute Force------------------------------------------------*/


            case 2: 
                
                printf("Enter the text to decrypted: ");
                fgets(plaintext, sizeof(plaintext), stdin);

                for (int i = 1; i < strlen(plaintext); i++) 
                {
                    plaintext[i] = toupper(plaintext[i]);

                }

                // Looping though the keys for brutefroce
                for(a = 1; a < 26; a++)
                    {
                        // Checking if key a is relatively prime to 26
                        if (gcd(a, 26) == 1)   
                        {
                            for(b= 0; b < 26; ++b)
                            {
                                    
                                    affineBruteFroce(plaintext, a, b); 
                            }
                        }
                    }

                break;


            // If wrong input is entered
            default:

                printf("\nEnter invaid! Enter 1 or 2!\n");
                
                break;
            }

    }while (menu != 1 || menu != 2 );
}


/*------------------------------------GCD------------------------------------------------*/

// Function to calculate the GCD of two numbers

int gcd(int a, int b) {
    // checking if the second input is equal to zero
    if (a==0)
    { 
        return b;
    }
    
    // Return the calculation of gcd to the functions
    return gcd(b % a, a); 
}

/*------------------------------------modInv------------------------------------------------*/

// Function to calculate the modular multiplicative inverse 

int modInv(int a, int m)
{
   // Loop though to 26
    for (int i = 1; i < m; i++)
    {
        if ((a * i) % m == 1)
        {
            return i;
        }
    }
    
   return -1;
}

    

/*------------------------------------removeNonLetters------------------------------------------------*/

// Function to remove numbers and symbols from string

char removeNonLetters(char *plaintext)
{
    int j, i;

    for (i = 0, j = 0; plaintext[i] != '\0'; i++)
     {
        if (!isspace(plaintext[i]) && !isalpha(plaintext[i]))
        {
            continue;   
        }
        plaintext[j++] = plaintext[i];
    }
    plaintext[j-1] = '\0';
    
}



/*------------------------------------affineBruteFroce------------------------------------------------*/

// Function to implement the Brute Force

void affineBruteFroce(char *plaintext, int a, int b)
{
    int i, modInvCheck, decryt, lengh;
    lengh = strlen(plaintext);

    char character, text[lengh];

    // Check to to see if a is inverted
    modInvCheck = modInv(a, 26);
        if(modInvCheck == 0)
        {
            return;
        }


    // Replace each letter with the corresponding letter
    // decrypted using the affine cipher
    for (i = 0; i < strlen(plaintext); i++)
    {
        // Stores a letter from the cipher text in character
        // The decrypts the text with the keys
        character = plaintext[i];
        decryt = (modInvCheck * (character - 'A' - b)) % 26;

        // If number is less then 0 add 26 to get a number that is in the alphabet 
        if(decryt < 0)
            decryt += 26;

        // Add A for the ASCII conversion  
        text[i] = 'A' + decryt;
    }

    text[lengh-1] = '\0';

    // Will print out all 312 possible decryptions 
    printf("\nPrivare Keys: a = %d, b = %d \tResult: %s\n", a, b, text);
}




/*------------------------------------affineEncrypt------------------------------------------------*/

// Function to implement the affine cipher for encryption


void affineEncrypt(char *plaintext, int a, int b)
{
    int i; 

    // Replace each letter with the corresponding letter
    // encrypted using the affine cipher
    for (i = 0; i < strlen(plaintext); i++)
    {
        // For maintaining the in text space
        if(plaintext[i] == ' ')
        {
            continue;
        }
        else
        {
            plaintext[i] = (a * (plaintext[i] - 'A') + b) % 26 + 'A';
        }
    }
    
}

/*------------------------------------affineDecrypt------------------------------------------------*/

// Function to implement the affine cipher for decryption


void affineDecrypt(char *plaintext, int a, int b)
{
    int i; 
    
    // Replace each letter with the corresponding letter
    // decrypted using the affine cipher
    for (i = 0; i < strlen(plaintext); i++)
    {
        if(plaintext[i] == ' ')
        {
            continue;
        }
        else
        {
            plaintext[i] = (modInv(a, 26) * ((plaintext[i] - 'A') - b + 26)) % 26 + 'A';
        }
    }   
}
