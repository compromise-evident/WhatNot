#!/usr/bin/env python3

# YOUR CONTROLS (CHANGE ANY 1st 4? GET NEW MODEL!)                                                                                         Run it: "apt install geany python3-torch". Open the .py in Geany.
longest =  784 # Longest data string in train.txt, test.txt, cognize.txt  (safe.)    input  layer                                          Replace "python" with "python3" in Geany's execute command. F5 to run.
classes =   10 # Number of different labels (2 = labels 0,1. 500 = labels 0-499.)    output layer
width   =   70 # Number of neurons per hidden layer (wide = attentive to detail.)    hidden layer size
depth   =    2 # Number of hidden layers  (the active brain parts of your model.)    hidden layer quantity
ln_rate = 0.01 # Learning-rate. This tells PyTorch how aggressively each model parameter is to be adjusted.
a_batch =    1 # Number of train.txt items studied at once; accumulated. If 1, retrain can also be 1/small.
retrain =    1 # Number of times to train on entire train.txt. It's best to increase retrain if a_batch >1.



# ML ready to use. Verify that your model can generalize on the given training-data by
# scoring well. Then replace the data with your own (label & string per line in text file.)

import torch, torch.nn as nn, torch.optim as optim

print("\n(1) Model   (Create a new model and save it as one file.)")
print(  "(2) Train   (Train & test model on train.txt & test.txt.)")
print(  "(3) Test    (See only testing on test.txt - no training.)")
print(  "(4) Use     (Classify unlabeled cognize.txt - no spaces.)"); o = int(input("\nOption: "));

model = nn.Sequential(); model.add_module('input',       nn.Linear(longest, width  )); model.add_module('relu1',     nn.ReLU());
for a in range(depth):   model.add_module(f'hidden_{a}', nn.Linear(  width, width  )); model.add_module(f'relu_{a}', nn.ReLU());
model.add_module                         ('output',      nn.Linear(  width, classes)); normalized = [0.0] * longest;

if o == 1: # Model___________________________________________________________________________________________________________________________________________________
	torch.save(model.state_dict(), 'Model.pth'); print("\nModel.pth saved with hidden layers:  ", width, "wide,", depth, "deep.")          # Saves model to file.

if o == 2: # Train___________________________________________________________________________________________________________________________________________________
	model.load_state_dict(torch.load('Model.pth', map_location = 'cpu'))                                                                   # Loads model from file.
	with open('training-data/train.txt', 'r') as f: total_training_data_items = sum(1 for line in f)
	number_of_full_batches = (total_training_data_items - (total_training_data_items % a_batch)) // a_batch                                # Number of full batches.
	criterion = nn.CrossEntropyLoss(); optimizer = optim.SGD(model.parameters(), lr = ln_rate); model.train(); print("\n", end = '');
	input_data = torch.empty(a_batch, longest); target_data = torch.empty(a_batch, 1, dtype=torch.long).squeeze(1);
	for loop in range(retrain):
		in_stream = open('training-data/train.txt', 'r')
		for a in range(number_of_full_batches):
			print(f"Training on {a_batch}-batch {a + 1} of {number_of_full_batches}   round {loop + 1} of {retrain}")
			for b in range(a_batch):                                                                                                       # Grabs a batch.
				normalized[:] = [0.0] * longest; line = in_stream.readline().split(); length = len(line[1]);
				if length > longest: length = longest
				for c in range(length):
					if line[1][c] == '@': normalized[c] = 1.0
				target_data[b] = int(line[0]); input_data[b] = torch.tensor(normalized);                                                   # Class, data.
			optimizer.zero_grad(); outputs = model(input_data); loss = criterion(outputs, target_data); loss.backward(); optimizer.step(); # Uses & updates model.
		in_stream.close()
	torch.save(model.state_dict(), 'Model.pth');                                                                                           # Saves updated model.

if o == 3 or o == 2: # Test__________________________________________________________________________________________________________________________________________
	if o == 3: model.load_state_dict(torch.load('Model.pth', map_location = 'cpu'))                                                        # Loads model from file.
	with open('training-data/test.txt', 'r') as f: total_testing_data_items = sum(1 for line in f)                                         # Quantity to test on.
	misclassified = 0; off_by_summation = 0; model.eval(); print("\n", end = '');
	in_stream = open('training-data/test.txt', 'r'); out_stream = open('results.txt', 'w'); out_xtra = open('results_extra.txt', 'w');
	for a in range(total_testing_data_items):
		print("Testing on test.txt line", (a + 1), "of", total_testing_data_items)
		normalized[:] = [0.0] * longest; line = in_stream.readline().split(); length = len(line[1]); expected_class = int(line[0]);        # Expected classification.
		if length > longest: length = longest
		for b in range(length):                                                                                                            # Data to be classified.
			if line[1][b] == '@': normalized[b] = 1.0
		input_data = torch.tensor(normalized).view(1, longest)
		with torch.no_grad(): outputs = model(input_data); _, predictions = torch.max(outputs, 1);                                         # Uses model.
		classification = predictions[0].item(); out_stream.write(f"{classification}\n");                                                   # Saves classification.
		if classification != expected_class: misclassified += 1; off_by_summation += (abs(expected_class - classification));               # Checks if misclassified.
		if classification == expected_class: out_xtra.write(f"{classification} (OK\n")
		else: out_xtra.write(f"{classification} ({expected_class}  was the label - off by {abs(expected_class - classification)}\n")
	in_stream.close(); out_stream.close(); out_xtra.close();
	print("\n\n\n", format((((total_testing_data_items - misclassified) / total_testing_data_items) * 100), ".15f"), end = "% correct")
	print(" (misclassifies", misclassified, "out of", total_testing_data_items, end = ")\n\n")
	print(f"Off by {off_by_summation / misclassified} on average (see results_extra.txt)")

if o == 4: # Use_____________________________________________________________________________________________________________________________________________________
	model.load_state_dict(torch.load('Model.pth', map_location = 'cpu'))                                                                   # Loads model from file.
	with open('cognize.txt', 'r') as f: total_real_world_items = sum(1 for line in f)                                                      # Quantity to cognize.
	in_stream = open('cognize.txt', 'r'); out_stream = open('results.txt', 'w'); model.eval(); print("\n", end = '');
	for a in range(total_real_world_items):
		print("Classifying cognize.txt line", (a + 1), "of", total_real_world_items)
		normalized[:] = [0.0] * longest; line = in_stream.readline(); length = (len(line) - 1);
		if length > longest: length = longest
		for b in range(length):                                                                                                            # Data to be classified.
			if line[b] == '@': normalized[b] = 1.0
		input_data = torch.tensor(normalized).view(1, longest)
		with torch.no_grad(): outputs = model(input_data); _, predictions = torch.max(outputs, 1);                                         # Uses model.
		classification = predictions[0].item(); out_stream.write(f"{classification}\n");                                                   # Saves classification.
	in_stream.close(); out_stream.close(); print("\nSee results.txt");
