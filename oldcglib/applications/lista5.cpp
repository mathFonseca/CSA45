#include <dcel.h>
#include <geo.h>

// For randomize numbers
#include <cstdlib>
#include <ctime>


    
/* Gera um número aleatório. Scale pode ser usada para determinar o tamanho do número gerado
*/

double randomNumber(int scale)
{
    double number;
    //srand(time(NULL));
    number = rand() % scale;
    return number;
}
/* fazer dinamicamente*/
void generateNumber(int n_points)
{
    for(int i=0; i < n_points; i++)
    {
        vector_points[i] = randomNumber(513);
    }
}