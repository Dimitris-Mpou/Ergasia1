struct curve{
	int id;
	int noPoints;
	struct point *points;
};

struct point{
	double x;
	double y;
};

struct dtw_cell{
	double value;
	struct dtw_cell *previous;
};
