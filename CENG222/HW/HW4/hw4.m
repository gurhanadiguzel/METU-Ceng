
N=4147;   % 4146.7 size of the Monte Carlo simulation with alpha = 0.05 and error = 0.002
lambda_auto = 50; 
lambda_truck = 10;
TotalWeight =  zeros(N,1);

for k=1:N;
	U1= rand; i = 0; 
	F_auto = exp(-lambda_auto);
	while (U1 >= F_auto);
		i=i+1;
		F_auto = F_auto + exp(-lambda_auto) * lambda_auto^i/gamma(i+1);
	end;
	CountAuto = i;   % The number of automobile
	WeightAuto = sum( -1/0.15 * log(rand(190,CountAuto)));
	TotalWeightAuto =sum(WeightAuto);

	U2 = rand; j = 0; 
	F_truck = exp(-lambda_truck);
	while (U2 >= F_truck);
		j=j+1;
		F_truck = F_truck + exp(-lambda_truck) * lambda_truck^j / gamma(j+1);
	end;
	CountTruck = j;   % The number of trucks
	WeightTruck = sum( -1/0.01 * log(rand(110,CountTruck)));
	TotalWeightTruck = sum(WeightTruck);

	TotalWeight(k) = TotalWeightAuto + TotalWeightTruck;	
end;

stdWeight = std(TotalWeight);

fprintf('Probability that the total weight of all the vehicles that pass over the bridge on a day = %f\n',mean(TotalWeight>200000));

fprintf('Total weight of all the vehicles that pass over the bridge on a day = %f\n',mean(TotalWeight));

fprintf('Standard deviation = %f\n',stdWeight);