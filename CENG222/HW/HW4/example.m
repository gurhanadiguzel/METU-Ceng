N=38416;      % size of the Monte Carlo simulation with alpha = 0.05 and error = 0.005
lambda = 12;  % number of fish caught in 3 hours is a Poisson with 3*lambda = 12
TotalWeight=zeros(N,1); % a vector that keeps the total weight of the caught fish for each Monte Carlo run
for k=1:N;
	U = rand; i = 0; % first generate sample Y, the number of caught fish in 3 hours using sampling from Poisson
	F = exp(-lambda);
	while (U>=F);
		i=i+1;
		F = F+exp(-lambda)*lambda^i/gamma(i+1);
	end;
	Y = i;   % Y is the number of fish caught
	weight = 0; % total weight of fish for this run
	
	% now sample Y fish weights using rejection sampling
	s = 0; t = 3; m = 0.7;  % the boundary of the rejection sampling rectangle
	for f=1:Y; 
		CX = 0; CY = m; % initial coordinates for rejection sampling
		F = 0.3; % initial F at CX = 0
		while (CY > F); 
			U = rand; V = rand;
			CX = s+(t-s)*U; CY = m*V;
			
			if CX <= 1
				F = 0.4*(CX^3) - 0.6*(CX^2) + 0.3;
			elseif CX <=2
				F = -1.2*((CX-1)^3) + 1.8*((CX-1)^2) + 0.1;
			else
				F = 1.2*((CX-2)^3) - 1.8*((CX-2)^2) + 0.7;
			end
		end;
		weight = weight + CX;	
	end;
	TotalWeight(k) = weight;
end;
p_est = mean(TotalWeight>25);
expectedWeight = mean(TotalWeight);
stdWeight = std(TotalWeight);
fprintf('Estimated probability = %f\n',p_est);
fprintf('Expected weight = %f\n',expectedWeight);
fprintf('Standard deviation = %f\n',stdWeight);