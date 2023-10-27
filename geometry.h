#include <stdbool.h>

typedef struct Point{
	double x, y;
} Point;
typedef struct Color{
	int r, g, b, a;
} Color;
typedef struct Vertex{
	Point coord;
	Color col;
	double speed;
	double dir;
} Vertex;
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

/*két pont komparátor: először x majd y alapján rendezi*/
bool gt(Point a, Point b);
/*pontok ekvivalenciáját vizsgálja (x és y koordinátájuk is megegyezik-e) */
bool eqPoint(Point p1, Point p2);
/*VertEdgek ekvivalenciáját vizsgálja*/
bool eqEdge(VertEdge e1, VertEdge e2);
/*VertTrianglek ekvivalenciáját vizsgálja*/
bool eqTriangle(VertTri t1, VertTri t2);

/*VertTri konstruktor három Vertex pointerből: x majd y alapján sorba rendezi őket*/
VertTri newTri(Vertex *a, Vertex *b, Vertex *c);
/*VertEdge konstruktor két Vertex pointerből: x majd y alapján sorba rendezi őket,
alapértelmezetten invalid hamis*/
VertEdge newEdge(Vertex *a, Vertex *b);

/*adott vertex a háromszög potnjai között van-e és ha igen, melyik helyen*/
int point_in_tri(Point a, VertTri tri);
/*adott pont benne van-e egy háromszög körülírt körében*/
bool point_in_circumscribed(Point p, VertTri tri);

/*két pont közötti távolság négyzete*/
double dist2(Point a, Point b);

/*két vektor skalárszorzata*/
int dotProduct(Point a, Point b);
