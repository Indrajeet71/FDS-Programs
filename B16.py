"""
Write  a Python program  to  store  first  year percentage  of  students  in  array.  Write function  for  sorting  array  of  floating  point  numbers  in  ascending  order  using  quick  sort and display top five scores.
"""

def partition(arr, low, high):
    i = (low-1)
    pivot = arr[high]
    for j in range(low, high):
        if arr[j] < pivot:
            i = i+1
            arr[i], arr[j] = arr[j], arr[i]
    arr[i+1], arr[high] = arr[high], arr[i+1]
    return (i+1)


def quick_sort(arr, low, high):
    if low < high:
        pi = partition(arr, low, high)
        quick_sort(arr, low, pi-1)
        quick_sort(arr, pi+1, high)
    return arr


if __name__ == "__main__":
    arr = [int(x) for x in input("Enter percentages of students : ").split()]
    qSorted = quick_sort(arr, 0, len(arr)-1)
    print(f"Percentages sorted using bubble sort : {qSorted}")
    print(f"Top 5 percentages : {qSorted[:-6:-1]}")
