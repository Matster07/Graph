#include <stdio.h>
#include <stdlib.h>

struct verticale {
    int value;
    int *arrEdges;
    int arrEdgesLen;
};



void main() {
    int numbVert;
    int numbEdges;
    int numbEdgeValue;
    FILE * file;

    printf("Enter the number of vertices:\n");
    scanf("%d", &numbVert);

    printf("\n");

    if (numbVert > 0) {
        struct verticale verticales[numbVert];

        for (int i = 0; i < numbVert; i++) {
            printf("Enter the value of %d verticale:\n", i);
            scanf("%d", &verticales[i].value);
        }

        for (int j = 0; j < numbVert; j++) {
            printf("\nEnter the edge number of %d verticale:\n", j);
            scanf("%d", &numbEdges);

            printf("\n");

            if (numbEdges > 0) {
                if ((verticales[j].arrEdges = (int*) malloc(numbEdges * sizeof(int))) != NULL) {
                    verticales[j].arrEdgesLen = numbEdges;

                    printf("Enter the verticale to connect with among: ");
                    for (int k = 0; k < numbVert; k++) {
                        printf("%d ", verticales[k].value);
                    }

                    printf("\n");

                    for (int t = 0; t < numbEdges; t++) {
                        printf("The %d edge connect with:\n", t+1);
                        scanf("%d", &numbEdgeValue);

                        int flag = 0;

                        for (int i = 0; i < numbVert; i++) {
                            if (numbEdgeValue == verticales[i].value) {
                                flag =  1;
                                break;
                            }
                        }

                        if (flag == 0) {
                            printf("There is no such an edge! Try again!\n");
                            exit("Error!");
                        } else {
                            verticales[j].arrEdges[t] = numbEdgeValue;
                        }

                    }

                } else {
                    printf("Cannot allocate the memory!");
                }
            } else {
                printf("The length cannot be 0!");
            }

        }

        file = fopen("graph.dot", "w");
        if (file != NULL) {
            fprintf(file, "digraph mainGraph {\n");

            for (int i = 0; i < numbVert; i++) {
                for (int j = 0; j < verticales[i].arrEdgesLen; j++) {
                    fprintf(file, "  %d -> %d\n", verticales[i].value, verticales[i].arrEdges[j]);
                }
            }

           fprintf(file, "}");
        } else {
            printf("Error during writing file!");
            exit("Error");
        }
    }
}

