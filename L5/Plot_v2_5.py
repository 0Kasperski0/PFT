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
		plt.show()

	def pltsettings(self):
		plt.grid(True)
		plt.legend()

	def pandasdataframe(self,xmax,ymax):
		self.xmax=xmax
		self.ymax=ymax

		self.df = pd.DataFrame(data=self.data, index=np.around(np.linspace(0,self.ymax,len(self.data),endpoint=True),1), columns=np.around(np.linspace(0,self.xmax,len(self.data[0]),endpoint=True),1))


	def heatmap(self):
		ax=sns.heatmap(self.df,cmap="plasma")
		ax.invert_yaxis()
		
	def heatmap_3d(self):
		fig = plt.figure()
		ax = fig.gca(projection='3d')
		X = np.around(np.linspace(0,self.xmax,len(self.data[0]),endpoint=True),1)
		Y = np.around(np.linspace(0,self.ymax,len(self.data),endpoint=True),1)
		X, Y = np.meshgrid(X, Y)
		surf = ax.plot_surface(X, Y, self.data, cmap="PiYG",
                       linewidth=0, antialiased=False)

		fig.colorbar(surf, shrink=0.5, aspect=5)

		plt.show()
		
file='pft5_0.txt'

# Test=CsPlot()
# Cols=np.arange(0,4)#[0,1,2,3]
# Test.loaddatafromto(file,0,3)
# #Test.loaddatacollist('pft4_0.txt',Cols)
# Test.plot2D(0,1,u'E')
# Test.plot2D(0,2,u'T')
# Test.plot2D(0,3,u'U')
# Test.set_label_title(u't [s]',u'E',u"Energia układu")
# Test.pltsettings()
# Test.plt_size_save_show(16/1.5, 9/1.5,False)


# b=np.arange(4,55)
# a=np.array([0])


# Cols=np.concatenate((a,b),axis=0)

Cols=np.arange(1,31)
print(Cols)
Heat=CsPlot()
Heat.loaddatacollist(file,Cols)
Heat.pandasdataframe(3,15)
Heat.heatmap()
Heat.set_label_title('rho','z','V - mapa')
Heat.plt_size_save_show(10,10,False)


Heat.heatmap_3d()



Slice=CsPlot()
Slice.loaddatacollist(file,Cols)
Slice.pandasdataframe(3,15)
Slice.slice_ox(85,"pot")
Slice.set_label_title('rho','z','V(rho,zmax_2)')
Slice.plt_size_save_show(10,10,False)
Slice.pltsettings()


Slice.slice_oy(0,"pot")
Slice.set_label_title('rho','z','V(rho,zmax_2)')
Slice.plt_size_save_show(10,10,False)
Slice.pltsettings()