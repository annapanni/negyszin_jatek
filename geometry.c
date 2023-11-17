#include "geometry.h"

/*két pont komparátor: először x majd y alapján rendezi*/
bool gt(Point a, Point b){
	return (a.x>b.x) || (a.x==b.x && a.y>b.y);
}
/*pontok ekvivalenciáját vizsgálja (x és y koordinátájuk is megegyezik-e) */
bool eqPoint(Point p1, Point p2){
	return p1.x==p2.x && p1.y==p2.y;
}
/*VertEdgek ekvivalenciáját vizsgálja*/
bool eqEdge(VertEdge e1, VertEdge e2){
	//mivel edge oldalai rendezve vannak
	return eqPoint(e1.a->coord, e2.a->coord) && eqPoint(e1.b->coord, e2.b->coord);
}
/*VertTrianglek ekvivalenciáját vizsgálja*/
bool eqTriangle(VertTri t1, VertTri t2){
	return eqPoint(t1.a->coord, t2.a->coord) && eqPoint(t1.b->coord, t2.b->coord)
	 && eqPoint(t1.c->coord, t2.c->coord);
}
/*visszaadja az a,b,c pontok által meghatározott háromszög körülírt körének középponját*/
Point circumCenter(Point a, Point b, Point c){
	double cx, cy;
	if (a.y-b.y == 0){
		double m = -1* (a.x-c.x)/(a.y-c.y);
		double b1 = (a.y+c.y)/2 - m*((a.x+c.x)/2);
		cx = (a.x+b.x)/2;
		cy = m*cx+b1;
	} else if (a.y-c.y == 0){
		double m = -1* (a.x-b.x)/(a.y-b.y);
		double b1 = (a.y+b.y)/2 - m*((a.x+b.x)/2);
		cx = (a.x+c.x)/2;
		cy = m*cx+b1;
	} else {
		double m1 = -1* (a.x-b.x)/(a.y-b.y);
		double m2 = -1* (a.x-c.x)/(a.y-c.y);
		double b1 = (a.y+b.y)/2 - m1*((a.x+b.x)/2);
		double b2 = (a.y+c.y)/2 - m2*((a.x+c.x)/2);
		cx = (b2-b1)/(m1-m2);
		cy = m1*cx + b1;
	}
	return (Point){cx, cy};
}

/*VertTri konstruktor három Vertex pointerből: x majd y alapján sorba rendezi őket*/
VertTri newTri(Vertex *a, Vertex *b, Vertex *c){
	Vertex *descending[3];
	if (gt(a->coord, b->coord)) {
		descending[0] = a;
		descending[1] = b;
	} else {
		descending[0] = b;
		descending[1] = a;
	}
	if (gt(descending[1]->coord, c->coord)) {
		descending[2] = c;
	} else if (gt(descending[0]->coord, c->coord)){
		descending[2] = descending[1];
		descending[1] = c;
	} else {
		descending[2] = descending[1];
		descending[1] = descending[0];
		descending[0] = c;
	}
	Point cc = circumCenter(descending[0]->coord, descending[1]->coord, descending[2]->coord);
	return (VertTri){descending[0], descending[1], descending[2], cc};
}

/*VertEdge konstruktor két Vertex pointerből: x majd y alapján sorba rendezi őket,
alapértelmezetten invalid hamis*/
VertEdge newEdge(Vertex *a, Vertex *b){
	if (gt(a->coord, b->coord)){
		return (VertEdge){b, a, false};
	} else {
		return (VertEdge){a, b, false};
	}
}

/*adott pont benne van-e egy háromszög körülírt körében*/
bool pointInCircumscribed(Point p, VertTri tri){
	double radius2 = dist2(tri.a->coord, tri.center);
	double pdist2 = dist2(p, tri.center);
	return pdist2 < radius2;
}
/*két pont közötti távolság négyzete*/
double dist2(Point a, Point b){
	return (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y);
}
/*két vektor skalárszorzata*/
int dotProduct(Point a, Point b){
	return a.x*b.x + a.y*b.y;
}
