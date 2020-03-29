#include<stdio.h>
struct pro
{
	int pid;
	int b_time;
	int a_time;
	int pr;
	int w_time;
};
int comp_time,bcomp_time=0,r=-1;
int totalp=-1,i=-1;
struct pro list[100],result[100],swap;
int pro_create()
{
	int n;
	printf("No. of processes to run:");
	scanf("%d",&n);
	return n;
}
void pro_exec()
{
	if(totalp>=0)
	{
		int wt,j;
		if(bcomp_time!=0 && list[0].b_time!=0)
		{
			list[0].b_time--;
			bcomp_time--;
			list[0].pr++;
			list[0].a_time=comp_time+1;
			comp_time++;	
			for(wt=1;wt<=totalp;wt++)
			{
				list[wt].pr+=2;
				list[wt].w_time=++list[wt].w_time;
			}
		}
		if(list[0].b_time==0)
		{
			r++;
			result[r]=list[0];
			for(wt=0;wt<totalp;wt++)
			{
				list[wt]=list[wt+1];
			}
			totalp--;
		}
		for(wt=0;wt<totalp;wt++)
		{
			for(j=0;j<totalp;j++)
			{
				if(list[wt].pr<=list[j].pr)
				{
					swap=list[wt];
					list[wt]=list[j];
					list[j]=swap;
				}
			}
		}
		if(list[0].pr<=list[1].pr && totalp>=1)
		{
			swap=list[0];
			for(wt=0;wt<totalp;wt++)
			{
				list[wt]=list[wt+1];
			}
			list[totalp]=swap;
		}
	}
}
void main()
{
	int i,j,n=pro_create(),c=0;
	float avg_wtime=0;
	struct pro pcreate[n];
	for(i=0;i<n;i++)
	{
		pcreate[i].pid=i+1;
		printf("\nArrival time of pro[%d]: ",i+1);
		scanf("%d",&pcreate[i].a_time);
		printf("\nService time of pro[%d]: ",i+1);
		scanf("%d",&pcreate[i].b_time);
		pcreate[i].pr=0;
		pcreate[i].w_time=0;
		bcomp_time=bcomp_time+pcreate[i].b_time;
	}
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
		if(pcreate[i].a_time<pcreate[j].a_time)
		{
			swap=pcreate[i];
			pcreate[i]=pcreate[j];
			pcreate[j]=swap;
		}
		if(pcreate[i].a_time==pcreate[j].a_time)
		{
			if(pcreate[i].b_time<=pcreate[j].b_time)
			{
			swap=pcreate[i];
			pcreate[i]=pcreate[j];
			pcreate[j]=swap;
			}
	 	}
	    }
	}
    printf("Sorted Process Table \n");
    printf(" ");
    printf("processID       Arrival Time        Service Time \n");
    printf(" ");
	for(i=0;i<n;i++)
	{
		printf("\n%d                  %d                      %d\n",pcreate[i].pid,pcreate[i].a_time,pcreate[i].b_time );
	}
	comp_time=pcreate[0].a_time;
	for(j=pcreate[0].a_time;j<=pcreate[n-1].a_time;j++)
	{
		for(i=0;i<n;i++)
		{
			if(pcreate[i].a_time==j && c!=n)
			{
				totalp++;
				list[totalp]=pcreate[i];
				c++;
			}
			if(c==n)
				break;
		}
		pro_exec();
		comp_time++;
	while(bcomp_time!=0 && c==n)
	{
		pro_exec();
		comp_time++;
	}
	if(c==n)
		break;
	}
    printf("Sorted Table w.r.t Completion Time \n");
    printf(" ");
    printf("processID       Arrival Time        Service Time        Waiting Time \n");
    printf(" ");
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if(result[i].pid==pcreate[j].pid)
			{
	printf("\n%d                      %d                      %d                      %d\n",result[i].pid,pcreate[j].a_time,pcreate[j].b_time,result[i].w_time);
			break;
			}
		}
		avg_wtime+=(result[i].w_time);
	}
	printf("AVERAGE  WAITING  TIME :%f\n",avg_wtime/n);
}	
