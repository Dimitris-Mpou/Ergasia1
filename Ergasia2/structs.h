struct vec{
    char id[64];
    double *coord;
	char isMedoid;
	struct vec *nearest_centroid;
};
