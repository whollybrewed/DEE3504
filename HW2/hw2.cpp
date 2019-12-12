#include <iostream>
#include <fstream>
#include <algorithm> 

struct CorpInfo{
	int area;
	int value;
};

int recur(CorpInfo *corp, int remain, int type);
int dynamic(CorpInfo *corp, int field_area);
int memo(CorpInfo *corp, int remain, int *cache);

int num_corp;

int main(int argc, char* argv[])
{
	std::ifstream fin;
	int mode, field_area, result;
	fin.open(argv[1]);	 
	fin >> mode;
	fin >> field_area;
	fin >> num_corp;
	CorpInfo corp[num_corp];
	for (int i = 0; i < num_corp; i++){
		fin >> corp[i].area;
		fin >> corp[i].value;
	}
	fin.close();
	if (mode == 0){
		result = recur(corp, field_area, num_corp);
	}
	else if (mode == 1){
		result = dynamic(corp, field_area);
	}
	else if (mode == 2){
		int cache[field_area + 1];
		for (int i = 0; i < field_area + 1; i++){
			cache[i] = -1;
		} 
		result = memo(corp, field_area, cache);
	}
	std::ofstream fout;
	fout.open(argv[2]);	
	fout << result;
	fout.close();
	return 0; 
}

int recur(CorpInfo *corp, int remain, int type)
{
    int highest_val = 0, new_remain, val_choose, val_not_choose;
    if (remain < 0 || type < 0){
        return 0;
    }
    if (remain < corp[type].area){
        highest_val = recur(corp, remain, type - 1);
    }
    else{
        new_remain = remain - corp[type].area;
        val_choose = corp[type].value + recur(corp, new_remain, type);
        val_not_choose = recur(corp, remain, type - 1);
        highest_val = std::max(val_choose, val_not_choose);
    }
    return highest_val;
}

int dynamic(CorpInfo *corp, int field_area)
{
	int field_best[field_area + 1];
	for (int i = 0; i < field_area + 1; i++){
		field_best[i] = 0;
	} 
	int tmp_val;
	for (int tmp_area = 0; tmp_area < field_area + 1; tmp_area++){
		for (int i = 0; i < num_corp; i++){
			if (corp[i].area <= tmp_area){
				tmp_val = field_best[tmp_area - corp[i].area] + corp[i].value;
				field_best[tmp_area] = std::max(field_best[tmp_area], tmp_val);   
			}
		}
	}
	return field_best[field_area];
}

int memo(CorpInfo *corp, int remain, int *cache)
{   
	if (cache[remain] == -1){
		int highest_val = 0, tmp_val, new_remain, buffer;
		for (int i = 0; i < num_corp; i++){
			new_remain = remain - corp[i].area;
			if (new_remain < 0){ 
				continue;
			}
			buffer = memo(corp, new_remain, cache);
			cache[new_remain] = buffer;
			tmp_val = corp[i].value + buffer;
			highest_val = std::max(highest_val, tmp_val);
		}
		return highest_val;
	}
	else{
		return cache[remain];
	}
}
