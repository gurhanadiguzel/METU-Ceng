function [L, U, P, Q] = my_lu_cp(A)
    size = length(A);
    
    % P*S*Q = L*U
    U = A; % Upper triangular matrix
    L = eye(size); % Lower triangular matrix
    P = eye(size); % Row permutation
    Q = eye(size); % Column permutation
    
    for y = 1:size-1
        [maxValue, pivotRow] = max(abs(U(y:size, y:size)));
        [~, pivotColumn] = max(maxValue);
        pivotRow = pivotRow(pivotColumn) + y - 1;
        pivotColumn = pivotColumn + y - 1;

         % Swap rows in U
        temp = U(y, :);
        U(y, :) = U(pivotRow, :);
        U(pivotRow, :) = temp;

        % Swap rows in L
        temp = L(y, 1:y-1);
        L(y, 1:y-1) = L(pivotRow, 1:y-1);
        L(pivotRow, 1:y-1) = temp;
       
        % Swap rows in P
        temp = P(y, :);
        P(y, :) = P(pivotRow, :);
        P(pivotRow, :) = temp;

        % Swap columns in U
        temp = U(:, y);
        U(:, y) = U(:, pivotColumn);
        U(:, pivotColumn) = temp;

        % Swap columns in Q
        temp = Q(:, y);
        Q(:, y) = Q(:, pivotColumn);
        Q(:, pivotColumn) = temp;

        for x = y+1:size
            factor = U(x, y) / U(y, y);
            L(x, y) = factor;
            U(x, y:end) = U(x, y:end) - factor * U(y, y:end);
        end
    end
end

% A3 = hilb(5);
% [L3, U3, P3, Q3] = my_lu_cp(A3);
