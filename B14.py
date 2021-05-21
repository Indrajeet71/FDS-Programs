"""
Write  a Python program  to  store  first  year  percentage  of  students  in  array.  
Write function for sorting array of floating point numbers in ascending order using 
a) Selection Sort 
b) Bubble sort and display top five scores.
"""

def selection_sort(arr):
    for i in range(len(arr)):
        min_i = i
        for j in range(i+1, len(arr)):
            if arr[min_i] > arr[j]:
                min_i = j
        arr[i], arr[min_i] = arr[min_i], arr[i]
    return arr


def bubble_sort(arr):
    for i in range(len(arr)):
        for j in range(len(arr) - i - 1):
            if arr[j] > arr[j+1]:
                arr[j], arr[j+1] = arr[j+1], arr[j]
    return arr


if __name__ == "__main__":
    arr = [int(x) for x in input("Enter percentages of students : ").split()]
    sSorted = selection_sort(arr)
    bSorted = bubble_sort(arr)
    print(f"Percentages sorted using selection sort : {sSorted}")
    print(f"Percentages sorted using bubble sort : {bSorted}")
    print(f"Top 5 percentages : {bSorted[:-6:-1]}")
