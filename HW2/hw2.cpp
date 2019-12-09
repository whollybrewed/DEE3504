#include <iostream>
#include <fstream>
#include <algorithm> 

struct CropInfo{
	int area;
	int value;
};

int recur(CropInfo *crop, int remain);

int num_crop;

int main(int argc, char* argv[])
{
	std::ifstream fin;
	int mode, field_area;
	fin.open(argv[1]);	 
	fin >> mode;
    fin >> field_area;
    fin >> num_crop;
	
	CropInfo crop[num_crop];
	for (int i = 0; i < num_crop; i++){
		fin >> crop[i].area;
		fin >> crop[i].value;
	}
	fin.close();
    std::cout << recur(crop, field_area) << std::endl; 
	return 0; 
}

int recur(CropInfo *crop, int remain)
{
        int highest_val = 0, tmp, new_remain;
        for (int i = 0; i < num_crop; i++){
            new_remain = remain - crop[i].area;
            if (new_remain < 0){ 
                continue;
            }
            tmp = crop[i].value + recur(crop, new_remain);
            highest_val = std::max(highest_val, tmp);
        }
        return highest_val;
}
