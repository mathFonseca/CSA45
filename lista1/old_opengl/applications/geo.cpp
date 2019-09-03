#include "geo.h"
#include <math.h>

/* 
* Ao acessar uma estrutura de dados por ponteiro, usamos -> ao invés de ponto.
* Exemplo:
* Acesso por ponteiro normal: ponteiro.valor
* Acesso por ponteiro (struct): ponteiro->valor
*/

point_2d point(double x, double y)
{
    point_2d ponto;
    ponto.x = x;
    ponto.y = y;
    return ponto;
}

point_2d vector(point_2d ponto_1, point_2d ponto_2)
{
    point_2d vetor;
    vetor.x = ponto_1.x - ponto_2.x;
    vetor.y = ponto_1.y - ponto_2.y;
    return vetor;
}

point_2d soma_vetores(point_2d vetor_1, point_2d vetor_2)
{
    /*
    *   u + v = (u.x + v.x, u.y + v.y)
    */ 
    point_2d resp;
    resp.x = vetor_1.x + vetor_2.x;
    resp.y = vetor_1.y + vetor_2.y;
    return resp;
}

double produto_interno(point_2d vetor_1, point_2d vetor_2)
{
    /*
    *   u * v = (u.x * v.x + u.y * v.y)
    */
    double resp = 0;
    resp = (vetor_1.x * vetor_2.x);
    resp += (vetor_1.y * vetor_2.y);
    return resp;
}

point_2d produto_vetorial(point_2d vetor_1, point_2d vetor_2)
{
    /*
    *   u x v = (u.x * v.y - u.y * v.x) apontando para z
    *   No caso, como estamos trabalhando com pontos em 2D,
    *   O retorno dessa função está usando a mesma magnitude, usando o eixo x.
    */ 
    point_2d resp;
    resp.x = vetor_1.x * vetor_2.y;
    resp.x += vetor_1.y * vetor_2.x;
    return resp;
}

double area_triangulo_unsigned(point_2d ponto_1, point_2d ponto_2, point_2d ponto_3)
{
    double area = ( ( (ponto_2.x - ponto_1.x) * (ponto_3.y - ponto_1.y) )
             - ( (ponto_3.x - ponto_1.x) * (ponto_2.y - ponto_1.y)) )/2;
    
    return area = (area>0) ? area : area*(-1);
}

double area_triangulo_signed(point_2d ponto_1, point_2d ponto_2, point_2d ponto_3)
{
    double area = ( ( (ponto_2.x - ponto_1.x) * (ponto_3.y - ponto_1.y) )
             - ( (ponto_3.x - ponto_1.x) * (ponto_2.y - ponto_1.y)) )/2;
    
    return area;
}

// 1 se a esquerda. 0 caso contrário
bool left(point_2d ponto_1, point_2d ponto_2, point_2d ponto_3)
{
    double area;

    area = ( ( (ponto_2.x - ponto_1.x) * (ponto_3.y - ponto_1.y) )
             - ( (ponto_3.x - ponto_1.x) * (ponto_2.y - ponto_1.y)) )/2;

    return (area > 0) ? true : false;
}

// 1 se a esquerda ou em cima da reta. 0 caso contrário
bool leftOn(point_2d ponto_1, point_2d ponto_2, point_2d ponto_3)
{
    double area;

    area = ( ( (ponto_2.x - ponto_1.x) * (ponto_3.y - ponto_1.y) )
             - ( (ponto_3.x - ponto_1.x) * (ponto_2.y - ponto_1.y)) )/2;

    return (area>=0) ? true : false;
}

// 1 somente se em cima da reta. 0 caso contrário.
bool collinear(point_2d ponto_1, point_2d ponto_2, point_2d ponto_3)
{
    double area;

    area = ( ( (ponto_2.x - ponto_1.x) * (ponto_3.y - ponto_1.y) )
             - ( (ponto_3.x - ponto_1.x) * (ponto_2.y - ponto_1.y)) )/2;

    return (area == 0) ? true : false;
}

bool intersection(point_2d ponto_1, point_2d ponto_2, point_2d ponto_3, point_2d ponto_4)
{
    // Checa intersecções impróprias
    bool between_12_3 = between(ponto_1, ponto_2, ponto_3);
    bool between_12_4 = between(ponto_1, ponto_2, ponto_4);

    if(between_12_3 == false && between_12_4 == false)
    {
        // Não existe impropriedade. Checa intersecção própria
        bool resposta_12_34 ( left(ponto_1, ponto_2, ponto_3) ^ left(ponto_1, ponto_2, ponto_4) ) ? true : false;
        bool resposta_34_12 ( left(ponto_3, ponto_4, ponto_1) ^ left(ponto_3, ponto_4, ponto_2) ) ? true : false;
        
        return (resposta_12_34 == resposta_34_12) ? true : false;
    }
    else if(between_12_3 == true)
    {

    }
    else if(between_12_4 == true)
    {
        
    }
}

bool between(point_2d ponto_1, point_2d ponto_2, point_2d ponto_3)
{
    bool resp = collinear(ponto_1, ponto_2, ponto_3);
    if (resp == false)
        return false;
    else
    {
        if((ponto_1.x < ponto_3.x && ponto_3.x < ponto_2.x) && (ponto_1.y < ponto_3.y && ponto_3.y < ponto_2.y) )
            return true;
    }
    
}

bool intersection_full()