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
const std::size_t found = std::string::npos;
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
{	if (id == 0){ 
		return 0;
	}
	int id_left = tree[id].left;
	int id_right = tree[id].right;
	
	int new_left_chain = 0;
	int new_right_chain = 0;

	int left_chain = find_longest_chain(tree, id_left);
	int right_chain = find_longest_chain(tree, id_right);

	if (id_left != 0){
		if (vowels.find(tree[id].letter) != found
		    &&
		    vowels.find(tree[id_left].letter) != found){
			new_left_chain += left_chain + 1;
		}

	}
	if (id_right != 0){
		if (vowels.find(tree[id].letter) != found
		    &&
		    vowels.find(tree[id_right].letter) != found){
			new_right_chain += right_chain + 1;
		}

	}
	long_chain = std::max(long_chain, new_left_chain + new_right_chain);
	return std::max(new_left_chain, new_right_chain);
}
