#include <fdeep/fdeep.hpp>

#include "cnpy.h"
#include "tqdm/tqdm.h"

#include <iostream>
#include <chrono>
#include <vector>
#include <numeric>

using namespace std;

int main()
{
    const auto model = fdeep::load_model("../res/models/my_model_tech_db_filtered2020-05-13_15-05-43_0.094_0.094.json");
    
    cnpy::NpyArray image = cnpy::npy_load("../res/dataset/1000008.npy");
    
    cout << "\nImage dimensions : " << '(' << image.shape[0] << ',' << image.shape[1] << ',' << image.shape[2] << ')' << endl;
    
    float* imageData = image.data<float>();
    vector<float> imageVector(imageData, imageData + 68*68);
    
    const fdeep::tensor input = fdeep::tensor(fdeep::tensor_shape(68, 68, 1), imageVector);
    cout << "Input tensor shape : " << fdeep::show_tensor_shape(input.shape()) << endl;
    
    const fdeep::tensor qp = fdeep::tensor(fdeep::tensor_shape(1), 22);
    cout << "QP tensor shape : " << fdeep::show_tensor_shape(qp.shape()) << endl << endl;
    
    vector<double> elapsedTimes;
    tqdm bar;
    
    auto start = chrono::high_resolution_clock::now();
    const auto result = model.predict({input,qp});
    chrono::duration<double> elapsed = chrono::high_resolution_clock::now() - start;
    
    elapsedTimes.push_back(elapsed.count() * 1000);
    
    bar.progress(1, 100);
    
    for(int i = 0; i < 99; i++) {
    
	    auto start = chrono::high_resolution_clock::now();
	    const auto innerResult = model.predict({input,qp});
	    chrono::duration<double> elapsed = chrono::high_resolution_clock::now() - start;
	    
	    elapsedTimes.push_back(elapsed.count() * 1000);
	    
	    bar.progress(i+1, 100);
    
    }
    
    bar.finish();
    
    cout << "\nResult tensor shape : " << fdeep::show_tensor_shape(result.front().shape()) << endl;
    cout << "Average inference duration : " << accumulate(elapsedTimes.begin(),elapsedTimes.end(),0.0)/elapsedTimes.size() << "ms" << endl << endl;
    
}
