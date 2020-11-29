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
            fprintf(file, "graph mainGraph {\n");

            for (int i = 0; i < numbVert; i++) {
                for (int j = 0; j < verticales[i].arrEdgesLen; j++) {
                    fprintf(file, "  %d -- %d\n", verticales[i].value, verticales[i].arrEdges[j]);
                }
            }

           fprintf(file, "}");
        } else {
            printf("Error during writing file!");
            exit("Error");
        }


        findVerticaleWithMaxEdges(&verticales, numbVert);
        checkCoherence(&verticales, numbVert);
    }
}

void checkCoherence(struct verticale *verticales, int numVerticales) {
    int numEdges = 0;
    int flag = 0;

    for (int j = 0; j < numVerticales; j++) {
        numEdges += verticales[j].arrEdgesLen;

        for (int i = 0; i < verticales[j].arrEdgesLen; i++) {
            if (verticales[j].value == verticales[j].arrEdges[i]) {
                flag = 1;
            }

            for (int k = 0; k < numVerticales; k++) {
                if ((i != k) && (verticales[j].arrEdges[i]) == verticales[j].arrEdges[k]) {
                    flag = 1;
                }
            }
        }
    }

    for (int j = 0; j < numVerticales; j++) {
        for (int i = 0; i < verticales[j].arrEdgesLen; i++) {
            if (verticales[j].value == verticales[j].arrEdges[i]) {
                flag = 1;
            }
        }
    }


    if ((numEdges > ((numVerticales-1)*(numVerticales - 2))/2) && flag == 0) {
        printf("\nThis graph is connectivity\n");
    } else if (flag == 1) {
        printf("\nThe requirements are not met\n");
    } else {
        printf("\nThis graph is not connectivity\n");
    }
}

void findVerticaleWithMaxEdges(struct verticale *verticales, int numVerticales) {
    int max = 0;

    if (numVerticales != 0) {
        for (int i = 0; i < numVerticales; i++) {
            if (verticales[i].arrEdgesLen > max) {
                max = verticales[i].arrEdgesLen;
            }
        }

        for (int j = 0; j < numVerticales; j++) {
            if (verticales[j].arrEdgesLen == max) {
                printf("\nVerticale %d has max number of edges\n", j + 1);
            }
        }

    } else {
        printf("You must have at least one verticale to find one with the max edges!\n");
    }

}

