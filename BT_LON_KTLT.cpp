#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<ctype.h>
#include<string.h>
#define max 20
#define MAXCHAR 10000

void NhapMaTran(float *a, int dong, int cot);
void XuatMaTran(float *a, int dong, int cot);
void NhapVecto(float *b,int dong);
void XuatVecto( float *b, int dong);

float norm_row( float *a, int n);
float norm_col(float a[max][max], int n);

int kt_hoi_tuDON(FILE *f, float *a, float *b, float *alpha1, int dong, int cot);
void loop_kDON(FILE *f,float *a, float *b,float x[max], float x0[max], int n, int k);
void loop_eps1(FILE *f,float *a, float *b, float x[max], float x0[max],float epsi, int n);

int cheotroi(FILE *f,float *a, int dong, int cot);
float * kt_hoi_tuSEIDEL(FILE *f,float *a,float *b,int h,int dong, int cot);
void loop_kSEIDEL(FILE *f,float *a, float *b,float x[max], float x0[max], int n, int k);
void loop_eps2(FILE *f,float *a, float *b, float x[max], float x0[max],float epsi, int n);

void writeA(FILE *f, float *a, int dong, int cot);
void writeB(FILE *f, float *b, int n, int cot);
int read_FILE();

int main()
{
	int dong, cot;
    
    float x[max], s[max], x0[max];
	
	int i,j,k,n,dem,t1,kt=0;
	float epsi,lamda,sum;
	double ss;
	char ans;
	printf("Nhap so dong: ");
	scanf("%d",&dong);
	printf("Nhap so cot: ");
	scanf("%d",&cot);
    float size = dong * cot * sizeof(int);
    float*a = (float *)malloc (size);
    float *b = (float *) malloc (sizeof (float));
    float *alpha1 = (float *)malloc (size);
    float *alpha2 = (float *)malloc (size);
    int choose;
    
    FILE *fp = fopen("D:\\C project\\final_exam.txt", "w");
    fprintf(fp,"--------------CAC KET QUA THU DUOC LUU O DAY!!!-----------------\n");
    fclose(fp);
    fp = fopen("D:\\C project\\final_exam.txt","a");
    do{

	printf("-------------------MENU LUA CHON----------------------\n");
	printf("1.Nhap vao ma tran A va vector B\n");
	printf("2.Tinh chuan va kiem tra tinh hoi tu cua phuong phap lap don\n");
	printf("3.Tinh nghiem gan dung voi k cho truoc va kiem tra sai so hau nghiem(tien nghiem) cho pp Lap don\n");
	printf("4.Tinh nghiem gan dung voi epsilon cho truoc theo cong thuc sai so hau nghiem(tien nghiem) cho Lap don\n");
	
	printf("5.Kiem tra tinh cheo troi cua ma tran A(pp lap Seidel)\n");
	printf("6.Tinh chuan va kiem tra tinh hoi tu cua phuong phap lap Seidel\n");
	printf("7.Tinh nghiem gan dung voi k cho truoc va kiem tra sai so hau nghiem(tien nghiem) cho pp Lap Seidel\n");
	printf("8.Tinh nghiem gan dung voi epsilon cho truoc theo cong thuc sai so hau nghiem(tien nghiem) cho Lap Seidel\n");
	
	printf("9.Hien thi ket qua duoc ghi trong file ra man hinh!\n");
	printf("10.Thoat chuong trinh!!! \n");
	printf("Nhap lua chon cua ban: ");
	scanf("%d",&choose);
	int check;
	switch (choose)
	{
		case 1: 
		     printf("\nNhap ma tran A:\n");
		     NhapMaTran(a, dong, cot);
		     XuatMaTran(a, dong, cot);
		     printf("\nNhap vector B:\n");
		     NhapVecto(b, cot);
		     XuatVecto(b, cot);
		     writeA(fp,a,dong,cot);
		     writeB(fp,b,dong,1);
		     break;
		case 2:
			fprintf(fp,"2.Tinh chuan va kiem tra tinh hoi tu cua phuong phap lap don\n");
			kt = kt_hoi_tuDON(fp,a, b, alpha1, dong,cot);
			break;
		case 3:
			if (kt ==1) 
			{	printf("Nhap so lan lap k= ");
				scanf("%d",&k);
				fprintf(fp,"\n3.Tinh nghiem gan dung voi k cho truoc va kiem tra sai so hau nghiem(tien nghiem) cho pp Lap don\n");
				loop_kDON(fp,alpha1, b, x, x0, dong, k);
				}
			else {	printf("Do chuan alpha < 1 nen pp lap ko hoi tu\n");
					fprintf(fp,"Do chuan alpha < 1 nen pp lap ko hoi tu\n");
					}
			break;
		case 4:
			if (kt == 1)
			{  	printf("\nNhap sai so epsilon = ");
				scanf("%f",&epsi);
				fprintf(fp,"\n4.Lap don voi sai so cho truoc epsilon = %.10f\n",epsi);
				loop_eps1(fp,alpha1,b,x,x0,epsi,dong);
			}
			else {	printf("Do ma tran alpha co chuan > 1 nen pp lap don ko hoi tu!\n");
					fprintf(fp,"Do ma tran alpha co chuan > 1 nen pp lap don ko hoi tu!\n");
				}
			break;
		case 5:
			 fprintf(fp,"\n5.Kiem tra tinh cheo troi cua ma tran A (pp lap Seidel)");
			 check = cheotroi(fp,a,dong,cot);
			 if (check == 1)
			 {	 printf("\n >>>>> MA TRAN A LA MA TRAN CHEO TROI HANG! <<<<<\n");
			 	 fprintf(fp,"\n >>>>> MA TRAN A LA MA TRAN CHEO TROI HANG! <<<<<\n");
			 	 }
			 break;
		case 6:
			 fprintf(fp,"\n6.Tinh chuan va kiem tra tinh hoi tu cua phuong phap lap Seidel\n");
			 check = cheotroi(fp,a,dong,cot);
			 alpha2 = kt_hoi_tuSEIDEL(fp,a, b, check, dong,cot);
			 break;
		case 7:
			printf("Nhap so lan lap k= ");
			scanf("%d",&k);
			fprintf(fp,"\n7.Tinh nghiem gan dung voi k cho truoc va kiem tra sai so hau nghiem(tien nghiem) cho pp Lap Seidel\n",k);
			loop_kSEIDEL(fp,alpha2, b, x, x0, dong, k);
			break;
		case 8:
			printf("\nNhap sai so epsilon = ");
			scanf("%f",&epsi);
			fprintf(fp,"\n8.Lap seidel voi sai so cho truoc epsilon = %.10f\n",epsi);
			loop_eps2(fp,alpha2, b, x, x0, epsi, dong );
			break;
		case 9:
    	    fclose(fp);
    	    read_FILE();
			break;
		case 10:
			printf("\nThoat chuong trinh!!!");
			fprintf(fp,"\nKet thuc chuong trinh!!!");
			break;
	}
	printf("\n");
	}
	while (choose != 10);
	fclose(fp);
	free(a);
	free(b);
 	free(alpha1);
 	free(alpha2);
	return 1;
}

float norm_row( float *a, int n)
{   int i,j;
    float norm = 0 , sum[max];
    for ( i=0; i<n; i++)
         {   sum[i] = 0;
             for ( j=0; j<n; j++)
                 sum[i] += fabs(a[i*n +j]);
         }
    for ( i=0; i<n; i++)
       if (sum[i] > norm)  norm = sum[i];
    return norm;
}

float norm_col(float a[max][max], int n)
{   int i,j;
    float norm=0 , sum[max];
    for ( j=0; j<n; j++)
         {   sum[j] = 0;
             for ( i=0; i<n; i++)
                 sum[j] += fabs(a[i][j]);
         }
    for ( i=0; i<n; i++)
       if (sum[i] > norm)  norm = sum[i];
    return norm;
}

void NhapMaTran(float *a, int dong, int cot)
{
    int i;
     for( i = 0; i < dong * cot; i++)
    {
        printf(" a[%d, %d] = ", i / cot, i % cot);
        scanf("%f", a + i);
    }
}
void XuatMaTran(float *a, int dong, int cot)
{
    int i, j;
    printf("\n");
    for(i = 0; i < dong; i++)
    {
        for(j = 0; j < cot; j++)
            printf("%.3f  ", *(a+i * cot + j));
        printf("\n");
    }
}

int cheotroi(FILE *f,float *a, int dong, int cot)
{   int i,j;
    float t;
	for (i=0; i<dong; i++)
	    {    
		   t=0;
		   for (j=0; j<cot; j++)
		      if (i != j) t += fabs(a[i * cot + j]);
		   if (t > fabs(a[i * cot + i]))  
		      {  
		         printf("MA TRAN A KHONG CHEO TROI HANG\n");
		         fprintf(f,"MA TRAN A KHONG CHEO TROI HANG\n");
		         return 0;
		       }
		}
	return 1;
}
void loop_kSEIDEL(FILE *f,float *a, float *b,float x[max], float x0[max], int n, int k)
{
    int i, j, kt = 0,dem = 0;
    float sum1, sum2, ss=0, ss1=0, lamda;
    lamda = norm_row(a,n);
    
    printf("\nVecto xap xi ban dau X0 la: ");
    fprintf(f,"\nVecto xap xi ban dau X0 la: ");
	for (i=0; i<n; i++)
	     {  
		    x[i] = b[i];
			x0[i] = b[i];
			printf(" %.3f ",x0[i]);
			fprintf(f," %.3f ",x0[i]);
		 }
    while (kt == 0)
       {
       	   dem += 1;
       	   printf("\nLan lap thu %d : ",dem);
       	   fprintf(f,"\nLan lap thu %d : ",dem);
       	   for (i=0; i<n; i++)
	   	  	{   sum1 = 0;
	   	  	    sum2 = 0;	   	  	    
			    for (j=0; j<n; j++)
	   	        	{   if (j<i)
	   	    	            sum1 += a[i * n + j] * x[j];
	   	    	        else if (j>i)
	   	    	            sum2 += a[i * n + j] * x0[j]; 
						  }
	   	    	x[i] = b[i] + sum1 + sum2;
	   	    	printf(" %.20f  ",x[i]);
				fprintf(f," %.20f  ",x[i]);	
			    	 
			for (j=0; j<n; j++)
	   	    	    if (fabs(x[j]-x0[j]) > ss) 
					    ss = fabs(x[j] - x0[j]) ;
			ss = ss * (lamda/(1-lamda));
			}
		
			printf("\tSai so = %.20f",ss);
			fprintf(f,"\tSai so = %.20f",ss);
			
			if (dem==1) 
			    {   for (j=0; j<n; j++)
	   	    	        if (fabs(x[j]-x0[j]) > ss1) 
					        ss1 = fabs(x[j] - x0[j]) ;
			        ss1 = ss1 * (pow(lamda,k)/(1-lamda));
				}
				
			if (dem >= k)
			    kt =1;
			else 
			    for(int count=0; count<n; count++)
			   	     x0[count] = x[count];
			 
	   }	
	   printf("\nSai so tien nghiem = %.20f",ss1);
	   fprintf(f,"\nSai so tien nghiem = %.20f",ss1);
	   printf("\nSai so hau nghiem sau %d lan lap = %.20f",dem,ss);
	   fprintf(f,"\nSai so hau nghiem sau %d lan lap = %.20f",dem,ss);

}

void loop_kDON(FILE *f,float *a, float *b,float x[max], float x0[max], int n, int k)
{
    int i, j, kt = 0,dem = 0;
    float tmp[max];
    float ss=0, ss1=0, lamda;
    lamda = norm_row(a,n);
    
    printf("\nVecto xap xi ban dau X0 la: ");
    fprintf(f,"\nVecto xap xi ban dau X0 la: ");
	for (i=0; i<n; i++)
	     {  
			x0[i] = b[i];
			printf(" %.3f ",x0[i]);
			fprintf(f," %.3f ",x0[i]);
		 }
    while (kt == 0)
       {
       	dem += 1;
       	printf("\nLan lap thu %d : ",dem);
    	fprintf(f,"\nLan lap thu %d : ",dem);     	   
        for (i=0; i<n ; i++)
        	{	tmp[i]=0;
            	for (j=0; j<n; j++)
					 tmp[i] += a[i * n +j]*x0[j];
            	tmp[i]= tmp[i]+b[i];
            	
        	}
        for (i=0; i<n; i++)
        {	x[i]= tmp[i];
			printf(" %.20f ",x[i]);
			fprintf(f," %.20f ",x[i]);
		}
		for (j=0; j<n; j++)
	   	    if (fabs(x[j]-x0[j]) > ss) 
				ss = fabs(x[j] - x0[j]) ;
		ss = ss * (lamda/(1-lamda));
		
		printf("\tSai so = %.15f",ss);
		fprintf(f,"\tSai so = %.15f",ss);
			
		if (dem==1) 
		{   for (j=0; j<n; j++)
	   	    	if (fabs(x[j]-x0[j]) > ss1) 
					ss1 = fabs(x[j] - x0[j]) ;
			ss1 = ss1 * (pow(lamda,k)/(1-lamda));
		}
				
		if (dem >= k)
			kt =1;
		else 
			for(int count=0; count<n; count++)
			   	x0[count] = x[count];
	   }	
	   printf("\nSai so tien nghiem = %.15f",ss1);
	   fprintf(f,"\nSai so tien nghiem = %.15f",ss1);
	   printf("\nSai so hau nghiem sau %d lan lap = %.15f",dem,ss);
	   fprintf(f,"\nSai so hau nghiem sau %d lan lap = %.15f",dem,ss);

}
void loop_eps1(FILE *f,float *a, float *b, float x[max], float x0[max],float epsi, int n)
{
	int i,j, kt = 0, dem = 0;
	float tmp[max];
    float ss=0,ss1=0, lamda;
    lamda = norm_row(a,n);
    printf("\nChuan ma tran alpha lamda = %.3f",lamda);
	 //thuc hien lap den khi sai so < epsilon
	printf("\nVecto xap xi ban dau X0 la: ");
	fprintf(f,"\nVecto xap xi ban dau X0 la: ");
	for (i=0; i<n; i++)
	     {  
			x0[i] = b[i];
			printf(" %.8f ",x0[i]);
			fprintf(f," %.8f ",x0[i]);
		 }
	 while (kt == 0)
       {
       	   dem += 1;
       	   printf("\nLan lap thu %d : ",dem);
       	   fprintf(f,"\nLan lap thu %d : ",dem);
       	   for (i=0; i<n; i++)	  	    
			{   tmp[i] = 0;
            	for (j=0; j<n; j++)
					 tmp[i] += a[i * n +j]*x0[j];
            	tmp[i] = tmp[i] + b[i];
            	
        	}
			for (i=0; i<n; i++)	
			    {
				 	x[i] = tmp[i];   
					printf(" %.20f ",x[i]);
					fprintf(f," %.20f ",x[i]); 	 
				}
			for (j=0; j<n ; j++)
	   	    	if ( fabs(x[j]-x0[j]) > ss ) 
					ss = fabs(x[j] - x0[j]) ;
			ss = ss * (lamda/(1-lamda));
			printf("\tSai so = %.20f",ss);
			fprintf(f,"\tSai so = %.20f",ss);
			 
			if (dem==1) 
			    {   for (j=0; j<n; j++)
	   	    	        if (fabs(x[j]-x0[j]) > ss1) 
					        ss1 = fabs(x[j] - x0[j]) ;
				}
			    
			if (ss < epsi)
			    kt =1;
			 else 
			    for(int count=0; count<n; count++)
			   	     x0[count] = x[count];
		}
		ss1 = ss1 * (pow(lamda,dem)/(1-lamda));
		printf("\nSai so tien nghiem = %.20f",ss1);
		fprintf(f,"\nSai so tien nghiem = %.20f",ss1);
		printf("\nSai so hau nghiem sau %d lan lap la : %.20f",dem,ss);	
		fprintf(f,"\nSai so hau nghiem sau %d lan lap la : %.20f",dem,ss);	
}

void loop_eps2(FILE *f,float *a, float *b, float x[max], float x0[max],float epsi, int n)
{
	int i, j, kt = 0, dem = 0;
    float sum1, sum2, ss=0,ss1=0, lamda;
    lamda = norm_row(a,n);
    printf("\nChuan ma tran alpha lamda = %.3f",lamda);
	 //thuc hien lap den khi sai so < epsilon
	printf("\nVecto xap xi ban dau X0 la: ");
	fprintf(f,"\nVecto xap xi ban dau X0 la: ");
	for (i=0; i<n; i++)
	     {  
		    x[i] = b[i];
			x0[i] = b[i];
			printf(" %.8f ",x0[i]);
			fprintf(f," %.8f ",x0[i]);
		 }
	 while (kt == 0)
       {
       	   dem += 1;
       	   printf("\nLan lap thu %d : ",dem);
       	   fprintf(f,"\nLan lap thu %d : ",dem);
       	   for (i=0; i<n; i++)
	   	    {   sum1 = 0;
	   	  	    sum2 = 0;	   	  	    
			    for (j=0; j<n; j++)
	   	        	{   if (j<i)
	   	    	            sum1 += a[i * n +j] * x[j];
	   	    	        else if (j>i)
	   	    	            sum2 += a[i * n +j] * x0[j]; 
						  }
	   	    	x[i] = b[i] + sum1 + sum2;
	   	    	printf(" %.20f  ",x[i]);
				fprintf(f," %.20f  ",x[i]);	
			    	 
			    for (j=0; j<n ; j++)
	   	    	    if (fabs(x[j]-x0[j]) > ss) 
					    ss = fabs(x[j] - x0[j]) ;
			    ss = ss * (lamda/(1-lamda));
			}
			printf("\tSai so = %.20f",ss);
			fprintf(f,"\tSai so = %.20f",ss);
			 
			if (dem==1) 
			    {   for (j=0; j<n; j++)
	   	    	        if (fabs(x[j]-x0[j]) > ss1) 
					        ss1 = fabs(x[j] - x0[j]) ;
				}
			    
			if (ss < epsi)
			    kt =1;
			 else 
			    for(int count=0; count<n; count++)
			   	     x0[count] = x[count];
		}
		ss1 = ss1 * (pow(lamda,dem)/(1-lamda));
		printf("\nSai so tien nghiem = %.20f",ss1);
		fprintf(f,"\nSai so tien nghiem = %.20f",ss1);
		printf("\nSai so hau nghiem sau %d lan lap la : %.20f",dem,ss);	
		fprintf(f,"\nSai so hau nghiem sau %d lan lap la : %.20f",dem,ss);	
}
int kt_hoi_tuDON(FILE *f, float *a, float *b, float *alpha1, int dong, int cot)
{  
	float lamda;
	int i,j;
	for ( i=0; i<dong; i++)
	    for (j=0; j<cot; j++)
	    	if (i==j)
				alpha1[i*cot +j] = 1 - *(a+i * cot + j);
			else 
				alpha1[i*cot +j] = - *(a+i * cot + j);
	lamda = norm_row(alpha1,dong);
	
	printf("\nMa tran alpha la:\n");
	fprintf(f,"Ma tran alpha la:\n");

	for (i=0; i<dong; i++)
	    {   for (j=0; j<cot; j++)
		        {   printf("%f ",alpha1[i * cot +j]);
		        	fprintf(f,"%f ",alpha1[i * cot +j]);}
		    printf("\n");
		    fprintf(f,"\n");
		} 
	printf("\nVector beta la: ");
	fprintf(f,"\nVector beta la: ");
	for (i=0; i<dong; i++)
	     {  printf("%f  ",b[i]);
	     	fprintf(f,"%f  ",b[i]);
		 }
	printf("\n");	fprintf(f,"\n");
	if (lamda<1) 
	{	printf("\n >>>>> PHUONG PHAP LAP DON HOI TU VI CHUAN MA TRAN ALPHA = %.3f < 1  <<<<<\n",lamda);
		fprintf(f,"\n >>>>> PHUONG PHAP LAP DON HOI TU VI CHUAN MA TRAN ALPHA = %.3f < 1  <<<<<\n",lamda);
		return 1;
	}
	else
	{	printf("\n >>>>> PHUONG PHAP LAP DON KHONG HOI TU VI CHUAN MA TRAN ALPHA = %.3f > 1  <<<<<\n",lamda);
		fprintf(f,"\n >>>>> PHUONG PHAP LAP DON KHONG HOI TU VI CHUAN MA TRAN ALPHA = %.3f > 1  <<<<<\n",lamda);
		return 0;
	}    
}	
float * kt_hoi_tuSEIDEL(FILE *f,float *a,float *b,int h,int dong, int cot)
{   float s[max], x[max], x0[max],lamda;
	float size = dong * cot * sizeof(int);
    float*alpha = (float *)malloc (size);  
	int i,j;
	if (h==1) 
	   {
	    for ( i=0; i<dong; i++)
	     {  s[i] = 0;
		    for ( j=0; j<cot; j++)
	           { 
	             if (j !=i)
			      alpha[i*cot +j] = -*(a+i * cot + j)/ *(a+i * cot + i);
	            }  
		    b[i] = b[i]/ *(a+i * cot + i);
	        alpha[i * cot +i] = 0;
	     } 
	    }
    lamda= norm_row(alpha,dong);
	if (lamda<1) 
	{	printf("\n >>>>> PHUONG PHAP LAP SEIDEL HOI TU VI CHUAN MA TRAN ALPHA = %.3f <1  <<<<<\n",lamda);
		fprintf(f,"\n >>>>> PHUONG PHAP LAP SEIDEL HOI TU VI CHUAN MA TRAN ALPHA = %.3f <1  <<<<<\n",lamda);
	}
	printf("Ma tran alpha la:\n");
	fprintf(f,"Ma tran alpha la:\n");
	for (i=0; i<dong; i++)
	    {   for (j=0; j<cot; j++)
		        {   printf("%f ",alpha[i * cot +j]);
		        	fprintf(f,"%f ",alpha[i * cot +j]);}
		    printf("\n");
		    fprintf(f,"\n");
		} 		
	printf("\nVector beta la: ");
	fprintf(f,"\nVector beta la: ");
	for (i=0; i<dong; i++)
	     {  printf("%f  ",b[i]);
	     	fprintf(f,"%f  ",b[i]);
		 }
	printf("\n");	fprintf(f,"\n");
	return alpha;
}	
void NhapVecto(float *b,int dong)
{
	int i;
     for(i = 0; i < dong ; i++)
    {
        printf("b[%d] = ", i);
        scanf("%f", b + i);
    }
    
}
void XuatVecto( float *b, int dong)
{
	int i;
	for (i=0; i< dong; i++)
	    printf("%.3f  ", *(b+i));
}
void writeA(FILE *f, float *a, int dong, int cot)
{
	int i,j;
	fprintf(f,"Ma tran A la:\n");
	for(i = 0; i < dong; i++)
    {
        for(j = 0; j < cot; j++)
            fprintf(f,"%f  ", *(a+i * cot + j));
        fprintf(f,"\n");
    }
}

void writeB(FILE *f, float *b, int n, int cot)
{  
	fprintf(f,"\nVecto B la: ");
	for(int i=0; i<n; i++)
		fprintf(f," %f ",*(b+i));	
}	
int read_FILE() {
    FILE *fp;
    char str[MAXCHAR];
    fp = fopen("D:\\C project\\final_exam.txt", "r");
    if (fp == NULL){
        printf("Could not open file %s","D:\\C project\\final_exam.txt");
        return 1;
    }
    while (fgets(str, MAXCHAR, fp) != NULL)
        printf("%s", str);
    fclose(fp);
    return 0;
}
