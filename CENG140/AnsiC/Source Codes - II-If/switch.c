#include<stdio.h>
int main( void )
{
	int grade;
	printf("Enter your grade ");
	scanf("%d",&grade);
	
	switch( grade / 10 ) {
		case 10: 
		case 9: printf("grade: A\n"); break;
		case 8: printf("grade: B\n"); break;
		case 7: printf("grade: C\n"); break;
		case 6: printf("grade: D\n"); break;
		case 5:
		case 4:
		case 3:
		case 2: 
		case 1:
		case 0: printf("grade: F\n"); break;
		default:
			printf("AN ERROR OCCURED!\n");
	}
	
	system("pause");
	return 0;
}
