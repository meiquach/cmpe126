#include "doubly_linked_list.h"

namespace lab6 {
    // Auxiliary Functions
    unsigned partition(doubly_linked_list &to_sort, int low, int high);
    doubly_linked_list recursive_merge_sort(doubly_linked_list to_sort);
    doubly_linked_list merge(doubly_linked_list left, doubly_linked_list right);

    unsigned partition(doubly_linked_list &to_sort, int low, int high) {
        //pivot as a last element in sorted array
        int pivot = to_sort.get_data(high);

        //smaller element index and right position of pivot
        unsigned i = low;
        for (unsigned j = low; j < high; j++) {
            // If current element is smaller than the pivot
            if (to_sort.get_data(j) < pivot) {
                //smaller element increase
                to_sort.swap(i, j);
                i++;
            }
        }
        to_sort.swap(i, high);
        return (i);

    }

    void quicksort(doubly_linked_list &to_sort, int low, int high) {
        // Check if list is empty or only has one element
        if (low < high) {
            unsigned pi = partition(to_sort, low, high);
            quicksort(to_sort, low, pi - 1);
            quicksort(to_sort, pi + 1, high);
        }
    }

    void mergesort(doubly_linked_list &to_sort) {
        to_sort = recursive_merge_sort(to_sort);
    }

    doubly_linked_list recursive_merge_sort(doubly_linked_list to_sort) {
        if (to_sort.size() <= 1) {
            return to_sort;
        }
        //Split in half
        unsigned size = to_sort.size();
        doubly_linked_list left =to_sort.split_set(0,(size-1)/2);
        doubly_linked_list right = to_sort;

        //sort each half
        right = recursive_merge_sort(right);
        left = recursive_merge_sort(left);
        doubly_linked_list sorted_list = merge(left, right);
        to_sort = sorted_list;
        return to_sort;
    }


    //Used for the merging the two lists
    doubly_linked_list merge(doubly_linked_list left, doubly_linked_list right) {
        doubly_linked_list list;

        // From left to right in each half, add the smaller value between the two lists to the list
        unsigned leftSize = left.size(), rightSize = right.size();
        unsigned leftIndex = 0, rightIndex = 0;
        while (leftIndex < leftSize && rightIndex < rightSize) {
            if (left.get_data(leftIndex) <= right.get_data(rightIndex)) {
                list.append(left.get_data(leftIndex++));
            }else
                list.append(right.get_data(rightIndex++));
        }

        // the left over from non-empty list add them on
        while (leftIndex < leftSize)
            list.append(left.get_data(leftIndex++));
        while (rightIndex < rightSize)
            list.append(right.get_data(rightIndex++));
        return list;

    }
}