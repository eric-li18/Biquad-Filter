#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[]){
	double input_arr[3] = {0,0,0}; 
	double output_arr[2] = {0,0};
	double coeff[5];
	for (int i=1;i<6;i++){
		coeff[i-1] = atof(argv[i]);
	}
	double output;

	while(scanf("%lf",(input_arr+2))!=EOF){
		
		output = (coeff[0]*(input_arr[2] + coeff[1]*input_arr[1] + coeff[2]*input_arr[0]))-coeff[3]*output_arr[1]-coeff[4]*output_arr[0];
		input_arr[0] = input_arr[1];
		input_arr[1] = input_arr[2];
		output_arr[0] = output_arr[1];
		output_arr[1] = output;
		printf("%g\n",output);
	}
	return 0;
}
