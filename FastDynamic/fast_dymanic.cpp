// FastDynamic.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <ostream>
#include <iostream>
#include <cmath>
#include <time.h>
#include "transform_query_file.h"
#include "pre_process_data_graph.h"
#include "time.h"
#include "utility.h"
#include "cfl_decomposition.h"
#include "seed_finder.h"
#include "cpi_builder.h"
#include "matching_order.h"
#include "enumeration.h"
#include "sim_base_build_cpi.h"
#include "core_query_tree_build.h"
#include "inexact_matching_order.h"
#include "find_result.h"
#include "ParsePredicateMatrix.h"

using namespace std;

CUtility *cu_total = new CUtility();
CUtility *cu_readQuery = new CUtility();
CUtility *cu_prepare = new CUtility();
CUtility *cu_simulation = new CUtility();
CUtility *cu_getSequence = new CUtility();
CUtility *cu_querying = new CUtility();

#define TOTAL_BEGIN cu_total->startCT();
#define TOTAL_END g_time_total = cu_total->endCT(false);

#define READ_QUERY_BEGIN cu_readQuery->startCT();
#define READ_QUERY_END g_time_readQuery = cu_readQuery->endCT(false);

#define PREPARE_BEGIN cu_prepare->startCT();
#define PREPARE_END g_time_prepare = cu_prepare->endCT(false);

#define SIMULATION_BEGIN cu_simulation->startCT();
#define SIMULATION_END g_time_simulation = cu_simulation->endCT(false);

#define GET_SEQ_BEGIN cu_getSequence->startCT();
#define GET_SEQ_END g_time_getSequence = cu_getSequence->endCT(false);

#define SEARCH_BEGIN cu_querying->startCT();
#define SEARCH_END g_time_search = cu_querying->endCT(false);

void print_globals()
{
	cout << "g_max_label_counter:" << g_max_label_counter << endl;
	cout << "g_cnt_node_of_data_graph:" << g_cnt_node_of_data_graph << endl;
	cout << "g_cnt_unique_label_data_graph:" << g_cnt_unique_label_data_graph << endl;
	// cout << "g_cnt_unique_label_data_graph_actual:" << g_cnt_unique_label_data_graph_actual << endl;
	cout << "g_largest_label_data_graph:" << g_largest_label_data_graph << endl;
	cout << "MAX_DEGREE_A_NODE_QUERY:" << MAX_DEGREE_A_NODE_QUERY << endl;
	cout << "g_degree_of_sort_by_label_degree_data_graph:";
	print_vector(g_degree_of_sort_by_label_degree_data_graph);
	cout << "g_nodes_label_after_change_data_graph:";
	print_array(g_nodes_label_after_change_data_graph);
	cout << "g_label_freqency_data_graph:";
	print_array(g_label_freqency_data_graph);
	cout << "g_transfer_label_mapping:";
	print_array(g_transfer_label_mapping);
	cout << "g_core_number_data_graph:";
	print_array(g_core_number_data_graph);
	cout << "g_node_degree_data_graph:";
	print_array(g_node_degree_data_graph);
	cout << "g_nodes_neighbors_start_position_data_graph:";
	print_array(g_nodes_neighbors_start_position_data_graph);
	cout << "g_node_id_sort_by_label_degree_data_graph:";
	print_array(g_node_id_sort_by_label_degree_data_graph);
	cout << "size_of_g_nodes_adj_list_with_edge_type_data_graph:" << size_of_g_nodes_adj_list_with_edge_type_data_graph << endl;
	cout << "g_node_id_sort_by_label_degree_data_graph:";
	print_array(g_node_id_sort_by_label_degree_data_graph);

	// query graph variables
	cout << "LIMIT:" << LIMIT << endl;
	cout << "g_cnt_node_query_graph:" << g_cnt_node_query_graph << endl;
	cout << "g_sum_degree_query_graph:" << g_sum_degree_query_graph << endl;
	cout << "g_mapping_found:" << g_mapping_found << endl;
	cout << "g_max_sum_degree_query_graphs:" << g_max_sum_degree_query_graphs << endl;
	cout << "g_nodes_adj_list_start_index_query_graph:";
	print_array(g_nodes_adj_list_start_index_query_graph);
	cout << "g_label_cur_node_query_graph:" << g_label_cur_node_query_graph << endl;
	cout << "g_degree_cur_node_query_graph:" << g_degree_cur_node_query_graph << endl;

	cout << "g_nodes_label_query_graph:";
	print_array(g_nodes_label_query_graph);
	cout << "g_node_degree_query_graph:";
	print_array(g_node_degree_query_graph);
	cout << "g_core_number_query_graph:";
	print_array(g_core_number_query_graph);
	cout << "g_visited_for_query_graph:";
	print_array(g_visited_for_query_graph);
	cout << "NEC_mapping_child_with_same_label_cnt:";
	print_array(NEC_mapping_child_with_same_label_cnt);
	cout << "NEC_map:";
	print_array(NEC_map);
	cout << "NEC_mapping_Actual_first:";
	print_array(NEC_mapping_Actual_first);
	cout << "dfs_stack_query:";
	print_array(dfs_stack_query);
	cout << "g_residual_tree_match_seq_index:" << g_residual_tree_match_seq_index << endl;
	cout << "g_residual_tree_leaf_node_index:" << g_residual_tree_leaf_node_index << endl;
	cout << "g_residual_tree_match_seq_query:";
	print_array(g_residual_tree_match_seq_query);
	cout << "g_tree_node_parent_query_graph:";
	print_array(g_tree_node_parent_query_graph);
	cout << "NEC_set_index:" << NEC_set_index << endl;
	cout << "g_root_node_id_of_query:" << g_root_node_id_of_query << endl;
	cout << "NLF_array_query:";
	print_array(NLF_array_query);
	cout << "NLF_size:" << NLF_size << endl;
	cout << "NLF_check:";
	print_array(NLF_check);
	cout << "g_root_candidates:";
	print_array(g_root_candidates);
	cout << "g_root_candidates_size:" << g_root_candidates_size << endl;
	cout << "g_nte_array_for_matching_unit_index:" << g_nte_array_for_matching_unit_index << endl;
	cout << "g_matching_sequence_index:" << g_matching_sequence_index << endl;

	cout << "g_good_count_data_graph:";
	print_array(g_good_count_data_graph);
	cout << "g_good_count_need_clean_index_data_graph:";
	print_array(g_good_count_need_clean_index_data_graph);
	cout << "g_good_count_need_clean_size:" << g_good_count_need_clean_size << endl;
	cout << "g_check_value:" << g_check_value << endl;
	cout << "g_forward_build_sequence:";
	print_vector(g_forward_build_sequence);
	cout << "g_forward_build_parent:";
	print_array(g_forward_build_parent);
	cout << "g_forward_level:";
	print_array(g_forward_level);
	cout << "g_build_cpi_sequence:";
	print_array(g_build_cpi_sequence);
	cout << "g_build_cpi_sequence_size:" << g_build_cpi_sequence_size << endl;
	cout << "g_already_has_one_parent_data_node:";
	print_array(g_already_has_one_parent_data_node);

	cout << "count_index_array_for_indexSet:" << count_index_array_for_indexSet << endl;
	cout << "g_visited_int_for_query_graph:";
	print_array(g_visited_int_for_query_graph);
	cout << "g_core_tree_node_child_array:";
	print_vector(g_core_tree_node_child_array);
	cout << "g_core_tree_node_nte_array:";
	print_vector(g_core_tree_node_nte_array);
	cout << "g_core_tree_node_child_array_index:" << g_core_tree_node_child_array_index << endl;
	cout << "g_core_tree_node_nte_array_index:" << g_core_tree_node_nte_array_index << endl;
	cout << "g_actual_mapping:";
	print_array(g_actual_mapping);
	cout << "g_cand_pos_in_indexset:";
	print_array(g_cand_pos_in_indexset);
	cout << "g_core_size:" << g_core_size << endl;

	cout << "leaf_necs:";
	print_array(leaf_necs);
	cout << "leaf_necs_idx:" << leaf_necs_idx << endl;
	cout << "all_mapping:";
	print_array(all_mapping);

	cout << "NEC_leaf_mapping_pair_index:" << NEC_leaf_mapping_pair_index << endl;
	cout << "g_isTree:" << g_isTree << endl;
	cout << "g_data_edge_matrix:";
	print_array(g_data_edge_matrix);
	// cout << "g_level:";
	// print_vector(&g_level);
	cout << "g_level_size:" << g_level_size << endl;
	cout << "v_cnt:";
	print_array(v_cnt);

	cout << "MAX_NB_degree_data:";
	print_array(MAX_NB_degree_data);
	cout << "g_BFS_sequence_length:" << g_BFS_sequence_length << endl;
	cout << "found_mapping_enumeration:" << found_mapping_enumeration << endl;
	/*cout << "g_one_hop_label_count_data_graph:";
	print_array(g_one_hop_label_count_data_graph);
	cout << "g_two_hop_label_count_data_graph:";
	print_array(g_two_hop_label_count_data_graph);
	cout << "g_one_hop_label_count_query_graph:";
	print_array(g_one_hop_label_count_query_graph);
	cout << "g_two_hop_label_count_query_graph:";
	print_array(g_two_hop_label_count_query_graph);*/
	cout << "BFS_parent_query:";
	print_array(BFS_parent_query);
	cout << "BFS_level_query:";
	print_array(BFS_level_query);

	cout << "g_sim_visited:";
	print_array(g_sim_visited);
	cout << "g_sim_visited_stack:";
	print_array(g_sim_visited_stack);
	cout << "g_sim_visited_length:" << g_sim_visited_length << endl;
	cout << "g_max_degree_data_graph:" << g_max_degree_data_graph << endl;
	cout << "DYNAMIC:" << DYNAMIC << endl;
	cout << "query_root_sort_list:";
	print_vector(query_root_sort_list);

	cout << "g_already_visited_data_graph:";
	print_array(g_already_visited_data_graph);

	cout << "g_node_similarity_matrix:";
	print_array(g_node_similarity_matrix);
	// cout << "g_edge_matching_array:";
	// print_array(g_edge_matching_array);
	cout << "g_is_init_edge_matchinig_array:" << g_is_init_edge_matchinig_array << endl;
	// cout << "core_query_tree";
	// print_array(core_query_tree)
}

void getLimit_full(string str_full_limit, long &LIMIT)
{
	if (str_full_limit == "1K")
		LIMIT = 1000;
	else if (str_full_limit == "10K")
		LIMIT = 10000;
	else if (str_full_limit == "100K")
		LIMIT = 100000;
	else if (str_full_limit == "100M")
		LIMIT = 100000000;
	else if (str_full_limit == "1B")
		LIMIT = 100000000000;
	else
		LIMIT = atol(str_full_limit.c_str());
}

void printVectorInt(vector<int> &vet)
{
	for (vector<int>::iterator pos = vet.begin(); pos != vet.end(); pos++)
	{
		printf("%d ", *pos);
	}
	putchar('\n');
}

void myy(vector<int> &a)
{
	for (int i = 0; i < a.size(); i++)
	{
		cout << i;
	}
}

inline bool is_contain_empty_indexset()
{
	for (int step = 0; step < g_core_size; step++)
	{
		CPINode *tmp_node = &indexSet[step];
		if (tmp_node->size == 1 && tmp_node->candidates[0] == -1)
		{
			return true;
		}
	}
	return false;
}

int main(int argc, char *argv[])
{

	// use for directed graph

	/*argv[1] = "C:\\Users\\data.format";
	argv[2] = "C:\\Users\\Template3_C.gdf.format";
	argv[3] = "C:\\Users\\predicate_similarity.txt";

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	argv[4] = "-f";
	argv[5] = "1";
	argv[6] = "1";*/

	// top 10
	TOPK = 100;
	NODE_MISS_COST = 10;
	BRIDGE_COST = 10;
	EDGE_MISSING_COST = 10;
	DYNAMIC = true;
	// IS_ONE_HOP_DATA_GRAPH should be equl to 1 or 0
	// 1 means yes
	IS_ONE_HOP_DATA_GRAPH = 1;
	DISTINCT_LABEL = 0;

	string data_graph_file = argv[1];
	string query_graph_file = argv[2];
	string edge_sim_file = argv[3];

	ParsePredicateMatrix::parsePredicateFile(edge_sim_file);

	TOPK = stoi(argv[4]);
	NODE_MISS_COST = stoi(argv[5]);
	BRIDGE_COST = stoi(argv[6]);
	EDGE_MISSING_COST = stoi(argv[7]);
	IS_ONE_HOP_DATA_GRAPH = stoi(argv[8]);
	VERTEX_EXTENDER = stoi(argv[9]);

	cout << endl
		 << "*******************************************************************" << endl;
	cout << "Data File :" << argv[1] << endl;
	cout << "Query file:" << argv[2] << endl;
	cout << "Edge Similarity file:" << argv[3] << endl;
	cout << "Top-K: " << TOPK << endl;
	cout << "Missing Node Cost: " << NODE_MISS_COST << endl;
	cout << "Intermediate Cost: " << BRIDGE_COST << endl;
	cout << "Missing Edge Cost: " << EDGE_MISSING_COST << endl;
	cout << "Is One Hop: " << IS_ONE_HOP_DATA_GRAPH << endl;
	cout << "Using Vertex extender selection: " << VERTEX_EXTENDER << endl;
	cout << "*******************************************************************" << endl;

	// ======= Begin clock ========
	g_clock = clock();

	//==== FIRST step: read and process the data graph ============================
	cout << "Reading data graph ..." << endl;
	preprocessDataGraph(data_graph_file);
	cout << "processing data graph ..." << endl;
	readAndProcessDataGraph(data_graph_file);
	initNECStructure();
	cout << "OK!" << endl;

	cout << "Building index..." << endl;
	cout << "Begin parametersInitilisingBeforeQuery..." << endl;
	initParametersBeforeQuery();
	cout << "Begin initializeStatisticParameters..." << endl;
	initializeStatisticParameters();
	cout << "OK!" << endl;
	//=======FIRST step END =====================================================

	cout << "ATTENTION: Finish data index cost: " << (clock() - g_clock) * 1.0 / CLOCKS_PER_SEC << endl;

	int count_query_file = atoi(argv[5]);
	count_query_file = 1;
	// string str_full_limit = argv[5];

	// getLimit_full(str_full_limit, LIMIT);

	char c;
	int query_id;

	for (long long i = 0; i < count_query_file; i++)
	{
		// clean heap here
		{
			g_result_heap.clear();
			g_maxPartialNum = 0;
			g_mapping_found = 0;
			back_trace_counter = 0;
		}

		TOTAL_BEGIN;

		single_readQueryGraph(query_graph_file);

		PREPARE_BEGIN;

		string command = "";
		do
		{
			g_result_heap.clear();
			coreDecompositionQuery();
			cout << "Decompose Query OK!" << endl;
			g_isTree = true;
			for (long long i = 0; i < g_cnt_node_query_graph; i++)
			{
				if (g_core_number_query_graph[i] >= 2)
				{
					g_isTree = false;
					break;
				}
			}

			g_isTree = false;
			if (g_isTree)
			{
			}
			else
			{
				// extract residual tree and NEC from query
				// extractResidualStructures();
				g_root_node_id_of_query = selectRootFromQuery();
				// g_root_node_id_of_query = 3;
				findRootCandidate();
				int root_index_point = -1;
				while (g_root_candidates_size == 0)
				{
					root_index_point = root_index_point + 1;
					if (root_index_point == query_root_sort_list.size())
					{
						cout << "All node in core has no candidate!" << endl;
						return 0;
					}
					g_root_node_id_of_query = query_root_sort_list[root_index_point] % ONE_M;
					findRootCandidate();
				}

				PREPARE_END;

				for (int region = 0; region < g_root_candidates_size; region++)
				{

					long long root_cand_id = g_root_candidates[region];

					g_nte_array_for_matching_unit_index = 0;
					g_matching_sequence_index = 0;
					g_matching_order_size_of_core = 0;

					// BFS method
					if (!DYNAMIC)
					{
						buildBFSCoreQueryTree();
						buildBFSTreeCPI(root_cand_id);
						// backwardPrune();
						generateInexactMatchingOrder();
					}
					else
					{
						buildDynamicTreeCPI(root_cand_id);
						for (int ii = 0; ii < 20; ii++)
						{
							// backwardPrune();

							// if (is_contain_empty_indexset()) {
							//	break;
							// }
						}

						// buildCoreQueryTree();
						generateMatchingOrderByDynamic();
					}

					// print correct partial match
					cout << "Exact Partial Match: ";
					for (int step = 0; step < g_core_size; step++)
					{
						CPINode *tmp_node = &indexSet[step];
						/*print_array(tmp_node->path);
						cout << "|";
						print_array(tmp_node->candidates);
						cout << "|" << tmp_node->size << "|";*/
						if (tmp_node->size == 1)
						{
							cout << step << ":" << tmp_node->candidates[0] << " ";
						}
						else
						{
							cout << " ";
						}
					}
					cout << endl;

					/*if (g_core_size != g_cnt_node_query_graph) {
						continue;
					}*/

					// Dynamic method
					// forwardBuildQueue(root_cand_id);

					// buildDynamicTreeCPI(root_cand_id);
					// forwardBuild(root_cand_id);
					// buildCoreQueryTree();
					//  build core query tree

					// cout << "forward Done" << endl;

					// cout << "backward Done" << endl;
					// buildSearchIterator();
					// cout << "build search iterator Done" << endl;
					// generateMatchingOrder();
					// generateInexactMatchingOrder();
					// generateMatchingOrderByCoreQueryTree();
					// matchingOrderLayer();
					// test1();
					// cout << "generateMatchingOrder Done" << endl;
					// findAllMatching();
					find_inexact_result();
					// cout << "all_mapping:";
					//  print_array(all_mapping);
					//  cout << endl;
					int aaa = 0;
				}
			}
			output_result();
			/*for (Result re : g_result_heap)
			{
				cout << " / ";
				print_vector(re.result);
				cout << endl;
			}*/

			cout << "ATTENTION: Cost: " << (clock() - g_clock) * 1.0 / CLOCKS_PER_SEC << endl;
			cout << "# of backtraces: " << back_trace_counter << endl;

			// fin_query.close();
			// print_globals();
			// command = "done";
			string arg1 = "";
			string arg2 = "";
			cin >> command >> arg1 >> arg2;
			pcocess_query_modification(command, arg1, arg2);
		} while (command.at(0) != 'd');
	}

	return 0;
}
