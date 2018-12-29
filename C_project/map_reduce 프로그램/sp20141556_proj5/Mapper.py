#!/usr/bin/python3
# -*- coding: utf-8 -*-
from sys import stdin,stdout
while True:
	content=stdin.readline().strip()
	if content =="":
		break
	wordlist=content.split()
	for i in range(0,len(wordlist)-1):
		stdout.write(wordlist[i]+' '+wordlist[i+1]+' '+str(1)+'\n')
