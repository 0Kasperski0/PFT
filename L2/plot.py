import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np
import math as m


def fun(x):
	a=9.81/1
	return 0.0698131701*np.cos(np.sqrt(a)*x)

def plotting(str,a,b,lab):
	X=np.loadtxt(str,usecols=a)
	Y=np.loadtxt(str,usecols=b)
	
	

	plt.plot(X, Y,color='red',label=lab)

def plottingtst(str,lab):
	fig = plt.figure()
	ax = fig.gca(projection='3d')
	a=0.5
	z=np.loadtxt(str,usecols=2)
	PH=np.loadtxt(str,usecols=1)
	
	p=z*np.tan(a)
	X=p*np.cos(PH)
	Y=p*np.sin(PH)
	Z=z
	ax.plot(X, Y, Z,label=lab)
	ax.legend()
	plt.show()

def plottingtst2(str,lab):
	fig = plt.figure()
	ax = fig.gca(projection='3d')
	a=0.5
	z=np.loadtxt(str,usecols=2)
	PH=np.loadtxt(str,usecols=1)
	
	p=z*np.tan(a)
	Xa=p*np.cos(PH)
	Ya=p*np.sin(PH)
	Za=z

	TH=np.pi/2-a
	
	X=np.cos(TH)*Xa+np.sin(TH)*Za
	Y=Ya
	Z=-np.sin(TH)*Xa+np.cos(TH)*Za


	ax.set_xlabel('x')
	ax.set_ylabel('y')
	ax.set_zlabel('z')
	ax.plot(X, Y, Z,label=lab)
	
	

xs=0
ys=7
# t fi z vfi vz t u e
label=u'Trajektoria'

file='pft2_3.txt'
#plotting(file,xs,ys,label)
#plottingtst(file,'\u03C6 = 4')

plottingtst2(file,label)
#plotting2('pft2.txt',xs,ys,'\u03C6 = 4 analityczni')


#plotting('45.txt',xs,ys,'\u03C6 = 45')
#plotting('90.txt',xs,ys,'\u03C6 = 90')
#plotting('135.txt',xs,ys,'\u03C6 = 135')
#plotting('175.txt',xs,ys,'\u03C6 = 175')


plt.grid(True)
plt.legend()
#plt.xlabel('t [s]')
#plt.ylabel(label)
#plt.zlabel('z')
plt.show()