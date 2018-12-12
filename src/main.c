/*      ____  ____  ____
 *     / __ \/ __ \/ __ \
 *    / /  \/ /  \/ /  \ \
 *    \ \  / /\  / /\  / /
 *     \ \/ /\ \/ /\ \/ /
 *      \ \/  \ \/  \ \/
 *      /\ \  /\ \  /\ \
 *     / /\ \/ /\ \/ /\ \
 *    / /  \/ /  \/ /  \ \
 *   / /   / /\  / /\   \ \
 *   | |  / / /  \ \ \  | |
 *   \ \__\/ /    \/ /__/ /
 *    \_____/\____/ /____/
 *          \______/
 *
 * Trabalho 2 de Alg1 - 2018.2 - ICMC USP
 * Benchmarking de estruturas de dados
 *
 * 10734540 - Bráulio Bezerra da Silva
 *  4482145 - André Luís Mendes Fakhoury
 */

#include <stdio.h>

#include "vector.h"
#include "sorted_list.h"
#include "sorted_list_sentinel.h"
#include "freq_list.h"
#include "bst.h"
#include "avl.h"

#include "benchmarks.h"

int main() {

	// Data structures

	Method methods[] = {
		{"BB"   , (NewFn)vector_create          , (InsFn)vector_insert          , (SchFn)vector_search          , (RemFn)vector_remove          , NULL},
		{"LO"   , (NewFn)sorted_list_create     , (InsFn)sorted_list_insert     , (SchFn)sorted_list_search     , (RemFn)sorted_list_remove     , (FreeFn) sorted_list_free},
		{"LOS"  , (NewFn)sorted_list_sent_create, (InsFn)sorted_list_sent_insert, (SchFn)sorted_list_sent_search, (RemFn)sorted_list_sent_remove, (FreeFn) sorted_list_sent_free},
		{"ABB"  , (NewFn)bst_create             , (InsFn)bst_insert             , (SchFn)bst_search             , (RemFn)bst_remove             , (FreeFn) bst_free},
		{"AVL"  , (NewFn)avl_create             , (InsFn)avl_insert             , (SchFn)avl_search             , (RemFn)avl_remove             , (FreeFn) avl_free},
		{"LFREQ", (NewFn)freq_list_create       , (InsFn)freq_list_insert       , (SchFn)freq_list_search       , (RemFn)freq_list_remove       , (FreeFn) freq_list_free}
	};

	// Benchmarks

	Benchmark benchs[] = {
		{"Tabela 1: Tempo de insercao crescente", ascending_insertions},
		{"Tabela 2: Tempo de insercao decrescente", descending_insertions},
		{"Tabela 3: Tempo de insercao aleatoria", random_insertions},
		{"Tabela 4: Tempo de remocao crescente (apos insercao crescente)", ascending_removes_after_asc_ins},
		{"Tabela 5: Tempo de remocao decrescente (apos insercao crescente)", descending_removes_after_asc_ins},
		{"Tabela 6: Tempo de remocao aleatoria (apos insercao aleatoria)", random_removes_after_rand_ins},
		{"Tabela 7: Tempo de busca (apos insercao crescente)", searches_after_asc_ins},
		{"Tabela 8: Tempo de busca (apos insercao decrescente)", searches_after_desc_ins},
		{"Tabela 9: Tempo de busca (apos insercao aleatoria)", searches_after_rand_ins},
	};

	// Dataset sizes

	const int REPETITIONS_PER_BENCHMARK = 10;
	int ns[] = {100, 1000, 10000, 100000};

	// for each benchmark 'bench'
	for (size_t b = 0; b < (sizeof(benchs) / sizeof(Benchmark)); b++) {

		Benchmark * benchmark = &benchs[b];
		puts(benchmark->name);
		puts("\tn=100\tn=1.000\tn=10.000\tn=100.000");

		char filename[256];
		sprintf(filename, "%s.gnuplot", benchmark->name);
		FILE * gnuplot_data = fopen(filename, "w");

		fprintf(gnuplot_data, "set title \"%s\"\n\n", benchmark->name);

		// for each method 'meth'
		for (size_t m = 0; m < (sizeof(methods) / sizeof(Method)); m++) {

			Method * method = &methods[m];
			printf("%s ", method->name);
			fflush(stdout);

			fprintf(gnuplot_data, "$%s << EOD\n", method->name);

			// for each dataset size 'n'
			for (size_t i = 0; i < (sizeof(ns) / sizeof(int)); i++) {

				int n = ns[i];
				double total_time = 0.0;

				// runs more than one time to avoid flukes
				for (int t = 0; t < REPETITIONS_PER_BENCHMARK; t++) {

					// Allocates the current method's container

					Vector stack_container;
					void * container;
					if (method->free == NULL) { // no destructor => stack
						// initialize directly on stack
						((void (*)(void *))method->create)(&stack_container);
						container = &stack_container;
					} else { // heap
						container = method->create();
					}

					// Run the benchmark

					total_time += benchmark->run(method, container, n);

					// Frees the memory of the current method's container

					if (method->free != NULL) {
						method->free(container);
					}
				}

				double time = total_time / REPETITIONS_PER_BENCHMARK;

				printf("\t%.6lf", time);
				fflush(stdout);

				// Add datapoint to gnuplot

				fprintf(gnuplot_data, "%d %.9lf\n", n, time);
				fflush(gnuplot_data);
			}

			putchar('\n');

			fprintf(gnuplot_data, "EOD\n\n");
			fflush(gnuplot_data);
		}
		puts("-");

		// Gnuplot magic

		fprintf(gnuplot_data, "set xlabel \"n\"\n");
		fprintf(gnuplot_data, "set ylabel \"segundos\"\n");
		fprintf(gnuplot_data, "set key outside\n");
		fprintf(gnuplot_data, "set terminal pngcairo size 768,512\n");

		fprintf(gnuplot_data, "\nset logscale xy\n");
		fprintf(gnuplot_data, "set output '%s.log.png'\n", benchmark->name);
		fprintf(gnuplot_data, "plot");
		for (size_t m = 0; m < (sizeof(methods) / sizeof(Method)); m++) {
			fprintf(gnuplot_data, "%c$%s title '%s' with lines lt %lu lw 2.3 ",
					m > 0 ? ',' : ' ', methods[m].name, methods[m].name, m + 1);
		}
		fprintf(gnuplot_data, "\n");

		fclose(gnuplot_data);

		// Run gnuplot to save graphic to image

		char command[1024];
		sprintf(command, "gnuplot '%s'", filename);
		system(command);
	}

	return 0;
}
