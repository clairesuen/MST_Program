#include <stdio.h>
#include <iostream>
#include <math.h>
#include "heap.hpp"

//clock_t start, end;

float Prim(int n, int dim, float *x, float *y, float *z, float *a )
{
    float distance[n];
    int vert[n];
    heap heap_mst(n, n/8);

    //initialize vertices
    for (int i = 1; i < n; i++)
    {
        distance[i] = 1000000;
        vert[i] = 0;
    }

    //initialize values
    float largest_edge = -50.0;
    Node v = {-1, -1};
    float MST = 0.0;

    distance[0] = 0;
    vert[0] = 1;
    heap_mst.insert_elt(0, 0);

    while (!heap_mst.is_empty())
    {
        v = heap_mst.delete_node(v);
        float dist_edge = distance[v.vertex];
        if(dist_edge >= largest_edge)
            largest_edge = dist_edge;
        vert[v.vertex] = 1;
        MST += dist_edge;

        int p[n];
        for (int e = 0; e < n; e++)
        {
            if (vert[e] == 0)
            {
                int n2 = e;
                int n1 = v.vertex;
                float edge_weight;

                if (dim == 0)
                {
                    edge_weight = (float)rand() / RAND_MAX;
                }
                if (dim == 1)
                {
                    edge_weight = (float)rand() / RAND_MAX;
                }
                else if (dim == 2)
                {
                    edge_weight = sqrt(pow(x[n1] - x[n2], 2.0) + (pow(y[n1] - y[n2], 2.0)));
                }

                else if (dim == 3)
                {
                    edge_weight = sqrt(pow(x[n1] - x[n2], 2.0) + (pow(y[n1] - y[n2], 2.0)) + (pow(z[n1] - z[n2], 2.0)));
                }

                else if (dim == 4)
                {
                    edge_weight = sqrt(pow(x[n1] - x[n2], 2.0) + (pow(y[n1] - y[n2], 2.0)) + (pow(z[n1] - z[n2], 2.0)) + (pow(a[n1] - a[n2], 2.0)));
                }

                if (distance[e] >= edge_weight)
                {
                    p[e] = v.vertex;
                    distance[e] = edge_weight;
                    heap_mst.insert_elt(e, distance[e]);
                }
            }
        }
    }
    return MST;
}

float helper(int num_pt, int num_trial, int dim)
{
    //srand((unsigned)time(NULL));
    float MST = 0.0;
    for (int i = 0; i < num_trial; i++)
    {
        if (dim == 0)
        {
            float x[1];
            float y[1];
            float z[1];
            float a[1];
            MST += Prim(num_pt, dim, x, y, z, a);
        }
        else if (dim == 1)
        {
            return num_pt;
            return num_trial;
            return dim;
        }
        else if (dim == 2)
        {
            float x[num_pt];
            float y[num_pt];
            float z[1];
            float a[1];
            for (int a = 0; a < num_pt; a++)
            {
                x[a] = (float)rand() / RAND_MAX;
                y[a] = (float)rand() / RAND_MAX;
            }
            MST += Prim(num_pt, dim, x, y, z, a);
        }
        else if (dim == 3)
        {
            float x[num_pt];
            float y[num_pt];
            float z[num_pt];
            float a[1];
            for (int a = 0; a < num_pt; a++)
            {
                x[a] = (float)rand() / RAND_MAX;
                y[a] = (float)rand() / RAND_MAX;
                z[a] = (float)rand() / RAND_MAX;
            }
            MST += Prim(num_pt, dim, x, y, z, a);
        }
        else if (dim == 4)
        {
            float x[num_pt];
            float y[num_pt];
            float z[num_pt];
            float a[num_pt];
            for (int i = 0; i < num_pt; i++)
            {
                x[i] = (float)rand() / RAND_MAX;
                y[i] = (float)rand() / RAND_MAX;
                z[i] = (float)rand() / RAND_MAX;
                a[i] = (float)rand() / RAND_MAX;
            }
            MST += Prim(num_pt, dim, x, y, z, a);
        }
    }
    return MST;
}

int main(int argc, const char * argv[])
{
    int n = atoi(argv[2]);
    int trials = atoi(argv[3]);
    int dim = atoi(argv[4]);
    float MST = helper(n, trials, dim);
    std::cout << MST / trials << " " << n << " " << trials << " " << dim << std::endl;
}