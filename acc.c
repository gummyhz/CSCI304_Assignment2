#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<math.h>    // when compiling, use -lm as well
#include<stdlib.h>

// convert binary in short int; return value
short get_binary_op (char *bin) {
    short s = 0;
    for (int i=strlen(bin)-1; i>=0; i--) {
        if (i==0 && bin[i]=='1') {                  // for two's complement subtract msb
            s -= (int) pow(2, (strlen(bin)-1-i));
        } else {                                    // if there is a 1, add the place value to the sum
            if (bin[i] =='1') {
                s += (int) pow(2, (strlen(bin)-1-i));
            }
        }
    }
    return s;
}

// format acc in binary for output
void convert_to_binary (short acc, char *bin) {
    int x = acc;
    if (acc<0) {                    // for negative inputs
        x = (pow(2,16)-abs(acc));   // convert int goal into decimal equivalent of the two's complement when treated as unsigned
    }
    for (int i=15; i>=0; i--) {     // use remainders of division by two to convert to binary string
        bin[i] = (x % 2) + 48;
        x /= 2;
    }
    bin[16] = '\0';
}

// read in value in mode; return value
short get_operand (char mode) {
    short x = 0;
    switch (mode) {
        case 'B':
            char inB;
            printf("Enter binary value: ");
            scanf("%s", &inB);
            char b[17];
            strcpy(b,&inB);
            x = get_binary_op(b);
            break;
        case 'O':
            printf("Enter oct value: ");
            scanf("%ho", &x);
            break;
        case 'H':
            printf("Enter hex value: ");
            scanf("%hX", &x);
            break;
        default:    // default mode is decimal
            printf("Enter decimal value: ");
            scanf("%hd", &x);
            break;
    } 
    printf("\n");
    return x;
}

// print out accumulator values
void print_acc (short acc) {
    char b[17];
    convert_to_binary(acc, b);

    // if statements here are to make the asterisks line up when printing; but they only work for terminal output
    printf("*Binary\t : %s            *\n", b);

    if (acc < 0) {
        printf("*Hex\t : %04X\t\t       *\n", acc);
    } else { printf("*Hex\t : %04X\t\t\t       *\n", acc); }

    printf("*Octal\t : %06o\t\t       *\n", acc);

    if (acc > 9999 || acc < -999) {
        printf("*Decimal : %d\t\t       *\n", acc);
    } else {  printf("*Decimal : %d\t\t\t       *\n", acc); }    
}

// print menu and get option
char print_menu () {
    // print menu
    printf("Please select one of the following options:\n");
    printf("B   Binary Mode\n");
    printf("O   Octal Mode\n");
    printf("H   Hexadecimal Mode\n");
    printf("D   Decimal Mode\n\n");
    printf("C   Clear Accumulator\n");
    printf("S   Set Accumulator\n\n");
    printf("Q   Quit\n");
    // get option
    char choice;
    printf("Option:\n");
    scanf(" %c", &choice);
    return choice;
}

// main menu loop; execute option or call appropriate function
int main() {
    short acc = 0;      // accumulator's accumulated value
    char m[4] = "Dec";  // where the selected mode is stored
    int stop = 0;       // 0 or 1, depending on if the end-loop condition is met

    while (stop == 0) {
        switch(toupper(print_menu())) {
            case 'B':
                printf("Mode is Bin\n");
                strcpy(m,"Bin");
                break;
            case 'O':
                printf("Mode is Oct\n");
                strcpy(m,"Oct");
                break;
            case 'H':
                printf("Mode is Hex\n");
                strcpy(m,"Hex");
                break;
            case 'D':
                printf("Mode is Dec\n");
                strcpy(m,"Dec");
                break;
            case 'C':
                acc = 0;
                break;
            case 'S':
                acc += get_operand(m[0]);
                break;
            case 'Q':
                stop = 1;
                break;
            default:
                printf("Invalid option\n");
                break;
        }
        if (stop == 0) { // avoids displaying accumulator an extra time after the user chooses to quit
            printf("****************************************\n");
            printf("* Accumulator:\t\tInput Mode: %s*\n", m);       // mode printed here so that mode doesn't have to be global or passed to print_acc
            print_acc(acc);
            printf("****************************************\n");
        }
    } // end main menu loop 
    return 0; 
} // end main function
