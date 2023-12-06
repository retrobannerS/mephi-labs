#include "menu.hpp"

namespace sem3 {
    void menu::print_check_time() {
        cout << "Check time Menu:" << endl;
        cout << "1. Yes" << endl;
        cout << "2. No" << endl;

        cout << "Enter the corresponding number to choose a mode: ";
    }

    void menu::switch_graph() {
        int choice = get_from_console(1, 2);

        switch (choice) {
        case 1: {
            graph_or_digraph = false;
            break;
        }
        case 2: {
            graph_or_digraph = true;
            break;
        }
        default:
            cout << "Invalid number." << endl;
        }
    }

    void menu::switch_my_or_random() {
        int choice = get_from_console(1, 2);

        switch (choice) {
        case 1: {
            my_or_random = false;
            break;
        }
        case 2: {
            my_or_random = true;
            break;
        }
        default:
            cout << "Invalid number." << endl;
        }
    }

    void menu::switch_size() {
        string str = graph_or_digraph ? "digraph" : "graph";
        cout << "Enter the size of the random " << str << ": ";
        size = get_from_console(0, 10000);
    }

    void menu::switch_check_time() {
        int choice = get_from_console(1, 2);

        switch (choice) {
        case 1: {
            check_time = true;
            break;
        }
        case 2: {
            check_time = false;
            break;
        }
        default:
            cout << "Invalid number." << endl;
        }
    }

    int menu::switch_actions_graph() {
        int choice = get_from_console(1, 11);

        print_separator();

        switch (choice) {
        case 1: {
            achievable_from_graph();
            break;
        }
        case 2: {
            is_connected_graph();
            break;
        }
        case 3: {
            is_acyclic_graph();
            break;
        }
        case 4: {
            output_cycles_graph();
            break;
        }
        case 5: {
            is_tree_graph();
            break;
        }
        case 6: {
            color_graph();
            break;
        }
        case 7: {
            output_spanning_trees_graph();
            break;
        }
        case 8: {
            distance_graph();
            break;
        }
        case 9: {
            distance_all_graph();
            break;
        }
        case 10: {
            change_settings();
            break;
        }
        case 11: {
            return 0;
        }
        default:
            cout << "Invalid number." << endl;
        }
        return 1;
    }

    int menu::switch_actions_digraph() {
        int choice = get_from_console(1, 13);

        print_separator();

        switch (choice) {
        case 1: {
            achievable_from_digraph();
            break;
        }
        case 2: {
            is_strongly_connected_digraph();
            break;
        }
        case 3: {
            components_digraph();
            break;
        }
        case 4: {
            is_acyclic_digraph();
            break;
        }
        case 5: {
            is_tree_digraph();
        }
        case 6: {
            all_cycles_output_digraph();
            break;
        }
        case 7: {
            topological_sort_digraph();
            break;
        }
        case 8: {
            count_paths_digraph();
            break;
        }
        case 9: {
            output_spanning_trees_digraph();
            break;
        }
        case 10: {
            distance_all_digraph();
            break;
        }
        case 11: {
            distance_digraph();
            break;
        }
        case 12: {
            change_settings();
            break;
        }
        case 13: {
            return 0;
        }
        }
        return 1;
    }

    void menu::print_condition() {
        string what_graph = graph_or_digraph ? "digraph" : "graph";
        string what_mode = my_or_random ? "random" : "my";
        int size = graph_or_digraph ? digraph.getGraph()->getVertexCount() : graph.getGraph()->getVertexCount();
        cout << "Graph: " << what_mode << " " << what_graph << endl;
        cout << "Size: " << size << endl;
        cout << "Check time: " << (check_time ? "Yes" : "No") << endl;
    }

    void menu::print_actions_digraph() {
        cout << "Actions Menu:" << endl;
        cout << "1. Achievement from" << endl;
        cout << "2. Is strongly connected?" << endl;
        cout << "3. Output components of strongly connecting" << endl;
        cout << "4. Is acyclic?" << endl;
        cout << "5. Is tree?" << endl;
        cout << "6. Output all cycles" << endl;
        cout << "7. Output topological sort" << endl;
        cout << "8. Count paths in DAG" << endl;
        cout << "9. Output all spanning trees" << endl;
        cout << "10. Distance from to all" << endl;
        cout << "11. Distance from two vertices" << endl;
        cout << "12. Change settings" << endl;
        cout << "13. Exit" << endl;

        cout << "Enter the corresponding number to choose an action: ";
    }

    void menu::print_actions_graph() {
        cout << "Actions Menu:" << endl;
        cout << "1. Achievement from" << endl;
        cout << "2. Is connected?" << endl;
        cout << "3. Is acyclic?" << endl;
        cout << "4. Output all cycles" << endl;
        cout << "5. Is tree?" << endl;
        cout << "6. Colorize" << endl;
        cout << "7. Output all spanning trees" << endl;
        cout << "8. Distance from to all" << endl;
        cout << "9. Distance from two vertices" << endl;
        cout << "10. Change settings" << endl;
        cout << "11. Exit" << endl;

        cout << "Enter the corresponding number to choose an action: ";
    }

    void menu::print_separator() { cout << endl << "----------------------------------------" << endl << endl; }

    void menu::print_graphs() {
        cout << "Graphs Menu:" << endl;
        cout << "1. Graph" << endl;
        cout << "2. DiGraph" << endl;

        cout << "Enter the corresponding number to choose a graph: ";
    }

    void menu::print_my_or_random() {
        cout << "My or Random Menu:" << endl;
        cout << "1. My" << endl;
        cout << "2. Random" << endl;

        cout << "Enter the corresponding number to choose a mode: ";
    }

    int menu::get_from_console(int min, int max) {
        int num;
        while (!(std::cin >> num && num >= min && num <= max)) {
            std::cin.clear();                                                   // clear bad input flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard input
            std::cout << "Invalid input; please re-enter: ";
        }
        return num;
    }

    void menu::read_graph() {
        cout << "Enter the number of vertices: ";
        int vertex_count = get_from_console(0, 15);
        cout << "Enter the number of edges: ";
        int edge_count = get_from_console(0, vertex_count * (vertex_count - 1) / 2);
        ArraySequence<ArraySequence<int>> matrix(vertex_count);
        for (int i = 0; i < vertex_count; i++) {
            matrix[i] = ArraySequence<int>(vertex_count);
        }
        for (int i = 0; i < edge_count; i++) {
            cout << "Enter the first vertex: ";
            int vertex1 = get_from_console(0, vertex_count - 1);
            cout << "Enter the second vertex: ";
            int vertex2 = get_from_console(0, vertex_count - 1);
            matrix[vertex1][vertex2] = 1;
            matrix[vertex2][vertex1] = 1;
        }
        graph.SetGraph(make_shared<Graph>(matrix));
    }

    void menu::read_digraph() {
        cout << "Enter the number of vertices: ";
        int vertex_count = get_from_console(0, 15);
        cout << "Enter the number of edges: ";
        int edge_count = get_from_console(0, vertex_count * (vertex_count - 1));
        ArraySequence<ArraySequence<int>> matrix(vertex_count);
        for (int i = 0; i < vertex_count; i++) {
            matrix[i] = ArraySequence<int>(vertex_count);
        }
        for (int i = 0; i < edge_count; i++) {
            cout << "Enter the first vertex: ";
            int vertex1 = get_from_console(0, vertex_count - 1);
            cout << "Enter the second vertex: ";
            int vertex2 = get_from_console(0, vertex_count - 1);
            matrix[vertex1][vertex2] = 1;
        }
        digraph.SetGraph(make_shared<DiGraph>(matrix));
    }

    void menu::setRandomGraph() {
        srand(time(NULL));
        if (graph_or_digraph) {
            ArraySequence<ArraySequence<int>> matrix(size);
            for (int i = 0; i < size; i++) {
                matrix[i] = ArraySequence<int>(size);
            }
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    if (i == j)
                        continue;
                    int num = rand() % 2;
                    matrix[i][j] = num;
                }
            }
            digraph.SetGraph(make_shared<DiGraph>(matrix));
        } else {
            ArraySequence<ArraySequence<int>> matrix(size);
            for (int i = 0; i < size; i++) {
                matrix[i] = ArraySequence<int>(size);
            }
            for (int i = 0; i < size; i++) {
                for (int j = i + 1; j < size; j++) {
                    int num = rand() % 2;
                    matrix[i][j] = num;
                    matrix[j][i] = num;
                }
            }
            graph.SetGraph(make_shared<Graph>(matrix));
        }
    }

    void menu::change_settings() {
        print_settings();
        switch_settings();
    }

    void menu::print_settings() {
        bool flag = graph_or_digraph ? digraph.getGraph()->isEmpty() : graph.getGraph()->isEmpty();

        cout << "Settings Menu:" << endl;
        if (my_or_random)
            cout << "0. SetNewRandomGraph" << endl;
        cout << "1. Change graph type" << endl;
        cout << "2. Change mode" << endl;
        if (my_or_random) {
            cout << "3. Change size" << endl;
        } else {
            cout << "3. Read new graph" << endl;
        }
        cout << "4. Change check time" << endl;
        if (!flag)
            cout << "5. Switch to other graph" << endl;
        cout << "Enter the corresponding number to choose a setting: ";
    }

    void menu::switch_settings() {
        int choice;

        bool flag = graph_or_digraph ? !digraph.getGraph()->isEmpty() : !graph.getGraph()->isEmpty();
        bool flag2 = my_or_random;
        choice = get_from_console(1 - flag2, 4 + flag);

        print_separator();
        switch (choice) {
        case 0: {
            setRandomGraph();
            break;
        }
        case 1: {
            print_graphs();
            switch_graph();
            break;
        }
        case 2: {
            print_my_or_random();
            switch_my_or_random();
            break;
        }
        case 3: {
            if (my_or_random) {
                switch_size();
            } else {
                if (graph_or_digraph) {
                    // read_graph();
                } else {
                    // read_digraph();
                }
            }
            break;
        }
        case 4: {
            print_check_time();
            switch_check_time();
            break;
        }
        case 5: {
            if (flag) {
                graph_or_digraph = !graph_or_digraph;
                break;
            }
        }
        default:
            cout << "Invalid number." << endl;
        }
        print_separator();
    }

    void menu::print_graph() {
        cout << "Graph:" << endl;
        cout << *graph.getGraph() << endl;
    }

    void menu::achievable_from_graph() {
        chrono::high_resolution_clock::time_point start, end;
        print_graph();
        cout << "Enter the vertex: ";
        int vertex = get_from_console(0, graph.getGraph()->getVertexCount() - 1);
        cout << "Achievable from " << vertex << ": ";
        if (check_time)
            start = chrono::high_resolution_clock::now();
        ArraySequence<int> arr = graph.achievableFrom(vertex);
        if (check_time)
            end = chrono::high_resolution_clock::now();
        for (int i = 0; i < arr.GetSize(); i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
        if (check_time)
            cout << "Time: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " μs";
        cout << endl;
    }

    void menu::is_connected_graph() {
        chrono::high_resolution_clock::time_point start, end;
        print_graph();
        if (check_time)
            start = chrono::high_resolution_clock::now();
        bool flag = graph.isConnected();
        if (check_time)
            end = chrono::high_resolution_clock::now();
        cout << "Is connected: " << (flag ? "Yes" : "No") << endl;
        if (check_time)
            cout << "Time: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " μs";
        cout << endl;
    }

    void menu::is_acyclic_graph() {
        chrono::high_resolution_clock::time_point start, end;
        print_graph();
        if (check_time)
            start = chrono::high_resolution_clock::now();
        bool flag = graph.isAcyclic();
        if (check_time)
            end = chrono::high_resolution_clock::now();
        cout << "Is acyclic: " << (flag ? "Yes" : "No") << endl;
        if (check_time)
            cout << "Time: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " μs";
        cout << endl;
    }

    void menu::output_cycles_graph() {
        if (graph.getGraph()->isEmpty()) {
            cout << "Graph is empty" << endl;
            return;
        }
        chrono::high_resolution_clock::time_point start, end;
        print_graph();
        if (check_time)
            start = chrono::high_resolution_clock::now();
        ArraySequence<ArraySequence<int>> arr = graph.getCycles();
        if (check_time)
            end = chrono::high_resolution_clock::now();
        cout << "Cycles: " << endl;
        for (int i = 0; i < arr.GetSize(); i++) {
            for (int j = 0; j < arr[i].GetSize(); j++) {
                cout << arr[i][j] << " ";
            }
            cout << endl;
        }
        if (check_time)
            cout << "Time: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " μs";
        cout << endl;
    }

    void menu::is_tree_graph() {
        chrono::high_resolution_clock::time_point start, end;
        print_graph();
        if (check_time)
            start = chrono::high_resolution_clock::now();
        bool flag = graph.isTree();
        if (check_time)
            end = chrono::high_resolution_clock::now();
        cout << "Is tree: " << (flag ? "Yes" : "No") << endl;
        if (check_time)
            cout << "Time: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " μs";
        cout << endl;
    }

    void menu::color_graph() {
        if (graph.getGraph()->isEmpty()) {
            cout << "Graph is empty" << endl;
            return;
        }
        chrono::high_resolution_clock::time_point start, end;
        print_graph();
        if (check_time)
            start = chrono::high_resolution_clock::now();
        ArraySequence<string> arr = graph.colorGraph();
        if (check_time)
            end = chrono::high_resolution_clock::now();
        cout << "Colors: " << endl;
        for (int i = 0; i < arr.GetSize(); i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
        if (check_time)
            cout << "Time: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " μs";
        cout << endl;
    }

    void menu::output_spanning_trees_graph() {
        if (graph.getGraph()->isEmpty()) {
            cout << "Graph is empty" << endl;
            return;
        }
        chrono::high_resolution_clock::time_point start, end;
        print_graph();
        if (check_time)
            start = chrono::high_resolution_clock::now();
        ArraySequence<ArraySequence<pair<int, int>>> arr = graph.getSpanningTrees();
        if (check_time)
            end = chrono::high_resolution_clock::now();
        cout << "Spanning trees: " << endl;
        for (int i = 0; i < arr.GetSize(); i++) {
            for (int j = 0; j < arr[i].GetSize(); j++) {
                cout << "(" << arr[i][j].first << ", " << arr[i][j].second << ") ";
            }
            cout << endl;
        }
        if (check_time)
            cout << "Time: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " μs";
        cout << endl;
    }

    void menu::distance_graph() {
        if (graph.getGraph()->isEmpty()) {
            cout << "Graph is empty" << endl;
            return;
        }
        chrono::high_resolution_clock::time_point start, end;
        print_graph();
        cout << "Enter the first vertex: ";
        int vertex1 = get_from_console(0, graph.getGraph()->getVertexCount() - 1);
        cout << "Enter the second vertex: ";
        int vertex2 = get_from_console(0, graph.getGraph()->getVertexCount() - 1);
        if (check_time)
            start = chrono::high_resolution_clock::now();
        int dist = graph.distance(vertex1, vertex2);
        if (check_time)
            end = chrono::high_resolution_clock::now();
        cout << "Distance: " << dist << endl;
        if (check_time)
            cout << "Time: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " μs";
        cout << endl;
    }

    void menu::distance_all_graph() {
        if (graph.getGraph()->isEmpty()) {
            cout << "Graph is empty" << endl;
            return;
        }
        chrono::high_resolution_clock::time_point start, end;
        print_graph();
        cout << "Enter the vertex: ";
        int vertex = get_from_console(0, graph.getGraph()->getVertexCount() - 1);
        if (check_time)
            start = chrono::high_resolution_clock::now();
        ArraySequence<int> arr = graph.BFS(vertex);
        if (check_time)
            end = chrono::high_resolution_clock::now();
        cout << "Distances: " << endl;
        for (int i = 0; i < arr.GetSize(); i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
        if (check_time)
            cout << "Time: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " μs";
        cout << endl;
    }

    void menu::print_digraph() {
        cout << "DiGraph:" << endl;
        cout << *digraph.getGraph() << endl;
    }

    void menu::achievable_from_digraph() {
        chrono::high_resolution_clock::time_point start, end;
        print_digraph();
        cout << "Enter the vertex: ";
        int vertex = get_from_console(0, digraph.getGraph()->getVertexCount() - 1);
        cout << "Achievable from " << vertex << ": ";
        if (check_time)
            start = chrono::high_resolution_clock::now();
        ArraySequence<int> arr = digraph.achievableFrom(vertex);
        if (check_time)
            end = chrono::high_resolution_clock::now();
        for (int i = 0; i < arr.GetSize(); i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
        if (check_time)
            cout << "Time: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " μs";
        cout << endl;
    }

    void menu::is_strongly_connected_digraph() {
        chrono::high_resolution_clock::time_point start, end;
        print_digraph();
        if (check_time)
            start = chrono::high_resolution_clock::now();
        bool flag = digraph.isStronglyConnected();
        if (check_time)
            end = chrono::high_resolution_clock::now();
        cout << "Is strongly connected: " << (flag ? "Yes" : "No") << endl;
        if (check_time)
            cout << "Time: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " μs";
    }

    void menu::components_digraph() {
        if (digraph.getGraph()->isEmpty()) {
            cout << "Graph is empty" << endl;
            return;
        }
        chrono::high_resolution_clock::time_point start, end;
        print_digraph();
        if (check_time)
            start = chrono::high_resolution_clock::now();
        ArraySequence<ArraySequence<int>> arr = digraph.getStronglyConnectedComponents();
        if (check_time)
            end = chrono::high_resolution_clock::now();
        cout << "Components: " << endl;
        for (int i = 0; i < arr.GetSize(); i++) {
            for (int j = 0; j < arr[i].GetSize(); j++) {
                cout << arr[i][j] << " ";
            }
            cout << endl;
        }
        if (check_time)
            cout << "Time: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " μs";
    }

    void menu::is_acyclic_digraph() {
        chrono::high_resolution_clock::time_point start, end;
        print_digraph();
        if (check_time)
            start = chrono::high_resolution_clock::now();
        bool flag = digraph.isAcyclic();
        if (check_time)
            end = chrono::high_resolution_clock::now();
        cout << "Is acyclic: " << (flag ? "Yes" : "No") << endl;
        if (check_time)
            cout << "Time: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " μs";
    }

    void menu::is_tree_digraph() {
        chrono::high_resolution_clock::time_point start, end;
        print_digraph();
        if (check_time)
            start = chrono::high_resolution_clock::now();
        bool flag = digraph.isTree();
        if (check_time)
            end = chrono::high_resolution_clock::now();
        cout << "Is tree: " << (flag ? "Yes" : "No") << endl;
        if (check_time)
            cout << "Time: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " μs";
    }

    void menu::output_cycles_digraph() {
        if (digraph.getGraph()->isEmpty()) {
            cout << "Graph is empty" << endl;
            return;
        }
        chrono::high_resolution_clock::time_point start, end;
        print_digraph();
        if (check_time)
            start = chrono::high_resolution_clock::now();
        ArraySequence<ArraySequence<int>> arr = digraph.getCycles();
        if (check_time)
            end = chrono::high_resolution_clock::now();
        cout << "Cycles: " << endl;
        for (int i = 0; i < arr.GetSize(); i++) {
            for (int j = 0; j < arr[i].GetSize(); j++) {
                cout << arr[i][j] << " ";
            }
            cout << endl;
        }
        if (check_time)
            cout << "Time: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " μs";
    }

    void menu::topological_sort_digraph() {
        if (digraph.getGraph()->isEmpty()) {
            cout << "Graph is empty" << endl;
            return;
        }
        chrono::high_resolution_clock::time_point start, end;
        print_digraph();
        if (check_time)
            start = chrono::high_resolution_clock::now();
        ArraySequence<int> arr;
        try {
            arr = digraph.topSort();
        } catch (logic_error) {
            cout << "Graph is not acyclic" << endl;
            return;
        }
        if (check_time)
            end = chrono::high_resolution_clock::now();
        cout << "Topological sort: " << endl;
        for (int i = 0; i < arr.GetSize(); i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
        if (check_time)
            cout << "Time: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " μs";
    }

    void menu::count_paths_digraph() {
        if (digraph.getGraph()->isEmpty()) {
            cout << "Graph is empty" << endl;
            return;
        }
        chrono::high_resolution_clock::time_point start, end;
        print_digraph();
        cout << "Enter the vertex: ";
        int vertex = get_from_console(0, digraph.getGraph()->getVertexCount() - 1);
        if (check_time)
            start = chrono::high_resolution_clock::now();
        int count = digraph.DAGPathsCount(vertex);
        if (check_time)
            end = chrono::high_resolution_clock::now();
        cout << "Count: " << count << endl;
        if (check_time)
            cout << "Time: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " μs";
    }

    void menu::output_spanning_trees_digraph() {
        if (digraph.getGraph()->isEmpty()) {
            cout << "Graph is empty" << endl;
            return;
        }
        chrono::high_resolution_clock::time_point start, end;
        print_digraph();
        if (check_time)
            start = chrono::high_resolution_clock::now();
        ArraySequence<ArraySequence<pair<int, int>>> arr = digraph.getSpanningTrees();
        if (check_time)
            end = chrono::high_resolution_clock::now();
        cout << "Spanning trees: " << endl;
        for (int i = 0; i < arr.GetSize(); i++) {
            for (int j = 0; j < arr[i].GetSize(); j++) {
                cout << "(" << arr[i][j].first << ", " << arr[i][j].second << ") ";
            }
            cout << endl;
        }
        if (check_time)
            cout << "Time: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " μs";
    }

    void menu::distance_digraph() {
        if (digraph.getGraph()->isEmpty()) {
            cout << "Graph is empty" << endl;
            return;
        }
        chrono::high_resolution_clock::time_point start, end;
        print_digraph();
        cout << "Enter the first vertex: ";
        int vertex1 = get_from_console(0, digraph.getGraph()->getVertexCount() - 1);
        cout << "Enter the second vertex: ";
        int vertex2 = get_from_console(0, digraph.getGraph()->getVertexCount() - 1);
        if (check_time)
            start = chrono::high_resolution_clock::now();
        int dist = digraph.distance(vertex1, vertex2);
        if (check_time)
            end = chrono::high_resolution_clock::now();
        cout << "Distance: " << dist << endl;
        if (check_time)
            cout << "Time: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " μs";
    }

    void menu::distance_all_digraph() {
        if (digraph.getGraph()->isEmpty()) {
            cout << "Graph is empty" << endl;
            return;
        }
        chrono::high_resolution_clock::time_point start, end;
        print_digraph();
        cout << "Enter the vertex: ";
        int vertex = get_from_console(0, digraph.getGraph()->getVertexCount() - 1);
        if (check_time)
            start = chrono::high_resolution_clock::now();
        ArraySequence<int> arr = digraph.BFS(vertex);
        if (check_time)
            end = chrono::high_resolution_clock::now();
        cout << "Distances: " << endl;
        for (int i = 0; i < arr.GetSize(); i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
        if (check_time)
            cout << "Time: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " μs";
    }

    void menu::all_cycles_output_digraph() {
        if (digraph.getGraph()->isEmpty()) {
            cout << "Graph is empty" << endl;
            return;
        }
        chrono::high_resolution_clock::time_point start, end;
        print_digraph();
        if (check_time)
            start = chrono::high_resolution_clock::now();
        ArraySequence<ArraySequence<int>> arr = digraph.getCycles();
        if (check_time)
            end = chrono::high_resolution_clock::now();
        cout << "Cycles: " << endl;
        for (int i = 0; i < arr.GetSize(); i++) {
            for (int j = 0; j < arr[i].GetSize(); j++) {
                cout << arr[i][j] << " ";
            }
            cout << endl;
        }
        if (check_time)
            cout << "Time: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " μs";
    }

    menu::menu() : graph(make_shared<Graph>()), digraph(make_shared<DiGraph>()) {
        check_time = false;
        graph_or_digraph = false;
        my_or_random = false;
    }

    void menu::run() {
        print_graphs();
        switch_graph();
        print_separator();
        print_my_or_random();
        switch_my_or_random();
        if (!my_or_random) {
            if (graph_or_digraph) {
                read_digraph();
                print_digraph();
            } else {
                read_graph();
            }
        } else {
            switch_size();
            setRandomGraph();
        }
        print_separator();
        print_check_time();
        switch_check_time();
        print_separator();

        while (true) {
            print_condition();
            print_separator();
            if (graph_or_digraph) {
                print_actions_digraph();
                if (!switch_actions_digraph()) {
                    break;
                }
            } else {
                print_actions_graph();
                if (!switch_actions_graph()) {
                    break;
                }
            }
            print_separator();
        }
    }

} // namespace sem3