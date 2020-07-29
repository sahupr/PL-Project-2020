#include "json-parser/json.h"
#include <stdio.h>
#include <string.h>
#define BUFFER_SIZE 1048576

void read_input(int*** spread_matrix, int* sizex, int*sizey, int* startx, int* starty, int* endx, int* endy, FILE* fp) {
    char* buffer;
    int read_len;
    json_value* root;
    json_value* value;
    json_value* value1;

    buffer = (char*)malloc(BUFFER_SIZE);
    read_len = fread(buffer, 1, BUFFER_SIZE, fp);
    root = json_parse((json_char*)buffer, read_len);
    
    for(int i = 0; i < root->u.object.length; i++) {
        if(!strcmp(root->u.object.values[i].name, "startx")) {
            *startx = root->u.object.values[i].value->u.integer;
        }
        else if(!strcmp(root->u.object.values[i].name, "starty")) {
            *starty = root->u.object.values[i].value->u.integer;
        }
        else if(!strcmp(root->u.object.values[i].name, "endx")) {
            *endx = root->u.object.values[i].value->u.integer;
        }
        else if(!strcmp(root->u.object.values[i].name, "endy")) {
            *endy = root->u.object.values[i].value->u.integer;
        }
        else {
            value = root->u.object.values[i].value;
            *sizex = value->u.array.length;
            *spread_matrix = (int**)malloc(value->u.array.length * sizeof(int*));
            for(int j = 0; j < value->u.array.length; j++) {
                value1 = value->u.array.values[j];
                *sizey = value1->u.array.length;
                (*spread_matrix)[j] = (int*)malloc(value1->u.array.length * sizeof(int));
                for(int k = 0; k < value1->u.array.length; k++) {
                    (*spread_matrix)[j][k] = value1->u.array.values[k]->u.integer;
                }
            }
        }
    }

    free(buffer);
    json_value_free(root);
}

void initialize_path(int** pathx, int** pathy, int max_path_len) {
    *pathx = (int*)malloc(max_path_len * sizeof(int));
    *pathy = (int*)malloc(max_path_len * sizeof(int));
}

void find_path(int* pathx, int* pathy, int* path_len, int** spread_matrix, int sizex, int sizey, int startx, int starty, int endx, int endy) {
    int** parx;
    int** pary;
    int* queuex;
    int* queuey;
    int front;
    int back;
    int dirx[8] = {-1, -1, -1, 0, 1, 1, 1, 0};
    int diry[8] = {-1, 0, 1, 1, 1, 0, -1, -1};
    int x;
    int y;
    int xx;
    int yy;

    if(spread_matrix[startx][starty] || spread_matrix[endx][endy]) {
        *path_len = 0;
        return;
    }

    parx = (int**)malloc(sizex * sizeof(int*));
    pary = (int**)malloc(sizex * sizeof(int*));
    for(int i = 0; i < sizex; i++) {
        parx[i] = (int*)malloc(sizey * sizeof(int));
        pary[i] = (int*)malloc(sizey * sizeof(int));
        for(int j = 0; j < sizey; j++) {
            parx[i][j] = -1;
            pary[i][j] = -1;
        }
    }
    parx[endx][endy] = endx;
    pary[endx][endy] = endy;

    queuex = (int*)malloc(sizex * sizey * sizeof(int));
    queuey = (int*)malloc(sizex * sizey * sizeof(int));
    queuex[0] = endx;
    queuey[0] = endy;
    front = 0;
    back = 1;

    while(front < back) {
        x = queuex[front];
        y = queuey[front];
        front++;
        for(int i = 0; i < 8; i++) {
            xx = x + dirx[i];
            yy = y + diry[i];
            if(xx >= 0 && xx < sizex && yy >= 0 && yy < sizey && !spread_matrix[xx][yy] && parx[xx][yy] == -1) {
                parx[xx][yy] = x;
                pary[xx][yy] = y;
                queuex[back] = xx;
                queuey[back] = yy;
                back++;
            }
            if(parx[startx][starty] != -1) {
                break;
            }
        }
        if(parx[startx][starty] != -1) {
            break;
        }
    }

    pathx[0] = startx;
    pathy[0] = starty;
    *path_len = 1;
    x = startx;
    y = starty;
    while(x != endx || y != endy) {
        xx = parx[x][y];
        yy = pary[x][y];
        pathx[*path_len] = xx;
        pathy[*path_len] = yy;
        (*path_len)++;
        x = xx;
        y = yy;
    }

    for(int i = 0; i < sizex; i++) {
        free(parx[i]);
        free(pary[i]);
    }
    free(parx);
    free(pary);
    free(queuex);
    free(queuey);
}

void write_output(int* pathx, int* pathy, int path_len, FILE* fp) {
    fprintf(fp, "{\"safe_path\":[");
    for(int i = 0; i < path_len; i++) {
        fprintf(fp, "[%d,%d]", pathx[i], pathy[i]);
        if(i + 1 < path_len) {
            fprintf(fp, ",");
        }
    }
    fprintf(fp, "]}\n");
}

void free_memory(int** spread_matrix, int sizex, int* pathx, int* pathy) {
    for(int i = 0; i < sizex; i++) {
        free(spread_matrix[i]);
    }
    free(spread_matrix);
    free(pathx);
    free(pathy);
}

int main() {
    int** spread_matrix;
    int sizex;
    int sizey;
    int startx;
    int starty;
    int endx;
    int endy;
    int* pathx;
    int* pathy;
    int path_len;

    read_input(&spread_matrix, &sizex, &sizey, &startx, &starty, &endx, &endy, stdin);
    initialize_path(&pathx, &pathy, sizex * sizey);
    find_path(pathx, pathy, &path_len, spread_matrix, sizex, sizey, startx, starty, endx, endy);
    write_output(pathx, pathy, path_len, stdout);
    free_memory(spread_matrix, sizex, pathx, pathy);

    return 0;
}