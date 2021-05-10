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