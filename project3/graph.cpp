#include "graph.hpp"

//make graph funtion
int makeGraph()
{

        //initialize variables
        std::string line;
        int num_buckets;
        std::vector<int> buckets;

        //check input file
        std::ifstream input_file("input.txt");
        if (!input_file)
        {
                std::cout << "Failed to open file\n";
                ;
                return 0;
        }

        //read in number of buckets
        std::getline(input_file, line);
        std::stringstream in_bucket(line);
        in_bucket >> num_buckets;

        //read in the size of buckets
        std::getline(input_file, line);
        std::stringstream b_size(line);
        std::string temp;
        int _bucket;
        while (!b_size.eof())
        {
                b_size >> temp;
                if (std::stringstream(temp) >> _bucket)
                        buckets.push_back(_bucket);
                temp = "";
        }
        input_file.close();

        //get number of vertices
        int num_vertices;
        for (int i = 0; i < buckets.size(); i++)
        {
                buckets.at(i);
                if (i == 0)
                        num_vertices = buckets.at(i) + 1;
                else
                        num_vertices *= buckets.at(i) + 1;
        }

        //add vectors as keys to and map to vertice number
        std::map<std::vector<int>, int> all_vertices;
        for (int i = 0; i < num_vertices; i++)
        {
                all_vertices.insert(std::pair<std::vector<int>, int>(Vertex(i, buckets), i));
        }

        //index to map to get vertex for index in graph
        std::map<int, int> key;
        int kp = 0;
        for (std::map<std::vector<int>, int>::iterator it = all_vertices.begin(); it != all_vertices.end(); ++it)
        {
                key.insert(std::pair<int, int>(it->second, kp));
                kp++;
        }

        //make graph
        int edge_counter = 0;
        std::vector<int> *graph = new std::vector<int>[num_vertices];
        //varibales for loops and vertices
        int r = 0;
        int v_Id;
        //add edges to graph
        //iterate through map of all vertices key: state, value: vertID
        for (std::map<std::vector<int>, int>::iterator it = all_vertices.begin(); it != all_vertices.end(); ++it)
        {
                // temp variables to hold states
                std::vector<int> e_temp = it->first;
                std::vector<int> e_temp2 = e_temp;
                //iterate through states to get edges to add
                //std::cout << v_Id << "  ";
                for (int i = 0; i < e_temp.size(); i++)
                {

                        //check if can fill then fill
                        if (fill(buckets.at(i), e_temp.at(i)))
                        {
                                e_temp2.at(i) = buckets.at(i);
                                v_Id = all_vertices[e_temp2];
                                graph[r].push_back(v_Id);
                                //std::cout << v_Id << " ";
                                edge_counter++;
                                e_temp2 = e_temp;
                        }
                        //check if there is any amount to empty if so empty it
                        if (empty(e_temp.at(i)))
                        {
                                e_temp2.at(i) = 0;
                                v_Id = all_vertices[e_temp2];
                                graph[r].push_back(v_Id);
                                //std::cout << v_Id << " ";
                                edge_counter++;
                                e_temp2 = e_temp;
                        }

                        // pour one bukcet into another transition
                        for (int j = 0; j < e_temp.size(); j++)
                        {
                                if (i == j)
                                {
                                        continue;
                                } //same bucket skip
                                if ((e_temp.at(j) < buckets.at(j)) && e_temp.at(i) != 0)
                                { //if the bucket not full
                                        e_temp2.at(j) += e_temp.at(i);
                                        e_temp2.at(i) = 0;
                                        if (e_temp2.at(j) > buckets.at(j))
                                        {
                                                e_temp2.at(i) = e_temp2.at(j) - buckets.at(j);
                                                e_temp2.at(j) = buckets.at(j);
                                        }
                                        v_Id = all_vertices[e_temp2];
                                        graph[r].push_back(v_Id);
                                        edge_counter++;
                                        e_temp2 = e_temp;
                                }
                        }
                }
                r++;
        }

        //BFS initialize data structures
        int bfs_level[num_vertices];
        bool visited[num_vertices];
        int sums[sum(buckets) + 1];
        for (int i = 0; i < num_vertices; i++)
        {
                bfs_level[i] = -1;
                visited[i] = false;
                if (i < (sum(buckets) + 1))
                        sums[i] = -1;
        }

        //BFS
        //start vertex
        int u = 0;
        visited[u] = true;
        bfs_level[u] = 0;

        //to store hardest to make and the moves it took
        int max_moves = 0;
        int max_vertex = 0;

        //begin BFS at vertex u
        std::queue<int> queue;
        queue.push(u);

        //check queue
        while (!queue.empty())
        {
                u = queue.front();
                queue.pop();
                for (int i = 0; i < graph[key[u]].size(); i++)
                {
                        int temp = graph[key[u]].at(i);
                        if (visited[temp] == false)
                        {
                                queue.push(temp);
                                bfs_level[temp] = bfs_level[u] + 1;
                                visited[temp] = true;
                                if ((bfs_level[temp] > max_moves) && sums[sum(Vertex(temp, buckets))] == -1)
                                {
                                        max_moves = bfs_level[temp];
                                        max_vertex = temp;
                                        sums[sum(Vertex(temp, buckets))] = max_moves;
                                }
                                else if (sums[sum(Vertex(temp, buckets))] == -1)
                                        sums[sum(Vertex(temp, buckets))] = bfs_level[u] + 1;
                        }
                }
        }

        //if there is a tie use smallest amount of water look in sums array
        for (int i = 0; i < sum(buckets) + 1; i++)
        {
                if (max_moves == sums[i])
                {
                        max_vertex = i;
                        break;
                }
                else
                        max_vertex = sum(Vertex(max_vertex, buckets));
        }

        //write to file
        std::ofstream outfile("output.txt");
        outfile << num_vertices << "," << edge_counter << "," << max_vertex << "," << max_moves;
        outfile.close();

        delete[] graph;
        return 0;
}

//helper functions
int sum(std::vector<int> v)
{
        int sum = 0;
        for (int i = 0; i < v.size(); ++i)
                sum += v[i];
        return sum;
}

//make states in graph and map to the vertex number
std::vector<int> Vertex(int vertex_id, std::vector<int> _b)
{
        std::vector<int> build_state;
        for (int i = 0; i < _b.size(); i++)
        {
                build_state.push_back(vertex_id % (_b.at(i) + 1));
                vertex_id /= _b.at(i) + 1;
        }
        return build_state;
}

//check if bucket can be filled
bool fill(int max_size, int amount)
{
        if (amount < max_size)
        {
                return true;
        }
        return false;
}

//check if bucket is empty
bool empty(int current_amount)
{
        if (current_amount == 0)
        {
                return false;
        }
        return true;
}
