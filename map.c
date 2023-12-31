#include "map.h"

/*beírja a paraméterként kapott tömb első négy helyére a négy sarokpontot (tehát
a kapott tömbnek min 4 hosszúnak kell lennie)*/
static void genCornerVertice(Vertex *vertice){
	vertice[0] = (Vertex){
		.coord =(Point){0,0},
		.col = 0,
		.speed = 0,
		.dir = 0
	};
	vertice[1] = (Vertex){
		.coord = (Point){mapWidth, 0},
		.col = 0,
		.speed = 0,
		.dir = 0
	};
	vertice[2] = (Vertex){
		.coord = (Point){0, mapHeight},
		.col = 0,
		.speed = 0,
		.dir = 0
	};
	vertice[3] = (Vertex){
		.coord = (Point){mapWidth,mapHeight},
		.col = 0,
		.speed = 0,
		.dir = 0
	};
}

/*kitölti a paraméterként megkapott vertice tömböt, összesen vertNum elemmel*/
void genVertice(VertList *vertice, int vertNum){//vertnum minumum 4-et kell!
	Vertex *vs = (Vertex*)malloc(vertNum * sizeof(Vertex));
	if (vs == NULL) {
		printf("Nem sikerült létrehozn a mezők középpontjait\n");
		exit(1);
	}
	genCornerVertice(vs);
	double minspeed = sqrt(pow(mapWidth,2)+ pow(mapHeight,2)) / 7000000;
	double maxspeed = sqrt(pow(mapWidth,2)+ pow(mapHeight,2)) / 400000;
	for (int i = 4; i < vertNum; i++) {//négy sarokpontot kihagyva
		vs[i] = (Vertex){
			.coord =(Point){randInt(0, mapWidth), randInt(0, mapHeight)},
			.col = 0,
			.speed = randDouble(minspeed, maxspeed, 4),
			.dir = randDouble(0, 2*M_PI, 4)
		};
	}
	free(vertice->list);
	vertice->list = vs;
	vertice->len = vertNum;
}

/*kiveszi azon élek minden duplikátumát, amelyek legalább kétszer szerepelnek*/
static void rmvDoubles(EdgeLinkedList *ebuff){
	EdgeChain *current1 = ebuff->first;
	while (current1 != NULL) {
		EdgeChain *next1 = current1->next;
		bool duplicate = false;
		//külön lekezelem, hogy közvetlen a mostani él mögött van-e a duplikátum
		while (next1 != NULL && eqEdge(current1->e, next1->e)) {
			EdgeChain *newNext = next1->next;
			rmvfromELinked(ebuff, next1);
			duplicate = true;
			next1 = newNext;
		}
		EdgeChain *current2 = next1;
		while (current2 != NULL) {
			EdgeChain *next2 = current2->next;
			if (eqEdge(current1->e, current2->e)){
				rmvfromELinked(ebuff, current2);
				duplicate = true;
			}
			current2 = next2;
		}
		if (duplicate) {
			rmvfromELinked(ebuff, current1);
		}
		current1 = next1;
	}
}

/*egy új a adott pontra módosítja, kibővíti a triangulációt*/
static void addVertex(Vertex *v, TriLinkedList *triangles){
	EdgeLinkedList edgebuffer = {NULL, NULL, 0};
	TriChain *current = triangles->first;
	while (current != NULL) {
		VertTri tri = current->tri;
		TriChain *next = current->next;
		if (pointInCircumscribed(v->coord, tri)) {
			addToELinked(&edgebuffer, newEdge(tri.a, tri.b));
			addToELinked(&edgebuffer, newEdge(tri.a, tri.c));
			addToELinked(&edgebuffer, newEdge(tri.b, tri.c));
			rmvfromTriLinked(triangles, current);
		}
		current = next;
	}
	rmvDoubles(&edgebuffer);
	EdgeChain *currentE = edgebuffer.first;
	while (currentE != NULL) {
		VertEdge e = currentE->e;
		addToTriLinked(triangles, newTri(e.a, e.b, v));
		currentE = currentE->next;
	}
	delELinked(&edgebuffer);
}

/*létrehozza a delaunay triangulácíót egy láncolt listába, amit a hívónak kell
felszabadítania (a visszatérési értéke a listára mutató pointer struct)*/
static TriLinkedList delaunay(VertList vertice){
	//reference: https://www.codeguru.com/cplusplus/delaunay-triangles/
	//szuperháromszögek létrehozása a négy sarokpontból
	Vertex *vs = vertice.list;
	TriLinkedList triangles = {NULL, NULL, 0};
	addToTriLinked(&triangles, newTri(&vs[0], &vs[1], &vs[2]));
	addToTriLinked(&triangles, newTri(&vs[1], &vs[2], &vs[3]));
	//a pontokat sorra "hozzáadjuk" a triangulációhoz
	for (int i = 4; i < vertice.len; i++) {
		addVertex(&vs[i], &triangles);
	}
	return triangles;
}

/*eltávolítja a láncolt listából az invalidnak jelölt éleket*/
static void rmvInvalids(EdgeLinkedList *edges) {
	EdgeChain *current = edges->first;
	while (current != NULL) {
		EdgeChain *next = current->next;
		if (current->e.invalid) {
			rmvfromELinked(edges, current);
		}
		current = next;
	}
}

/*hozzáfűz egy elemet az edge listához úgy, hogy az egyforma elemek vagy mind invalidak
vagy egyikük sem (tehát ha az új elem invalid akkor minden korábbi elemet invalidra
állít, ha nem invalid, de van más invalid, akkor az új elemet is invalidként adja hozzá)*/
static void keepInvalidAdd(EdgeLinkedList *edges, VertEdge new){
	EdgeChain *current = edges->first;
	if (new.invalid) {//végig kell mennünka teljes listán
		while (current != NULL) {
			if (eqEdge(current->e, new)) {
				current->e.invalid = true;
			}
			current = current->next;
		}
	} else {//elég az első invalidig menni, ilyenkor már invalidra állíthatjuk
		while (current != NULL) {
			if (current->e.invalid && eqEdge(current->e, new)) {
				new.invalid = true;
				addToELinked(edges, new);
				return;
			}
			current = current->next;
		}
	}
	addToELinked(edges, new);
}

/*ha egy háromszög körülírt középponja a térképen kívül van, akkor megnézi melyik
a "rossz" éle, tehát melyik két mező nem szomszédos valójában
Megj.: felhasználja azt, hogy a háromszögek csúcsai mind a térképen belül vannak,
így a "rossz" és mindig a tompaszöggel szembeni*/
static int badEdge(VertTri tri){
	Point va = {tri.a->coord.x-tri.center.x, tri.a->coord.y-tri.center.y};
	Point vb = {tri.b->coord.x-tri.center.x, tri.b->coord.y-tri.center.y};
	Point vc = {tri.c->coord.x-tri.center.x, tri.c->coord.y-tri.center.y};
	int ab = dotProduct(va, vb);
	int ac = dotProduct(va, vc);
	int bc = dotProduct(vb, vc);
	int m = min2(ab, min2(ac, bc));
	if (m==ab)
		return 0;
	if (m==ac)
		return 1;
	if (m==bc)
		return 2;
	return -1; //error kód
}

/*elkészíti a a végső szomszédsági gráfot, tehát megnézi, hogy a mezők valójában
csak a térképen kívűl, vagy valóban érintkeznek-e*/
static EdgeLinkedList finalEdges(TriLinkedList triangles){
	EdgeLinkedList edges = {NULL, NULL, 0};
	TriChain *currentTri = triangles.first;
	while (currentTri != NULL) {
		VertTri tri = currentTri->tri;
		VertEdge triEdges[3] = {
			newEdge(tri.a, tri.b),
			newEdge(tri.a, tri.c),
			newEdge(tri.b, tri.c)
		};
		//a képernyőn belül van-e a hszög körülírt középponja
		if (!(0<tri.center.x && tri.center.x<mapWidth && 0<tri.center.y && tri.center.y<mapHeight)){
			triEdges[badEdge(tri)].invalid = true;
		}
		for (int i = 0; i < 3; i++) {
			keepInvalidAdd(&edges, triEdges[i]);
		}
		currentTri = currentTri->next;
	}
	rmvInvalids(&edges);
	return edges;
}

void moveVertice(VertList vertice, int dt){
	for (int i = 0; i < vertice.len; i++) {
		Vertex v = vertice.list[i];
		Point newCoord = {
			.x = v.coord.x + cos(v.dir)*v.speed*dt,
			.y = v.coord.y + sin(v.dir)*v.speed*dt
		};
		double newDir;
		if (newCoord.x<=0 || newCoord.x>=mapWidth || newCoord.y<=0 || newCoord.y>=mapHeight) {
			newCoord.x = v.coord.x;
			newCoord.y = v.coord.y;
			newDir = v.dir - M_PI;
		} else {
			newDir = v.dir + randDouble(-0.05, 0.05, 5);
		}
		vertice.list[i].coord = newCoord;
		vertice.list[i].dir = newDir;
	}
}

int recolorField(Point click, VertList vertice, int col){
	int miniIdx = 0;
	click.x = click.x - mapOffset;
	click.y = click.y - mapOffset;
	double min = dist2(vertice.list[0].coord, click);
	for (int i = 1; i < vertice.len; i++) {
		double d = dist2(vertice.list[i].coord, click);
		if (d < min) {
			min = d;
			miniIdx = i;
		}
	}
	int prevcol = vertice.list[miniIdx].col;
	vertice.list[miniIdx].col = col;
	if (prevcol == 0 && col != 0) {//semlegesről színesre
		return -1;
	} else if (prevcol != 0 && col == 0){//színesről semlegesre
		return 1;
	}
	return 0;
}

bool correctMap(const VertList vertice){
	TriLinkedList triangles = delaunay(vertice);
	EdgeLinkedList edges = finalEdges(triangles);
	EdgeChain *current = edges.first;
	while (current != NULL) {
		if (current->e.a->col == current->e.b->col) {
			delTriLinked(&triangles);
			delELinked(&edges);
			return false;
		}
		current = current->next;
	}
	delTriLinked(&triangles);
	delELinked(&edges);
	return true;
}
