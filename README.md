# Neural Net

Neural Net is a C++ library able to easely create and use a neural network from a file containing its weights.
The vector product is parallelized using `pthread`. (Disabled by default)

Currently, only the *Dense* layers are available.

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
Where:
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
      for i in range(nb_neurons):
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

#include "neuralnet.hpp"

using namespace std;

int main (int argc, char** argv) {
  NeuralNetwork nn("example_weights.nn");
  nn.summary();
  
  vector<double> data {1265, 88};
	
  cout << "Prediction: " << nn.single_predict(data)[0] << endl;
	
  return 1;
}
```

Output:
```
Network summary:
--------------------------------------------------------
Layer 0 → 256 neurons with relu activation function.
Layer 1 → 128 neurons with relu activation function.
Layer 2 → 64 neurons with relu activation function.
Layer 3 → 1 neuron with linear activation function.
--------------------------------------------------------

Prediction: 1.44234
```

Multiple predictions:
```c++
#include <iostream>
#include <vector>

#include "neuralnet.hpp"

using namespace std;

int main (int argc, char** argv) {
  NeuralNetwork nn;
  nn.init("example_weights.nn");
  nn.parallelization = true;
  nn.summary();

  vector<vector<double>> data {{154, 675}, {2312, 832}};

  vector<vector<double>> predictions = nn.predict(data);
  for (int i = 0; i<predictions.size(); i++)
	  cout << "Prediction" << i << ": " << predictions[i][0] << endl;
	
  return 1;
}
```

Output:
```
Network summary:
--------------------------------------------------------
Layer 0 → 256 neurons with relu activation function.
Layer 1 → 128 neurons with relu activation function.
Layer 2 → 64 neurons with relu activation function.
Layer 3 → 1 neuron with linear activation function.
--------------------------------------------------------

Prediction0: 0.407461
Prediction1: 1.18481
```

## References
Please cite Neural Net in your publications if this is useful for your research. Here is an example BibTeX entry:
```
@misc{serre2021neuralnet,
  title={Neural Net},
  author={Gaëtan Serré},
  year={2021},
  howpublished={\url{https://github.com/LE10EENFAIT/NeuralNet}},
}
```


## License
[GPL v3](https://choosealicense.com/licenses/gpl-3.0/)