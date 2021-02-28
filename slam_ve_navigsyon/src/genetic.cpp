#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <iostream>
#include <map>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <stdlib.h>     /* srand, rand */
#include <time.h> 
#include <vector>
using namespace std;
#define SIZE 10


int rand_num(int end) 
{ 
    int start =1;
    int rnum = start + rand() % end; 
    return rnum; 
} 
bool repeat(int s[SIZE], int sayi) 
{ 	

	int flag = 0;
    for (int i = 0; i < SIZE; i++) {
        if (s[i] == sayi) 
            {
            	return true;
                      	
			}
    } 
    return false; 
}
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;
typedef map<int,pair<double,double>,less<int>> Midd;
int main(int argc, char **argv)
{
	srand (time(NULL));
	Midd mymap;

    double x[SIZE]={-3.10,-2.85,-1.25,-3.75,-0.75,-1.25,-2.40,-1.20,-4.25,-3.45};
    double y[SIZE]={-1.25,-2.40,-1.20,-2.50,-3.10,-2.85,-2.55,-1.25,-3.75,-0.75};
    for (int i=0;i<SIZE;i++)
    {	pair<double,double> temp(x[i],y[i]);
    	mymap.insert (Midd::value_type(i+1,temp));
	}
   

    double kr[SIZE+1][SIZE+1]={};

    map<int,pair<double,double>>::iterator it;
    map<int,pair<double,double>>::iterator it2;

    
    for (int i = 0; i < SIZE; i++)
    {   
        it = mymap.find(i+1);

        for (int j = 0; j < SIZE; j++)
        {
            it2 = mymap.find(j+1);
            // x ekseni       it2->second.first;
            // y ekseni       it2->second.second;
            // x ekseni       it->second.first;
            // y ekseni       it->second.second;
            kr[i+1][j+1]=sqrt((pow((it2->second.first-it->second.first),2)+pow((it->second.second-it2->second.second),2)));
        }
        
    }
    
	for(int i = 0;i <SIZE ;i++)
	{
		
		for(int j=0;j<SIZE ;j++)
		cout << setw(8) << setprecision(3) << kr[i+1][j+1] ;
		cout <<endl << endl;
	}
	
	cout << endl << "--------------------------------------------------------------------------------" << endl;
    int holder =0;
	int kromozom[SIZE][SIZE]={};
	
	int a[SIZE] ={};
	for(int i=0 ;i<SIZE;i++)
	{	
		for(int j=0 ; j<SIZE ; j++)
		{
		holder = rand_num(10);
		while(repeat(a,holder)==true)
		{
			holder = rand_num(10);
		}
			a[j]= holder;
			kromozom[i][j]=holder;
		}
		holder = 0;
		for (int f=0;f<SIZE;f++)
		{
			a[f]=0;
		}
	} 
	cout << endl;
	cout << "Kromozom" << endl;
	for (int i = 0 ;i<SIZE ;i++)
	{
		for (int j =0 ; j<SIZE ; j++)
		{
			cout<< setw(8) << kromozom[i][j] ;
		}
		cout << endl << endl;
	}

	double maliyet[SIZE] = {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
	double tutucu=0.0;
	
	for(int i =0 ;i<SIZE;i++)
	{
		for(int j=0 ;j<SIZE ; j++)
		{
			it = mymap.find(kromozom[i][j]);
			tutucu = 0;
			for(int k=0 ; k<SIZE ; k++)
			{
				it2 = mymap.find(kromozom[i][k]);
				tutucu=tutucu+sqrt((pow((it2->second.first-it->second.first),2)+pow((it->second.second-it2->second.second),2)));
			}
			maliyet[j]=tutucu;

		}
		
	}
cout << endl << "--------------------------------------------------------------------------------" << endl;

	for(int i=0;i<SIZE;i++)
	{
		cout << setw(8) << fixed  << setprecision(2) << maliyet[i] ;
	}

cout << endl << "--------------------------------------------------------------------------------" << endl;

	// Sıra çaprazlamaları
	// rastgele bir segment şecilir burada 
	// bir segmen seçilir .Diğer kromozama aktarılır.
	//rastgele ikitane kromozom şeçilir.

	int holder1[SIZE]={};
	int holder2[SIZE]={};
	int b1,b2;
	int lower,upper;
	double cost1=0.0;
	double cost2=0.0;
	int counter2=0;
	int counter3=0;
	int tutucu1[SIZE]={};
	int tutucu2[SIZE]={};
	int bu=0;
	for(int v=0;v<50;v++)
{
		counter2=0;
		counter3=0;
		cost1=0.0;
		cost2=0.0;
		b1=0;
		b2=0;
		lower=0;
		upper=0;

		for(int i=0;i<SIZE;i++)
		{
				tutucu1[i]=0.0;
				tutucu2[i]=0.0;
		}
		
		for(int f=0;f<SIZE;f++)
		{
			holder1[f]=0;
			holder2[f]=0;
		}
		
		b1=rand()%10;
		b2=rand()%10;
		while(b1==b2)
		{	
			b1=rand()%10;
		}
		cout <<endl;
		cout << "b1 = " << b1 << "    b2 = " << b2 << endl;
		
		lower=rand_num(5);
		upper=rand_num(8);
		while(upper <=lower || (1 >=(upper-lower)) || lower==1)
		{	
			lower =rand_num(5);
			upper=rand()%10;
		}
		cout << endl;	
		cout <<"Upper" <<upper<< endl;
		cout <<"Lover" <<lower<< endl;
		for(int i=lower;i<upper;i++)
		{
			holder1[i]=kromozom[b2][i];
			holder2[i]=kromozom[b1][i];
		}
		for(int i=0;i<SIZE;i++)
		{
			tutucu1[i]=0;
			tutucu2[i]=0;
		}
		for(int i=0;i<SIZE;i++)
		{
			tutucu1[i]=holder1[i];
			tutucu2[i]=holder2[i];
		}
		int k=0 ;
		while(k<SIZE && counter2 < 10)
		{
			
			if(repeat(tutucu1,kromozom[b1][k]))
			{
				k++;
			}
			else
			{ 
				if(counter2<lower)
				{	//cout << "counter2 1  : " << counter2 << endl;
					holder1[counter2]=kromozom[b1][k];
					counter2++;
					k++;
				}	
				if(counter2>=lower && counter2<upper)
				{	//cout << "counter2 2  : " << counter2 << endl;
					counter2++;
				
				} 
				if(counter2>=upper)
				{	//cout << "counter2 3  : " << counter2 << endl;
					holder1[counter2]=kromozom[b1][k];
					counter2++;	
					k++;
				}	 
			}
		}
		k=0;
		
		while(k<SIZE && counter3 < 10 )
		{
			if(repeat(tutucu2,kromozom[b2][k]))
			{
				k++;
			}
			else
			{
				if(counter3<lower)
				{
					holder2[counter3]=kromozom[b2][k];
					counter3++;
					k++;	
				}
				if(counter3>=lower && counter3< upper)
				{
					counter3++;	
				}	
				if(counter3>=upper)
				{	
					holder2[counter3]=kromozom[b2][k];
					counter3++;
					k++;
				}
			}
		}		
		double maliyet2[10]={};

		for(int m=0 ;m<SIZE ; m++)
		{
			it = mymap.find(holder1[m]);
			tutucu = 0;
			for(int k=0 ; k<SIZE ; k++)
			{
				it2 = mymap.find(holder1[k]);
				tutucu=tutucu+sqrt((pow((it2->second.first-it->second.first),2)+pow((it->second.second-it2->second.second),2)));
			}
			maliyet2[0]=tutucu;
		}

		for(int m=0 ;m<SIZE ; m++)
		{
			it = mymap.find(holder2[m]);
			tutucu = 0;
			for(int k=0 ; k<SIZE ; k++)
			{
				it2 = mymap.find(holder1[k]);
				tutucu=tutucu+sqrt((pow((it2->second.first-it->second.first),2)+pow((it->second.second-it2->second.second),2)));
			}
			maliyet2[1]=tutucu;	
		}
	cout <<"1 incisi ebevyn icin maliyet : " << maliyet[b1] << endl;
	cout << "2 incisi ebevyn icin  maliyet : " << maliyet[b2] << endl;	
	cout << endl;
	cout << endl;	
	cout << "1 incisi cocul maliyet : " << maliyet2[0] << endl;
	cout << "2 incisi cocuk maliyet : " << maliyet2[1] << endl ;
	cout << endl;
for(int i=0;i<SIZE;i++)
{
	cout<<setw(3) <<kromozom[b1][i];
}
cout << endl;
for(int i=0;i<SIZE;i++)
{
	cout<<setw(3) <<kromozom[b2][i];
}
cout << endl;
for(int i=0;i<SIZE;i++)
{
	cout<<setw(3) <<holder1[i];
}
cout << endl;
for(int i=0;i<SIZE;i++)
{
	cout<<setw(3) <<holder2[i];
}
cout << endl;

if(maliyet[b1]>maliyet2[0])
{
	for(int l=0;l<SIZE;l++)
		{
			kromozom[b1][l]=holder1[l];
		}
		maliyet[b1] = maliyet2[0];
}
	if(maliyet[b2]>maliyet2[1])
	{
		for(int l=0;l<SIZE;l++)
		{
			kromozom[b2][l]=holder2[l];
		}
			maliyet[b2] = maliyet2[1];		
	}
cout << endl ;
cout << "Degisme isleminden sonra" << endl;
for(int i=0;i<SIZE;i++)
{
	cout<<setw(3) <<kromozom[b1][i];
}
cout << endl;
for(int i=0;i<SIZE;i++)
{
	cout<<setw(3) <<kromozom[b2][i];
}


}
cout << endl << "--------------------------------------------------------------------------------" << endl;
cout << endl << "--------------------------------------------------------------------------------" << endl;
for(int i=0;i<SIZE;i++)
{
	cout<<setw(3) <<kromozom[b1][i];
}
cout << endl;
for(int i=0;i<SIZE;i++)
{
	cout<<setw(3) <<kromozom[b2][i];
}
cout << endl;

cout << endl << "--------------------------------------------------------------------------------" << endl;
cout << endl << "--------------------------------------------------------------------------------" << endl; 
	for (int i = 0 ;i<SIZE ;i++)
	{
		for (int j =0 ; j<SIZE ; j++)
		{
			cout<< setw(8) << fixed << kromozom[i][j] ;
		}
		cout << endl << endl;
	}   
cout << endl << "--------------------------------------------------------------------------------" << endl;
cout << endl << "--------------------------------------------------------------------------------" << endl;  
 
 	for(int i=0;i<SIZE;i++)
	{
		cout << setw(8) << fixed  << setprecision(2) << maliyet[i] ;
	}  
   	int index=0;
	double v = maliyet[0];
	for (int i = 0; i < SIZE; i++)
	{
		if(v  >= maliyet[i])
		{
			v = maliyet[i];
			index=i;
		}
	}
	cout << "v :" << v << endl;
	cout << "index :" << index << endl;
	// en düşük mailyet bulunur
	// artık bizim rotamız kromozm [v] bizim istediğimiz nokta 

	int i =0;
	it = mymap.find(kromozom[index][i]);
	it2 = mymap.find(kromozom[index][i+1]);
	double bnx=it->second.first;
	double bny=it->second.second;
	double bnz=(it2->second.second-it->second.second)/(it2->second.first-it->second.first);

 	ros::init(argc, argv, "simple_navigation_goals");
 
	//tell the action client that we want to spin a thread by default
	MoveBaseClient ac("move_base", true);

	//wait for the action server to come up
	while(!ac.waitForServer(ros::Duration(5.0))){
		ROS_INFO("Waiting for the move_base action server to come up");
	}


	move_base_msgs::MoveBaseGoal goal;
	
	//we'll send a goal to the robot to move 1 meter forward
	goal.target_pose.header.frame_id = "map";
	goal.target_pose.header.stamp = ros::Time::now();

	goal.target_pose.pose.position.x = bnx;
	goal.target_pose.pose.position.y = bny;
	goal.target_pose.pose.orientation.z = bnz;
	i++;
	ROS_INFO("Sending goal");
	ac.sendGoal(goal);

	ac.waitForResult();

	

	if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
	{
		ROS_INFO("hedefe vardi");
	while(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED && i<10)  
		{	 
		while(!ac.waitForServer(ros::Duration(5.0))){
		ROS_INFO("Waiting for the move_base action server to come up");
			}
		move_base_msgs::MoveBaseGoal goal1;
		goal1.target_pose.header.frame_id = "map";
		goal1.target_pose.header.stamp = ros::Time::now();

		it = mymap.find(kromozom[index][i]);
		it2 = mymap.find(kromozom[index][i+1]);
		bnx=it->second.first;
		bny=it->second.second;
		bnz=(it2->second.second-it->second.second)/(it2->second.first-it->second.first);
		ROS_INFO("X ekseninde : %f  Y ekseninde : %f  noktalarına gidiyor.",bnx,bny);
		goal1.target_pose.pose.position.x = bnx;
		goal1.target_pose.pose.position.y = bny;
		goal1.target_pose.pose.orientation.z = bnz;
		i++;
		ROS_INFO("Sending goal");
		ac.sendGoal(goal1);
		
		ROS_INFO("i = %d",i);
		ac.waitForResult();
		ROS_INFO("hedefe vardi");
	} }   
else
    ROS_INFO("bir hata meyfana geldi");

    /* code */
    
    return 0;
}