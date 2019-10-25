int count_curves(char *);
int count_points(char *, struct curve *);
void save_input(char *, struct curve *);
double euclidean(struct point, struct point);
double dtw(struct curve, struct curve);
struct dtw_cell *min_neighbour(struct dtw_cell *, struct dtw_cell *, struct dtw_cell *);
double count_d(struct curve *, int);
