#include<iostream>
#include<stdio.h>
#include<map>
#include<cstring>
#include<fstream>
#include<string.h>
#include<stdlib.h>
#include <ctype.h>
#include <unistd.h>

using namespace std;
struct cust
{
	int visit=0;
	int spent=0;
};
struct modstring
{
	string s[100];
	int count=0;
};
int main(int argc, char **argv)
{
	
	map<string,cust> customer; //holds customer id and its visits and amount spent
	map<int,modstring> temp;  //temporary map for sorting purpose
	map<string,int> bookprice; //hold book id and its corresponding price
	map<string,int> bookcount; //holds book id and its corresponding number of purchase
	map<int,string> trnsact;  //holds amount and customer id for corresponding purchase

	string id,temp1,temp2,custid;
	int price,i=0,l,val,c=0,d,r=-1;

	ifstream fin_trans,fin_price;

	map<int,modstring>::iterator it2;
	map<string,cust>::iterator it;
	map<string,int>::iterator it3;
	map<int,string>::iterator it4;


	
	//----------CODE--------------
	 
	 opterr = 0;
  while ((c = getopt (argc, argv, "t:p:r:d:c:")) != -1)
    switch (c)
      {
      case 't':
        fin_price.open(optarg);
        break;
      case 'p':
       fin_trans.open(optarg);
       	while(!fin_trans.eof())
		{
			getline(fin_trans,temp1,',');
			getline(fin_trans,temp2,',');
			bookprice[temp1]=atoi (temp2.c_str());
			bookcount[temp1]=0;
			getline(fin_trans,temp2);
		}
		while(!fin_price.eof())
		{
			getline(fin_price,id,',');
			customer[id].visit++;
			getline(fin_price,temp1);
			l=temp1.length();
			temp2="";
			price=0;
			for(i=0;i<l;i++)
			{
				if(temp1.at(i)!=',')
				temp2+=temp1.at(i);
				else
				{
					bookcount[temp2]++;
					customer[id].spent+=bookprice[temp2];
					price+=bookprice[temp2];
					temp2="";
				}
			}
		
	    	bookcount[temp2]++;
	    	customer[id].spent+=bookprice[temp2];
	    	price+=bookprice[temp2];
	    	trnsact[-price]=id;
		}
        break;
      case 'r':
        r = atoi(optarg);
	
		//section for top N frequent customers and the number of visits they made
		for(it=customer.begin();it!=customer.end();++it)
		{
			val=-(it->second).visit;
			temp[val].s[temp[val].count]=it->first;
			temp[val].count++;
		}
		c=0;
		for(it2=temp.begin();it2!=temp.end();++it2)
		{
			for(i=0;i<it2->second.count;i++)
			cout<<it2->second.s[i]<<" "<<-it2->first<<",";
			c++;
			if(c==r)
			break;
		}
		cout<<"\n";
		temp.clear();
		c=0;
	
		//section for top N highest transactions and the corresponding customerid
		for(it4=trnsact.begin();it4!=trnsact.end();++it4)
		{
			cout<<it4->second<<" "<<-it4->first<<",";
			c++;
			if(c==r)
			break;
		}
		cout<<"\n";
		temp.clear();
		c=0;
	
		//the top N highest selling books and quantity sold
		for(it3=bookcount.begin();it3!=bookcount.end();++it3)
		{
			val=-it3->second;
			temp[val].s[temp[val].count]=it3->first;
			temp[val].count++;
		}
	
		for(it2=temp.begin();it2!=temp.end();++it2)
		{
			for(i=0;i<it2->second.count;i++)
			cout<<it2->second.s[i]<<" "<<-it2->first<<",";
			c++;
			if(c==r)
			break;
		}
		cout<<"\n";
		temp.clear();
		c=0;
	
		//the N least selling books and quantity sold (this includes books that did not sell at all as well
		for(it3=bookcount.begin();it3!=bookcount.end();++it3)
		{
			val=it3->second;
			temp[val].s[temp[val].count]=it3->first;
			temp[val].count++;
		}
	
		for(it2=temp.begin();it2!=temp.end();++it2)
		{
			for(i=0;i<it2->second.count;i++)
			cout<<it2->second.s[i]<<" "<<it2->first<<",";
			c++;
			if(c==r)
			break;
		}
        break;
      case 'd':
        d = atoi(optarg);
        break;
      case 'c':
        custid= optarg;
        if(customer[custid].spent>=d)
        cout<<"1";
        else cout<<"0";
        break;
      case '?':
        if (optopt == 'c')
          fprintf (stderr, "Option -%c requires an argument.\n", optopt);
        else if (isprint (optopt))
          fprintf (stderr, "Unknown option `-%c'.\n", optopt);
        else
          fprintf (stderr,
                   "Unknown option character `\\x%x'.\n",
                   optopt);
        return 1;
      default:
        abort ();
      }
}
