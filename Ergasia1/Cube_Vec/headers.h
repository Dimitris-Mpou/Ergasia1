struct vec{
    int id;
    int *coord;
};

struct h_func{
	int h_sum;
	int *s;
};

struct list_node{
	unsigned int g;
	int vec_pos;
	struct list_node *next;
};

struct projection{
	unsigned int *g;
	int *f;
}; 
