#pragma once
#include "DiGraphProcessor.hpp"
#include "GraphProcessor.hpp"
#include <chrono>
#include <iostream>
#include <string>

using namespace std;

namespace sem3 {
    class menu {
    private:
        GraphProcessor graph;
        DiGraphProcessor digraph;
        bool check_time;
        bool graph_or_digraph;
        bool my_or_random;
        int size;

        void print_separator();
        void print_graphs();
        void print_my_or_random();
        void print_check_time();
        void print_condition();
        void print_actions_graph();
        void print_actions_digraph();

        void switch_graph();
        void switch_my_or_random();
        void switch_size();
        void switch_check_time();
        int switch_actions_graph();
        int switch_actions_digraph();

        int get_from_console(int min, int max);
        void read_graph();
        void read_digraph();

        void setRandomGraph();

        void change_settings();
        void print_settings();
        void switch_settings();

        //graphs
        void print_graph();
        void achievable_from_graph();
        void is_connected_graph();
        void is_acyclic_graph();
        void output_cycles_graph();
        void is_tree_graph();
        void color_graph();
        void output_spanning_trees_graph();
        void distance_graph();
        void distance_all_graph();

        //digraphs
        void print_digraph();
        void achievable_from_digraph();
        void is_strongly_connected_digraph();
        void components_digraph();
        void is_acyclic_digraph();
        void output_cycles_digraph();
        void is_tree_digraph();
        void topological_sort_digraph();
        void count_paths_digraph();
        void output_spanning_trees_digraph();
        void distance_digraph();
        void distance_all_digraph();
        void all_cycles_output_digraph();

    public:
        menu();
        void run();
    };

} // namespace sem3