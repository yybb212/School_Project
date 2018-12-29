#!/usr/bin/python3
# -*- coding: utf-8 -*-
from sys import stdin,stdout
dic=dict()
wordlist=[]
while True:
	content=stdin.readline().strip()
	if content=="":
		break
	one,two,null=content.split()
	key=one+" "+two
	if key in dic:
		dic[key]+=1
	else:
		dic[key]=1
wordlist=sorted(dic)
for i in wordlist:
	stdout.write(i+"\t"+str(dic[i])+"\n")
