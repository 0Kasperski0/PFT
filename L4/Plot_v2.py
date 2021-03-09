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

	def pandasdataframe(self,tmax):
		self.df = pd.DataFrame(data=self.data, index=np.around(np.linspace(0,tmax,len(self.data),endpoint=True),0), columns=np.arange(0,51))


	def heatmap(self):
		ax=sns.heatmap(self.df,cmap="PiYG")
		ax.invert_yaxis()
		
		
file='pft4_0_09.txt'

Test=CsPlot()
Cols=np.arange(0,4)#[0,1,2,3]
Test.loaddatafromto(file,0,3)
#Test.loaddatacollist('pft4_0.txt',Cols)
Test.plot2D(0,1,u'E')
Test.plot2D(0,2,u'T')
Test.plot2D(0,3,u'U')
Test.set_label_title(u't [s]',u'E',u"Energia układu")
Test.pltsettings()
Test.plt_size_save_show(16/1.5, 9/1.5,False)


# b=np.arange(4,55)
# a=np.array([0])


# Cols=np.concatenate((a,b),axis=0)

Cols=np.arange(4,55)
print(Cols)
Heat=CsPlot()
Heat.loaddatacollist(file,Cols)
Heat.pandasdataframe(2222.52)
Heat.heatmap()
Heat.set_label_title('x','t [s]','n=0.9')
Heat.plt_size_save_show(10,10,False)


