#include <stdio.h>
#include<stdlib.h>

typedef struct node{
	double meanOfIntegratedProfile;
	double standardDeviationOfTheIntegratedProfile;
	double excessKurtosisOfTheIntegratedProfile;
	double skewnessOfTheIntegratedProfile;
	double meanOfTheDMSNRCurve;
	double standardDeviationOfTheDMSNRCurve;
	double excessKurtosisOfTheDMSNRCurve;
	double skewnessOfTheDMRSNRCurve;
	int class;
	struct node *next;	
}Node;

typedef struct{
	Node *head, *tail;
	int length;
}List;

List *createList()
{
	List *p = (List*)malloc(sizeof(List));
	p->head = p->tail = NULL;
	p->length = 0;
	return p;
}

Node *createNode(double meanOfTheIntegratedProfile, double standardDeviationOfTheIntegratedProfile, double excessKurtosisOfTheIntegratedProfile,double skewnessOfTheIntegratedProfile, double meanOfTheDMSNRCurve, double standardDeviationOfTheDMSNRCurve, double excessKurtosisOfTheDMSNRCurve,double skewnessOfTheDMRSNRCurve,int class)
{
	Node *p = (Node*)malloc(sizeof(Node));
	p->meanOfIntegratedProfile = meanOfTheIntegratedProfile;
	p->standardDeviationOfTheIntegratedProfile = standardDeviationOfTheIntegratedProfile;
	p->excessKurtosisOfTheIntegratedProfile = excessKurtosisOfTheIntegratedProfile;
	p->skewnessOfTheIntegratedProfile = skewnessOfTheIntegratedProfile;
	p->meanOfTheDMSNRCurve = meanOfTheDMSNRCurve;
	p->standardDeviationOfTheDMSNRCurve = standardDeviationOfTheDMSNRCurve;
	p->excessKurtosisOfTheDMSNRCurve = excessKurtosisOfTheDMSNRCurve;
	p->skewnessOfTheDMRSNRCurve = skewnessOfTheDMRSNRCurve;
	p->class = class;
	p->next = NULL;
	return p;
}

void push(List *ulist,double meanOfTheIntegratedProfile, double standardDeviationOfTheIntegratedProfile, double excessKurtosisOfTheIntegratedProfile,double skewnessOfTheIntegratedProfile, double meanOfTheDMSNRCurve, double standardDeviationOfTheDMSNRCurve, double excessKurtosisOfTheDMSNRCurve,double skewnessOfTheDMRSNRCurve,int class)
{
	Node *p = createNode(meanOfTheIntegratedProfile, standardDeviationOfTheIntegratedProfile, excessKurtosisOfTheIntegratedProfile, skewnessOfTheIntegratedProfile, meanOfTheDMSNRCurve, standardDeviationOfTheDMSNRCurve, excessKurtosisOfTheDMSNRCurve, skewnessOfTheDMRSNRCurve, class);
	if(ulist->head)
	{
		ulist->length++;
		p->next = ulist->head;
		ulist->head = p;
	}
	else
	{
		ulist->length = 1;
		ulist->head = ulist->tail = p;
	}
}
void readFile(char *filename, List *ulist)
{
	FILE *fp = fopen(filename,"r");
	double meanOfTheIntegratedProfile, standardDeviationOfTheIntegratedProfile, excessKurtosisOfTheIntegratedProfile, skewnessOfTheIntegratedProfile, meanOfTheDMSNRCurve, standardDeviationOfTheDMSNRCurve, excessKurtosisOfTheDMSNRCurve, skewnessOfTheDMRSNRCurve;
	int class;
	while(fscanf(fp,"%lf %lf %lf %lf %lf %lf %lf %lf %d",&meanOfTheIntegratedProfile,&standardDeviationOfTheIntegratedProfile,&excessKurtosisOfTheIntegratedProfile,&skewnessOfTheIntegratedProfile,&meanOfTheDMSNRCurve,&standardDeviationOfTheDMSNRCurve,&excessKurtosisOfTheDMSNRCurve,&skewnessOfTheDMRSNRCurve,&class) != EOF)
	{
		push(ulist,meanOfTheIntegratedProfile, standardDeviationOfTheIntegratedProfile, excessKurtosisOfTheIntegratedProfile, skewnessOfTheIntegratedProfile, meanOfTheDMSNRCurve, standardDeviationOfTheDMSNRCurve, excessKurtosisOfTheDMSNRCurve, skewnessOfTheDMRSNRCurve, class);

	}	
}

void print(List *ulist)
{
	Node *p = ulist->head;
	while(p != NULL)
	{
		printf("Mean of the integrated profile: %.4lf\nStandard Deviation of the integrated profile: %.4lf\nExcess kurtosis of the integrated profile: %.4lf\nSkewness of the integrated profile: %.4lf\nMean of the DM-SNR curve: %.4lf\nStandard Deviation of the DM-SNR curve: %.4lf\nExcess kurtosis of the DM-SNR curve: %.4lf\n Skewness of the DM-SNR curve: %.4lf\nClass %d\n",p->meanOfIntegratedProfile, p->standardDeviationOfTheIntegratedProfile, p->excessKurtosisOfTheIntegratedProfile, p->skewnessOfTheIntegratedProfile,p->meanOfTheDMSNRCurve, p->standardDeviationOfTheDMSNRCurve, p->excessKurtosisOfTheDMSNRCurve, p->skewnessOfTheDMRSNRCurve, p->class);
		p = p->next;
	}
}

int numberOfZeros(List *ulist)
{
	int count  = 0;
	Node *p = ulist->head;
	while(p != NULL)
	{
		if(p->class == 0)count++;
		p = p->next;
	}
	return count;
}

int numberOfOnes(List *ulist)
{
	int count  = 0;
        Node *p = ulist->head;
        while(p != NULL)
        {
                if(p->class == 1)count++;
                p = p->next;
        }
        return count;
}
void main()
{
	List *stars = createList();
	readFile("pulsar_stars.txt",stars);
	FILE *fp = fopen("README.md","a");
	fprintf(fp,"Dataset contains %d samples\n",stars->length);
	fprintf(fp,"From this dataset we can see that %d samples correspond to class 0\n",numberOfZeros(stars));
	fprintf(fp,"From this dataset we can see that %d samples correspond to class 1\n",numberOfOnes(stars));
}
