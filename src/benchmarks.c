#include "benchmarks.h"

#include <stdlib.h>
#include <time.h>

static void shuffle(int * vec, int len) {
	for (int i = 0; i < len; i++) {
		int p = rand() % len;
		int tmp = vec[i];
		vec[i] = vec[p];
		vec[p] = tmp;
	}
}

double ascending_insertions(Method *method, void *container, int n) {
	clock_t init = clock();
	for (int i = 0; i < n; i++) {
		method->insert(container, i);
	}
	clock_t end = clock();

	// use the values, to avoid the compiler optimizing out the insertions
	method->search(container, n / 2);
	
	return (end - init) / (double) CLOCKS_PER_SEC;
}

double descending_insertions(Method *method, void *container, int n) {
	clock_t init = clock();
	for (int i = n; i >= 1; i--) {
		method->insert(container, i);
	}
	clock_t end = clock();

	// use the values, to avoid the compiler optimizing out the previous operations
	method->search(container, n / 2);
	
	return (end - init) / (double) CLOCKS_PER_SEC;
}

double random_insertions(Method *method, void *container, int n) {
	srand((unsigned int) clock());

	int * nums = malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++) {
		nums[i] = rand() % n;
	}
	shuffle(nums, n);

	clock_t init = clock();
	for (int i = 0; i < n; i++) {
		method->insert(container, nums[i]);
	}
	clock_t end = clock();

	// use the values, to avoid the compiler optimizing out the previous operations
	method->search(container, n / 2);

	return (end - init) / (double) CLOCKS_PER_SEC;
}

double ascending_removes_after_asc_ins(Method *method, void *container, int n) {
	for (int i = 0; i < n; i++) {
		method->insert(container, i);
	}

	clock_t init = clock();
	for (int i = 0; i < n; i++) {
		method->remove(container, i);
	}
	clock_t end = clock();

	// use the values, to avoid the compiler optimizing out the previous operations
	method->search(container, n / 2);
	
	return (end - init) / (double) CLOCKS_PER_SEC;
}

double descending_removes_after_asc_ins(Method *method, void *container, int n) {
	for (int i = 0; i < n; i++) {
		method->insert(container, i);
	}

	clock_t init = clock();
	for (int i = n; i >= 1; i--) {
		method->remove(container, i);
	}
	clock_t end = clock();

	// use the values, to avoid the compiler optimizing out the previous operations
	method->search(container, n / 2);
	
	return (end - init) / (double) CLOCKS_PER_SEC;
}

double random_removes_after_rand_ins(Method *method, void *container, int n) {
	srand((unsigned int) clock());

	int * nums = malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++) {
		nums[i] = n;
	}
	
	shuffle(nums, n);
	for (int i = 0; i < n; i++) {
		method->insert(container, nums[i]);
	}
	
	shuffle(nums, n);

	clock_t init = clock();
	for (int i = 0; i < n; i++) {
		method->remove(container, nums[i]);
	}
	clock_t end = clock();

	// use the values, to avoid the compiler optimizing out the previous operations
	method->search(container, n / 2);

	free(nums);

	return (end - init) / (double) CLOCKS_PER_SEC;
}

double searches_after_asc_ins(Method *method, void *container, int n) {
	for (int i = 0; i < n; i++) {
		method->insert(container, i);
	}

	clock_t init = clock();
	for (int i = 0; i < n; i++) {
		method->search(container, i);
	}
	clock_t end = clock();

	// use the values, to avoid the compiler optimizing out the previous operations
	method->search(container, n / 2);
	
	return (end - init) / (double) CLOCKS_PER_SEC;
}

double searches_after_desc_ins(Method *method, void *container, int n) {
	for (int i = n; i >= 1; i--) {
		method->insert(container, i);
	}

	clock_t init = clock();
	for (int i = 0; i < n; i++) {
		method->search(container, i);
	}
	clock_t end = clock();

	// use the values, to avoid the compiler optimizing out the previous operations
	method->search(container, n / 2);
	
	return (end - init) / (double) CLOCKS_PER_SEC;
}

double searches_after_rand_ins(Method *method, void *container, int n) {
	srand((unsigned int) clock());

	int * nums = malloc(sizeof(int) * (n+1));
	for (int i = 0; i < n; i++) {
		nums[i] = n;
	}
	
	shuffle(nums, n);
	for (int i = 0; i < n; i++) {
		method->insert(container, nums[i]);
	}

	clock_t init = clock();
	for (int i = 0; i < n; i++) {
		method->search(container, nums[i]);
	}
	clock_t end = clock();

	// use the values, to avoid the compiler optimizing out the previous operations
	method->search(container, n / 2);

	free(nums);
	
	return (end - init) / (double) CLOCKS_PER_SEC;
}
