% Initialize variables
nValues = 2:300; % Creates an array containing integers from 2 to 300

% Initialize ar rays to store run times and relative errors
% Number of rows equal to the number of elements in nValues and 3 columns.
totalRunTimes = zeros(numel(nValues), 3); % One column for each algorithm
relErrors = zeros(numel(nValues), 3);     % Subsequent computations will be repeated 
normType = 'fro';
%normType = 2;

% Loop different matrix sizes
for index=1 : numel(nValues)
    n = nValues(index);
    
    % Generate Hilbert matrix
    A = hilb(n);
    
    % Perform LU factorization without pivoting
    tic; %Start timerQ
    [L, U] = my_lu(A);
    totalRunTimes(index, 1) = toc ; % Stop the timer
    relErrors(index, 1) = norm(A - L * U, normType) / norm(A, normType); % Calculate relative error
    
    % Perform LU factorization with partial pivoting
    tic; %Start timer
    [L, U, P] = my_lu_pp(A);
    totalRunTimes(index, 2) = toc ; % Stop the timer
    relErrors(index, 2) = norm(P*A - L*U, normType) / norm(P*A, normType); % Calculate relative error
    
    % Perform LU factorization with complete pivoting
    tic; %Start timer   
    [L, U, P, Q] = my_lu_cp(A);   
    totalRunTimes(index, 3) = toc ;  % Stop the timer 
    relErrors(index, 3) = norm(P*A*Q - L*U, normType) / norm(P*A*Q, normType); % Calculate relative error

end

figure;
% Plot run times
subplot(2, 1, 1);
plot(nValues, totalRunTimes(:, 1), 'o-', 'DisplayName', 'LU without Pivoting');
hold on;
plot(nValues, totalRunTimes(:, 2), 's-', 'DisplayName', 'LU with Partial Pivoting');
plot(nValues, totalRunTimes(:, 3), '^-', 'DisplayName', 'LU with Complete Pivoting');
xlabel('Matrix Size (n)');
ylabel('Average Run Time (s)');
legend('Location', 'Best');
title('Comparison of LU Algorithms: Run Times');

% Plot relative errors
subplot(2, 1, 2);
semilogy(nValues, relErrors(:, 1), 'o-', 'DisplayName', 'LU without Pivoting');
hold on;
semilogy(nValues, relErrors(:, 2), 's-', 'DisplayName', 'LU with Partial Pivoting');
semilogy(nValues, relErrors(:, 3), '^-', 'DisplayName', 'LU with Complete Pivoting');
xlabel('Matrix Size (n)');
ylabel('Relative Error');
legend('Location', 'Best');
title('Comparison of LU Algorithms: Relative Errors');