# Neural Net

Neural Net is a C++ library able to create a neural network from a file containing the weights.

Currently, only the *Dense* layers and the *Relu* activation function are available but it's quite easy to add more.

## Structure of the weight file

```
layer activation_function
w1,1 w1,2 w1,3 b1
w2,1 w2,2 w2,3 b2
...
layer activation_function
w1,1 w1,2 w1,3 b1
w2,1 w2,2 w2,3 b2
...
```
Where 
+ *wi,d* is the weight at dimension *d* for the neuron number *i*.
+ *bi* is the bias of the neuron number *i*.
+ *activation_function* is the activation function of each neuron in the layer. (See [Activation functions](#activation-functions) section below).

## Save your model
If you are using Keras and Tensorflow, you can use this function to save your model into a file recognized by Neural Net:
```python
def saveTFModel(model, output_path):
  s = ""
  for layer in model.layers:
    w = layer.get_weights()
    if len(w) > 1:
      s += f"layer {layer.get_config()['activation']}\n"
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

## Activation functions
+ 'linear'
+ 'relu'
+ 'softplus'
+ 'softsign'
+ 'tanh'

It's pretty easy to add more activation functions. See `activation_function.h` if you want to add your own.


## Examples
Single prediction:
```c++
#include <iostream>
#include <vector>

#include "neuralnet.h"

using namespace std;

int main (int argc, char** argv) {
  NeuralNetwork nn("weights.nn");
  nn.summary();
  
  vector<double> data;
  data.push_back(763);
  data.push_back(151);
	
  cout << "Prediction: " << nn.single_predict(data) << endl;
	
  return 1;
}
```

Output:
```
Layer 0 → 2 neurons with tanh activation function.
Layer 1 → 1 neuron with linear activation function.
Prediction: 0.0295543
```

Multiple predictions:
```c++
#include <iostream>
#include <vector>

#include "neuralnet.h"

using namespace std;

int main (int argc, char** argv) {
  NeuralNetwork nn;
  nn.init("weights.nn");
  nn.summary();

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

Output:
```
Layer 0 → 64 neurons with tanh activation function.
Layer 1 → 256 neurons with softplus activation function.
Layer 2 → 1 neuron with linear activation function.
Prediction0: 0.622099
Prediction1: 0.477628
```


## License
[GPL v3](https://choosealicense.com/licenses/gpl-3.0/)