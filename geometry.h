#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <stdbool.h>
#include <SDL2/SDL.h>

/*pont struktúra*/
typedef struct Point{
	double x, y;
} Point;
/*egy mező középpontját adó vertex struktúra*/
typedef struct Vertex{
	Point coord;
	int col;
	double speed;
	double dir;
} Vertex;
/*vertexek listája*/
typedef struct VertList{
	Vertex *list;
	int len;
} VertList;
/*grafikus megjelenésben látható színek*/
typedef struct Palette{
	SDL_Color bckgr, btn, dark, grey, pauseArrow;
	SDL_Color fields[5];
} Palette;
/*egy Vertex pointerekből háromszög és a körülírt körének középponja
az a,b,c pontok x majd y koordinátájuk alapján rendezve vannak*/
typedef struct VertTri{
	Vertex *a, *b, *c;
	Point center;//circumcenter
} VertTri;
/*egy Vertex pointerekből összekötő él, a és b Vertex az x és y koordinátájuk
alapján rendezve vannak*/
typedef struct VertEdge{
	Vertex *a, *b;
	bool invalid;
} VertEdge;

/*két pont komparátor: először x majd y alapján rendezi
paraméter(ek): összahasonlítandó pontokat
visszatérési érték: true ha a>b, különben false*/
bool gt(Point a, Point b);

/*pontok ekvivalenciáját vizsgálja (x és y koordinátájuk is megegyezik-e)
paraméter(ek): összahasonlítandó pontokat
visszatérési érték: a pontok egyenlőek-e*/
bool eqPoint(Point p1, Point p2);

/*VertEdgek ekvivalenciáját vizsgálja
paraméter(ek): összahasonlítandó élek
visszatérési érték: az élek egyenlőek-e*/
bool eqEdge(VertEdge e1, VertEdge e2);

/*VertTrianglek ekvivalenciáját vizsgálja
paraméter(ek): összahasonlítandó háromszögek
visszatérési érték: a háromszögek egyenlőek-e*/
bool eqTriangle(VertTri t1, VertTri t2);

/*VertTri konstruktor három Vertex pointerből: x majd y alapján sorba rendezi őket
paraméter(ek): háromszöget alkotó vertexekre mutató pointerek
visszatérési érték: az új háromszög*/
VertTri newTri(Vertex *a, Vertex *b, Vertex *c);

/*VertEdge konstruktor két Vertex pointerből: x majd y alapján sorba rendezi őket,
alapértelmezetten invalid mező hamis
paraméter(ek): élez alkotó vertexekre mutató pointerek
visszatérési érték: az új él*/
VertEdge newEdge(Vertex *a, Vertex *b);

/*adott vertex a háromszög potnjai között van-e és ha igen, melyik helyen
paraméter(ek): a vizsgálandó pont és háromszög
visszatérési érték: 0, 1, 2, 3
0 ha a pont nem eleme a háromszögnek
1 ha a pont a háromszög a mezőjével egyenlő
2 ha a pont a háromszög b mezőjével egyenlő
3 ha a pont a háromszög c mezőjével egyenlő*/
int point_in_tri(Point a, VertTri tri);

/*adott pont benne van-e egy háromszög körülírt körében
paraméter(ek): a vizsgálandó pont és háromszög
visszatérési érték: true ha benne van a körülírt körében, különben false */
bool point_in_circumscribed(Point p, VertTri tri);

/*két pont közötti távolság négyzete
paraméter(ek): a vizsgálandó pontok
visszatérési érték: a két pont közötti távolság négyzete*/
double dist2(Point a, Point b);

/*két vektor skalárszorzata
paraméter(ek): a vizsgálandó kétdimenziós vektorok
visszatérési érték: a két vektor skalárszorzata*/
int dotProduct(Point a, Point b);

#endif
