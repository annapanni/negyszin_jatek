#include "file_management.h"

/*hívónak felszabadítani*/
void *getTop10(ResList *list){
	PlayerResult *top10 = (PlayerResult*)malloc(10*sizeof(PlayerResult));
	FILE* f = fopen("leaderboard.txt", "r");
	int readOK = fscanf(f, "%[^\t]\t%d:%d:%d\n", top10[0].name, &top10[0].t.min, &top10[0].t.sec, &top10[0].t.csec);
	int i = 1;
	while (readOK == 4 && i < 10) {
		readOK = fscanf(f, "%[^\t]\t%d:%d:%d\n", top10[i].name, &top10[i].t.min, &top10[i].t.sec, &top10[i].t.csec);
		i++;
	}
	fclose(f);
	list->len = i;
	list->results = top10;
}

int addToLeaderBoard(PlayerResult newres){
	FILE* f = fopen("leaderboard.txt", "r");
	if (f == NULL) { //ha nem létezett a fájl
		f = fopen("leaderboard.txt", "w");
		fprintf(f, "%s\t%d:%d:%d\n", newres.name, newres.t.min, newres.t.sec, newres.t.csec);
		fclose(f);
		return 0;
	}
	FILE* f_temp = fopen("lb_temp.txt", "w");
	PlayerResult line;
	int place = 0;
	bool found = false;
	while (!found && fscanf(f, "%[^\t]\t%d:%d:%d\n", line.name, &line.t.min, &line.t.sec, &line.t.csec)==4){
		if (compTime(newres.t, line.t) == -1) {
			found = true;
		} else {
			place += 1;
			fprintf(f_temp, "%s\t%d:%d:%d\n", line.name, line.t.min, line.t.sec, line.t.csec);
		}
	}
	fprintf(f_temp, "%s\t%d:%d:%d\n", newres.name, newres.t.min, newres.t.sec, newres.t.csec);
	if (found) {
		fprintf(f_temp, "%s\t%d:%d:%d\n", line.name, line.t.min, line.t.sec, line.t.csec);
	}
	//utána következők másolása
	while (fscanf(f, "%[^\t]\t%d:%d:%d\n", line.name, &line.t.min, &line.t.sec, &line.t.csec)==4){
		fprintf(f_temp, "%s\t%d:%d:%d\n", line.name, line.t.min, line.t.sec, line.t.csec);
	}
	//visszamásolás
	fclose(f);
	fclose(f_temp);
	rename("lb_temp.txt", "leaderboard.txt");
	return place;
}
