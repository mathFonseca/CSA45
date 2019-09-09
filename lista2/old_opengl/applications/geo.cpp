#include "geo.h"
#include <math.h>

#define PI 3.1415

/* 
* Ao acessar uma estrutura de dados por ponteiro, usamos -> ao invés de ponto.
* Exemplo:
* Acesso por ponteiro normal: ponteiro.valor
* Acesso por ponteiro (struct): ponteiro->valor
*/

// cria o ponto x,y
point_2d point(double x, double y)
{
    point_2d ponto;
    ponto.x = x;
    ponto.y = y;
    return ponto;
}

// cria o vetor AB (B - A)
point_2d vector(point_2d A, point_2d B)
{
    point_2d vetor;
    vetor.x = B.x - A.x;
    vetor.y = B.y - A.y;
    return vetor;
}

// Soma os vetores coordenada por coordenada
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

// Calcula o produto interno dos vetores.
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

// Calcula o produto vetorial dos vetores. Vetor resposta com coordenada em z.
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

double area_triangulo_unsigned(point_2d A, point_2d B, point_2d C)
{
    double area = ( ( (B.x - A.x) * (C.y - A.y) )
             - ( (C.x - A.x) * (B.y - A.y)) )/2;
    
    return area = (area>0) ? area : area*(-1);
}

double area_triangulo_signed(point_2d A, point_2d B, point_2d C)
{
    double area = ( ( (B.x - A.x) * (C.y - A.y) )
             - ( (C.x - A.x) * (B.y - A.y)) )/2;
    
    return area;
}

// 1 se a esquerda. 0 caso contrário
bool left(point_2d A, point_2d B, point_2d C)
{
    double area;
    area = ( ( (B.x - A.x) * (C.y - A.y) )
             - ( (C.x - A.x) * (B.y - A.y)) )/2;

    return (area > 0) ? true : false;
}

// 1 se a esquerda ou em cima da reta. 0 caso contrário
bool leftOn(point_2d A, point_2d B, point_2d C)
{
    double area;

    area = ( ( (B.x - A.x) * (C.y - A.y) )
             - ( (C.x - A.x) * (B.y - A.y)) )/2;

    return (area>=0) ? true : false;
}

// 1 somente se em cima da reta. 0 caso contrário.
bool collinear(point_2d A, point_2d B, point_2d C)
{
    double area;

    area = ( ( (B.x - A.x) * (C.y - A.y) )
             - ( (C.x - A.x) * (B.y - A.y)) )/2;

    return (area == 0) ? true : false;
}

bool intersectPropria(point_2d A, point_2d B, point_2d C, point_2d D)
{
    if(collinear(A, B, C) || collinear(A, B, D) || collinear(C, D, B) )
    {
        return false;
    }
    return ( ( (left(A, B, C)) ^ (left(A, B, D)) ) 
        &&   ( (left(C, D, A)) ^ (left(C, D, B)) ) );
}

bool between(point_2d A, point_2d B, point_2d C)
{
    if(!collinear(A, B, C))
        return false;
    if(A.x != B.x)
    {
        return ( ( (A.x <= C.x) && (C.x <= B.x) ) || 
                 ( (A.x >= B.x) && (C.x >= B.x) ) );
    }
    else
    {
        return ( ( (A.y <= C.y) && (C.y <= B.y) ) || 
                 ( (A.y >= C.y) && (C.y >= B.y) ) );
    }
                
}

bool intersect(point_2d A, point_2d B, point_2d C, point_2d D)
{
    if(intersecPropria(A, B, C, D))
        return true;
    else if(between(A, B, C) || between(A, B, D) ||
            between(C, D, A) || between(C, D, B))
        return true;
    else
        return false;
    
}

/*
bool intersectPolygon(point_2d A, point_2d B, polygon_2d *polygon )
{
    // realizar inteserc com cada reta do poligono?
    int i;
    bool resposta = true;
    for(i = 0; i < polygon->lenght && resposta == true ; i++)
    {
        if( i != (polygon->lenght - 1))
            resposta = intersec(polygon->vector[i], polygon->vector[i+1], A, B);
        else
            resposta = intersec(polygon->vector[i], polygon->vector[0], A, B);
    }

    return resposta;
}*/

void classifica_vertice(polygon_2d polygon)
{
    // Dado 3 pontos, aplica LeftOn
    polygon_2d polygon_aux = polygon->next;
    while(polygon_aux != polygon)
    {
        // A é o centro.
        point_2d A = polygon_aux.info;
        point_2d B = polygon_aux.prev->info;
        point_2d C = polygon_aux.next->info;

        // Classifica o vértice
        if(leftOn(A, B, C))
        {
            polygon_aux.type_of_angle = 0;
        }
        else
        {
            polygon_aux.type_of_angle = 1;
        }
        
        //Pega o próximo vértice.
        polygon_aux = polygon_aux->next;
    }
}

// Retorna angulo em graus de A.
float computa_angulo(point_2d A, point_2d B, point_2d C)
{
    // Vetores: AB e AC
    point_2d u, v;
    u = vector()
    u.x = B.x - A.x;
    u.y = B.y = A.y;

    v.x = C.x - A.x;
    v.y = C.y - A.y;

    double modulo_AB = produto_interno(u, u);
    double modulo_AC = produto_interno(v, v);

    double aux = produto_interno(u,v);

    return angle = acos(aux / (modulo_AB * modulo_AC));
}

// Retorna true se o poligono foi passado em anti horario. 0 se horario
double winding_number(polygon_2d polygon)
{
    double k;
    polygon_2d polygon_aux = polygon->next;
    while(polygon_aux != polygon)
    {
        // A é o centro.
        point_2d A = polygon_aux.info;
        point_2d B = polygon_aux.prev->info;
        point_2d C = polygon_aux.next->info;

        // Computa o angulo de A.
        k += computa_angulo(A, B, C);
        
        //Pega o próximo vértice.
        polygon_aux = polygon_aux->next;        
    }
    k = k/(2*PI);
    return (k>0) ? true : false;
}

// Retorna true se A está acima de B. False caso contrário
bool checkUpwardPoint(point_2d A, point_2d B)
{
    if(A.x > B.x)
    {
        if(A.y <= B.y)
        {
            return true;
        }

         return false;
    }
    else
    {
        return false;
    }
}

// Classifica os pontos do polígono
void classifyPoints(polygon_2d polygon)
{
    polygon_2d polygon_aux = polygon->next;
    while(polygon_aux != polygon)
    {
        // A é o centro. (pi). B é o pi-1 e C é o pi+1
        point_2d A = polygon_aux.info;
        point_2d B = polygon_aux.prev->info;
        point_2d C = polygon_aux.next->info;

        // Verifica se é start
        if( !checkUpwardPoint(B, A) && !checkUpwardPoint(C, A) && (computa_angulo(A, B, C) < PI ))
        {
            polygon_aux.pointType = start;
        }
        // Verifica se é split
        else if(!checkUpwardPoint(B, A) && !checkUpwardPoint(C, A) && (computa_angulo(A, B, C) > PI))  
        {
            polygon_aux.pointType = split;
        }
        // Verifica se é end
        else if(checkUpwardPoint(B, A) && checkUpwardPoint(C, A) && (computa_angulo(A, B, C) < PI)) 
        {
            polygon_aux.pointType = end;
        }
        // Verifica se é merge
        else if(checkUpwardPoint(B, A) && checkUpwardPoint(C, A) && (computa_angulo(A, B, C) > PI))   
        {
            polygon_aux.pointType = merge;
        }
        else    // É regular
        {
            polygon_aux.pointType = regular;   
        }        

        // Move para o próximo vértice
        polygon_aux = polygon_aux->next;
    }
}