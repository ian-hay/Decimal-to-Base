#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// TODO: what are function prototypes?
void other_base(unsigned, unsigned);
void power2_base(unsigned, unsigned);
void base_256(unsigned, unsigned);

// this will not change, so we can declare it constant
const char *ascii = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz+/";

// this _will_ change, however
char buffer[32];

//use for correct buffer printing location
int length;

//buffer starting place
int buff=30;

// every C program must implement the `main()` function
int main(int argc, char *argv[]) {

	// TODO: error check

	//checks argc for enough arguments
	if(argc!=3){	
		printf("Not enough Arguments \n");
		return -1;
	}
	

	// properly NULL terminate the buffer
	buffer[31] = 0;

	// use `atoi()` function to translate characters to numbers
	unsigned decimal = atoi(argv[1]);
	unsigned base    = atoi(argv[2]);
	
	//checks to see if base is valid
	if((base<2 || base>64) && base!=256){
		printf("INVALID BASE \n");
		return -1;
	}
	

	// TODO: decide which function to call based on
	// the user's desired base

	//if statements to determine what function to use for conversion
	if(base==256){
		base_256(decimal,base);
	}else if(ceil(log2(base)) == floor(log2(base))){
		power2_base(decimal,base);	
	}else{
		other_base(decimal,base);
	}
	
	
	// here are two ways to print from certain
	// location in the buffer, use one of them
	
	//prints buffer using global int length
	printf("%s \n", &buffer[31-length]);
	
	
	// remember there should only be a SINGLE call
	// to `printf()` in your entire program

	// exit with 0 if the program was successful
	return 0;
}

void other_base(unsigned decimal, unsigned base) {

	// TODO: for bases that are not a power of 2 or 256
	// fill the buffer from the end, toward the start
	
	//two ints for holding numbers while converting
	int div = 0;
	int mod = 0;

	
	
	//converts numbers by using division and modulo and puts them in the buffer
	while(decimal != 0){
		div = decimal / base;
		mod = decimal % base;
		decimal = div;
		buffer[buff]=ascii[mod];
		buff--;
		length++;
	}

	return;
}

void power2_base(unsigned decimal, unsigned base) {
	// TODO: for bases that are a power of 2 but still not 256
	
	//initializes mask variable to base-1
	int mask= base-1;
	//initializes shift variable
	int shift = 0;
	//initializes track variable to use to find number for shift
	int track=0;
	
	//finds shift number by plugging in values to pow() starting at 0
	while(shift !=base){
		shift= pow(2,track);
		track++;
	}

	//sets shift to track-1 for shifting number which is based on the base number
	shift=track-1;
	
	//mask & shift while loop
	while(decimal != 0){
		buffer[buff]=ascii[decimal & mask];
		decimal=decimal>>shift;
		length++;
		buff--;
	}
	return;
}

void base_256(unsigned decimal, unsigned base) {

	// TODO: for base 256 only
	
	//initializes shift int to 8 because of base 256
	int shift= 8;
	//for putting values into array
	int count=3;
	//holds decimal values
	int mask=0;
	//array for putting numbers in
	int nums[4];
	
	//mask & shift
	while(decimal!=0){
		mask=decimal & (base-1);
		nums[count]=mask;
		decimal=decimal>>shift;	
		count--;
	}
	
	//fills num array with using % and then changes to ascii and fills buffer	
	for(int i=(sizeof(nums)/sizeof(int))-1;i>count;i--){
		while(nums[i]!=0){
			mask=nums[i]%10;
			buffer[buff]=ascii[mask];
			nums[i]=nums[i]/10;
			buff--;
			length++;
		}//puts '.' in correct buffer spots
		if(i!=count+1){
			buffer[buff]='.';
			buff--;
			length++;
		}
	}


	return;
}

