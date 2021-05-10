# Neural Net

Neural Net is a C++ library able to create a neural network from a file containing the weights.

Currently, only the *Dense* layers and the *Relu* activation function are available but it's quite easy to add more.

## Structure of the weight file

```
layer
w1,1 w1,2 w1,3 b1
w2,1 w2,2 w2,3 b2
...
layer
w1,1 w1,2 w1,3 b1
w2,1 w2,2 w2,3 b2
...
```
With 
+ *wi,d* the weight at dimension *d* for the neuron number *i*.
+ *bi* the bias of the neuron number *i*.

## Save your model
If you are using Keras and Tensorflow, you can use this function to save your model into a file recognized by Neural Net:
```python
def saveTFModel(model, output_path):
    s = ""
    for layer in model.layers:
        w = layer.get_weights()
        if len(w) > 1:
            s += "layer\n"
            weights = w[0]
            bias = w[1]

            dimensions = len(weights)
            nb_neurons = len(weights[0])

            if nb_neurons == 1:
                for i in range(dimensions):
                    s += str(weights[i][0]) + " "
                s+= str(bias[0]) + "\n"

            else:
                for i in range(nb_neurons):
                    w = []
                    for j in range(dimensions):
                        s += str(weights[j][i]) + " "
                    s+= str(bias[i]) + "\n"
    f = open(output_path, "w")
    f.write(s)
    f.close()
```

## Examples
Single prediction:
```c++
#include <iostream>
#include <vector>

#include "neuralnet.h"

using namespace std;

int main (int argc, char** argv) {
	NeuralNetwork nn;
	nn.init("weights.txt");
	vector<double> data;
	data.push_back(1.0);
	data.push_back(-0.62);
	
	cout << "Prediction: " << nn.single_predict(data) << endl;
	
	return 1;
}
```

Multiple predictions:
```c++
#include <iostream>
#include <vector>

#include "neuralnet.h"

using namespace std;

int main (int argc, char** argv) {
	NeuralNetwork nn;
	nn.init("weights.txt");
	vector<vector<double>> data;
	vector<double> temp;
	
	temp.push_back(1.0);
	temp.push_back(-0.62);
	data.push_back(vector<double> (temp));
	temp.clear();
	
	temp.push_back(-2.3);
	temp.push_back(0.42);
	data.push_back(vector<double> (temp));
	temp.clear();
	
	vector<double> predictions = nn.predict(data);
	for (int i = 0; i<predictions.size(); i++)
		cout << "Prediction" << i << ": " << predictions[i] << endl;
	
	return 1;
}
```


## License
[GPL v3](https://choosealicense.com/licenses/gpl-3.0/)