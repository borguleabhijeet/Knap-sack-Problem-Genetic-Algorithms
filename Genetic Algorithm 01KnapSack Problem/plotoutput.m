clear all;
close all;
load('output.txt')
plot(output(:,2),'r')
hold on
plot(output(:,3),'b')
xlabel('Iteration')
ylabel('Profit')
legend('Profit','Weight')
