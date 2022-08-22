from cProfile import label
import matplotlib.pyplot as plt


x = []
y = []
with open('bucket_points_continue.txt') as archivo:
    for linea in archivo:
        punto = [int(i) for i in linea.split(',')]
        x.append(punto[0])
        y.append(punto[1])

plt.plot(x, y, "o--", label="Bucket Sort")
'''

x = []
y = []
with open('insertion_points_continue.txt') as archivo:
    for linea in archivo:
        punto = [int(i) for i in linea.split(',')]
        x.append(punto[0])
        y.append(punto[1])

plt.plot(x, y, "o--", label="Insertion Sort")
plt.legend(loc="best" )
'''


#plt.xscale("log") 
#plt.yscale("log")
plt.ylim(0, 123000)
plt.ylabel("Tiempo en ms")
plt.xlabel("Cantidad de datos a ordenar")
plt.title("Bucket Sort")
plt.savefig("Bucket_Sort_continue2.jpg")
plt.show()
