void count_input(char[256], int *, int *);
void save_input(char[256], struct vec *);
float average_dist(int, int, struct vec *, int *);
int modulo_calc(int, int, int);
void factors(int, int, int, int *);
unsigned int concut(struct h_func *, int);
void hash(struct list_node **, int, int, int);
void lsh_train(struct vec *, struct h_func **, struct list_node ***, int *, int , int , int , int , int, int , int);
int lsh_search(struct vec *, struct vec, struct h_func **, struct list_node ***, int *, int, int, int, int, int, int, int);
