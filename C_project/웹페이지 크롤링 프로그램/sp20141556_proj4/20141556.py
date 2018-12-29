import requests
from bs4 import BeautifulSoup
from operator import eq
original="http://cspro.sogang.ac.kr/~gr120170213/"
original2="http://cspro.sogang.ac.kr/~gr120170213/index.html"
r=requests.get("http://cspro.sogang.ac.kr/~gr120170213/index.html")
before=original
contentlist=[]
number=1;

def search(Root,k):
	global contentlist
	global p
	if findlist(k) == 1:
		return
	else:
		contentlist.append(k.content)
	global original
	global before
	alist=Root.find_all('a')
	if alist == []:
		return
	for hrefelement in alist:
		temp=hrefelement.get('href')
		if temp[:4]=="http":
			goto=temp
		elif temp=="":
			goto=before
		elif temp[:1]=="#":
			goto=before+temp
		else:
			goto=original+temp	
		before=goto
		r=requests.get(goto)
		if findlist(r) == 1:
			continue
		Descendant=BeautifulSoup(r.content,"html.parser")
		if r.status_code == 404:
			continue
		printpage(r)
		p.write(goto)
		p.write('\n')
		search(Descendant,r)

def printpage(r):
	global number
	f=open("Output_%04d.txt"%(number),"w")
	Root=BeautifulSoup(r.content,"html.parser")
	f.writelines(Root.get_text())
	number+=1
	f.close()
def findlist(r):
	global contentlist
	for index in contentlist:
		if eq(index,r.content) == True:
			return 1
	return 0

printpage(r)
p=open("URL.txt","w")
p.write(original2)
p.write('\n')
Root=BeautifulSoup(r.content,"html.parser")
search(Root,r)
p.close()		
