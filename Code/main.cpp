#include "bwt.h"
#include "lz77.h"

int main()
{
    unsigned int choice = 1;
    std::string filename{"files/bibleline.txt"};

    /// MENU ///
    while(choice > 0 && choice < 4) {
        std::cout << "What do you want to do ?" << std::endl
                  << "1) Change file  -  Current file: " << filename << std::endl
                  << "2) LZ77: Lempel-Ziv 1977" << std::endl
                  << "3) BWT: Burrows-Wheeler Transform" << std::endl
                  << "Else) Quit" << std::endl
                  << ">> ";

        std::cin >> choice;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch(choice) {
            case 1:
                changeFile(filename);
                break;
            case 2:
                lz77(filename);
                break;
            case 3:
                BWT(filename);
                break;
            default:
                std::cout << std::endl << "Bye !";
        }

        std::cout << std::endl << std::endl;
    }

    return 0;
}
