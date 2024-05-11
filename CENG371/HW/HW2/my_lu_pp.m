function [L, U, P] = my_lu_pp(A)
    size = length(A);

    % P*A = L*U
    U = A; % Upper triangular matrix
    L = eye(size); % Lower triangular matrix
    P = eye(size); % Row permutation
    
    % Starting with first rows calculate factor and create L, U and P
    for y=1 : size-1
        % When deciding pivot take maximum of absolute values of numbers in the same column.
        % pivotRow is the index of the maximum absolute value
        [~, pivotRow] = max(abs(U(y:size, y)));
        pivotRow = pivotRow + y - 1;
        
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

        for x=y+1 : size
            factor = U(x, y) / U(y, y);
            L(x, y) = factor;
            U(x, :) = U(x, :) - factor * U(y, :);
        end
    end
end

% A2 = [-2, 2, -1; 6, -6, 7; 3, -8, 4];
% [L2, U2, P2] = my_lu_pp(A2);