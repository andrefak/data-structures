#ifndef BENCHMARKS_H
#define BENCHMARKS_H

#include <stdbool.h>

// Standardized, container-independent, function types

/** Generic new() interface. */
typedef void * (*NewFn)();
/** Generic insert() interface. */
typedef void (*InsFn)(void *, int);
/** Generic search() interface. */
typedef bool (*SchFn)(void *, int);
/** Generic remove() interface. */
typedef int (*RemFn)(void *, int);
/** Generic free() interface. */
typedef void (*FreeFn)(void *);

/** Stores all info about a data structure/algorithm */
typedef struct {
	char name[64];
	NewFn create;
	InsFn insert;
	SchFn search;
	RemFn remove;
	FreeFn free;
} Method;

/** Generic benchmark interface. */
typedef double (*BenchFn)(Method *, void * container, int n);

/** Stores a benchmark function and its name. */
typedef struct {
	char name[128];
	BenchFn run;
} Benchmark;

double ascending_insertions(Method *method, void *container, int n);
double descending_insertions(Method *method, void *container, int n);
double random_insertions(Method *method, void *container, int n);
double ascending_removes_after_asc_ins(Method *method, void *container, int n);
double descending_removes_after_asc_ins(Method *method, void *container, int n);
double random_removes_after_rand_ins(Method *method, void *container, int n);
double searches_after_asc_ins(Method *method, void *container, int n);
double searches_after_desc_ins(Method *method, void *container, int n);
double searches_after_rand_ins(Method *method, void *container, int n);

#endif
