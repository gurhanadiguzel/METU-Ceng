rows = 5;  % number of rows
columns = 3;  % number of columns

% Initialize the matrix 
A = zeros(rows, columns);
b = zeros(rows,1);

for i = 1:rows
    for j = 1:columns
        A(i, j) = sqrt(i^2 + j^2);
    end
    b(i,1) = i;
end

%disp('Matrix A:')
%disp(A)

%disp('Matrix B:')
%disp(b)

augmentedMatrix = [A, b];
disp('Augmented Matrix [A | b]:')
disp(augmentedMatrix)

% Perform Gaussian elimination to get the row-echelon form
[rows, columns] = size(augmentedMatrix);

for i = 1:min(rows, columns-1)
    % Perform row swaps to get a non-zero pivot
    [~, pivot_row] = max(abs(augmentedMatrix(i:end, i)));
    pivot_row = pivot_row + i - 1;

    % Swap rows
    augmentedMatrix([i, pivot_row], :) = augmentedMatrix([pivot_row, i], :);

    % Eliminate below the pivot
    for j = i+1:rows
        factor = augmentedMatrix(j, i) / augmentedMatrix(i, i);
        augmentedMatrix(j, :) = augmentedMatrix(j, :) - factor * augmentedMatrix(i, :);
    end
end

% Display the row-echelon form
disp('Row-Echelon Form of Augmented Matrix:')
disp(augmentedMatrix)

