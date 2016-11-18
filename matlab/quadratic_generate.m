clear;

t = 0:0.001:2;
x = chirp(t, 100, 1, 200, 'quadratic');
plot(x);

fileID = fopen([pwd '/../data/quadratic.txt'], 'w');

fprintf(fileID, '%12.8f ', x);
fclose(fileID);
