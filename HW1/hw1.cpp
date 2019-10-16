#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

struct Node{
	char letter;
	int left;
	int right;
};

int find_longest_chain(Node *tree, int id);

std::string vowels = "aeiou";
int long_chain = 0;
int main(int argc, char* argv[])
{
	std::ifstream fin;
	int num_of_nodes, mode;
	fin.open(argv[1]);	 
	fin >> num_of_nodes;
	fin >> mode;
	Node alphabet_tree[num_of_nodes + 1];
	for (int i = 1; i <= num_of_nodes; i++){
		int tmp_id = 0;
		fin >> tmp_id; 
		fin >> alphabet_tree[tmp_id].letter;
		fin >> alphabet_tree[tmp_id].left;
		fin >> alphabet_tree[tmp_id].right;
			
	}
	fin.close(); 
	find_longest_chain(alphabet_tree, num_of_nodes);
	std::cout << long_chain << std::endl;
	return 0; 
}

int find_longest_chain(Node *tree, int id)
{
	if (tree[id].left + tree[id].right == 0){ 
		if (vowels.find(tree[id].letter) != std::string::npos){
			return 1;
		}
	}
	else{	
		int left_chain = 0;
		int right_chain = 0;
		int new_left_chain = 0;
		int new_right_chain = 0;
		if (tree[id].left != 0)
			left_chain = find_longest_chain(tree, tree[id].left);
		if (tree[id].right != 0)
			 right_chain = find_longest_chain(tree, tree[id].right);
		if (vowels.find(tree[id].letter) != std::string::npos){
			new_left_chain = left_chain + 1;
			new_right_chain = right_chain + 1;
		}
		long_chain = std::max(long_chain, new_left_chain + new_right_chain - 2);
		return std::max(new_left_chain, new_right_chain);
	}
}
