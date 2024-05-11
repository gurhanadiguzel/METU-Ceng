I = imread('tiger.png');
I = rgb2gray(I);

% Convert image matrix to double precision
I = double(I);

% Perform SVD
[U, S, V] = svd(I);

% Get the size of the image
[rows, columns] = size(I);
r = min(rows,columns);

% Compute low-rank approximations for various values of k
kValues = [r/2, r-10];
approximations = cell(1, r);
for k = 1:r
    A_k = U(:, 1:r-k) * S(1:r-k, 1:r-k) * V(:, 1:r-k)';
    approximations{k} = A_k;
end

% Display the original image
figure;
subplot(1, numel(kValues) + 1, 1);
imshow(uint8(I));
title('Original Image');

% Display the approximated images for specified values of k
for i = 1:numel(kValues)
    subplot(1, numel(kValues) + 1, i + 1);
    imshow(uint8(approximations{round(kValues(i))}));
    title(['k = ' num2str(kValues(i))]);
end

% Calculate S_k  
singularValues(1:r) = diag(S(1:r, 1:r));
singularValues = sort(singularValues, 'ascend');
singularValuesSquared = singularValues.^2;
cumulativeSum = cumsum(singularValuesSquared);
S_k = sqrt(cumulativeSum);

% Calculate Errors
errors = zeros(r, 1);
for i=1:r
    errors(i) = norm(I - approximations{i}, 'fro');
end

% Plot both S(k) and errors for k
figure;
loglog(1:r, S_k, 'r-', 'LineWidth', 2);
hold on;
loglog(1:r, errors, 'y--', 'LineWidth', 2);
xlabel('k');
ylabel('S_k & Errors');
title('S_k & Errors vs k');
legend('Location', 'Best');
grid on;
hold off;
