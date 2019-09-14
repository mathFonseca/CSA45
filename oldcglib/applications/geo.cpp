/* Autores das bibliotecas:
* Matheus Fonseca Alexandre de Oliveira
* <matheus.2016@alunos.utfpr.edu.br>
*/

/* Libraries */
#include "geo.h"
#include <math.h>

/* Defines */
#define PI 3.1415

/* Additional <personal> comments: 
* Ao acessar uma estrutura de dados por ponteiro, 
* usamos -> ao invés de ponto.
* Exemplo:
* Acesso por ponteiro normal: ponteiro.valor
* Acesso por ponteiro (struct): ponteiro->valor
*/

/* Funções */

point_2d c_Point(double x, double y)
{
    point_2d ponto;
    ponto.x = x;
    ponto.y = y;
    return ponto;
}

point_2d c_Vector(point_2d A, point_2d B)
{
    // Relembrando: um vetor u AB é formado por B-A
    point_2d vector;
    vector.x = B.x - A.x;
    vector.y = B.y - A.y;
    return vector;
}

// Soma os vetores u + v
point_2d sumVector(point_2d u, point_2d v)
{
    point_2d result;
    result.x = u.x + v.x;
    result.y = u.y + v.y;
    return result;
}

// Multiplicação de vetores u*v
double prodInterno(point_2d u, point_2d v)
{
    double result;
    result = u.x * v.x;
    result += u.y * v.y;
    return result;
}

/* Produto vetorial de u x v
*  Resultado é originalmente no eixo Z.
*  A função está retornando atualmente no eixo x 
*/
point_2d prodVetorial(point_2d u, point_2d v)
{
    point_2d result;
    result.x = (u.x * v.y) - (v.x * u.y);
    return result;
}

// Retorna area unsigned do triangulo formado pelos pontos ABC
double u_areaTriangle(point_2d A, point_2d B, point_2d C)
{
    // Utiliza o módulo do produto vetorial
    point_2d result;
    point_2d u;
    point_2d v;
    double valor;
    u = c_Vector(A, C); // C - A
    v = c_Vector(A, B); // B - A
    result = prodVetorial(u, v);
    valor = result.x;
    return (valor>0) ? valor/2 : (-1)*(valor/2);
}

// Retorna area signed do triangulo formado pelos pontos ABC
double s_areaTriangle(point_2d A, point_2d B, point_2d C)
{
    // utiliza o produto vetorial
    point_2d result;
    point_2d u;
    point_2d v;
    double valor;
    u = c_Vector(A, C); // C - A
    v = c_Vector(A, B); // B - A
    result = prodVetorial(u, v);
    valor = result.x;
    return valor;
}

// Retorna true se C está a left de AB. False se contrário
bool left(point_2d A, point_2d B, point_2d C)
{
    double area;
    area = ((B.x - A.x) * (C.y - A.y)) - ((C.x - A.x) * (B.y - A.y) );
    area = area/2;
    return (area > 0) ? true : false;
}

// Retorna true se C está a left/em cima de AB. False se contrário
bool leftOn(point_2d A, point_2d B, point_2d C)
{
    double area;
    area = ((B.x - A.x) * (C.y - A.y)) - ((C.x - A.x) * (B.y - A.y) );
    area = area/2;
    return (area >= 0) ? true : false;    
}

// Retorna true se C está em cima de AB. False se contrário
bool collinear(point_2d A, point_2d B, point_2d C)
{
    double area;
    area = ((B.x - A.x) * (C.y - A.y)) - ((C.x - A.x) * (B.y - A.y) );
    area = area/2;
    return (area == 0) ? true : false;        
}

// Retorna true se C está a em cima e entre de AB. False se contrário
bool between(point_2d A, point_2d B, point_2d C)
{
    // Primeiro checa se C é collinear em relação a reta AB
    if(collinear(A, B, C))
    {
        // Se a reta AB não for vertical, então verifica a coordenada x.
        if(A.x != B.x)
        {
            return ( ( (A.x <= C.x) && (C.x <= B.x) ) ||
                     ( (A.x >= C.x) && (C.x >= B.x) ) );
        }
        // Se a reta AB for vertical, então verifica a coordenada y.
        else
        {
            return ( ( (A.y <= C.y) && (C.y <= B.y) ) ||
                     ( (A.y >= C.y) && (C.y >= B.y) ) );
        }
    }
    else
    {
        return false;
    }    
}

void classifyVertex(polygon_2d Polygon);
double calculateAngle(point_2d A, point_2d B, point_2d C)
{
        // Vetores: AB e AC
    point_2d u, v;
    u.x = B.x - A.x;
    u.y = B.y = A.y;

    v.x = C.x - A.x;
    v.y = C.y - A.y;

    double modulo_AB = prodInterno(u, u);
    double modulo_AC = prodInterno(v, v);

    double aux = prodInterno(u,v);

    return (double)acos(aux / (modulo_AB * modulo_AC));
}
void windingNumber(); // Precisa de revisão
bool checkUpward(point_2d A, point_2d B)
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

/*  Classifica os vértices do polígono entre 5 categorias.
*   Regular, Split, Merge, Start, End
*/
void classifyVertexMonotonePolygon(polygon_2d * polygon)
{
    // Pontos usados, onde o vértice Pi é A, Pi-1 é B, Pi+1 é C.
    point_2d A;
    point_2d B;
    point_2d C;

    polygon_2d * polygon_aux = polygon->prev;

    while(polygon_aux != polygon)
    {
        A = polygon_aux->info;
        B = polygon_aux->prev->info;
        C = polygon_aux->next->info;

        if(!checkUpward(B, A) && !checkUpward(C, A) &&
             calculateAngle(A, B, C) < PI)
        {
            polygon->pointType = start;
        }
        else if(!checkUpward(B, A) && !checkUpward(C, A) &&
             calculateAngle(A, B, C) > PI)
        {
            polygon->pointType = split;
        }
        else if(checkUpward(B, A) && checkUpward(C, A) &&
             calculateAngle(A, B, C) < PI) 
        {
            polygon->pointType = end;
        }
        else if(checkUpward(B, A) && checkUpward(C, A) &&
             calculateAngle(A, B, C) > PI)
        {
            polygon->pointType = merge;
        }
        else
        {
            polygon->pointType = regular;
        }
        
        polygon_aux = polygon_aux->next;
    }
}

/*
Dizemos que um ponto p = (xp, yp) est´a abaixo de um ponto q = (xq, yq)
se yp < yq ou se yp = yq e xp > xq. Dado um pol´ıgono simples P = {p1, p2, . . . , pn},
escreva uma fun¸c˜ao que classifique um v´ertice pi em uma das seguintes categorias:
1. start: pi−1 e pi+1 est˜ao abaixo de pi e o ˆangulo interno em pi ´e menor que π;
2. split: pi−1 e pi+1 est˜ao abaixo de pi e o ˆangulo interno em pi ´e maior que π;
3. end: pi−1 e pi+1 est˜ao acima de pi e o ˆangulo interno em pi ´e menor que π;
4. merge: pi−1 e pi+1 est˜ao acima de pi e o ˆangulo interno em pi ´e maior que π;
5. regular: caso n˜ao seja nenhum dos anteriores.
Considerando que p1−1 = pn e pn+1 = p1.*/
// ==================================================================
/* Old Functions */
/* cria o ponto x,y
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

    point_2d resp;
    resp.x = vetor_1.x + vetor_2.x;
    resp.y = vetor_1.y + vetor_2.y;
    return resp;
}

// Calcula o produto interno dos vetores.
double produto_interno(point_2d vetor_1, point_2d vetor_2)
{

    double resp = 0;
    resp = (vetor_1.x * vetor_2.x);
    resp += (vetor_1.y * vetor_2.y);
    return resp;
}

// Calcula o produto vetorial dos vetores. Vetor resposta com coordenada em z.
point_2d produto_vetorial(point_2d vetor_1, point_2d vetor_2)
{

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
}

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
}*/