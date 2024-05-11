function [L, U] = my_lu(A)
    size = length(A);

    % A = L*U
    U = A; % Upper triangular matrix
    L = eye(size); % Lower triangular matrix
    
    % Starting with first rows calculate factor and create L and U
    for y=1 : size-1
        for x=y+1 : size
            factor = U(x, y) / U(y, y);
            L(x, y) = factor;
            U(x, :) = U(x, :) - factor * U(y, :);
        end
    end
end

% A1 = [1, -1, 2; 4, 0, 1; -3, 1, -3];
% [L1, U1] = my_lu(A1);