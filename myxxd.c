#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
        int c;                                                                  // store file contents
        int endian[135];                                                        // storage for -e

        if (argc != 3)                                                          // if user inputs too many or too few arguments...
        {
                printf("Too few or too many arguments. Please enter three arguments: ./myxdd -[p, b, C, e, u] [INPUT]\n>");
        }

        FILE *file;                                                             // file variable
        file = fopen(argv[2], "r");                                             // open file in read mode

        if (strcmp(argv[1], "-p") == 0)                                         // if user inputs -p flag
        {
                if (file)                                                       // if file exists
                {
                        while ((c = getc(file)) != EOF)                         // go through each char in file...
                        {
                                printf("%02x", c);                              // ...and print out hex version
                        }
                }
                else                                                            // if file does not exist
                {
                        printf("A file under that name does not exist.\n");
                }

                printf("\n");
        }
        else if (strcmp(argv[1], "-b") == 0)                                    // if user inputs -b flag
        {
                if (file)                                                       // if file exists
                {
                        while ((c = getc(file)) != EOF)                         // go through each char in file...
                        {
                                for (int i = 0; i < 8; i++)                     // loop 8 times because a char in C is 8 bytes
                                {
                                        printf("%d", !!((c << i) & 0x80));      // print binary of c (8 bytes)
                                }

                                printf(" ");                                    // spacing between bytes
                        }
                }
                else                                                            // if file does not exist
                {
                        printf("A file under that name does not exist.\n");
                }

                printf("\n");
        }
        else if (strcmp(argv[1], "-C") == 0)                                    // if user inputs -C flag
        {
                int count = 1;                                                  // tracking for printing

                if (file)                                                       // if file exists
                {
                        while ((c = getc(file)) != EOF)                         // go through each char in file...
                        {
                                printf("%02x", c);
                                count++;                                        // increment

                                if (count == 3)                                 // for spacing between hex
                                {
                                        printf(" ");                            // space
                                        count = 1;                              // reset
                                }
                        }
                }
                else                                                            // if file does not exist
                {
                        printf("A file under that name does not exist.\n");
                }

                printf("\n");
        }
        else if (strcmp(argv[1], "-e") == 0)                                    // if user inputs -e flag
        {
                int i = 0;                                                      // index

                if (file)                                                       // if file exists
                {
                        while ((c = getc(file)) != EOF)                         // go through each char in file...
                        {
                                endian[i] = c & 255;                            // put hex version in endian[]
                                i++;
                        }

                        for (int i = 0; i < 132; i += 4)                        // convert to hex and print out little endian format
                        {
                                printf("%02x", endian[i + 3] & 255);
                                printf("%02x", endian[i + 2] & 255);
                                printf("%02x", endian[i + 1] & 255);
                                printf("%02x", endian[i] & 255);
                                printf(" ");
                        }

                        printf("%02x", endian[134] & 255);                      // the rest
                        printf("%02x", endian[133] & 255);
                        printf("%02x", endian[132] & 255);
                }
                else                                                            // if file does not exist
                {
                        printf("A file under that name does not exist.\n");
                }

                printf("\n");
        }
        else if (strcmp(argv[1], "-u") == 0)                                    // if user inputs -u flag
        {
                int count = 1;                                                  // tracking for printing

                if (file)                                                       // if file exists
                {
                        while ((c = getc(file)) != EOF)                         // go through each char in file...
                        {
                                printf("%02X", c);                              // capital x for capital hex
                                count++;                                        // increment

                                if (count == 3)                                 // for spacing between hex
                                {
                                        printf(" ");                            // space
                                        count = 1;                              // reset
                                }
                        }
                }
                else                                                            // if file does not exist
                {
                        printf("A file under that name does not exist.\n");
                }
                printf("\n");
        }
        else                                                                    // user inputs invalid flags
        {
                printf("Please input -p, -b, -C, -e, or -u.\n");
        }

        fclose(file);                                                           // close file

        return 0;                                                               // return
}
