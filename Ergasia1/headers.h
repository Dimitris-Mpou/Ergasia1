struct vec{
    int id;
    int *coord;
};

struct h_func{
	int h_sum;
	int *s;
};

struct list_node{
	int g;
	int vec_pos;
	struct list_node *next;
};
