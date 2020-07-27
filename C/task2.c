#include "json-parser/json.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#define BUFFER_SIZE 1048576
#define EPS 0.000001

double dot_product(double x, double y, double xx, double yy, double xxx, double yyy) {
    return (xx - x) * (xxx - x) + (yy - y) * (yyy - y);
}

double cross_product(double x, double y, double xx, double yy, double xxx, double yyy) {
    return (xx - x) * (yyy - y) - (xxx - x) * (yy - y);
}

double dist_point_point(double x, double y, double xx, double yy) {
    return sqrt(dot_product(x, y, xx, yy, xx, yy));
}

double dist_point_line(double x, double y, double line_x, double line_y, double line_xx, double line_yy) {
    return abs(cross_product(x, y, line_x, line_y, line_xx, line_yy)) / dist_point_point(line_x, line_y, line_xx, line_yy);
}

int is_inside_shape(int x, int y, int shape_r, int shape_x, int shape_y, int shape_xx, int shape_yy) {
    if(dist_point_point(x, y, shape_x, shape_y) <= shape_r + EPS) {
        return 1;
    }
    if(dist_point_point(x, y, shape_xx, shape_yy) <= shape_r + EPS) {
        return 1;
    }
    if(dot_product(shape_x, shape_y, shape_xx, shape_yy, x, y) + EPS >= 0 && dot_product(shape_xx, shape_yy, shape_x, shape_y, x, y) + EPS >= 0 && dist_point_line(x, y, shape_x, shape_y, shape_xx, shape_yy) <= shape_r + EPS) {
        return 1;
    }
    return 0;
}

void read_input(int*** geometric_shapes, int* num_shapes, int* sizex, int* sizey, FILE* fp) {
    char* buffer;
    int read_len;
    json_value* root;
    json_value* value;
    json_value* value1;

    buffer = (char*)malloc(BUFFER_SIZE);
    read_len = fread(buffer, 1, BUFFER_SIZE, fp);
    root = json_parse((json_char*)buffer, read_len);
    
    for(int i = 0; i < root->u.object.length; i++) {
        if(!strcmp(root->u.object.values[i].name, "sizex")) {
            *sizex = root->u.object.values[i].value->u.integer;
        }
        else if(!strcmp(root->u.object.values[i].name, "sizey")) {
            *sizey = root->u.object.values[i].value->u.integer;
        }
        else {
            value = root->u.object.values[i].value;
            *num_shapes = value->u.array.length;
            *geometric_shapes = (int**)malloc(value->u.array.length * sizeof(int*));
            for(int j = 0; j < value->u.array.length; j++) {
                value1 = value->u.array.values[j];
                (*geometric_shapes)[j] = (int*)malloc(value1->u.array.length * sizeof(int));
                for(int k = 0; k < value1->u.array.length; k++) {
                    (*geometric_shapes)[j][k] = value1->u.array.values[k]->u.integer;
                }
            }
        }
    }

    free(buffer);
    json_value_free(root);
}

void initialize_spread_matrix(int*** spread_matrix, int sizex, int sizey) {
    *spread_matrix = (int**)malloc(sizex * sizeof(int*));
    for(int i = 0; i < sizex; i++) {
        (*spread_matrix)[i] = (int*)malloc(sizey * sizeof(int));
    }
}

void create_spread_matrix(int** spread_matrix, int** geometric_shapes, int num_shapes, int sizex, int sizey) {
    int* shape;

    for(int i = 0; i < sizex; i++) {
        for(int j = 0; j < sizey; j++) {
            spread_matrix[i][j] = 0;
        }
    }

    for(int ishape = 0; ishape < num_shapes; ishape++) {
        shape = geometric_shapes[ishape];
        for(int i = 0; i < sizex; i++) {
            for(int j = 0; j < sizey; j++) {
                if(is_inside_shape(i, j, shape[0], shape[1], shape[2], shape[3], shape[4])) {
                    spread_matrix[i][j] = 1;
                }
            }
        }
    }
}

void write_output(int** spread_matrix, int sizex, int sizey, FILE* fp) {
    fprintf(fp, "{\"spread_matrix\":[");
    for(int i = 0; i < sizex; i++) {
        fprintf(fp, "[");
        for(int j = 0; j < sizey; j++) {
            fprintf(fp, "%d", spread_matrix[i][j]);
            if(j + 1 < sizey) {
                fprintf(fp, ",");
            }
        }
        fprintf(fp, "]");
        if(i + 1 < sizex) {
            fprintf(fp, ",");
        }
    }
    fprintf(fp, "]}\n");
}

void free_memory(int** geometric_shapes, int num_shapes, int** spread_matrix, int sizex) {
    for(int i = 0; i < num_shapes; i++) {
        free(geometric_shapes[i]);
    }
    free(geometric_shapes);
    for(int i = 0; i < sizex; i++) {
        free(spread_matrix[i]);
    }
    free(spread_matrix);
}

int main() {
    int** geometric_shapes;
    int num_shapes;
    int sizex;
    int sizey;
    int** spread_matrix;

    read_input(&geometric_shapes, &num_shapes, &sizex, &sizey, stdin);
    initialize_spread_matrix(&spread_matrix, sizex, sizey);
    create_spread_matrix(spread_matrix, geometric_shapes, num_shapes, sizex, sizey);
    write_output(spread_matrix, sizex, sizey, stdout);
    free_memory(geometric_shapes, num_shapes, spread_matrix, sizex);

    return 0;
}