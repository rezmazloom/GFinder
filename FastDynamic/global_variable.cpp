#pragma once
#include "stdafx.h"
#include "global_variable.h"

long long back_trace_counter = 0;
int VERTEX_EXTENDER = 0;

// data label max number
long long g_max_label_counter = 0;
// data graph # of nodes
int g_cnt_node_of_data_graph = 0;
// # of unique labels in data graph
int g_cnt_unique_label_data_graph = 0;
// not used??
long long g_cnt_unique_label_data_graph_actual = 0;

// data label max number??
int g_largest_label_data_graph = 0;
// as it says
long long MAX_DEGREE_A_NODE_QUERY = 0;
// 2 1 3 3 4 2 2 2 3 3 2 3
vector<int> g_degree_of_sort_by_label_degree_data_graph(0);

// node lables
int *g_nodes_label_after_change_data_graph;
// frequency of node label in data graph
int *g_label_freqency_data_graph;
// NO IDEA????? 0-data label type max
int *g_transfer_label_mapping;
// data graph node edges (no idea of the differene between core and degree??????)
int *g_core_number_data_graph;
// data graph node edges  2 3 2 3 3 2 3 3
int *g_node_degree_data_graph;
EdgeType *g_nodes_neighbors_list_of_edge_type_data_graph;
// 30
int size_of_g_nodes_adj_list_with_edge_type_data_graph;
// 0 2 5 7 10 13 15 18
int *g_nodes_neighbors_start_position_data_graph;

// node_id * g_cnt_unique_label_data_graph + label_id = <start, end>
unordered_map<int, pair<int, int>> *g_position_of_neighbors_have_label_data_graph;
// sorted data graph by 1)label number 2)degree increasing
int *g_node_id_sort_by_label_degree_data_graph;
pair<int, int> *g_label_to_sort_by_degree_node_data_graph;

// time
double g_time_search;
double g_time_process;
double g_time_simulation;
double g_time_prepare;
double g_time_preliminary;
double g_time_readQuery;
double g_time_getSequence;
double g_time_total;
double g_time_rest;
double g_time_query;

// 0
long LIMIT;

// query # of nodes
int g_cnt_node_query_graph;
// query edge count (bidirectional counted as two edges) aka sum(g_node_degree_query_graph)
long long g_sum_degree_query_graph;
// 0
double g_mapping_found;

// 18 query edge count (bidirectional counted as two edges) aka sum(g_node_degree_query_graph)
long long g_max_sum_degree_query_graphs;
vector<EdgeType> g_nodes_adj_list_with_edge_type_query_graph;
// 0 2 5 7 9 12 15 16
int g_nodes_adj_list_start_index_query_graph[MAX_QUERY_NODE];
// 0 (root?)
long long g_label_cur_node_query_graph;
// 0
long long g_degree_cur_node_query_graph;

// query graph node labels
int g_nodes_label_query_graph[MAX_QUERY_NODE];
// query graph node degrees
long long g_node_degree_query_graph[MAX_QUERY_NODE];
// 2 2 2 2 2 2 1 2
long long g_core_number_query_graph[MAX_QUERY_NODE];
// empty at the end
char g_visited_for_query_graph[MAX_QUERY_NODE];

// all zeros 0 0 0 0 0 0 0 0 (does not do what it says so far)
int *NEC_mapping_child_with_same_label_cnt;
NEC_element *NEC_mapping_pair;
NEC_set_array_element *NEC_set_array;
NEC_Node *NEC_Node_array;
// 0 0 0 0 0 0 0 0
long long NEC_map[MAX_QUERY_NODE];
// 0 0 0 0 0 0 0 0
int *NEC_mapping_Actual_first;

// 0 0 0 0 0 0 0 0
long long dfs_stack_query[MAX_QUERY_NODE]; // let algorithm run fast
// 0
long long g_residual_tree_match_seq_index = 0;
// 0
long long g_residual_tree_leaf_node_index;
// 0
long long g_residual_tree_match_seq_query[MAX_QUERY_NODE];
// 0 0 0 0 0 0 0 0
int *g_tree_node_parent_query_graph;
// storeage the leaf nodeid in query graph
pair<long long, double> g_residual_tree_leaf_node[MAX_QUERY_NODE];
// 0
long long NEC_set_index;
vector<pair<long long, long long>> NEC_set_by_label_index;

// 2????
long long g_root_node_id_of_query;
// # the tree we were looking for
// index_N_up_u is 2-D matrix for [parent candidate][self candidate]
CPINode indexSet[MAX_QUERY_NODE];
// 4 0 0 113 0 0 0 0
long long *NLF_array_query;
// 1
long long NLF_size = -1;
// 0 0 0 0 0 0 0 0
long long *NLF_check;
int SIZEOF_INT = sizeof(int) * 8;
// 10 11 4 6 0 0 65 0
int *g_root_candidates;
// 4
int g_root_candidates_size = 0;

// 1
long long g_nte_array_for_matching_unit_index = 0;
// 0
long long g_matching_sequence_index = 0;

// 2 hop pruning
int *g_good_count_data_graph;
int *g_good_count_need_clean_index_data_graph;
long long g_good_count_need_clean_size;
long long g_check_value = 0;
// BFS ordered list of query nodeIDs
vector<long long> g_forward_build_sequence;
// parent of each query node as index
long long g_forward_build_parent[MAX_QUERY_NODE];
int g_forward_level[MAX_QUERY_NODE];

// vector<set <long long>> g_adj_list_data_graph;
long long g_build_cpi_sequence[MAX_QUERY_NODE];
long long g_build_cpi_sequence_size;
int *g_already_has_one_parent_data_node;

CPICell *g_index_array_for_indexSet;
long long count_index_array_for_indexSet;

CoreQueryBFSTreeNode core_query_tree[MAX_QUERY_NODE];
long long g_visited_int_for_query_graph[MAX_QUERY_NODE];
vector<long long> g_core_tree_node_child_array;
vector<long long> g_core_tree_node_nte_array;

long long g_core_tree_node_child_array_index = 0;
long long g_core_tree_node_nte_array_index = 0;
long long g_actual_mapping[MAX_QUERY_NODE];
// 0 1 0 0 1 2 0 0
long long g_cand_pos_in_indexset[MAX_QUERY_NODE];
// 7
long long g_core_size = 0;

// for enumerating the result of leaf nodes ====
// 0 0 0 0 0 0 0 0
int *leaf_necs;
// 0
long long leaf_necs_idx = 0;
// 0 3 6 7 9 11 10 0
int *all_mapping;

// 0
long long NEC_leaf_mapping_pair_index = 0;

// false
bool g_isTree;

// NULL
char *g_data_edge_matrix;
char SIZEOK;
int SIZE_OF_EDGE_MATRIX = 10000;
HashTable **g_hash_table;

// could not print!
vector<long long> g_level[MAX_QUERY_NODE + 1];
// 4
long long g_level_size = 0;
// NULL
char *v_cnt;

// 3 3 3 3 3 3 4 4
int *MAX_NB_degree_data;

// both below as default
long long g_BFS_sequence_length = 0;
double found_mapping_enumeration = 10;
// print skipped due to errors and NULLs
int *g_one_hop_label_count_data_graph;
int *g_two_hop_label_count_data_graph;
// nodeID * (data # of nuique edge_labels) + edge_label  - 1 [for each node]
int *g_one_hop_label_count_query_graph = NULL;
int *g_two_hop_label_count_query_graph = NULL;
vector<set<long long>> g_set_of_node_adj_list_query_graph;
vector<pair<long long, long long>> level_index;

// 1 2 1 2 -1 4 5 0
long long BFS_parent_query[MAX_QUERY_NODE];
// 0 0 0 0 0 0 0 0
long long BFS_level_query[MAX_QUERY_NODE];

// vector<set <int>> g_adj_list_one_to_four_data_graph;
HashTable *g_adj_list_one_hop_distance_data_graph;
HashTable *g_adj_list_two_hop_distance_data_graph;

// NULL
char *g_sim_visited;
// 0 0 0 0 0 0 0 0
int *g_sim_visited_stack;
// 0
long long g_sim_visited_length = 0;

int TOPK = 10;
int NODE_MISS_COST = 3;
int BRIDGE_COST = 10;
int EDGE_MISSING_COST = 10;
int IS_ONE_HOP_DATA_GRAPH = 0;
int DISTINCT_LABEL = 0;
long long g_maxPartialNum = 0;

// max data graph degree max(data_degree)
int g_max_degree_data_graph = 0;

// true
bool DYNAMIC = false;

// 20000000002 10000000004 10000000003 10000000001 6666600005 5000000000 7
vector<long long> query_root_sort_list;
long long ONE_M = 100000;

clock_t g_clock;

// NULL
char *g_already_visited_data_graph;
// 1 0 1 0 1 1 1 1 (why the zeros?)
// g_node_similarity_matrix[query_id * g_cnt_node_of_data_graph + data_id] = 1 - (([degree_diff OR 0] * 1.0) / query_degree);
double *g_node_similarity_matrix;

// NULL
int *g_edge_matching_array;
// false
bool g_is_init_edge_matchinig_array = false;
//=============================================
