def length(x) :
    len =0
    for _ in x :
        len +=1 
    return len

def avg(x):
    total = 0
    for i in x:
        total += i
    avg = total/length(x)
    return avg

def sorting(x):
    n=length(x)
    for i in range(n):
        for j in range (i+1,n):
            if x[i] > x[j] :
                x[i],x[j] = x[j], x[i]
    return x

def freq(x):
    frequency = {}
    for i in x :
        frequency[i]=frequency.get(i,0)+i
    times =list(frequency.values())
    times = sorting(times)
    z= times[-1]
    for key,value in frequency.items():
        if z == value:
            return(key)

def main():
    count =0
    fds_marks =[]
    N= int(input("Enter the number of students : \t"))
    for _ in range(N):
        m=int(input("Enter the score of student .If absent enter -1 :\t"))
        if m == -1:
            count +=1
        else:
            fds_marks.append(m)
    print("Average score of class :",avg(fds_marks))
    score =sorting(fds_marks)
    print("Lowest score of class is : ",score[0])
    print("Highest score of class is :",score[-1])
    print("Count of students who were absent for test is :",count)
    print("Marks with highest frequency is:",freq(fds_marks))

if __name__ == '__main__':
    main()