void count_input(char[256], int *, int *);
void save_input(char[256], struct vec *);
float average_dist(int, int, struct vec *);
int modulo_calc(int, int, int);
void factors(int, int, int, int *);
unsigned int concut(struct h_func *, int);
void hash(struct list_node **, int, int, int);
void lsh_train(struct vec *, struct h_func *, int *,int **, int, int, int, int, int);
void lsh_search(struct vec, struct h_func *, int *,int *, int, int, int, int);
int query_knn(int, int, struct vec *, struct vec, int *);
void write_output(char[256], int, struct vec *, struct vec *, int *, int *, int *, float *, float *);
void cube_train(int **, struct list_node ***, struct list_node **, int, int);
int cube_search(int *, struct list_node ***, struct list_node **, struct vec *, struct vec, int *, int, int, int, int);
void edges(int *, int *, int, int);
int count_edges(int, int, int *, int *, int, int, int);
