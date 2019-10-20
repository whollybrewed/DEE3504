#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector> 

struct Node{
	char letter;
	int left;
	int right;
};
int find_longest_chain(Node *tree, std::vector<std::vector<int> > &table, int id);
void print_result(int mode, char* output_name);
const std::size_t unfound = std::string::npos;
std::string vowels = "aeiou";
int long_chain = 0;
std::vector<int> result_chain;
int main(int argc, char* argv[])
{
	std::ifstream fin;
	int num_of_nodes, mode;
	fin.open(argv[1]);	 
	fin >> num_of_nodes;
	fin >> mode;
	Node alphabet_tree[num_of_nodes + 1];
	std::vector<std::vector<int> > chain_table(num_of_nodes + 1);
	for (int i = 1; i <= num_of_nodes; i++){
		int tmp_id = 0;
		fin >> tmp_id; 
		fin >> alphabet_tree[tmp_id].letter;
		fin >> alphabet_tree[tmp_id].left;
		fin >> alphabet_tree[tmp_id].right;

	}
	fin.close(); 
	find_longest_chain(alphabet_tree, chain_table, num_of_nodes);
	print_result(mode, argv[2]);
	return 0; 
}

int find_longest_chain(Node *tree, std::vector<std::vector<int> > &table, int id)
{	if (id == 0){ 
		return 0;
	}
	std::vector<int> left_result;
	std::vector<int> right_result;
	std::vector<int> right_result_reverse;

	int id_left = tree[id].left;
	int id_right = tree[id].right;
	
	int new_left_chain = 0;
	int new_right_chain = 0;
	
	int left_chain = find_longest_chain(tree, table, id_left);
	int right_chain = find_longest_chain(tree, table, id_right);

	if (id_left != 0){
		if (vowels.find(tree[id].letter) != unfound
		    &&
		    vowels.find(tree[id_left].letter) != unfound){
			new_left_chain += left_chain + 1;
			left_result = table[id_left];
		}
	}
	if (id_right != 0){
		if (vowels.find(tree[id].letter) != unfound
		    &&
		    vowels.find(tree[id_right].letter) != unfound){
			new_right_chain += right_chain + 1;
			right_result = table[id_right];
		}
	}
	if (new_left_chain + new_right_chain > long_chain){
		result_chain.clear();
		result_chain.insert(result_chain.begin(), left_result.begin(), left_result.end());
		result_chain.push_back(id);
		right_result_reverse = right_result;
		std::reverse(right_result_reverse.begin(),right_result_reverse.end());
		result_chain.insert(result_chain.end(), right_result_reverse.begin(), right_result_reverse.end());	
	}
	

	long_chain = std::max(long_chain, new_left_chain + new_right_chain);

	if (new_left_chain > new_right_chain){
		table[id].clear();
		if (vowels.find(tree[id].letter) != unfound){
			table[id] = left_result;
			table[id].push_back(id);
		}
		return new_left_chain;
		
	}
	else{
		table[id].clear();
		if (vowels.find(tree[id].letter) != unfound){
			table[id] = right_result;
			table[id].push_back(id);
		}
		return new_right_chain;
		
	}
}

void print_result(int mode, char *output_name)
{
	std::ofstream fout;
	fout.open(output_name);	
	fout << long_chain << std::endl;
	if (mode == 1){
		if (result_chain.front() > result_chain.back()){
			std::reverse(result_chain.begin(), result_chain.end());
		}
		fout << '\n';
		for (int i = 0; i< result_chain.size(); i++) {
			fout << result_chain[i] << '\n';
		}	
	}
	fout.close();
}
