#include<stdio.h>
#include<stdlib.h>
void swap(int x,int y)
{
	int temp;
	temp=x;
	x=y;
	y=temp;
}
void shellsort(int R[],int n)
{
	int i,j,d;
	int tmp;
	d=n/2;
	while(d>0)
	{
		for(i=d;i<n;i++)
		{
			tmp=R[i];
			j=i-d;
			while(j>=0&&tmp<R[j])
			{
				R[j+d]=R[j];
				j=j-d;
			}
			R[j+d]=tmp;
		}
		d=d/2;
	}
}
int partition(int R[],int s,int t)
{
	int i=s,j=t;
	int base=R[i];
	while(i<j)
	{
		while(j>i&&R[j]>=base)
			j--;
		if(i<j)
		{
			R[i]=R[j];
			i++;
		}
		while(i<j&&R[i]<=base)
			i++;
		if(i<j)
		{
			R[j]=R[i];
			j--;
		}
	}
	R[i]=base;
	return i;
}
void QuickSort(int R[],int s,int t)
{
	int i;
	if(s<t)
	{
		i=partition(R,s,t);
		QuickSort(R,s,i-1);
		QuickSort(R,i+1,t);
	}
}
void sift(int R[],int low,int high)
{
	int i=low,j=2*i;
	int tmp=R[i];
	while(j<=high)
	{
		if(j<high&&R[j]<R[j+1])
			j++;
		if(tmp<R[j])
		{
			R[i]=R[j];
			i=j;
			j=2*i;
		}
		else break;	
	}
	R[i]=tmp;
}
void HeapSort(int R[],int n)
{
	int i;
	for(i=(n+1)/2;i>=0;i--)
		sift(R,i,n);
	for(i=n;i>=1;i--)
	{
		swap(R[0],R[i]);
		sift(R,1,i-1);
	}
}
void Merge(int R[],int low, int mid, int high)
{
	int *R1;
	int i=low,j=mid+1,k=0;
	R1=(int *)malloc((high-low+1)*sizeof(int *));
	while(i<=mid&&j<=high)
	{
		if(R[i]<R[j])
		{
			R1[k]=R[i];
			i++;k++;
		}
		else
		{
			R1[k]=R[j];
			j++;k++;
		}
	}
	while(i<=mid)
	{
		R1[k]=R[i];
		i++;k++;
	}
	while(j<=high)
	{
		R1[k]=R[j];
		j++;k++;
	}
	for(k=0,i=low;i<=high;k++,i++)
	{
		R[i]=R1[k];
	}
	free(R1);
}
void MergePass(int R[],int length,int n)
{
	int i;
	for(i=0;i+2*length-1<n;i=i+2*length)
		Merge(R,i,i+length-1,i+2*length-1);
	if(i+length-1<n-1)
		Merge(R,i,i+length-1,n-1);
}
void MergeSort(int R[],int n)
{
	int length;
	for(length=1;length<n;length=2*length)
		MergePass(R,length,n);
}
void MergeSortDC(int R[],int low, int high)
{
	int mid;
	if(low<high)
	{
		mid=(low+high)/2;
		MergeSortDC(R,low,mid);
		MergeSortDC(R,mid+1,high);
		Merge(R,low,mid,high);
	}
}
void MergeSort1(int R[],int n)
{
	MergeSortDC(R,0,n-1);
}
void RadixSort(int R[], int n)
{
	int max = R[0];
	int base = 1;
	for (int i = 0; i < n; i++)
	{
		if (R[i] > max)
		{
			max = R[i];
		}
	}
	int* tmp = (int*)malloc(sizeof(int)*n);
	while (max / base > 0)
	{
		int bucket[10] = { 0 };
		for (int i = 0; i < n; i++)
		{
			bucket[R[i] / base % 10]++;
		}
		for (int i = 1; i < 10; i++)
		{
			bucket[i] += bucket[i - 1];
		}
		for (int i = n - 1; i >= 0; i--)
		{
			tmp[bucket[R[i] / base % 10] - 1] = R[i];
			bucket[R[i] / base % 10]--;
		}
		for (int i = 0; i < n; i++)
		{
			R[i] = tmp[i];
		}
		base *= 10;
	}
	free(tmp);
}

int main()
{
	
	printf("ÇëÑ¡ÔñÐèÒªµÄÅÅÐò·½Ê½£º\n1.Ï£¶ûÅÅÐò\n2.¿ìËÙÅÅÐò\n3.¶ÑÅÅÐò\n4.¹é²¢ÅÅÐò\n5.»ùÊýÅÅÐò\n0.ÍË³ö\n");
	int n=1;
	while(n!=0){
		scanf("%d",&n);
	int R[10]={6, 12, 458, 5, 4, 28, 19, 1230, 9, 47};
	if(n == 1) 
		shellsort(R,10);
	else if(n == 2)
		QuickSort(R,0,9);
	else if(n == 3)
		HeapSort(R,10);
	else if(n == 4)
		MergeSort(R,10);
	else if(n == 5)
		RadixSort(R,10);
	else if(n == 0)
		break;
	int i;
	if(n != 3)
	{	
		for(i=0;i<9;i++)
		{
			printf("%d ",R[i]);
		}
		printf("%d\n",R[i]);
	}
	else
		{
		for(i=9;i>0;i--)
		printf("%d ",R[i]);
	printf("%d\n",R[i]); }
}
	return 0;
	
}
