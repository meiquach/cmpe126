#include "doubly_linked_list.h"

namespace lab6{
    // Auxiliary Functions
    unsigned partition(doubly_linked_list& to_sort, int low, int high);

    doubly_linked_list recursive_merge_sort(doubly_linked_list to_sort);
    doubly_linked_list merge(doubly_linked_list left, doubly_linked_list right);

    void quicksort(doubly_linked_list& to_sort, int low, int high){
        // Check if list is empty or only has one element
        unsigned size = (high - low) + 1;
        if (size < 2) return;

        if (low < high) {
            unsigned partitionIndex = partition(to_sort, low, high);

            // Sort the half below and above the partition index
            quicksort(to_sort, low, partitionIndex - 1);
            quicksort(to_sort, partitionIndex + 1, high);
        }

    }

    unsigned partition(doubly_linked_list& to_sort, int low, int high) {
        int pivot = to_sort.get_data(high);

        unsigned i = (low - 1);
        for (unsigned j = low; j <= high - 1; j++) {
            // If current element is smaller than the pivot
            if (to_sort.get_data(j) < pivot) to_sort.swap(++i, j);
        }

        to_sort.swap(i + 1, high);

        return (i + 1);
    }

    void mergesort(doubly_linked_list& to_sort)
    {
        to_sort = recursive_merge_sort(to_sort);
    }

    doubly_linked_list recursive_merge_sort(doubly_linked_list to_sort){
        int mid = (to_sort.size()-1)/2;
        if(mid < 1)
        {
            return to_sort;
        }
        doubly_linked_list right = to_sort.split(mid);
        to_sort = recursive_merge_sort(to_sort); // to_sort now the left hand side
        right = recursive_merge_sort(right);
        return merge(to_sort, right);

    }

    //Used for the merging the two lists
    doubly_linked_list merge(doubly_linked_list left, doubly_linked_list right){
        doubly_linked_list final;
        int x = left.size();
        int y = right.size();
        int i = 0; // for left
        int j = 0; // for right
        while(i < x && j < y)
        {
            if(left.get_data(i) <= right.get_data(j))
            {
                final.append(left.get_data(i));
                i++;
            }
            else
            {
                final.append(right.get_data(j));
                j++;
            }
        }
        if(i < x)
        {
            for(; i < x; i++)
            {
                final.append(left.get_data(i));
            }
        }
        if(j < y)
        {
            for(; j < y; j++)
            {
                final.append(right.get_data(j));
            }
        }
        return final;

    }
}