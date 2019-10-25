int count_curves(char *);
void count_points(char *, struct curve *);
void save_input(char *, struct curve *);
double dtw(struct curve, struct curve);
struct dtw_cell *min_neighbour(struct dtw_cell *, struct dtw_cell *, struct dtw_cell *);
double euclidean(struct point, struct point);
