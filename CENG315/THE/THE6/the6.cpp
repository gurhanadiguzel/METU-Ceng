#include "the6.h"

/* 
    in the6.h "struct Pipeline" is defined as below:
    
    struct Pipeline {
        int id;                     // pipeline id
        int end1;                   // id of the building-1
        int end2;                   // id of the building-2
        int cost_of_consumption;    // amount/cost of consumption for pipeline
    };

*/
#define MAX_WEIGHT 1001

vector<int> plan_min_cost_pipeline_usage(vector<Pipeline*> pipelines, int num_of_buildings) {
    
    vector<int> solution;
    vector<bool> visited(num_of_buildings+1, false);
    vector<vector<int>> matrix(num_of_buildings+1, vector<int> (num_of_buildings+1, MAX_WEIGHT));   
    vector<vector<int>> matrixOfId(num_of_buildings+1, vector<int> (num_of_buildings+1, -1)); 

    for(int i=0; i<pipelines.size();i++)
    {
        if(pipelines[i]->end1 == pipelines[i]->end2 && matrix[num_of_buildings][pipelines[i]->end2] > pipelines[i]->cost_of_consumption){
            matrix[num_of_buildings][pipelines[i]->end2] = pipelines[i]->cost_of_consumption;
            matrix[pipelines[i]->end2][num_of_buildings] = pipelines[i]->cost_of_consumption;
            matrixOfId[num_of_buildings][pipelines[i]->end2] = pipelines[i]->id;
            matrixOfId[pipelines[i]->end2][num_of_buildings] = pipelines[i]->id;
        }
        else if(matrix[pipelines[i]->end1][pipelines[i]->end2] > pipelines[i]->cost_of_consumption){
            matrix[pipelines[i]->end1][pipelines[i]->end2] = pipelines[i]->cost_of_consumption;
            matrix[pipelines[i]->end2][pipelines[i]->end1] = pipelines[i]->cost_of_consumption;
            matrixOfId[pipelines[i]->end1][pipelines[i]->end2] = pipelines[i]->id;
            matrixOfId[pipelines[i]->end2][pipelines[i]->end1] = pipelines[i]->id;

        }  
    }
    
    visited[num_of_buildings] = true;
    int no_edge=0;  // number of edge
    int x;          //  row number
    int y;          //  col number

    while (no_edge < num_of_buildings) {
        int min = MAX_WEIGHT;
        x = -1;
        y = -1;
        for (int i = 0; i < num_of_buildings+1; i++) {
            if (visited[i]) {
                for (int j = 0; j < num_of_buildings+1; j++) {
                    if (!visited[j] && matrix[i][j] != MAX_WEIGHT && min > matrix[i][j]) {
                        min = matrix[i][j];
                        x = i;
                        y = j;
                    }
                }
            }
        }
        visited[y] = true;
        no_edge++;
        solution.push_back(matrixOfId[x][y]);
    }

    return solution;    
}

vector<int> optimize_plan(vector<Pipeline*> current_solution, Pipeline* new_pipeline) {
 
    vector<int> solution;
    int index = -1;
    int max = 0;
    for (int i = 0; i < current_solution.size(); i++)
    {
        
        if (current_solution[i]->end1 == current_solution[i]->end2 &&
            (current_solution[i]->end1 == new_pipeline->end1 || current_solution[i]->end1 == new_pipeline->end2) &&
            max < current_solution[i]->cost_of_consumption && 
            current_solution[i]->cost_of_consumption > new_pipeline->cost_of_consumption)
        {
            index = i;
            max = new_pipeline->cost_of_consumption;
        }
    }
    if (index != -1)
    {
        current_solution[index] = new_pipeline;
        for (int i = 0; i < current_solution.size(); i++)
        {
            solution.push_back(current_solution[i]->id);
        }
    }
    else{
        current_solution.push_back(new_pipeline);
        solution = plan_min_cost_pipeline_usage(current_solution, current_solution.size()-1);
    }

    return solution;
    
}

