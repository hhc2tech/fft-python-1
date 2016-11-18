t=0:0.001:2;
x=chirp(t,0,1,200);
plot(x);
fileID = fopen('CHIRP2.txt','w');
fprintf(fileID,'%12.8f ',x);
fclose(fileID);
