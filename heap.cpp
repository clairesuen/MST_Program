#include "heap.hpp"
#include <iostream>

heap::heap(int vertices, int node_child)
{
    curr_size = 0;
    heap_array = new Node[vertices];
    heap_posi = new int[vertices];
    for (int i = 0; i < vertices; i++)
    {
        heap_posi[i] = -1;
    }
    num_child = node_child;
    max = vertices;
}

bool heap::is_empty()
{
    return curr_size == 0;
}

bool heap::is_max()
{
    return curr_size == max;
}

Node heap::delete_node(Node min)
{
    int next_size = curr_size - 1;
    if (is_empty())
    {
        std::cout << "Heap empty" << std::endl;
        return min;
    }
    else
    {
        min.vertex = heap_array[0].vertex;
        heap_posi[min.vertex] = -1;
        min.distance = heap_array[0].distance;
        if (!is_empty())
        {
            int value = heap_array[next_size].vertex;
            heap_posi[value] = 0;
        }
        heap_array[0] = heap_array[next_size];
        curr_size --;
        min_heap(0);
        return min;
    }
}
void heap::insert_elt(int v, float d)
{
    if (is_max())
    {
        std::cout << "Max heap size reached." << std::endl;
        return;
    }
    else
    {
        if (vertex_posi(v) != -1)
        {
            min_heap(heap_posi[v]);
            bubble_up(heap_posi[v]);
            heap_array[heap_posi[v]].distance = d;
        }
        else
        {
            heap_posi[v] = curr_size;
            bubble_up(curr_size);
            heap_array[curr_size].vertex = v;
            heap_array[curr_size].distance = d;
            curr_size++;
        }
    }
}

void heap::swap_idx(Node x, Node y, int x_idx, int y_idx)
{
    heap_posi[x.vertex] = y_idx;
    heap_posi[y.vertex] = x_idx;
}

int heap::parent(int child_idx)
{
    return (child_idx - 1) / num_child;
}

int heap::child_index(int parent_index, int child)
{
    return (parent_index * num_child) + child;
}

int heap::vertex_posi(int vertex)
{
    if (heap_posi[vertex] != -1)
    {
        return heap_posi[vertex];
    }
    else
    {
        return -1;
    }
}

void heap::bubble_up(int move)
{
    while (heap_array[move].distance < heap_array[parent(move)].distance && move > 0)
    {
        int parent_pos = parent(move);
        swap_idx(heap_array[move], heap_array[parent_pos], move, parent_pos);
        std::swap(heap_array[move], heap_array[parent_pos]);
        move = parent_pos;
    }
}

void heap::min_heap(int pos)
{
    int position_status = 1;
    int position_swap = pos;
    int range_val = num_child + 1;
    while (position_status)
    {
        for (int i = 1; i < range_val; i++)
        {
            if (child_index(pos, i) < curr_size)
            {
                /*int array_idx_d = heap_array[child_index(pos, i)].distance;
                int array_idx_swap_d = heap_array[position_swap].distance*/
                if (heap_array[child_index(pos, i)].distance < heap_array[position_swap].distance)
                {
                    position_swap = child_index(pos, i);
                }
            }
        }
        if (position_swap == pos) 
        {
            position_status = 0;
        }
        else
        {
            swap_idx(heap_array[pos], heap_array[position_swap], pos, position_swap);
            std::swap(heap_array[pos], heap_array[position_swap]);
            pos = position_swap;
        }
    }
}
