#include "add.h"
#include "minus.h"

int add (int a, int b){
	return a+b;
}

int callMinusToAdd (int a, int b, int c){
	int value = minus(b, c);
	return a+value;
}

int getValue (int c){
	return c;
}
