#include <string.h>
#include <stdlib.h>

typedef struct{
	char *model;
	int year;
	int cost;

}Car;
int Car_setModel(Car *car,const char *new_model){
	free(car->model);
	car-> model = strdup(new_model);
	if (!car->model) return 1;
	return 0;
}
*char Car_getModel(Car *car){
        return car-> model;
}
int Car_setYear(Car *car,int new_year){
	car->year = new_year;
	return 0;
}
int Car_getYear(Car *car){
        return car->year;
}
int Car_setCost(Car *car,int new_cost){
        car->cost = new_cost;
        return 0;
}
int Car_getCost(Car *car){
	return car->cost;
}

