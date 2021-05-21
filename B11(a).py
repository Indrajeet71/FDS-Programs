"""
a)Write  a Python program  to  store  roll  numbers  of  student  in  array  who  attended training  program  in  random  order.  Write  function  for  searching  whether  particular student attended training program or not, using Linear search and Sentinel search. 
"""

def linearsearch(arr, x):
   for i in range(len(arr)):
      if arr[i] == x:
         return i
   return -1

def sentinel_linear_search(arr, target):
    arr.append(target)
 
    index = 0
    while arr[index] != target:
        index += 1
 
    arr.pop()
 
    if index == len(arr):
        return None
 
    return index

def main():
    arr = [int(x) for x in input(
        "Enter roll nos of students who attended training : ").split()]
    print(f"Student was {'not ' if linearsearch(arr, int(input('Enter roll no. of student to be searched (linear) : '))) == -1 else ' '}present.")

    target=int(input('Enter roll no. of student to be searched (Sentinal) : '))
    result = sentinel_linear_search(arr, target)
    if result is not None:
        print(f"{target} found at positions: {result}")
    else:
        print("Not found")

if __name__ == "__main__":
    main()