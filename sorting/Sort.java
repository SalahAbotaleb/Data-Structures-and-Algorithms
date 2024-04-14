package sorting;

import java.util.Arrays;

interface SortAlgo {
    public void sort(int arr[]);

    public String algoName();
}

/**
 * Stable: yes
 * Description:
 * 
 * Time complexity:
 * Space complexity:-
 * Notes:-
 */
class InsertionSort implements SortAlgo {
    /**
     * Stable: yes
     * Description: Insert each element in its correct order in increasing list
     * Time complexity: O(n^2), best case all sorted O(n)
     * Space complexity: O(1)
     * Notes: -
     */
    @Override
    public void sort(int[] arr) {
        for (int i = 1; i < arr.length; i++) {
            int curr = arr[i];
            int lstIdx = i - 1;
            while (lstIdx > -1 && curr < arr[lstIdx]) {
                arr[lstIdx + 1] = arr[lstIdx];
                lstIdx = lstIdx - 1;
            }
            arr[lstIdx + 1] = curr;
        }

    }

    @Override
    public String algoName() {
        return "Insertion sort";
    }

}

class QuickSort implements SortAlgo {
    /**
     * Stable: no
     * Description: Get the correct position of an element where all
     * elements on the left are smaller than or equal
     * and all elements on the right are larger than
     * then sort elements on the left and then sort elements on the right
     * Time complexity: O(nlog(n)), best case all sorted O(n)
     * Space complexity: O(1)
     * Notes: Worst case if all same element will be O(n^2)
     */
    @Override
    public void sort(int[] arr) {
        sort(0, arr.length - 1, arr);
    }

    private void swap(int i, int j, int arr[]) {
        int tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }

    private void sort(int l, int r, int arr[]) {
        if (l >= r)
            return;
        int pivot = l + (int) Math.round(Math.random() * (r - l));
        swap(pivot, r, arr);
        int idx = qs(l, r, arr);
        sort(l, idx - 1, arr);
        sort(idx + 1, r, arr);
    }

    private int qs(int l, int r, int[] arr) {
        int idx = l - 1;
        for (int i = l; i < r; i++) {
            if (arr[i] <= arr[r]) {
                idx++;
                swap(i, idx, arr);
            }
        }
        swap(idx + 1, r, arr);
        return idx + 1;
    }

    @Override
    public String algoName() {
        return "Quick sort";
    }

}

class MergeSort implements SortAlgo {
    /**
     * Stable: yes
     * Description: Divide the array into two equal parts until you reach one
     * element
     * then merge the divided parts and upon merging sort them.
     * where the divided parts are already sorted so merging the sorted
     * parts will take O(n) only.
     * Time complexity: O(nlog(n))
     * Space complexity: O(n)
     */
    @Override
    public void sort(int[] arr) {
        divide(0, arr.length - 1, arr);
    }

    private void divide(int l, int r, int arr[]) {
        if (l >= r)
            return;
        int mid = (l + r) / 2;
        divide(l, mid, arr);
        divide(mid + 1, r, arr);
        merge(l, mid, r, arr);
    }

    private void merge(int l, int mid, int r, int[] arr) {
        int tmp[] = new int[mid - l + 2];
        int tmp1[] = new int[r - mid + 1];
        Arrays.fill(tmp, Integer.MAX_VALUE);
        Arrays.fill(tmp1, Integer.MAX_VALUE);
        for (int i = l; i <= mid; i++) {
            tmp[i - l] = arr[i];
        }
        for (int i = mid + 1; i <= r; i++) {
            tmp1[i - (mid + 1)] = arr[i];
        }
        int curr = l;
        int currA = 0;
        int currB = 0;

        while (curr <= r) {
            if (tmp[currA] <= tmp1[currB]) {
                arr[curr] = tmp[currA];
                currA++;
            } else {
                arr[curr] = tmp1[currB];
                currB++;
            }
            curr++;
        }
    }

    @Override
    public String algoName() {
        return "Merge sort";
    }

}

public class Sort {

    public static void main(String args[]) {
        SortAlgo algo = new MergeSort();
        int arr[] = new int[] { 8, 1, 3, 8, -1, 6, -2, 0, 8, 122, 16, 3, 3, 3, -199 };
        algo.sort(arr);
        for (int item : arr) {
            System.out.print(item + " ");
        }
        System.out.println();
    }
}