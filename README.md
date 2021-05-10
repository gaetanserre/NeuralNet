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

## License
[GPL v3](https://choosealicense.com/licenses/gpl-3.0/)