# -*- coding: utf-8 -*- 
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib.ticker import MaxNLocator
import numpy as np
import math as m
import seaborn as sns; #sns.set()
import pandas as pd 
import sys
from datetime import datetime
from matplotlib import cm
from matplotlib.ticker import LinearLocator, FormatStrFormatter


class CsPlot:
	
	def __init__(self):
		self.data=np.array
		
	def printtxt(self):
		print(self.file)
	
	def plot2D(self,a,b,lab):
		y=self.data[:,b]
		x=self.data[:,a]
		self.fig=plt.plot(x,y,label=lab)
		
	def loaddatafromto(self,str,ca,cb):
		self.data=np.loadtxt(str,usecols=np.arange(ca,cb+1))
		
	def loaddatacollist(self,str,lst):
		self.data=np.loadtxt(str,usecols=lst)

	def slice_ox(self,x_index,lab):
		y=self.data[x_index,:]
		x=np.around(np.linspace(0,self.xmax,len(self.data[0]),endpoint=True),1)
		self.fig=plt.plot(x,y,label=lab)


	def slice_oy(self,y_index,lab):
		y=self.data[:,y_index]
		x=np.around(np.linspace(0,self.ymax,len(self.data),endpoint=True),1)
		self.fig=plt.plot(x,y,label=lab)
		
	def set_label_title(self,xlbl,ylbl,title):
		plt.xlabel(xlbl)
		plt.ylabel(ylbl)
		self.title=title
		plt.title(title)

	def plt_size_save_show(self,a,b,sve):
		fig = plt.gcf()
		fig.set_size_inches(a,b)
		if sve==True:
			fig.savefig(str(datetime.now().time())+'.png', dpi=100)
		plt.gca().set_aspect('equal', adjustable='box')	
		plt.show()

	def pltsettings(self):
		plt.grid(True)
		plt.legend()

	def pandasdataframe(self,xmax,ymax):
		self.xmax=xmax
		self.ymax=ymax

		self.df = pd.DataFrame(data=self.data, index=np.around(np.linspace(0,self.ymax,len(self.data),endpoint=True),1), columns=np.around(np.linspace(0,self.xmax,len(self.data[0]),endpoint=True),1))


	def heatmap(self):
		self.ax=sns.heatmap(self.df,cmap="plasma")
		self.ax.invert_yaxis()
		
	def heatmap_3d(self):
		fig = plt.figure()
		ax = fig.gca(projection='3d')

		X = np.around(np.linspace(0,self.xmax,len(self.data[0]),endpoint=True),1)
		Y = np.around(np.linspace(0,self.ymax,len(self.data),endpoint=True),1)
		X, Y = np.meshgrid(X, Y)
		surf = ax.plot_surface(X, Y, self.data, cmap="plasma",
                       linewidth=0, antialiased=False)

		fig.colorbar(surf, shrink=0.5, aspect=5)

		plt.show()	

		#prj 6 
	def vector_plt(self,a,b,c,d,s):
		x=self.data[:,a]
		y=self.data[:,b]
		
		u=self.data[:,c]
		v=self.data[:,d]
		fig, ax = plt.subplots()
		widths = np.linspace(0, 0.1, x.size)
		ax.quiver(x,y,u,v,scale=s)

		circ1=plt.Circle((0,0),1,facecolor='None',edgecolor='b')
		ax.add_patch(circ1)
	def plt_vectors_to_heat(self,a,b,c):
		x=self.data[:,a]
		y=self.data[:,b]
		z=self.data[:,c]
		Z=np.reshape(z,[41,41])
		self.df = pd.DataFrame(data=Z,index=np.around(np.linspace(-3.0,3.0,41,endpoint=True),1), columns=np.around(np.linspace(-3.0,3.0,41,endpoint=True),1))
	
	def pltcircle(self):
		circ1=plt.Circle((21,21),7,facecolor='None',edgecolor='black')
		self.ax.add_patch(circ1)
		
	def slice_withreshape(self,a,b,c):
		print('ayaya')	
		x=self.data[:,a]
		y=self.data[:,b]
		z=self.data[:,c]
		Z=np.reshape(z,[41,41])

		X=np.around(np.linspace(-3.0,3.0,41,endpoint=True),3)
		Y=Z[:,21]
		self.fig=plt.plot(X,Y)


	def plt_vectors_to_heat3D(self):
		fig = plt.figure()
		ax = fig.gca(projection='3d')

		X=np.around(np.linspace(-3.0,3.0,41,endpoint=True),3)
		Y=np.around(np.linspace(-3.0,3.0,41,endpoint=True),3)
		z=self.data[:,2]
		Z=np.reshape(z,[41,41])
		X, Y = np.meshgrid(X, Y)
		surf = ax.plot_surface(X, Y, Z, cmap="plasma",
                       linewidth=0, antialiased=False)

		fig.colorbar(surf, shrink=0.5, aspect=5)
		plt.show()


	

file='pft6_pi4.txt'

Test=CsPlot()
Cols=np.arange(0,3)#[0,1,2,3]
Test.loaddatafromto(file,0,6)
# #Test.loaddatacollist('pft4_0.txt',Cols)
#Test.plot2D(0,2,u'E')
# Test.plot2D(0,2,u'T')
# Test.plot2D(0,3,u'U')
Test.slice_withreshape(0,1,2)
Test.pltsettings()
Test.set_label_title('y','V','V(0,y,0)')
Test.plt_size_save_show(10,10,False)



