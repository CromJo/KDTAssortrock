/*
    *
   ***
  *****
 *******
*********
 *******
  *****
   ***
    *
*/

#include <iostream>>

int main()
{
    char star = '*';

    int input;
    std::cin >> input;
    int repeat = input;

    for (int i = 0; i < input; i++)
    {
        int cycle = input * 2;

        for (int j = 0; j < repeat; j++)
        {
            std::cout << " ";
            
        }
        
        for (int j = 0; j < cycle; j++)
        {
            if(j >= repeat -1)
                std::cout << "*";
            else

        }
        
        std::cout << std::endl;

        repeat--;
    }

    return 0;
}