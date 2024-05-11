c_k = [0.3, 2, -1.2, 0.5]';
n_values = [5, 10, 100];
runTime = 100;

A_list = cell(numel(n_values), 1);
O_list = cell(numel(n_values), 1);
c_k_list = cell(numel(n_values), 1);
c_k_error_average = zeros(numel(n_values), 1);

for i=1:numel(n_values)
    n = n_values(i);
    [A_n,b_n,t_n]=N_obs(n,3);
    A_list{i} = A_n;
    O_list{i} = [t_n, b_n];
end 

for j=1:runTime 
    for i=1:numel(n_values)
        b_n=O_list{i}(:,2);
        A_n=A_list{i};
        [Q,R] = qr(A_n);
        [m, n] = size(A_n);
        r = rank(A_n);
        Q1 = Q(:, 1:r); % Columns 1 to rank(A) for row space
        Q2 = Q(:, r+1:end) ;% Columns rank(A)+1 to end for null space
        appx_c_k=inv(R(1:r,1:r))*Q1'*b_n;
        c_k_list{i}=appx_c_k;
    end
    
    for i=1:numel(n_values)
        c_k_error_average(i) = c_k_error_average(i)+ norm(c_k - c_k_list{i},2);
    end
end
c_k_error_average= c_k_error_average/runTime;

function [A_n, b_n, t_n] = N_obs(n, k)
    A_n = zeros(n, k + 1);
    t_n = (1:n)' / (n + 1);
    c_k = [0.3, 2, -1.2, 0.5];
    epsilon = randn(n, 1) * 0.01;

    for i = 0:k
        A_n(:, i + 1) = t_n.^i;
    end

    A_n_noised = A_n;
    A_n_noised(:, 2:end) = A_n_noised(:, 2:end) + epsilon;

    b_n = A_n_noised * c_k';
end