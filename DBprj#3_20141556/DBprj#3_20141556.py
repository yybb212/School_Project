#-*- coding: utf-8 -*-
import datetime
import time
import sys
import MeCab
import operator
from pymongo import MongoClient
from bson import ObjectId
from itertools import combinations
stop_word={}

def printMenu():
    print "0. CopyData"
    print "1. Morph"
    print "2. print morphs"
    print "3. print wordset"
    print "4. frequent item set"
    print "5. association rule"



def p0():
    """
    TODO:
    CopyData news to news_freq
    """
    col1=db['news']
    col2=db['news_freq']
    col2.drop()
    for doc in col1.find():
        contenDic={}
        for key in doc.keys():
            if key !="_id":
                contenDic[key]=doc[key]
        col2.insert(contenDic)


## Make stop word            
def make_stop_word():
    f=open("wordList.txt",'r')
    while True:
        line=f.readline()
        if not line: break
        stop_word[line.strip('\n')]=line.strip('\n')
    f.close()



def morphing(content):
    global stop_word
    t=MeCab.Tagger('-d/usr/local/lib/mecab/dic/mecab-ko-dic')
    nodes=t.parseToNode(content.encode('utf-8'))
    MorpList=[]
    while nodes:
        if nodes.feature[0]=='N' and nodes.feature[1]=='N':
            w=nodes.surface
            if not w in stop_word:
                try:
                    w=w.encode('utf-8')
                    MorpList.append(w)
                except:
                    pass
        nodes=nodes.next
    return MorpList


def p1():
    """
    TODO:
    Morph news and update news db
    """
    for doc in db['news_freq'].find():
        doc['morph']=morphing(doc['content'])
        db['news_freq'].update({"_id":doc['_id']},doc)

def p2(url):
    """
    TODO:
    input   : news url
    output  : news morphs
    """
    for doc in db['news_freq'].find():
        if doc['url']==url:
            for i in doc['morph']:
                print(i.encode('utf-8'))
            break
     
def p3():
    """
    TODO:
    copy news morph to new db named news_wordset
    """
    col1=db['news_freq']
    col2=db['news_wordset']
    col2.drop()
    for doc in col1.find():
        new_doc={}
        new_set=set()
        for w in doc['morph']:
            new_set.add(w.encode('utf-8'))
        new_doc['word_set']=list(new_set)
        new_doc['url']=doc['url']
        col2.insert(new_doc)

def p4(url):
    """
    TODO:
    input   : news url
    output  : news wordset
    """
    for doc in db['news_wordset'].find():
        if doc['url']==url:
            for i in doc['word_set']:
                print(i.encode('utf-8'))
            break

def p5(length):
    """
    TODO:
    make frequent item_set
    and inset new dbs (dbname = candidate_L+"length")
    ex) 1-th frequent item set dbbname = candidate_L1
    """
    dbname="candidate_L"+(str)(length)
    col1=db[dbname]
    col1.drop()
    col2=db['news_wordset']
    dic=dict()
    if length==1:
        for doc in col2.find():
            for word in doc['word_set']:
                if word in dic:
                    dic[word]+=1
                else:
                    dic[word]=1
        for i in dic:
            if dic[i]>=10:
                new_doc={}
                new_doc['item_set']=i
                new_doc['support']=dic[i]
                col1.insert(new_doc)

    if length==2:
        for doc in col2.find():
            do=doc['word_set']
            for i in range(0,len(doc['word_set'])):
                for j in range(i+1,len(doc['word_set'])):
                    tempset=set()
                    tempset.add(do[i])
                    tempset.add(do[j])
                    tempset=frozenset(tempset)
                    if tempset in dic:
                        dic[tempset]+=1
                    else:
                        dic[tempset]=1
        for i in dic:
            if dic[i]>=10:
                new_doc={}
                new_doc['item_set']=list(i)
                new_doc['support']=dic[i]
                col1.insert(new_doc)
    if length==3:
        for doc in col2.find():
            do=doc['word_set']
            num=len(doc['word_set'])
            for i in range(0,num):
                for j in range(i+1,num):
                    for k in range(j+1,num):
                        tempset=set()
                        tempset.add(do[i])
                        tempset.add(do[j])
                        tempset.add(do[k])
                        tempset=frozenset(tempset)
                        if tempset in dic:
                            dic[tempset]+=1
                        else:
                            dic[tempset]=1
##시간복잡도가 너무 큽니다...... 프로그램이 너무 오래걸려요...
        for i in dic:
            if dic[i]>=10:
                new_doc={}
                new_doc['item_set']=list(i)
                new_doc['support']=dic[i]
                col1.insert(new_doc)             

def p6(length):
    """
    TODO:
    make strong association rule
    and print all of strong rules
    by length-th frequent item set
    """
    if length==2:
        col2=db['candidate_L2']
        col1=db['candidate_L1']
        for doc in col2.find():
            wordlist=doc['item_set']
            one=wordlist[0]
            two=wordlist[1]
            one_count=1
            for doc2 in col1.find():
                if one in doc2['item_set']:
                    one_count=doc2['support']
                    break;
            result=float(float(doc['support'])/float(one_count))
            if (result>=0.5) & (result<=1):
                print(one+" =>"+two+"\t"+str(result))
            one=wordlist[1]
            two=wordlist[0]
            one_count=1
            for doc2 in col1.find():
                if one in doc2['item_set']:
                    one_count=doc2['support']
                    break;
            result=float(doc['support'])/float(one_count)
            if (result>=0.5)&(result<=1):
                print(one+" =>"+two+"\t"+str(result))
    elif length==3:
        col3=db['candidate_L3']
        col2=db['candidate_L2']
        col1=db['candidate_L1']
        for doc in col3.find():
            wordlist=doc['item_set']
            num=len(wordlist)
            for i in range(0,num):
                one=wordlist[i]
                otherset=set()
                if i==0:
                    otherset.add(wordlist[1])
                    otherset.add(wordlist[2])
                elif i==1:
                    otherset.add(wordlist[0])
                    otherset.add(wordlist[2])
                elif i==2:
                    otherset.add(wordlist[1])
                    otherset.add(wordlist[0])
                one_count=1111111
                for doc1 in col1.find():
                    if one == doc1['item_set']:
                        one_count=doc1['support']
                        break;
                result=float(doc['support'])/float(one_count)
                if result>=0.5:
                    two=list(otherset)[0]
                    three=list(otherset)[1]
                    print(one+" =>"+two+" ,"+three+"\t"+str(result))
                one_count=111111
                for doc2 in col2.find():
                    if otherset == set(doc2['item_set']):
                        one_count=doc2['support']
                        break;
                result=float(doc['support'])/float(one_count)
                if result>=0.5:
                    two=list(otherset)[0]
                    three=list(otherset)[1]
                    print(two+" ,"+three+" =>"+one+"\t"+str(result))



DBname="db20141556"
conn=MongoClient('dbpurple.sogang.ac.kr')
db=conn[DBname]
db.authenticate(DBname,DBname)
#stop_word=[]

if __name__=="__main__":
    make_stop_word()
    printMenu()
    selector = input()
    if selector == 0:
        p0()
    elif selector==1:
        p1()
        p3()
    elif selector==2:
        url=str(raw_input("input news url:"))
        p2(url)
    elif selector==3:
        url=str(raw_input("input news url:"))
        p4(url)
    elif selector==4:
        length=int(raw_input("input length of the frequent item:"))
        p5(length)
    elif selector==5:
        length=int(raw_input("input length of the frequent item:"))
        p6(length)












